<शैली गुरु>
/* bnx2x_मुख्य.c: QLogic Everest network driver.
 *
 * Copyright (c) 2007-2013 Broadcom Corporation
 * Copyright (c) 2014 QLogic Corporation
 * All rights reserved
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * Maपूर्णांकained by: Ariel Elior <ariel.elior@qlogic.com>
 * Written by: Eliezer Tamir
 * Based on code from Michael Chan's bnx2 driver
 * UDP CSUM errata workaround by Arik Gendelman
 * Slowpath and fastpath rework by Vladislav Zolotarov
 * Statistics and Link management by Yitchak Gertner
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>  /* क्रम dev_info() */
#समावेश <linux/समयr.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/aer.h>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/bitops.h>
#समावेश <linux/irq.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/समय.स>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/crash_dump.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/tcp.h>
#समावेश <net/vxlan.h>
#समावेश <net/checksum.h>
#समावेश <net/ip6_checksum.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/crc32.h>
#समावेश <linux/crc32c.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/zlib.h>
#समावेश <linux/पन.स>
#समावेश <linux/semaphore.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश "bnx2x.h"
#समावेश "bnx2x_init.h"
#समावेश "bnx2x_init_ops.h"
#समावेश "bnx2x_cmn.h"
#समावेश "bnx2x_vfpf.h"
#समावेश "bnx2x_dcb.h"
#समावेश "bnx2x_sp.h"
#समावेश <linux/firmware.h>
#समावेश "bnx2x_fw_file_hdr.h"
/* FW files */
#घोषणा FW_खाता_VERSION					\
	__stringअगरy(BCM_5710_FW_MAJOR_VERSION) "."	\
	__stringअगरy(BCM_5710_FW_MINOR_VERSION) "."	\
	__stringअगरy(BCM_5710_FW_REVISION_VERSION) "."	\
	__stringअगरy(BCM_5710_FW_ENGINEERING_VERSION)
#घोषणा FW_खाता_NAME_E1		"bnx2x/bnx2x-e1-" FW_खाता_VERSION ".fw"
#घोषणा FW_खाता_NAME_E1H	"bnx2x/bnx2x-e1h-" FW_खाता_VERSION ".fw"
#घोषणा FW_खाता_NAME_E2		"bnx2x/bnx2x-e2-" FW_खाता_VERSION ".fw"

/* Time in jअगरfies beक्रमe concluding the transmitter is hung */
#घोषणा TX_TIMEOUT		(5*HZ)

MODULE_AUTHOR("Eliezer Tamir");
MODULE_DESCRIPTION("QLogic "
		   "BCM57710/57711/57711E/"
		   "57712/57712_MF/57800/57800_MF/57810/57810_MF/"
		   "57840/57840_MF Driver");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(FW_खाता_NAME_E1);
MODULE_FIRMWARE(FW_खाता_NAME_E1H);
MODULE_FIRMWARE(FW_खाता_NAME_E2);

पूर्णांक bnx2x_num_queues;
module_param_named(num_queues, bnx2x_num_queues, पूर्णांक, 0444);
MODULE_PARM_DESC(num_queues,
		 " Set number of queues (default is as a number of CPUs)");

अटल पूर्णांक disable_tpa;
module_param(disable_tpa, पूर्णांक, 0444);
MODULE_PARM_DESC(disable_tpa, " Disable the TPA (LRO) feature");

अटल पूर्णांक पूर्णांक_mode;
module_param(पूर्णांक_mode, पूर्णांक, 0444);
MODULE_PARM_DESC(पूर्णांक_mode, " Force interrupt mode other than MSI-X "
				"(1 INT#x; 2 MSI)");

अटल पूर्णांक dropless_fc;
module_param(dropless_fc, पूर्णांक, 0444);
MODULE_PARM_DESC(dropless_fc, " Pause on exhausted host ring");

अटल पूर्णांक mrrs = -1;
module_param(mrrs, पूर्णांक, 0444);
MODULE_PARM_DESC(mrrs, " Force Max Read Req Size (0..3) (for debug)");

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0444);
MODULE_PARM_DESC(debug, " Default debug msglevel");

अटल काष्ठा workqueue_काष्ठा *bnx2x_wq;
काष्ठा workqueue_काष्ठा *bnx2x_iov_wq;

काष्ठा bnx2x_mac_vals अणु
	u32 xmac_addr;
	u32 xmac_val;
	u32 emac_addr;
	u32 emac_val;
	u32 umac_addr[2];
	u32 umac_val[2];
	u32 bmac_addr;
	u32 bmac_val[2];
पूर्ण;

क्रमागत bnx2x_board_type अणु
	BCM57710 = 0,
	BCM57711,
	BCM57711E,
	BCM57712,
	BCM57712_MF,
	BCM57712_VF,
	BCM57800,
	BCM57800_MF,
	BCM57800_VF,
	BCM57810,
	BCM57810_MF,
	BCM57810_VF,
	BCM57840_4_10,
	BCM57840_2_20,
	BCM57840_MF,
	BCM57840_VF,
	BCM57811,
	BCM57811_MF,
	BCM57840_O,
	BCM57840_MFO,
	BCM57811_VF
पूर्ण;

/* indexed by board_type, above */
अटल काष्ठा अणु
	अक्षर *name;
पूर्ण board_info[] = अणु
	[BCM57710]	= अणु "QLogic BCM57710 10 Gigabit PCIe [Everest]" पूर्ण,
	[BCM57711]	= अणु "QLogic BCM57711 10 Gigabit PCIe" पूर्ण,
	[BCM57711E]	= अणु "QLogic BCM57711E 10 Gigabit PCIe" पूर्ण,
	[BCM57712]	= अणु "QLogic BCM57712 10 Gigabit Ethernet" पूर्ण,
	[BCM57712_MF]	= अणु "QLogic BCM57712 10 Gigabit Ethernet Multi Function" पूर्ण,
	[BCM57712_VF]	= अणु "QLogic BCM57712 10 Gigabit Ethernet Virtual Function" पूर्ण,
	[BCM57800]	= अणु "QLogic BCM57800 10 Gigabit Ethernet" पूर्ण,
	[BCM57800_MF]	= अणु "QLogic BCM57800 10 Gigabit Ethernet Multi Function" पूर्ण,
	[BCM57800_VF]	= अणु "QLogic BCM57800 10 Gigabit Ethernet Virtual Function" पूर्ण,
	[BCM57810]	= अणु "QLogic BCM57810 10 Gigabit Ethernet" पूर्ण,
	[BCM57810_MF]	= अणु "QLogic BCM57810 10 Gigabit Ethernet Multi Function" पूर्ण,
	[BCM57810_VF]	= अणु "QLogic BCM57810 10 Gigabit Ethernet Virtual Function" पूर्ण,
	[BCM57840_4_10]	= अणु "QLogic BCM57840 10 Gigabit Ethernet" पूर्ण,
	[BCM57840_2_20]	= अणु "QLogic BCM57840 20 Gigabit Ethernet" पूर्ण,
	[BCM57840_MF]	= अणु "QLogic BCM57840 10/20 Gigabit Ethernet Multi Function" पूर्ण,
	[BCM57840_VF]	= अणु "QLogic BCM57840 10/20 Gigabit Ethernet Virtual Function" पूर्ण,
	[BCM57811]	= अणु "QLogic BCM57811 10 Gigabit Ethernet" पूर्ण,
	[BCM57811_MF]	= अणु "QLogic BCM57811 10 Gigabit Ethernet Multi Function" पूर्ण,
	[BCM57840_O]	= अणु "QLogic BCM57840 10/20 Gigabit Ethernet" पूर्ण,
	[BCM57840_MFO]	= अणु "QLogic BCM57840 10/20 Gigabit Ethernet Multi Function" पूर्ण,
	[BCM57811_VF]	= अणु "QLogic BCM57840 10/20 Gigabit Ethernet Virtual Function" पूर्ण
पूर्ण;

#अगर_अघोषित PCI_DEVICE_ID_NX2_57710
#घोषणा PCI_DEVICE_ID_NX2_57710		CHIP_NUM_57710
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_NX2_57711
#घोषणा PCI_DEVICE_ID_NX2_57711		CHIP_NUM_57711
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_NX2_57711E
#घोषणा PCI_DEVICE_ID_NX2_57711E	CHIP_NUM_57711E
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_NX2_57712
#घोषणा PCI_DEVICE_ID_NX2_57712		CHIP_NUM_57712
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_NX2_57712_MF
#घोषणा PCI_DEVICE_ID_NX2_57712_MF	CHIP_NUM_57712_MF
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_NX2_57712_VF
#घोषणा PCI_DEVICE_ID_NX2_57712_VF	CHIP_NUM_57712_VF
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_NX2_57800
#घोषणा PCI_DEVICE_ID_NX2_57800		CHIP_NUM_57800
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_NX2_57800_MF
#घोषणा PCI_DEVICE_ID_NX2_57800_MF	CHIP_NUM_57800_MF
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_NX2_57800_VF
#घोषणा PCI_DEVICE_ID_NX2_57800_VF	CHIP_NUM_57800_VF
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_NX2_57810
#घोषणा PCI_DEVICE_ID_NX2_57810		CHIP_NUM_57810
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_NX2_57810_MF
#घोषणा PCI_DEVICE_ID_NX2_57810_MF	CHIP_NUM_57810_MF
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_NX2_57840_O
#घोषणा PCI_DEVICE_ID_NX2_57840_O	CHIP_NUM_57840_OBSOLETE
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_NX2_57810_VF
#घोषणा PCI_DEVICE_ID_NX2_57810_VF	CHIP_NUM_57810_VF
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_NX2_57840_4_10
#घोषणा PCI_DEVICE_ID_NX2_57840_4_10	CHIP_NUM_57840_4_10
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_NX2_57840_2_20
#घोषणा PCI_DEVICE_ID_NX2_57840_2_20	CHIP_NUM_57840_2_20
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_NX2_57840_MFO
#घोषणा PCI_DEVICE_ID_NX2_57840_MFO	CHIP_NUM_57840_MF_OBSOLETE
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_NX2_57840_MF
#घोषणा PCI_DEVICE_ID_NX2_57840_MF	CHIP_NUM_57840_MF
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_NX2_57840_VF
#घोषणा PCI_DEVICE_ID_NX2_57840_VF	CHIP_NUM_57840_VF
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_NX2_57811
#घोषणा PCI_DEVICE_ID_NX2_57811		CHIP_NUM_57811
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_NX2_57811_MF
#घोषणा PCI_DEVICE_ID_NX2_57811_MF	CHIP_NUM_57811_MF
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_NX2_57811_VF
#घोषणा PCI_DEVICE_ID_NX2_57811_VF	CHIP_NUM_57811_VF
#पूर्ण_अगर

अटल स्थिर काष्ठा pci_device_id bnx2x_pci_tbl[] = अणु
	अणु PCI_VDEVICE(BROADCOM, PCI_DEVICE_ID_NX2_57710), BCM57710 पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, PCI_DEVICE_ID_NX2_57711), BCM57711 पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, PCI_DEVICE_ID_NX2_57711E), BCM57711E पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, PCI_DEVICE_ID_NX2_57712), BCM57712 पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, PCI_DEVICE_ID_NX2_57712_MF), BCM57712_MF पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, PCI_DEVICE_ID_NX2_57712_VF), BCM57712_VF पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, PCI_DEVICE_ID_NX2_57800), BCM57800 पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, PCI_DEVICE_ID_NX2_57800_MF), BCM57800_MF पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, PCI_DEVICE_ID_NX2_57800_VF), BCM57800_VF पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, PCI_DEVICE_ID_NX2_57810), BCM57810 पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, PCI_DEVICE_ID_NX2_57810_MF), BCM57810_MF पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, PCI_DEVICE_ID_NX2_57840_O), BCM57840_O पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, PCI_DEVICE_ID_NX2_57840_4_10), BCM57840_4_10 पूर्ण,
	अणु PCI_VDEVICE(QLOGIC,	PCI_DEVICE_ID_NX2_57840_4_10), BCM57840_4_10 पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, PCI_DEVICE_ID_NX2_57840_2_20), BCM57840_2_20 पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, PCI_DEVICE_ID_NX2_57810_VF), BCM57810_VF पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, PCI_DEVICE_ID_NX2_57840_MFO), BCM57840_MFO पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, PCI_DEVICE_ID_NX2_57840_MF), BCM57840_MF पूर्ण,
	अणु PCI_VDEVICE(QLOGIC,	PCI_DEVICE_ID_NX2_57840_MF), BCM57840_MF पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, PCI_DEVICE_ID_NX2_57840_VF), BCM57840_VF पूर्ण,
	अणु PCI_VDEVICE(QLOGIC,	PCI_DEVICE_ID_NX2_57840_VF), BCM57840_VF पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, PCI_DEVICE_ID_NX2_57811), BCM57811 पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, PCI_DEVICE_ID_NX2_57811_MF), BCM57811_MF पूर्ण,
	अणु PCI_VDEVICE(BROADCOM, PCI_DEVICE_ID_NX2_57811_VF), BCM57811_VF पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, bnx2x_pci_tbl);

स्थिर u32 dmae_reg_go_c[] = अणु
	DMAE_REG_GO_C0, DMAE_REG_GO_C1, DMAE_REG_GO_C2, DMAE_REG_GO_C3,
	DMAE_REG_GO_C4, DMAE_REG_GO_C5, DMAE_REG_GO_C6, DMAE_REG_GO_C7,
	DMAE_REG_GO_C8, DMAE_REG_GO_C9, DMAE_REG_GO_C10, DMAE_REG_GO_C11,
	DMAE_REG_GO_C12, DMAE_REG_GO_C13, DMAE_REG_GO_C14, DMAE_REG_GO_C15
पूर्ण;

/* Global resources क्रम unloading a previously loaded device */
#घोषणा BNX2X_PREV_WAIT_NEEDED 1
अटल DEFINE_SEMAPHORE(bnx2x_prev_sem);
अटल LIST_HEAD(bnx2x_prev_list);

/* Forward declaration */
अटल काष्ठा cnic_eth_dev *bnx2x_cnic_probe(काष्ठा net_device *dev);
अटल u32 bnx2x_rx_ustorm_prods_offset(काष्ठा bnx2x_fastpath *fp);
अटल पूर्णांक bnx2x_set_storm_rx_mode(काष्ठा bnx2x *bp);

/****************************************************************************
* General service functions
****************************************************************************/

अटल पूर्णांक bnx2x_hwtstamp_ioctl(काष्ठा bnx2x *bp, काष्ठा अगरreq *अगरr);

अटल व्योम __storm_स_रखो_dma_mapping(काष्ठा bnx2x *bp,
				       u32 addr, dma_addr_t mapping)
अणु
	REG_WR(bp,  addr, U64_LO(mapping));
	REG_WR(bp,  addr + 4, U64_HI(mapping));
पूर्ण

अटल व्योम storm_स_रखो_spq_addr(काष्ठा bnx2x *bp,
				  dma_addr_t mapping, u16 असल_fid)
अणु
	u32 addr = XSEM_REG_FAST_MEMORY +
			XSTORM_SPQ_PAGE_BASE_OFFSET(असल_fid);

	__storm_स_रखो_dma_mapping(bp, addr, mapping);
पूर्ण

अटल व्योम storm_स_रखो_vf_to_pf(काष्ठा bnx2x *bp, u16 असल_fid,
				  u16 pf_id)
अणु
	REG_WR8(bp, BAR_XSTRORM_INTMEM + XSTORM_VF_TO_PF_OFFSET(असल_fid),
		pf_id);
	REG_WR8(bp, BAR_CSTRORM_INTMEM + CSTORM_VF_TO_PF_OFFSET(असल_fid),
		pf_id);
	REG_WR8(bp, BAR_TSTRORM_INTMEM + TSTORM_VF_TO_PF_OFFSET(असल_fid),
		pf_id);
	REG_WR8(bp, BAR_USTRORM_INTMEM + USTORM_VF_TO_PF_OFFSET(असल_fid),
		pf_id);
पूर्ण

अटल व्योम storm_स_रखो_func_en(काष्ठा bnx2x *bp, u16 असल_fid,
				 u8 enable)
अणु
	REG_WR8(bp, BAR_XSTRORM_INTMEM + XSTORM_FUNC_EN_OFFSET(असल_fid),
		enable);
	REG_WR8(bp, BAR_CSTRORM_INTMEM + CSTORM_FUNC_EN_OFFSET(असल_fid),
		enable);
	REG_WR8(bp, BAR_TSTRORM_INTMEM + TSTORM_FUNC_EN_OFFSET(असल_fid),
		enable);
	REG_WR8(bp, BAR_USTRORM_INTMEM + USTORM_FUNC_EN_OFFSET(असल_fid),
		enable);
पूर्ण

अटल व्योम storm_स_रखो_eq_data(काष्ठा bnx2x *bp,
				 काष्ठा event_ring_data *eq_data,
				u16 pfid)
अणु
	माप_प्रकार size = माप(काष्ठा event_ring_data);

	u32 addr = BAR_CSTRORM_INTMEM + CSTORM_EVENT_RING_DATA_OFFSET(pfid);

	__storm_स_रखो_काष्ठा(bp, addr, size, (u32 *)eq_data);
पूर्ण

अटल व्योम storm_स_रखो_eq_prod(काष्ठा bnx2x *bp, u16 eq_prod,
				 u16 pfid)
अणु
	u32 addr = BAR_CSTRORM_INTMEM + CSTORM_EVENT_RING_PROD_OFFSET(pfid);
	REG_WR16(bp, addr, eq_prod);
पूर्ण

/* used only at init
 * locking is करोne by mcp
 */
अटल व्योम bnx2x_reg_wr_ind(काष्ठा bnx2x *bp, u32 addr, u32 val)
अणु
	pci_ग_लिखो_config_dword(bp->pdev, PCICFG_GRC_ADDRESS, addr);
	pci_ग_लिखो_config_dword(bp->pdev, PCICFG_GRC_DATA, val);
	pci_ग_लिखो_config_dword(bp->pdev, PCICFG_GRC_ADDRESS,
			       PCICFG_VENDOR_ID_OFFSET);
पूर्ण

अटल u32 bnx2x_reg_rd_ind(काष्ठा bnx2x *bp, u32 addr)
अणु
	u32 val;

	pci_ग_लिखो_config_dword(bp->pdev, PCICFG_GRC_ADDRESS, addr);
	pci_पढ़ो_config_dword(bp->pdev, PCICFG_GRC_DATA, &val);
	pci_ग_लिखो_config_dword(bp->pdev, PCICFG_GRC_ADDRESS,
			       PCICFG_VENDOR_ID_OFFSET);

	वापस val;
पूर्ण

#घोषणा DMAE_DP_SRC_GRC		"grc src_addr [%08x]"
#घोषणा DMAE_DP_SRC_PCI		"pci src_addr [%x:%08x]"
#घोषणा DMAE_DP_DST_GRC		"grc dst_addr [%08x]"
#घोषणा DMAE_DP_DST_PCI		"pci dst_addr [%x:%08x]"
#घोषणा DMAE_DP_DST_NONE	"dst_addr [none]"

अटल व्योम bnx2x_dp_dmae(काष्ठा bnx2x *bp,
			  काष्ठा dmae_command *dmae, पूर्णांक msglvl)
अणु
	u32 src_type = dmae->opcode & DMAE_COMMAND_SRC;
	पूर्णांक i;

	चयन (dmae->opcode & DMAE_COMMAND_DST) अणु
	हाल DMAE_CMD_DST_PCI:
		अगर (src_type == DMAE_CMD_SRC_PCI)
			DP(msglvl, "DMAE: opcode 0x%08x\n"
			   "src [%x:%08x], len [%d*4], dst [%x:%08x]\n"
			   "comp_addr [%x:%08x], comp_val 0x%08x\n",
			   dmae->opcode, dmae->src_addr_hi, dmae->src_addr_lo,
			   dmae->len, dmae->dst_addr_hi, dmae->dst_addr_lo,
			   dmae->comp_addr_hi, dmae->comp_addr_lo,
			   dmae->comp_val);
		अन्यथा
			DP(msglvl, "DMAE: opcode 0x%08x\n"
			   "src [%08x], len [%d*4], dst [%x:%08x]\n"
			   "comp_addr [%x:%08x], comp_val 0x%08x\n",
			   dmae->opcode, dmae->src_addr_lo >> 2,
			   dmae->len, dmae->dst_addr_hi, dmae->dst_addr_lo,
			   dmae->comp_addr_hi, dmae->comp_addr_lo,
			   dmae->comp_val);
		अवरोध;
	हाल DMAE_CMD_DST_GRC:
		अगर (src_type == DMAE_CMD_SRC_PCI)
			DP(msglvl, "DMAE: opcode 0x%08x\n"
			   "src [%x:%08x], len [%d*4], dst_addr [%08x]\n"
			   "comp_addr [%x:%08x], comp_val 0x%08x\n",
			   dmae->opcode, dmae->src_addr_hi, dmae->src_addr_lo,
			   dmae->len, dmae->dst_addr_lo >> 2,
			   dmae->comp_addr_hi, dmae->comp_addr_lo,
			   dmae->comp_val);
		अन्यथा
			DP(msglvl, "DMAE: opcode 0x%08x\n"
			   "src [%08x], len [%d*4], dst [%08x]\n"
			   "comp_addr [%x:%08x], comp_val 0x%08x\n",
			   dmae->opcode, dmae->src_addr_lo >> 2,
			   dmae->len, dmae->dst_addr_lo >> 2,
			   dmae->comp_addr_hi, dmae->comp_addr_lo,
			   dmae->comp_val);
		अवरोध;
	शेष:
		अगर (src_type == DMAE_CMD_SRC_PCI)
			DP(msglvl, "DMAE: opcode 0x%08x\n"
			   "src_addr [%x:%08x]  len [%d * 4]  dst_addr [none]\n"
			   "comp_addr [%x:%08x]  comp_val 0x%08x\n",
			   dmae->opcode, dmae->src_addr_hi, dmae->src_addr_lo,
			   dmae->len, dmae->comp_addr_hi, dmae->comp_addr_lo,
			   dmae->comp_val);
		अन्यथा
			DP(msglvl, "DMAE: opcode 0x%08x\n"
			   "src_addr [%08x]  len [%d * 4]  dst_addr [none]\n"
			   "comp_addr [%x:%08x]  comp_val 0x%08x\n",
			   dmae->opcode, dmae->src_addr_lo >> 2,
			   dmae->len, dmae->comp_addr_hi, dmae->comp_addr_lo,
			   dmae->comp_val);
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < (माप(काष्ठा dmae_command)/4); i++)
		DP(msglvl, "DMAE RAW [%02d]: 0x%08x\n",
		   i, *(((u32 *)dmae) + i));
पूर्ण

/* copy command पूर्णांकo DMAE command memory and set DMAE command go */
व्योम bnx2x_post_dmae(काष्ठा bnx2x *bp, काष्ठा dmae_command *dmae, पूर्णांक idx)
अणु
	u32 cmd_offset;
	पूर्णांक i;

	cmd_offset = (DMAE_REG_CMD_MEM + माप(काष्ठा dmae_command) * idx);
	क्रम (i = 0; i < (माप(काष्ठा dmae_command)/4); i++) अणु
		REG_WR(bp, cmd_offset + i*4, *(((u32 *)dmae) + i));
	पूर्ण
	REG_WR(bp, dmae_reg_go_c[idx], 1);
पूर्ण

u32 bnx2x_dmae_opcode_add_comp(u32 opcode, u8 comp_type)
अणु
	वापस opcode | ((comp_type << DMAE_COMMAND_C_DST_SHIFT) |
			   DMAE_CMD_C_ENABLE);
पूर्ण

u32 bnx2x_dmae_opcode_clr_src_reset(u32 opcode)
अणु
	वापस opcode & ~DMAE_CMD_SRC_RESET;
पूर्ण

u32 bnx2x_dmae_opcode(काष्ठा bnx2x *bp, u8 src_type, u8 dst_type,
			     bool with_comp, u8 comp_type)
अणु
	u32 opcode = 0;

	opcode |= ((src_type << DMAE_COMMAND_SRC_SHIFT) |
		   (dst_type << DMAE_COMMAND_DST_SHIFT));

	opcode |= (DMAE_CMD_SRC_RESET | DMAE_CMD_DST_RESET);

	opcode |= (BP_PORT(bp) ? DMAE_CMD_PORT_1 : DMAE_CMD_PORT_0);
	opcode |= ((BP_VN(bp) << DMAE_CMD_E1HVN_SHIFT) |
		   (BP_VN(bp) << DMAE_COMMAND_DST_VN_SHIFT));
	opcode |= (DMAE_COM_SET_ERR << DMAE_COMMAND_ERR_POLICY_SHIFT);

#अगर_घोषित __BIG_ENDIAN
	opcode |= DMAE_CMD_ENDIANITY_B_DW_SWAP;
#अन्यथा
	opcode |= DMAE_CMD_ENDIANITY_DW_SWAP;
#पूर्ण_अगर
	अगर (with_comp)
		opcode = bnx2x_dmae_opcode_add_comp(opcode, comp_type);
	वापस opcode;
पूर्ण

व्योम bnx2x_prep_dmae_with_comp(काष्ठा bnx2x *bp,
				      काष्ठा dmae_command *dmae,
				      u8 src_type, u8 dst_type)
अणु
	स_रखो(dmae, 0, माप(काष्ठा dmae_command));

	/* set the opcode */
	dmae->opcode = bnx2x_dmae_opcode(bp, src_type, dst_type,
					 true, DMAE_COMP_PCI);

	/* fill in the completion parameters */
	dmae->comp_addr_lo = U64_LO(bnx2x_sp_mapping(bp, wb_comp));
	dmae->comp_addr_hi = U64_HI(bnx2x_sp_mapping(bp, wb_comp));
	dmae->comp_val = DMAE_COMP_VAL;
पूर्ण

/* issue a dmae command over the init-channel and रुको क्रम completion */
पूर्णांक bnx2x_issue_dmae_with_comp(काष्ठा bnx2x *bp, काष्ठा dmae_command *dmae,
			       u32 *comp)
अणु
	पूर्णांक cnt = CHIP_REV_IS_SLOW(bp) ? (400000) : 4000;
	पूर्णांक rc = 0;

	bnx2x_dp_dmae(bp, dmae, BNX2X_MSG_DMAE);

	/* Lock the dmae channel. Disable BHs to prevent a dead-lock
	 * as दीर्घ as this code is called both from syscall context and
	 * from nकरो_set_rx_mode() flow that may be called from BH.
	 */

	spin_lock_bh(&bp->dmae_lock);

	/* reset completion */
	*comp = 0;

	/* post the command on the channel used क्रम initializations */
	bnx2x_post_dmae(bp, dmae, INIT_DMAE_C(bp));

	/* रुको क्रम completion */
	udelay(5);
	जबतक ((*comp & ~DMAE_PCI_ERR_FLAG) != DMAE_COMP_VAL) अणु

		अगर (!cnt ||
		    (bp->recovery_state != BNX2X_RECOVERY_DONE &&
		     bp->recovery_state != BNX2X_RECOVERY_NIC_LOADING)) अणु
			BNX2X_ERR("DMAE timeout!\n");
			rc = DMAE_TIMEOUT;
			जाओ unlock;
		पूर्ण
		cnt--;
		udelay(50);
	पूर्ण
	अगर (*comp & DMAE_PCI_ERR_FLAG) अणु
		BNX2X_ERR("DMAE PCI error!\n");
		rc = DMAE_PCI_ERROR;
	पूर्ण

unlock:

	spin_unlock_bh(&bp->dmae_lock);

	वापस rc;
पूर्ण

व्योम bnx2x_ग_लिखो_dmae(काष्ठा bnx2x *bp, dma_addr_t dma_addr, u32 dst_addr,
		      u32 len32)
अणु
	पूर्णांक rc;
	काष्ठा dmae_command dmae;

	अगर (!bp->dmae_पढ़ोy) अणु
		u32 *data = bnx2x_sp(bp, wb_data[0]);

		अगर (CHIP_IS_E1(bp))
			bnx2x_init_ind_wr(bp, dst_addr, data, len32);
		अन्यथा
			bnx2x_init_str_wr(bp, dst_addr, data, len32);
		वापस;
	पूर्ण

	/* set opcode and fixed command fields */
	bnx2x_prep_dmae_with_comp(bp, &dmae, DMAE_SRC_PCI, DMAE_DST_GRC);

	/* fill in addresses and len */
	dmae.src_addr_lo = U64_LO(dma_addr);
	dmae.src_addr_hi = U64_HI(dma_addr);
	dmae.dst_addr_lo = dst_addr >> 2;
	dmae.dst_addr_hi = 0;
	dmae.len = len32;

	/* issue the command and रुको क्रम completion */
	rc = bnx2x_issue_dmae_with_comp(bp, &dmae, bnx2x_sp(bp, wb_comp));
	अगर (rc) अणु
		BNX2X_ERR("DMAE returned failure %d\n", rc);
#अगर_घोषित BNX2X_STOP_ON_ERROR
		bnx2x_panic();
#पूर्ण_अगर
	पूर्ण
पूर्ण

व्योम bnx2x_पढ़ो_dmae(काष्ठा bnx2x *bp, u32 src_addr, u32 len32)
अणु
	पूर्णांक rc;
	काष्ठा dmae_command dmae;

	अगर (!bp->dmae_पढ़ोy) अणु
		u32 *data = bnx2x_sp(bp, wb_data[0]);
		पूर्णांक i;

		अगर (CHIP_IS_E1(bp))
			क्रम (i = 0; i < len32; i++)
				data[i] = bnx2x_reg_rd_ind(bp, src_addr + i*4);
		अन्यथा
			क्रम (i = 0; i < len32; i++)
				data[i] = REG_RD(bp, src_addr + i*4);

		वापस;
	पूर्ण

	/* set opcode and fixed command fields */
	bnx2x_prep_dmae_with_comp(bp, &dmae, DMAE_SRC_GRC, DMAE_DST_PCI);

	/* fill in addresses and len */
	dmae.src_addr_lo = src_addr >> 2;
	dmae.src_addr_hi = 0;
	dmae.dst_addr_lo = U64_LO(bnx2x_sp_mapping(bp, wb_data));
	dmae.dst_addr_hi = U64_HI(bnx2x_sp_mapping(bp, wb_data));
	dmae.len = len32;

	/* issue the command and रुको क्रम completion */
	rc = bnx2x_issue_dmae_with_comp(bp, &dmae, bnx2x_sp(bp, wb_comp));
	अगर (rc) अणु
		BNX2X_ERR("DMAE returned failure %d\n", rc);
#अगर_घोषित BNX2X_STOP_ON_ERROR
		bnx2x_panic();
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल व्योम bnx2x_ग_लिखो_dmae_phys_len(काष्ठा bnx2x *bp, dma_addr_t phys_addr,
				      u32 addr, u32 len)
अणु
	पूर्णांक dmae_wr_max = DMAE_LEN32_WR_MAX(bp);
	पूर्णांक offset = 0;

	जबतक (len > dmae_wr_max) अणु
		bnx2x_ग_लिखो_dmae(bp, phys_addr + offset,
				 addr + offset, dmae_wr_max);
		offset += dmae_wr_max * 4;
		len -= dmae_wr_max;
	पूर्ण

	bnx2x_ग_लिखो_dmae(bp, phys_addr + offset, addr + offset, len);
पूर्ण

क्रमागत storms अणु
	   XSTORM,
	   TSTORM,
	   CSTORM,
	   USTORM,
	   MAX_STORMS
पूर्ण;

#घोषणा STORMS_NUM 4
#घोषणा REGS_IN_ENTRY 4

अटल अंतरभूत पूर्णांक bnx2x_get_निश्चित_list_entry(काष्ठा bnx2x *bp,
					      क्रमागत storms storm,
					      पूर्णांक entry)
अणु
	चयन (storm) अणु
	हाल XSTORM:
		वापस XSTORM_ASSERT_LIST_OFFSET(entry);
	हाल TSTORM:
		वापस TSTORM_ASSERT_LIST_OFFSET(entry);
	हाल CSTORM:
		वापस CSTORM_ASSERT_LIST_OFFSET(entry);
	हाल USTORM:
		वापस USTORM_ASSERT_LIST_OFFSET(entry);
	हाल MAX_STORMS:
	शेष:
		BNX2X_ERR("unknown storm\n");
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक bnx2x_mc_निश्चित(काष्ठा bnx2x *bp)
अणु
	अक्षर last_idx;
	पूर्णांक i, j, rc = 0;
	क्रमागत storms storm;
	u32 regs[REGS_IN_ENTRY];
	u32 bar_storm_पूर्णांकmem[STORMS_NUM] = अणु
		BAR_XSTRORM_INTMEM,
		BAR_TSTRORM_INTMEM,
		BAR_CSTRORM_INTMEM,
		BAR_USTRORM_INTMEM
	पूर्ण;
	u32 storm_निश्चित_list_index[STORMS_NUM] = अणु
		XSTORM_ASSERT_LIST_INDEX_OFFSET,
		TSTORM_ASSERT_LIST_INDEX_OFFSET,
		CSTORM_ASSERT_LIST_INDEX_OFFSET,
		USTORM_ASSERT_LIST_INDEX_OFFSET
	पूर्ण;
	अक्षर *storms_string[STORMS_NUM] = अणु
		"XSTORM",
		"TSTORM",
		"CSTORM",
		"USTORM"
	पूर्ण;

	क्रम (storm = XSTORM; storm < MAX_STORMS; storm++) अणु
		last_idx = REG_RD8(bp, bar_storm_पूर्णांकmem[storm] +
				   storm_निश्चित_list_index[storm]);
		अगर (last_idx)
			BNX2X_ERR("%s_ASSERT_LIST_INDEX 0x%x\n",
				  storms_string[storm], last_idx);

		/* prपूर्णांक the निश्चितs */
		क्रम (i = 0; i < STROM_ASSERT_ARRAY_SIZE; i++) अणु
			/* पढ़ो a single निश्चित entry */
			क्रम (j = 0; j < REGS_IN_ENTRY; j++)
				regs[j] = REG_RD(bp, bar_storm_पूर्णांकmem[storm] +
					  bnx2x_get_निश्चित_list_entry(bp,
								      storm,
								      i) +
					  माप(u32) * j);

			/* log entry अगर it contains a valid निश्चित */
			अगर (regs[0] != COMMON_ASM_INVALID_ASSERT_OPCODE) अणु
				BNX2X_ERR("%s_ASSERT_INDEX 0x%x = 0x%08x 0x%08x 0x%08x 0x%08x\n",
					  storms_string[storm], i, regs[3],
					  regs[2], regs[1], regs[0]);
				rc++;
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	BNX2X_ERR("Chip Revision: %s, FW Version: %d_%d_%d\n",
		  CHIP_IS_E1(bp) ? "everest1" :
		  CHIP_IS_E1H(bp) ? "everest1h" :
		  CHIP_IS_E2(bp) ? "everest2" : "everest3",
		  BCM_5710_FW_MAJOR_VERSION,
		  BCM_5710_FW_MINOR_VERSION,
		  BCM_5710_FW_REVISION_VERSION);

	वापस rc;
पूर्ण

#घोषणा MCPR_TRACE_BUFFER_SIZE	(0x800)
#घोषणा SCRATCH_BUFFER_SIZE(bp)	\
	(CHIP_IS_E1(bp) ? 0x10000 : (CHIP_IS_E1H(bp) ? 0x20000 : 0x28000))

व्योम bnx2x_fw_dump_lvl(काष्ठा bnx2x *bp, स्थिर अक्षर *lvl)
अणु
	u32 addr, val;
	u32 mark, offset;
	__be32 data[9];
	पूर्णांक word;
	u32 trace_shmem_base;
	अगर (BP_NOMCP(bp)) अणु
		BNX2X_ERR("NO MCP - can not dump\n");
		वापस;
	पूर्ण
	netdev_prपूर्णांकk(lvl, bp->dev, "bc %d.%d.%d\n",
		(bp->common.bc_ver & 0xff0000) >> 16,
		(bp->common.bc_ver & 0xff00) >> 8,
		(bp->common.bc_ver & 0xff));

	अगर (pci_channel_offline(bp->pdev)) अणु
		BNX2X_ERR("Cannot dump MCP info while in PCI error\n");
		वापस;
	पूर्ण

	val = REG_RD(bp, MCP_REG_MCPR_CPU_PROGRAM_COUNTER);
	अगर (val == REG_RD(bp, MCP_REG_MCPR_CPU_PROGRAM_COUNTER))
		BNX2X_ERR("%s" "MCP PC at 0x%x\n", lvl, val);

	अगर (BP_PATH(bp) == 0)
		trace_shmem_base = bp->common.shmem_base;
	अन्यथा
		trace_shmem_base = SHMEM2_RD(bp, other_shmem_base_addr);

	/* sanity */
	अगर (trace_shmem_base < MCPR_SCRATCH_BASE(bp) + MCPR_TRACE_BUFFER_SIZE ||
	    trace_shmem_base >= MCPR_SCRATCH_BASE(bp) +
				SCRATCH_BUFFER_SIZE(bp)) अणु
		BNX2X_ERR("Unable to dump trace buffer (mark %x)\n",
			  trace_shmem_base);
		वापस;
	पूर्ण

	addr = trace_shmem_base - MCPR_TRACE_BUFFER_SIZE;

	/* validate TRCB signature */
	mark = REG_RD(bp, addr);
	अगर (mark != MFW_TRACE_SIGNATURE) अणु
		BNX2X_ERR("Trace buffer signature is missing.");
		वापस ;
	पूर्ण

	/* पढ़ो cyclic buffer poपूर्णांकer */
	addr += 4;
	mark = REG_RD(bp, addr);
	mark = MCPR_SCRATCH_BASE(bp) + ((mark + 0x3) & ~0x3) - 0x08000000;
	अगर (mark >= trace_shmem_base || mark < addr + 4) अणु
		BNX2X_ERR("Mark doesn't fall inside Trace Buffer\n");
		वापस;
	पूर्ण
	prपूर्णांकk("%s" "begin fw dump (mark 0x%x)\n", lvl, mark);

	prपूर्णांकk("%s", lvl);

	/* dump buffer after the mark */
	क्रम (offset = mark; offset < trace_shmem_base; offset += 0x8*4) अणु
		क्रम (word = 0; word < 8; word++)
			data[word] = htonl(REG_RD(bp, offset + 4*word));
		data[8] = 0x0;
		pr_cont("%s", (अक्षर *)data);
	पूर्ण

	/* dump buffer beक्रमe the mark */
	क्रम (offset = addr + 4; offset <= mark; offset += 0x8*4) अणु
		क्रम (word = 0; word < 8; word++)
			data[word] = htonl(REG_RD(bp, offset + 4*word));
		data[8] = 0x0;
		pr_cont("%s", (अक्षर *)data);
	पूर्ण
	prपूर्णांकk("%s" "end of fw dump\n", lvl);
पूर्ण

अटल व्योम bnx2x_fw_dump(काष्ठा bnx2x *bp)
अणु
	bnx2x_fw_dump_lvl(bp, KERN_ERR);
पूर्ण

अटल व्योम bnx2x_hc_पूर्णांक_disable(काष्ठा bnx2x *bp)
अणु
	पूर्णांक port = BP_PORT(bp);
	u32 addr = port ? HC_REG_CONFIG_1 : HC_REG_CONFIG_0;
	u32 val = REG_RD(bp, addr);

	/* in E1 we must use only PCI configuration space to disable
	 * MSI/MSIX capability
	 * It's क्रमbidden to disable IGU_PF_CONF_MSI_MSIX_EN in HC block
	 */
	अगर (CHIP_IS_E1(bp)) अणु
		/* Since IGU_PF_CONF_MSI_MSIX_EN still always on
		 * Use mask रेजिस्टर to prevent from HC sending पूर्णांकerrupts
		 * after we निकास the function
		 */
		REG_WR(bp, HC_REG_INT_MASK + port*4, 0);

		val &= ~(HC_CONFIG_0_REG_SINGLE_ISR_EN_0 |
			 HC_CONFIG_0_REG_INT_LINE_EN_0 |
			 HC_CONFIG_0_REG_ATTN_BIT_EN_0);
	पूर्ण अन्यथा
		val &= ~(HC_CONFIG_0_REG_SINGLE_ISR_EN_0 |
			 HC_CONFIG_0_REG_MSI_MSIX_INT_EN_0 |
			 HC_CONFIG_0_REG_INT_LINE_EN_0 |
			 HC_CONFIG_0_REG_ATTN_BIT_EN_0);

	DP(NETIF_MSG_IFDOWN,
	   "write %x to HC %d (addr 0x%x)\n",
	   val, port, addr);

	REG_WR(bp, addr, val);
	अगर (REG_RD(bp, addr) != val)
		BNX2X_ERR("BUG! Proper val not read from IGU!\n");
पूर्ण

अटल व्योम bnx2x_igu_पूर्णांक_disable(काष्ठा bnx2x *bp)
अणु
	u32 val = REG_RD(bp, IGU_REG_PF_CONFIGURATION);

	val &= ~(IGU_PF_CONF_MSI_MSIX_EN |
		 IGU_PF_CONF_INT_LINE_EN |
		 IGU_PF_CONF_ATTN_BIT_EN);

	DP(NETIF_MSG_IFDOWN, "write %x to IGU\n", val);

	REG_WR(bp, IGU_REG_PF_CONFIGURATION, val);
	अगर (REG_RD(bp, IGU_REG_PF_CONFIGURATION) != val)
		BNX2X_ERR("BUG! Proper val not read from IGU!\n");
पूर्ण

अटल व्योम bnx2x_पूर्णांक_disable(काष्ठा bnx2x *bp)
अणु
	अगर (bp->common.पूर्णांक_block == INT_BLOCK_HC)
		bnx2x_hc_पूर्णांक_disable(bp);
	अन्यथा
		bnx2x_igu_पूर्णांक_disable(bp);
पूर्ण

व्योम bnx2x_panic_dump(काष्ठा bnx2x *bp, bool disable_पूर्णांक)
अणु
	पूर्णांक i;
	u16 j;
	काष्ठा hc_sp_status_block_data sp_sb_data;
	पूर्णांक func = BP_FUNC(bp);
#अगर_घोषित BNX2X_STOP_ON_ERROR
	u16 start = 0, end = 0;
	u8 cos;
#पूर्ण_अगर
	अगर (IS_PF(bp) && disable_पूर्णांक)
		bnx2x_पूर्णांक_disable(bp);

	bp->stats_state = STATS_STATE_DISABLED;
	bp->eth_stats.unrecoverable_error++;
	DP(BNX2X_MSG_STATS, "stats_state - DISABLED\n");

	BNX2X_ERR("begin crash dump -----------------\n");

	/* Indices */
	/* Common */
	अगर (IS_PF(bp)) अणु
		काष्ठा host_sp_status_block *def_sb = bp->def_status_blk;
		पूर्णांक data_size, cstorm_offset;

		BNX2X_ERR("def_idx(0x%x)  def_att_idx(0x%x)  attn_state(0x%x)  spq_prod_idx(0x%x) next_stats_cnt(0x%x)\n",
			  bp->def_idx, bp->def_att_idx, bp->attn_state,
			  bp->spq_prod_idx, bp->stats_counter);
		BNX2X_ERR("DSB: attn bits(0x%x)  ack(0x%x)  id(0x%x)  idx(0x%x)\n",
			  def_sb->atten_status_block.attn_bits,
			  def_sb->atten_status_block.attn_bits_ack,
			  def_sb->atten_status_block.status_block_id,
			  def_sb->atten_status_block.attn_bits_index);
		BNX2X_ERR("     def (");
		क्रम (i = 0; i < HC_SP_SB_MAX_INDICES; i++)
			pr_cont("0x%x%s",
				def_sb->sp_sb.index_values[i],
				(i == HC_SP_SB_MAX_INDICES - 1) ? ")  " : " ");

		data_size = माप(काष्ठा hc_sp_status_block_data) /
			    माप(u32);
		cstorm_offset = CSTORM_SP_STATUS_BLOCK_DATA_OFFSET(func);
		क्रम (i = 0; i < data_size; i++)
			*((u32 *)&sp_sb_data + i) =
				REG_RD(bp, BAR_CSTRORM_INTMEM + cstorm_offset +
					   i * माप(u32));

		pr_cont("igu_sb_id(0x%x)  igu_seg_id(0x%x) pf_id(0x%x)  vnic_id(0x%x)  vf_id(0x%x)  vf_valid (0x%x) state(0x%x)\n",
			sp_sb_data.igu_sb_id,
			sp_sb_data.igu_seg_id,
			sp_sb_data.p_func.pf_id,
			sp_sb_data.p_func.vnic_id,
			sp_sb_data.p_func.vf_id,
			sp_sb_data.p_func.vf_valid,
			sp_sb_data.state);
	पूर्ण

	क्रम_each_eth_queue(bp, i) अणु
		काष्ठा bnx2x_fastpath *fp = &bp->fp[i];
		पूर्णांक loop;
		काष्ठा hc_status_block_data_e2 sb_data_e2;
		काष्ठा hc_status_block_data_e1x sb_data_e1x;
		काष्ठा hc_status_block_sm  *hc_sm_p =
			CHIP_IS_E1x(bp) ?
			sb_data_e1x.common.state_machine :
			sb_data_e2.common.state_machine;
		काष्ठा hc_index_data *hc_index_p =
			CHIP_IS_E1x(bp) ?
			sb_data_e1x.index_data :
			sb_data_e2.index_data;
		u8 data_size, cos;
		u32 *sb_data_p;
		काष्ठा bnx2x_fp_txdata txdata;

		अगर (!bp->fp)
			अवरोध;

		अगर (!fp->rx_cons_sb)
			जारी;

		/* Rx */
		BNX2X_ERR("fp%d: rx_bd_prod(0x%x)  rx_bd_cons(0x%x)  rx_comp_prod(0x%x)  rx_comp_cons(0x%x)  *rx_cons_sb(0x%x)\n",
			  i, fp->rx_bd_prod, fp->rx_bd_cons,
			  fp->rx_comp_prod,
			  fp->rx_comp_cons, le16_to_cpu(*fp->rx_cons_sb));
		BNX2X_ERR("     rx_sge_prod(0x%x)  last_max_sge(0x%x)  fp_hc_idx(0x%x)\n",
			  fp->rx_sge_prod, fp->last_max_sge,
			  le16_to_cpu(fp->fp_hc_idx));

		/* Tx */
		क्रम_each_cos_in_tx_queue(fp, cos)
		अणु
			अगर (!fp->txdata_ptr[cos])
				अवरोध;

			txdata = *fp->txdata_ptr[cos];

			अगर (!txdata.tx_cons_sb)
				जारी;

			BNX2X_ERR("fp%d: tx_pkt_prod(0x%x)  tx_pkt_cons(0x%x)  tx_bd_prod(0x%x)  tx_bd_cons(0x%x)  *tx_cons_sb(0x%x)\n",
				  i, txdata.tx_pkt_prod,
				  txdata.tx_pkt_cons, txdata.tx_bd_prod,
				  txdata.tx_bd_cons,
				  le16_to_cpu(*txdata.tx_cons_sb));
		पूर्ण

		loop = CHIP_IS_E1x(bp) ?
			HC_SB_MAX_INDICES_E1X : HC_SB_MAX_INDICES_E2;

		/* host sb data */

		अगर (IS_FCOE_FP(fp))
			जारी;

		BNX2X_ERR("     run indexes (");
		क्रम (j = 0; j < HC_SB_MAX_SM; j++)
			pr_cont("0x%x%s",
			       fp->sb_running_index[j],
			       (j == HC_SB_MAX_SM - 1) ? ")" : " ");

		BNX2X_ERR("     indexes (");
		क्रम (j = 0; j < loop; j++)
			pr_cont("0x%x%s",
			       fp->sb_index_values[j],
			       (j == loop - 1) ? ")" : " ");

		/* VF cannot access FW refelection क्रम status block */
		अगर (IS_VF(bp))
			जारी;

		/* fw sb data */
		data_size = CHIP_IS_E1x(bp) ?
			माप(काष्ठा hc_status_block_data_e1x) :
			माप(काष्ठा hc_status_block_data_e2);
		data_size /= माप(u32);
		sb_data_p = CHIP_IS_E1x(bp) ?
			(u32 *)&sb_data_e1x :
			(u32 *)&sb_data_e2;
		/* copy sb data in here */
		क्रम (j = 0; j < data_size; j++)
			*(sb_data_p + j) = REG_RD(bp, BAR_CSTRORM_INTMEM +
				CSTORM_STATUS_BLOCK_DATA_OFFSET(fp->fw_sb_id) +
				j * माप(u32));

		अगर (!CHIP_IS_E1x(bp)) अणु
			pr_cont("pf_id(0x%x)  vf_id(0x%x)  vf_valid(0x%x) vnic_id(0x%x)  same_igu_sb_1b(0x%x) state(0x%x)\n",
				sb_data_e2.common.p_func.pf_id,
				sb_data_e2.common.p_func.vf_id,
				sb_data_e2.common.p_func.vf_valid,
				sb_data_e2.common.p_func.vnic_id,
				sb_data_e2.common.same_igu_sb_1b,
				sb_data_e2.common.state);
		पूर्ण अन्यथा अणु
			pr_cont("pf_id(0x%x)  vf_id(0x%x)  vf_valid(0x%x) vnic_id(0x%x)  same_igu_sb_1b(0x%x) state(0x%x)\n",
				sb_data_e1x.common.p_func.pf_id,
				sb_data_e1x.common.p_func.vf_id,
				sb_data_e1x.common.p_func.vf_valid,
				sb_data_e1x.common.p_func.vnic_id,
				sb_data_e1x.common.same_igu_sb_1b,
				sb_data_e1x.common.state);
		पूर्ण

		/* SB_SMs data */
		क्रम (j = 0; j < HC_SB_MAX_SM; j++) अणु
			pr_cont("SM[%d] __flags (0x%x) igu_sb_id (0x%x)  igu_seg_id(0x%x) time_to_expire (0x%x) timer_value(0x%x)\n",
				j, hc_sm_p[j].__flags,
				hc_sm_p[j].igu_sb_id,
				hc_sm_p[j].igu_seg_id,
				hc_sm_p[j].समय_प्रकारo_expire,
				hc_sm_p[j].समयr_value);
		पूर्ण

		/* Indices data */
		क्रम (j = 0; j < loop; j++) अणु
			pr_cont("INDEX[%d] flags (0x%x) timeout (0x%x)\n", j,
			       hc_index_p[j].flags,
			       hc_index_p[j].समयout);
		पूर्ण
	पूर्ण

#अगर_घोषित BNX2X_STOP_ON_ERROR
	अगर (IS_PF(bp)) अणु
		/* event queue */
		BNX2X_ERR("eq cons %x prod %x\n", bp->eq_cons, bp->eq_prod);
		क्रम (i = 0; i < NUM_EQ_DESC; i++) अणु
			u32 *data = (u32 *)&bp->eq_ring[i].message.data;

			BNX2X_ERR("event queue [%d]: header: opcode %d, error %d\n",
				  i, bp->eq_ring[i].message.opcode,
				  bp->eq_ring[i].message.error);
			BNX2X_ERR("data: %x %x %x\n",
				  data[0], data[1], data[2]);
		पूर्ण
	पूर्ण

	/* Rings */
	/* Rx */
	क्रम_each_valid_rx_queue(bp, i) अणु
		काष्ठा bnx2x_fastpath *fp = &bp->fp[i];

		अगर (!bp->fp)
			अवरोध;

		अगर (!fp->rx_cons_sb)
			जारी;

		start = RX_BD(le16_to_cpu(*fp->rx_cons_sb) - 10);
		end = RX_BD(le16_to_cpu(*fp->rx_cons_sb) + 503);
		क्रम (j = start; j != end; j = RX_BD(j + 1)) अणु
			u32 *rx_bd = (u32 *)&fp->rx_desc_ring[j];
			काष्ठा sw_rx_bd *sw_bd = &fp->rx_buf_ring[j];

			BNX2X_ERR("fp%d: rx_bd[%x]=[%x:%x]  sw_bd=[%p]\n",
				  i, j, rx_bd[1], rx_bd[0], sw_bd->data);
		पूर्ण

		start = RX_SGE(fp->rx_sge_prod);
		end = RX_SGE(fp->last_max_sge);
		क्रम (j = start; j != end; j = RX_SGE(j + 1)) अणु
			u32 *rx_sge = (u32 *)&fp->rx_sge_ring[j];
			काष्ठा sw_rx_page *sw_page = &fp->rx_page_ring[j];

			BNX2X_ERR("fp%d: rx_sge[%x]=[%x:%x]  sw_page=[%p]\n",
				  i, j, rx_sge[1], rx_sge[0], sw_page->page);
		पूर्ण

		start = RCQ_BD(fp->rx_comp_cons - 10);
		end = RCQ_BD(fp->rx_comp_cons + 503);
		क्रम (j = start; j != end; j = RCQ_BD(j + 1)) अणु
			u32 *cqe = (u32 *)&fp->rx_comp_ring[j];

			BNX2X_ERR("fp%d: cqe[%x]=[%x:%x:%x:%x]\n",
				  i, j, cqe[0], cqe[1], cqe[2], cqe[3]);
		पूर्ण
	पूर्ण

	/* Tx */
	क्रम_each_valid_tx_queue(bp, i) अणु
		काष्ठा bnx2x_fastpath *fp = &bp->fp[i];

		अगर (!bp->fp)
			अवरोध;

		क्रम_each_cos_in_tx_queue(fp, cos) अणु
			काष्ठा bnx2x_fp_txdata *txdata = fp->txdata_ptr[cos];

			अगर (!fp->txdata_ptr[cos])
				अवरोध;

			अगर (!txdata->tx_cons_sb)
				जारी;

			start = TX_BD(le16_to_cpu(*txdata->tx_cons_sb) - 10);
			end = TX_BD(le16_to_cpu(*txdata->tx_cons_sb) + 245);
			क्रम (j = start; j != end; j = TX_BD(j + 1)) अणु
				काष्ठा sw_tx_bd *sw_bd =
					&txdata->tx_buf_ring[j];

				BNX2X_ERR("fp%d: txdata %d, packet[%x]=[%p,%x]\n",
					  i, cos, j, sw_bd->skb,
					  sw_bd->first_bd);
			पूर्ण

			start = TX_BD(txdata->tx_bd_cons - 10);
			end = TX_BD(txdata->tx_bd_cons + 254);
			क्रम (j = start; j != end; j = TX_BD(j + 1)) अणु
				u32 *tx_bd = (u32 *)&txdata->tx_desc_ring[j];

				BNX2X_ERR("fp%d: txdata %d, tx_bd[%x]=[%x:%x:%x:%x]\n",
					  i, cos, j, tx_bd[0], tx_bd[1],
					  tx_bd[2], tx_bd[3]);
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	अगर (IS_PF(bp)) अणु
		पूर्णांक पंचांगp_msg_en = bp->msg_enable;

		bnx2x_fw_dump(bp);
		bp->msg_enable |= NETIF_MSG_HW;
		BNX2X_ERR("Idle check (1st round) ----------\n");
		bnx2x_idle_chk(bp);
		BNX2X_ERR("Idle check (2nd round) ----------\n");
		bnx2x_idle_chk(bp);
		bp->msg_enable = पंचांगp_msg_en;
		bnx2x_mc_निश्चित(bp);
	पूर्ण

	BNX2X_ERR("end crash dump -----------------\n");
पूर्ण

/*
 * FLR Support क्रम E2
 *
 * bnx2x_pf_flr_clnup() is called during nic_load in the per function HW
 * initialization.
 */
#घोषणा FLR_WAIT_USEC		10000	/* 10 milliseconds */
#घोषणा FLR_WAIT_INTERVAL	50	/* usec */
#घोषणा	FLR_POLL_CNT		(FLR_WAIT_USEC/FLR_WAIT_INTERVAL) /* 200 */

काष्ठा pbf_pN_buf_regs अणु
	पूर्णांक pN;
	u32 init_crd;
	u32 crd;
	u32 crd_मुक्तd;
पूर्ण;

काष्ठा pbf_pN_cmd_regs अणु
	पूर्णांक pN;
	u32 lines_occup;
	u32 lines_मुक्तd;
पूर्ण;

अटल व्योम bnx2x_pbf_pN_buf_flushed(काष्ठा bnx2x *bp,
				     काष्ठा pbf_pN_buf_regs *regs,
				     u32 poll_count)
अणु
	u32 init_crd, crd, crd_start, crd_मुक्तd, crd_मुक्तd_start;
	u32 cur_cnt = poll_count;

	crd_मुक्तd = crd_मुक्तd_start = REG_RD(bp, regs->crd_मुक्तd);
	crd = crd_start = REG_RD(bp, regs->crd);
	init_crd = REG_RD(bp, regs->init_crd);

	DP(BNX2X_MSG_SP, "INIT CREDIT[%d] : %x\n", regs->pN, init_crd);
	DP(BNX2X_MSG_SP, "CREDIT[%d]      : s:%x\n", regs->pN, crd);
	DP(BNX2X_MSG_SP, "CREDIT_FREED[%d]: s:%x\n", regs->pN, crd_मुक्तd);

	जबतक ((crd != init_crd) && ((u32)SUB_S32(crd_मुक्तd, crd_मुक्तd_start) <
	       (init_crd - crd_start))) अणु
		अगर (cur_cnt--) अणु
			udelay(FLR_WAIT_INTERVAL);
			crd = REG_RD(bp, regs->crd);
			crd_मुक्तd = REG_RD(bp, regs->crd_मुक्तd);
		पूर्ण अन्यथा अणु
			DP(BNX2X_MSG_SP, "PBF tx buffer[%d] timed out\n",
			   regs->pN);
			DP(BNX2X_MSG_SP, "CREDIT[%d]      : c:%x\n",
			   regs->pN, crd);
			DP(BNX2X_MSG_SP, "CREDIT_FREED[%d]: c:%x\n",
			   regs->pN, crd_मुक्तd);
			अवरोध;
		पूर्ण
	पूर्ण
	DP(BNX2X_MSG_SP, "Waited %d*%d usec for PBF tx buffer[%d]\n",
	   poll_count-cur_cnt, FLR_WAIT_INTERVAL, regs->pN);
पूर्ण

अटल व्योम bnx2x_pbf_pN_cmd_flushed(काष्ठा bnx2x *bp,
				     काष्ठा pbf_pN_cmd_regs *regs,
				     u32 poll_count)
अणु
	u32 occup, to_मुक्त, मुक्तd, मुक्तd_start;
	u32 cur_cnt = poll_count;

	occup = to_मुक्त = REG_RD(bp, regs->lines_occup);
	मुक्तd = मुक्तd_start = REG_RD(bp, regs->lines_मुक्तd);

	DP(BNX2X_MSG_SP, "OCCUPANCY[%d]   : s:%x\n", regs->pN, occup);
	DP(BNX2X_MSG_SP, "LINES_FREED[%d] : s:%x\n", regs->pN, मुक्तd);

	जबतक (occup && ((u32)SUB_S32(मुक्तd, मुक्तd_start) < to_मुक्त)) अणु
		अगर (cur_cnt--) अणु
			udelay(FLR_WAIT_INTERVAL);
			occup = REG_RD(bp, regs->lines_occup);
			मुक्तd = REG_RD(bp, regs->lines_मुक्तd);
		पूर्ण अन्यथा अणु
			DP(BNX2X_MSG_SP, "PBF cmd queue[%d] timed out\n",
			   regs->pN);
			DP(BNX2X_MSG_SP, "OCCUPANCY[%d]   : s:%x\n",
			   regs->pN, occup);
			DP(BNX2X_MSG_SP, "LINES_FREED[%d] : s:%x\n",
			   regs->pN, मुक्तd);
			अवरोध;
		पूर्ण
	पूर्ण
	DP(BNX2X_MSG_SP, "Waited %d*%d usec for PBF cmd queue[%d]\n",
	   poll_count-cur_cnt, FLR_WAIT_INTERVAL, regs->pN);
पूर्ण

अटल u32 bnx2x_flr_clnup_reg_poll(काष्ठा bnx2x *bp, u32 reg,
				    u32 expected, u32 poll_count)
अणु
	u32 cur_cnt = poll_count;
	u32 val;

	जबतक ((val = REG_RD(bp, reg)) != expected && cur_cnt--)
		udelay(FLR_WAIT_INTERVAL);

	वापस val;
पूर्ण

पूर्णांक bnx2x_flr_clnup_poll_hw_counter(काष्ठा bnx2x *bp, u32 reg,
				    अक्षर *msg, u32 poll_cnt)
अणु
	u32 val = bnx2x_flr_clnup_reg_poll(bp, reg, 0, poll_cnt);
	अगर (val != 0) अणु
		BNX2X_ERR("%s usage count=%d\n", msg, val);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* Common routines with VF FLR cleanup */
u32 bnx2x_flr_clnup_poll_count(काष्ठा bnx2x *bp)
अणु
	/* adjust polling समयout */
	अगर (CHIP_REV_IS_EMUL(bp))
		वापस FLR_POLL_CNT * 2000;

	अगर (CHIP_REV_IS_FPGA(bp))
		वापस FLR_POLL_CNT * 120;

	वापस FLR_POLL_CNT;
पूर्ण

व्योम bnx2x_tx_hw_flushed(काष्ठा bnx2x *bp, u32 poll_count)
अणु
	काष्ठा pbf_pN_cmd_regs cmd_regs[] = अणु
		अणु0, (CHIP_IS_E3B0(bp)) ?
			PBF_REG_TQ_OCCUPANCY_Q0 :
			PBF_REG_P0_TQ_OCCUPANCY,
		    (CHIP_IS_E3B0(bp)) ?
			PBF_REG_TQ_LINES_FREED_CNT_Q0 :
			PBF_REG_P0_TQ_LINES_FREED_CNTपूर्ण,
		अणु1, (CHIP_IS_E3B0(bp)) ?
			PBF_REG_TQ_OCCUPANCY_Q1 :
			PBF_REG_P1_TQ_OCCUPANCY,
		    (CHIP_IS_E3B0(bp)) ?
			PBF_REG_TQ_LINES_FREED_CNT_Q1 :
			PBF_REG_P1_TQ_LINES_FREED_CNTपूर्ण,
		अणु4, (CHIP_IS_E3B0(bp)) ?
			PBF_REG_TQ_OCCUPANCY_LB_Q :
			PBF_REG_P4_TQ_OCCUPANCY,
		    (CHIP_IS_E3B0(bp)) ?
			PBF_REG_TQ_LINES_FREED_CNT_LB_Q :
			PBF_REG_P4_TQ_LINES_FREED_CNTपूर्ण
	पूर्ण;

	काष्ठा pbf_pN_buf_regs buf_regs[] = अणु
		अणु0, (CHIP_IS_E3B0(bp)) ?
			PBF_REG_INIT_CRD_Q0 :
			PBF_REG_P0_INIT_CRD ,
		    (CHIP_IS_E3B0(bp)) ?
			PBF_REG_CREDIT_Q0 :
			PBF_REG_P0_CREDIT,
		    (CHIP_IS_E3B0(bp)) ?
			PBF_REG_INTERNAL_CRD_FREED_CNT_Q0 :
			PBF_REG_P0_INTERNAL_CRD_FREED_CNTपूर्ण,
		अणु1, (CHIP_IS_E3B0(bp)) ?
			PBF_REG_INIT_CRD_Q1 :
			PBF_REG_P1_INIT_CRD,
		    (CHIP_IS_E3B0(bp)) ?
			PBF_REG_CREDIT_Q1 :
			PBF_REG_P1_CREDIT,
		    (CHIP_IS_E3B0(bp)) ?
			PBF_REG_INTERNAL_CRD_FREED_CNT_Q1 :
			PBF_REG_P1_INTERNAL_CRD_FREED_CNTपूर्ण,
		अणु4, (CHIP_IS_E3B0(bp)) ?
			PBF_REG_INIT_CRD_LB_Q :
			PBF_REG_P4_INIT_CRD,
		    (CHIP_IS_E3B0(bp)) ?
			PBF_REG_CREDIT_LB_Q :
			PBF_REG_P4_CREDIT,
		    (CHIP_IS_E3B0(bp)) ?
			PBF_REG_INTERNAL_CRD_FREED_CNT_LB_Q :
			PBF_REG_P4_INTERNAL_CRD_FREED_CNTपूर्ण,
	पूर्ण;

	पूर्णांक i;

	/* Verअगरy the command queues are flushed P0, P1, P4 */
	क्रम (i = 0; i < ARRAY_SIZE(cmd_regs); i++)
		bnx2x_pbf_pN_cmd_flushed(bp, &cmd_regs[i], poll_count);

	/* Verअगरy the transmission buffers are flushed P0, P1, P4 */
	क्रम (i = 0; i < ARRAY_SIZE(buf_regs); i++)
		bnx2x_pbf_pN_buf_flushed(bp, &buf_regs[i], poll_count);
पूर्ण

#घोषणा OP_GEN_PARAM(param) \
	(((param) << SDM_OP_GEN_COMP_PARAM_SHIFT) & SDM_OP_GEN_COMP_PARAM)

#घोषणा OP_GEN_TYPE(type) \
	(((type) << SDM_OP_GEN_COMP_TYPE_SHIFT) & SDM_OP_GEN_COMP_TYPE)

#घोषणा OP_GEN_AGG_VECT(index) \
	(((index) << SDM_OP_GEN_AGG_VECT_IDX_SHIFT) & SDM_OP_GEN_AGG_VECT_IDX)

पूर्णांक bnx2x_send_final_clnup(काष्ठा bnx2x *bp, u8 clnup_func, u32 poll_cnt)
अणु
	u32 op_gen_command = 0;
	u32 comp_addr = BAR_CSTRORM_INTMEM +
			CSTORM_FINAL_CLEANUP_COMPLETE_OFFSET(clnup_func);

	अगर (REG_RD(bp, comp_addr)) अणु
		BNX2X_ERR("Cleanup complete was not 0 before sending\n");
		वापस 1;
	पूर्ण

	op_gen_command |= OP_GEN_PARAM(XSTORM_AGG_INT_FINAL_CLEANUP_INDEX);
	op_gen_command |= OP_GEN_TYPE(XSTORM_AGG_INT_FINAL_CLEANUP_COMP_TYPE);
	op_gen_command |= OP_GEN_AGG_VECT(clnup_func);
	op_gen_command |= 1 << SDM_OP_GEN_AGG_VECT_IDX_VALID_SHIFT;

	DP(BNX2X_MSG_SP, "sending FW Final cleanup\n");
	REG_WR(bp, XSDM_REG_OPERATION_GEN, op_gen_command);

	अगर (bnx2x_flr_clnup_reg_poll(bp, comp_addr, 1, poll_cnt) != 1) अणु
		BNX2X_ERR("FW final cleanup did not succeed\n");
		DP(BNX2X_MSG_SP, "At timeout completion address contained %x\n",
		   (REG_RD(bp, comp_addr)));
		bnx2x_panic();
		वापस 1;
	पूर्ण
	/* Zero completion क्रम next FLR */
	REG_WR(bp, comp_addr, 0);

	वापस 0;
पूर्ण

u8 bnx2x_is_pcie_pending(काष्ठा pci_dev *dev)
अणु
	u16 status;

	pcie_capability_पढ़ो_word(dev, PCI_EXP_DEVSTA, &status);
	वापस status & PCI_EXP_DEVSTA_TRPND;
पूर्ण

/* PF FLR specअगरic routines
*/
अटल पूर्णांक bnx2x_poll_hw_usage_counters(काष्ठा bnx2x *bp, u32 poll_cnt)
अणु
	/* रुको क्रम CFC PF usage-counter to zero (includes all the VFs) */
	अगर (bnx2x_flr_clnup_poll_hw_counter(bp,
			CFC_REG_NUM_LCIDS_INSIDE_PF,
			"CFC PF usage counter timed out",
			poll_cnt))
		वापस 1;

	/* Wait क्रम DQ PF usage-counter to zero (until DQ cleanup) */
	अगर (bnx2x_flr_clnup_poll_hw_counter(bp,
			DORQ_REG_PF_USAGE_CNT,
			"DQ PF usage counter timed out",
			poll_cnt))
		वापस 1;

	/* Wait क्रम QM PF usage-counter to zero (until DQ cleanup) */
	अगर (bnx2x_flr_clnup_poll_hw_counter(bp,
			QM_REG_PF_USG_CNT_0 + 4*BP_FUNC(bp),
			"QM PF usage counter timed out",
			poll_cnt))
		वापस 1;

	/* Wait क्रम Timer PF usage-counters to zero (until DQ cleanup) */
	अगर (bnx2x_flr_clnup_poll_hw_counter(bp,
			TM_REG_LIN0_VNIC_UC + 4*BP_PORT(bp),
			"Timers VNIC usage counter timed out",
			poll_cnt))
		वापस 1;
	अगर (bnx2x_flr_clnup_poll_hw_counter(bp,
			TM_REG_LIN0_NUM_SCANS + 4*BP_PORT(bp),
			"Timers NUM_SCANS usage counter timed out",
			poll_cnt))
		वापस 1;

	/* Wait DMAE PF usage counter to zero */
	अगर (bnx2x_flr_clnup_poll_hw_counter(bp,
			dmae_reg_go_c[INIT_DMAE_C(bp)],
			"DMAE command register timed out",
			poll_cnt))
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम bnx2x_hw_enable_status(काष्ठा bnx2x *bp)
अणु
	u32 val;

	val = REG_RD(bp, CFC_REG_WEAK_ENABLE_PF);
	DP(BNX2X_MSG_SP, "CFC_REG_WEAK_ENABLE_PF is 0x%x\n", val);

	val = REG_RD(bp, PBF_REG_DISABLE_PF);
	DP(BNX2X_MSG_SP, "PBF_REG_DISABLE_PF is 0x%x\n", val);

	val = REG_RD(bp, IGU_REG_PCI_PF_MSI_EN);
	DP(BNX2X_MSG_SP, "IGU_REG_PCI_PF_MSI_EN is 0x%x\n", val);

	val = REG_RD(bp, IGU_REG_PCI_PF_MSIX_EN);
	DP(BNX2X_MSG_SP, "IGU_REG_PCI_PF_MSIX_EN is 0x%x\n", val);

	val = REG_RD(bp, IGU_REG_PCI_PF_MSIX_FUNC_MASK);
	DP(BNX2X_MSG_SP, "IGU_REG_PCI_PF_MSIX_FUNC_MASK is 0x%x\n", val);

	val = REG_RD(bp, PGLUE_B_REG_SHADOW_BME_PF_7_0_CLR);
	DP(BNX2X_MSG_SP, "PGLUE_B_REG_SHADOW_BME_PF_7_0_CLR is 0x%x\n", val);

	val = REG_RD(bp, PGLUE_B_REG_FLR_REQUEST_PF_7_0_CLR);
	DP(BNX2X_MSG_SP, "PGLUE_B_REG_FLR_REQUEST_PF_7_0_CLR is 0x%x\n", val);

	val = REG_RD(bp, PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER);
	DP(BNX2X_MSG_SP, "PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER is 0x%x\n",
	   val);
पूर्ण

अटल पूर्णांक bnx2x_pf_flr_clnup(काष्ठा bnx2x *bp)
अणु
	u32 poll_cnt = bnx2x_flr_clnup_poll_count(bp);

	DP(BNX2X_MSG_SP, "Cleanup after FLR PF[%d]\n", BP_ABS_FUNC(bp));

	/* Re-enable PF target पढ़ो access */
	REG_WR(bp, PGLUE_B_REG_INTERNAL_PFID_ENABLE_TARGET_READ, 1);

	/* Poll HW usage counters */
	DP(BNX2X_MSG_SP, "Polling usage counters\n");
	अगर (bnx2x_poll_hw_usage_counters(bp, poll_cnt))
		वापस -EBUSY;

	/* Zero the igu 'trailing edge' and 'leading edge' */

	/* Send the FW cleanup command */
	अगर (bnx2x_send_final_clnup(bp, (u8)BP_FUNC(bp), poll_cnt))
		वापस -EBUSY;

	/* ATC cleanup */

	/* Verअगरy TX hw is flushed */
	bnx2x_tx_hw_flushed(bp, poll_cnt);

	/* Wait 100ms (not adjusted according to platक्रमm) */
	msleep(100);

	/* Verअगरy no pending pci transactions */
	अगर (bnx2x_is_pcie_pending(bp->pdev))
		BNX2X_ERR("PCIE Transactions still pending\n");

	/* Debug */
	bnx2x_hw_enable_status(bp);

	/*
	 * Master enable - Due to WB DMAE ग_लिखोs perक्रमmed beक्रमe this
	 * रेजिस्टर is re-initialized as part of the regular function init
	 */
	REG_WR(bp, PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER, 1);

	वापस 0;
पूर्ण

अटल व्योम bnx2x_hc_पूर्णांक_enable(काष्ठा bnx2x *bp)
अणु
	पूर्णांक port = BP_PORT(bp);
	u32 addr = port ? HC_REG_CONFIG_1 : HC_REG_CONFIG_0;
	u32 val = REG_RD(bp, addr);
	bool msix = (bp->flags & USING_MSIX_FLAG) ? true : false;
	bool single_msix = (bp->flags & USING_SINGLE_MSIX_FLAG) ? true : false;
	bool msi = (bp->flags & USING_MSI_FLAG) ? true : false;

	अगर (msix) अणु
		val &= ~(HC_CONFIG_0_REG_SINGLE_ISR_EN_0 |
			 HC_CONFIG_0_REG_INT_LINE_EN_0);
		val |= (HC_CONFIG_0_REG_MSI_MSIX_INT_EN_0 |
			HC_CONFIG_0_REG_ATTN_BIT_EN_0);
		अगर (single_msix)
			val |= HC_CONFIG_0_REG_SINGLE_ISR_EN_0;
	पूर्ण अन्यथा अगर (msi) अणु
		val &= ~HC_CONFIG_0_REG_INT_LINE_EN_0;
		val |= (HC_CONFIG_0_REG_SINGLE_ISR_EN_0 |
			HC_CONFIG_0_REG_MSI_MSIX_INT_EN_0 |
			HC_CONFIG_0_REG_ATTN_BIT_EN_0);
	पूर्ण अन्यथा अणु
		val |= (HC_CONFIG_0_REG_SINGLE_ISR_EN_0 |
			HC_CONFIG_0_REG_MSI_MSIX_INT_EN_0 |
			HC_CONFIG_0_REG_INT_LINE_EN_0 |
			HC_CONFIG_0_REG_ATTN_BIT_EN_0);

		अगर (!CHIP_IS_E1(bp)) अणु
			DP(NETIF_MSG_IFUP,
			   "write %x to HC %d (addr 0x%x)\n", val, port, addr);

			REG_WR(bp, addr, val);

			val &= ~HC_CONFIG_0_REG_MSI_MSIX_INT_EN_0;
		पूर्ण
	पूर्ण

	अगर (CHIP_IS_E1(bp))
		REG_WR(bp, HC_REG_INT_MASK + port*4, 0x1FFFF);

	DP(NETIF_MSG_IFUP,
	   "write %x to HC %d (addr 0x%x) mode %s\n", val, port, addr,
	   (msix ? "MSI-X" : (msi ? "MSI" : "INTx")));

	REG_WR(bp, addr, val);
	/*
	 * Ensure that HC_CONFIG is written beक्रमe leading/trailing edge config
	 */
	barrier();

	अगर (!CHIP_IS_E1(bp)) अणु
		/* init leading/trailing edge */
		अगर (IS_MF(bp)) अणु
			val = (0xee0f | (1 << (BP_VN(bp) + 4)));
			अगर (bp->port.pmf)
				/* enable nig and gpio3 attention */
				val |= 0x1100;
		पूर्ण अन्यथा
			val = 0xffff;

		REG_WR(bp, HC_REG_TRAILING_EDGE_0 + port*8, val);
		REG_WR(bp, HC_REG_LEADING_EDGE_0 + port*8, val);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_igu_पूर्णांक_enable(काष्ठा bnx2x *bp)
अणु
	u32 val;
	bool msix = (bp->flags & USING_MSIX_FLAG) ? true : false;
	bool single_msix = (bp->flags & USING_SINGLE_MSIX_FLAG) ? true : false;
	bool msi = (bp->flags & USING_MSI_FLAG) ? true : false;

	val = REG_RD(bp, IGU_REG_PF_CONFIGURATION);

	अगर (msix) अणु
		val &= ~(IGU_PF_CONF_INT_LINE_EN |
			 IGU_PF_CONF_SINGLE_ISR_EN);
		val |= (IGU_PF_CONF_MSI_MSIX_EN |
			IGU_PF_CONF_ATTN_BIT_EN);

		अगर (single_msix)
			val |= IGU_PF_CONF_SINGLE_ISR_EN;
	पूर्ण अन्यथा अगर (msi) अणु
		val &= ~IGU_PF_CONF_INT_LINE_EN;
		val |= (IGU_PF_CONF_MSI_MSIX_EN |
			IGU_PF_CONF_ATTN_BIT_EN |
			IGU_PF_CONF_SINGLE_ISR_EN);
	पूर्ण अन्यथा अणु
		val &= ~IGU_PF_CONF_MSI_MSIX_EN;
		val |= (IGU_PF_CONF_INT_LINE_EN |
			IGU_PF_CONF_ATTN_BIT_EN |
			IGU_PF_CONF_SINGLE_ISR_EN);
	पूर्ण

	/* Clean previous status - need to configure igu prior to ack*/
	अगर ((!msix) || single_msix) अणु
		REG_WR(bp, IGU_REG_PF_CONFIGURATION, val);
		bnx2x_ack_पूर्णांक(bp);
	पूर्ण

	val |= IGU_PF_CONF_FUNC_EN;

	DP(NETIF_MSG_IFUP, "write 0x%x to IGU  mode %s\n",
	   val, (msix ? "MSI-X" : (msi ? "MSI" : "INTx")));

	REG_WR(bp, IGU_REG_PF_CONFIGURATION, val);

	अगर (val & IGU_PF_CONF_INT_LINE_EN)
		pci_पूर्णांकx(bp->pdev, true);

	barrier();

	/* init leading/trailing edge */
	अगर (IS_MF(bp)) अणु
		val = (0xee0f | (1 << (BP_VN(bp) + 4)));
		अगर (bp->port.pmf)
			/* enable nig and gpio3 attention */
			val |= 0x1100;
	पूर्ण अन्यथा
		val = 0xffff;

	REG_WR(bp, IGU_REG_TRAILING_EDGE_LATCH, val);
	REG_WR(bp, IGU_REG_LEADING_EDGE_LATCH, val);
पूर्ण

व्योम bnx2x_पूर्णांक_enable(काष्ठा bnx2x *bp)
अणु
	अगर (bp->common.पूर्णांक_block == INT_BLOCK_HC)
		bnx2x_hc_पूर्णांक_enable(bp);
	अन्यथा
		bnx2x_igu_पूर्णांक_enable(bp);
पूर्ण

व्योम bnx2x_पूर्णांक_disable_sync(काष्ठा bnx2x *bp, पूर्णांक disable_hw)
अणु
	पूर्णांक msix = (bp->flags & USING_MSIX_FLAG) ? 1 : 0;
	पूर्णांक i, offset;

	अगर (disable_hw)
		/* prevent the HW from sending पूर्णांकerrupts */
		bnx2x_पूर्णांक_disable(bp);

	/* make sure all ISRs are करोne */
	अगर (msix) अणु
		synchronize_irq(bp->msix_table[0].vector);
		offset = 1;
		अगर (CNIC_SUPPORT(bp))
			offset++;
		क्रम_each_eth_queue(bp, i)
			synchronize_irq(bp->msix_table[offset++].vector);
	पूर्ण अन्यथा
		synchronize_irq(bp->pdev->irq);

	/* make sure sp_task is not running */
	cancel_delayed_work(&bp->sp_task);
	cancel_delayed_work(&bp->period_task);
	flush_workqueue(bnx2x_wq);
पूर्ण

/* fast path */

/*
 * General service functions
 */

/* Return true अगर succeeded to acquire the lock */
अटल bool bnx2x_trylock_hw_lock(काष्ठा bnx2x *bp, u32 resource)
अणु
	u32 lock_status;
	u32 resource_bit = (1 << resource);
	पूर्णांक func = BP_FUNC(bp);
	u32 hw_lock_control_reg;

	DP(NETIF_MSG_HW | NETIF_MSG_IFUP,
	   "Trying to take a lock on resource %d\n", resource);

	/* Validating that the resource is within range */
	अगर (resource > HW_LOCK_MAX_RESOURCE_VALUE) अणु
		DP(NETIF_MSG_HW | NETIF_MSG_IFUP,
		   "resource(0x%x) > HW_LOCK_MAX_RESOURCE_VALUE(0x%x)\n",
		   resource, HW_LOCK_MAX_RESOURCE_VALUE);
		वापस false;
	पूर्ण

	अगर (func <= 5)
		hw_lock_control_reg = (MISC_REG_DRIVER_CONTROL_1 + func*8);
	अन्यथा
		hw_lock_control_reg =
				(MISC_REG_DRIVER_CONTROL_7 + (func - 6)*8);

	/* Try to acquire the lock */
	REG_WR(bp, hw_lock_control_reg + 4, resource_bit);
	lock_status = REG_RD(bp, hw_lock_control_reg);
	अगर (lock_status & resource_bit)
		वापस true;

	DP(NETIF_MSG_HW | NETIF_MSG_IFUP,
	   "Failed to get a lock on resource %d\n", resource);
	वापस false;
पूर्ण

/**
 * bnx2x_get_leader_lock_resource - get the recovery leader resource id
 *
 * @bp:	driver handle
 *
 * Returns the recovery leader resource id according to the engine this function
 * beदीर्घs to. Currently only only 2 engines is supported.
 */
अटल पूर्णांक bnx2x_get_leader_lock_resource(काष्ठा bnx2x *bp)
अणु
	अगर (BP_PATH(bp))
		वापस HW_LOCK_RESOURCE_RECOVERY_LEADER_1;
	अन्यथा
		वापस HW_LOCK_RESOURCE_RECOVERY_LEADER_0;
पूर्ण

/**
 * bnx2x_trylock_leader_lock- try to acquire a leader lock.
 *
 * @bp: driver handle
 *
 * Tries to acquire a leader lock क्रम current engine.
 */
अटल bool bnx2x_trylock_leader_lock(काष्ठा bnx2x *bp)
अणु
	वापस bnx2x_trylock_hw_lock(bp, bnx2x_get_leader_lock_resource(bp));
पूर्ण

अटल व्योम bnx2x_cnic_cfc_comp(काष्ठा bnx2x *bp, पूर्णांक cid, u8 err);

/* schedule the sp task and mark that पूर्णांकerrupt occurred (runs from ISR) */
अटल पूर्णांक bnx2x_schedule_sp_task(काष्ठा bnx2x *bp)
अणु
	/* Set the पूर्णांकerrupt occurred bit क्रम the sp-task to recognize it
	 * must ack the पूर्णांकerrupt and transition according to the IGU
	 * state machine.
	 */
	atomic_set(&bp->पूर्णांकerrupt_occurred, 1);

	/* The sp_task must execute only after this bit
	 * is set, otherwise we will get out of sync and miss all
	 * further पूर्णांकerrupts. Hence, the barrier.
	 */
	smp_wmb();

	/* schedule sp_task to workqueue */
	वापस queue_delayed_work(bnx2x_wq, &bp->sp_task, 0);
पूर्ण

व्योम bnx2x_sp_event(काष्ठा bnx2x_fastpath *fp, जोड़ eth_rx_cqe *rr_cqe)
अणु
	काष्ठा bnx2x *bp = fp->bp;
	पूर्णांक cid = SW_CID(rr_cqe->ramrod_cqe.conn_and_cmd_data);
	पूर्णांक command = CQE_CMD(rr_cqe->ramrod_cqe.conn_and_cmd_data);
	क्रमागत bnx2x_queue_cmd drv_cmd = BNX2X_Q_CMD_MAX;
	काष्ठा bnx2x_queue_sp_obj *q_obj = &bnx2x_sp_obj(bp, fp).q_obj;

	DP(BNX2X_MSG_SP,
	   "fp %d  cid %d  got ramrod #%d  state is %x  type is %d\n",
	   fp->index, cid, command, bp->state,
	   rr_cqe->ramrod_cqe.ramrod_type);

	/* If cid is within VF range, replace the slowpath object with the
	 * one corresponding to this VF
	 */
	अगर (cid >= BNX2X_FIRST_VF_CID  &&
	    cid < BNX2X_FIRST_VF_CID + BNX2X_VF_CIDS)
		bnx2x_iov_set_queue_sp_obj(bp, cid, &q_obj);

	चयन (command) अणु
	हाल (RAMROD_CMD_ID_ETH_CLIENT_UPDATE):
		DP(BNX2X_MSG_SP, "got UPDATE ramrod. CID %d\n", cid);
		drv_cmd = BNX2X_Q_CMD_UPDATE;
		अवरोध;

	हाल (RAMROD_CMD_ID_ETH_CLIENT_SETUP):
		DP(BNX2X_MSG_SP, "got MULTI[%d] setup ramrod\n", cid);
		drv_cmd = BNX2X_Q_CMD_SETUP;
		अवरोध;

	हाल (RAMROD_CMD_ID_ETH_TX_QUEUE_SETUP):
		DP(BNX2X_MSG_SP, "got MULTI[%d] tx-only setup ramrod\n", cid);
		drv_cmd = BNX2X_Q_CMD_SETUP_TX_ONLY;
		अवरोध;

	हाल (RAMROD_CMD_ID_ETH_HALT):
		DP(BNX2X_MSG_SP, "got MULTI[%d] halt ramrod\n", cid);
		drv_cmd = BNX2X_Q_CMD_HALT;
		अवरोध;

	हाल (RAMROD_CMD_ID_ETH_TERMINATE):
		DP(BNX2X_MSG_SP, "got MULTI[%d] terminate ramrod\n", cid);
		drv_cmd = BNX2X_Q_CMD_TERMINATE;
		अवरोध;

	हाल (RAMROD_CMD_ID_ETH_EMPTY):
		DP(BNX2X_MSG_SP, "got MULTI[%d] empty ramrod\n", cid);
		drv_cmd = BNX2X_Q_CMD_EMPTY;
		अवरोध;

	हाल (RAMROD_CMD_ID_ETH_TPA_UPDATE):
		DP(BNX2X_MSG_SP, "got tpa update ramrod CID=%d\n", cid);
		drv_cmd = BNX2X_Q_CMD_UPDATE_TPA;
		अवरोध;

	शेष:
		BNX2X_ERR("unexpected MC reply (%d) on fp[%d]\n",
			  command, fp->index);
		वापस;
	पूर्ण

	अगर ((drv_cmd != BNX2X_Q_CMD_MAX) &&
	    q_obj->complete_cmd(bp, q_obj, drv_cmd))
		/* q_obj->complete_cmd() failure means that this was
		 * an unexpected completion.
		 *
		 * In this हाल we करोn't want to increase the bp->spq_left
		 * because apparently we haven't sent this command the first
		 * place.
		 */
#अगर_घोषित BNX2X_STOP_ON_ERROR
		bnx2x_panic();
#अन्यथा
		वापस;
#पूर्ण_अगर

	smp_mb__beक्रमe_atomic();
	atomic_inc(&bp->cq_spq_left);
	/* push the change in bp->spq_left and towards the memory */
	smp_mb__after_atomic();

	DP(BNX2X_MSG_SP, "bp->cq_spq_left %x\n", atomic_पढ़ो(&bp->cq_spq_left));

	अगर ((drv_cmd == BNX2X_Q_CMD_UPDATE) && (IS_FCOE_FP(fp)) &&
	    (!!test_bit(BNX2X_AFEX_FCOE_Q_UPDATE_PENDING, &bp->sp_state))) अणु
		/* अगर Q update ramrod is completed क्रम last Q in AFEX vअगर set
		 * flow, then ACK MCP at the end
		 *
		 * mark pending ACK to MCP bit.
		 * prevent हाल that both bits are cleared.
		 * At the end of load/unload driver checks that
		 * sp_state is cleared, and this order prevents
		 * races
		 */
		smp_mb__beक्रमe_atomic();
		set_bit(BNX2X_AFEX_PENDING_VIFSET_MCP_ACK, &bp->sp_state);
		wmb();
		clear_bit(BNX2X_AFEX_FCOE_Q_UPDATE_PENDING, &bp->sp_state);
		smp_mb__after_atomic();

		/* schedule the sp task as mcp ack is required */
		bnx2x_schedule_sp_task(bp);
	पूर्ण

	वापस;
पूर्ण

irqवापस_t bnx2x_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev_instance);
	u16 status = bnx2x_ack_पूर्णांक(bp);
	u16 mask;
	पूर्णांक i;
	u8 cos;

	/* Return here अगर पूर्णांकerrupt is shared and it's not क्रम us */
	अगर (unlikely(status == 0)) अणु
		DP(NETIF_MSG_INTR, "not our interrupt!\n");
		वापस IRQ_NONE;
	पूर्ण
	DP(NETIF_MSG_INTR, "got an interrupt  status 0x%x\n", status);

#अगर_घोषित BNX2X_STOP_ON_ERROR
	अगर (unlikely(bp->panic))
		वापस IRQ_HANDLED;
#पूर्ण_अगर

	क्रम_each_eth_queue(bp, i) अणु
		काष्ठा bnx2x_fastpath *fp = &bp->fp[i];

		mask = 0x2 << (fp->index + CNIC_SUPPORT(bp));
		अगर (status & mask) अणु
			/* Handle Rx or Tx according to SB id */
			क्रम_each_cos_in_tx_queue(fp, cos)
				prefetch(fp->txdata_ptr[cos]->tx_cons_sb);
			prefetch(&fp->sb_running_index[SM_RX_ID]);
			napi_schedule_irqoff(&bnx2x_fp(bp, fp->index, napi));
			status &= ~mask;
		पूर्ण
	पूर्ण

	अगर (CNIC_SUPPORT(bp)) अणु
		mask = 0x2;
		अगर (status & (mask | 0x1)) अणु
			काष्ठा cnic_ops *c_ops = शून्य;

			rcu_पढ़ो_lock();
			c_ops = rcu_dereference(bp->cnic_ops);
			अगर (c_ops && (bp->cnic_eth_dev.drv_state &
				      CNIC_DRV_STATE_HANDLES_IRQ))
				c_ops->cnic_handler(bp->cnic_data, शून्य);
			rcu_पढ़ो_unlock();

			status &= ~mask;
		पूर्ण
	पूर्ण

	अगर (unlikely(status & 0x1)) अणु

		/* schedule sp task to perक्रमm शेष status block work, ack
		 * attentions and enable पूर्णांकerrupts.
		 */
		bnx2x_schedule_sp_task(bp);

		status &= ~0x1;
		अगर (!status)
			वापस IRQ_HANDLED;
	पूर्ण

	अगर (unlikely(status))
		DP(NETIF_MSG_INTR, "got an unknown interrupt! (status 0x%x)\n",
		   status);

	वापस IRQ_HANDLED;
पूर्ण

/* Link */

/*
 * General service functions
 */

पूर्णांक bnx2x_acquire_hw_lock(काष्ठा bnx2x *bp, u32 resource)
अणु
	u32 lock_status;
	u32 resource_bit = (1 << resource);
	पूर्णांक func = BP_FUNC(bp);
	u32 hw_lock_control_reg;
	पूर्णांक cnt;

	/* Validating that the resource is within range */
	अगर (resource > HW_LOCK_MAX_RESOURCE_VALUE) अणु
		BNX2X_ERR("resource(0x%x) > HW_LOCK_MAX_RESOURCE_VALUE(0x%x)\n",
		   resource, HW_LOCK_MAX_RESOURCE_VALUE);
		वापस -EINVAL;
	पूर्ण

	अगर (func <= 5) अणु
		hw_lock_control_reg = (MISC_REG_DRIVER_CONTROL_1 + func*8);
	पूर्ण अन्यथा अणु
		hw_lock_control_reg =
				(MISC_REG_DRIVER_CONTROL_7 + (func - 6)*8);
	पूर्ण

	/* Validating that the resource is not alपढ़ोy taken */
	lock_status = REG_RD(bp, hw_lock_control_reg);
	अगर (lock_status & resource_bit) अणु
		BNX2X_ERR("lock_status 0x%x  resource_bit 0x%x\n",
		   lock_status, resource_bit);
		वापस -EEXIST;
	पूर्ण

	/* Try क्रम 5 second every 5ms */
	क्रम (cnt = 0; cnt < 1000; cnt++) अणु
		/* Try to acquire the lock */
		REG_WR(bp, hw_lock_control_reg + 4, resource_bit);
		lock_status = REG_RD(bp, hw_lock_control_reg);
		अगर (lock_status & resource_bit)
			वापस 0;

		usleep_range(5000, 10000);
	पूर्ण
	BNX2X_ERR("Timeout\n");
	वापस -EAGAIN;
पूर्ण

पूर्णांक bnx2x_release_leader_lock(काष्ठा bnx2x *bp)
अणु
	वापस bnx2x_release_hw_lock(bp, bnx2x_get_leader_lock_resource(bp));
पूर्ण

पूर्णांक bnx2x_release_hw_lock(काष्ठा bnx2x *bp, u32 resource)
अणु
	u32 lock_status;
	u32 resource_bit = (1 << resource);
	पूर्णांक func = BP_FUNC(bp);
	u32 hw_lock_control_reg;

	/* Validating that the resource is within range */
	अगर (resource > HW_LOCK_MAX_RESOURCE_VALUE) अणु
		BNX2X_ERR("resource(0x%x) > HW_LOCK_MAX_RESOURCE_VALUE(0x%x)\n",
		   resource, HW_LOCK_MAX_RESOURCE_VALUE);
		वापस -EINVAL;
	पूर्ण

	अगर (func <= 5) अणु
		hw_lock_control_reg = (MISC_REG_DRIVER_CONTROL_1 + func*8);
	पूर्ण अन्यथा अणु
		hw_lock_control_reg =
				(MISC_REG_DRIVER_CONTROL_7 + (func - 6)*8);
	पूर्ण

	/* Validating that the resource is currently taken */
	lock_status = REG_RD(bp, hw_lock_control_reg);
	अगर (!(lock_status & resource_bit)) अणु
		BNX2X_ERR("lock_status 0x%x resource_bit 0x%x. Unlock was called but lock wasn't taken!\n",
			  lock_status, resource_bit);
		वापस -EFAULT;
	पूर्ण

	REG_WR(bp, hw_lock_control_reg, resource_bit);
	वापस 0;
पूर्ण

पूर्णांक bnx2x_get_gpio(काष्ठा bnx2x *bp, पूर्णांक gpio_num, u8 port)
अणु
	/* The GPIO should be swapped अगर swap रेजिस्टर is set and active */
	पूर्णांक gpio_port = (REG_RD(bp, NIG_REG_PORT_SWAP) &&
			 REG_RD(bp, NIG_REG_STRAP_OVERRIDE)) ^ port;
	पूर्णांक gpio_shअगरt = gpio_num +
			(gpio_port ? MISC_REGISTERS_GPIO_PORT_SHIFT : 0);
	u32 gpio_mask = (1 << gpio_shअगरt);
	u32 gpio_reg;
	पूर्णांक value;

	अगर (gpio_num > MISC_REGISTERS_GPIO_3) अणु
		BNX2X_ERR("Invalid GPIO %d\n", gpio_num);
		वापस -EINVAL;
	पूर्ण

	/* पढ़ो GPIO value */
	gpio_reg = REG_RD(bp, MISC_REG_GPIO);

	/* get the requested pin value */
	अगर ((gpio_reg & gpio_mask) == gpio_mask)
		value = 1;
	अन्यथा
		value = 0;

	वापस value;
पूर्ण

पूर्णांक bnx2x_set_gpio(काष्ठा bnx2x *bp, पूर्णांक gpio_num, u32 mode, u8 port)
अणु
	/* The GPIO should be swapped अगर swap रेजिस्टर is set and active */
	पूर्णांक gpio_port = (REG_RD(bp, NIG_REG_PORT_SWAP) &&
			 REG_RD(bp, NIG_REG_STRAP_OVERRIDE)) ^ port;
	पूर्णांक gpio_shअगरt = gpio_num +
			(gpio_port ? MISC_REGISTERS_GPIO_PORT_SHIFT : 0);
	u32 gpio_mask = (1 << gpio_shअगरt);
	u32 gpio_reg;

	अगर (gpio_num > MISC_REGISTERS_GPIO_3) अणु
		BNX2X_ERR("Invalid GPIO %d\n", gpio_num);
		वापस -EINVAL;
	पूर्ण

	bnx2x_acquire_hw_lock(bp, HW_LOCK_RESOURCE_GPIO);
	/* पढ़ो GPIO and mask except the भग्न bits */
	gpio_reg = (REG_RD(bp, MISC_REG_GPIO) & MISC_REGISTERS_GPIO_FLOAT);

	चयन (mode) अणु
	हाल MISC_REGISTERS_GPIO_OUTPUT_LOW:
		DP(NETIF_MSG_LINK,
		   "Set GPIO %d (shift %d) -> output low\n",
		   gpio_num, gpio_shअगरt);
		/* clear FLOAT and set CLR */
		gpio_reg &= ~(gpio_mask << MISC_REGISTERS_GPIO_FLOAT_POS);
		gpio_reg |=  (gpio_mask << MISC_REGISTERS_GPIO_CLR_POS);
		अवरोध;

	हाल MISC_REGISTERS_GPIO_OUTPUT_HIGH:
		DP(NETIF_MSG_LINK,
		   "Set GPIO %d (shift %d) -> output high\n",
		   gpio_num, gpio_shअगरt);
		/* clear FLOAT and set SET */
		gpio_reg &= ~(gpio_mask << MISC_REGISTERS_GPIO_FLOAT_POS);
		gpio_reg |=  (gpio_mask << MISC_REGISTERS_GPIO_SET_POS);
		अवरोध;

	हाल MISC_REGISTERS_GPIO_INPUT_HI_Z:
		DP(NETIF_MSG_LINK,
		   "Set GPIO %d (shift %d) -> input\n",
		   gpio_num, gpio_shअगरt);
		/* set FLOAT */
		gpio_reg |= (gpio_mask << MISC_REGISTERS_GPIO_FLOAT_POS);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	REG_WR(bp, MISC_REG_GPIO, gpio_reg);
	bnx2x_release_hw_lock(bp, HW_LOCK_RESOURCE_GPIO);

	वापस 0;
पूर्ण

पूर्णांक bnx2x_set_mult_gpio(काष्ठा bnx2x *bp, u8 pins, u32 mode)
अणु
	u32 gpio_reg = 0;
	पूर्णांक rc = 0;

	/* Any port swapping should be handled by caller. */

	bnx2x_acquire_hw_lock(bp, HW_LOCK_RESOURCE_GPIO);
	/* पढ़ो GPIO and mask except the भग्न bits */
	gpio_reg = REG_RD(bp, MISC_REG_GPIO);
	gpio_reg &= ~(pins << MISC_REGISTERS_GPIO_FLOAT_POS);
	gpio_reg &= ~(pins << MISC_REGISTERS_GPIO_CLR_POS);
	gpio_reg &= ~(pins << MISC_REGISTERS_GPIO_SET_POS);

	चयन (mode) अणु
	हाल MISC_REGISTERS_GPIO_OUTPUT_LOW:
		DP(NETIF_MSG_LINK, "Set GPIO 0x%x -> output low\n", pins);
		/* set CLR */
		gpio_reg |= (pins << MISC_REGISTERS_GPIO_CLR_POS);
		अवरोध;

	हाल MISC_REGISTERS_GPIO_OUTPUT_HIGH:
		DP(NETIF_MSG_LINK, "Set GPIO 0x%x -> output high\n", pins);
		/* set SET */
		gpio_reg |= (pins << MISC_REGISTERS_GPIO_SET_POS);
		अवरोध;

	हाल MISC_REGISTERS_GPIO_INPUT_HI_Z:
		DP(NETIF_MSG_LINK, "Set GPIO 0x%x -> input\n", pins);
		/* set FLOAT */
		gpio_reg |= (pins << MISC_REGISTERS_GPIO_FLOAT_POS);
		अवरोध;

	शेष:
		BNX2X_ERR("Invalid GPIO mode assignment %d\n", mode);
		rc = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (rc == 0)
		REG_WR(bp, MISC_REG_GPIO, gpio_reg);

	bnx2x_release_hw_lock(bp, HW_LOCK_RESOURCE_GPIO);

	वापस rc;
पूर्ण

पूर्णांक bnx2x_set_gpio_पूर्णांक(काष्ठा bnx2x *bp, पूर्णांक gpio_num, u32 mode, u8 port)
अणु
	/* The GPIO should be swapped अगर swap रेजिस्टर is set and active */
	पूर्णांक gpio_port = (REG_RD(bp, NIG_REG_PORT_SWAP) &&
			 REG_RD(bp, NIG_REG_STRAP_OVERRIDE)) ^ port;
	पूर्णांक gpio_shअगरt = gpio_num +
			(gpio_port ? MISC_REGISTERS_GPIO_PORT_SHIFT : 0);
	u32 gpio_mask = (1 << gpio_shअगरt);
	u32 gpio_reg;

	अगर (gpio_num > MISC_REGISTERS_GPIO_3) अणु
		BNX2X_ERR("Invalid GPIO %d\n", gpio_num);
		वापस -EINVAL;
	पूर्ण

	bnx2x_acquire_hw_lock(bp, HW_LOCK_RESOURCE_GPIO);
	/* पढ़ो GPIO पूर्णांक */
	gpio_reg = REG_RD(bp, MISC_REG_GPIO_INT);

	चयन (mode) अणु
	हाल MISC_REGISTERS_GPIO_INT_OUTPUT_CLR:
		DP(NETIF_MSG_LINK,
		   "Clear GPIO INT %d (shift %d) -> output low\n",
		   gpio_num, gpio_shअगरt);
		/* clear SET and set CLR */
		gpio_reg &= ~(gpio_mask << MISC_REGISTERS_GPIO_INT_SET_POS);
		gpio_reg |=  (gpio_mask << MISC_REGISTERS_GPIO_INT_CLR_POS);
		अवरोध;

	हाल MISC_REGISTERS_GPIO_INT_OUTPUT_SET:
		DP(NETIF_MSG_LINK,
		   "Set GPIO INT %d (shift %d) -> output high\n",
		   gpio_num, gpio_shअगरt);
		/* clear CLR and set SET */
		gpio_reg &= ~(gpio_mask << MISC_REGISTERS_GPIO_INT_CLR_POS);
		gpio_reg |=  (gpio_mask << MISC_REGISTERS_GPIO_INT_SET_POS);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	REG_WR(bp, MISC_REG_GPIO_INT, gpio_reg);
	bnx2x_release_hw_lock(bp, HW_LOCK_RESOURCE_GPIO);

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_set_spio(काष्ठा bnx2x *bp, पूर्णांक spio, u32 mode)
अणु
	u32 spio_reg;

	/* Only 2 SPIOs are configurable */
	अगर ((spio != MISC_SPIO_SPIO4) && (spio != MISC_SPIO_SPIO5)) अणु
		BNX2X_ERR("Invalid SPIO 0x%x\n", spio);
		वापस -EINVAL;
	पूर्ण

	bnx2x_acquire_hw_lock(bp, HW_LOCK_RESOURCE_SPIO);
	/* पढ़ो SPIO and mask except the भग्न bits */
	spio_reg = (REG_RD(bp, MISC_REG_SPIO) & MISC_SPIO_FLOAT);

	चयन (mode) अणु
	हाल MISC_SPIO_OUTPUT_LOW:
		DP(NETIF_MSG_HW, "Set SPIO 0x%x -> output low\n", spio);
		/* clear FLOAT and set CLR */
		spio_reg &= ~(spio << MISC_SPIO_FLOAT_POS);
		spio_reg |=  (spio << MISC_SPIO_CLR_POS);
		अवरोध;

	हाल MISC_SPIO_OUTPUT_HIGH:
		DP(NETIF_MSG_HW, "Set SPIO 0x%x -> output high\n", spio);
		/* clear FLOAT and set SET */
		spio_reg &= ~(spio << MISC_SPIO_FLOAT_POS);
		spio_reg |=  (spio << MISC_SPIO_SET_POS);
		अवरोध;

	हाल MISC_SPIO_INPUT_HI_Z:
		DP(NETIF_MSG_HW, "Set SPIO 0x%x -> input\n", spio);
		/* set FLOAT */
		spio_reg |= (spio << MISC_SPIO_FLOAT_POS);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	REG_WR(bp, MISC_REG_SPIO, spio_reg);
	bnx2x_release_hw_lock(bp, HW_LOCK_RESOURCE_SPIO);

	वापस 0;
पूर्ण

व्योम bnx2x_calc_fc_adv(काष्ठा bnx2x *bp)
अणु
	u8 cfg_idx = bnx2x_get_link_cfg_idx(bp);

	bp->port.advertising[cfg_idx] &= ~(ADVERTISED_Asym_Pause |
					   ADVERTISED_Pause);
	चयन (bp->link_vars.ieee_fc &
		MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_MASK) अणु
	हाल MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH:
		bp->port.advertising[cfg_idx] |= (ADVERTISED_Asym_Pause |
						  ADVERTISED_Pause);
		अवरोध;

	हाल MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_ASYMMETRIC:
		bp->port.advertising[cfg_idx] |= ADVERTISED_Asym_Pause;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम bnx2x_set_requested_fc(काष्ठा bnx2x *bp)
अणु
	/* Initialize link parameters काष्ठाure variables
	 * It is recommended to turn off RX FC क्रम jumbo frames
	 *  क्रम better perक्रमmance
	 */
	अगर (CHIP_IS_E1x(bp) && (bp->dev->mtu > 5000))
		bp->link_params.req_fc_स्वतः_adv = BNX2X_FLOW_CTRL_TX;
	अन्यथा
		bp->link_params.req_fc_स्वतः_adv = BNX2X_FLOW_CTRL_BOTH;
पूर्ण

अटल व्योम bnx2x_init_dropless_fc(काष्ठा bnx2x *bp)
अणु
	u32 छोड़ो_enabled = 0;

	अगर (!CHIP_IS_E1(bp) && bp->dropless_fc && bp->link_vars.link_up) अणु
		अगर (bp->link_vars.flow_ctrl & BNX2X_FLOW_CTRL_TX)
			छोड़ो_enabled = 1;

		REG_WR(bp, BAR_USTRORM_INTMEM +
			   USTORM_ETH_PAUSE_ENABLED_OFFSET(BP_PORT(bp)),
		       छोड़ो_enabled);
	पूर्ण

	DP(NETIF_MSG_IFUP | NETIF_MSG_LINK, "dropless_fc is %s\n",
	   छोड़ो_enabled ? "enabled" : "disabled");
पूर्ण

पूर्णांक bnx2x_initial_phy_init(काष्ठा bnx2x *bp, पूर्णांक load_mode)
अणु
	पूर्णांक rc, cfx_idx = bnx2x_get_link_cfg_idx(bp);
	u16 req_line_speed = bp->link_params.req_line_speed[cfx_idx];

	अगर (!BP_NOMCP(bp)) अणु
		bnx2x_set_requested_fc(bp);
		bnx2x_acquire_phy_lock(bp);

		अगर (load_mode == LOAD_DIAG) अणु
			काष्ठा link_params *lp = &bp->link_params;
			lp->loopback_mode = LOOPBACK_XGXS;
			/* Prefer करोing PHY loopback at highest speed */
			अगर (lp->req_line_speed[cfx_idx] < SPEED_20000) अणु
				अगर (lp->speed_cap_mask[cfx_idx] &
				    PORT_HW_CFG_SPEED_CAPABILITY_D0_20G)
					lp->req_line_speed[cfx_idx] =
					SPEED_20000;
				अन्यथा अगर (lp->speed_cap_mask[cfx_idx] &
					    PORT_HW_CFG_SPEED_CAPABILITY_D0_10G)
						lp->req_line_speed[cfx_idx] =
						SPEED_10000;
				अन्यथा
					lp->req_line_speed[cfx_idx] =
					SPEED_1000;
			पूर्ण
		पूर्ण

		अगर (load_mode == LOAD_LOOPBACK_EXT) अणु
			काष्ठा link_params *lp = &bp->link_params;
			lp->loopback_mode = LOOPBACK_EXT;
		पूर्ण

		rc = bnx2x_phy_init(&bp->link_params, &bp->link_vars);

		bnx2x_release_phy_lock(bp);

		bnx2x_init_dropless_fc(bp);

		bnx2x_calc_fc_adv(bp);

		अगर (bp->link_vars.link_up) अणु
			bnx2x_stats_handle(bp, STATS_EVENT_LINK_UP);
			bnx2x_link_report(bp);
		पूर्ण
		queue_delayed_work(bnx2x_wq, &bp->period_task, 0);
		bp->link_params.req_line_speed[cfx_idx] = req_line_speed;
		वापस rc;
	पूर्ण
	BNX2X_ERR("Bootcode is missing - can not initialize link\n");
	वापस -EINVAL;
पूर्ण

व्योम bnx2x_link_set(काष्ठा bnx2x *bp)
अणु
	अगर (!BP_NOMCP(bp)) अणु
		bnx2x_acquire_phy_lock(bp);
		bnx2x_phy_init(&bp->link_params, &bp->link_vars);
		bnx2x_release_phy_lock(bp);

		bnx2x_init_dropless_fc(bp);

		bnx2x_calc_fc_adv(bp);
	पूर्ण अन्यथा
		BNX2X_ERR("Bootcode is missing - can not set link\n");
पूर्ण

अटल व्योम bnx2x__link_reset(काष्ठा bnx2x *bp)
अणु
	अगर (!BP_NOMCP(bp)) अणु
		bnx2x_acquire_phy_lock(bp);
		bnx2x_lfa_reset(&bp->link_params, &bp->link_vars);
		bnx2x_release_phy_lock(bp);
	पूर्ण अन्यथा
		BNX2X_ERR("Bootcode is missing - can not reset link\n");
पूर्ण

व्योम bnx2x_क्रमce_link_reset(काष्ठा bnx2x *bp)
अणु
	bnx2x_acquire_phy_lock(bp);
	bnx2x_link_reset(&bp->link_params, &bp->link_vars, 1);
	bnx2x_release_phy_lock(bp);
पूर्ण

u8 bnx2x_link_test(काष्ठा bnx2x *bp, u8 is_serdes)
अणु
	u8 rc = 0;

	अगर (!BP_NOMCP(bp)) अणु
		bnx2x_acquire_phy_lock(bp);
		rc = bnx2x_test_link(&bp->link_params, &bp->link_vars,
				     is_serdes);
		bnx2x_release_phy_lock(bp);
	पूर्ण अन्यथा
		BNX2X_ERR("Bootcode is missing - can not test link\n");

	वापस rc;
पूर्ण

/* Calculates the sum of vn_min_rates.
   It's needed क्रम further normalizing of the min_rates.
   Returns:
     sum of vn_min_rates.
       or
     0 - अगर all the min_rates are 0.
     In the later हाल fairness algorithm should be deactivated.
     If not all min_rates are zero then those that are zeroes will be set to 1.
 */
अटल व्योम bnx2x_calc_vn_min(काष्ठा bnx2x *bp,
				      काष्ठा cmng_init_input *input)
अणु
	पूर्णांक all_zero = 1;
	पूर्णांक vn;

	क्रम (vn = VN_0; vn < BP_MAX_VN_NUM(bp); vn++) अणु
		u32 vn_cfg = bp->mf_config[vn];
		u32 vn_min_rate = ((vn_cfg & FUNC_MF_CFG_MIN_BW_MASK) >>
				   FUNC_MF_CFG_MIN_BW_SHIFT) * 100;

		/* Skip hidden vns */
		अगर (vn_cfg & FUNC_MF_CFG_FUNC_HIDE)
			vn_min_rate = 0;
		/* If min rate is zero - set it to 1 */
		अन्यथा अगर (!vn_min_rate)
			vn_min_rate = DEF_MIN_RATE;
		अन्यथा
			all_zero = 0;

		input->vnic_min_rate[vn] = vn_min_rate;
	पूर्ण

	/* अगर ETS or all min rates are zeros - disable fairness */
	अगर (BNX2X_IS_ETS_ENABLED(bp)) अणु
		input->flags.cmng_enables &=
					~CMNG_FLAGS_PER_PORT_FAIRNESS_VN;
		DP(NETIF_MSG_IFUP, "Fairness will be disabled due to ETS\n");
	पूर्ण अन्यथा अगर (all_zero) अणु
		input->flags.cmng_enables &=
					~CMNG_FLAGS_PER_PORT_FAIRNESS_VN;
		DP(NETIF_MSG_IFUP,
		   "All MIN values are zeroes fairness will be disabled\n");
	पूर्ण अन्यथा
		input->flags.cmng_enables |=
					CMNG_FLAGS_PER_PORT_FAIRNESS_VN;
पूर्ण

अटल व्योम bnx2x_calc_vn_max(काष्ठा bnx2x *bp, पूर्णांक vn,
				    काष्ठा cmng_init_input *input)
अणु
	u16 vn_max_rate;
	u32 vn_cfg = bp->mf_config[vn];

	अगर (vn_cfg & FUNC_MF_CFG_FUNC_HIDE)
		vn_max_rate = 0;
	अन्यथा अणु
		u32 maxCfg = bnx2x_extract_max_cfg(bp, vn_cfg);

		अगर (IS_MF_PERCENT_BW(bp)) अणु
			/* maxCfg in percents of linkspeed */
			vn_max_rate = (bp->link_vars.line_speed * maxCfg) / 100;
		पूर्ण अन्यथा /* SD modes */
			/* maxCfg is असलolute in 100Mb units */
			vn_max_rate = maxCfg * 100;
	पूर्ण

	DP(NETIF_MSG_IFUP, "vn %d: vn_max_rate %d\n", vn, vn_max_rate);

	input->vnic_max_rate[vn] = vn_max_rate;
पूर्ण

अटल पूर्णांक bnx2x_get_cmng_fns_mode(काष्ठा bnx2x *bp)
अणु
	अगर (CHIP_REV_IS_SLOW(bp))
		वापस CMNG_FNS_NONE;
	अगर (IS_MF(bp))
		वापस CMNG_FNS_MINMAX;

	वापस CMNG_FNS_NONE;
पूर्ण

व्योम bnx2x_पढ़ो_mf_cfg(काष्ठा bnx2x *bp)
अणु
	पूर्णांक vn, n = (CHIP_MODE_IS_4_PORT(bp) ? 2 : 1);

	अगर (BP_NOMCP(bp))
		वापस; /* what should be the शेष value in this हाल */

	/* For 2 port configuration the असलolute function number क्रमmula
	 * is:
	 *      असल_func = 2 * vn + BP_PORT + BP_PATH
	 *
	 *      and there are 4 functions per port
	 *
	 * For 4 port configuration it is
	 *      असल_func = 4 * vn + 2 * BP_PORT + BP_PATH
	 *
	 *      and there are 2 functions per port
	 */
	क्रम (vn = VN_0; vn < BP_MAX_VN_NUM(bp); vn++) अणु
		पूर्णांक /*असल*/func = n * (2 * vn + BP_PORT(bp)) + BP_PATH(bp);

		अगर (func >= E1H_FUNC_MAX)
			अवरोध;

		bp->mf_config[vn] =
			MF_CFG_RD(bp, func_mf_config[func].config);
	पूर्ण
	अगर (bp->mf_config[BP_VN(bp)] & FUNC_MF_CFG_FUNC_DISABLED) अणु
		DP(NETIF_MSG_IFUP, "mf_cfg function disabled\n");
		bp->flags |= MF_FUNC_DIS;
	पूर्ण अन्यथा अणु
		DP(NETIF_MSG_IFUP, "mf_cfg function enabled\n");
		bp->flags &= ~MF_FUNC_DIS;
	पूर्ण
पूर्ण

अटल व्योम bnx2x_cmng_fns_init(काष्ठा bnx2x *bp, u8 पढ़ो_cfg, u8 cmng_type)
अणु
	काष्ठा cmng_init_input input;
	स_रखो(&input, 0, माप(काष्ठा cmng_init_input));

	input.port_rate = bp->link_vars.line_speed;

	अगर (cmng_type == CMNG_FNS_MINMAX && input.port_rate) अणु
		पूर्णांक vn;

		/* पढ़ो mf conf from shmem */
		अगर (पढ़ो_cfg)
			bnx2x_पढ़ो_mf_cfg(bp);

		/* vn_weight_sum and enable fairness अगर not 0 */
		bnx2x_calc_vn_min(bp, &input);

		/* calculate and set min-max rate क्रम each vn */
		अगर (bp->port.pmf)
			क्रम (vn = VN_0; vn < BP_MAX_VN_NUM(bp); vn++)
				bnx2x_calc_vn_max(bp, vn, &input);

		/* always enable rate shaping and fairness */
		input.flags.cmng_enables |=
					CMNG_FLAGS_PER_PORT_RATE_SHAPING_VN;

		bnx2x_init_cmng(&input, &bp->cmng);
		वापस;
	पूर्ण

	/* rate shaping and fairness are disabled */
	DP(NETIF_MSG_IFUP,
	   "rate shaping and fairness are disabled\n");
पूर्ण

अटल व्योम storm_स_रखो_cmng(काष्ठा bnx2x *bp,
			      काष्ठा cmng_init *cmng,
			      u8 port)
अणु
	पूर्णांक vn;
	माप_प्रकार size = माप(काष्ठा cmng_काष्ठा_per_port);

	u32 addr = BAR_XSTRORM_INTMEM +
			XSTORM_CMNG_PER_PORT_VARS_OFFSET(port);

	__storm_स_रखो_काष्ठा(bp, addr, size, (u32 *)&cmng->port);

	क्रम (vn = VN_0; vn < BP_MAX_VN_NUM(bp); vn++) अणु
		पूर्णांक func = func_by_vn(bp, vn);

		addr = BAR_XSTRORM_INTMEM +
		       XSTORM_RATE_SHAPING_PER_VN_VARS_OFFSET(func);
		size = माप(काष्ठा rate_shaping_vars_per_vn);
		__storm_स_रखो_काष्ठा(bp, addr, size,
				      (u32 *)&cmng->vnic.vnic_max_rate[vn]);

		addr = BAR_XSTRORM_INTMEM +
		       XSTORM_FAIRNESS_PER_VN_VARS_OFFSET(func);
		size = माप(काष्ठा fairness_vars_per_vn);
		__storm_स_रखो_काष्ठा(bp, addr, size,
				      (u32 *)&cmng->vnic.vnic_min_rate[vn]);
	पूर्ण
पूर्ण

/* init cmng mode in HW according to local configuration */
व्योम bnx2x_set_local_cmng(काष्ठा bnx2x *bp)
अणु
	पूर्णांक cmng_fns = bnx2x_get_cmng_fns_mode(bp);

	अगर (cmng_fns != CMNG_FNS_NONE) अणु
		bnx2x_cmng_fns_init(bp, false, cmng_fns);
		storm_स_रखो_cmng(bp, &bp->cmng, BP_PORT(bp));
	पूर्ण अन्यथा अणु
		/* rate shaping and fairness are disabled */
		DP(NETIF_MSG_IFUP,
		   "single function mode without fairness\n");
	पूर्ण
पूर्ण

/* This function is called upon link पूर्णांकerrupt */
अटल व्योम bnx2x_link_attn(काष्ठा bnx2x *bp)
अणु
	/* Make sure that we are synced with the current statistics */
	bnx2x_stats_handle(bp, STATS_EVENT_STOP);

	bnx2x_link_update(&bp->link_params, &bp->link_vars);

	bnx2x_init_dropless_fc(bp);

	अगर (bp->link_vars.link_up) अणु

		अगर (bp->link_vars.mac_type != MAC_TYPE_EMAC) अणु
			काष्ठा host_port_stats *pstats;

			pstats = bnx2x_sp(bp, port_stats);
			/* reset old mac stats */
			स_रखो(&(pstats->mac_stx[0]), 0,
			       माप(काष्ठा mac_stx));
		पूर्ण
		अगर (bp->state == BNX2X_STATE_OPEN)
			bnx2x_stats_handle(bp, STATS_EVENT_LINK_UP);
	पूर्ण

	अगर (bp->link_vars.link_up && bp->link_vars.line_speed)
		bnx2x_set_local_cmng(bp);

	__bnx2x_link_report(bp);

	अगर (IS_MF(bp))
		bnx2x_link_sync_notअगरy(bp);
पूर्ण

व्योम bnx2x__link_status_update(काष्ठा bnx2x *bp)
अणु
	अगर (bp->state != BNX2X_STATE_OPEN)
		वापस;

	/* पढ़ो updated dcb configuration */
	अगर (IS_PF(bp)) अणु
		bnx2x_dcbx_pmf_update(bp);
		bnx2x_link_status_update(&bp->link_params, &bp->link_vars);
		अगर (bp->link_vars.link_up)
			bnx2x_stats_handle(bp, STATS_EVENT_LINK_UP);
		अन्यथा
			bnx2x_stats_handle(bp, STATS_EVENT_STOP);
			/* indicate link status */
		bnx2x_link_report(bp);

	पूर्ण अन्यथा अणु /* VF */
		bp->port.supported[0] |= (SUPPORTED_10baseT_Half |
					  SUPPORTED_10baseT_Full |
					  SUPPORTED_100baseT_Half |
					  SUPPORTED_100baseT_Full |
					  SUPPORTED_1000baseT_Full |
					  SUPPORTED_2500baseX_Full |
					  SUPPORTED_10000baseT_Full |
					  SUPPORTED_TP |
					  SUPPORTED_FIBRE |
					  SUPPORTED_Autoneg |
					  SUPPORTED_Pause |
					  SUPPORTED_Asym_Pause);
		bp->port.advertising[0] = bp->port.supported[0];

		bp->link_params.bp = bp;
		bp->link_params.port = BP_PORT(bp);
		bp->link_params.req_duplex[0] = DUPLEX_FULL;
		bp->link_params.req_flow_ctrl[0] = BNX2X_FLOW_CTRL_NONE;
		bp->link_params.req_line_speed[0] = SPEED_10000;
		bp->link_params.speed_cap_mask[0] = 0x7f0000;
		bp->link_params.चयन_cfg = SWITCH_CFG_10G;
		bp->link_vars.mac_type = MAC_TYPE_BMAC;
		bp->link_vars.line_speed = SPEED_10000;
		bp->link_vars.link_status =
			(LINK_STATUS_LINK_UP |
			 LINK_STATUS_SPEED_AND_DUPLEX_10GTFD);
		bp->link_vars.link_up = 1;
		bp->link_vars.duplex = DUPLEX_FULL;
		bp->link_vars.flow_ctrl = BNX2X_FLOW_CTRL_NONE;
		__bnx2x_link_report(bp);

		bnx2x_sample_bulletin(bp);

		/* अगर bulletin board did not have an update क्रम link status
		 * __bnx2x_link_report will report current status
		 * but it will NOT duplicate report in हाल of alपढ़ोy reported
		 * during sampling bulletin board.
		 */
		bnx2x_stats_handle(bp, STATS_EVENT_LINK_UP);
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_afex_func_update(काष्ठा bnx2x *bp, u16 vअगरid,
				  u16 vlan_val, u8 allowed_prio)
अणु
	काष्ठा bnx2x_func_state_params func_params = अणुशून्यपूर्ण;
	काष्ठा bnx2x_func_afex_update_params *f_update_params =
		&func_params.params.afex_update;

	func_params.f_obj = &bp->func_obj;
	func_params.cmd = BNX2X_F_CMD_AFEX_UPDATE;

	/* no need to रुको क्रम RAMROD completion, so करोn't
	 * set RAMROD_COMP_WAIT flag
	 */

	f_update_params->vअगर_id = vअगरid;
	f_update_params->afex_शेष_vlan = vlan_val;
	f_update_params->allowed_priorities = allowed_prio;

	/* अगर ramrod can not be sent, response to MCP immediately */
	अगर (bnx2x_func_state_change(bp, &func_params) < 0)
		bnx2x_fw_command(bp, DRV_MSG_CODE_AFEX_VIFSET_ACK, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_afex_handle_vअगर_list_cmd(काष्ठा bnx2x *bp, u8 cmd_type,
					  u16 vअगर_index, u8 func_bit_map)
अणु
	काष्ठा bnx2x_func_state_params func_params = अणुशून्यपूर्ण;
	काष्ठा bnx2x_func_afex_vअगरlists_params *update_params =
		&func_params.params.afex_vअगरlists;
	पूर्णांक rc;
	u32 drv_msg_code;

	/* validate only LIST_SET and LIST_GET are received from चयन */
	अगर ((cmd_type != VIF_LIST_RULE_GET) && (cmd_type != VIF_LIST_RULE_SET))
		BNX2X_ERR("BUG! afex_handle_vif_list_cmd invalid type 0x%x\n",
			  cmd_type);

	func_params.f_obj = &bp->func_obj;
	func_params.cmd = BNX2X_F_CMD_AFEX_VIFLISTS;

	/* set parameters according to cmd_type */
	update_params->afex_vअगर_list_command = cmd_type;
	update_params->vअगर_list_index = vअगर_index;
	update_params->func_bit_map =
		(cmd_type == VIF_LIST_RULE_GET) ? 0 : func_bit_map;
	update_params->func_to_clear = 0;
	drv_msg_code =
		(cmd_type == VIF_LIST_RULE_GET) ?
		DRV_MSG_CODE_AFEX_LISTGET_ACK :
		DRV_MSG_CODE_AFEX_LISTSET_ACK;

	/* अगर ramrod can not be sent, respond to MCP immediately क्रम
	 * SET and GET requests (other are not triggered from MCP)
	 */
	rc = bnx2x_func_state_change(bp, &func_params);
	अगर (rc < 0)
		bnx2x_fw_command(bp, drv_msg_code, 0);

	वापस 0;
पूर्ण

अटल व्योम bnx2x_handle_afex_cmd(काष्ठा bnx2x *bp, u32 cmd)
अणु
	काष्ठा afex_stats afex_stats;
	u32 func = BP_ABS_FUNC(bp);
	u32 mf_config;
	u16 vlan_val;
	u32 vlan_prio;
	u16 vअगर_id;
	u8 allowed_prio;
	u8 vlan_mode;
	u32 addr_to_ग_लिखो, vअगरid, addrs, stats_type, i;

	अगर (cmd & DRV_STATUS_AFEX_LISTGET_REQ) अणु
		vअगरid = SHMEM2_RD(bp, afex_param1_to_driver[BP_FW_MB_IDX(bp)]);
		DP(BNX2X_MSG_MCP,
		   "afex: got MCP req LISTGET_REQ for vifid 0x%x\n", vअगरid);
		bnx2x_afex_handle_vअगर_list_cmd(bp, VIF_LIST_RULE_GET, vअगरid, 0);
	पूर्ण

	अगर (cmd & DRV_STATUS_AFEX_LISTSET_REQ) अणु
		vअगरid = SHMEM2_RD(bp, afex_param1_to_driver[BP_FW_MB_IDX(bp)]);
		addrs = SHMEM2_RD(bp, afex_param2_to_driver[BP_FW_MB_IDX(bp)]);
		DP(BNX2X_MSG_MCP,
		   "afex: got MCP req LISTSET_REQ for vifid 0x%x addrs 0x%x\n",
		   vअगरid, addrs);
		bnx2x_afex_handle_vअगर_list_cmd(bp, VIF_LIST_RULE_SET, vअगरid,
					       addrs);
	पूर्ण

	अगर (cmd & DRV_STATUS_AFEX_STATSGET_REQ) अणु
		addr_to_ग_लिखो = SHMEM2_RD(bp,
			afex_scratchpad_addr_to_ग_लिखो[BP_FW_MB_IDX(bp)]);
		stats_type = SHMEM2_RD(bp,
			afex_param1_to_driver[BP_FW_MB_IDX(bp)]);

		DP(BNX2X_MSG_MCP,
		   "afex: got MCP req STATSGET_REQ, write to addr 0x%x\n",
		   addr_to_ग_लिखो);

		bnx2x_afex_collect_stats(bp, (व्योम *)&afex_stats, stats_type);

		/* ग_लिखो response to scratchpad, क्रम MCP */
		क्रम (i = 0; i < (माप(काष्ठा afex_stats)/माप(u32)); i++)
			REG_WR(bp, addr_to_ग_लिखो + i*माप(u32),
			       *(((u32 *)(&afex_stats))+i));

		/* send ack message to MCP */
		bnx2x_fw_command(bp, DRV_MSG_CODE_AFEX_STATSGET_ACK, 0);
	पूर्ण

	अगर (cmd & DRV_STATUS_AFEX_VIFSET_REQ) अणु
		mf_config = MF_CFG_RD(bp, func_mf_config[func].config);
		bp->mf_config[BP_VN(bp)] = mf_config;
		DP(BNX2X_MSG_MCP,
		   "afex: got MCP req VIFSET_REQ, mf_config 0x%x\n",
		   mf_config);

		/* अगर VIF_SET is "enabled" */
		अगर (!(mf_config & FUNC_MF_CFG_FUNC_DISABLED)) अणु
			/* set rate limit directly to पूर्णांकernal RAM */
			काष्ठा cmng_init_input cmng_input;
			काष्ठा rate_shaping_vars_per_vn m_rs_vn;
			माप_प्रकार size = माप(काष्ठा rate_shaping_vars_per_vn);
			u32 addr = BAR_XSTRORM_INTMEM +
			    XSTORM_RATE_SHAPING_PER_VN_VARS_OFFSET(BP_FUNC(bp));

			bp->mf_config[BP_VN(bp)] = mf_config;

			bnx2x_calc_vn_max(bp, BP_VN(bp), &cmng_input);
			m_rs_vn.vn_counter.rate =
				cmng_input.vnic_max_rate[BP_VN(bp)];
			m_rs_vn.vn_counter.quota =
				(m_rs_vn.vn_counter.rate *
				 RS_PERIODIC_TIMEOUT_USEC) / 8;

			__storm_स_रखो_काष्ठा(bp, addr, size, (u32 *)&m_rs_vn);

			/* पढ़ो relevant values from mf_cfg काष्ठा in shmem */
			vअगर_id =
				(MF_CFG_RD(bp, func_mf_config[func].e1hov_tag) &
				 FUNC_MF_CFG_E1HOV_TAG_MASK) >>
				FUNC_MF_CFG_E1HOV_TAG_SHIFT;
			vlan_val =
				(MF_CFG_RD(bp, func_mf_config[func].e1hov_tag) &
				 FUNC_MF_CFG_AFEX_VLAN_MASK) >>
				FUNC_MF_CFG_AFEX_VLAN_SHIFT;
			vlan_prio = (mf_config &
				     FUNC_MF_CFG_TRANSMIT_PRIORITY_MASK) >>
				    FUNC_MF_CFG_TRANSMIT_PRIORITY_SHIFT;
			vlan_val |= (vlan_prio << VLAN_PRIO_SHIFT);
			vlan_mode =
				(MF_CFG_RD(bp,
					   func_mf_config[func].afex_config) &
				 FUNC_MF_CFG_AFEX_VLAN_MODE_MASK) >>
				FUNC_MF_CFG_AFEX_VLAN_MODE_SHIFT;
			allowed_prio =
				(MF_CFG_RD(bp,
					   func_mf_config[func].afex_config) &
				 FUNC_MF_CFG_AFEX_COS_FILTER_MASK) >>
				FUNC_MF_CFG_AFEX_COS_FILTER_SHIFT;

			/* send ramrod to FW, वापस in हाल of failure */
			अगर (bnx2x_afex_func_update(bp, vअगर_id, vlan_val,
						   allowed_prio))
				वापस;

			bp->afex_def_vlan_tag = vlan_val;
			bp->afex_vlan_mode = vlan_mode;
		पूर्ण अन्यथा अणु
			/* notअगरy link करोwn because BP->flags is disabled */
			bnx2x_link_report(bp);

			/* send INVALID VIF ramrod to FW */
			bnx2x_afex_func_update(bp, 0xFFFF, 0, 0);

			/* Reset the शेष afex VLAN */
			bp->afex_def_vlan_tag = -1;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम bnx2x_handle_update_svid_cmd(काष्ठा bnx2x *bp)
अणु
	काष्ठा bnx2x_func_चयन_update_params *चयन_update_params;
	काष्ठा bnx2x_func_state_params func_params;

	स_रखो(&func_params, 0, माप(काष्ठा bnx2x_func_state_params));
	चयन_update_params = &func_params.params.चयन_update;
	func_params.f_obj = &bp->func_obj;
	func_params.cmd = BNX2X_F_CMD_SWITCH_UPDATE;

	/* Prepare parameters क्रम function state transitions */
	__set_bit(RAMROD_COMP_WAIT, &func_params.ramrod_flags);
	__set_bit(RAMROD_RETRY, &func_params.ramrod_flags);

	अगर (IS_MF_UFP(bp) || IS_MF_BD(bp)) अणु
		पूर्णांक func = BP_ABS_FUNC(bp);
		u32 val;

		/* Re-learn the S-tag from shmem */
		val = MF_CFG_RD(bp, func_mf_config[func].e1hov_tag) &
				FUNC_MF_CFG_E1HOV_TAG_MASK;
		अगर (val != FUNC_MF_CFG_E1HOV_TAG_DEFAULT) अणु
			bp->mf_ov = val;
		पूर्ण अन्यथा अणु
			BNX2X_ERR("Got an SVID event, but no tag is configured in shmem\n");
			जाओ fail;
		पूर्ण

		/* Configure new S-tag in LLH */
		REG_WR(bp, NIG_REG_LLH0_FUNC_VLAN_ID + BP_PORT(bp) * 8,
		       bp->mf_ov);

		/* Send Ramrod to update FW of change */
		__set_bit(BNX2X_F_UPDATE_SD_VLAN_TAG_CHNG,
			  &चयन_update_params->changes);
		चयन_update_params->vlan = bp->mf_ov;

		अगर (bnx2x_func_state_change(bp, &func_params) < 0) अणु
			BNX2X_ERR("Failed to configure FW of S-tag Change to %02x\n",
				  bp->mf_ov);
			जाओ fail;
		पूर्ण अन्यथा अणु
			DP(BNX2X_MSG_MCP, "Configured S-tag %02x\n",
			   bp->mf_ov);
		पूर्ण
	पूर्ण अन्यथा अणु
		जाओ fail;
	पूर्ण

	bnx2x_fw_command(bp, DRV_MSG_CODE_OEM_UPDATE_SVID_OK, 0);
	वापस;
fail:
	bnx2x_fw_command(bp, DRV_MSG_CODE_OEM_UPDATE_SVID_FAILURE, 0);
पूर्ण

अटल व्योम bnx2x_pmf_update(काष्ठा bnx2x *bp)
अणु
	पूर्णांक port = BP_PORT(bp);
	u32 val;

	bp->port.pmf = 1;
	DP(BNX2X_MSG_MCP, "pmf %d\n", bp->port.pmf);

	/*
	 * We need the mb() to ensure the ordering between the writing to
	 * bp->port.pmf here and पढ़ोing it from the bnx2x_periodic_task().
	 */
	smp_mb();

	/* queue a periodic task */
	queue_delayed_work(bnx2x_wq, &bp->period_task, 0);

	bnx2x_dcbx_pmf_update(bp);

	/* enable nig attention */
	val = (0xff0f | (1 << (BP_VN(bp) + 4)));
	अगर (bp->common.पूर्णांक_block == INT_BLOCK_HC) अणु
		REG_WR(bp, HC_REG_TRAILING_EDGE_0 + port*8, val);
		REG_WR(bp, HC_REG_LEADING_EDGE_0 + port*8, val);
	पूर्ण अन्यथा अगर (!CHIP_IS_E1x(bp)) अणु
		REG_WR(bp, IGU_REG_TRAILING_EDGE_LATCH, val);
		REG_WR(bp, IGU_REG_LEADING_EDGE_LATCH, val);
	पूर्ण

	bnx2x_stats_handle(bp, STATS_EVENT_PMF);
पूर्ण

/* end of Link */

/* slow path */

/*
 * General service functions
 */

/* send the MCP a request, block until there is a reply */
u32 bnx2x_fw_command(काष्ठा bnx2x *bp, u32 command, u32 param)
अणु
	पूर्णांक mb_idx = BP_FW_MB_IDX(bp);
	u32 seq;
	u32 rc = 0;
	u32 cnt = 1;
	u8 delay = CHIP_REV_IS_SLOW(bp) ? 100 : 10;

	mutex_lock(&bp->fw_mb_mutex);
	seq = ++bp->fw_seq;
	SHMEM_WR(bp, func_mb[mb_idx].drv_mb_param, param);
	SHMEM_WR(bp, func_mb[mb_idx].drv_mb_header, (command | seq));

	DP(BNX2X_MSG_MCP, "wrote command (%x) to FW MB param 0x%08x\n",
			(command | seq), param);

	करो अणु
		/* let the FW करो it's magic ... */
		msleep(delay);

		rc = SHMEM_RD(bp, func_mb[mb_idx].fw_mb_header);

		/* Give the FW up to 5 second (500*10ms) */
	पूर्ण जबतक ((seq != (rc & FW_MSG_SEQ_NUMBER_MASK)) && (cnt++ < 500));

	DP(BNX2X_MSG_MCP, "[after %d ms] read (%x) seq is (%x) from FW MB\n",
	   cnt*delay, rc, seq);

	/* is this a reply to our command? */
	अगर (seq == (rc & FW_MSG_SEQ_NUMBER_MASK))
		rc &= FW_MSG_CODE_MASK;
	अन्यथा अणु
		/* FW BUG! */
		BNX2X_ERR("FW failed to respond!\n");
		bnx2x_fw_dump(bp);
		rc = 0;
	पूर्ण
	mutex_unlock(&bp->fw_mb_mutex);

	वापस rc;
पूर्ण

अटल व्योम storm_स_रखो_func_cfg(काष्ठा bnx2x *bp,
				 काष्ठा tstorm_eth_function_common_config *tcfg,
				 u16 असल_fid)
अणु
	माप_प्रकार size = माप(काष्ठा tstorm_eth_function_common_config);

	u32 addr = BAR_TSTRORM_INTMEM +
			TSTORM_FUNCTION_COMMON_CONFIG_OFFSET(असल_fid);

	__storm_स_रखो_काष्ठा(bp, addr, size, (u32 *)tcfg);
पूर्ण

व्योम bnx2x_func_init(काष्ठा bnx2x *bp, काष्ठा bnx2x_func_init_params *p)
अणु
	अगर (CHIP_IS_E1x(bp)) अणु
		काष्ठा tstorm_eth_function_common_config tcfg = अणु0पूर्ण;

		storm_स_रखो_func_cfg(bp, &tcfg, p->func_id);
	पूर्ण

	/* Enable the function in the FW */
	storm_स_रखो_vf_to_pf(bp, p->func_id, p->pf_id);
	storm_स_रखो_func_en(bp, p->func_id, 1);

	/* spq */
	अगर (p->spq_active) अणु
		storm_स_रखो_spq_addr(bp, p->spq_map, p->func_id);
		REG_WR(bp, XSEM_REG_FAST_MEMORY +
		       XSTORM_SPQ_PROD_OFFSET(p->func_id), p->spq_prod);
	पूर्ण
पूर्ण

/**
 * bnx2x_get_common_flags - Return common flags
 *
 * @bp:		device handle
 * @fp:		queue handle
 * @zero_stats:	TRUE अगर statistics zeroing is needed
 *
 * Return the flags that are common क्रम the Tx-only and not normal connections.
 */
अटल अचिन्हित दीर्घ bnx2x_get_common_flags(काष्ठा bnx2x *bp,
					    काष्ठा bnx2x_fastpath *fp,
					    bool zero_stats)
अणु
	अचिन्हित दीर्घ flags = 0;

	/* PF driver will always initialize the Queue to an ACTIVE state */
	__set_bit(BNX2X_Q_FLG_ACTIVE, &flags);

	/* tx only connections collect statistics (on the same index as the
	 * parent connection). The statistics are zeroed when the parent
	 * connection is initialized.
	 */

	__set_bit(BNX2X_Q_FLG_STATS, &flags);
	अगर (zero_stats)
		__set_bit(BNX2X_Q_FLG_ZERO_STATS, &flags);

	अगर (bp->flags & TX_SWITCHING)
		__set_bit(BNX2X_Q_FLG_TX_SWITCH, &flags);

	__set_bit(BNX2X_Q_FLG_PCSUM_ON_PKT, &flags);
	__set_bit(BNX2X_Q_FLG_TUN_INC_INNER_IP_ID, &flags);

#अगर_घोषित BNX2X_STOP_ON_ERROR
	__set_bit(BNX2X_Q_FLG_TX_SEC, &flags);
#पूर्ण_अगर

	वापस flags;
पूर्ण

अटल अचिन्हित दीर्घ bnx2x_get_q_flags(काष्ठा bnx2x *bp,
				       काष्ठा bnx2x_fastpath *fp,
				       bool leading)
अणु
	अचिन्हित दीर्घ flags = 0;

	/* calculate other queue flags */
	अगर (IS_MF_SD(bp))
		__set_bit(BNX2X_Q_FLG_OV, &flags);

	अगर (IS_FCOE_FP(fp)) अणु
		__set_bit(BNX2X_Q_FLG_FCOE, &flags);
		/* For FCoE - क्रमce usage of शेष priority (क्रम afex) */
		__set_bit(BNX2X_Q_FLG_FORCE_DEFAULT_PRI, &flags);
	पूर्ण

	अगर (fp->mode != TPA_MODE_DISABLED) अणु
		__set_bit(BNX2X_Q_FLG_TPA, &flags);
		__set_bit(BNX2X_Q_FLG_TPA_IPV6, &flags);
		अगर (fp->mode == TPA_MODE_GRO)
			__set_bit(BNX2X_Q_FLG_TPA_GRO, &flags);
	पूर्ण

	अगर (leading) अणु
		__set_bit(BNX2X_Q_FLG_LEADING_RSS, &flags);
		__set_bit(BNX2X_Q_FLG_MCAST, &flags);
	पूर्ण

	/* Always set HW VLAN stripping */
	__set_bit(BNX2X_Q_FLG_VLAN, &flags);

	/* configure silent vlan removal */
	अगर (IS_MF_AFEX(bp))
		__set_bit(BNX2X_Q_FLG_SILENT_VLAN_REM, &flags);

	वापस flags | bnx2x_get_common_flags(bp, fp, true);
पूर्ण

अटल व्योम bnx2x_pf_q_prep_general(काष्ठा bnx2x *bp,
	काष्ठा bnx2x_fastpath *fp, काष्ठा bnx2x_general_setup_params *gen_init,
	u8 cos)
अणु
	gen_init->stat_id = bnx2x_stats_id(fp);
	gen_init->spcl_id = fp->cl_id;

	/* Always use mini-jumbo MTU क्रम FCoE L2 ring */
	अगर (IS_FCOE_FP(fp))
		gen_init->mtu = BNX2X_FCOE_MINI_JUMBO_MTU;
	अन्यथा
		gen_init->mtu = bp->dev->mtu;

	gen_init->cos = cos;

	gen_init->fp_hsi = ETH_FP_HSI_VERSION;
पूर्ण

अटल व्योम bnx2x_pf_rx_q_prep(काष्ठा bnx2x *bp,
	काष्ठा bnx2x_fastpath *fp, काष्ठा rxq_छोड़ो_params *छोड़ो,
	काष्ठा bnx2x_rxq_setup_params *rxq_init)
अणु
	u8 max_sge = 0;
	u16 sge_sz = 0;
	u16 tpa_agg_size = 0;

	अगर (fp->mode != TPA_MODE_DISABLED) अणु
		छोड़ो->sge_th_lo = SGE_TH_LO(bp);
		छोड़ो->sge_th_hi = SGE_TH_HI(bp);

		/* validate SGE ring has enough to cross high threshold */
		WARN_ON(bp->dropless_fc &&
				छोड़ो->sge_th_hi + FW_PREFETCH_CNT >
				MAX_RX_SGE_CNT * NUM_RX_SGE_PAGES);

		tpa_agg_size = TPA_AGG_SIZE;
		max_sge = SGE_PAGE_ALIGN(bp->dev->mtu) >>
			SGE_PAGE_SHIFT;
		max_sge = ((max_sge + PAGES_PER_SGE - 1) &
			  (~(PAGES_PER_SGE-1))) >> PAGES_PER_SGE_SHIFT;
		sge_sz = (u16)min_t(u32, SGE_PAGES, 0xffff);
	पूर्ण

	/* छोड़ो - not क्रम e1 */
	अगर (!CHIP_IS_E1(bp)) अणु
		छोड़ो->bd_th_lo = BD_TH_LO(bp);
		छोड़ो->bd_th_hi = BD_TH_HI(bp);

		छोड़ो->rcq_th_lo = RCQ_TH_LO(bp);
		छोड़ो->rcq_th_hi = RCQ_TH_HI(bp);
		/*
		 * validate that rings have enough entries to cross
		 * high thresholds
		 */
		WARN_ON(bp->dropless_fc &&
				छोड़ो->bd_th_hi + FW_PREFETCH_CNT >
				bp->rx_ring_size);
		WARN_ON(bp->dropless_fc &&
				छोड़ो->rcq_th_hi + FW_PREFETCH_CNT >
				NUM_RCQ_RINGS * MAX_RCQ_DESC_CNT);

		छोड़ो->pri_map = 1;
	पूर्ण

	/* rxq setup */
	rxq_init->dscr_map = fp->rx_desc_mapping;
	rxq_init->sge_map = fp->rx_sge_mapping;
	rxq_init->rcq_map = fp->rx_comp_mapping;
	rxq_init->rcq_np_map = fp->rx_comp_mapping + BCM_PAGE_SIZE;

	/* This should be a maximum number of data bytes that may be
	 * placed on the BD (not including paddings).
	 */
	rxq_init->buf_sz = fp->rx_buf_size - BNX2X_FW_RX_ALIGN_START -
			   BNX2X_FW_RX_ALIGN_END - IP_HEADER_ALIGNMENT_PADDING;

	rxq_init->cl_qzone_id = fp->cl_qzone_id;
	rxq_init->tpa_agg_sz = tpa_agg_size;
	rxq_init->sge_buf_sz = sge_sz;
	rxq_init->max_sges_pkt = max_sge;
	rxq_init->rss_engine_id = BP_FUNC(bp);
	rxq_init->mcast_engine_id = BP_FUNC(bp);

	/* Maximum number or simultaneous TPA aggregation क्रम this Queue.
	 *
	 * For PF Clients it should be the maximum available number.
	 * VF driver(s) may want to define it to a smaller value.
	 */
	rxq_init->max_tpa_queues = MAX_AGG_QS(bp);

	rxq_init->cache_line_log = BNX2X_RX_ALIGN_SHIFT;
	rxq_init->fw_sb_id = fp->fw_sb_id;

	अगर (IS_FCOE_FP(fp))
		rxq_init->sb_cq_index = HC_SP_INDEX_ETH_FCOE_RX_CQ_CONS;
	अन्यथा
		rxq_init->sb_cq_index = HC_INDEX_ETH_RX_CQ_CONS;
	/* configure silent vlan removal
	 * अगर multi function mode is afex, then mask शेष vlan
	 */
	अगर (IS_MF_AFEX(bp)) अणु
		rxq_init->silent_removal_value = bp->afex_def_vlan_tag;
		rxq_init->silent_removal_mask = VLAN_VID_MASK;
	पूर्ण
पूर्ण

अटल व्योम bnx2x_pf_tx_q_prep(काष्ठा bnx2x *bp,
	काष्ठा bnx2x_fastpath *fp, काष्ठा bnx2x_txq_setup_params *txq_init,
	u8 cos)
अणु
	txq_init->dscr_map = fp->txdata_ptr[cos]->tx_desc_mapping;
	txq_init->sb_cq_index = HC_INDEX_ETH_FIRST_TX_CQ_CONS + cos;
	txq_init->traffic_type = LLFC_TRAFFIC_TYPE_NW;
	txq_init->fw_sb_id = fp->fw_sb_id;

	/*
	 * set the tss leading client id क्रम TX classअगरication ==
	 * leading RSS client id
	 */
	txq_init->tss_leading_cl_id = bnx2x_fp(bp, 0, cl_id);

	अगर (IS_FCOE_FP(fp)) अणु
		txq_init->sb_cq_index = HC_SP_INDEX_ETH_FCOE_TX_CQ_CONS;
		txq_init->traffic_type = LLFC_TRAFFIC_TYPE_FCOE;
	पूर्ण
पूर्ण

अटल व्योम bnx2x_pf_init(काष्ठा bnx2x *bp)
अणु
	काष्ठा bnx2x_func_init_params func_init = अणु0पूर्ण;
	काष्ठा event_ring_data eq_data = अणु अणु0पूर्ण पूर्ण;

	अगर (!CHIP_IS_E1x(bp)) अणु
		/* reset IGU PF statistics: MSIX + ATTN */
		/* PF */
		REG_WR(bp, IGU_REG_STATISTIC_NUM_MESSAGE_SENT +
			   BNX2X_IGU_STAS_MSG_VF_CNT*4 +
			   (CHIP_MODE_IS_4_PORT(bp) ?
				BP_FUNC(bp) : BP_VN(bp))*4, 0);
		/* ATTN */
		REG_WR(bp, IGU_REG_STATISTIC_NUM_MESSAGE_SENT +
			   BNX2X_IGU_STAS_MSG_VF_CNT*4 +
			   BNX2X_IGU_STAS_MSG_PF_CNT*4 +
			   (CHIP_MODE_IS_4_PORT(bp) ?
				BP_FUNC(bp) : BP_VN(bp))*4, 0);
	पूर्ण

	func_init.spq_active = true;
	func_init.pf_id = BP_FUNC(bp);
	func_init.func_id = BP_FUNC(bp);
	func_init.spq_map = bp->spq_mapping;
	func_init.spq_prod = bp->spq_prod_idx;

	bnx2x_func_init(bp, &func_init);

	स_रखो(&(bp->cmng), 0, माप(काष्ठा cmng_काष्ठा_per_port));

	/*
	 * Congestion management values depend on the link rate
	 * There is no active link so initial link rate is set to 10 Gbps.
	 * When the link comes up The congestion management values are
	 * re-calculated according to the actual link rate.
	 */
	bp->link_vars.line_speed = SPEED_10000;
	bnx2x_cmng_fns_init(bp, true, bnx2x_get_cmng_fns_mode(bp));

	/* Only the PMF sets the HW */
	अगर (bp->port.pmf)
		storm_स_रखो_cmng(bp, &bp->cmng, BP_PORT(bp));

	/* init Event Queue - PCI bus guarantees correct endianity*/
	eq_data.base_addr.hi = U64_HI(bp->eq_mapping);
	eq_data.base_addr.lo = U64_LO(bp->eq_mapping);
	eq_data.producer = bp->eq_prod;
	eq_data.index_id = HC_SP_INDEX_EQ_CONS;
	eq_data.sb_id = DEF_SB_ID;
	storm_स_रखो_eq_data(bp, &eq_data, BP_FUNC(bp));
पूर्ण

अटल व्योम bnx2x_e1h_disable(काष्ठा bnx2x *bp)
अणु
	पूर्णांक port = BP_PORT(bp);

	bnx2x_tx_disable(bp);

	REG_WR(bp, NIG_REG_LLH0_FUNC_EN + port*8, 0);
पूर्ण

अटल व्योम bnx2x_e1h_enable(काष्ठा bnx2x *bp)
अणु
	पूर्णांक port = BP_PORT(bp);

	अगर (!(IS_MF_UFP(bp) && BNX2X_IS_MF_SD_PROTOCOL_FCOE(bp)))
		REG_WR(bp, NIG_REG_LLH0_FUNC_EN + port * 8, 1);

	/* Tx queue should be only re-enabled */
	netअगर_tx_wake_all_queues(bp->dev);

	/*
	 * Should not call netअगर_carrier_on since it will be called अगर the link
	 * is up when checking क्रम link state
	 */
पूर्ण

#घोषणा DRV_INFO_ETH_STAT_NUM_MACS_REQUIRED 3

अटल व्योम bnx2x_drv_info_ether_stat(काष्ठा bnx2x *bp)
अणु
	काष्ठा eth_stats_info *ether_stat =
		&bp->slowpath->drv_info_to_mcp.ether_stat;
	काष्ठा bnx2x_vlan_mac_obj *mac_obj =
		&bp->sp_objs->mac_obj;
	पूर्णांक i;

	strlcpy(ether_stat->version, DRV_MODULE_VERSION,
		ETH_STAT_INFO_VERSION_LEN);

	/* get DRV_INFO_ETH_STAT_NUM_MACS_REQUIRED macs, placing them in the
	 * mac_local field in ether_stat काष्ठा. The base address is offset by 2
	 * bytes to account क्रम the field being 8 bytes but a mac address is
	 * only 6 bytes. Likewise, the stride क्रम the get_n_elements function is
	 * 2 bytes to compensate from the 6 bytes of a mac to the 8 bytes
	 * allocated by the ether_stat काष्ठा, so the macs will land in their
	 * proper positions.
	 */
	क्रम (i = 0; i < DRV_INFO_ETH_STAT_NUM_MACS_REQUIRED; i++)
		स_रखो(ether_stat->mac_local + i, 0,
		       माप(ether_stat->mac_local[0]));
	mac_obj->get_n_elements(bp, &bp->sp_objs[0].mac_obj,
				DRV_INFO_ETH_STAT_NUM_MACS_REQUIRED,
				ether_stat->mac_local + MAC_PAD, MAC_PAD,
				ETH_ALEN);
	ether_stat->mtu_size = bp->dev->mtu;
	अगर (bp->dev->features & NETIF_F_RXCSUM)
		ether_stat->feature_flags |= FEATURE_ETH_CHKSUM_OFFLOAD_MASK;
	अगर (bp->dev->features & NETIF_F_TSO)
		ether_stat->feature_flags |= FEATURE_ETH_LSO_MASK;
	ether_stat->feature_flags |= bp->common.boot_mode;

	ether_stat->promiscuous_mode = (bp->dev->flags & IFF_PROMISC) ? 1 : 0;

	ether_stat->txq_size = bp->tx_ring_size;
	ether_stat->rxq_size = bp->rx_ring_size;

#अगर_घोषित CONFIG_BNX2X_SRIOV
	ether_stat->vf_cnt = IS_SRIOV(bp) ? bp->vfdb->sriov.nr_virtfn : 0;
#पूर्ण_अगर
पूर्ण

अटल व्योम bnx2x_drv_info_fcoe_stat(काष्ठा bnx2x *bp)
अणु
	काष्ठा bnx2x_dcbx_app_params *app = &bp->dcbx_port_params.app;
	काष्ठा fcoe_stats_info *fcoe_stat =
		&bp->slowpath->drv_info_to_mcp.fcoe_stat;

	अगर (!CNIC_LOADED(bp))
		वापस;

	स_नकल(fcoe_stat->mac_local + MAC_PAD, bp->fip_mac, ETH_ALEN);

	fcoe_stat->qos_priority =
		app->traffic_type_priority[LLFC_TRAFFIC_TYPE_FCOE];

	/* insert FCoE stats from ramrod response */
	अगर (!NO_FCOE(bp)) अणु
		काष्ठा tstorm_per_queue_stats *fcoe_q_tstorm_stats =
			&bp->fw_stats_data->queue_stats[FCOE_IDX(bp)].
			tstorm_queue_statistics;

		काष्ठा xstorm_per_queue_stats *fcoe_q_xstorm_stats =
			&bp->fw_stats_data->queue_stats[FCOE_IDX(bp)].
			xstorm_queue_statistics;

		काष्ठा fcoe_statistics_params *fw_fcoe_stat =
			&bp->fw_stats_data->fcoe;

		ADD_64_LE(fcoe_stat->rx_bytes_hi, LE32_0,
			  fcoe_stat->rx_bytes_lo,
			  fw_fcoe_stat->rx_stat0.fcoe_rx_byte_cnt);

		ADD_64_LE(fcoe_stat->rx_bytes_hi,
			  fcoe_q_tstorm_stats->rcv_ucast_bytes.hi,
			  fcoe_stat->rx_bytes_lo,
			  fcoe_q_tstorm_stats->rcv_ucast_bytes.lo);

		ADD_64_LE(fcoe_stat->rx_bytes_hi,
			  fcoe_q_tstorm_stats->rcv_bcast_bytes.hi,
			  fcoe_stat->rx_bytes_lo,
			  fcoe_q_tstorm_stats->rcv_bcast_bytes.lo);

		ADD_64_LE(fcoe_stat->rx_bytes_hi,
			  fcoe_q_tstorm_stats->rcv_mcast_bytes.hi,
			  fcoe_stat->rx_bytes_lo,
			  fcoe_q_tstorm_stats->rcv_mcast_bytes.lo);

		ADD_64_LE(fcoe_stat->rx_frames_hi, LE32_0,
			  fcoe_stat->rx_frames_lo,
			  fw_fcoe_stat->rx_stat0.fcoe_rx_pkt_cnt);

		ADD_64_LE(fcoe_stat->rx_frames_hi, LE32_0,
			  fcoe_stat->rx_frames_lo,
			  fcoe_q_tstorm_stats->rcv_ucast_pkts);

		ADD_64_LE(fcoe_stat->rx_frames_hi, LE32_0,
			  fcoe_stat->rx_frames_lo,
			  fcoe_q_tstorm_stats->rcv_bcast_pkts);

		ADD_64_LE(fcoe_stat->rx_frames_hi, LE32_0,
			  fcoe_stat->rx_frames_lo,
			  fcoe_q_tstorm_stats->rcv_mcast_pkts);

		ADD_64_LE(fcoe_stat->tx_bytes_hi, LE32_0,
			  fcoe_stat->tx_bytes_lo,
			  fw_fcoe_stat->tx_stat.fcoe_tx_byte_cnt);

		ADD_64_LE(fcoe_stat->tx_bytes_hi,
			  fcoe_q_xstorm_stats->ucast_bytes_sent.hi,
			  fcoe_stat->tx_bytes_lo,
			  fcoe_q_xstorm_stats->ucast_bytes_sent.lo);

		ADD_64_LE(fcoe_stat->tx_bytes_hi,
			  fcoe_q_xstorm_stats->bcast_bytes_sent.hi,
			  fcoe_stat->tx_bytes_lo,
			  fcoe_q_xstorm_stats->bcast_bytes_sent.lo);

		ADD_64_LE(fcoe_stat->tx_bytes_hi,
			  fcoe_q_xstorm_stats->mcast_bytes_sent.hi,
			  fcoe_stat->tx_bytes_lo,
			  fcoe_q_xstorm_stats->mcast_bytes_sent.lo);

		ADD_64_LE(fcoe_stat->tx_frames_hi, LE32_0,
			  fcoe_stat->tx_frames_lo,
			  fw_fcoe_stat->tx_stat.fcoe_tx_pkt_cnt);

		ADD_64_LE(fcoe_stat->tx_frames_hi, LE32_0,
			  fcoe_stat->tx_frames_lo,
			  fcoe_q_xstorm_stats->ucast_pkts_sent);

		ADD_64_LE(fcoe_stat->tx_frames_hi, LE32_0,
			  fcoe_stat->tx_frames_lo,
			  fcoe_q_xstorm_stats->bcast_pkts_sent);

		ADD_64_LE(fcoe_stat->tx_frames_hi, LE32_0,
			  fcoe_stat->tx_frames_lo,
			  fcoe_q_xstorm_stats->mcast_pkts_sent);
	पूर्ण

	/* ask L5 driver to add data to the काष्ठा */
	bnx2x_cnic_notअगरy(bp, CNIC_CTL_FCOE_STATS_GET_CMD);
पूर्ण

अटल व्योम bnx2x_drv_info_iscsi_stat(काष्ठा bnx2x *bp)
अणु
	काष्ठा bnx2x_dcbx_app_params *app = &bp->dcbx_port_params.app;
	काष्ठा iscsi_stats_info *iscsi_stat =
		&bp->slowpath->drv_info_to_mcp.iscsi_stat;

	अगर (!CNIC_LOADED(bp))
		वापस;

	स_नकल(iscsi_stat->mac_local + MAC_PAD, bp->cnic_eth_dev.iscsi_mac,
	       ETH_ALEN);

	iscsi_stat->qos_priority =
		app->traffic_type_priority[LLFC_TRAFFIC_TYPE_ISCSI];

	/* ask L5 driver to add data to the काष्ठा */
	bnx2x_cnic_notअगरy(bp, CNIC_CTL_ISCSI_STATS_GET_CMD);
पूर्ण

/* called due to MCP event (on pmf):
 *	reपढ़ो new bandwidth configuration
 *	configure FW
 *	notअगरy others function about the change
 */
अटल व्योम bnx2x_config_mf_bw(काष्ठा bnx2x *bp)
अणु
	/* Workaround क्रम MFW bug.
	 * MFW is not supposed to generate BW attention in
	 * single function mode.
	 */
	अगर (!IS_MF(bp)) अणु
		DP(BNX2X_MSG_MCP,
		   "Ignoring MF BW config in single function mode\n");
		वापस;
	पूर्ण

	अगर (bp->link_vars.link_up) अणु
		bnx2x_cmng_fns_init(bp, true, CMNG_FNS_MINMAX);
		bnx2x_link_sync_notअगरy(bp);
	पूर्ण
	storm_स_रखो_cmng(bp, &bp->cmng, BP_PORT(bp));
पूर्ण

अटल व्योम bnx2x_set_mf_bw(काष्ठा bnx2x *bp)
अणु
	bnx2x_config_mf_bw(bp);
	bnx2x_fw_command(bp, DRV_MSG_CODE_SET_MF_BW_ACK, 0);
पूर्ण

अटल व्योम bnx2x_handle_eee_event(काष्ठा bnx2x *bp)
अणु
	DP(BNX2X_MSG_MCP, "EEE - LLDP event\n");
	bnx2x_fw_command(bp, DRV_MSG_CODE_EEE_RESULTS_ACK, 0);
पूर्ण

#घोषणा BNX2X_UPDATE_DRV_INFO_IND_LENGTH	(20)
#घोषणा BNX2X_UPDATE_DRV_INFO_IND_COUNT		(25)

अटल व्योम bnx2x_handle_drv_info_req(काष्ठा bnx2x *bp)
अणु
	क्रमागत drv_info_opcode op_code;
	u32 drv_info_ctl = SHMEM2_RD(bp, drv_info_control);
	bool release = false;
	पूर्णांक रुको;

	/* अगर drv_info version supported by MFW करोesn't match - send NACK */
	अगर ((drv_info_ctl & DRV_INFO_CONTROL_VER_MASK) != DRV_INFO_CUR_VER) अणु
		bnx2x_fw_command(bp, DRV_MSG_CODE_DRV_INFO_NACK, 0);
		वापस;
	पूर्ण

	op_code = (drv_info_ctl & DRV_INFO_CONTROL_OP_CODE_MASK) >>
		  DRV_INFO_CONTROL_OP_CODE_SHIFT;

	/* Must prevent other flows from accessing drv_info_to_mcp */
	mutex_lock(&bp->drv_info_mutex);

	स_रखो(&bp->slowpath->drv_info_to_mcp, 0,
	       माप(जोड़ drv_info_to_mcp));

	चयन (op_code) अणु
	हाल ETH_STATS_OPCODE:
		bnx2x_drv_info_ether_stat(bp);
		अवरोध;
	हाल FCOE_STATS_OPCODE:
		bnx2x_drv_info_fcoe_stat(bp);
		अवरोध;
	हाल ISCSI_STATS_OPCODE:
		bnx2x_drv_info_iscsi_stat(bp);
		अवरोध;
	शेष:
		/* अगर op code isn't supported - send NACK */
		bnx2x_fw_command(bp, DRV_MSG_CODE_DRV_INFO_NACK, 0);
		जाओ out;
	पूर्ण

	/* अगर we got drv_info attn from MFW then these fields are defined in
	 * shmem2 क्रम sure
	 */
	SHMEM2_WR(bp, drv_info_host_addr_lo,
		U64_LO(bnx2x_sp_mapping(bp, drv_info_to_mcp)));
	SHMEM2_WR(bp, drv_info_host_addr_hi,
		U64_HI(bnx2x_sp_mapping(bp, drv_info_to_mcp)));

	bnx2x_fw_command(bp, DRV_MSG_CODE_DRV_INFO_ACK, 0);

	/* Since possible management wants both this and get_driver_version
	 * need to रुको until management notअगरies us it finished utilizing
	 * the buffer.
	 */
	अगर (!SHMEM2_HAS(bp, mfw_drv_indication)) अणु
		DP(BNX2X_MSG_MCP, "Management does not support indication\n");
	पूर्ण अन्यथा अगर (!bp->drv_info_mng_owner) अणु
		u32 bit = MFW_DRV_IND_READ_DONE_OFFSET((BP_ABS_FUNC(bp) >> 1));

		क्रम (रुको = 0; रुको < BNX2X_UPDATE_DRV_INFO_IND_COUNT; रुको++) अणु
			u32 indication = SHMEM2_RD(bp, mfw_drv_indication);

			/* Management is करोne; need to clear indication */
			अगर (indication & bit) अणु
				SHMEM2_WR(bp, mfw_drv_indication,
					  indication & ~bit);
				release = true;
				अवरोध;
			पूर्ण

			msleep(BNX2X_UPDATE_DRV_INFO_IND_LENGTH);
		पूर्ण
	पूर्ण
	अगर (!release) अणु
		DP(BNX2X_MSG_MCP, "Management did not release indication\n");
		bp->drv_info_mng_owner = true;
	पूर्ण

out:
	mutex_unlock(&bp->drv_info_mutex);
पूर्ण

अटल u32 bnx2x_update_mng_version_utility(u8 *version, bool bnx2x_क्रमmat)
अणु
	u8 vals[4];
	पूर्णांक i = 0;

	अगर (bnx2x_क्रमmat) अणु
		i = माला_पूछो(version, "1.%c%hhd.%hhd.%hhd",
			   &vals[0], &vals[1], &vals[2], &vals[3]);
		अगर (i > 0)
			vals[0] -= '0';
	पूर्ण अन्यथा अणु
		i = माला_पूछो(version, "%hhd.%hhd.%hhd.%hhd",
			   &vals[0], &vals[1], &vals[2], &vals[3]);
	पूर्ण

	जबतक (i < 4)
		vals[i++] = 0;

	वापस (vals[0] << 24) | (vals[1] << 16) | (vals[2] << 8) | vals[3];
पूर्ण

व्योम bnx2x_update_mng_version(काष्ठा bnx2x *bp)
अणु
	u32 iscsiver = DRV_VER_NOT_LOADED;
	u32 fcoever = DRV_VER_NOT_LOADED;
	u32 ethver = DRV_VER_NOT_LOADED;
	पूर्णांक idx = BP_FW_MB_IDX(bp);
	u8 *version;

	अगर (!SHMEM2_HAS(bp, func_os_drv_ver))
		वापस;

	mutex_lock(&bp->drv_info_mutex);
	/* Must not proceed when `bnx2x_handle_drv_info_req' is feasible */
	अगर (bp->drv_info_mng_owner)
		जाओ out;

	अगर (bp->state != BNX2X_STATE_OPEN)
		जाओ out;

	/* Parse ethernet driver version */
	ethver = bnx2x_update_mng_version_utility(DRV_MODULE_VERSION, true);
	अगर (!CNIC_LOADED(bp))
		जाओ out;

	/* Try getting storage driver version via cnic */
	स_रखो(&bp->slowpath->drv_info_to_mcp, 0,
	       माप(जोड़ drv_info_to_mcp));
	bnx2x_drv_info_iscsi_stat(bp);
	version = bp->slowpath->drv_info_to_mcp.iscsi_stat.version;
	iscsiver = bnx2x_update_mng_version_utility(version, false);

	स_रखो(&bp->slowpath->drv_info_to_mcp, 0,
	       माप(जोड़ drv_info_to_mcp));
	bnx2x_drv_info_fcoe_stat(bp);
	version = bp->slowpath->drv_info_to_mcp.fcoe_stat.version;
	fcoever = bnx2x_update_mng_version_utility(version, false);

out:
	SHMEM2_WR(bp, func_os_drv_ver[idx].versions[DRV_PERS_ETHERNET], ethver);
	SHMEM2_WR(bp, func_os_drv_ver[idx].versions[DRV_PERS_ISCSI], iscsiver);
	SHMEM2_WR(bp, func_os_drv_ver[idx].versions[DRV_PERS_FCOE], fcoever);

	mutex_unlock(&bp->drv_info_mutex);

	DP(BNX2X_MSG_MCP, "Setting driver version: ETH [%08x] iSCSI [%08x] FCoE [%08x]\n",
	   ethver, iscsiver, fcoever);
पूर्ण

व्योम bnx2x_update_mfw_dump(काष्ठा bnx2x *bp)
अणु
	u32 drv_ver;
	u32 valid_dump;

	अगर (!SHMEM2_HAS(bp, drv_info))
		वापस;

	/* Update Driver load समय, possibly broken in y2038 */
	SHMEM2_WR(bp, drv_info.epoc, (u32)kसमय_get_real_seconds());

	drv_ver = bnx2x_update_mng_version_utility(DRV_MODULE_VERSION, true);
	SHMEM2_WR(bp, drv_info.drv_ver, drv_ver);

	SHMEM2_WR(bp, drv_info.fw_ver, REG_RD(bp, XSEM_REG_PRAM));

	/* Check & notअगरy On-Chip dump. */
	valid_dump = SHMEM2_RD(bp, drv_info.valid_dump);

	अगर (valid_dump & FIRST_DUMP_VALID)
		DP(NETIF_MSG_IFUP, "A valid On-Chip MFW dump found on 1st partition\n");

	अगर (valid_dump & SECOND_DUMP_VALID)
		DP(NETIF_MSG_IFUP, "A valid On-Chip MFW dump found on 2nd partition\n");
पूर्ण

अटल व्योम bnx2x_oem_event(काष्ठा bnx2x *bp, u32 event)
अणु
	u32 cmd_ok, cmd_fail;

	/* sanity */
	अगर (event & DRV_STATUS_DCC_EVENT_MASK &&
	    event & DRV_STATUS_OEM_EVENT_MASK) अणु
		BNX2X_ERR("Received simultaneous events %08x\n", event);
		वापस;
	पूर्ण

	अगर (event & DRV_STATUS_DCC_EVENT_MASK) अणु
		cmd_fail = DRV_MSG_CODE_DCC_FAILURE;
		cmd_ok = DRV_MSG_CODE_DCC_OK;
	पूर्ण अन्यथा /* अगर (event & DRV_STATUS_OEM_EVENT_MASK) */ अणु
		cmd_fail = DRV_MSG_CODE_OEM_FAILURE;
		cmd_ok = DRV_MSG_CODE_OEM_OK;
	पूर्ण

	DP(BNX2X_MSG_MCP, "oem_event 0x%x\n", event);

	अगर (event & (DRV_STATUS_DCC_DISABLE_ENABLE_PF |
		     DRV_STATUS_OEM_DISABLE_ENABLE_PF)) अणु
		/* This is the only place besides the function initialization
		 * where the bp->flags can change so it is करोne without any
		 * locks
		 */
		अगर (bp->mf_config[BP_VN(bp)] & FUNC_MF_CFG_FUNC_DISABLED) अणु
			DP(BNX2X_MSG_MCP, "mf_cfg function disabled\n");
			bp->flags |= MF_FUNC_DIS;

			bnx2x_e1h_disable(bp);
		पूर्ण अन्यथा अणु
			DP(BNX2X_MSG_MCP, "mf_cfg function enabled\n");
			bp->flags &= ~MF_FUNC_DIS;

			bnx2x_e1h_enable(bp);
		पूर्ण
		event &= ~(DRV_STATUS_DCC_DISABLE_ENABLE_PF |
			   DRV_STATUS_OEM_DISABLE_ENABLE_PF);
	पूर्ण

	अगर (event & (DRV_STATUS_DCC_BANDWIDTH_ALLOCATION |
		     DRV_STATUS_OEM_BANDWIDTH_ALLOCATION)) अणु
		bnx2x_config_mf_bw(bp);
		event &= ~(DRV_STATUS_DCC_BANDWIDTH_ALLOCATION |
			   DRV_STATUS_OEM_BANDWIDTH_ALLOCATION);
	पूर्ण

	/* Report results to MCP */
	अगर (event)
		bnx2x_fw_command(bp, cmd_fail, 0);
	अन्यथा
		bnx2x_fw_command(bp, cmd_ok, 0);
पूर्ण

/* must be called under the spq lock */
अटल काष्ठा eth_spe *bnx2x_sp_get_next(काष्ठा bnx2x *bp)
अणु
	काष्ठा eth_spe *next_spe = bp->spq_prod_bd;

	अगर (bp->spq_prod_bd == bp->spq_last_bd) अणु
		bp->spq_prod_bd = bp->spq;
		bp->spq_prod_idx = 0;
		DP(BNX2X_MSG_SP, "end of spq\n");
	पूर्ण अन्यथा अणु
		bp->spq_prod_bd++;
		bp->spq_prod_idx++;
	पूर्ण
	वापस next_spe;
पूर्ण

/* must be called under the spq lock */
अटल व्योम bnx2x_sp_prod_update(काष्ठा bnx2x *bp)
अणु
	पूर्णांक func = BP_FUNC(bp);

	/*
	 * Make sure that BD data is updated beक्रमe writing the producer:
	 * BD data is written to the memory, the producer is पढ़ो from the
	 * memory, thus we need a full memory barrier to ensure the ordering.
	 */
	mb();

	REG_WR16_RELAXED(bp, BAR_XSTRORM_INTMEM + XSTORM_SPQ_PROD_OFFSET(func),
			 bp->spq_prod_idx);
पूर्ण

/**
 * bnx2x_is_contextless_ramrod - check अगर the current command ends on EQ
 *
 * @cmd:	command to check
 * @cmd_type:	command type
 */
अटल bool bnx2x_is_contextless_ramrod(पूर्णांक cmd, पूर्णांक cmd_type)
अणु
	अगर ((cmd_type == NONE_CONNECTION_TYPE) ||
	    (cmd == RAMROD_CMD_ID_ETH_FORWARD_SETUP) ||
	    (cmd == RAMROD_CMD_ID_ETH_CLASSIFICATION_RULES) ||
	    (cmd == RAMROD_CMD_ID_ETH_FILTER_RULES) ||
	    (cmd == RAMROD_CMD_ID_ETH_MULTICAST_RULES) ||
	    (cmd == RAMROD_CMD_ID_ETH_SET_MAC) ||
	    (cmd == RAMROD_CMD_ID_ETH_RSS_UPDATE))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

/**
 * bnx2x_sp_post - place a single command on an SP ring
 *
 * @bp:		driver handle
 * @command:	command to place (e.g. SETUP, FILTER_RULES, etc.)
 * @cid:	SW CID the command is related to
 * @data_hi:	command निजी data address (high 32 bits)
 * @data_lo:	command निजी data address (low 32 bits)
 * @cmd_type:	command type (e.g. NONE, ETH)
 *
 * SP data is handled as अगर it's always an address pair, thus data fields are
 * not swapped to little endian in upper functions. Instead this function swaps
 * data as अगर it's two u32 fields.
 */
पूर्णांक bnx2x_sp_post(काष्ठा bnx2x *bp, पूर्णांक command, पूर्णांक cid,
		  u32 data_hi, u32 data_lo, पूर्णांक cmd_type)
अणु
	काष्ठा eth_spe *spe;
	u16 type;
	bool common = bnx2x_is_contextless_ramrod(command, cmd_type);

#अगर_घोषित BNX2X_STOP_ON_ERROR
	अगर (unlikely(bp->panic)) अणु
		BNX2X_ERR("Can't post SP when there is panic\n");
		वापस -EIO;
	पूर्ण
#पूर्ण_अगर

	spin_lock_bh(&bp->spq_lock);

	अगर (common) अणु
		अगर (!atomic_पढ़ो(&bp->eq_spq_left)) अणु
			BNX2X_ERR("BUG! EQ ring full!\n");
			spin_unlock_bh(&bp->spq_lock);
			bnx2x_panic();
			वापस -EBUSY;
		पूर्ण
	पूर्ण अन्यथा अगर (!atomic_पढ़ो(&bp->cq_spq_left)) अणु
			BNX2X_ERR("BUG! SPQ ring full!\n");
			spin_unlock_bh(&bp->spq_lock);
			bnx2x_panic();
			वापस -EBUSY;
	पूर्ण

	spe = bnx2x_sp_get_next(bp);

	/* CID needs port number to be encoded पूर्णांक it */
	spe->hdr.conn_and_cmd_data =
			cpu_to_le32((command << SPE_HDR_CMD_ID_SHIFT) |
				    HW_CID(bp, cid));

	/* In some हालs, type may alपढ़ोy contain the func-id
	 * मुख्यly in SRIOV related use हालs, so we add it here only
	 * अगर it's not alपढ़ोy set.
	 */
	अगर (!(cmd_type & SPE_HDR_FUNCTION_ID)) अणु
		type = (cmd_type << SPE_HDR_CONN_TYPE_SHIFT) &
			SPE_HDR_CONN_TYPE;
		type |= ((BP_FUNC(bp) << SPE_HDR_FUNCTION_ID_SHIFT) &
			 SPE_HDR_FUNCTION_ID);
	पूर्ण अन्यथा अणु
		type = cmd_type;
	पूर्ण

	spe->hdr.type = cpu_to_le16(type);

	spe->data.update_data_addr.hi = cpu_to_le32(data_hi);
	spe->data.update_data_addr.lo = cpu_to_le32(data_lo);

	/*
	 * It's ok अगर the actual decrement is issued towards the memory
	 * somewhere between the spin_lock and spin_unlock. Thus no
	 * more explicit memory barrier is needed.
	 */
	अगर (common)
		atomic_dec(&bp->eq_spq_left);
	अन्यथा
		atomic_dec(&bp->cq_spq_left);

	DP(BNX2X_MSG_SP,
	   "SPQE[%x] (%x:%x)  (cmd, common?) (%d,%d)  hw_cid %x  data (%x:%x) type(0x%x) left (CQ, EQ) (%x,%x)\n",
	   bp->spq_prod_idx, (u32)U64_HI(bp->spq_mapping),
	   (u32)(U64_LO(bp->spq_mapping) +
	   (व्योम *)bp->spq_prod_bd - (व्योम *)bp->spq), command, common,
	   HW_CID(bp, cid), data_hi, data_lo, type,
	   atomic_पढ़ो(&bp->cq_spq_left), atomic_पढ़ो(&bp->eq_spq_left));

	bnx2x_sp_prod_update(bp);
	spin_unlock_bh(&bp->spq_lock);
	वापस 0;
पूर्ण

/* acquire split MCP access lock रेजिस्टर */
अटल पूर्णांक bnx2x_acquire_alr(काष्ठा bnx2x *bp)
अणु
	u32 j, val;
	पूर्णांक rc = 0;

	might_sleep();
	क्रम (j = 0; j < 1000; j++) अणु
		REG_WR(bp, MCP_REG_MCPR_ACCESS_LOCK, MCPR_ACCESS_LOCK_LOCK);
		val = REG_RD(bp, MCP_REG_MCPR_ACCESS_LOCK);
		अगर (val & MCPR_ACCESS_LOCK_LOCK)
			अवरोध;

		usleep_range(5000, 10000);
	पूर्ण
	अगर (!(val & MCPR_ACCESS_LOCK_LOCK)) अणु
		BNX2X_ERR("Cannot acquire MCP access lock register\n");
		rc = -EBUSY;
	पूर्ण

	वापस rc;
पूर्ण

/* release split MCP access lock रेजिस्टर */
अटल व्योम bnx2x_release_alr(काष्ठा bnx2x *bp)
अणु
	REG_WR(bp, MCP_REG_MCPR_ACCESS_LOCK, 0);
पूर्ण

#घोषणा BNX2X_DEF_SB_ATT_IDX	0x0001
#घोषणा BNX2X_DEF_SB_IDX	0x0002

अटल u16 bnx2x_update_dsb_idx(काष्ठा bnx2x *bp)
अणु
	काष्ठा host_sp_status_block *def_sb = bp->def_status_blk;
	u16 rc = 0;

	barrier(); /* status block is written to by the chip */
	अगर (bp->def_att_idx != def_sb->atten_status_block.attn_bits_index) अणु
		bp->def_att_idx = def_sb->atten_status_block.attn_bits_index;
		rc |= BNX2X_DEF_SB_ATT_IDX;
	पूर्ण

	अगर (bp->def_idx != def_sb->sp_sb.running_index) अणु
		bp->def_idx = def_sb->sp_sb.running_index;
		rc |= BNX2X_DEF_SB_IDX;
	पूर्ण

	/* Do not reorder: indices पढ़ोing should complete beक्रमe handling */
	barrier();
	वापस rc;
पूर्ण

/*
 * slow path service functions
 */

अटल व्योम bnx2x_attn_पूर्णांक_निश्चितed(काष्ठा bnx2x *bp, u32 निश्चितed)
अणु
	पूर्णांक port = BP_PORT(bp);
	u32 aeu_addr = port ? MISC_REG_AEU_MASK_ATTN_FUNC_1 :
			      MISC_REG_AEU_MASK_ATTN_FUNC_0;
	u32 nig_पूर्णांक_mask_addr = port ? NIG_REG_MASK_INTERRUPT_PORT1 :
				       NIG_REG_MASK_INTERRUPT_PORT0;
	u32 aeu_mask;
	u32 nig_mask = 0;
	u32 reg_addr;

	अगर (bp->attn_state & निश्चितed)
		BNX2X_ERR("IGU ERROR\n");

	bnx2x_acquire_hw_lock(bp, HW_LOCK_RESOURCE_PORT0_ATT_MASK + port);
	aeu_mask = REG_RD(bp, aeu_addr);

	DP(NETIF_MSG_HW, "aeu_mask %x  newly asserted %x\n",
	   aeu_mask, निश्चितed);
	aeu_mask &= ~(निश्चितed & 0x3ff);
	DP(NETIF_MSG_HW, "new mask %x\n", aeu_mask);

	REG_WR(bp, aeu_addr, aeu_mask);
	bnx2x_release_hw_lock(bp, HW_LOCK_RESOURCE_PORT0_ATT_MASK + port);

	DP(NETIF_MSG_HW, "attn_state %x\n", bp->attn_state);
	bp->attn_state |= निश्चितed;
	DP(NETIF_MSG_HW, "new state %x\n", bp->attn_state);

	अगर (निश्चितed & ATTN_HARD_WIRED_MASK) अणु
		अगर (निश्चितed & ATTN_NIG_FOR_FUNC) अणु

			bnx2x_acquire_phy_lock(bp);

			/* save nig पूर्णांकerrupt mask */
			nig_mask = REG_RD(bp, nig_पूर्णांक_mask_addr);

			/* If nig_mask is not set, no need to call the update
			 * function.
			 */
			अगर (nig_mask) अणु
				REG_WR(bp, nig_पूर्णांक_mask_addr, 0);

				bnx2x_link_attn(bp);
			पूर्ण

			/* handle unicore attn? */
		पूर्ण
		अगर (निश्चितed & ATTN_SW_TIMER_4_FUNC)
			DP(NETIF_MSG_HW, "ATTN_SW_TIMER_4_FUNC!\n");

		अगर (निश्चितed & GPIO_2_FUNC)
			DP(NETIF_MSG_HW, "GPIO_2_FUNC!\n");

		अगर (निश्चितed & GPIO_3_FUNC)
			DP(NETIF_MSG_HW, "GPIO_3_FUNC!\n");

		अगर (निश्चितed & GPIO_4_FUNC)
			DP(NETIF_MSG_HW, "GPIO_4_FUNC!\n");

		अगर (port == 0) अणु
			अगर (निश्चितed & ATTN_GENERAL_ATTN_1) अणु
				DP(NETIF_MSG_HW, "ATTN_GENERAL_ATTN_1!\n");
				REG_WR(bp, MISC_REG_AEU_GENERAL_ATTN_1, 0x0);
			पूर्ण
			अगर (निश्चितed & ATTN_GENERAL_ATTN_2) अणु
				DP(NETIF_MSG_HW, "ATTN_GENERAL_ATTN_2!\n");
				REG_WR(bp, MISC_REG_AEU_GENERAL_ATTN_2, 0x0);
			पूर्ण
			अगर (निश्चितed & ATTN_GENERAL_ATTN_3) अणु
				DP(NETIF_MSG_HW, "ATTN_GENERAL_ATTN_3!\n");
				REG_WR(bp, MISC_REG_AEU_GENERAL_ATTN_3, 0x0);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (निश्चितed & ATTN_GENERAL_ATTN_4) अणु
				DP(NETIF_MSG_HW, "ATTN_GENERAL_ATTN_4!\n");
				REG_WR(bp, MISC_REG_AEU_GENERAL_ATTN_4, 0x0);
			पूर्ण
			अगर (निश्चितed & ATTN_GENERAL_ATTN_5) अणु
				DP(NETIF_MSG_HW, "ATTN_GENERAL_ATTN_5!\n");
				REG_WR(bp, MISC_REG_AEU_GENERAL_ATTN_5, 0x0);
			पूर्ण
			अगर (निश्चितed & ATTN_GENERAL_ATTN_6) अणु
				DP(NETIF_MSG_HW, "ATTN_GENERAL_ATTN_6!\n");
				REG_WR(bp, MISC_REG_AEU_GENERAL_ATTN_6, 0x0);
			पूर्ण
		पूर्ण

	पूर्ण /* अगर hardwired */

	अगर (bp->common.पूर्णांक_block == INT_BLOCK_HC)
		reg_addr = (HC_REG_COMMAND_REG + port*32 +
			    COMMAND_REG_ATTN_BITS_SET);
	अन्यथा
		reg_addr = (BAR_IGU_INTMEM + IGU_CMD_ATTN_BIT_SET_UPPER*8);

	DP(NETIF_MSG_HW, "about to mask 0x%08x at %s addr 0x%x\n", निश्चितed,
	   (bp->common.पूर्णांक_block == INT_BLOCK_HC) ? "HC" : "IGU", reg_addr);
	REG_WR(bp, reg_addr, निश्चितed);

	/* now set back the mask */
	अगर (निश्चितed & ATTN_NIG_FOR_FUNC) अणु
		/* Verअगरy that IGU ack through BAR was written beक्रमe restoring
		 * NIG mask. This loop should निकास after 2-3 iterations max.
		 */
		अगर (bp->common.पूर्णांक_block != INT_BLOCK_HC) अणु
			u32 cnt = 0, igu_acked;
			करो अणु
				igu_acked = REG_RD(bp,
						   IGU_REG_ATTENTION_ACK_BITS);
			पूर्ण जबतक (((igu_acked & ATTN_NIG_FOR_FUNC) == 0) &&
				 (++cnt < MAX_IGU_ATTN_ACK_TO));
			अगर (!igu_acked)
				DP(NETIF_MSG_HW,
				   "Failed to verify IGU ack on time\n");
			barrier();
		पूर्ण
		REG_WR(bp, nig_पूर्णांक_mask_addr, nig_mask);
		bnx2x_release_phy_lock(bp);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_fan_failure(काष्ठा bnx2x *bp)
अणु
	पूर्णांक port = BP_PORT(bp);
	u32 ext_phy_config;
	/* mark the failure */
	ext_phy_config =
		SHMEM_RD(bp,
			 dev_info.port_hw_config[port].बाह्यal_phy_config);

	ext_phy_config &= ~PORT_HW_CFG_XGXS_EXT_PHY_TYPE_MASK;
	ext_phy_config |= PORT_HW_CFG_XGXS_EXT_PHY_TYPE_FAILURE;
	SHMEM_WR(bp, dev_info.port_hw_config[port].बाह्यal_phy_config,
		 ext_phy_config);

	/* log the failure */
	netdev_err(bp->dev, "Fan Failure on Network Controller has caused the driver to shutdown the card to prevent permanent damage.\n"
			    "Please contact OEM Support for assistance\n");

	/* Schedule device reset (unload)
	 * This is due to some boards consuming sufficient घातer when driver is
	 * up to overheat अगर fan fails.
	 */
	bnx2x_schedule_sp_rtnl(bp, BNX2X_SP_RTNL_FAN_FAILURE, 0);
पूर्ण

अटल व्योम bnx2x_attn_पूर्णांक_deनिश्चितed0(काष्ठा bnx2x *bp, u32 attn)
अणु
	पूर्णांक port = BP_PORT(bp);
	पूर्णांक reg_offset;
	u32 val;

	reg_offset = (port ? MISC_REG_AEU_ENABLE1_FUNC_1_OUT_0 :
			     MISC_REG_AEU_ENABLE1_FUNC_0_OUT_0);

	अगर (attn & AEU_INPUTS_ATTN_BITS_SPIO5) अणु

		val = REG_RD(bp, reg_offset);
		val &= ~AEU_INPUTS_ATTN_BITS_SPIO5;
		REG_WR(bp, reg_offset, val);

		BNX2X_ERR("SPIO5 hw attention\n");

		/* Fan failure attention */
		bnx2x_hw_reset_phy(&bp->link_params);
		bnx2x_fan_failure(bp);
	पूर्ण

	अगर ((attn & bp->link_vars.aeu_पूर्णांक_mask) && bp->port.pmf) अणु
		bnx2x_acquire_phy_lock(bp);
		bnx2x_handle_module_detect_पूर्णांक(&bp->link_params);
		bnx2x_release_phy_lock(bp);
	पूर्ण

	अगर (attn & HW_INTERRUPT_ASSERT_SET_0) अणु

		val = REG_RD(bp, reg_offset);
		val &= ~(attn & HW_INTERRUPT_ASSERT_SET_0);
		REG_WR(bp, reg_offset, val);

		BNX2X_ERR("FATAL HW block attention set0 0x%x\n",
			  (u32)(attn & HW_INTERRUPT_ASSERT_SET_0));
		bnx2x_panic();
	पूर्ण
पूर्ण

अटल व्योम bnx2x_attn_पूर्णांक_deनिश्चितed1(काष्ठा bnx2x *bp, u32 attn)
अणु
	u32 val;

	अगर (attn & AEU_INPUTS_ATTN_BITS_DOORBELLQ_HW_INTERRUPT) अणु

		val = REG_RD(bp, DORQ_REG_DORQ_INT_STS_CLR);
		BNX2X_ERR("DB hw attention 0x%x\n", val);
		/* DORQ discard attention */
		अगर (val & 0x2)
			BNX2X_ERR("FATAL error from DORQ\n");
	पूर्ण

	अगर (attn & HW_INTERRUPT_ASSERT_SET_1) अणु

		पूर्णांक port = BP_PORT(bp);
		पूर्णांक reg_offset;

		reg_offset = (port ? MISC_REG_AEU_ENABLE1_FUNC_1_OUT_1 :
				     MISC_REG_AEU_ENABLE1_FUNC_0_OUT_1);

		val = REG_RD(bp, reg_offset);
		val &= ~(attn & HW_INTERRUPT_ASSERT_SET_1);
		REG_WR(bp, reg_offset, val);

		BNX2X_ERR("FATAL HW block attention set1 0x%x\n",
			  (u32)(attn & HW_INTERRUPT_ASSERT_SET_1));
		bnx2x_panic();
	पूर्ण
पूर्ण

अटल व्योम bnx2x_attn_पूर्णांक_deनिश्चितed2(काष्ठा bnx2x *bp, u32 attn)
अणु
	u32 val;

	अगर (attn & AEU_INPUTS_ATTN_BITS_CFC_HW_INTERRUPT) अणु

		val = REG_RD(bp, CFC_REG_CFC_INT_STS_CLR);
		BNX2X_ERR("CFC hw attention 0x%x\n", val);
		/* CFC error attention */
		अगर (val & 0x2)
			BNX2X_ERR("FATAL error from CFC\n");
	पूर्ण

	अगर (attn & AEU_INPUTS_ATTN_BITS_PXP_HW_INTERRUPT) अणु
		val = REG_RD(bp, PXP_REG_PXP_INT_STS_CLR_0);
		BNX2X_ERR("PXP hw attention-0 0x%x\n", val);
		/* RQ_USDMDP_FIFO_OVERFLOW */
		अगर (val & 0x18000)
			BNX2X_ERR("FATAL error from PXP\n");

		अगर (!CHIP_IS_E1x(bp)) अणु
			val = REG_RD(bp, PXP_REG_PXP_INT_STS_CLR_1);
			BNX2X_ERR("PXP hw attention-1 0x%x\n", val);
		पूर्ण
	पूर्ण

	अगर (attn & HW_INTERRUPT_ASSERT_SET_2) अणु

		पूर्णांक port = BP_PORT(bp);
		पूर्णांक reg_offset;

		reg_offset = (port ? MISC_REG_AEU_ENABLE1_FUNC_1_OUT_2 :
				     MISC_REG_AEU_ENABLE1_FUNC_0_OUT_2);

		val = REG_RD(bp, reg_offset);
		val &= ~(attn & HW_INTERRUPT_ASSERT_SET_2);
		REG_WR(bp, reg_offset, val);

		BNX2X_ERR("FATAL HW block attention set2 0x%x\n",
			  (u32)(attn & HW_INTERRUPT_ASSERT_SET_2));
		bnx2x_panic();
	पूर्ण
पूर्ण

अटल व्योम bnx2x_attn_पूर्णांक_deनिश्चितed3(काष्ठा bnx2x *bp, u32 attn)
अणु
	u32 val;

	अगर (attn & EVEREST_GEN_ATTN_IN_USE_MASK) अणु

		अगर (attn & BNX2X_PMF_LINK_ASSERT) अणु
			पूर्णांक func = BP_FUNC(bp);

			REG_WR(bp, MISC_REG_AEU_GENERAL_ATTN_12 + func*4, 0);
			bnx2x_पढ़ो_mf_cfg(bp);
			bp->mf_config[BP_VN(bp)] = MF_CFG_RD(bp,
					func_mf_config[BP_ABS_FUNC(bp)].config);
			val = SHMEM_RD(bp,
				       func_mb[BP_FW_MB_IDX(bp)].drv_status);

			अगर (val & (DRV_STATUS_DCC_EVENT_MASK |
				   DRV_STATUS_OEM_EVENT_MASK))
				bnx2x_oem_event(bp,
					(val & (DRV_STATUS_DCC_EVENT_MASK |
						DRV_STATUS_OEM_EVENT_MASK)));

			अगर (val & DRV_STATUS_SET_MF_BW)
				bnx2x_set_mf_bw(bp);

			अगर (val & DRV_STATUS_DRV_INFO_REQ)
				bnx2x_handle_drv_info_req(bp);

			अगर (val & DRV_STATUS_VF_DISABLED)
				bnx2x_schedule_iov_task(bp,
							BNX2X_IOV_HANDLE_FLR);

			अगर ((bp->port.pmf == 0) && (val & DRV_STATUS_PMF))
				bnx2x_pmf_update(bp);

			अगर (bp->port.pmf &&
			    (val & DRV_STATUS_DCBX_NEGOTIATION_RESULTS) &&
				bp->dcbx_enabled > 0)
				/* start dcbx state machine */
				bnx2x_dcbx_set_params(bp,
					BNX2X_DCBX_STATE_NEG_RECEIVED);
			अगर (val & DRV_STATUS_AFEX_EVENT_MASK)
				bnx2x_handle_afex_cmd(bp,
					val & DRV_STATUS_AFEX_EVENT_MASK);
			अगर (val & DRV_STATUS_EEE_NEGOTIATION_RESULTS)
				bnx2x_handle_eee_event(bp);

			अगर (val & DRV_STATUS_OEM_UPDATE_SVID)
				bnx2x_schedule_sp_rtnl(bp,
					BNX2X_SP_RTNL_UPDATE_SVID, 0);

			अगर (bp->link_vars.periodic_flags &
			    PERIODIC_FLAGS_LINK_EVENT) अणु
				/*  sync with link */
				bnx2x_acquire_phy_lock(bp);
				bp->link_vars.periodic_flags &=
					~PERIODIC_FLAGS_LINK_EVENT;
				bnx2x_release_phy_lock(bp);
				अगर (IS_MF(bp))
					bnx2x_link_sync_notअगरy(bp);
				bnx2x_link_report(bp);
			पूर्ण
			/* Always call it here: bnx2x_link_report() will
			 * prevent the link indication duplication.
			 */
			bnx2x__link_status_update(bp);
		पूर्ण अन्यथा अगर (attn & BNX2X_MC_ASSERT_BITS) अणु

			BNX2X_ERR("MC assert!\n");
			bnx2x_mc_निश्चित(bp);
			REG_WR(bp, MISC_REG_AEU_GENERAL_ATTN_10, 0);
			REG_WR(bp, MISC_REG_AEU_GENERAL_ATTN_9, 0);
			REG_WR(bp, MISC_REG_AEU_GENERAL_ATTN_8, 0);
			REG_WR(bp, MISC_REG_AEU_GENERAL_ATTN_7, 0);
			bnx2x_panic();

		पूर्ण अन्यथा अगर (attn & BNX2X_MCP_ASSERT) अणु

			BNX2X_ERR("MCP assert!\n");
			REG_WR(bp, MISC_REG_AEU_GENERAL_ATTN_11, 0);
			bnx2x_fw_dump(bp);

		पूर्ण अन्यथा
			BNX2X_ERR("Unknown HW assert! (attn 0x%x)\n", attn);
	पूर्ण

	अगर (attn & EVEREST_LATCHED_ATTN_IN_USE_MASK) अणु
		BNX2X_ERR("LATCHED attention 0x%08x (masked)\n", attn);
		अगर (attn & BNX2X_GRC_TIMEOUT) अणु
			val = CHIP_IS_E1(bp) ? 0 :
					REG_RD(bp, MISC_REG_GRC_TIMEOUT_ATTN);
			BNX2X_ERR("GRC time-out 0x%08x\n", val);
		पूर्ण
		अगर (attn & BNX2X_GRC_RSV) अणु
			val = CHIP_IS_E1(bp) ? 0 :
					REG_RD(bp, MISC_REG_GRC_RSV_ATTN);
			BNX2X_ERR("GRC reserved 0x%08x\n", val);
		पूर्ण
		REG_WR(bp, MISC_REG_AEU_CLR_LATCH_SIGNAL, 0x7ff);
	पूर्ण
पूर्ण

/*
 * Bits map:
 * 0-7   - Engine0 load counter.
 * 8-15  - Engine1 load counter.
 * 16    - Engine0 RESET_IN_PROGRESS bit.
 * 17    - Engine1 RESET_IN_PROGRESS bit.
 * 18    - Engine0 ONE_IS_LOADED. Set when there is at least one active function
 *         on the engine
 * 19    - Engine1 ONE_IS_LOADED.
 * 20    - Chip reset flow bit. When set none-leader must रुको क्रम both engines
 *         leader to complete (check क्रम both RESET_IN_PROGRESS bits and not क्रम
 *         just the one beदीर्घing to its engine).
 *
 */
#घोषणा BNX2X_RECOVERY_GLOB_REG		MISC_REG_GENERIC_POR_1

#घोषणा BNX2X_PATH0_LOAD_CNT_MASK	0x000000ff
#घोषणा BNX2X_PATH0_LOAD_CNT_SHIFT	0
#घोषणा BNX2X_PATH1_LOAD_CNT_MASK	0x0000ff00
#घोषणा BNX2X_PATH1_LOAD_CNT_SHIFT	8
#घोषणा BNX2X_PATH0_RST_IN_PROG_BIT	0x00010000
#घोषणा BNX2X_PATH1_RST_IN_PROG_BIT	0x00020000
#घोषणा BNX2X_GLOBAL_RESET_BIT		0x00040000

/*
 * Set the GLOBAL_RESET bit.
 *
 * Should be run under rtnl lock
 */
व्योम bnx2x_set_reset_global(काष्ठा bnx2x *bp)
अणु
	u32 val;
	bnx2x_acquire_hw_lock(bp, HW_LOCK_RESOURCE_RECOVERY_REG);
	val = REG_RD(bp, BNX2X_RECOVERY_GLOB_REG);
	REG_WR(bp, BNX2X_RECOVERY_GLOB_REG, val | BNX2X_GLOBAL_RESET_BIT);
	bnx2x_release_hw_lock(bp, HW_LOCK_RESOURCE_RECOVERY_REG);
पूर्ण

/*
 * Clear the GLOBAL_RESET bit.
 *
 * Should be run under rtnl lock
 */
अटल व्योम bnx2x_clear_reset_global(काष्ठा bnx2x *bp)
अणु
	u32 val;
	bnx2x_acquire_hw_lock(bp, HW_LOCK_RESOURCE_RECOVERY_REG);
	val = REG_RD(bp, BNX2X_RECOVERY_GLOB_REG);
	REG_WR(bp, BNX2X_RECOVERY_GLOB_REG, val & (~BNX2X_GLOBAL_RESET_BIT));
	bnx2x_release_hw_lock(bp, HW_LOCK_RESOURCE_RECOVERY_REG);
पूर्ण

/*
 * Checks the GLOBAL_RESET bit.
 *
 * should be run under rtnl lock
 */
अटल bool bnx2x_reset_is_global(काष्ठा bnx2x *bp)
अणु
	u32 val = REG_RD(bp, BNX2X_RECOVERY_GLOB_REG);

	DP(NETIF_MSG_HW, "GEN_REG_VAL=0x%08x\n", val);
	वापस (val & BNX2X_GLOBAL_RESET_BIT) ? true : false;
पूर्ण

/*
 * Clear RESET_IN_PROGRESS bit क्रम the current engine.
 *
 * Should be run under rtnl lock
 */
अटल व्योम bnx2x_set_reset_करोne(काष्ठा bnx2x *bp)
अणु
	u32 val;
	u32 bit = BP_PATH(bp) ?
		BNX2X_PATH1_RST_IN_PROG_BIT : BNX2X_PATH0_RST_IN_PROG_BIT;
	bnx2x_acquire_hw_lock(bp, HW_LOCK_RESOURCE_RECOVERY_REG);
	val = REG_RD(bp, BNX2X_RECOVERY_GLOB_REG);

	/* Clear the bit */
	val &= ~bit;
	REG_WR(bp, BNX2X_RECOVERY_GLOB_REG, val);

	bnx2x_release_hw_lock(bp, HW_LOCK_RESOURCE_RECOVERY_REG);
पूर्ण

/*
 * Set RESET_IN_PROGRESS क्रम the current engine.
 *
 * should be run under rtnl lock
 */
व्योम bnx2x_set_reset_in_progress(काष्ठा bnx2x *bp)
अणु
	u32 val;
	u32 bit = BP_PATH(bp) ?
		BNX2X_PATH1_RST_IN_PROG_BIT : BNX2X_PATH0_RST_IN_PROG_BIT;
	bnx2x_acquire_hw_lock(bp, HW_LOCK_RESOURCE_RECOVERY_REG);
	val = REG_RD(bp, BNX2X_RECOVERY_GLOB_REG);

	/* Set the bit */
	val |= bit;
	REG_WR(bp, BNX2X_RECOVERY_GLOB_REG, val);
	bnx2x_release_hw_lock(bp, HW_LOCK_RESOURCE_RECOVERY_REG);
पूर्ण

/*
 * Checks the RESET_IN_PROGRESS bit क्रम the given engine.
 * should be run under rtnl lock
 */
bool bnx2x_reset_is_करोne(काष्ठा bnx2x *bp, पूर्णांक engine)
अणु
	u32 val = REG_RD(bp, BNX2X_RECOVERY_GLOB_REG);
	u32 bit = engine ?
		BNX2X_PATH1_RST_IN_PROG_BIT : BNX2X_PATH0_RST_IN_PROG_BIT;

	/* वापस false अगर bit is set */
	वापस (val & bit) ? false : true;
पूर्ण

/*
 * set pf load क्रम the current pf.
 *
 * should be run under rtnl lock
 */
व्योम bnx2x_set_pf_load(काष्ठा bnx2x *bp)
अणु
	u32 val1, val;
	u32 mask = BP_PATH(bp) ? BNX2X_PATH1_LOAD_CNT_MASK :
			     BNX2X_PATH0_LOAD_CNT_MASK;
	u32 shअगरt = BP_PATH(bp) ? BNX2X_PATH1_LOAD_CNT_SHIFT :
			     BNX2X_PATH0_LOAD_CNT_SHIFT;

	bnx2x_acquire_hw_lock(bp, HW_LOCK_RESOURCE_RECOVERY_REG);
	val = REG_RD(bp, BNX2X_RECOVERY_GLOB_REG);

	DP(NETIF_MSG_IFUP, "Old GEN_REG_VAL=0x%08x\n", val);

	/* get the current counter value */
	val1 = (val & mask) >> shअगरt;

	/* set bit of that PF */
	val1 |= (1 << bp->pf_num);

	/* clear the old value */
	val &= ~mask;

	/* set the new one */
	val |= ((val1 << shअगरt) & mask);

	REG_WR(bp, BNX2X_RECOVERY_GLOB_REG, val);
	bnx2x_release_hw_lock(bp, HW_LOCK_RESOURCE_RECOVERY_REG);
पूर्ण

/**
 * bnx2x_clear_pf_load - clear pf load mark
 *
 * @bp:		driver handle
 *
 * Should be run under rtnl lock.
 * Decrements the load counter क्रम the current engine. Returns
 * whether other functions are still loaded
 */
bool bnx2x_clear_pf_load(काष्ठा bnx2x *bp)
अणु
	u32 val1, val;
	u32 mask = BP_PATH(bp) ? BNX2X_PATH1_LOAD_CNT_MASK :
			     BNX2X_PATH0_LOAD_CNT_MASK;
	u32 shअगरt = BP_PATH(bp) ? BNX2X_PATH1_LOAD_CNT_SHIFT :
			     BNX2X_PATH0_LOAD_CNT_SHIFT;

	bnx2x_acquire_hw_lock(bp, HW_LOCK_RESOURCE_RECOVERY_REG);
	val = REG_RD(bp, BNX2X_RECOVERY_GLOB_REG);
	DP(NETIF_MSG_IFDOWN, "Old GEN_REG_VAL=0x%08x\n", val);

	/* get the current counter value */
	val1 = (val & mask) >> shअगरt;

	/* clear bit of that PF */
	val1 &= ~(1 << bp->pf_num);

	/* clear the old value */
	val &= ~mask;

	/* set the new one */
	val |= ((val1 << shअगरt) & mask);

	REG_WR(bp, BNX2X_RECOVERY_GLOB_REG, val);
	bnx2x_release_hw_lock(bp, HW_LOCK_RESOURCE_RECOVERY_REG);
	वापस val1 != 0;
पूर्ण

/*
 * Read the load status क्रम the current engine.
 *
 * should be run under rtnl lock
 */
अटल bool bnx2x_get_load_status(काष्ठा bnx2x *bp, पूर्णांक engine)
अणु
	u32 mask = (engine ? BNX2X_PATH1_LOAD_CNT_MASK :
			     BNX2X_PATH0_LOAD_CNT_MASK);
	u32 shअगरt = (engine ? BNX2X_PATH1_LOAD_CNT_SHIFT :
			     BNX2X_PATH0_LOAD_CNT_SHIFT);
	u32 val = REG_RD(bp, BNX2X_RECOVERY_GLOB_REG);

	DP(NETIF_MSG_HW | NETIF_MSG_IFUP, "GLOB_REG=0x%08x\n", val);

	val = (val & mask) >> shअगरt;

	DP(NETIF_MSG_HW | NETIF_MSG_IFUP, "load mask for engine %d = 0x%x\n",
	   engine, val);

	वापस val != 0;
पूर्ण

अटल व्योम _prपूर्णांक_parity(काष्ठा bnx2x *bp, u32 reg)
अणु
	pr_cont(" [0x%08x] ", REG_RD(bp, reg));
पूर्ण

अटल व्योम _prपूर्णांक_next_block(पूर्णांक idx, स्थिर अक्षर *blk)
अणु
	pr_cont("%s%s", idx ? ", " : "", blk);
पूर्ण

अटल bool bnx2x_check_blocks_with_parity0(काष्ठा bnx2x *bp, u32 sig,
					    पूर्णांक *par_num, bool prपूर्णांक)
अणु
	u32 cur_bit;
	bool res;
	पूर्णांक i;

	res = false;

	क्रम (i = 0; sig; i++) अणु
		cur_bit = (0x1UL << i);
		अगर (sig & cur_bit) अणु
			res |= true; /* Each bit is real error! */

			अगर (prपूर्णांक) अणु
				चयन (cur_bit) अणु
				हाल AEU_INPUTS_ATTN_BITS_BRB_PARITY_ERROR:
					_prपूर्णांक_next_block((*par_num)++, "BRB");
					_prपूर्णांक_parity(bp,
						      BRB1_REG_BRB1_PRTY_STS);
					अवरोध;
				हाल AEU_INPUTS_ATTN_BITS_PARSER_PARITY_ERROR:
					_prपूर्णांक_next_block((*par_num)++,
							  "PARSER");
					_prपूर्णांक_parity(bp, PRS_REG_PRS_PRTY_STS);
					अवरोध;
				हाल AEU_INPUTS_ATTN_BITS_TSDM_PARITY_ERROR:
					_prपूर्णांक_next_block((*par_num)++, "TSDM");
					_prपूर्णांक_parity(bp,
						      TSDM_REG_TSDM_PRTY_STS);
					अवरोध;
				हाल AEU_INPUTS_ATTN_BITS_SEARCHER_PARITY_ERROR:
					_prपूर्णांक_next_block((*par_num)++,
							  "SEARCHER");
					_prपूर्णांक_parity(bp, SRC_REG_SRC_PRTY_STS);
					अवरोध;
				हाल AEU_INPUTS_ATTN_BITS_TCM_PARITY_ERROR:
					_prपूर्णांक_next_block((*par_num)++, "TCM");
					_prपूर्णांक_parity(bp, TCM_REG_TCM_PRTY_STS);
					अवरोध;
				हाल AEU_INPUTS_ATTN_BITS_TSEMI_PARITY_ERROR:
					_prपूर्णांक_next_block((*par_num)++,
							  "TSEMI");
					_prपूर्णांक_parity(bp,
						      TSEM_REG_TSEM_PRTY_STS_0);
					_prपूर्णांक_parity(bp,
						      TSEM_REG_TSEM_PRTY_STS_1);
					अवरोध;
				हाल AEU_INPUTS_ATTN_BITS_PBCLIENT_PARITY_ERROR:
					_prपूर्णांक_next_block((*par_num)++, "XPB");
					_prपूर्णांक_parity(bp, GRCBASE_XPB +
							  PB_REG_PB_PRTY_STS);
					अवरोध;
				पूर्ण
			पूर्ण

			/* Clear the bit */
			sig &= ~cur_bit;
		पूर्ण
	पूर्ण

	वापस res;
पूर्ण

अटल bool bnx2x_check_blocks_with_parity1(काष्ठा bnx2x *bp, u32 sig,
					    पूर्णांक *par_num, bool *global,
					    bool prपूर्णांक)
अणु
	u32 cur_bit;
	bool res;
	पूर्णांक i;

	res = false;

	क्रम (i = 0; sig; i++) अणु
		cur_bit = (0x1UL << i);
		अगर (sig & cur_bit) अणु
			res |= true; /* Each bit is real error! */
			चयन (cur_bit) अणु
			हाल AEU_INPUTS_ATTN_BITS_PBF_PARITY_ERROR:
				अगर (prपूर्णांक) अणु
					_prपूर्णांक_next_block((*par_num)++, "PBF");
					_prपूर्णांक_parity(bp, PBF_REG_PBF_PRTY_STS);
				पूर्ण
				अवरोध;
			हाल AEU_INPUTS_ATTN_BITS_QM_PARITY_ERROR:
				अगर (prपूर्णांक) अणु
					_prपूर्णांक_next_block((*par_num)++, "QM");
					_prपूर्णांक_parity(bp, QM_REG_QM_PRTY_STS);
				पूर्ण
				अवरोध;
			हाल AEU_INPUTS_ATTN_BITS_TIMERS_PARITY_ERROR:
				अगर (prपूर्णांक) अणु
					_prपूर्णांक_next_block((*par_num)++, "TM");
					_prपूर्णांक_parity(bp, TM_REG_TM_PRTY_STS);
				पूर्ण
				अवरोध;
			हाल AEU_INPUTS_ATTN_BITS_XSDM_PARITY_ERROR:
				अगर (prपूर्णांक) अणु
					_prपूर्णांक_next_block((*par_num)++, "XSDM");
					_prपूर्णांक_parity(bp,
						      XSDM_REG_XSDM_PRTY_STS);
				पूर्ण
				अवरोध;
			हाल AEU_INPUTS_ATTN_BITS_XCM_PARITY_ERROR:
				अगर (prपूर्णांक) अणु
					_prपूर्णांक_next_block((*par_num)++, "XCM");
					_prपूर्णांक_parity(bp, XCM_REG_XCM_PRTY_STS);
				पूर्ण
				अवरोध;
			हाल AEU_INPUTS_ATTN_BITS_XSEMI_PARITY_ERROR:
				अगर (prपूर्णांक) अणु
					_prपूर्णांक_next_block((*par_num)++,
							  "XSEMI");
					_prपूर्णांक_parity(bp,
						      XSEM_REG_XSEM_PRTY_STS_0);
					_prपूर्णांक_parity(bp,
						      XSEM_REG_XSEM_PRTY_STS_1);
				पूर्ण
				अवरोध;
			हाल AEU_INPUTS_ATTN_BITS_DOORBELLQ_PARITY_ERROR:
				अगर (prपूर्णांक) अणु
					_prपूर्णांक_next_block((*par_num)++,
							  "DOORBELLQ");
					_prपूर्णांक_parity(bp,
						      DORQ_REG_DORQ_PRTY_STS);
				पूर्ण
				अवरोध;
			हाल AEU_INPUTS_ATTN_BITS_NIG_PARITY_ERROR:
				अगर (prपूर्णांक) अणु
					_prपूर्णांक_next_block((*par_num)++, "NIG");
					अगर (CHIP_IS_E1x(bp)) अणु
						_prपूर्णांक_parity(bp,
							NIG_REG_NIG_PRTY_STS);
					पूर्ण अन्यथा अणु
						_prपूर्णांक_parity(bp,
							NIG_REG_NIG_PRTY_STS_0);
						_prपूर्णांक_parity(bp,
							NIG_REG_NIG_PRTY_STS_1);
					पूर्ण
				पूर्ण
				अवरोध;
			हाल AEU_INPUTS_ATTN_BITS_VAUX_PCI_CORE_PARITY_ERROR:
				अगर (prपूर्णांक)
					_prपूर्णांक_next_block((*par_num)++,
							  "VAUX PCI CORE");
				*global = true;
				अवरोध;
			हाल AEU_INPUTS_ATTN_BITS_DEBUG_PARITY_ERROR:
				अगर (prपूर्णांक) अणु
					_prपूर्णांक_next_block((*par_num)++,
							  "DEBUG");
					_prपूर्णांक_parity(bp, DBG_REG_DBG_PRTY_STS);
				पूर्ण
				अवरोध;
			हाल AEU_INPUTS_ATTN_BITS_USDM_PARITY_ERROR:
				अगर (prपूर्णांक) अणु
					_prपूर्णांक_next_block((*par_num)++, "USDM");
					_prपूर्णांक_parity(bp,
						      USDM_REG_USDM_PRTY_STS);
				पूर्ण
				अवरोध;
			हाल AEU_INPUTS_ATTN_BITS_UCM_PARITY_ERROR:
				अगर (prपूर्णांक) अणु
					_prपूर्णांक_next_block((*par_num)++, "UCM");
					_prपूर्णांक_parity(bp, UCM_REG_UCM_PRTY_STS);
				पूर्ण
				अवरोध;
			हाल AEU_INPUTS_ATTN_BITS_USEMI_PARITY_ERROR:
				अगर (prपूर्णांक) अणु
					_prपूर्णांक_next_block((*par_num)++,
							  "USEMI");
					_prपूर्णांक_parity(bp,
						      USEM_REG_USEM_PRTY_STS_0);
					_prपूर्णांक_parity(bp,
						      USEM_REG_USEM_PRTY_STS_1);
				पूर्ण
				अवरोध;
			हाल AEU_INPUTS_ATTN_BITS_UPB_PARITY_ERROR:
				अगर (prपूर्णांक) अणु
					_prपूर्णांक_next_block((*par_num)++, "UPB");
					_prपूर्णांक_parity(bp, GRCBASE_UPB +
							  PB_REG_PB_PRTY_STS);
				पूर्ण
				अवरोध;
			हाल AEU_INPUTS_ATTN_BITS_CSDM_PARITY_ERROR:
				अगर (prपूर्णांक) अणु
					_prपूर्णांक_next_block((*par_num)++, "CSDM");
					_prपूर्णांक_parity(bp,
						      CSDM_REG_CSDM_PRTY_STS);
				पूर्ण
				अवरोध;
			हाल AEU_INPUTS_ATTN_BITS_CCM_PARITY_ERROR:
				अगर (prपूर्णांक) अणु
					_prपूर्णांक_next_block((*par_num)++, "CCM");
					_prपूर्णांक_parity(bp, CCM_REG_CCM_PRTY_STS);
				पूर्ण
				अवरोध;
			पूर्ण

			/* Clear the bit */
			sig &= ~cur_bit;
		पूर्ण
	पूर्ण

	वापस res;
पूर्ण

अटल bool bnx2x_check_blocks_with_parity2(काष्ठा bnx2x *bp, u32 sig,
					    पूर्णांक *par_num, bool prपूर्णांक)
अणु
	u32 cur_bit;
	bool res;
	पूर्णांक i;

	res = false;

	क्रम (i = 0; sig; i++) अणु
		cur_bit = (0x1UL << i);
		अगर (sig & cur_bit) अणु
			res = true; /* Each bit is real error! */
			अगर (prपूर्णांक) अणु
				चयन (cur_bit) अणु
				हाल AEU_INPUTS_ATTN_BITS_CSEMI_PARITY_ERROR:
					_prपूर्णांक_next_block((*par_num)++,
							  "CSEMI");
					_prपूर्णांक_parity(bp,
						      CSEM_REG_CSEM_PRTY_STS_0);
					_prपूर्णांक_parity(bp,
						      CSEM_REG_CSEM_PRTY_STS_1);
					अवरोध;
				हाल AEU_INPUTS_ATTN_BITS_PXP_PARITY_ERROR:
					_prपूर्णांक_next_block((*par_num)++, "PXP");
					_prपूर्णांक_parity(bp, PXP_REG_PXP_PRTY_STS);
					_prपूर्णांक_parity(bp,
						      PXP2_REG_PXP2_PRTY_STS_0);
					_prपूर्णांक_parity(bp,
						      PXP2_REG_PXP2_PRTY_STS_1);
					अवरोध;
				हाल AEU_IN_ATTN_BITS_PXPPCICLOCKCLIENT_PARITY_ERROR:
					_prपूर्णांक_next_block((*par_num)++,
							  "PXPPCICLOCKCLIENT");
					अवरोध;
				हाल AEU_INPUTS_ATTN_BITS_CFC_PARITY_ERROR:
					_prपूर्णांक_next_block((*par_num)++, "CFC");
					_prपूर्णांक_parity(bp,
						      CFC_REG_CFC_PRTY_STS);
					अवरोध;
				हाल AEU_INPUTS_ATTN_BITS_CDU_PARITY_ERROR:
					_prपूर्णांक_next_block((*par_num)++, "CDU");
					_prपूर्णांक_parity(bp, CDU_REG_CDU_PRTY_STS);
					अवरोध;
				हाल AEU_INPUTS_ATTN_BITS_DMAE_PARITY_ERROR:
					_prपूर्णांक_next_block((*par_num)++, "DMAE");
					_prपूर्णांक_parity(bp,
						      DMAE_REG_DMAE_PRTY_STS);
					अवरोध;
				हाल AEU_INPUTS_ATTN_BITS_IGU_PARITY_ERROR:
					_prपूर्णांक_next_block((*par_num)++, "IGU");
					अगर (CHIP_IS_E1x(bp))
						_prपूर्णांक_parity(bp,
							HC_REG_HC_PRTY_STS);
					अन्यथा
						_prपूर्णांक_parity(bp,
							IGU_REG_IGU_PRTY_STS);
					अवरोध;
				हाल AEU_INPUTS_ATTN_BITS_MISC_PARITY_ERROR:
					_prपूर्णांक_next_block((*par_num)++, "MISC");
					_prपूर्णांक_parity(bp,
						      MISC_REG_MISC_PRTY_STS);
					अवरोध;
				पूर्ण
			पूर्ण

			/* Clear the bit */
			sig &= ~cur_bit;
		पूर्ण
	पूर्ण

	वापस res;
पूर्ण

अटल bool bnx2x_check_blocks_with_parity3(काष्ठा bnx2x *bp, u32 sig,
					    पूर्णांक *par_num, bool *global,
					    bool prपूर्णांक)
अणु
	bool res = false;
	u32 cur_bit;
	पूर्णांक i;

	क्रम (i = 0; sig; i++) अणु
		cur_bit = (0x1UL << i);
		अगर (sig & cur_bit) अणु
			चयन (cur_bit) अणु
			हाल AEU_INPUTS_ATTN_BITS_MCP_LATCHED_ROM_PARITY:
				अगर (prपूर्णांक)
					_prपूर्णांक_next_block((*par_num)++,
							  "MCP ROM");
				*global = true;
				res = true;
				अवरोध;
			हाल AEU_INPUTS_ATTN_BITS_MCP_LATCHED_UMP_RX_PARITY:
				अगर (prपूर्णांक)
					_prपूर्णांक_next_block((*par_num)++,
							  "MCP UMP RX");
				*global = true;
				res = true;
				अवरोध;
			हाल AEU_INPUTS_ATTN_BITS_MCP_LATCHED_UMP_TX_PARITY:
				अगर (prपूर्णांक)
					_prपूर्णांक_next_block((*par_num)++,
							  "MCP UMP TX");
				*global = true;
				res = true;
				अवरोध;
			हाल AEU_INPUTS_ATTN_BITS_MCP_LATCHED_SCPAD_PARITY:
				(*par_num)++;
				/* clear latched SCPAD PATIRY from MCP */
				REG_WR(bp, MISC_REG_AEU_CLR_LATCH_SIGNAL,
				       1UL << 10);
				अवरोध;
			पूर्ण

			/* Clear the bit */
			sig &= ~cur_bit;
		पूर्ण
	पूर्ण

	वापस res;
पूर्ण

अटल bool bnx2x_check_blocks_with_parity4(काष्ठा bnx2x *bp, u32 sig,
					    पूर्णांक *par_num, bool prपूर्णांक)
अणु
	u32 cur_bit;
	bool res;
	पूर्णांक i;

	res = false;

	क्रम (i = 0; sig; i++) अणु
		cur_bit = (0x1UL << i);
		अगर (sig & cur_bit) अणु
			res = true; /* Each bit is real error! */
			अगर (prपूर्णांक) अणु
				चयन (cur_bit) अणु
				हाल AEU_INPUTS_ATTN_BITS_PGLUE_PARITY_ERROR:
					_prपूर्णांक_next_block((*par_num)++,
							  "PGLUE_B");
					_prपूर्णांक_parity(bp,
						      PGLUE_B_REG_PGLUE_B_PRTY_STS);
					अवरोध;
				हाल AEU_INPUTS_ATTN_BITS_ATC_PARITY_ERROR:
					_prपूर्णांक_next_block((*par_num)++, "ATC");
					_prपूर्णांक_parity(bp,
						      ATC_REG_ATC_PRTY_STS);
					अवरोध;
				पूर्ण
			पूर्ण
			/* Clear the bit */
			sig &= ~cur_bit;
		पूर्ण
	पूर्ण

	वापस res;
पूर्ण

अटल bool bnx2x_parity_attn(काष्ठा bnx2x *bp, bool *global, bool prपूर्णांक,
			      u32 *sig)
अणु
	bool res = false;

	अगर ((sig[0] & HW_PRTY_ASSERT_SET_0) ||
	    (sig[1] & HW_PRTY_ASSERT_SET_1) ||
	    (sig[2] & HW_PRTY_ASSERT_SET_2) ||
	    (sig[3] & HW_PRTY_ASSERT_SET_3) ||
	    (sig[4] & HW_PRTY_ASSERT_SET_4)) अणु
		पूर्णांक par_num = 0;

		DP(NETIF_MSG_HW, "Was parity error: HW block parity attention:\n"
				 "[0]:0x%08x [1]:0x%08x [2]:0x%08x [3]:0x%08x [4]:0x%08x\n",
			  sig[0] & HW_PRTY_ASSERT_SET_0,
			  sig[1] & HW_PRTY_ASSERT_SET_1,
			  sig[2] & HW_PRTY_ASSERT_SET_2,
			  sig[3] & HW_PRTY_ASSERT_SET_3,
			  sig[4] & HW_PRTY_ASSERT_SET_4);
		अगर (prपूर्णांक) अणु
			अगर (((sig[0] & HW_PRTY_ASSERT_SET_0) ||
			     (sig[1] & HW_PRTY_ASSERT_SET_1) ||
			     (sig[2] & HW_PRTY_ASSERT_SET_2) ||
			     (sig[4] & HW_PRTY_ASSERT_SET_4)) ||
			     (sig[3] & HW_PRTY_ASSERT_SET_3_WITHOUT_SCPAD)) अणु
				netdev_err(bp->dev,
					   "Parity errors detected in blocks: ");
			पूर्ण अन्यथा अणु
				prपूर्णांक = false;
			पूर्ण
		पूर्ण
		res |= bnx2x_check_blocks_with_parity0(bp,
			sig[0] & HW_PRTY_ASSERT_SET_0, &par_num, prपूर्णांक);
		res |= bnx2x_check_blocks_with_parity1(bp,
			sig[1] & HW_PRTY_ASSERT_SET_1, &par_num, global, prपूर्णांक);
		res |= bnx2x_check_blocks_with_parity2(bp,
			sig[2] & HW_PRTY_ASSERT_SET_2, &par_num, prपूर्णांक);
		res |= bnx2x_check_blocks_with_parity3(bp,
			sig[3] & HW_PRTY_ASSERT_SET_3, &par_num, global, prपूर्णांक);
		res |= bnx2x_check_blocks_with_parity4(bp,
			sig[4] & HW_PRTY_ASSERT_SET_4, &par_num, prपूर्णांक);

		अगर (prपूर्णांक)
			pr_cont("\n");
	पूर्ण

	वापस res;
पूर्ण

/**
 * bnx2x_chk_parity_attn - checks क्रम parity attentions.
 *
 * @bp:		driver handle
 * @global:	true अगर there was a global attention
 * @prपूर्णांक:	show parity attention in syslog
 */
bool bnx2x_chk_parity_attn(काष्ठा bnx2x *bp, bool *global, bool prपूर्णांक)
अणु
	काष्ठा attn_route attn = अणु अणु0पूर्ण पूर्ण;
	पूर्णांक port = BP_PORT(bp);

	attn.sig[0] = REG_RD(bp,
		MISC_REG_AEU_AFTER_INVERT_1_FUNC_0 +
			     port*4);
	attn.sig[1] = REG_RD(bp,
		MISC_REG_AEU_AFTER_INVERT_2_FUNC_0 +
			     port*4);
	attn.sig[2] = REG_RD(bp,
		MISC_REG_AEU_AFTER_INVERT_3_FUNC_0 +
			     port*4);
	attn.sig[3] = REG_RD(bp,
		MISC_REG_AEU_AFTER_INVERT_4_FUNC_0 +
			     port*4);
	/* Since MCP attentions can't be disabled inside the block, we need to
	 * पढ़ो AEU रेजिस्टरs to see whether they're currently disabled
	 */
	attn.sig[3] &= ((REG_RD(bp,
				!port ? MISC_REG_AEU_ENABLE4_FUNC_0_OUT_0
				      : MISC_REG_AEU_ENABLE4_FUNC_1_OUT_0) &
			 MISC_AEU_ENABLE_MCP_PRTY_BITS) |
			~MISC_AEU_ENABLE_MCP_PRTY_BITS);

	अगर (!CHIP_IS_E1x(bp))
		attn.sig[4] = REG_RD(bp,
			MISC_REG_AEU_AFTER_INVERT_5_FUNC_0 +
				     port*4);

	वापस bnx2x_parity_attn(bp, global, prपूर्णांक, attn.sig);
पूर्ण

अटल व्योम bnx2x_attn_पूर्णांक_deनिश्चितed4(काष्ठा bnx2x *bp, u32 attn)
अणु
	u32 val;
	अगर (attn & AEU_INPUTS_ATTN_BITS_PGLUE_HW_INTERRUPT) अणु

		val = REG_RD(bp, PGLUE_B_REG_PGLUE_B_INT_STS_CLR);
		BNX2X_ERR("PGLUE hw attention 0x%x\n", val);
		अगर (val & PGLUE_B_PGLUE_B_INT_STS_REG_ADDRESS_ERROR)
			BNX2X_ERR("PGLUE_B_PGLUE_B_INT_STS_REG_ADDRESS_ERROR\n");
		अगर (val & PGLUE_B_PGLUE_B_INT_STS_REG_INCORRECT_RCV_BEHAVIOR)
			BNX2X_ERR("PGLUE_B_PGLUE_B_INT_STS_REG_INCORRECT_RCV_BEHAVIOR\n");
		अगर (val & PGLUE_B_PGLUE_B_INT_STS_REG_WAS_ERROR_ATTN)
			BNX2X_ERR("PGLUE_B_PGLUE_B_INT_STS_REG_WAS_ERROR_ATTN\n");
		अगर (val & PGLUE_B_PGLUE_B_INT_STS_REG_VF_LENGTH_VIOLATION_ATTN)
			BNX2X_ERR("PGLUE_B_PGLUE_B_INT_STS_REG_VF_LENGTH_VIOLATION_ATTN\n");
		अगर (val &
		    PGLUE_B_PGLUE_B_INT_STS_REG_VF_GRC_SPACE_VIOLATION_ATTN)
			BNX2X_ERR("PGLUE_B_PGLUE_B_INT_STS_REG_VF_GRC_SPACE_VIOLATION_ATTN\n");
		अगर (val &
		    PGLUE_B_PGLUE_B_INT_STS_REG_VF_MSIX_BAR_VIOLATION_ATTN)
			BNX2X_ERR("PGLUE_B_PGLUE_B_INT_STS_REG_VF_MSIX_BAR_VIOLATION_ATTN\n");
		अगर (val & PGLUE_B_PGLUE_B_INT_STS_REG_TCPL_ERROR_ATTN)
			BNX2X_ERR("PGLUE_B_PGLUE_B_INT_STS_REG_TCPL_ERROR_ATTN\n");
		अगर (val & PGLUE_B_PGLUE_B_INT_STS_REG_TCPL_IN_TWO_RCBS_ATTN)
			BNX2X_ERR("PGLUE_B_PGLUE_B_INT_STS_REG_TCPL_IN_TWO_RCBS_ATTN\n");
		अगर (val & PGLUE_B_PGLUE_B_INT_STS_REG_CSSNOOP_FIFO_OVERFLOW)
			BNX2X_ERR("PGLUE_B_PGLUE_B_INT_STS_REG_CSSNOOP_FIFO_OVERFLOW\n");
	पूर्ण
	अगर (attn & AEU_INPUTS_ATTN_BITS_ATC_HW_INTERRUPT) अणु
		val = REG_RD(bp, ATC_REG_ATC_INT_STS_CLR);
		BNX2X_ERR("ATC hw attention 0x%x\n", val);
		अगर (val & ATC_ATC_INT_STS_REG_ADDRESS_ERROR)
			BNX2X_ERR("ATC_ATC_INT_STS_REG_ADDRESS_ERROR\n");
		अगर (val & ATC_ATC_INT_STS_REG_ATC_TCPL_TO_NOT_PEND)
			BNX2X_ERR("ATC_ATC_INT_STS_REG_ATC_TCPL_TO_NOT_PEND\n");
		अगर (val & ATC_ATC_INT_STS_REG_ATC_GPA_MULTIPLE_HITS)
			BNX2X_ERR("ATC_ATC_INT_STS_REG_ATC_GPA_MULTIPLE_HITS\n");
		अगर (val & ATC_ATC_INT_STS_REG_ATC_RCPL_TO_EMPTY_CNT)
			BNX2X_ERR("ATC_ATC_INT_STS_REG_ATC_RCPL_TO_EMPTY_CNT\n");
		अगर (val & ATC_ATC_INT_STS_REG_ATC_TCPL_ERROR)
			BNX2X_ERR("ATC_ATC_INT_STS_REG_ATC_TCPL_ERROR\n");
		अगर (val & ATC_ATC_INT_STS_REG_ATC_IREQ_LESS_THAN_STU)
			BNX2X_ERR("ATC_ATC_INT_STS_REG_ATC_IREQ_LESS_THAN_STU\n");
	पूर्ण

	अगर (attn & (AEU_INPUTS_ATTN_BITS_PGLUE_PARITY_ERROR |
		    AEU_INPUTS_ATTN_BITS_ATC_PARITY_ERROR)) अणु
		BNX2X_ERR("FATAL parity attention set4 0x%x\n",
		(u32)(attn & (AEU_INPUTS_ATTN_BITS_PGLUE_PARITY_ERROR |
		    AEU_INPUTS_ATTN_BITS_ATC_PARITY_ERROR)));
	पूर्ण
पूर्ण

अटल व्योम bnx2x_attn_पूर्णांक_deनिश्चितed(काष्ठा bnx2x *bp, u32 deनिश्चितed)
अणु
	काष्ठा attn_route attn, *group_mask;
	पूर्णांक port = BP_PORT(bp);
	पूर्णांक index;
	u32 reg_addr;
	u32 val;
	u32 aeu_mask;
	bool global = false;

	/* need to take HW lock because MCP or other port might also
	   try to handle this event */
	bnx2x_acquire_alr(bp);

	अगर (bnx2x_chk_parity_attn(bp, &global, true)) अणु
#अगर_अघोषित BNX2X_STOP_ON_ERROR
		bp->recovery_state = BNX2X_RECOVERY_INIT;
		schedule_delayed_work(&bp->sp_rtnl_task, 0);
		/* Disable HW पूर्णांकerrupts */
		bnx2x_पूर्णांक_disable(bp);
		/* In हाल of parity errors करोn't handle attentions so that
		 * other function would "see" parity errors.
		 */
#अन्यथा
		bnx2x_panic();
#पूर्ण_अगर
		bnx2x_release_alr(bp);
		वापस;
	पूर्ण

	attn.sig[0] = REG_RD(bp, MISC_REG_AEU_AFTER_INVERT_1_FUNC_0 + port*4);
	attn.sig[1] = REG_RD(bp, MISC_REG_AEU_AFTER_INVERT_2_FUNC_0 + port*4);
	attn.sig[2] = REG_RD(bp, MISC_REG_AEU_AFTER_INVERT_3_FUNC_0 + port*4);
	attn.sig[3] = REG_RD(bp, MISC_REG_AEU_AFTER_INVERT_4_FUNC_0 + port*4);
	अगर (!CHIP_IS_E1x(bp))
		attn.sig[4] =
		      REG_RD(bp, MISC_REG_AEU_AFTER_INVERT_5_FUNC_0 + port*4);
	अन्यथा
		attn.sig[4] = 0;

	DP(NETIF_MSG_HW, "attn: %08x %08x %08x %08x %08x\n",
	   attn.sig[0], attn.sig[1], attn.sig[2], attn.sig[3], attn.sig[4]);

	क्रम (index = 0; index < MAX_DYNAMIC_ATTN_GRPS; index++) अणु
		अगर (deनिश्चितed & (1 << index)) अणु
			group_mask = &bp->attn_group[index];

			DP(NETIF_MSG_HW, "group[%d]: %08x %08x %08x %08x %08x\n",
			   index,
			   group_mask->sig[0], group_mask->sig[1],
			   group_mask->sig[2], group_mask->sig[3],
			   group_mask->sig[4]);

			bnx2x_attn_पूर्णांक_deनिश्चितed4(bp,
					attn.sig[4] & group_mask->sig[4]);
			bnx2x_attn_पूर्णांक_deनिश्चितed3(bp,
					attn.sig[3] & group_mask->sig[3]);
			bnx2x_attn_पूर्णांक_deनिश्चितed1(bp,
					attn.sig[1] & group_mask->sig[1]);
			bnx2x_attn_पूर्णांक_deनिश्चितed2(bp,
					attn.sig[2] & group_mask->sig[2]);
			bnx2x_attn_पूर्णांक_deनिश्चितed0(bp,
					attn.sig[0] & group_mask->sig[0]);
		पूर्ण
	पूर्ण

	bnx2x_release_alr(bp);

	अगर (bp->common.पूर्णांक_block == INT_BLOCK_HC)
		reg_addr = (HC_REG_COMMAND_REG + port*32 +
			    COMMAND_REG_ATTN_BITS_CLR);
	अन्यथा
		reg_addr = (BAR_IGU_INTMEM + IGU_CMD_ATTN_BIT_CLR_UPPER*8);

	val = ~deनिश्चितed;
	DP(NETIF_MSG_HW, "about to mask 0x%08x at %s addr 0x%x\n", val,
	   (bp->common.पूर्णांक_block == INT_BLOCK_HC) ? "HC" : "IGU", reg_addr);
	REG_WR(bp, reg_addr, val);

	अगर (~bp->attn_state & deनिश्चितed)
		BNX2X_ERR("IGU ERROR\n");

	reg_addr = port ? MISC_REG_AEU_MASK_ATTN_FUNC_1 :
			  MISC_REG_AEU_MASK_ATTN_FUNC_0;

	bnx2x_acquire_hw_lock(bp, HW_LOCK_RESOURCE_PORT0_ATT_MASK + port);
	aeu_mask = REG_RD(bp, reg_addr);

	DP(NETIF_MSG_HW, "aeu_mask %x  newly deasserted %x\n",
	   aeu_mask, deनिश्चितed);
	aeu_mask |= (deनिश्चितed & 0x3ff);
	DP(NETIF_MSG_HW, "new mask %x\n", aeu_mask);

	REG_WR(bp, reg_addr, aeu_mask);
	bnx2x_release_hw_lock(bp, HW_LOCK_RESOURCE_PORT0_ATT_MASK + port);

	DP(NETIF_MSG_HW, "attn_state %x\n", bp->attn_state);
	bp->attn_state &= ~deनिश्चितed;
	DP(NETIF_MSG_HW, "new state %x\n", bp->attn_state);
पूर्ण

अटल व्योम bnx2x_attn_पूर्णांक(काष्ठा bnx2x *bp)
अणु
	/* पढ़ो local copy of bits */
	u32 attn_bits = le32_to_cpu(bp->def_status_blk->atten_status_block.
								attn_bits);
	u32 attn_ack = le32_to_cpu(bp->def_status_blk->atten_status_block.
								attn_bits_ack);
	u32 attn_state = bp->attn_state;

	/* look क्रम changed bits */
	u32 निश्चितed   =  attn_bits & ~attn_ack & ~attn_state;
	u32 deनिश्चितed = ~attn_bits &  attn_ack &  attn_state;

	DP(NETIF_MSG_HW,
	   "attn_bits %x  attn_ack %x  asserted %x  deasserted %x\n",
	   attn_bits, attn_ack, निश्चितed, deनिश्चितed);

	अगर (~(attn_bits ^ attn_ack) & (attn_bits ^ attn_state))
		BNX2X_ERR("BAD attention state\n");

	/* handle bits that were उठाओd */
	अगर (निश्चितed)
		bnx2x_attn_पूर्णांक_निश्चितed(bp, निश्चितed);

	अगर (deनिश्चितed)
		bnx2x_attn_पूर्णांक_deनिश्चितed(bp, deनिश्चितed);
पूर्ण

व्योम bnx2x_igu_ack_sb(काष्ठा bnx2x *bp, u8 igu_sb_id, u8 segment,
		      u16 index, u8 op, u8 update)
अणु
	u32 igu_addr = bp->igu_base_addr;
	igu_addr += (IGU_CMD_INT_ACK_BASE + igu_sb_id)*8;
	bnx2x_igu_ack_sb_gen(bp, igu_sb_id, segment, index, op, update,
			     igu_addr);
पूर्ण

अटल व्योम bnx2x_update_eq_prod(काष्ठा bnx2x *bp, u16 prod)
अणु
	/* No memory barriers */
	storm_स_रखो_eq_prod(bp, prod, BP_FUNC(bp));
पूर्ण

अटल पूर्णांक  bnx2x_cnic_handle_cfc_del(काष्ठा bnx2x *bp, u32 cid,
				      जोड़ event_ring_elem *elem)
अणु
	u8 err = elem->message.error;

	अगर (!bp->cnic_eth_dev.starting_cid  ||
	    (cid < bp->cnic_eth_dev.starting_cid &&
	    cid != bp->cnic_eth_dev.iscsi_l2_cid))
		वापस 1;

	DP(BNX2X_MSG_SP, "got delete ramrod for CNIC CID %d\n", cid);

	अगर (unlikely(err)) अणु

		BNX2X_ERR("got delete ramrod for CNIC CID %d with error!\n",
			  cid);
		bnx2x_panic_dump(bp, false);
	पूर्ण
	bnx2x_cnic_cfc_comp(bp, cid, err);
	वापस 0;
पूर्ण

अटल व्योम bnx2x_handle_mcast_eqe(काष्ठा bnx2x *bp)
अणु
	काष्ठा bnx2x_mcast_ramrod_params rparam;
	पूर्णांक rc;

	स_रखो(&rparam, 0, माप(rparam));

	rparam.mcast_obj = &bp->mcast_obj;

	netअगर_addr_lock_bh(bp->dev);

	/* Clear pending state क्रम the last command */
	bp->mcast_obj.raw.clear_pending(&bp->mcast_obj.raw);

	/* If there are pending mcast commands - send them */
	अगर (bp->mcast_obj.check_pending(&bp->mcast_obj)) अणु
		rc = bnx2x_config_mcast(bp, &rparam, BNX2X_MCAST_CMD_CONT);
		अगर (rc < 0)
			BNX2X_ERR("Failed to send pending mcast commands: %d\n",
				  rc);
	पूर्ण

	netअगर_addr_unlock_bh(bp->dev);
पूर्ण

अटल व्योम bnx2x_handle_classअगरication_eqe(काष्ठा bnx2x *bp,
					    जोड़ event_ring_elem *elem)
अणु
	अचिन्हित दीर्घ ramrod_flags = 0;
	पूर्णांक rc = 0;
	u32 echo = le32_to_cpu(elem->message.data.eth_event.echo);
	u32 cid = echo & BNX2X_SWCID_MASK;
	काष्ठा bnx2x_vlan_mac_obj *vlan_mac_obj;

	/* Always push next commands out, करोn't रुको here */
	__set_bit(RAMROD_CONT, &ramrod_flags);

	चयन (echo >> BNX2X_SWCID_SHIFT) अणु
	हाल BNX2X_FILTER_MAC_PENDING:
		DP(BNX2X_MSG_SP, "Got SETUP_MAC completions\n");
		अगर (CNIC_LOADED(bp) && (cid == BNX2X_ISCSI_ETH_CID(bp)))
			vlan_mac_obj = &bp->iscsi_l2_mac_obj;
		अन्यथा
			vlan_mac_obj = &bp->sp_objs[cid].mac_obj;

		अवरोध;
	हाल BNX2X_FILTER_VLAN_PENDING:
		DP(BNX2X_MSG_SP, "Got SETUP_VLAN completions\n");
		vlan_mac_obj = &bp->sp_objs[cid].vlan_obj;
		अवरोध;
	हाल BNX2X_FILTER_MCAST_PENDING:
		DP(BNX2X_MSG_SP, "Got SETUP_MCAST completions\n");
		/* This is only relevant क्रम 57710 where multicast MACs are
		 * configured as unicast MACs using the same ramrod.
		 */
		bnx2x_handle_mcast_eqe(bp);
		वापस;
	शेष:
		BNX2X_ERR("Unsupported classification command: 0x%x\n", echo);
		वापस;
	पूर्ण

	rc = vlan_mac_obj->complete(bp, vlan_mac_obj, elem, &ramrod_flags);

	अगर (rc < 0)
		BNX2X_ERR("Failed to schedule new commands: %d\n", rc);
	अन्यथा अगर (rc > 0)
		DP(BNX2X_MSG_SP, "Scheduled next pending commands...\n");
पूर्ण

अटल व्योम bnx2x_set_iscsi_eth_rx_mode(काष्ठा bnx2x *bp, bool start);

अटल व्योम bnx2x_handle_rx_mode_eqe(काष्ठा bnx2x *bp)
अणु
	netअगर_addr_lock_bh(bp->dev);

	clear_bit(BNX2X_FILTER_RX_MODE_PENDING, &bp->sp_state);

	/* Send rx_mode command again अगर was requested */
	अगर (test_and_clear_bit(BNX2X_FILTER_RX_MODE_SCHED, &bp->sp_state))
		bnx2x_set_storm_rx_mode(bp);
	अन्यथा अगर (test_and_clear_bit(BNX2X_FILTER_ISCSI_ETH_START_SCHED,
				    &bp->sp_state))
		bnx2x_set_iscsi_eth_rx_mode(bp, true);
	अन्यथा अगर (test_and_clear_bit(BNX2X_FILTER_ISCSI_ETH_STOP_SCHED,
				    &bp->sp_state))
		bnx2x_set_iscsi_eth_rx_mode(bp, false);

	netअगर_addr_unlock_bh(bp->dev);
पूर्ण

अटल व्योम bnx2x_after_afex_vअगर_lists(काष्ठा bnx2x *bp,
					      जोड़ event_ring_elem *elem)
अणु
	अगर (elem->message.data.vअगर_list_event.echo == VIF_LIST_RULE_GET) अणु
		DP(BNX2X_MSG_SP,
		   "afex: ramrod completed VIF LIST_GET, addrs 0x%x\n",
		   elem->message.data.vअगर_list_event.func_bit_map);
		bnx2x_fw_command(bp, DRV_MSG_CODE_AFEX_LISTGET_ACK,
			elem->message.data.vअगर_list_event.func_bit_map);
	पूर्ण अन्यथा अगर (elem->message.data.vअगर_list_event.echo ==
		   VIF_LIST_RULE_SET) अणु
		DP(BNX2X_MSG_SP, "afex: ramrod completed VIF LIST_SET\n");
		bnx2x_fw_command(bp, DRV_MSG_CODE_AFEX_LISTSET_ACK, 0);
	पूर्ण
पूर्ण

/* called with rtnl_lock */
अटल व्योम bnx2x_after_function_update(काष्ठा bnx2x *bp)
अणु
	पूर्णांक q, rc;
	काष्ठा bnx2x_fastpath *fp;
	काष्ठा bnx2x_queue_state_params queue_params = अणुशून्यपूर्ण;
	काष्ठा bnx2x_queue_update_params *q_update_params =
		&queue_params.params.update;

	/* Send Q update command with afex vlan removal values क्रम all Qs */
	queue_params.cmd = BNX2X_Q_CMD_UPDATE;

	/* set silent vlan removal values according to vlan mode */
	__set_bit(BNX2X_Q_UPDATE_SILENT_VLAN_REM_CHNG,
		  &q_update_params->update_flags);
	__set_bit(BNX2X_Q_UPDATE_SILENT_VLAN_REM,
		  &q_update_params->update_flags);
	__set_bit(RAMROD_COMP_WAIT, &queue_params.ramrod_flags);

	/* in access mode mark mask and value are 0 to strip all vlans */
	अगर (bp->afex_vlan_mode == FUNC_MF_CFG_AFEX_VLAN_ACCESS_MODE) अणु
		q_update_params->silent_removal_value = 0;
		q_update_params->silent_removal_mask = 0;
	पूर्ण अन्यथा अणु
		q_update_params->silent_removal_value =
			(bp->afex_def_vlan_tag & VLAN_VID_MASK);
		q_update_params->silent_removal_mask = VLAN_VID_MASK;
	पूर्ण

	क्रम_each_eth_queue(bp, q) अणु
		/* Set the appropriate Queue object */
		fp = &bp->fp[q];
		queue_params.q_obj = &bnx2x_sp_obj(bp, fp).q_obj;

		/* send the ramrod */
		rc = bnx2x_queue_state_change(bp, &queue_params);
		अगर (rc < 0)
			BNX2X_ERR("Failed to config silent vlan rem for Q %d\n",
				  q);
	पूर्ण

	अगर (!NO_FCOE(bp) && CNIC_ENABLED(bp)) अणु
		fp = &bp->fp[FCOE_IDX(bp)];
		queue_params.q_obj = &bnx2x_sp_obj(bp, fp).q_obj;

		/* clear pending completion bit */
		__clear_bit(RAMROD_COMP_WAIT, &queue_params.ramrod_flags);

		/* mark latest Q bit */
		smp_mb__beक्रमe_atomic();
		set_bit(BNX2X_AFEX_FCOE_Q_UPDATE_PENDING, &bp->sp_state);
		smp_mb__after_atomic();

		/* send Q update ramrod क्रम FCoE Q */
		rc = bnx2x_queue_state_change(bp, &queue_params);
		अगर (rc < 0)
			BNX2X_ERR("Failed to config silent vlan rem for Q %d\n",
				  q);
	पूर्ण अन्यथा अणु
		/* If no FCoE ring - ACK MCP now */
		bnx2x_link_report(bp);
		bnx2x_fw_command(bp, DRV_MSG_CODE_AFEX_VIFSET_ACK, 0);
	पूर्ण
पूर्ण

अटल काष्ठा bnx2x_queue_sp_obj *bnx2x_cid_to_q_obj(
	काष्ठा bnx2x *bp, u32 cid)
अणु
	DP(BNX2X_MSG_SP, "retrieving fp from cid %d\n", cid);

	अगर (CNIC_LOADED(bp) && (cid == BNX2X_FCOE_ETH_CID(bp)))
		वापस &bnx2x_fcoe_sp_obj(bp, q_obj);
	अन्यथा
		वापस &bp->sp_objs[CID_TO_FP(cid, bp)].q_obj;
पूर्ण

अटल व्योम bnx2x_eq_पूर्णांक(काष्ठा bnx2x *bp)
अणु
	u16 hw_cons, sw_cons, sw_prod;
	जोड़ event_ring_elem *elem;
	u8 echo;
	u32 cid;
	u8 opcode;
	पूर्णांक rc, spqe_cnt = 0;
	काष्ठा bnx2x_queue_sp_obj *q_obj;
	काष्ठा bnx2x_func_sp_obj *f_obj = &bp->func_obj;
	काष्ठा bnx2x_raw_obj *rss_raw = &bp->rss_conf_obj.raw;

	hw_cons = le16_to_cpu(*bp->eq_cons_sb);

	/* The hw_cos range is 1-255, 257 - the sw_cons range is 0-254, 256.
	 * when we get the next-page we need to adjust so the loop
	 * condition below will be met. The next element is the size of a
	 * regular element and hence incrementing by 1
	 */
	अगर ((hw_cons & EQ_DESC_MAX_PAGE) == EQ_DESC_MAX_PAGE)
		hw_cons++;

	/* This function may never run in parallel with itself क्रम a
	 * specअगरic bp, thus there is no need in "paired" पढ़ो memory
	 * barrier here.
	 */
	sw_cons = bp->eq_cons;
	sw_prod = bp->eq_prod;

	DP(BNX2X_MSG_SP, "EQ:  hw_cons %u  sw_cons %u bp->eq_spq_left %x\n",
			hw_cons, sw_cons, atomic_पढ़ो(&bp->eq_spq_left));

	क्रम (; sw_cons != hw_cons;
	      sw_prod = NEXT_EQ_IDX(sw_prod), sw_cons = NEXT_EQ_IDX(sw_cons)) अणु

		elem = &bp->eq_ring[EQ_DESC(sw_cons)];

		rc = bnx2x_iov_eq_sp_event(bp, elem);
		अगर (!rc) अणु
			DP(BNX2X_MSG_IOV, "bnx2x_iov_eq_sp_event returned %d\n",
			   rc);
			जाओ next_spqe;
		पूर्ण

		opcode = elem->message.opcode;

		/* handle eq element */
		चयन (opcode) अणु
		हाल EVENT_RING_OPCODE_VF_PF_CHANNEL:
			bnx2x_vf_mbx_schedule(bp,
					      &elem->message.data.vf_pf_event);
			जारी;

		हाल EVENT_RING_OPCODE_STAT_QUERY:
			DP_AND((BNX2X_MSG_SP | BNX2X_MSG_STATS),
			       "got statistics comp event %d\n",
			       bp->stats_comp++);
			/* nothing to करो with stats comp */
			जाओ next_spqe;

		हाल EVENT_RING_OPCODE_CFC_DEL:
			/* handle according to cid range */
			/*
			 * we may want to verअगरy here that the bp state is
			 * HALTING
			 */

			/* elem CID originates from FW; actually LE */
			cid = SW_CID(elem->message.data.cfc_del_event.cid);

			DP(BNX2X_MSG_SP,
			   "got delete ramrod for MULTI[%d]\n", cid);

			अगर (CNIC_LOADED(bp) &&
			    !bnx2x_cnic_handle_cfc_del(bp, cid, elem))
				जाओ next_spqe;

			q_obj = bnx2x_cid_to_q_obj(bp, cid);

			अगर (q_obj->complete_cmd(bp, q_obj, BNX2X_Q_CMD_CFC_DEL))
				अवरोध;

			जाओ next_spqe;

		हाल EVENT_RING_OPCODE_STOP_TRAFFIC:
			DP(BNX2X_MSG_SP | BNX2X_MSG_DCB, "got STOP TRAFFIC\n");
			bnx2x_dcbx_set_params(bp, BNX2X_DCBX_STATE_TX_PAUSED);
			अगर (f_obj->complete_cmd(bp, f_obj,
						BNX2X_F_CMD_TX_STOP))
				अवरोध;
			जाओ next_spqe;

		हाल EVENT_RING_OPCODE_START_TRAFFIC:
			DP(BNX2X_MSG_SP | BNX2X_MSG_DCB, "got START TRAFFIC\n");
			bnx2x_dcbx_set_params(bp, BNX2X_DCBX_STATE_TX_RELEASED);
			अगर (f_obj->complete_cmd(bp, f_obj,
						BNX2X_F_CMD_TX_START))
				अवरोध;
			जाओ next_spqe;

		हाल EVENT_RING_OPCODE_FUNCTION_UPDATE:
			echo = elem->message.data.function_update_event.echo;
			अगर (echo == SWITCH_UPDATE) अणु
				DP(BNX2X_MSG_SP | NETIF_MSG_IFUP,
				   "got FUNC_SWITCH_UPDATE ramrod\n");
				अगर (f_obj->complete_cmd(
					bp, f_obj, BNX2X_F_CMD_SWITCH_UPDATE))
					अवरोध;

			पूर्ण अन्यथा अणु
				पूर्णांक cmd = BNX2X_SP_RTNL_AFEX_F_UPDATE;

				DP(BNX2X_MSG_SP | BNX2X_MSG_MCP,
				   "AFEX: ramrod completed FUNCTION_UPDATE\n");
				f_obj->complete_cmd(bp, f_obj,
						    BNX2X_F_CMD_AFEX_UPDATE);

				/* We will perक्रमm the Queues update from
				 * sp_rtnl task as all Queue SP operations
				 * should run under rtnl_lock.
				 */
				bnx2x_schedule_sp_rtnl(bp, cmd, 0);
			पूर्ण

			जाओ next_spqe;

		हाल EVENT_RING_OPCODE_AFEX_VIF_LISTS:
			f_obj->complete_cmd(bp, f_obj,
					    BNX2X_F_CMD_AFEX_VIFLISTS);
			bnx2x_after_afex_vअगर_lists(bp, elem);
			जाओ next_spqe;
		हाल EVENT_RING_OPCODE_FUNCTION_START:
			DP(BNX2X_MSG_SP | NETIF_MSG_IFUP,
			   "got FUNC_START ramrod\n");
			अगर (f_obj->complete_cmd(bp, f_obj, BNX2X_F_CMD_START))
				अवरोध;

			जाओ next_spqe;

		हाल EVENT_RING_OPCODE_FUNCTION_STOP:
			DP(BNX2X_MSG_SP | NETIF_MSG_IFUP,
			   "got FUNC_STOP ramrod\n");
			अगर (f_obj->complete_cmd(bp, f_obj, BNX2X_F_CMD_STOP))
				अवरोध;

			जाओ next_spqe;

		हाल EVENT_RING_OPCODE_SET_TIMESYNC:
			DP(BNX2X_MSG_SP | BNX2X_MSG_PTP,
			   "got set_timesync ramrod completion\n");
			अगर (f_obj->complete_cmd(bp, f_obj,
						BNX2X_F_CMD_SET_TIMESYNC))
				अवरोध;
			जाओ next_spqe;
		पूर्ण

		चयन (opcode | bp->state) अणु
		हाल (EVENT_RING_OPCODE_RSS_UPDATE_RULES |
		      BNX2X_STATE_OPEN):
		हाल (EVENT_RING_OPCODE_RSS_UPDATE_RULES |
		      BNX2X_STATE_OPENING_WAIT4_PORT):
		हाल (EVENT_RING_OPCODE_RSS_UPDATE_RULES |
		      BNX2X_STATE_CLOSING_WAIT4_HALT):
			DP(BNX2X_MSG_SP, "got RSS_UPDATE ramrod. CID %d\n",
			   SW_CID(elem->message.data.eth_event.echo));
			rss_raw->clear_pending(rss_raw);
			अवरोध;

		हाल (EVENT_RING_OPCODE_SET_MAC | BNX2X_STATE_OPEN):
		हाल (EVENT_RING_OPCODE_SET_MAC | BNX2X_STATE_DIAG):
		हाल (EVENT_RING_OPCODE_SET_MAC |
		      BNX2X_STATE_CLOSING_WAIT4_HALT):
		हाल (EVENT_RING_OPCODE_CLASSIFICATION_RULES |
		      BNX2X_STATE_OPEN):
		हाल (EVENT_RING_OPCODE_CLASSIFICATION_RULES |
		      BNX2X_STATE_DIAG):
		हाल (EVENT_RING_OPCODE_CLASSIFICATION_RULES |
		      BNX2X_STATE_CLOSING_WAIT4_HALT):
			DP(BNX2X_MSG_SP, "got (un)set vlan/mac ramrod\n");
			bnx2x_handle_classअगरication_eqe(bp, elem);
			अवरोध;

		हाल (EVENT_RING_OPCODE_MULTICAST_RULES |
		      BNX2X_STATE_OPEN):
		हाल (EVENT_RING_OPCODE_MULTICAST_RULES |
		      BNX2X_STATE_DIAG):
		हाल (EVENT_RING_OPCODE_MULTICAST_RULES |
		      BNX2X_STATE_CLOSING_WAIT4_HALT):
			DP(BNX2X_MSG_SP, "got mcast ramrod\n");
			bnx2x_handle_mcast_eqe(bp);
			अवरोध;

		हाल (EVENT_RING_OPCODE_FILTERS_RULES |
		      BNX2X_STATE_OPEN):
		हाल (EVENT_RING_OPCODE_FILTERS_RULES |
		      BNX2X_STATE_DIAG):
		हाल (EVENT_RING_OPCODE_FILTERS_RULES |
		      BNX2X_STATE_CLOSING_WAIT4_HALT):
			DP(BNX2X_MSG_SP, "got rx_mode ramrod\n");
			bnx2x_handle_rx_mode_eqe(bp);
			अवरोध;
		शेष:
			/* unknown event log error and जारी */
			BNX2X_ERR("Unknown EQ event %d, bp->state 0x%x\n",
				  elem->message.opcode, bp->state);
		पूर्ण
next_spqe:
		spqe_cnt++;
	पूर्ण /* क्रम */

	smp_mb__beक्रमe_atomic();
	atomic_add(spqe_cnt, &bp->eq_spq_left);

	bp->eq_cons = sw_cons;
	bp->eq_prod = sw_prod;
	/* Make sure that above mem ग_लिखोs were issued towards the memory */
	smp_wmb();

	/* update producer */
	bnx2x_update_eq_prod(bp, bp->eq_prod);
पूर्ण

अटल व्योम bnx2x_sp_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bnx2x *bp = container_of(work, काष्ठा bnx2x, sp_task.work);

	DP(BNX2X_MSG_SP, "sp task invoked\n");

	/* make sure the atomic पूर्णांकerrupt_occurred has been written */
	smp_rmb();
	अगर (atomic_पढ़ो(&bp->पूर्णांकerrupt_occurred)) अणु

		/* what work needs to be perक्रमmed? */
		u16 status = bnx2x_update_dsb_idx(bp);

		DP(BNX2X_MSG_SP, "status %x\n", status);
		DP(BNX2X_MSG_SP, "setting interrupt_occurred to 0\n");
		atomic_set(&bp->पूर्णांकerrupt_occurred, 0);

		/* HW attentions */
		अगर (status & BNX2X_DEF_SB_ATT_IDX) अणु
			bnx2x_attn_पूर्णांक(bp);
			status &= ~BNX2X_DEF_SB_ATT_IDX;
		पूर्ण

		/* SP events: STAT_QUERY and others */
		अगर (status & BNX2X_DEF_SB_IDX) अणु
			काष्ठा bnx2x_fastpath *fp = bnx2x_fcoe_fp(bp);

			अगर (FCOE_INIT(bp) &&
			    (bnx2x_has_rx_work(fp) || bnx2x_has_tx_work(fp))) अणु
				/* Prevent local bottom-halves from running as
				 * we are going to change the local NAPI list.
				 */
				local_bh_disable();
				napi_schedule(&bnx2x_fcoe(bp, napi));
				local_bh_enable();
			पूर्ण

			/* Handle EQ completions */
			bnx2x_eq_पूर्णांक(bp);
			bnx2x_ack_sb(bp, bp->igu_dsb_id, USTORM_ID,
				     le16_to_cpu(bp->def_idx), IGU_INT_NOP, 1);

			status &= ~BNX2X_DEF_SB_IDX;
		पूर्ण

		/* अगर status is non zero then perhaps something went wrong */
		अगर (unlikely(status))
			DP(BNX2X_MSG_SP,
			   "got an unknown interrupt! (status 0x%x)\n", status);

		/* ack status block only अगर something was actually handled */
		bnx2x_ack_sb(bp, bp->igu_dsb_id, ATTENTION_ID,
			     le16_to_cpu(bp->def_att_idx), IGU_INT_ENABLE, 1);
	पूर्ण

	/* afex - poll to check अगर VIFSET_ACK should be sent to MFW */
	अगर (test_and_clear_bit(BNX2X_AFEX_PENDING_VIFSET_MCP_ACK,
			       &bp->sp_state)) अणु
		bnx2x_link_report(bp);
		bnx2x_fw_command(bp, DRV_MSG_CODE_AFEX_VIFSET_ACK, 0);
	पूर्ण
पूर्ण

irqवापस_t bnx2x_msix_sp_पूर्णांक(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा net_device *dev = dev_instance;
	काष्ठा bnx2x *bp = netdev_priv(dev);

	bnx2x_ack_sb(bp, bp->igu_dsb_id, USTORM_ID, 0,
		     IGU_INT_DISABLE, 0);

#अगर_घोषित BNX2X_STOP_ON_ERROR
	अगर (unlikely(bp->panic))
		वापस IRQ_HANDLED;
#पूर्ण_अगर

	अगर (CNIC_LOADED(bp)) अणु
		काष्ठा cnic_ops *c_ops;

		rcu_पढ़ो_lock();
		c_ops = rcu_dereference(bp->cnic_ops);
		अगर (c_ops)
			c_ops->cnic_handler(bp->cnic_data, शून्य);
		rcu_पढ़ो_unlock();
	पूर्ण

	/* schedule sp task to perक्रमm शेष status block work, ack
	 * attentions and enable पूर्णांकerrupts.
	 */
	bnx2x_schedule_sp_task(bp);

	वापस IRQ_HANDLED;
पूर्ण

/* end of slow path */

व्योम bnx2x_drv_pulse(काष्ठा bnx2x *bp)
अणु
	SHMEM_WR(bp, func_mb[BP_FW_MB_IDX(bp)].drv_pulse_mb,
		 bp->fw_drv_pulse_wr_seq);
पूर्ण

अटल व्योम bnx2x_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा bnx2x *bp = from_समयr(bp, t, समयr);

	अगर (!netअगर_running(bp->dev))
		वापस;

	अगर (IS_PF(bp) &&
	    !BP_NOMCP(bp)) अणु
		पूर्णांक mb_idx = BP_FW_MB_IDX(bp);
		u16 drv_pulse;
		u16 mcp_pulse;

		++bp->fw_drv_pulse_wr_seq;
		bp->fw_drv_pulse_wr_seq &= DRV_PULSE_SEQ_MASK;
		drv_pulse = bp->fw_drv_pulse_wr_seq;
		bnx2x_drv_pulse(bp);

		mcp_pulse = (SHMEM_RD(bp, func_mb[mb_idx].mcp_pulse_mb) &
			     MCP_PULSE_SEQ_MASK);
		/* The delta between driver pulse and mcp response
		 * should not get too big. If the MFW is more than 5 pulses
		 * behind, we should worry about it enough to generate an error
		 * log.
		 */
		अगर (((drv_pulse - mcp_pulse) & MCP_PULSE_SEQ_MASK) > 5)
			BNX2X_ERR("MFW seems hanged: drv_pulse (0x%x) != mcp_pulse (0x%x)\n",
				  drv_pulse, mcp_pulse);
	पूर्ण

	अगर (bp->state == BNX2X_STATE_OPEN)
		bnx2x_stats_handle(bp, STATS_EVENT_UPDATE);

	/* sample pf vf bulletin board क्रम new posts from pf */
	अगर (IS_VF(bp))
		bnx2x_समयr_sriov(bp);

	mod_समयr(&bp->समयr, jअगरfies + bp->current_पूर्णांकerval);
पूर्ण

/* end of Statistics */

/* nic init */

/*
 * nic init service functions
 */

अटल व्योम bnx2x_fill(काष्ठा bnx2x *bp, u32 addr, पूर्णांक fill, u32 len)
अणु
	u32 i;
	अगर (!(len%4) && !(addr%4))
		क्रम (i = 0; i < len; i += 4)
			REG_WR(bp, addr + i, fill);
	अन्यथा
		क्रम (i = 0; i < len; i++)
			REG_WR8(bp, addr + i, fill);
पूर्ण

/* helper: ग_लिखोs FP SP data to FW - data_size in dwords */
अटल व्योम bnx2x_wr_fp_sb_data(काष्ठा bnx2x *bp,
				पूर्णांक fw_sb_id,
				u32 *sb_data_p,
				u32 data_size)
अणु
	पूर्णांक index;
	क्रम (index = 0; index < data_size; index++)
		REG_WR(bp, BAR_CSTRORM_INTMEM +
			CSTORM_STATUS_BLOCK_DATA_OFFSET(fw_sb_id) +
			माप(u32)*index,
			*(sb_data_p + index));
पूर्ण

अटल व्योम bnx2x_zero_fp_sb(काष्ठा bnx2x *bp, पूर्णांक fw_sb_id)
अणु
	u32 *sb_data_p;
	u32 data_size = 0;
	काष्ठा hc_status_block_data_e2 sb_data_e2;
	काष्ठा hc_status_block_data_e1x sb_data_e1x;

	/* disable the function first */
	अगर (!CHIP_IS_E1x(bp)) अणु
		स_रखो(&sb_data_e2, 0, माप(काष्ठा hc_status_block_data_e2));
		sb_data_e2.common.state = SB_DISABLED;
		sb_data_e2.common.p_func.vf_valid = false;
		sb_data_p = (u32 *)&sb_data_e2;
		data_size = माप(काष्ठा hc_status_block_data_e2)/माप(u32);
	पूर्ण अन्यथा अणु
		स_रखो(&sb_data_e1x, 0,
		       माप(काष्ठा hc_status_block_data_e1x));
		sb_data_e1x.common.state = SB_DISABLED;
		sb_data_e1x.common.p_func.vf_valid = false;
		sb_data_p = (u32 *)&sb_data_e1x;
		data_size = माप(काष्ठा hc_status_block_data_e1x)/माप(u32);
	पूर्ण
	bnx2x_wr_fp_sb_data(bp, fw_sb_id, sb_data_p, data_size);

	bnx2x_fill(bp, BAR_CSTRORM_INTMEM +
			CSTORM_STATUS_BLOCK_OFFSET(fw_sb_id), 0,
			CSTORM_STATUS_BLOCK_SIZE);
	bnx2x_fill(bp, BAR_CSTRORM_INTMEM +
			CSTORM_SYNC_BLOCK_OFFSET(fw_sb_id), 0,
			CSTORM_SYNC_BLOCK_SIZE);
पूर्ण

/* helper:  ग_लिखोs SP SB data to FW */
अटल व्योम bnx2x_wr_sp_sb_data(काष्ठा bnx2x *bp,
		काष्ठा hc_sp_status_block_data *sp_sb_data)
अणु
	पूर्णांक func = BP_FUNC(bp);
	पूर्णांक i;
	क्रम (i = 0; i < माप(काष्ठा hc_sp_status_block_data)/माप(u32); i++)
		REG_WR(bp, BAR_CSTRORM_INTMEM +
			CSTORM_SP_STATUS_BLOCK_DATA_OFFSET(func) +
			i*माप(u32),
			*((u32 *)sp_sb_data + i));
पूर्ण

अटल व्योम bnx2x_zero_sp_sb(काष्ठा bnx2x *bp)
अणु
	पूर्णांक func = BP_FUNC(bp);
	काष्ठा hc_sp_status_block_data sp_sb_data;
	स_रखो(&sp_sb_data, 0, माप(काष्ठा hc_sp_status_block_data));

	sp_sb_data.state = SB_DISABLED;
	sp_sb_data.p_func.vf_valid = false;

	bnx2x_wr_sp_sb_data(bp, &sp_sb_data);

	bnx2x_fill(bp, BAR_CSTRORM_INTMEM +
			CSTORM_SP_STATUS_BLOCK_OFFSET(func), 0,
			CSTORM_SP_STATUS_BLOCK_SIZE);
	bnx2x_fill(bp, BAR_CSTRORM_INTMEM +
			CSTORM_SP_SYNC_BLOCK_OFFSET(func), 0,
			CSTORM_SP_SYNC_BLOCK_SIZE);
पूर्ण

अटल व्योम bnx2x_setup_ndsb_state_machine(काष्ठा hc_status_block_sm *hc_sm,
					   पूर्णांक igu_sb_id, पूर्णांक igu_seg_id)
अणु
	hc_sm->igu_sb_id = igu_sb_id;
	hc_sm->igu_seg_id = igu_seg_id;
	hc_sm->समयr_value = 0xFF;
	hc_sm->समय_प्रकारo_expire = 0xFFFFFFFF;
पूर्ण

/* allocates state machine ids. */
अटल व्योम bnx2x_map_sb_state_machines(काष्ठा hc_index_data *index_data)
अणु
	/* zero out state machine indices */
	/* rx indices */
	index_data[HC_INDEX_ETH_RX_CQ_CONS].flags &= ~HC_INDEX_DATA_SM_ID;

	/* tx indices */
	index_data[HC_INDEX_OOO_TX_CQ_CONS].flags &= ~HC_INDEX_DATA_SM_ID;
	index_data[HC_INDEX_ETH_TX_CQ_CONS_COS0].flags &= ~HC_INDEX_DATA_SM_ID;
	index_data[HC_INDEX_ETH_TX_CQ_CONS_COS1].flags &= ~HC_INDEX_DATA_SM_ID;
	index_data[HC_INDEX_ETH_TX_CQ_CONS_COS2].flags &= ~HC_INDEX_DATA_SM_ID;

	/* map indices */
	/* rx indices */
	index_data[HC_INDEX_ETH_RX_CQ_CONS].flags |=
		SM_RX_ID << HC_INDEX_DATA_SM_ID_SHIFT;

	/* tx indices */
	index_data[HC_INDEX_OOO_TX_CQ_CONS].flags |=
		SM_TX_ID << HC_INDEX_DATA_SM_ID_SHIFT;
	index_data[HC_INDEX_ETH_TX_CQ_CONS_COS0].flags |=
		SM_TX_ID << HC_INDEX_DATA_SM_ID_SHIFT;
	index_data[HC_INDEX_ETH_TX_CQ_CONS_COS1].flags |=
		SM_TX_ID << HC_INDEX_DATA_SM_ID_SHIFT;
	index_data[HC_INDEX_ETH_TX_CQ_CONS_COS2].flags |=
		SM_TX_ID << HC_INDEX_DATA_SM_ID_SHIFT;
पूर्ण

व्योम bnx2x_init_sb(काष्ठा bnx2x *bp, dma_addr_t mapping, पूर्णांक vfid,
			  u8 vf_valid, पूर्णांक fw_sb_id, पूर्णांक igu_sb_id)
अणु
	पूर्णांक igu_seg_id;

	काष्ठा hc_status_block_data_e2 sb_data_e2;
	काष्ठा hc_status_block_data_e1x sb_data_e1x;
	काष्ठा hc_status_block_sm  *hc_sm_p;
	पूर्णांक data_size;
	u32 *sb_data_p;

	अगर (CHIP_INT_MODE_IS_BC(bp))
		igu_seg_id = HC_SEG_ACCESS_NORM;
	अन्यथा
		igu_seg_id = IGU_SEG_ACCESS_NORM;

	bnx2x_zero_fp_sb(bp, fw_sb_id);

	अगर (!CHIP_IS_E1x(bp)) अणु
		स_रखो(&sb_data_e2, 0, माप(काष्ठा hc_status_block_data_e2));
		sb_data_e2.common.state = SB_ENABLED;
		sb_data_e2.common.p_func.pf_id = BP_FUNC(bp);
		sb_data_e2.common.p_func.vf_id = vfid;
		sb_data_e2.common.p_func.vf_valid = vf_valid;
		sb_data_e2.common.p_func.vnic_id = BP_VN(bp);
		sb_data_e2.common.same_igu_sb_1b = true;
		sb_data_e2.common.host_sb_addr.hi = U64_HI(mapping);
		sb_data_e2.common.host_sb_addr.lo = U64_LO(mapping);
		hc_sm_p = sb_data_e2.common.state_machine;
		sb_data_p = (u32 *)&sb_data_e2;
		data_size = माप(काष्ठा hc_status_block_data_e2)/माप(u32);
		bnx2x_map_sb_state_machines(sb_data_e2.index_data);
	पूर्ण अन्यथा अणु
		स_रखो(&sb_data_e1x, 0,
		       माप(काष्ठा hc_status_block_data_e1x));
		sb_data_e1x.common.state = SB_ENABLED;
		sb_data_e1x.common.p_func.pf_id = BP_FUNC(bp);
		sb_data_e1x.common.p_func.vf_id = 0xff;
		sb_data_e1x.common.p_func.vf_valid = false;
		sb_data_e1x.common.p_func.vnic_id = BP_VN(bp);
		sb_data_e1x.common.same_igu_sb_1b = true;
		sb_data_e1x.common.host_sb_addr.hi = U64_HI(mapping);
		sb_data_e1x.common.host_sb_addr.lo = U64_LO(mapping);
		hc_sm_p = sb_data_e1x.common.state_machine;
		sb_data_p = (u32 *)&sb_data_e1x;
		data_size = माप(काष्ठा hc_status_block_data_e1x)/माप(u32);
		bnx2x_map_sb_state_machines(sb_data_e1x.index_data);
	पूर्ण

	bnx2x_setup_ndsb_state_machine(&hc_sm_p[SM_RX_ID],
				       igu_sb_id, igu_seg_id);
	bnx2x_setup_ndsb_state_machine(&hc_sm_p[SM_TX_ID],
				       igu_sb_id, igu_seg_id);

	DP(NETIF_MSG_IFUP, "Init FW SB %d\n", fw_sb_id);

	/* ग_लिखो indices to HW - PCI guarantees endianity of regpairs */
	bnx2x_wr_fp_sb_data(bp, fw_sb_id, sb_data_p, data_size);
पूर्ण

अटल व्योम bnx2x_update_coalesce_sb(काष्ठा bnx2x *bp, u8 fw_sb_id,
				     u16 tx_usec, u16 rx_usec)
अणु
	bnx2x_update_coalesce_sb_index(bp, fw_sb_id, HC_INDEX_ETH_RX_CQ_CONS,
				    false, rx_usec);
	bnx2x_update_coalesce_sb_index(bp, fw_sb_id,
				       HC_INDEX_ETH_TX_CQ_CONS_COS0, false,
				       tx_usec);
	bnx2x_update_coalesce_sb_index(bp, fw_sb_id,
				       HC_INDEX_ETH_TX_CQ_CONS_COS1, false,
				       tx_usec);
	bnx2x_update_coalesce_sb_index(bp, fw_sb_id,
				       HC_INDEX_ETH_TX_CQ_CONS_COS2, false,
				       tx_usec);
पूर्ण

अटल व्योम bnx2x_init_def_sb(काष्ठा bnx2x *bp)
अणु
	काष्ठा host_sp_status_block *def_sb = bp->def_status_blk;
	dma_addr_t mapping = bp->def_status_blk_mapping;
	पूर्णांक igu_sp_sb_index;
	पूर्णांक igu_seg_id;
	पूर्णांक port = BP_PORT(bp);
	पूर्णांक func = BP_FUNC(bp);
	पूर्णांक reg_offset, reg_offset_en5;
	u64 section;
	पूर्णांक index;
	काष्ठा hc_sp_status_block_data sp_sb_data;
	स_रखो(&sp_sb_data, 0, माप(काष्ठा hc_sp_status_block_data));

	अगर (CHIP_INT_MODE_IS_BC(bp)) अणु
		igu_sp_sb_index = DEF_SB_IGU_ID;
		igu_seg_id = HC_SEG_ACCESS_DEF;
	पूर्ण अन्यथा अणु
		igu_sp_sb_index = bp->igu_dsb_id;
		igu_seg_id = IGU_SEG_ACCESS_DEF;
	पूर्ण

	/* ATTN */
	section = ((u64)mapping) + दुरत्व(काष्ठा host_sp_status_block,
					    atten_status_block);
	def_sb->atten_status_block.status_block_id = igu_sp_sb_index;

	bp->attn_state = 0;

	reg_offset = (port ? MISC_REG_AEU_ENABLE1_FUNC_1_OUT_0 :
			     MISC_REG_AEU_ENABLE1_FUNC_0_OUT_0);
	reg_offset_en5 = (port ? MISC_REG_AEU_ENABLE5_FUNC_1_OUT_0 :
				 MISC_REG_AEU_ENABLE5_FUNC_0_OUT_0);
	क्रम (index = 0; index < MAX_DYNAMIC_ATTN_GRPS; index++) अणु
		पूर्णांक sindex;
		/* take care of sig[0]..sig[4] */
		क्रम (sindex = 0; sindex < 4; sindex++)
			bp->attn_group[index].sig[sindex] =
			   REG_RD(bp, reg_offset + sindex*0x4 + 0x10*index);

		अगर (!CHIP_IS_E1x(bp))
			/*
			 * enable5 is separate from the rest of the रेजिस्टरs,
			 * and thereक्रमe the address skip is 4
			 * and not 16 between the dअगरferent groups
			 */
			bp->attn_group[index].sig[4] = REG_RD(bp,
					reg_offset_en5 + 0x4*index);
		अन्यथा
			bp->attn_group[index].sig[4] = 0;
	पूर्ण

	अगर (bp->common.पूर्णांक_block == INT_BLOCK_HC) अणु
		reg_offset = (port ? HC_REG_ATTN_MSG1_ADDR_L :
				     HC_REG_ATTN_MSG0_ADDR_L);

		REG_WR(bp, reg_offset, U64_LO(section));
		REG_WR(bp, reg_offset + 4, U64_HI(section));
	पूर्ण अन्यथा अगर (!CHIP_IS_E1x(bp)) अणु
		REG_WR(bp, IGU_REG_ATTN_MSG_ADDR_L, U64_LO(section));
		REG_WR(bp, IGU_REG_ATTN_MSG_ADDR_H, U64_HI(section));
	पूर्ण

	section = ((u64)mapping) + दुरत्व(काष्ठा host_sp_status_block,
					    sp_sb);

	bnx2x_zero_sp_sb(bp);

	/* PCI guarantees endianity of regpairs */
	sp_sb_data.state		= SB_ENABLED;
	sp_sb_data.host_sb_addr.lo	= U64_LO(section);
	sp_sb_data.host_sb_addr.hi	= U64_HI(section);
	sp_sb_data.igu_sb_id		= igu_sp_sb_index;
	sp_sb_data.igu_seg_id		= igu_seg_id;
	sp_sb_data.p_func.pf_id		= func;
	sp_sb_data.p_func.vnic_id	= BP_VN(bp);
	sp_sb_data.p_func.vf_id		= 0xff;

	bnx2x_wr_sp_sb_data(bp, &sp_sb_data);

	bnx2x_ack_sb(bp, bp->igu_dsb_id, USTORM_ID, 0, IGU_INT_ENABLE, 0);
पूर्ण

व्योम bnx2x_update_coalesce(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;

	क्रम_each_eth_queue(bp, i)
		bnx2x_update_coalesce_sb(bp, bp->fp[i].fw_sb_id,
					 bp->tx_ticks, bp->rx_ticks);
पूर्ण

अटल व्योम bnx2x_init_sp_ring(काष्ठा bnx2x *bp)
अणु
	spin_lock_init(&bp->spq_lock);
	atomic_set(&bp->cq_spq_left, MAX_SPQ_PENDING);

	bp->spq_prod_idx = 0;
	bp->dsb_sp_prod = BNX2X_SP_DSB_INDEX;
	bp->spq_prod_bd = bp->spq;
	bp->spq_last_bd = bp->spq_prod_bd + MAX_SP_DESC_CNT;
पूर्ण

अटल व्योम bnx2x_init_eq_ring(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;
	क्रम (i = 1; i <= NUM_EQ_PAGES; i++) अणु
		जोड़ event_ring_elem *elem =
			&bp->eq_ring[EQ_DESC_CNT_PAGE * i - 1];

		elem->next_page.addr.hi =
			cpu_to_le32(U64_HI(bp->eq_mapping +
				   BCM_PAGE_SIZE * (i % NUM_EQ_PAGES)));
		elem->next_page.addr.lo =
			cpu_to_le32(U64_LO(bp->eq_mapping +
				   BCM_PAGE_SIZE*(i % NUM_EQ_PAGES)));
	पूर्ण
	bp->eq_cons = 0;
	bp->eq_prod = NUM_EQ_DESC;
	bp->eq_cons_sb = BNX2X_EQ_INDEX;
	/* we want a warning message beक्रमe it माला_लो wrought... */
	atomic_set(&bp->eq_spq_left,
		min_t(पूर्णांक, MAX_SP_DESC_CNT - MAX_SPQ_PENDING, NUM_EQ_DESC) - 1);
पूर्ण

/* called with netअगर_addr_lock_bh() */
अटल पूर्णांक bnx2x_set_q_rx_mode(काष्ठा bnx2x *bp, u8 cl_id,
			       अचिन्हित दीर्घ rx_mode_flags,
			       अचिन्हित दीर्घ rx_accept_flags,
			       अचिन्हित दीर्घ tx_accept_flags,
			       अचिन्हित दीर्घ ramrod_flags)
अणु
	काष्ठा bnx2x_rx_mode_ramrod_params ramrod_param;
	पूर्णांक rc;

	स_रखो(&ramrod_param, 0, माप(ramrod_param));

	/* Prepare ramrod parameters */
	ramrod_param.cid = 0;
	ramrod_param.cl_id = cl_id;
	ramrod_param.rx_mode_obj = &bp->rx_mode_obj;
	ramrod_param.func_id = BP_FUNC(bp);

	ramrod_param.pstate = &bp->sp_state;
	ramrod_param.state = BNX2X_FILTER_RX_MODE_PENDING;

	ramrod_param.rdata = bnx2x_sp(bp, rx_mode_rdata);
	ramrod_param.rdata_mapping = bnx2x_sp_mapping(bp, rx_mode_rdata);

	set_bit(BNX2X_FILTER_RX_MODE_PENDING, &bp->sp_state);

	ramrod_param.ramrod_flags = ramrod_flags;
	ramrod_param.rx_mode_flags = rx_mode_flags;

	ramrod_param.rx_accept_flags = rx_accept_flags;
	ramrod_param.tx_accept_flags = tx_accept_flags;

	rc = bnx2x_config_rx_mode(bp, &ramrod_param);
	अगर (rc < 0) अणु
		BNX2X_ERR("Set rx_mode %d failed\n", bp->rx_mode);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_fill_accept_flags(काष्ठा bnx2x *bp, u32 rx_mode,
				   अचिन्हित दीर्घ *rx_accept_flags,
				   अचिन्हित दीर्घ *tx_accept_flags)
अणु
	/* Clear the flags first */
	*rx_accept_flags = 0;
	*tx_accept_flags = 0;

	चयन (rx_mode) अणु
	हाल BNX2X_RX_MODE_NONE:
		/*
		 * 'drop all' supersedes any accept flags that may have been
		 * passed to the function.
		 */
		अवरोध;
	हाल BNX2X_RX_MODE_NORMAL:
		__set_bit(BNX2X_ACCEPT_UNICAST, rx_accept_flags);
		__set_bit(BNX2X_ACCEPT_MULTICAST, rx_accept_flags);
		__set_bit(BNX2X_ACCEPT_BROADCAST, rx_accept_flags);

		/* पूर्णांकernal चयनing mode */
		__set_bit(BNX2X_ACCEPT_UNICAST, tx_accept_flags);
		__set_bit(BNX2X_ACCEPT_MULTICAST, tx_accept_flags);
		__set_bit(BNX2X_ACCEPT_BROADCAST, tx_accept_flags);

		अगर (bp->accept_any_vlan) अणु
			__set_bit(BNX2X_ACCEPT_ANY_VLAN, rx_accept_flags);
			__set_bit(BNX2X_ACCEPT_ANY_VLAN, tx_accept_flags);
		पूर्ण

		अवरोध;
	हाल BNX2X_RX_MODE_ALLMULTI:
		__set_bit(BNX2X_ACCEPT_UNICAST, rx_accept_flags);
		__set_bit(BNX2X_ACCEPT_ALL_MULTICAST, rx_accept_flags);
		__set_bit(BNX2X_ACCEPT_BROADCAST, rx_accept_flags);

		/* पूर्णांकernal चयनing mode */
		__set_bit(BNX2X_ACCEPT_UNICAST, tx_accept_flags);
		__set_bit(BNX2X_ACCEPT_ALL_MULTICAST, tx_accept_flags);
		__set_bit(BNX2X_ACCEPT_BROADCAST, tx_accept_flags);

		अगर (bp->accept_any_vlan) अणु
			__set_bit(BNX2X_ACCEPT_ANY_VLAN, rx_accept_flags);
			__set_bit(BNX2X_ACCEPT_ANY_VLAN, tx_accept_flags);
		पूर्ण

		अवरोध;
	हाल BNX2X_RX_MODE_PROMISC:
		/* According to definition of SI mode, अगरace in promisc mode
		 * should receive matched and unmatched (in resolution of port)
		 * unicast packets.
		 */
		__set_bit(BNX2X_ACCEPT_UNMATCHED, rx_accept_flags);
		__set_bit(BNX2X_ACCEPT_UNICAST, rx_accept_flags);
		__set_bit(BNX2X_ACCEPT_ALL_MULTICAST, rx_accept_flags);
		__set_bit(BNX2X_ACCEPT_BROADCAST, rx_accept_flags);

		/* पूर्णांकernal चयनing mode */
		__set_bit(BNX2X_ACCEPT_ALL_MULTICAST, tx_accept_flags);
		__set_bit(BNX2X_ACCEPT_BROADCAST, tx_accept_flags);

		अगर (IS_MF_SI(bp))
			__set_bit(BNX2X_ACCEPT_ALL_UNICAST, tx_accept_flags);
		अन्यथा
			__set_bit(BNX2X_ACCEPT_UNICAST, tx_accept_flags);

		__set_bit(BNX2X_ACCEPT_ANY_VLAN, rx_accept_flags);
		__set_bit(BNX2X_ACCEPT_ANY_VLAN, tx_accept_flags);

		अवरोध;
	शेष:
		BNX2X_ERR("Unknown rx_mode: %d\n", rx_mode);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* called with netअगर_addr_lock_bh() */
अटल पूर्णांक bnx2x_set_storm_rx_mode(काष्ठा bnx2x *bp)
अणु
	अचिन्हित दीर्घ rx_mode_flags = 0, ramrod_flags = 0;
	अचिन्हित दीर्घ rx_accept_flags = 0, tx_accept_flags = 0;
	पूर्णांक rc;

	अगर (!NO_FCOE(bp))
		/* Configure rx_mode of FCoE Queue */
		__set_bit(BNX2X_RX_MODE_FCOE_ETH, &rx_mode_flags);

	rc = bnx2x_fill_accept_flags(bp, bp->rx_mode, &rx_accept_flags,
				     &tx_accept_flags);
	अगर (rc)
		वापस rc;

	__set_bit(RAMROD_RX, &ramrod_flags);
	__set_bit(RAMROD_TX, &ramrod_flags);

	वापस bnx2x_set_q_rx_mode(bp, bp->fp->cl_id, rx_mode_flags,
				   rx_accept_flags, tx_accept_flags,
				   ramrod_flags);
पूर्ण

अटल व्योम bnx2x_init_पूर्णांकernal_common(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;

	/* Zero this manually as its initialization is
	   currently missing in the initTool */
	क्रम (i = 0; i < (USTORM_AGG_DATA_SIZE >> 2); i++)
		REG_WR(bp, BAR_USTRORM_INTMEM +
		       USTORM_AGG_DATA_OFFSET + i * 4, 0);
	अगर (!CHIP_IS_E1x(bp)) अणु
		REG_WR8(bp, BAR_CSTRORM_INTMEM + CSTORM_IGU_MODE_OFFSET,
			CHIP_INT_MODE_IS_BC(bp) ?
			HC_IGU_BC_MODE : HC_IGU_NBC_MODE);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_init_पूर्णांकernal(काष्ठा bnx2x *bp, u32 load_code)
अणु
	चयन (load_code) अणु
	हाल FW_MSG_CODE_DRV_LOAD_COMMON:
	हाल FW_MSG_CODE_DRV_LOAD_COMMON_CHIP:
		bnx2x_init_पूर्णांकernal_common(bp);
		fallthrough;

	हाल FW_MSG_CODE_DRV_LOAD_PORT:
		/* nothing to करो */
		fallthrough;

	हाल FW_MSG_CODE_DRV_LOAD_FUNCTION:
		/* पूर्णांकernal memory per function is
		   initialized inside bnx2x_pf_init */
		अवरोध;

	शेष:
		BNX2X_ERR("Unknown load_code (0x%x) from MCP\n", load_code);
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत u8 bnx2x_fp_igu_sb_id(काष्ठा bnx2x_fastpath *fp)
अणु
	वापस fp->bp->igu_base_sb + fp->index + CNIC_SUPPORT(fp->bp);
पूर्ण

अटल अंतरभूत u8 bnx2x_fp_fw_sb_id(काष्ठा bnx2x_fastpath *fp)
अणु
	वापस fp->bp->base_fw_ndsb + fp->index + CNIC_SUPPORT(fp->bp);
पूर्ण

अटल u8 bnx2x_fp_cl_id(काष्ठा bnx2x_fastpath *fp)
अणु
	अगर (CHIP_IS_E1x(fp->bp))
		वापस BP_L_ID(fp->bp) + fp->index;
	अन्यथा	/* We want Client ID to be the same as IGU SB ID क्रम 57712 */
		वापस bnx2x_fp_igu_sb_id(fp);
पूर्ण

अटल व्योम bnx2x_init_eth_fp(काष्ठा bnx2x *bp, पूर्णांक fp_idx)
अणु
	काष्ठा bnx2x_fastpath *fp = &bp->fp[fp_idx];
	u8 cos;
	अचिन्हित दीर्घ q_type = 0;
	u32 cids[BNX2X_MULTI_TX_COS] = अणु 0 पूर्ण;
	fp->rx_queue = fp_idx;
	fp->cid = fp_idx;
	fp->cl_id = bnx2x_fp_cl_id(fp);
	fp->fw_sb_id = bnx2x_fp_fw_sb_id(fp);
	fp->igu_sb_id = bnx2x_fp_igu_sb_id(fp);
	/* qZone id equals to FW (per path) client id */
	fp->cl_qzone_id  = bnx2x_fp_qzone_id(fp);

	/* init लघुcut */
	fp->ustorm_rx_prods_offset = bnx2x_rx_ustorm_prods_offset(fp);

	/* Setup SB indices */
	fp->rx_cons_sb = BNX2X_RX_SB_INDEX;

	/* Configure Queue State object */
	__set_bit(BNX2X_Q_TYPE_HAS_RX, &q_type);
	__set_bit(BNX2X_Q_TYPE_HAS_TX, &q_type);

	BUG_ON(fp->max_cos > BNX2X_MULTI_TX_COS);

	/* init tx data */
	क्रम_each_cos_in_tx_queue(fp, cos) अणु
		bnx2x_init_txdata(bp, fp->txdata_ptr[cos],
				  CID_COS_TO_TX_ONLY_CID(fp->cid, cos, bp),
				  FP_COS_TO_TXQ(fp, cos, bp),
				  BNX2X_TX_SB_INDEX_BASE + cos, fp);
		cids[cos] = fp->txdata_ptr[cos]->cid;
	पूर्ण

	/* nothing more क्रम vf to करो here */
	अगर (IS_VF(bp))
		वापस;

	bnx2x_init_sb(bp, fp->status_blk_mapping, BNX2X_VF_ID_INVALID, false,
		      fp->fw_sb_id, fp->igu_sb_id);
	bnx2x_update_fpsb_idx(fp);
	bnx2x_init_queue_obj(bp, &bnx2x_sp_obj(bp, fp).q_obj, fp->cl_id, cids,
			     fp->max_cos, BP_FUNC(bp), bnx2x_sp(bp, q_rdata),
			     bnx2x_sp_mapping(bp, q_rdata), q_type);

	/**
	 * Configure classअगरication DBs: Always enable Tx चयनing
	 */
	bnx2x_init_vlan_mac_fp_objs(fp, BNX2X_OBJ_TYPE_RX_TX);

	DP(NETIF_MSG_IFUP,
	   "queue[%d]:  bnx2x_init_sb(%p,%p)  cl_id %d  fw_sb %d  igu_sb %d\n",
	   fp_idx, bp, fp->status_blk.e2_sb, fp->cl_id, fp->fw_sb_id,
	   fp->igu_sb_id);
पूर्ण

अटल व्योम bnx2x_init_tx_ring_one(काष्ठा bnx2x_fp_txdata *txdata)
अणु
	पूर्णांक i;

	क्रम (i = 1; i <= NUM_TX_RINGS; i++) अणु
		काष्ठा eth_tx_next_bd *tx_next_bd =
			&txdata->tx_desc_ring[TX_DESC_CNT * i - 1].next_bd;

		tx_next_bd->addr_hi =
			cpu_to_le32(U64_HI(txdata->tx_desc_mapping +
				    BCM_PAGE_SIZE*(i % NUM_TX_RINGS)));
		tx_next_bd->addr_lo =
			cpu_to_le32(U64_LO(txdata->tx_desc_mapping +
				    BCM_PAGE_SIZE*(i % NUM_TX_RINGS)));
	पूर्ण

	*txdata->tx_cons_sb = cpu_to_le16(0);

	SET_FLAG(txdata->tx_db.data.header.header, DOORBELL_HDR_DB_TYPE, 1);
	txdata->tx_db.data.zero_fill1 = 0;
	txdata->tx_db.data.prod = 0;

	txdata->tx_pkt_prod = 0;
	txdata->tx_pkt_cons = 0;
	txdata->tx_bd_prod = 0;
	txdata->tx_bd_cons = 0;
	txdata->tx_pkt = 0;
पूर्ण

अटल व्योम bnx2x_init_tx_rings_cnic(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;

	क्रम_each_tx_queue_cnic(bp, i)
		bnx2x_init_tx_ring_one(bp->fp[i].txdata_ptr[0]);
पूर्ण

अटल व्योम bnx2x_init_tx_rings(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;
	u8 cos;

	क्रम_each_eth_queue(bp, i)
		क्रम_each_cos_in_tx_queue(&bp->fp[i], cos)
			bnx2x_init_tx_ring_one(bp->fp[i].txdata_ptr[cos]);
पूर्ण

अटल व्योम bnx2x_init_fcoe_fp(काष्ठा bnx2x *bp)
अणु
	काष्ठा bnx2x_fastpath *fp = bnx2x_fcoe_fp(bp);
	अचिन्हित दीर्घ q_type = 0;

	bnx2x_fcoe(bp, rx_queue) = BNX2X_NUM_ETH_QUEUES(bp);
	bnx2x_fcoe(bp, cl_id) = bnx2x_cnic_eth_cl_id(bp,
						     BNX2X_FCOE_ETH_CL_ID_IDX);
	bnx2x_fcoe(bp, cid) = BNX2X_FCOE_ETH_CID(bp);
	bnx2x_fcoe(bp, fw_sb_id) = DEF_SB_ID;
	bnx2x_fcoe(bp, igu_sb_id) = bp->igu_dsb_id;
	bnx2x_fcoe(bp, rx_cons_sb) = BNX2X_FCOE_L2_RX_INDEX;
	bnx2x_init_txdata(bp, bnx2x_fcoe(bp, txdata_ptr[0]),
			  fp->cid, FCOE_TXQ_IDX(bp), BNX2X_FCOE_L2_TX_INDEX,
			  fp);

	DP(NETIF_MSG_IFUP, "created fcoe tx data (fp index %d)\n", fp->index);

	/* qZone id equals to FW (per path) client id */
	bnx2x_fcoe(bp, cl_qzone_id) = bnx2x_fp_qzone_id(fp);
	/* init लघुcut */
	bnx2x_fcoe(bp, ustorm_rx_prods_offset) =
		bnx2x_rx_ustorm_prods_offset(fp);

	/* Configure Queue State object */
	__set_bit(BNX2X_Q_TYPE_HAS_RX, &q_type);
	__set_bit(BNX2X_Q_TYPE_HAS_TX, &q_type);

	/* No multi-CoS क्रम FCoE L2 client */
	BUG_ON(fp->max_cos != 1);

	bnx2x_init_queue_obj(bp, &bnx2x_sp_obj(bp, fp).q_obj, fp->cl_id,
			     &fp->cid, 1, BP_FUNC(bp), bnx2x_sp(bp, q_rdata),
			     bnx2x_sp_mapping(bp, q_rdata), q_type);

	DP(NETIF_MSG_IFUP,
	   "queue[%d]: bnx2x_init_sb(%p,%p) cl_id %d fw_sb %d igu_sb %d\n",
	   fp->index, bp, fp->status_blk.e2_sb, fp->cl_id, fp->fw_sb_id,
	   fp->igu_sb_id);
पूर्ण

व्योम bnx2x_nic_init_cnic(काष्ठा bnx2x *bp)
अणु
	अगर (!NO_FCOE(bp))
		bnx2x_init_fcoe_fp(bp);

	bnx2x_init_sb(bp, bp->cnic_sb_mapping,
		      BNX2X_VF_ID_INVALID, false,
		      bnx2x_cnic_fw_sb_id(bp), bnx2x_cnic_igu_sb_id(bp));

	/* ensure status block indices were पढ़ो */
	rmb();
	bnx2x_init_rx_rings_cnic(bp);
	bnx2x_init_tx_rings_cnic(bp);

	/* flush all */
	mb();
पूर्ण

व्योम bnx2x_pre_irq_nic_init(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;

	/* Setup NIC पूर्णांकernals and enable पूर्णांकerrupts */
	क्रम_each_eth_queue(bp, i)
		bnx2x_init_eth_fp(bp, i);

	/* ensure status block indices were पढ़ो */
	rmb();
	bnx2x_init_rx_rings(bp);
	bnx2x_init_tx_rings(bp);

	अगर (IS_PF(bp)) अणु
		/* Initialize MOD_ABS पूर्णांकerrupts */
		bnx2x_init_mod_असल_पूर्णांक(bp, &bp->link_vars, bp->common.chip_id,
				       bp->common.shmem_base,
				       bp->common.shmem2_base, BP_PORT(bp));

		/* initialize the शेष status block and sp ring */
		bnx2x_init_def_sb(bp);
		bnx2x_update_dsb_idx(bp);
		bnx2x_init_sp_ring(bp);
	पूर्ण अन्यथा अणु
		bnx2x_स_रखो_stats(bp);
	पूर्ण
पूर्ण

व्योम bnx2x_post_irq_nic_init(काष्ठा bnx2x *bp, u32 load_code)
अणु
	bnx2x_init_eq_ring(bp);
	bnx2x_init_पूर्णांकernal(bp, load_code);
	bnx2x_pf_init(bp);
	bnx2x_stats_init(bp);

	/* flush all beक्रमe enabling पूर्णांकerrupts */
	mb();

	bnx2x_पूर्णांक_enable(bp);

	/* Check क्रम SPIO5 */
	bnx2x_attn_पूर्णांक_deनिश्चितed0(bp,
		REG_RD(bp, MISC_REG_AEU_AFTER_INVERT_1_FUNC_0 + BP_PORT(bp)*4) &
				   AEU_INPUTS_ATTN_BITS_SPIO5);
पूर्ण

/* gzip service functions */
अटल पूर्णांक bnx2x_gunzip_init(काष्ठा bnx2x *bp)
अणु
	bp->gunzip_buf = dma_alloc_coherent(&bp->pdev->dev, FW_BUF_SIZE,
					    &bp->gunzip_mapping, GFP_KERNEL);
	अगर (bp->gunzip_buf  == शून्य)
		जाओ gunzip_nomem1;

	bp->strm = kदो_स्मृति(माप(*bp->strm), GFP_KERNEL);
	अगर (bp->strm  == शून्य)
		जाओ gunzip_nomem2;

	bp->strm->workspace = vदो_स्मृति(zlib_inflate_workspacesize());
	अगर (bp->strm->workspace == शून्य)
		जाओ gunzip_nomem3;

	वापस 0;

gunzip_nomem3:
	kमुक्त(bp->strm);
	bp->strm = शून्य;

gunzip_nomem2:
	dma_मुक्त_coherent(&bp->pdev->dev, FW_BUF_SIZE, bp->gunzip_buf,
			  bp->gunzip_mapping);
	bp->gunzip_buf = शून्य;

gunzip_nomem1:
	BNX2X_ERR("Cannot allocate firmware buffer for un-compression\n");
	वापस -ENOMEM;
पूर्ण

अटल व्योम bnx2x_gunzip_end(काष्ठा bnx2x *bp)
अणु
	अगर (bp->strm) अणु
		vमुक्त(bp->strm->workspace);
		kमुक्त(bp->strm);
		bp->strm = शून्य;
	पूर्ण

	अगर (bp->gunzip_buf) अणु
		dma_मुक्त_coherent(&bp->pdev->dev, FW_BUF_SIZE, bp->gunzip_buf,
				  bp->gunzip_mapping);
		bp->gunzip_buf = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_gunzip(काष्ठा bnx2x *bp, स्थिर u8 *zbuf, पूर्णांक len)
अणु
	पूर्णांक n, rc;

	/* check gzip header */
	अगर ((zbuf[0] != 0x1f) || (zbuf[1] != 0x8b) || (zbuf[2] != Z_DEFLATED)) अणु
		BNX2X_ERR("Bad gzip header\n");
		वापस -EINVAL;
	पूर्ण

	n = 10;

#घोषणा FNAME				0x8

	अगर (zbuf[3] & FNAME)
		जबतक ((zbuf[n++] != 0) && (n < len));

	bp->strm->next_in = (typeof(bp->strm->next_in))zbuf + n;
	bp->strm->avail_in = len - n;
	bp->strm->next_out = bp->gunzip_buf;
	bp->strm->avail_out = FW_BUF_SIZE;

	rc = zlib_inflateInit2(bp->strm, -MAX_WBITS);
	अगर (rc != Z_OK)
		वापस rc;

	rc = zlib_inflate(bp->strm, Z_FINISH);
	अगर ((rc != Z_OK) && (rc != Z_STREAM_END))
		netdev_err(bp->dev, "Firmware decompression error: %s\n",
			   bp->strm->msg);

	bp->gunzip_outlen = (FW_BUF_SIZE - bp->strm->avail_out);
	अगर (bp->gunzip_outlen & 0x3)
		netdev_err(bp->dev,
			   "Firmware decompression error: gunzip_outlen (%d) not aligned\n",
				bp->gunzip_outlen);
	bp->gunzip_outlen >>= 2;

	zlib_inflateEnd(bp->strm);

	अगर (rc == Z_STREAM_END)
		वापस 0;

	वापस rc;
पूर्ण

/* nic load/unload */

/*
 * General service functions
 */

/* send a NIG loopback debug packet */
अटल व्योम bnx2x_lb_pckt(काष्ठा bnx2x *bp)
अणु
	u32 wb_ग_लिखो[3];

	/* Ethernet source and destination addresses */
	wb_ग_लिखो[0] = 0x55555555;
	wb_ग_लिखो[1] = 0x55555555;
	wb_ग_लिखो[2] = 0x20;		/* SOP */
	REG_WR_DMAE(bp, NIG_REG_DEBUG_PACKET_LB, wb_ग_लिखो, 3);

	/* NON-IP protocol */
	wb_ग_लिखो[0] = 0x09000000;
	wb_ग_लिखो[1] = 0x55555555;
	wb_ग_लिखो[2] = 0x10;		/* EOP, eop_bvalid = 0 */
	REG_WR_DMAE(bp, NIG_REG_DEBUG_PACKET_LB, wb_ग_लिखो, 3);
पूर्ण

/* some of the पूर्णांकernal memories
 * are not directly पढ़ोable from the driver
 * to test them we send debug packets
 */
अटल पूर्णांक bnx2x_पूर्णांक_mem_test(काष्ठा bnx2x *bp)
अणु
	पूर्णांक factor;
	पूर्णांक count, i;
	u32 val = 0;

	अगर (CHIP_REV_IS_FPGA(bp))
		factor = 120;
	अन्यथा अगर (CHIP_REV_IS_EMUL(bp))
		factor = 200;
	अन्यथा
		factor = 1;

	/* Disable inमाला_दो of parser neighbor blocks */
	REG_WR(bp, TSDM_REG_ENABLE_IN1, 0x0);
	REG_WR(bp, TCM_REG_PRS_IFEN, 0x0);
	REG_WR(bp, CFC_REG_DEBUG0, 0x1);
	REG_WR(bp, NIG_REG_PRS_REQ_IN_EN, 0x0);

	/*  Write 0 to parser credits क्रम CFC search request */
	REG_WR(bp, PRS_REG_CFC_SEARCH_INITIAL_CREDIT, 0x0);

	/* send Ethernet packet */
	bnx2x_lb_pckt(bp);

	/* TODO करो i reset NIG statistic? */
	/* Wait until NIG रेजिस्टर shows 1 packet of size 0x10 */
	count = 1000 * factor;
	जबतक (count) अणु

		bnx2x_पढ़ो_dmae(bp, NIG_REG_STAT2_BRB_OCTET, 2);
		val = *bnx2x_sp(bp, wb_data[0]);
		अगर (val == 0x10)
			अवरोध;

		usleep_range(10000, 20000);
		count--;
	पूर्ण
	अगर (val != 0x10) अणु
		BNX2X_ERR("NIG timeout  val = 0x%x\n", val);
		वापस -1;
	पूर्ण

	/* Wait until PRS रेजिस्टर shows 1 packet */
	count = 1000 * factor;
	जबतक (count) अणु
		val = REG_RD(bp, PRS_REG_NUM_OF_PACKETS);
		अगर (val == 1)
			अवरोध;

		usleep_range(10000, 20000);
		count--;
	पूर्ण
	अगर (val != 0x1) अणु
		BNX2X_ERR("PRS timeout val = 0x%x\n", val);
		वापस -2;
	पूर्ण

	/* Reset and init BRB, PRS */
	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_1_CLEAR, 0x03);
	msleep(50);
	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_1_SET, 0x03);
	msleep(50);
	bnx2x_init_block(bp, BLOCK_BRB1, PHASE_COMMON);
	bnx2x_init_block(bp, BLOCK_PRS, PHASE_COMMON);

	DP(NETIF_MSG_HW, "part2\n");

	/* Disable inमाला_दो of parser neighbor blocks */
	REG_WR(bp, TSDM_REG_ENABLE_IN1, 0x0);
	REG_WR(bp, TCM_REG_PRS_IFEN, 0x0);
	REG_WR(bp, CFC_REG_DEBUG0, 0x1);
	REG_WR(bp, NIG_REG_PRS_REQ_IN_EN, 0x0);

	/* Write 0 to parser credits क्रम CFC search request */
	REG_WR(bp, PRS_REG_CFC_SEARCH_INITIAL_CREDIT, 0x0);

	/* send 10 Ethernet packets */
	क्रम (i = 0; i < 10; i++)
		bnx2x_lb_pckt(bp);

	/* Wait until NIG रेजिस्टर shows 10 + 1
	   packets of size 11*0x10 = 0xb0 */
	count = 1000 * factor;
	जबतक (count) अणु

		bnx2x_पढ़ो_dmae(bp, NIG_REG_STAT2_BRB_OCTET, 2);
		val = *bnx2x_sp(bp, wb_data[0]);
		अगर (val == 0xb0)
			अवरोध;

		usleep_range(10000, 20000);
		count--;
	पूर्ण
	अगर (val != 0xb0) अणु
		BNX2X_ERR("NIG timeout  val = 0x%x\n", val);
		वापस -3;
	पूर्ण

	/* Wait until PRS रेजिस्टर shows 2 packets */
	val = REG_RD(bp, PRS_REG_NUM_OF_PACKETS);
	अगर (val != 2)
		BNX2X_ERR("PRS timeout  val = 0x%x\n", val);

	/* Write 1 to parser credits क्रम CFC search request */
	REG_WR(bp, PRS_REG_CFC_SEARCH_INITIAL_CREDIT, 0x1);

	/* Wait until PRS रेजिस्टर shows 3 packets */
	msleep(10 * factor);
	/* Wait until NIG रेजिस्टर shows 1 packet of size 0x10 */
	val = REG_RD(bp, PRS_REG_NUM_OF_PACKETS);
	अगर (val != 3)
		BNX2X_ERR("PRS timeout  val = 0x%x\n", val);

	/* clear NIG EOP FIFO */
	क्रम (i = 0; i < 11; i++)
		REG_RD(bp, NIG_REG_INGRESS_EOP_LB_FIFO);
	val = REG_RD(bp, NIG_REG_INGRESS_EOP_LB_EMPTY);
	अगर (val != 1) अणु
		BNX2X_ERR("clear of NIG failed\n");
		वापस -4;
	पूर्ण

	/* Reset and init BRB, PRS, NIG */
	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_1_CLEAR, 0x03);
	msleep(50);
	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_1_SET, 0x03);
	msleep(50);
	bnx2x_init_block(bp, BLOCK_BRB1, PHASE_COMMON);
	bnx2x_init_block(bp, BLOCK_PRS, PHASE_COMMON);
	अगर (!CNIC_SUPPORT(bp))
		/* set NIC mode */
		REG_WR(bp, PRS_REG_NIC_MODE, 1);

	/* Enable inमाला_दो of parser neighbor blocks */
	REG_WR(bp, TSDM_REG_ENABLE_IN1, 0x7fffffff);
	REG_WR(bp, TCM_REG_PRS_IFEN, 0x1);
	REG_WR(bp, CFC_REG_DEBUG0, 0x0);
	REG_WR(bp, NIG_REG_PRS_REQ_IN_EN, 0x1);

	DP(NETIF_MSG_HW, "done\n");

	वापस 0; /* OK */
पूर्ण

अटल व्योम bnx2x_enable_blocks_attention(काष्ठा bnx2x *bp)
अणु
	u32 val;

	REG_WR(bp, PXP_REG_PXP_INT_MASK_0, 0);
	अगर (!CHIP_IS_E1x(bp))
		REG_WR(bp, PXP_REG_PXP_INT_MASK_1, 0x40);
	अन्यथा
		REG_WR(bp, PXP_REG_PXP_INT_MASK_1, 0);
	REG_WR(bp, DORQ_REG_DORQ_INT_MASK, 0);
	REG_WR(bp, CFC_REG_CFC_INT_MASK, 0);
	/*
	 * mask पढ़ो length error पूर्णांकerrupts in brb क्रम parser
	 * (parsing unit and 'checksum and crc' unit)
	 * these errors are legal (PU पढ़ोs fixed length and CAC can cause
	 * पढ़ो length error on truncated packets)
	 */
	REG_WR(bp, BRB1_REG_BRB1_INT_MASK, 0xFC00);
	REG_WR(bp, QM_REG_QM_INT_MASK, 0);
	REG_WR(bp, TM_REG_TM_INT_MASK, 0);
	REG_WR(bp, XSDM_REG_XSDM_INT_MASK_0, 0);
	REG_WR(bp, XSDM_REG_XSDM_INT_MASK_1, 0);
	REG_WR(bp, XCM_REG_XCM_INT_MASK, 0);
/*	REG_WR(bp, XSEM_REG_XSEM_INT_MASK_0, 0); */
/*	REG_WR(bp, XSEM_REG_XSEM_INT_MASK_1, 0); */
	REG_WR(bp, USDM_REG_USDM_INT_MASK_0, 0);
	REG_WR(bp, USDM_REG_USDM_INT_MASK_1, 0);
	REG_WR(bp, UCM_REG_UCM_INT_MASK, 0);
/*	REG_WR(bp, USEM_REG_USEM_INT_MASK_0, 0); */
/*	REG_WR(bp, USEM_REG_USEM_INT_MASK_1, 0); */
	REG_WR(bp, GRCBASE_UPB + PB_REG_PB_INT_MASK, 0);
	REG_WR(bp, CSDM_REG_CSDM_INT_MASK_0, 0);
	REG_WR(bp, CSDM_REG_CSDM_INT_MASK_1, 0);
	REG_WR(bp, CCM_REG_CCM_INT_MASK, 0);
/*	REG_WR(bp, CSEM_REG_CSEM_INT_MASK_0, 0); */
/*	REG_WR(bp, CSEM_REG_CSEM_INT_MASK_1, 0); */

	val = PXP2_PXP2_INT_MASK_0_REG_PGL_CPL_AFT  |
		PXP2_PXP2_INT_MASK_0_REG_PGL_CPL_OF |
		PXP2_PXP2_INT_MASK_0_REG_PGL_PCIE_ATTN;
	अगर (!CHIP_IS_E1x(bp))
		val |= PXP2_PXP2_INT_MASK_0_REG_PGL_READ_BLOCKED |
			PXP2_PXP2_INT_MASK_0_REG_PGL_WRITE_BLOCKED;
	REG_WR(bp, PXP2_REG_PXP2_INT_MASK_0, val);

	REG_WR(bp, TSDM_REG_TSDM_INT_MASK_0, 0);
	REG_WR(bp, TSDM_REG_TSDM_INT_MASK_1, 0);
	REG_WR(bp, TCM_REG_TCM_INT_MASK, 0);
/*	REG_WR(bp, TSEM_REG_TSEM_INT_MASK_0, 0); */

	अगर (!CHIP_IS_E1x(bp))
		/* enable VFC attentions: bits 11 and 12, bits 31:13 reserved */
		REG_WR(bp, TSEM_REG_TSEM_INT_MASK_1, 0x07ff);

	REG_WR(bp, CDU_REG_CDU_INT_MASK, 0);
	REG_WR(bp, DMAE_REG_DMAE_INT_MASK, 0);
/*	REG_WR(bp, MISC_REG_MISC_INT_MASK, 0); */
	REG_WR(bp, PBF_REG_PBF_INT_MASK, 0x18);		/* bit 3,4 masked */
पूर्ण

अटल व्योम bnx2x_reset_common(काष्ठा bnx2x *bp)
अणु
	u32 val = 0x1400;

	/* reset_common */
	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_1_CLEAR,
	       0xd3ffff7f);

	अगर (CHIP_IS_E3(bp)) अणु
		val |= MISC_REGISTERS_RESET_REG_2_MSTAT0;
		val |= MISC_REGISTERS_RESET_REG_2_MSTAT1;
	पूर्ण

	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_2_CLEAR, val);
पूर्ण

अटल व्योम bnx2x_setup_dmae(काष्ठा bnx2x *bp)
अणु
	bp->dmae_पढ़ोy = 0;
	spin_lock_init(&bp->dmae_lock);
पूर्ण

अटल व्योम bnx2x_init_pxp(काष्ठा bnx2x *bp)
अणु
	u16 devctl;
	पूर्णांक r_order, w_order;

	pcie_capability_पढ़ो_word(bp->pdev, PCI_EXP_DEVCTL, &devctl);
	DP(NETIF_MSG_HW, "read 0x%x from devctl\n", devctl);
	w_order = ((devctl & PCI_EXP_DEVCTL_PAYLOAD) >> 5);
	अगर (bp->mrrs == -1)
		r_order = ((devctl & PCI_EXP_DEVCTL_READRQ) >> 12);
	अन्यथा अणु
		DP(NETIF_MSG_HW, "force read order to %d\n", bp->mrrs);
		r_order = bp->mrrs;
	पूर्ण

	bnx2x_init_pxp_arb(bp, r_order, w_order);
पूर्ण

अटल व्योम bnx2x_setup_fan_failure_detection(काष्ठा bnx2x *bp)
अणु
	पूर्णांक is_required;
	u32 val;
	पूर्णांक port;

	अगर (BP_NOMCP(bp))
		वापस;

	is_required = 0;
	val = SHMEM_RD(bp, dev_info.shared_hw_config.config2) &
	      SHARED_HW_CFG_FAN_FAILURE_MASK;

	अगर (val == SHARED_HW_CFG_FAN_FAILURE_ENABLED)
		is_required = 1;

	/*
	 * The fan failure mechanism is usually related to the PHY type since
	 * the घातer consumption of the board is affected by the PHY. Currently,
	 * fan is required क्रम most designs with SFX7101, BCM8727 and BCM8481.
	 */
	अन्यथा अगर (val == SHARED_HW_CFG_FAN_FAILURE_PHY_TYPE)
		क्रम (port = PORT_0; port < PORT_MAX; port++) अणु
			is_required |=
				bnx2x_fan_failure_det_req(
					bp,
					bp->common.shmem_base,
					bp->common.shmem2_base,
					port);
		पूर्ण

	DP(NETIF_MSG_HW, "fan detection setting: %d\n", is_required);

	अगर (is_required == 0)
		वापस;

	/* Fan failure is indicated by SPIO 5 */
	bnx2x_set_spio(bp, MISC_SPIO_SPIO5, MISC_SPIO_INPUT_HI_Z);

	/* set to active low mode */
	val = REG_RD(bp, MISC_REG_SPIO_INT);
	val |= (MISC_SPIO_SPIO5 << MISC_SPIO_INT_OLD_SET_POS);
	REG_WR(bp, MISC_REG_SPIO_INT, val);

	/* enable पूर्णांकerrupt to संकेत the IGU */
	val = REG_RD(bp, MISC_REG_SPIO_EVENT_EN);
	val |= MISC_SPIO_SPIO5;
	REG_WR(bp, MISC_REG_SPIO_EVENT_EN, val);
पूर्ण

व्योम bnx2x_pf_disable(काष्ठा bnx2x *bp)
अणु
	u32 val = REG_RD(bp, IGU_REG_PF_CONFIGURATION);
	val &= ~IGU_PF_CONF_FUNC_EN;

	REG_WR(bp, IGU_REG_PF_CONFIGURATION, val);
	REG_WR(bp, PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER, 0);
	REG_WR(bp, CFC_REG_WEAK_ENABLE_PF, 0);
पूर्ण

अटल व्योम bnx2x__common_init_phy(काष्ठा bnx2x *bp)
अणु
	u32 shmem_base[2], shmem2_base[2];
	/* Aव्योम common init in हाल MFW supports LFA */
	अगर (SHMEM2_RD(bp, size) >
	    (u32)दुरत्व(काष्ठा shmem2_region, lfa_host_addr[BP_PORT(bp)]))
		वापस;
	shmem_base[0] =  bp->common.shmem_base;
	shmem2_base[0] = bp->common.shmem2_base;
	अगर (!CHIP_IS_E1x(bp)) अणु
		shmem_base[1] =
			SHMEM2_RD(bp, other_shmem_base_addr);
		shmem2_base[1] =
			SHMEM2_RD(bp, other_shmem2_base_addr);
	पूर्ण
	bnx2x_acquire_phy_lock(bp);
	bnx2x_common_init_phy(bp, shmem_base, shmem2_base,
			      bp->common.chip_id);
	bnx2x_release_phy_lock(bp);
पूर्ण

अटल व्योम bnx2x_config_endianity(काष्ठा bnx2x *bp, u32 val)
अणु
	REG_WR(bp, PXP2_REG_RQ_QM_ENDIAN_M, val);
	REG_WR(bp, PXP2_REG_RQ_TM_ENDIAN_M, val);
	REG_WR(bp, PXP2_REG_RQ_SRC_ENDIAN_M, val);
	REG_WR(bp, PXP2_REG_RQ_CDU_ENDIAN_M, val);
	REG_WR(bp, PXP2_REG_RQ_DBG_ENDIAN_M, val);

	/* make sure this value is 0 */
	REG_WR(bp, PXP2_REG_RQ_HC_ENDIAN_M, 0);

	REG_WR(bp, PXP2_REG_RD_QM_SWAP_MODE, val);
	REG_WR(bp, PXP2_REG_RD_TM_SWAP_MODE, val);
	REG_WR(bp, PXP2_REG_RD_SRC_SWAP_MODE, val);
	REG_WR(bp, PXP2_REG_RD_CDURD_SWAP_MODE, val);
पूर्ण

अटल व्योम bnx2x_set_endianity(काष्ठा bnx2x *bp)
अणु
#अगर_घोषित __BIG_ENDIAN
	bnx2x_config_endianity(bp, 1);
#अन्यथा
	bnx2x_config_endianity(bp, 0);
#पूर्ण_अगर
पूर्ण

अटल व्योम bnx2x_reset_endianity(काष्ठा bnx2x *bp)
अणु
	bnx2x_config_endianity(bp, 0);
पूर्ण

/**
 * bnx2x_init_hw_common - initialize the HW at the COMMON phase.
 *
 * @bp:		driver handle
 */
अटल पूर्णांक bnx2x_init_hw_common(काष्ठा bnx2x *bp)
अणु
	u32 val;

	DP(NETIF_MSG_HW, "starting common init  func %d\n", BP_ABS_FUNC(bp));

	/*
	 * take the RESET lock to protect undi_unload flow from accessing
	 * रेजिस्टरs जबतक we're resetting the chip
	 */
	bnx2x_acquire_hw_lock(bp, HW_LOCK_RESOURCE_RESET);

	bnx2x_reset_common(bp);
	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_1_SET, 0xffffffff);

	val = 0xfffc;
	अगर (CHIP_IS_E3(bp)) अणु
		val |= MISC_REGISTERS_RESET_REG_2_MSTAT0;
		val |= MISC_REGISTERS_RESET_REG_2_MSTAT1;
	पूर्ण
	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_2_SET, val);

	bnx2x_release_hw_lock(bp, HW_LOCK_RESOURCE_RESET);

	bnx2x_init_block(bp, BLOCK_MISC, PHASE_COMMON);

	अगर (!CHIP_IS_E1x(bp)) अणु
		u8 असल_func_id;

		/**
		 * 4-port mode or 2-port mode we need to turn of master-enable
		 * क्रम everyone, after that, turn it back on क्रम self.
		 * so, we disregard multi-function or not, and always disable
		 * क्रम all functions on the given path, this means 0,2,4,6 क्रम
		 * path 0 and 1,3,5,7 क्रम path 1
		 */
		क्रम (असल_func_id = BP_PATH(bp);
		     असल_func_id < E2_FUNC_MAX*2; असल_func_id += 2) अणु
			अगर (असल_func_id == BP_ABS_FUNC(bp)) अणु
				REG_WR(bp,
				    PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER,
				    1);
				जारी;
			पूर्ण

			bnx2x_pretend_func(bp, असल_func_id);
			/* clear pf enable */
			bnx2x_pf_disable(bp);
			bnx2x_pretend_func(bp, BP_ABS_FUNC(bp));
		पूर्ण
	पूर्ण

	bnx2x_init_block(bp, BLOCK_PXP, PHASE_COMMON);
	अगर (CHIP_IS_E1(bp)) अणु
		/* enable HW पूर्णांकerrupt from PXP on USDM overflow
		   bit 16 on INT_MASK_0 */
		REG_WR(bp, PXP_REG_PXP_INT_MASK_0, 0);
	पूर्ण

	bnx2x_init_block(bp, BLOCK_PXP2, PHASE_COMMON);
	bnx2x_init_pxp(bp);
	bnx2x_set_endianity(bp);
	bnx2x_ilt_init_page_size(bp, INITOP_SET);

	अगर (CHIP_REV_IS_FPGA(bp) && CHIP_IS_E1H(bp))
		REG_WR(bp, PXP2_REG_PGL_TAGS_LIMIT, 0x1);

	/* let the HW करो it's magic ... */
	msleep(100);
	/* finish PXP init */
	val = REG_RD(bp, PXP2_REG_RQ_CFG_DONE);
	अगर (val != 1) अणु
		BNX2X_ERR("PXP2 CFG failed\n");
		वापस -EBUSY;
	पूर्ण
	val = REG_RD(bp, PXP2_REG_RD_INIT_DONE);
	अगर (val != 1) अणु
		BNX2X_ERR("PXP2 RD_INIT failed\n");
		वापस -EBUSY;
	पूर्ण

	/* Timers bug workaround E2 only. We need to set the entire ILT to
	 * have entries with value "0" and valid bit on.
	 * This needs to be करोne by the first PF that is loaded in a path
	 * (i.e. common phase)
	 */
	अगर (!CHIP_IS_E1x(bp)) अणु
/* In E2 there is a bug in the समयrs block that can cause function 6 / 7
 * (i.e. vnic3) to start even अगर it is marked as "scan-off".
 * This occurs when a dअगरferent function (func2,3) is being marked
 * as "scan-off". Real-lअगरe scenario क्रम example: अगर a driver is being
 * load-unloaded जबतक func6,7 are करोwn. This will cause the समयr to access
 * the ilt, translate to a logical address and send a request to पढ़ो/ग_लिखो.
 * Since the ilt क्रम the function that is करोwn is not valid, this will cause
 * a translation error which is unrecoverable.
 * The Workaround is पूर्णांकended to make sure that when this happens nothing fatal
 * will occur. The workaround:
 *	1.  First PF driver which loads on a path will:
 *		a.  After taking the chip out of reset, by using pretend,
 *		    it will ग_लिखो "0" to the following रेजिस्टरs of
 *		    the other vnics.
 *		    REG_WR(pdev, PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER, 0);
 *		    REG_WR(pdev, CFC_REG_WEAK_ENABLE_PF,0);
 *		    REG_WR(pdev, CFC_REG_STRONG_ENABLE_PF,0);
 *		    And क्रम itself it will ग_लिखो '1' to
 *		    PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER to enable
 *		    dmae-operations (writing to pram क्रम example.)
 *		    note: can be करोne क्रम only function 6,7 but cleaner this
 *			  way.
 *		b.  Write zero+valid to the entire ILT.
 *		c.  Init the first_समयrs_ilt_entry, last_समयrs_ilt_entry of
 *		    VNIC3 (of that port). The range allocated will be the
 *		    entire ILT. This is needed to prevent  ILT range error.
 *	2.  Any PF driver load flow:
 *		a.  ILT update with the physical addresses of the allocated
 *		    logical pages.
 *		b.  Wait 20msec. - note that this समयout is needed to make
 *		    sure there are no requests in one of the PXP पूर्णांकernal
 *		    queues with "old" ILT addresses.
 *		c.  PF enable in the PGLC.
 *		d.  Clear the was_error of the PF in the PGLC. (could have
 *		    occurred जबतक driver was करोwn)
 *		e.  PF enable in the CFC (WEAK + STRONG)
 *		f.  Timers scan enable
 *	3.  PF driver unload flow:
 *		a.  Clear the Timers scan_en.
 *		b.  Polling क्रम scan_on=0 क्रम that PF.
 *		c.  Clear the PF enable bit in the PXP.
 *		d.  Clear the PF enable in the CFC (WEAK + STRONG)
 *		e.  Write zero+valid to all ILT entries (The valid bit must
 *		    stay set)
 *		f.  If this is VNIC 3 of a port then also init
 *		    first_समयrs_ilt_entry to zero and last_समयrs_ilt_entry
 *		    to the last entry in the ILT.
 *
 *	Notes:
 *	Currently the PF error in the PGLC is non recoverable.
 *	In the future the there will be a recovery routine क्रम this error.
 *	Currently attention is masked.
 *	Having an MCP lock on the load/unload process करोes not guarantee that
 *	there is no Timer disable during Func6/7 enable. This is because the
 *	Timers scan is currently being cleared by the MCP on FLR.
 *	Step 2.d can be करोne only क्रम PF6/7 and the driver can also check अगर
 *	there is error beक्रमe clearing it. But the flow above is simpler and
 *	more general.
 *	All ILT entries are written by zero+valid and not just PF6/7
 *	ILT entries since in the future the ILT entries allocation क्रम
 *	PF-s might be dynamic.
 */
		काष्ठा ilt_client_info ilt_cli;
		काष्ठा bnx2x_ilt ilt;
		स_रखो(&ilt_cli, 0, माप(काष्ठा ilt_client_info));
		स_रखो(&ilt, 0, माप(काष्ठा bnx2x_ilt));

		/* initialize dummy TM client */
		ilt_cli.start = 0;
		ilt_cli.end = ILT_NUM_PAGE_ENTRIES - 1;
		ilt_cli.client_num = ILT_CLIENT_TM;

		/* Step 1: set zeroes to all ilt page entries with valid bit on
		 * Step 2: set the समयrs first/last ilt entry to poपूर्णांक
		 * to the entire range to prevent ILT range error क्रम 3rd/4th
		 * vnic	(this code assumes existence of the vnic)
		 *
		 * both steps perक्रमmed by call to bnx2x_ilt_client_init_op()
		 * with dummy TM client
		 *
		 * we must use pretend since PXP2_REG_RQ_##blk##_FIRST_ILT
		 * and his brother are split रेजिस्टरs
		 */
		bnx2x_pretend_func(bp, (BP_PATH(bp) + 6));
		bnx2x_ilt_client_init_op_ilt(bp, &ilt, &ilt_cli, INITOP_CLEAR);
		bnx2x_pretend_func(bp, BP_ABS_FUNC(bp));

		REG_WR(bp, PXP2_REG_RQ_DRAM_ALIGN, BNX2X_PXP_DRAM_ALIGN);
		REG_WR(bp, PXP2_REG_RQ_DRAM_ALIGN_RD, BNX2X_PXP_DRAM_ALIGN);
		REG_WR(bp, PXP2_REG_RQ_DRAM_ALIGN_SEL, 1);
	पूर्ण

	REG_WR(bp, PXP2_REG_RQ_DISABLE_INPUTS, 0);
	REG_WR(bp, PXP2_REG_RD_DISABLE_INPUTS, 0);

	अगर (!CHIP_IS_E1x(bp)) अणु
		पूर्णांक factor = CHIP_REV_IS_EMUL(bp) ? 1000 :
				(CHIP_REV_IS_FPGA(bp) ? 400 : 0);
		bnx2x_init_block(bp, BLOCK_PGLUE_B, PHASE_COMMON);

		bnx2x_init_block(bp, BLOCK_ATC, PHASE_COMMON);

		/* let the HW करो it's magic ... */
		करो अणु
			msleep(200);
			val = REG_RD(bp, ATC_REG_ATC_INIT_DONE);
		पूर्ण जबतक (factor-- && (val != 1));

		अगर (val != 1) अणु
			BNX2X_ERR("ATC_INIT failed\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	bnx2x_init_block(bp, BLOCK_DMAE, PHASE_COMMON);

	bnx2x_iov_init_dmae(bp);

	/* clean the DMAE memory */
	bp->dmae_पढ़ोy = 1;
	bnx2x_init_fill(bp, TSEM_REG_PRAM, 0, 8, 1);

	bnx2x_init_block(bp, BLOCK_TCM, PHASE_COMMON);

	bnx2x_init_block(bp, BLOCK_UCM, PHASE_COMMON);

	bnx2x_init_block(bp, BLOCK_CCM, PHASE_COMMON);

	bnx2x_init_block(bp, BLOCK_XCM, PHASE_COMMON);

	bnx2x_पढ़ो_dmae(bp, XSEM_REG_PASSIVE_BUFFER, 3);
	bnx2x_पढ़ो_dmae(bp, CSEM_REG_PASSIVE_BUFFER, 3);
	bnx2x_पढ़ो_dmae(bp, TSEM_REG_PASSIVE_BUFFER, 3);
	bnx2x_पढ़ो_dmae(bp, USEM_REG_PASSIVE_BUFFER, 3);

	bnx2x_init_block(bp, BLOCK_QM, PHASE_COMMON);

	/* QM queues poपूर्णांकers table */
	bnx2x_qm_init_ptr_table(bp, bp->qm_cid_count, INITOP_SET);

	/* soft reset pulse */
	REG_WR(bp, QM_REG_SOFT_RESET, 1);
	REG_WR(bp, QM_REG_SOFT_RESET, 0);

	अगर (CNIC_SUPPORT(bp))
		bnx2x_init_block(bp, BLOCK_TM, PHASE_COMMON);

	bnx2x_init_block(bp, BLOCK_DORQ, PHASE_COMMON);

	अगर (!CHIP_REV_IS_SLOW(bp))
		/* enable hw पूर्णांकerrupt from करोorbell Q */
		REG_WR(bp, DORQ_REG_DORQ_INT_MASK, 0);

	bnx2x_init_block(bp, BLOCK_BRB1, PHASE_COMMON);

	bnx2x_init_block(bp, BLOCK_PRS, PHASE_COMMON);
	REG_WR(bp, PRS_REG_A_PRSU_20, 0xf);

	अगर (!CHIP_IS_E1(bp))
		REG_WR(bp, PRS_REG_E1HOV_MODE, bp->path_has_ovlan);

	अगर (!CHIP_IS_E1x(bp) && !CHIP_IS_E3B0(bp)) अणु
		अगर (IS_MF_AFEX(bp)) अणु
			/* configure that VNTag and VLAN headers must be
			 * received in afex mode
			 */
			REG_WR(bp, PRS_REG_HDRS_AFTER_BASIC, 0xE);
			REG_WR(bp, PRS_REG_MUST_HAVE_HDRS, 0xA);
			REG_WR(bp, PRS_REG_HDRS_AFTER_TAG_0, 0x6);
			REG_WR(bp, PRS_REG_TAG_ETHERTYPE_0, 0x8926);
			REG_WR(bp, PRS_REG_TAG_LEN_0, 0x4);
		पूर्ण अन्यथा अणु
			/* Bit-map indicating which L2 hdrs may appear
			 * after the basic Ethernet header
			 */
			REG_WR(bp, PRS_REG_HDRS_AFTER_BASIC,
			       bp->path_has_ovlan ? 7 : 6);
		पूर्ण
	पूर्ण

	bnx2x_init_block(bp, BLOCK_TSDM, PHASE_COMMON);
	bnx2x_init_block(bp, BLOCK_CSDM, PHASE_COMMON);
	bnx2x_init_block(bp, BLOCK_USDM, PHASE_COMMON);
	bnx2x_init_block(bp, BLOCK_XSDM, PHASE_COMMON);

	अगर (!CHIP_IS_E1x(bp)) अणु
		/* reset VFC memories */
		REG_WR(bp, TSEM_REG_FAST_MEMORY + VFC_REG_MEMORIES_RST,
			   VFC_MEMORIES_RST_REG_CAM_RST |
			   VFC_MEMORIES_RST_REG_RAM_RST);
		REG_WR(bp, XSEM_REG_FAST_MEMORY + VFC_REG_MEMORIES_RST,
			   VFC_MEMORIES_RST_REG_CAM_RST |
			   VFC_MEMORIES_RST_REG_RAM_RST);

		msleep(20);
	पूर्ण

	bnx2x_init_block(bp, BLOCK_TSEM, PHASE_COMMON);
	bnx2x_init_block(bp, BLOCK_USEM, PHASE_COMMON);
	bnx2x_init_block(bp, BLOCK_CSEM, PHASE_COMMON);
	bnx2x_init_block(bp, BLOCK_XSEM, PHASE_COMMON);

	/* sync semi rtc */
	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_1_CLEAR,
	       0x80000000);
	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_1_SET,
	       0x80000000);

	bnx2x_init_block(bp, BLOCK_UPB, PHASE_COMMON);
	bnx2x_init_block(bp, BLOCK_XPB, PHASE_COMMON);
	bnx2x_init_block(bp, BLOCK_PBF, PHASE_COMMON);

	अगर (!CHIP_IS_E1x(bp)) अणु
		अगर (IS_MF_AFEX(bp)) अणु
			/* configure that VNTag and VLAN headers must be
			 * sent in afex mode
			 */
			REG_WR(bp, PBF_REG_HDRS_AFTER_BASIC, 0xE);
			REG_WR(bp, PBF_REG_MUST_HAVE_HDRS, 0xA);
			REG_WR(bp, PBF_REG_HDRS_AFTER_TAG_0, 0x6);
			REG_WR(bp, PBF_REG_TAG_ETHERTYPE_0, 0x8926);
			REG_WR(bp, PBF_REG_TAG_LEN_0, 0x4);
		पूर्ण अन्यथा अणु
			REG_WR(bp, PBF_REG_HDRS_AFTER_BASIC,
			       bp->path_has_ovlan ? 7 : 6);
		पूर्ण
	पूर्ण

	REG_WR(bp, SRC_REG_SOFT_RST, 1);

	bnx2x_init_block(bp, BLOCK_SRC, PHASE_COMMON);

	अगर (CNIC_SUPPORT(bp)) अणु
		REG_WR(bp, SRC_REG_KEYSEARCH_0, 0x63285672);
		REG_WR(bp, SRC_REG_KEYSEARCH_1, 0x24b8f2cc);
		REG_WR(bp, SRC_REG_KEYSEARCH_2, 0x223aef9b);
		REG_WR(bp, SRC_REG_KEYSEARCH_3, 0x26001e3a);
		REG_WR(bp, SRC_REG_KEYSEARCH_4, 0x7ae91116);
		REG_WR(bp, SRC_REG_KEYSEARCH_5, 0x5ce5230b);
		REG_WR(bp, SRC_REG_KEYSEARCH_6, 0x298d8adf);
		REG_WR(bp, SRC_REG_KEYSEARCH_7, 0x6eb0ff09);
		REG_WR(bp, SRC_REG_KEYSEARCH_8, 0x1830f82f);
		REG_WR(bp, SRC_REG_KEYSEARCH_9, 0x01e46be7);
	पूर्ण
	REG_WR(bp, SRC_REG_SOFT_RST, 0);

	अगर (माप(जोड़ cdu_context) != 1024)
		/* we currently assume that a context is 1024 bytes */
		dev_alert(&bp->pdev->dev,
			  "please adjust the size of cdu_context(%ld)\n",
			  (दीर्घ)माप(जोड़ cdu_context));

	bnx2x_init_block(bp, BLOCK_CDU, PHASE_COMMON);
	val = (4 << 24) + (0 << 12) + 1024;
	REG_WR(bp, CDU_REG_CDU_GLOBAL_PARAMS, val);

	bnx2x_init_block(bp, BLOCK_CFC, PHASE_COMMON);
	REG_WR(bp, CFC_REG_INIT_REG, 0x7FF);
	/* enable context validation पूर्णांकerrupt from CFC */
	REG_WR(bp, CFC_REG_CFC_INT_MASK, 0);

	/* set the thresholds to prevent CFC/CDU race */
	REG_WR(bp, CFC_REG_DEBUG0, 0x20020000);

	bnx2x_init_block(bp, BLOCK_HC, PHASE_COMMON);

	अगर (!CHIP_IS_E1x(bp) && BP_NOMCP(bp))
		REG_WR(bp, IGU_REG_RESET_MEMORIES, 0x36);

	bnx2x_init_block(bp, BLOCK_IGU, PHASE_COMMON);
	bnx2x_init_block(bp, BLOCK_MISC_AEU, PHASE_COMMON);

	/* Reset PCIE errors क्रम debug */
	REG_WR(bp, 0x2814, 0xffffffff);
	REG_WR(bp, 0x3820, 0xffffffff);

	अगर (!CHIP_IS_E1x(bp)) अणु
		REG_WR(bp, PCICFG_OFFSET + PXPCS_TL_CONTROL_5,
			   (PXPCS_TL_CONTROL_5_ERR_UNSPPORT1 |
				PXPCS_TL_CONTROL_5_ERR_UNSPPORT));
		REG_WR(bp, PCICFG_OFFSET + PXPCS_TL_FUNC345_STAT,
			   (PXPCS_TL_FUNC345_STAT_ERR_UNSPPORT4 |
				PXPCS_TL_FUNC345_STAT_ERR_UNSPPORT3 |
				PXPCS_TL_FUNC345_STAT_ERR_UNSPPORT2));
		REG_WR(bp, PCICFG_OFFSET + PXPCS_TL_FUNC678_STAT,
			   (PXPCS_TL_FUNC678_STAT_ERR_UNSPPORT7 |
				PXPCS_TL_FUNC678_STAT_ERR_UNSPPORT6 |
				PXPCS_TL_FUNC678_STAT_ERR_UNSPPORT5));
	पूर्ण

	bnx2x_init_block(bp, BLOCK_NIG, PHASE_COMMON);
	अगर (!CHIP_IS_E1(bp)) अणु
		/* in E3 this करोne in per-port section */
		अगर (!CHIP_IS_E3(bp))
			REG_WR(bp, NIG_REG_LLH_MF_MODE, IS_MF(bp));
	पूर्ण
	अगर (CHIP_IS_E1H(bp))
		/* not applicable क्रम E2 (and above ...) */
		REG_WR(bp, NIG_REG_LLH_E1HOV_MODE, IS_MF_SD(bp));

	अगर (CHIP_REV_IS_SLOW(bp))
		msleep(200);

	/* finish CFC init */
	val = reg_poll(bp, CFC_REG_LL_INIT_DONE, 1, 100, 10);
	अगर (val != 1) अणु
		BNX2X_ERR("CFC LL_INIT failed\n");
		वापस -EBUSY;
	पूर्ण
	val = reg_poll(bp, CFC_REG_AC_INIT_DONE, 1, 100, 10);
	अगर (val != 1) अणु
		BNX2X_ERR("CFC AC_INIT failed\n");
		वापस -EBUSY;
	पूर्ण
	val = reg_poll(bp, CFC_REG_CAM_INIT_DONE, 1, 100, 10);
	अगर (val != 1) अणु
		BNX2X_ERR("CFC CAM_INIT failed\n");
		वापस -EBUSY;
	पूर्ण
	REG_WR(bp, CFC_REG_DEBUG0, 0);

	अगर (CHIP_IS_E1(bp)) अणु
		/* पढ़ो NIG statistic
		   to see अगर this is our first up since घातerup */
		bnx2x_पढ़ो_dmae(bp, NIG_REG_STAT2_BRB_OCTET, 2);
		val = *bnx2x_sp(bp, wb_data[0]);

		/* करो पूर्णांकernal memory self test */
		अगर ((val == 0) && bnx2x_पूर्णांक_mem_test(bp)) अणु
			BNX2X_ERR("internal mem self test failed\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	bnx2x_setup_fan_failure_detection(bp);

	/* clear PXP2 attentions */
	REG_RD(bp, PXP2_REG_PXP2_INT_STS_CLR_0);

	bnx2x_enable_blocks_attention(bp);
	bnx2x_enable_blocks_parity(bp);

	अगर (!BP_NOMCP(bp)) अणु
		अगर (CHIP_IS_E1x(bp))
			bnx2x__common_init_phy(bp);
	पूर्ण अन्यथा
		BNX2X_ERR("Bootcode is missing - can not initialize link\n");

	अगर (SHMEM2_HAS(bp, netproc_fw_ver))
		SHMEM2_WR(bp, netproc_fw_ver, REG_RD(bp, XSEM_REG_PRAM));

	वापस 0;
पूर्ण

/**
 * bnx2x_init_hw_common_chip - init HW at the COMMON_CHIP phase.
 *
 * @bp:		driver handle
 */
अटल पूर्णांक bnx2x_init_hw_common_chip(काष्ठा bnx2x *bp)
अणु
	पूर्णांक rc = bnx2x_init_hw_common(bp);

	अगर (rc)
		वापस rc;

	/* In E2 2-PORT mode, same ext phy is used क्रम the two paths */
	अगर (!BP_NOMCP(bp))
		bnx2x__common_init_phy(bp);

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_init_hw_port(काष्ठा bnx2x *bp)
अणु
	पूर्णांक port = BP_PORT(bp);
	पूर्णांक init_phase = port ? PHASE_PORT1 : PHASE_PORT0;
	u32 low, high;
	u32 val, reg;

	DP(NETIF_MSG_HW, "starting port init  port %d\n", port);

	REG_WR(bp, NIG_REG_MASK_INTERRUPT_PORT0 + port*4, 0);

	bnx2x_init_block(bp, BLOCK_MISC, init_phase);
	bnx2x_init_block(bp, BLOCK_PXP, init_phase);
	bnx2x_init_block(bp, BLOCK_PXP2, init_phase);

	/* Timers bug workaround: disables the pf_master bit in pglue at
	 * common phase, we need to enable it here beक्रमe any dmae access are
	 * attempted. Thereक्रमe we manually added the enable-master to the
	 * port phase (it also happens in the function phase)
	 */
	अगर (!CHIP_IS_E1x(bp))
		REG_WR(bp, PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER, 1);

	bnx2x_init_block(bp, BLOCK_ATC, init_phase);
	bnx2x_init_block(bp, BLOCK_DMAE, init_phase);
	bnx2x_init_block(bp, BLOCK_PGLUE_B, init_phase);
	bnx2x_init_block(bp, BLOCK_QM, init_phase);

	bnx2x_init_block(bp, BLOCK_TCM, init_phase);
	bnx2x_init_block(bp, BLOCK_UCM, init_phase);
	bnx2x_init_block(bp, BLOCK_CCM, init_phase);
	bnx2x_init_block(bp, BLOCK_XCM, init_phase);

	/* QM cid (connection) count */
	bnx2x_qm_init_cid_count(bp, bp->qm_cid_count, INITOP_SET);

	अगर (CNIC_SUPPORT(bp)) अणु
		bnx2x_init_block(bp, BLOCK_TM, init_phase);
		REG_WR(bp, TM_REG_LIN0_SCAN_TIME + port*4, 20);
		REG_WR(bp, TM_REG_LIN0_MAX_ACTIVE_CID + port*4, 31);
	पूर्ण

	bnx2x_init_block(bp, BLOCK_DORQ, init_phase);

	bnx2x_init_block(bp, BLOCK_BRB1, init_phase);

	अगर (CHIP_IS_E1(bp) || CHIP_IS_E1H(bp)) अणु

		अगर (IS_MF(bp))
			low = ((bp->flags & ONE_PORT_FLAG) ? 160 : 246);
		अन्यथा अगर (bp->dev->mtu > 4096) अणु
			अगर (bp->flags & ONE_PORT_FLAG)
				low = 160;
			अन्यथा अणु
				val = bp->dev->mtu;
				/* (24*1024 + val*4)/256 */
				low = 96 + (val/64) +
						((val % 64) ? 1 : 0);
			पूर्ण
		पूर्ण अन्यथा
			low = ((bp->flags & ONE_PORT_FLAG) ? 80 : 160);
		high = low + 56;	/* 14*1024/256 */
		REG_WR(bp, BRB1_REG_PAUSE_LOW_THRESHOLD_0 + port*4, low);
		REG_WR(bp, BRB1_REG_PAUSE_HIGH_THRESHOLD_0 + port*4, high);
	पूर्ण

	अगर (CHIP_MODE_IS_4_PORT(bp))
		REG_WR(bp, (BP_PORT(bp) ?
			    BRB1_REG_MAC_GUARANTIED_1 :
			    BRB1_REG_MAC_GUARANTIED_0), 40);

	bnx2x_init_block(bp, BLOCK_PRS, init_phase);
	अगर (CHIP_IS_E3B0(bp)) अणु
		अगर (IS_MF_AFEX(bp)) अणु
			/* configure headers क्रम AFEX mode */
			REG_WR(bp, BP_PORT(bp) ?
			       PRS_REG_HDRS_AFTER_BASIC_PORT_1 :
			       PRS_REG_HDRS_AFTER_BASIC_PORT_0, 0xE);
			REG_WR(bp, BP_PORT(bp) ?
			       PRS_REG_HDRS_AFTER_TAG_0_PORT_1 :
			       PRS_REG_HDRS_AFTER_TAG_0_PORT_0, 0x6);
			REG_WR(bp, BP_PORT(bp) ?
			       PRS_REG_MUST_HAVE_HDRS_PORT_1 :
			       PRS_REG_MUST_HAVE_HDRS_PORT_0, 0xA);
		पूर्ण अन्यथा अणु
			/* Ovlan exists only अगर we are in multi-function +
			 * चयन-dependent mode, in चयन-independent there
			 * is no ovlan headers
			 */
			REG_WR(bp, BP_PORT(bp) ?
			       PRS_REG_HDRS_AFTER_BASIC_PORT_1 :
			       PRS_REG_HDRS_AFTER_BASIC_PORT_0,
			       (bp->path_has_ovlan ? 7 : 6));
		पूर्ण
	पूर्ण

	bnx2x_init_block(bp, BLOCK_TSDM, init_phase);
	bnx2x_init_block(bp, BLOCK_CSDM, init_phase);
	bnx2x_init_block(bp, BLOCK_USDM, init_phase);
	bnx2x_init_block(bp, BLOCK_XSDM, init_phase);

	bnx2x_init_block(bp, BLOCK_TSEM, init_phase);
	bnx2x_init_block(bp, BLOCK_USEM, init_phase);
	bnx2x_init_block(bp, BLOCK_CSEM, init_phase);
	bnx2x_init_block(bp, BLOCK_XSEM, init_phase);

	bnx2x_init_block(bp, BLOCK_UPB, init_phase);
	bnx2x_init_block(bp, BLOCK_XPB, init_phase);

	bnx2x_init_block(bp, BLOCK_PBF, init_phase);

	अगर (CHIP_IS_E1x(bp)) अणु
		/* configure PBF to work without PAUSE mtu 9000 */
		REG_WR(bp, PBF_REG_P0_PAUSE_ENABLE + port*4, 0);

		/* update threshold */
		REG_WR(bp, PBF_REG_P0_ARB_THRSH + port*4, (9040/16));
		/* update init credit */
		REG_WR(bp, PBF_REG_P0_INIT_CRD + port*4, (9040/16) + 553 - 22);

		/* probe changes */
		REG_WR(bp, PBF_REG_INIT_P0 + port*4, 1);
		udelay(50);
		REG_WR(bp, PBF_REG_INIT_P0 + port*4, 0);
	पूर्ण

	अगर (CNIC_SUPPORT(bp))
		bnx2x_init_block(bp, BLOCK_SRC, init_phase);

	bnx2x_init_block(bp, BLOCK_CDU, init_phase);
	bnx2x_init_block(bp, BLOCK_CFC, init_phase);

	अगर (CHIP_IS_E1(bp)) अणु
		REG_WR(bp, HC_REG_LEADING_EDGE_0 + port*8, 0);
		REG_WR(bp, HC_REG_TRAILING_EDGE_0 + port*8, 0);
	पूर्ण
	bnx2x_init_block(bp, BLOCK_HC, init_phase);

	bnx2x_init_block(bp, BLOCK_IGU, init_phase);

	bnx2x_init_block(bp, BLOCK_MISC_AEU, init_phase);
	/* init aeu_mask_attn_func_0/1:
	 *  - SF mode: bits 3-7 are masked. Only bits 0-2 are in use
	 *  - MF mode: bit 3 is masked. Bits 0-2 are in use as in SF
	 *             bits 4-7 are used क्रम "per vn group attention" */
	val = IS_MF(bp) ? 0xF7 : 0x7;
	/* Enable DCBX attention क्रम all but E1 */
	val |= CHIP_IS_E1(bp) ? 0 : 0x10;
	REG_WR(bp, MISC_REG_AEU_MASK_ATTN_FUNC_0 + port*4, val);

	/* SCPAD_PARITY should NOT trigger बंद the gates */
	reg = port ? MISC_REG_AEU_ENABLE4_NIG_1 : MISC_REG_AEU_ENABLE4_NIG_0;
	REG_WR(bp, reg,
	       REG_RD(bp, reg) &
	       ~AEU_INPUTS_ATTN_BITS_MCP_LATCHED_SCPAD_PARITY);

	reg = port ? MISC_REG_AEU_ENABLE4_PXP_1 : MISC_REG_AEU_ENABLE4_PXP_0;
	REG_WR(bp, reg,
	       REG_RD(bp, reg) &
	       ~AEU_INPUTS_ATTN_BITS_MCP_LATCHED_SCPAD_PARITY);

	bnx2x_init_block(bp, BLOCK_NIG, init_phase);

	अगर (!CHIP_IS_E1x(bp)) अणु
		/* Bit-map indicating which L2 hdrs may appear after the
		 * basic Ethernet header
		 */
		अगर (IS_MF_AFEX(bp))
			REG_WR(bp, BP_PORT(bp) ?
			       NIG_REG_P1_HDRS_AFTER_BASIC :
			       NIG_REG_P0_HDRS_AFTER_BASIC, 0xE);
		अन्यथा
			REG_WR(bp, BP_PORT(bp) ?
			       NIG_REG_P1_HDRS_AFTER_BASIC :
			       NIG_REG_P0_HDRS_AFTER_BASIC,
			       IS_MF_SD(bp) ? 7 : 6);

		अगर (CHIP_IS_E3(bp))
			REG_WR(bp, BP_PORT(bp) ?
				   NIG_REG_LLH1_MF_MODE :
				   NIG_REG_LLH_MF_MODE, IS_MF(bp));
	पूर्ण
	अगर (!CHIP_IS_E3(bp))
		REG_WR(bp, NIG_REG_XGXS_SERDES0_MODE_SEL + port*4, 1);

	अगर (!CHIP_IS_E1(bp)) अणु
		/* 0x2 disable mf_ov, 0x1 enable */
		REG_WR(bp, NIG_REG_LLH0_BRB1_DRV_MASK_MF + port*4,
		       (IS_MF_SD(bp) ? 0x1 : 0x2));

		अगर (!CHIP_IS_E1x(bp)) अणु
			val = 0;
			चयन (bp->mf_mode) अणु
			हाल MULTI_FUNCTION_SD:
				val = 1;
				अवरोध;
			हाल MULTI_FUNCTION_SI:
			हाल MULTI_FUNCTION_AFEX:
				val = 2;
				अवरोध;
			पूर्ण

			REG_WR(bp, (BP_PORT(bp) ? NIG_REG_LLH1_CLS_TYPE :
						  NIG_REG_LLH0_CLS_TYPE), val);
		पूर्ण
		अणु
			REG_WR(bp, NIG_REG_LLFC_ENABLE_0 + port*4, 0);
			REG_WR(bp, NIG_REG_LLFC_OUT_EN_0 + port*4, 0);
			REG_WR(bp, NIG_REG_PAUSE_ENABLE_0 + port*4, 1);
		पूर्ण
	पूर्ण

	/* If SPIO5 is set to generate पूर्णांकerrupts, enable it क्रम this port */
	val = REG_RD(bp, MISC_REG_SPIO_EVENT_EN);
	अगर (val & MISC_SPIO_SPIO5) अणु
		u32 reg_addr = (port ? MISC_REG_AEU_ENABLE1_FUNC_1_OUT_0 :
				       MISC_REG_AEU_ENABLE1_FUNC_0_OUT_0);
		val = REG_RD(bp, reg_addr);
		val |= AEU_INPUTS_ATTN_BITS_SPIO5;
		REG_WR(bp, reg_addr, val);
	पूर्ण

	अगर (CHIP_IS_E3B0(bp))
		bp->flags |= PTP_SUPPORTED;

	वापस 0;
पूर्ण

अटल व्योम bnx2x_ilt_wr(काष्ठा bnx2x *bp, u32 index, dma_addr_t addr)
अणु
	पूर्णांक reg;
	u32 wb_ग_लिखो[2];

	अगर (CHIP_IS_E1(bp))
		reg = PXP2_REG_RQ_ONCHIP_AT + index*8;
	अन्यथा
		reg = PXP2_REG_RQ_ONCHIP_AT_B0 + index*8;

	wb_ग_लिखो[0] = ONCHIP_ADDR1(addr);
	wb_ग_लिखो[1] = ONCHIP_ADDR2(addr);
	REG_WR_DMAE(bp, reg, wb_ग_लिखो, 2);
पूर्ण

व्योम bnx2x_igu_clear_sb_gen(काष्ठा bnx2x *bp, u8 func, u8 idu_sb_id, bool is_pf)
अणु
	u32 data, ctl, cnt = 100;
	u32 igu_addr_data = IGU_REG_COMMAND_REG_32LSB_DATA;
	u32 igu_addr_ctl = IGU_REG_COMMAND_REG_CTRL;
	u32 igu_addr_ack = IGU_REG_CSTORM_TYPE_0_SB_CLEANUP + (idu_sb_id/32)*4;
	u32 sb_bit =  1 << (idu_sb_id%32);
	u32 func_encode = func | (is_pf ? 1 : 0) << IGU_FID_ENCODE_IS_PF_SHIFT;
	u32 addr_encode = IGU_CMD_E2_PROD_UPD_BASE + idu_sb_id;

	/* Not supported in BC mode */
	अगर (CHIP_INT_MODE_IS_BC(bp))
		वापस;

	data = (IGU_USE_REGISTER_cstorm_type_0_sb_cleanup
			<< IGU_REGULAR_CLEANUP_TYPE_SHIFT)	|
		IGU_REGULAR_CLEANUP_SET				|
		IGU_REGULAR_BCLEANUP;

	ctl = addr_encode << IGU_CTRL_REG_ADDRESS_SHIFT		|
	      func_encode << IGU_CTRL_REG_FID_SHIFT		|
	      IGU_CTRL_CMD_TYPE_WR << IGU_CTRL_REG_TYPE_SHIFT;

	DP(NETIF_MSG_HW, "write 0x%08x to IGU(via GRC) addr 0x%x\n",
			 data, igu_addr_data);
	REG_WR(bp, igu_addr_data, data);
	barrier();
	DP(NETIF_MSG_HW, "write 0x%08x to IGU(via GRC) addr 0x%x\n",
			  ctl, igu_addr_ctl);
	REG_WR(bp, igu_addr_ctl, ctl);
	barrier();

	/* रुको क्रम clean up to finish */
	जबतक (!(REG_RD(bp, igu_addr_ack) & sb_bit) && --cnt)
		msleep(20);

	अगर (!(REG_RD(bp, igu_addr_ack) & sb_bit)) अणु
		DP(NETIF_MSG_HW,
		   "Unable to finish IGU cleanup: idu_sb_id %d offset %d bit %d (cnt %d)\n",
			  idu_sb_id, idu_sb_id/32, idu_sb_id%32, cnt);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_igu_clear_sb(काष्ठा bnx2x *bp, u8 idu_sb_id)
अणु
	bnx2x_igu_clear_sb_gen(bp, BP_FUNC(bp), idu_sb_id, true /*PF*/);
पूर्ण

अटल व्योम bnx2x_clear_func_ilt(काष्ठा bnx2x *bp, u32 func)
अणु
	u32 i, base = FUNC_ILT_BASE(func);
	क्रम (i = base; i < base + ILT_PER_FUNC; i++)
		bnx2x_ilt_wr(bp, i, 0);
पूर्ण

अटल व्योम bnx2x_init_searcher(काष्ठा bnx2x *bp)
अणु
	पूर्णांक port = BP_PORT(bp);
	bnx2x_src_init_t2(bp, bp->t2, bp->t2_mapping, SRC_CONN_NUM);
	/* T1 hash bits value determines the T1 number of entries */
	REG_WR(bp, SRC_REG_NUMBER_HASH_BITS0 + port*4, SRC_HASH_BITS);
पूर्ण

अटल अंतरभूत पूर्णांक bnx2x_func_चयन_update(काष्ठा bnx2x *bp, पूर्णांक suspend)
अणु
	पूर्णांक rc;
	काष्ठा bnx2x_func_state_params func_params = अणुशून्यपूर्ण;
	काष्ठा bnx2x_func_चयन_update_params *चयन_update_params =
		&func_params.params.चयन_update;

	/* Prepare parameters क्रम function state transitions */
	__set_bit(RAMROD_COMP_WAIT, &func_params.ramrod_flags);
	__set_bit(RAMROD_RETRY, &func_params.ramrod_flags);

	func_params.f_obj = &bp->func_obj;
	func_params.cmd = BNX2X_F_CMD_SWITCH_UPDATE;

	/* Function parameters */
	__set_bit(BNX2X_F_UPDATE_TX_SWITCH_SUSPEND_CHNG,
		  &चयन_update_params->changes);
	अगर (suspend)
		__set_bit(BNX2X_F_UPDATE_TX_SWITCH_SUSPEND,
			  &चयन_update_params->changes);

	rc = bnx2x_func_state_change(bp, &func_params);

	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_reset_nic_mode(काष्ठा bnx2x *bp)
अणु
	पूर्णांक rc, i, port = BP_PORT(bp);
	पूर्णांक vlan_en = 0, mac_en[NUM_MACS];

	/* Close input from network */
	अगर (bp->mf_mode == SINGLE_FUNCTION) अणु
		bnx2x_set_rx_filter(&bp->link_params, 0);
	पूर्ण अन्यथा अणु
		vlan_en = REG_RD(bp, port ? NIG_REG_LLH1_FUNC_EN :
				   NIG_REG_LLH0_FUNC_EN);
		REG_WR(bp, port ? NIG_REG_LLH1_FUNC_EN :
			  NIG_REG_LLH0_FUNC_EN, 0);
		क्रम (i = 0; i < NUM_MACS; i++) अणु
			mac_en[i] = REG_RD(bp, port ?
					     (NIG_REG_LLH1_FUNC_MEM_ENABLE +
					      4 * i) :
					     (NIG_REG_LLH0_FUNC_MEM_ENABLE +
					      4 * i));
			REG_WR(bp, port ? (NIG_REG_LLH1_FUNC_MEM_ENABLE +
					      4 * i) :
				  (NIG_REG_LLH0_FUNC_MEM_ENABLE + 4 * i), 0);
		पूर्ण
	पूर्ण

	/* Close BMC to host */
	REG_WR(bp, port ? NIG_REG_P0_TX_MNG_HOST_ENABLE :
	       NIG_REG_P1_TX_MNG_HOST_ENABLE, 0);

	/* Suspend Tx चयनing to the PF. Completion of this ramrod
	 * further guarantees that all the packets of that PF / child
	 * VFs in BRB were processed by the Parser, so it is safe to
	 * change the NIC_MODE रेजिस्टर.
	 */
	rc = bnx2x_func_चयन_update(bp, 1);
	अगर (rc) अणु
		BNX2X_ERR("Can't suspend tx-switching!\n");
		वापस rc;
	पूर्ण

	/* Change NIC_MODE रेजिस्टर */
	REG_WR(bp, PRS_REG_NIC_MODE, 0);

	/* Open input from network */
	अगर (bp->mf_mode == SINGLE_FUNCTION) अणु
		bnx2x_set_rx_filter(&bp->link_params, 1);
	पूर्ण अन्यथा अणु
		REG_WR(bp, port ? NIG_REG_LLH1_FUNC_EN :
			  NIG_REG_LLH0_FUNC_EN, vlan_en);
		क्रम (i = 0; i < NUM_MACS; i++) अणु
			REG_WR(bp, port ? (NIG_REG_LLH1_FUNC_MEM_ENABLE +
					      4 * i) :
				  (NIG_REG_LLH0_FUNC_MEM_ENABLE + 4 * i),
				  mac_en[i]);
		पूर्ण
	पूर्ण

	/* Enable BMC to host */
	REG_WR(bp, port ? NIG_REG_P0_TX_MNG_HOST_ENABLE :
	       NIG_REG_P1_TX_MNG_HOST_ENABLE, 1);

	/* Resume Tx चयनing to the PF */
	rc = bnx2x_func_चयन_update(bp, 0);
	अगर (rc) अणु
		BNX2X_ERR("Can't resume tx-switching!\n");
		वापस rc;
	पूर्ण

	DP(NETIF_MSG_IFUP, "NIC MODE disabled\n");
	वापस 0;
पूर्ण

पूर्णांक bnx2x_init_hw_func_cnic(काष्ठा bnx2x *bp)
अणु
	पूर्णांक rc;

	bnx2x_ilt_init_op_cnic(bp, INITOP_SET);

	अगर (CONFIGURE_NIC_MODE(bp)) अणु
		/* Configure searcher as part of function hw init */
		bnx2x_init_searcher(bp);

		/* Reset NIC mode */
		rc = bnx2x_reset_nic_mode(bp);
		अगर (rc)
			BNX2X_ERR("Can't change NIC mode!\n");
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

/* previous driver DMAE transaction may have occurred when pre-boot stage ended
 * and boot began, or when kdump kernel was loaded. Either हाल would invalidate
 * the addresses of the transaction, resulting in was-error bit set in the pci
 * causing all hw-to-host pcie transactions to समयout. If this happened we want
 * to clear the पूर्णांकerrupt which detected this from the pglueb and the was करोne
 * bit
 */
अटल व्योम bnx2x_clean_pglue_errors(काष्ठा bnx2x *bp)
अणु
	अगर (!CHIP_IS_E1x(bp))
		REG_WR(bp, PGLUE_B_REG_WAS_ERROR_PF_7_0_CLR,
		       1 << BP_ABS_FUNC(bp));
पूर्ण

अटल पूर्णांक bnx2x_init_hw_func(काष्ठा bnx2x *bp)
अणु
	पूर्णांक port = BP_PORT(bp);
	पूर्णांक func = BP_FUNC(bp);
	पूर्णांक init_phase = PHASE_PF0 + func;
	काष्ठा bnx2x_ilt *ilt = BP_ILT(bp);
	u16 cdu_ilt_start;
	u32 addr, val;
	u32 मुख्य_mem_base, मुख्य_mem_size, मुख्य_mem_prty_clr;
	पूर्णांक i, मुख्य_mem_width, rc;

	DP(NETIF_MSG_HW, "starting func init  func %d\n", func);

	/* FLR cleanup - hmmm */
	अगर (!CHIP_IS_E1x(bp)) अणु
		rc = bnx2x_pf_flr_clnup(bp);
		अगर (rc) अणु
			bnx2x_fw_dump(bp);
			वापस rc;
		पूर्ण
	पूर्ण

	/* set MSI reconfigure capability */
	अगर (bp->common.पूर्णांक_block == INT_BLOCK_HC) अणु
		addr = (port ? HC_REG_CONFIG_1 : HC_REG_CONFIG_0);
		val = REG_RD(bp, addr);
		val |= HC_CONFIG_0_REG_MSI_ATTN_EN_0;
		REG_WR(bp, addr, val);
	पूर्ण

	bnx2x_init_block(bp, BLOCK_PXP, init_phase);
	bnx2x_init_block(bp, BLOCK_PXP2, init_phase);

	ilt = BP_ILT(bp);
	cdu_ilt_start = ilt->clients[ILT_CLIENT_CDU].start;

	अगर (IS_SRIOV(bp))
		cdu_ilt_start += BNX2X_FIRST_VF_CID/ILT_PAGE_CIDS;
	cdu_ilt_start = bnx2x_iov_init_ilt(bp, cdu_ilt_start);

	/* since BNX2X_FIRST_VF_CID > 0 the PF L2 cids precedes
	 * those of the VFs, so start line should be reset
	 */
	cdu_ilt_start = ilt->clients[ILT_CLIENT_CDU].start;
	क्रम (i = 0; i < L2_ILT_LINES(bp); i++) अणु
		ilt->lines[cdu_ilt_start + i].page = bp->context[i].vcxt;
		ilt->lines[cdu_ilt_start + i].page_mapping =
			bp->context[i].cxt_mapping;
		ilt->lines[cdu_ilt_start + i].size = bp->context[i].size;
	पूर्ण

	bnx2x_ilt_init_op(bp, INITOP_SET);

	अगर (!CONFIGURE_NIC_MODE(bp)) अणु
		bnx2x_init_searcher(bp);
		REG_WR(bp, PRS_REG_NIC_MODE, 0);
		DP(NETIF_MSG_IFUP, "NIC MODE disabled\n");
	पूर्ण अन्यथा अणु
		/* Set NIC mode */
		REG_WR(bp, PRS_REG_NIC_MODE, 1);
		DP(NETIF_MSG_IFUP, "NIC MODE configured\n");
	पूर्ण

	अगर (!CHIP_IS_E1x(bp)) अणु
		u32 pf_conf = IGU_PF_CONF_FUNC_EN;

		/* Turn on a single ISR mode in IGU अगर driver is going to use
		 * INT#x or MSI
		 */
		अगर (!(bp->flags & USING_MSIX_FLAG))
			pf_conf |= IGU_PF_CONF_SINGLE_ISR_EN;
		/*
		 * Timers workaround bug: function init part.
		 * Need to रुको 20msec after initializing ILT,
		 * needed to make sure there are no requests in
		 * one of the PXP पूर्णांकernal queues with "old" ILT addresses
		 */
		msleep(20);
		/*
		 * Master enable - Due to WB DMAE ग_लिखोs perक्रमmed beक्रमe this
		 * रेजिस्टर is re-initialized as part of the regular function
		 * init
		 */
		REG_WR(bp, PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER, 1);
		/* Enable the function in IGU */
		REG_WR(bp, IGU_REG_PF_CONFIGURATION, pf_conf);
	पूर्ण

	bp->dmae_पढ़ोy = 1;

	bnx2x_init_block(bp, BLOCK_PGLUE_B, init_phase);

	bnx2x_clean_pglue_errors(bp);

	bnx2x_init_block(bp, BLOCK_ATC, init_phase);
	bnx2x_init_block(bp, BLOCK_DMAE, init_phase);
	bnx2x_init_block(bp, BLOCK_NIG, init_phase);
	bnx2x_init_block(bp, BLOCK_SRC, init_phase);
	bnx2x_init_block(bp, BLOCK_MISC, init_phase);
	bnx2x_init_block(bp, BLOCK_TCM, init_phase);
	bnx2x_init_block(bp, BLOCK_UCM, init_phase);
	bnx2x_init_block(bp, BLOCK_CCM, init_phase);
	bnx2x_init_block(bp, BLOCK_XCM, init_phase);
	bnx2x_init_block(bp, BLOCK_TSEM, init_phase);
	bnx2x_init_block(bp, BLOCK_USEM, init_phase);
	bnx2x_init_block(bp, BLOCK_CSEM, init_phase);
	bnx2x_init_block(bp, BLOCK_XSEM, init_phase);

	अगर (!CHIP_IS_E1x(bp))
		REG_WR(bp, QM_REG_PF_EN, 1);

	अगर (!CHIP_IS_E1x(bp)) अणु
		REG_WR(bp, TSEM_REG_VFPF_ERR_NUM, BNX2X_MAX_NUM_OF_VFS + func);
		REG_WR(bp, USEM_REG_VFPF_ERR_NUM, BNX2X_MAX_NUM_OF_VFS + func);
		REG_WR(bp, CSEM_REG_VFPF_ERR_NUM, BNX2X_MAX_NUM_OF_VFS + func);
		REG_WR(bp, XSEM_REG_VFPF_ERR_NUM, BNX2X_MAX_NUM_OF_VFS + func);
	पूर्ण
	bnx2x_init_block(bp, BLOCK_QM, init_phase);

	bnx2x_init_block(bp, BLOCK_TM, init_phase);
	bnx2x_init_block(bp, BLOCK_DORQ, init_phase);
	REG_WR(bp, DORQ_REG_MODE_ACT, 1); /* no dpm */

	bnx2x_iov_init_dq(bp);

	bnx2x_init_block(bp, BLOCK_BRB1, init_phase);
	bnx2x_init_block(bp, BLOCK_PRS, init_phase);
	bnx2x_init_block(bp, BLOCK_TSDM, init_phase);
	bnx2x_init_block(bp, BLOCK_CSDM, init_phase);
	bnx2x_init_block(bp, BLOCK_USDM, init_phase);
	bnx2x_init_block(bp, BLOCK_XSDM, init_phase);
	bnx2x_init_block(bp, BLOCK_UPB, init_phase);
	bnx2x_init_block(bp, BLOCK_XPB, init_phase);
	bnx2x_init_block(bp, BLOCK_PBF, init_phase);
	अगर (!CHIP_IS_E1x(bp))
		REG_WR(bp, PBF_REG_DISABLE_PF, 0);

	bnx2x_init_block(bp, BLOCK_CDU, init_phase);

	bnx2x_init_block(bp, BLOCK_CFC, init_phase);

	अगर (!CHIP_IS_E1x(bp))
		REG_WR(bp, CFC_REG_WEAK_ENABLE_PF, 1);

	अगर (IS_MF(bp)) अणु
		अगर (!(IS_MF_UFP(bp) && BNX2X_IS_MF_SD_PROTOCOL_FCOE(bp))) अणु
			REG_WR(bp, NIG_REG_LLH0_FUNC_EN + port * 8, 1);
			REG_WR(bp, NIG_REG_LLH0_FUNC_VLAN_ID + port * 8,
			       bp->mf_ov);
		पूर्ण
	पूर्ण

	bnx2x_init_block(bp, BLOCK_MISC_AEU, init_phase);

	/* HC init per function */
	अगर (bp->common.पूर्णांक_block == INT_BLOCK_HC) अणु
		अगर (CHIP_IS_E1H(bp)) अणु
			REG_WR(bp, MISC_REG_AEU_GENERAL_ATTN_12 + func*4, 0);

			REG_WR(bp, HC_REG_LEADING_EDGE_0 + port*8, 0);
			REG_WR(bp, HC_REG_TRAILING_EDGE_0 + port*8, 0);
		पूर्ण
		bnx2x_init_block(bp, BLOCK_HC, init_phase);

	पूर्ण अन्यथा अणु
		पूर्णांक num_segs, sb_idx, prod_offset;

		REG_WR(bp, MISC_REG_AEU_GENERAL_ATTN_12 + func*4, 0);

		अगर (!CHIP_IS_E1x(bp)) अणु
			REG_WR(bp, IGU_REG_LEADING_EDGE_LATCH, 0);
			REG_WR(bp, IGU_REG_TRAILING_EDGE_LATCH, 0);
		पूर्ण

		bnx2x_init_block(bp, BLOCK_IGU, init_phase);

		अगर (!CHIP_IS_E1x(bp)) अणु
			पूर्णांक dsb_idx = 0;
			/**
			 * Producer memory:
			 * E2 mode: address 0-135 match to the mapping memory;
			 * 136 - PF0 शेष prod; 137 - PF1 शेष prod;
			 * 138 - PF2 शेष prod; 139 - PF3 शेष prod;
			 * 140 - PF0 attn prod;    141 - PF1 attn prod;
			 * 142 - PF2 attn prod;    143 - PF3 attn prod;
			 * 144-147 reserved.
			 *
			 * E1.5 mode - In backward compatible mode;
			 * क्रम non शेष SB; each even line in the memory
			 * holds the U producer and each odd line hold
			 * the C producer. The first 128 producers are क्रम
			 * NDSB (PF0 - 0-31; PF1 - 32-63 and so on). The last 20
			 * producers are क्रम the DSB क्रम each PF.
			 * Each PF has five segments: (the order inside each
			 * segment is PF0; PF1; PF2; PF3) - 128-131 U prods;
			 * 132-135 C prods; 136-139 X prods; 140-143 T prods;
			 * 144-147 attn prods;
			 */
			/* non-शेष-status-blocks */
			num_segs = CHIP_INT_MODE_IS_BC(bp) ?
				IGU_BC_NDSB_NUM_SEGS : IGU_NORM_NDSB_NUM_SEGS;
			क्रम (sb_idx = 0; sb_idx < bp->igu_sb_cnt; sb_idx++) अणु
				prod_offset = (bp->igu_base_sb + sb_idx) *
					num_segs;

				क्रम (i = 0; i < num_segs; i++) अणु
					addr = IGU_REG_PROD_CONS_MEMORY +
							(prod_offset + i) * 4;
					REG_WR(bp, addr, 0);
				पूर्ण
				/* send consumer update with value 0 */
				bnx2x_ack_sb(bp, bp->igu_base_sb + sb_idx,
					     USTORM_ID, 0, IGU_INT_NOP, 1);
				bnx2x_igu_clear_sb(bp,
						   bp->igu_base_sb + sb_idx);
			पूर्ण

			/* शेष-status-blocks */
			num_segs = CHIP_INT_MODE_IS_BC(bp) ?
				IGU_BC_DSB_NUM_SEGS : IGU_NORM_DSB_NUM_SEGS;

			अगर (CHIP_MODE_IS_4_PORT(bp))
				dsb_idx = BP_FUNC(bp);
			अन्यथा
				dsb_idx = BP_VN(bp);

			prod_offset = (CHIP_INT_MODE_IS_BC(bp) ?
				       IGU_BC_BASE_DSB_PROD + dsb_idx :
				       IGU_NORM_BASE_DSB_PROD + dsb_idx);

			/*
			 * igu prods come in chunks of E1HVN_MAX (4) -
			 * करोes not matters what is the current chip mode
			 */
			क्रम (i = 0; i < (num_segs * E1HVN_MAX);
			     i += E1HVN_MAX) अणु
				addr = IGU_REG_PROD_CONS_MEMORY +
							(prod_offset + i)*4;
				REG_WR(bp, addr, 0);
			पूर्ण
			/* send consumer update with 0 */
			अगर (CHIP_INT_MODE_IS_BC(bp)) अणु
				bnx2x_ack_sb(bp, bp->igu_dsb_id,
					     USTORM_ID, 0, IGU_INT_NOP, 1);
				bnx2x_ack_sb(bp, bp->igu_dsb_id,
					     CSTORM_ID, 0, IGU_INT_NOP, 1);
				bnx2x_ack_sb(bp, bp->igu_dsb_id,
					     XSTORM_ID, 0, IGU_INT_NOP, 1);
				bnx2x_ack_sb(bp, bp->igu_dsb_id,
					     TSTORM_ID, 0, IGU_INT_NOP, 1);
				bnx2x_ack_sb(bp, bp->igu_dsb_id,
					     ATTENTION_ID, 0, IGU_INT_NOP, 1);
			पूर्ण अन्यथा अणु
				bnx2x_ack_sb(bp, bp->igu_dsb_id,
					     USTORM_ID, 0, IGU_INT_NOP, 1);
				bnx2x_ack_sb(bp, bp->igu_dsb_id,
					     ATTENTION_ID, 0, IGU_INT_NOP, 1);
			पूर्ण
			bnx2x_igu_clear_sb(bp, bp->igu_dsb_id);

			/* !!! These should become driver स्थिर once
			   rf-tool supports split-68 स्थिर */
			REG_WR(bp, IGU_REG_SB_INT_BEFORE_MASK_LSB, 0);
			REG_WR(bp, IGU_REG_SB_INT_BEFORE_MASK_MSB, 0);
			REG_WR(bp, IGU_REG_SB_MASK_LSB, 0);
			REG_WR(bp, IGU_REG_SB_MASK_MSB, 0);
			REG_WR(bp, IGU_REG_PBA_STATUS_LSB, 0);
			REG_WR(bp, IGU_REG_PBA_STATUS_MSB, 0);
		पूर्ण
	पूर्ण

	/* Reset PCIE errors क्रम debug */
	REG_WR(bp, 0x2114, 0xffffffff);
	REG_WR(bp, 0x2120, 0xffffffff);

	अगर (CHIP_IS_E1x(bp)) अणु
		मुख्य_mem_size = HC_REG_MAIN_MEMORY_SIZE / 2; /*dwords*/
		मुख्य_mem_base = HC_REG_MAIN_MEMORY +
				BP_PORT(bp) * (मुख्य_mem_size * 4);
		मुख्य_mem_prty_clr = HC_REG_HC_PRTY_STS_CLR;
		मुख्य_mem_width = 8;

		val = REG_RD(bp, मुख्य_mem_prty_clr);
		अगर (val)
			DP(NETIF_MSG_HW,
			   "Hmmm... Parity errors in HC block during function init (0x%x)!\n",
			   val);

		/* Clear "false" parity errors in MSI-X table */
		क्रम (i = मुख्य_mem_base;
		     i < मुख्य_mem_base + मुख्य_mem_size * 4;
		     i += मुख्य_mem_width) अणु
			bnx2x_पढ़ो_dmae(bp, i, मुख्य_mem_width / 4);
			bnx2x_ग_लिखो_dmae(bp, bnx2x_sp_mapping(bp, wb_data),
					 i, मुख्य_mem_width / 4);
		पूर्ण
		/* Clear HC parity attention */
		REG_RD(bp, मुख्य_mem_prty_clr);
	पूर्ण

#अगर_घोषित BNX2X_STOP_ON_ERROR
	/* Enable STORMs SP logging */
	REG_WR8(bp, BAR_USTRORM_INTMEM +
	       USTORM_RECORD_SLOW_PATH_OFFSET(BP_FUNC(bp)), 1);
	REG_WR8(bp, BAR_TSTRORM_INTMEM +
	       TSTORM_RECORD_SLOW_PATH_OFFSET(BP_FUNC(bp)), 1);
	REG_WR8(bp, BAR_CSTRORM_INTMEM +
	       CSTORM_RECORD_SLOW_PATH_OFFSET(BP_FUNC(bp)), 1);
	REG_WR8(bp, BAR_XSTRORM_INTMEM +
	       XSTORM_RECORD_SLOW_PATH_OFFSET(BP_FUNC(bp)), 1);
#पूर्ण_अगर

	bnx2x_phy_probe(&bp->link_params);

	वापस 0;
पूर्ण

व्योम bnx2x_मुक्त_mem_cnic(काष्ठा bnx2x *bp)
अणु
	bnx2x_ilt_mem_op_cnic(bp, ILT_MEMOP_FREE);

	अगर (!CHIP_IS_E1x(bp))
		BNX2X_PCI_FREE(bp->cnic_sb.e2_sb, bp->cnic_sb_mapping,
			       माप(काष्ठा host_hc_status_block_e2));
	अन्यथा
		BNX2X_PCI_FREE(bp->cnic_sb.e1x_sb, bp->cnic_sb_mapping,
			       माप(काष्ठा host_hc_status_block_e1x));

	BNX2X_PCI_FREE(bp->t2, bp->t2_mapping, SRC_T2_SZ);
पूर्ण

व्योम bnx2x_मुक्त_mem(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;

	BNX2X_PCI_FREE(bp->fw_stats, bp->fw_stats_mapping,
		       bp->fw_stats_data_sz + bp->fw_stats_req_sz);

	अगर (IS_VF(bp))
		वापस;

	BNX2X_PCI_FREE(bp->def_status_blk, bp->def_status_blk_mapping,
		       माप(काष्ठा host_sp_status_block));

	BNX2X_PCI_FREE(bp->slowpath, bp->slowpath_mapping,
		       माप(काष्ठा bnx2x_slowpath));

	क्रम (i = 0; i < L2_ILT_LINES(bp); i++)
		BNX2X_PCI_FREE(bp->context[i].vcxt, bp->context[i].cxt_mapping,
			       bp->context[i].size);
	bnx2x_ilt_mem_op(bp, ILT_MEMOP_FREE);

	BNX2X_FREE(bp->ilt->lines);

	BNX2X_PCI_FREE(bp->spq, bp->spq_mapping, BCM_PAGE_SIZE);

	BNX2X_PCI_FREE(bp->eq_ring, bp->eq_mapping,
		       BCM_PAGE_SIZE * NUM_EQ_PAGES);

	BNX2X_PCI_FREE(bp->t2, bp->t2_mapping, SRC_T2_SZ);

	bnx2x_iov_मुक्त_mem(bp);
पूर्ण

पूर्णांक bnx2x_alloc_mem_cnic(काष्ठा bnx2x *bp)
अणु
	अगर (!CHIP_IS_E1x(bp)) अणु
		/* size = the status block + ramrod buffers */
		bp->cnic_sb.e2_sb = BNX2X_PCI_ALLOC(&bp->cnic_sb_mapping,
						    माप(काष्ठा host_hc_status_block_e2));
		अगर (!bp->cnic_sb.e2_sb)
			जाओ alloc_mem_err;
	पूर्ण अन्यथा अणु
		bp->cnic_sb.e1x_sb = BNX2X_PCI_ALLOC(&bp->cnic_sb_mapping,
						     माप(काष्ठा host_hc_status_block_e1x));
		अगर (!bp->cnic_sb.e1x_sb)
			जाओ alloc_mem_err;
	पूर्ण

	अगर (CONFIGURE_NIC_MODE(bp) && !bp->t2) अणु
		/* allocate searcher T2 table, as it wasn't allocated beक्रमe */
		bp->t2 = BNX2X_PCI_ALLOC(&bp->t2_mapping, SRC_T2_SZ);
		अगर (!bp->t2)
			जाओ alloc_mem_err;
	पूर्ण

	/* ग_लिखो address to which L5 should insert its values */
	bp->cnic_eth_dev.addr_drv_info_to_mcp =
		&bp->slowpath->drv_info_to_mcp;

	अगर (bnx2x_ilt_mem_op_cnic(bp, ILT_MEMOP_ALLOC))
		जाओ alloc_mem_err;

	वापस 0;

alloc_mem_err:
	bnx2x_मुक्त_mem_cnic(bp);
	BNX2X_ERR("Can't allocate memory\n");
	वापस -ENOMEM;
पूर्ण

पूर्णांक bnx2x_alloc_mem(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i, allocated, context_size;

	अगर (!CONFIGURE_NIC_MODE(bp) && !bp->t2) अणु
		/* allocate searcher T2 table */
		bp->t2 = BNX2X_PCI_ALLOC(&bp->t2_mapping, SRC_T2_SZ);
		अगर (!bp->t2)
			जाओ alloc_mem_err;
	पूर्ण

	bp->def_status_blk = BNX2X_PCI_ALLOC(&bp->def_status_blk_mapping,
					     माप(काष्ठा host_sp_status_block));
	अगर (!bp->def_status_blk)
		जाओ alloc_mem_err;

	bp->slowpath = BNX2X_PCI_ALLOC(&bp->slowpath_mapping,
				       माप(काष्ठा bnx2x_slowpath));
	अगर (!bp->slowpath)
		जाओ alloc_mem_err;

	/* Allocate memory क्रम CDU context:
	 * This memory is allocated separately and not in the generic ILT
	 * functions because CDU dअगरfers in few aspects:
	 * 1. There are multiple entities allocating memory क्रम context -
	 * 'regular' driver, CNIC and SRIOV driver. Each separately controls
	 * its own ILT lines.
	 * 2. Since CDU page-size is not a single 4KB page (which is the हाल
	 * क्रम the other ILT clients), to be efficient we want to support
	 * allocation of sub-page-size in the last entry.
	 * 3. Context poपूर्णांकers are used by the driver to pass to FW / update
	 * the context (क्रम the other ILT clients the poपूर्णांकers are used just to
	 * मुक्त the memory during unload).
	 */
	context_size = माप(जोड़ cdu_context) * BNX2X_L2_CID_COUNT(bp);

	क्रम (i = 0, allocated = 0; allocated < context_size; i++) अणु
		bp->context[i].size = min(CDU_ILT_PAGE_SZ,
					  (context_size - allocated));
		bp->context[i].vcxt = BNX2X_PCI_ALLOC(&bp->context[i].cxt_mapping,
						      bp->context[i].size);
		अगर (!bp->context[i].vcxt)
			जाओ alloc_mem_err;
		allocated += bp->context[i].size;
	पूर्ण
	bp->ilt->lines = kसुस्मृति(ILT_MAX_LINES, माप(काष्ठा ilt_line),
				 GFP_KERNEL);
	अगर (!bp->ilt->lines)
		जाओ alloc_mem_err;

	अगर (bnx2x_ilt_mem_op(bp, ILT_MEMOP_ALLOC))
		जाओ alloc_mem_err;

	अगर (bnx2x_iov_alloc_mem(bp))
		जाओ alloc_mem_err;

	/* Slow path ring */
	bp->spq = BNX2X_PCI_ALLOC(&bp->spq_mapping, BCM_PAGE_SIZE);
	अगर (!bp->spq)
		जाओ alloc_mem_err;

	/* EQ */
	bp->eq_ring = BNX2X_PCI_ALLOC(&bp->eq_mapping,
				      BCM_PAGE_SIZE * NUM_EQ_PAGES);
	अगर (!bp->eq_ring)
		जाओ alloc_mem_err;

	वापस 0;

alloc_mem_err:
	bnx2x_मुक्त_mem(bp);
	BNX2X_ERR("Can't allocate memory\n");
	वापस -ENOMEM;
पूर्ण

/*
 * Init service functions
 */

पूर्णांक bnx2x_set_mac_one(काष्ठा bnx2x *bp, u8 *mac,
		      काष्ठा bnx2x_vlan_mac_obj *obj, bool set,
		      पूर्णांक mac_type, अचिन्हित दीर्घ *ramrod_flags)
अणु
	पूर्णांक rc;
	काष्ठा bnx2x_vlan_mac_ramrod_params ramrod_param;

	स_रखो(&ramrod_param, 0, माप(ramrod_param));

	/* Fill general parameters */
	ramrod_param.vlan_mac_obj = obj;
	ramrod_param.ramrod_flags = *ramrod_flags;

	/* Fill a user request section अगर needed */
	अगर (!test_bit(RAMROD_CONT, ramrod_flags)) अणु
		स_नकल(ramrod_param.user_req.u.mac.mac, mac, ETH_ALEN);

		__set_bit(mac_type, &ramrod_param.user_req.vlan_mac_flags);

		/* Set the command: ADD or DEL */
		अगर (set)
			ramrod_param.user_req.cmd = BNX2X_VLAN_MAC_ADD;
		अन्यथा
			ramrod_param.user_req.cmd = BNX2X_VLAN_MAC_DEL;
	पूर्ण

	rc = bnx2x_config_vlan_mac(bp, &ramrod_param);

	अगर (rc == -EEXIST) अणु
		DP(BNX2X_MSG_SP, "Failed to schedule ADD operations: %d\n", rc);
		/* करो not treat adding same MAC as error */
		rc = 0;
	पूर्ण अन्यथा अगर (rc < 0)
		BNX2X_ERR("%s MAC failed\n", (set ? "Set" : "Del"));

	वापस rc;
पूर्ण

पूर्णांक bnx2x_set_vlan_one(काष्ठा bnx2x *bp, u16 vlan,
		       काष्ठा bnx2x_vlan_mac_obj *obj, bool set,
		       अचिन्हित दीर्घ *ramrod_flags)
अणु
	पूर्णांक rc;
	काष्ठा bnx2x_vlan_mac_ramrod_params ramrod_param;

	स_रखो(&ramrod_param, 0, माप(ramrod_param));

	/* Fill general parameters */
	ramrod_param.vlan_mac_obj = obj;
	ramrod_param.ramrod_flags = *ramrod_flags;

	/* Fill a user request section अगर needed */
	अगर (!test_bit(RAMROD_CONT, ramrod_flags)) अणु
		ramrod_param.user_req.u.vlan.vlan = vlan;
		__set_bit(BNX2X_VLAN, &ramrod_param.user_req.vlan_mac_flags);
		/* Set the command: ADD or DEL */
		अगर (set)
			ramrod_param.user_req.cmd = BNX2X_VLAN_MAC_ADD;
		अन्यथा
			ramrod_param.user_req.cmd = BNX2X_VLAN_MAC_DEL;
	पूर्ण

	rc = bnx2x_config_vlan_mac(bp, &ramrod_param);

	अगर (rc == -EEXIST) अणु
		/* Do not treat adding same vlan as error. */
		DP(BNX2X_MSG_SP, "Failed to schedule ADD operations: %d\n", rc);
		rc = 0;
	पूर्ण अन्यथा अगर (rc < 0) अणु
		BNX2X_ERR("%s VLAN failed\n", (set ? "Set" : "Del"));
	पूर्ण

	वापस rc;
पूर्ण

व्योम bnx2x_clear_vlan_info(काष्ठा bnx2x *bp)
अणु
	काष्ठा bnx2x_vlan_entry *vlan;

	/* Mark that hw क्रमgot all entries */
	list_क्रम_each_entry(vlan, &bp->vlan_reg, link)
		vlan->hw = false;

	bp->vlan_cnt = 0;
पूर्ण

अटल पूर्णांक bnx2x_del_all_vlans(काष्ठा bnx2x *bp)
अणु
	काष्ठा bnx2x_vlan_mac_obj *vlan_obj = &bp->sp_objs[0].vlan_obj;
	अचिन्हित दीर्घ ramrod_flags = 0, vlan_flags = 0;
	पूर्णांक rc;

	__set_bit(RAMROD_COMP_WAIT, &ramrod_flags);
	__set_bit(BNX2X_VLAN, &vlan_flags);
	rc = vlan_obj->delete_all(bp, vlan_obj, &vlan_flags, &ramrod_flags);
	अगर (rc)
		वापस rc;

	bnx2x_clear_vlan_info(bp);

	वापस 0;
पूर्ण

पूर्णांक bnx2x_del_all_macs(काष्ठा bnx2x *bp,
		       काष्ठा bnx2x_vlan_mac_obj *mac_obj,
		       पूर्णांक mac_type, bool रुको_क्रम_comp)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ ramrod_flags = 0, vlan_mac_flags = 0;

	/* Wait क्रम completion of requested */
	अगर (रुको_क्रम_comp)
		__set_bit(RAMROD_COMP_WAIT, &ramrod_flags);

	/* Set the mac type of addresses we want to clear */
	__set_bit(mac_type, &vlan_mac_flags);

	rc = mac_obj->delete_all(bp, mac_obj, &vlan_mac_flags, &ramrod_flags);
	अगर (rc < 0)
		BNX2X_ERR("Failed to delete MACs: %d\n", rc);

	वापस rc;
पूर्ण

पूर्णांक bnx2x_set_eth_mac(काष्ठा bnx2x *bp, bool set)
अणु
	अगर (IS_PF(bp)) अणु
		अचिन्हित दीर्घ ramrod_flags = 0;

		DP(NETIF_MSG_IFUP, "Adding Eth MAC\n");
		__set_bit(RAMROD_COMP_WAIT, &ramrod_flags);
		वापस bnx2x_set_mac_one(bp, bp->dev->dev_addr,
					 &bp->sp_objs->mac_obj, set,
					 BNX2X_ETH_MAC, &ramrod_flags);
	पूर्ण अन्यथा अणु /* vf */
		वापस bnx2x_vfpf_config_mac(bp, bp->dev->dev_addr,
					     bp->fp->index, set);
	पूर्ण
पूर्ण

पूर्णांक bnx2x_setup_leading(काष्ठा bnx2x *bp)
अणु
	अगर (IS_PF(bp))
		वापस bnx2x_setup_queue(bp, &bp->fp[0], true);
	अन्यथा /* VF */
		वापस bnx2x_vfpf_setup_q(bp, &bp->fp[0], true);
पूर्ण

/**
 * bnx2x_set_पूर्णांक_mode - configure पूर्णांकerrupt mode
 *
 * @bp:		driver handle
 *
 * In हाल of MSI-X it will also try to enable MSI-X.
 */
पूर्णांक bnx2x_set_पूर्णांक_mode(काष्ठा bnx2x *bp)
अणु
	पूर्णांक rc = 0;

	अगर (IS_VF(bp) && पूर्णांक_mode != BNX2X_INT_MODE_MSIX) अणु
		BNX2X_ERR("VF not loaded since interrupt mode not msix\n");
		वापस -EINVAL;
	पूर्ण

	चयन (पूर्णांक_mode) अणु
	हाल BNX2X_INT_MODE_MSIX:
		/* attempt to enable msix */
		rc = bnx2x_enable_msix(bp);

		/* msix attained */
		अगर (!rc)
			वापस 0;

		/* vfs use only msix */
		अगर (rc && IS_VF(bp))
			वापस rc;

		/* failed to enable multiple MSI-X */
		BNX2X_DEV_INFO("Failed to enable multiple MSI-X (%d), set number of queues to %d\n",
			       bp->num_queues,
			       1 + bp->num_cnic_queues);

		fallthrough;
	हाल BNX2X_INT_MODE_MSI:
		bnx2x_enable_msi(bp);

		fallthrough;
	हाल BNX2X_INT_MODE_INTX:
		bp->num_ethernet_queues = 1;
		bp->num_queues = bp->num_ethernet_queues + bp->num_cnic_queues;
		BNX2X_DEV_INFO("set number of queues to 1\n");
		अवरोध;
	शेष:
		BNX2X_DEV_INFO("unknown value in int_mode module parameter\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* must be called prior to any HW initializations */
अटल अंतरभूत u16 bnx2x_cid_ilt_lines(काष्ठा bnx2x *bp)
अणु
	अगर (IS_SRIOV(bp))
		वापस (BNX2X_FIRST_VF_CID + BNX2X_VF_CIDS)/ILT_PAGE_CIDS;
	वापस L2_ILT_LINES(bp);
पूर्ण

व्योम bnx2x_ilt_set_info(काष्ठा bnx2x *bp)
अणु
	काष्ठा ilt_client_info *ilt_client;
	काष्ठा bnx2x_ilt *ilt = BP_ILT(bp);
	u16 line = 0;

	ilt->start_line = FUNC_ILT_BASE(BP_FUNC(bp));
	DP(BNX2X_MSG_SP, "ilt starts at line %d\n", ilt->start_line);

	/* CDU */
	ilt_client = &ilt->clients[ILT_CLIENT_CDU];
	ilt_client->client_num = ILT_CLIENT_CDU;
	ilt_client->page_size = CDU_ILT_PAGE_SZ;
	ilt_client->flags = ILT_CLIENT_SKIP_MEM;
	ilt_client->start = line;
	line += bnx2x_cid_ilt_lines(bp);

	अगर (CNIC_SUPPORT(bp))
		line += CNIC_ILT_LINES;
	ilt_client->end = line - 1;

	DP(NETIF_MSG_IFUP, "ilt client[CDU]: start %d, end %d, psz 0x%x, flags 0x%x, hw psz %d\n",
	   ilt_client->start,
	   ilt_client->end,
	   ilt_client->page_size,
	   ilt_client->flags,
	   ilog2(ilt_client->page_size >> 12));

	/* QM */
	अगर (QM_INIT(bp->qm_cid_count)) अणु
		ilt_client = &ilt->clients[ILT_CLIENT_QM];
		ilt_client->client_num = ILT_CLIENT_QM;
		ilt_client->page_size = QM_ILT_PAGE_SZ;
		ilt_client->flags = 0;
		ilt_client->start = line;

		/* 4 bytes क्रम each cid */
		line += DIV_ROUND_UP(bp->qm_cid_count * QM_QUEUES_PER_FUNC * 4,
							 QM_ILT_PAGE_SZ);

		ilt_client->end = line - 1;

		DP(NETIF_MSG_IFUP,
		   "ilt client[QM]: start %d, end %d, psz 0x%x, flags 0x%x, hw psz %d\n",
		   ilt_client->start,
		   ilt_client->end,
		   ilt_client->page_size,
		   ilt_client->flags,
		   ilog2(ilt_client->page_size >> 12));
	पूर्ण

	अगर (CNIC_SUPPORT(bp)) अणु
		/* SRC */
		ilt_client = &ilt->clients[ILT_CLIENT_SRC];
		ilt_client->client_num = ILT_CLIENT_SRC;
		ilt_client->page_size = SRC_ILT_PAGE_SZ;
		ilt_client->flags = 0;
		ilt_client->start = line;
		line += SRC_ILT_LINES;
		ilt_client->end = line - 1;

		DP(NETIF_MSG_IFUP,
		   "ilt client[SRC]: start %d, end %d, psz 0x%x, flags 0x%x, hw psz %d\n",
		   ilt_client->start,
		   ilt_client->end,
		   ilt_client->page_size,
		   ilt_client->flags,
		   ilog2(ilt_client->page_size >> 12));

		/* TM */
		ilt_client = &ilt->clients[ILT_CLIENT_TM];
		ilt_client->client_num = ILT_CLIENT_TM;
		ilt_client->page_size = TM_ILT_PAGE_SZ;
		ilt_client->flags = 0;
		ilt_client->start = line;
		line += TM_ILT_LINES;
		ilt_client->end = line - 1;

		DP(NETIF_MSG_IFUP,
		   "ilt client[TM]: start %d, end %d, psz 0x%x, flags 0x%x, hw psz %d\n",
		   ilt_client->start,
		   ilt_client->end,
		   ilt_client->page_size,
		   ilt_client->flags,
		   ilog2(ilt_client->page_size >> 12));
	पूर्ण

	BUG_ON(line > ILT_MAX_LINES);
पूर्ण

/**
 * bnx2x_pf_q_prep_init - prepare INIT transition parameters
 *
 * @bp:			driver handle
 * @fp:			poपूर्णांकer to fastpath
 * @init_params:	poपूर्णांकer to parameters काष्ठाure
 *
 * parameters configured:
 *      - HC configuration
 *      - Queue's CDU context
 */
अटल व्योम bnx2x_pf_q_prep_init(काष्ठा bnx2x *bp,
	काष्ठा bnx2x_fastpath *fp, काष्ठा bnx2x_queue_init_params *init_params)
अणु
	u8 cos;
	पूर्णांक cxt_index, cxt_offset;

	/* FCoE Queue uses Default SB, thus has no HC capabilities */
	अगर (!IS_FCOE_FP(fp)) अणु
		__set_bit(BNX2X_Q_FLG_HC, &init_params->rx.flags);
		__set_bit(BNX2X_Q_FLG_HC, &init_params->tx.flags);

		/* If HC is supported, enable host coalescing in the transition
		 * to INIT state.
		 */
		__set_bit(BNX2X_Q_FLG_HC_EN, &init_params->rx.flags);
		__set_bit(BNX2X_Q_FLG_HC_EN, &init_params->tx.flags);

		/* HC rate */
		init_params->rx.hc_rate = bp->rx_ticks ?
			(1000000 / bp->rx_ticks) : 0;
		init_params->tx.hc_rate = bp->tx_ticks ?
			(1000000 / bp->tx_ticks) : 0;

		/* FW SB ID */
		init_params->rx.fw_sb_id = init_params->tx.fw_sb_id =
			fp->fw_sb_id;

		/*
		 * CQ index among the SB indices: FCoE clients uses the शेष
		 * SB, thereक्रमe it's dअगरferent.
		 */
		init_params->rx.sb_cq_index = HC_INDEX_ETH_RX_CQ_CONS;
		init_params->tx.sb_cq_index = HC_INDEX_ETH_FIRST_TX_CQ_CONS;
	पूर्ण

	/* set maximum number of COSs supported by this queue */
	init_params->max_cos = fp->max_cos;

	DP(NETIF_MSG_IFUP, "fp: %d setting queue params max cos to: %d\n",
	    fp->index, init_params->max_cos);

	/* set the context poपूर्णांकers queue object */
	क्रम (cos = FIRST_TX_COS_INDEX; cos < init_params->max_cos; cos++) अणु
		cxt_index = fp->txdata_ptr[cos]->cid / ILT_PAGE_CIDS;
		cxt_offset = fp->txdata_ptr[cos]->cid - (cxt_index *
				ILT_PAGE_CIDS);
		init_params->cxts[cos] =
			&bp->context[cxt_index].vcxt[cxt_offset].eth;
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_setup_tx_only(काष्ठा bnx2x *bp, काष्ठा bnx2x_fastpath *fp,
			काष्ठा bnx2x_queue_state_params *q_params,
			काष्ठा bnx2x_queue_setup_tx_only_params *tx_only_params,
			पूर्णांक tx_index, bool leading)
अणु
	स_रखो(tx_only_params, 0, माप(*tx_only_params));

	/* Set the command */
	q_params->cmd = BNX2X_Q_CMD_SETUP_TX_ONLY;

	/* Set tx-only QUEUE flags: करोn't zero statistics */
	tx_only_params->flags = bnx2x_get_common_flags(bp, fp, false);

	/* choose the index of the cid to send the slow path on */
	tx_only_params->cid_index = tx_index;

	/* Set general TX_ONLY_SETUP parameters */
	bnx2x_pf_q_prep_general(bp, fp, &tx_only_params->gen_params, tx_index);

	/* Set Tx TX_ONLY_SETUP parameters */
	bnx2x_pf_tx_q_prep(bp, fp, &tx_only_params->txq_params, tx_index);

	DP(NETIF_MSG_IFUP,
	   "preparing to send tx-only ramrod for connection: cos %d, primary cid %d, cid %d, client id %d, sp-client id %d, flags %lx\n",
	   tx_index, q_params->q_obj->cids[FIRST_TX_COS_INDEX],
	   q_params->q_obj->cids[tx_index], q_params->q_obj->cl_id,
	   tx_only_params->gen_params.spcl_id, tx_only_params->flags);

	/* send the ramrod */
	वापस bnx2x_queue_state_change(bp, q_params);
पूर्ण

/**
 * bnx2x_setup_queue - setup queue
 *
 * @bp:		driver handle
 * @fp:		poपूर्णांकer to fastpath
 * @leading:	is leading
 *
 * This function perक्रमms 2 steps in a Queue state machine
 *      actually: 1) RESET->INIT 2) INIT->SETUP
 */

पूर्णांक bnx2x_setup_queue(काष्ठा bnx2x *bp, काष्ठा bnx2x_fastpath *fp,
		       bool leading)
अणु
	काष्ठा bnx2x_queue_state_params q_params = अणुशून्यपूर्ण;
	काष्ठा bnx2x_queue_setup_params *setup_params =
						&q_params.params.setup;
	काष्ठा bnx2x_queue_setup_tx_only_params *tx_only_params =
						&q_params.params.tx_only;
	पूर्णांक rc;
	u8 tx_index;

	DP(NETIF_MSG_IFUP, "setting up queue %d\n", fp->index);

	/* reset IGU state skip FCoE L2 queue */
	अगर (!IS_FCOE_FP(fp))
		bnx2x_ack_sb(bp, fp->igu_sb_id, USTORM_ID, 0,
			     IGU_INT_ENABLE, 0);

	q_params.q_obj = &bnx2x_sp_obj(bp, fp).q_obj;
	/* We want to रुको क्रम completion in this context */
	__set_bit(RAMROD_COMP_WAIT, &q_params.ramrod_flags);

	/* Prepare the INIT parameters */
	bnx2x_pf_q_prep_init(bp, fp, &q_params.params.init);

	/* Set the command */
	q_params.cmd = BNX2X_Q_CMD_INIT;

	/* Change the state to INIT */
	rc = bnx2x_queue_state_change(bp, &q_params);
	अगर (rc) अणु
		BNX2X_ERR("Queue(%d) INIT failed\n", fp->index);
		वापस rc;
	पूर्ण

	DP(NETIF_MSG_IFUP, "init complete\n");

	/* Now move the Queue to the SETUP state... */
	स_रखो(setup_params, 0, माप(*setup_params));

	/* Set QUEUE flags */
	setup_params->flags = bnx2x_get_q_flags(bp, fp, leading);

	/* Set general SETUP parameters */
	bnx2x_pf_q_prep_general(bp, fp, &setup_params->gen_params,
				FIRST_TX_COS_INDEX);

	bnx2x_pf_rx_q_prep(bp, fp, &setup_params->छोड़ो_params,
			    &setup_params->rxq_params);

	bnx2x_pf_tx_q_prep(bp, fp, &setup_params->txq_params,
			   FIRST_TX_COS_INDEX);

	/* Set the command */
	q_params.cmd = BNX2X_Q_CMD_SETUP;

	अगर (IS_FCOE_FP(fp))
		bp->fcoe_init = true;

	/* Change the state to SETUP */
	rc = bnx2x_queue_state_change(bp, &q_params);
	अगर (rc) अणु
		BNX2X_ERR("Queue(%d) SETUP failed\n", fp->index);
		वापस rc;
	पूर्ण

	/* loop through the relevant tx-only indices */
	क्रम (tx_index = FIRST_TX_ONLY_COS_INDEX;
	      tx_index < fp->max_cos;
	      tx_index++) अणु

		/* prepare and send tx-only ramrod*/
		rc = bnx2x_setup_tx_only(bp, fp, &q_params,
					  tx_only_params, tx_index, leading);
		अगर (rc) अणु
			BNX2X_ERR("Queue(%d.%d) TX_ONLY_SETUP failed\n",
				  fp->index, tx_index);
			वापस rc;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_stop_queue(काष्ठा bnx2x *bp, पूर्णांक index)
अणु
	काष्ठा bnx2x_fastpath *fp = &bp->fp[index];
	काष्ठा bnx2x_fp_txdata *txdata;
	काष्ठा bnx2x_queue_state_params q_params = अणुशून्यपूर्ण;
	पूर्णांक rc, tx_index;

	DP(NETIF_MSG_IFDOWN, "stopping queue %d cid %d\n", index, fp->cid);

	q_params.q_obj = &bnx2x_sp_obj(bp, fp).q_obj;
	/* We want to रुको क्रम completion in this context */
	__set_bit(RAMROD_COMP_WAIT, &q_params.ramrod_flags);

	/* बंद tx-only connections */
	क्रम (tx_index = FIRST_TX_ONLY_COS_INDEX;
	     tx_index < fp->max_cos;
	     tx_index++)अणु

		/* ascertain this is a normal queue*/
		txdata = fp->txdata_ptr[tx_index];

		DP(NETIF_MSG_IFDOWN, "stopping tx-only queue %d\n",
							txdata->txq_index);

		/* send halt terminate on tx-only connection */
		q_params.cmd = BNX2X_Q_CMD_TERMINATE;
		स_रखो(&q_params.params.terminate, 0,
		       माप(q_params.params.terminate));
		q_params.params.terminate.cid_index = tx_index;

		rc = bnx2x_queue_state_change(bp, &q_params);
		अगर (rc)
			वापस rc;

		/* send halt terminate on tx-only connection */
		q_params.cmd = BNX2X_Q_CMD_CFC_DEL;
		स_रखो(&q_params.params.cfc_del, 0,
		       माप(q_params.params.cfc_del));
		q_params.params.cfc_del.cid_index = tx_index;
		rc = bnx2x_queue_state_change(bp, &q_params);
		अगर (rc)
			वापस rc;
	पूर्ण
	/* Stop the primary connection: */
	/* ...halt the connection */
	q_params.cmd = BNX2X_Q_CMD_HALT;
	rc = bnx2x_queue_state_change(bp, &q_params);
	अगर (rc)
		वापस rc;

	/* ...terminate the connection */
	q_params.cmd = BNX2X_Q_CMD_TERMINATE;
	स_रखो(&q_params.params.terminate, 0,
	       माप(q_params.params.terminate));
	q_params.params.terminate.cid_index = FIRST_TX_COS_INDEX;
	rc = bnx2x_queue_state_change(bp, &q_params);
	अगर (rc)
		वापस rc;
	/* ...delete cfc entry */
	q_params.cmd = BNX2X_Q_CMD_CFC_DEL;
	स_रखो(&q_params.params.cfc_del, 0,
	       माप(q_params.params.cfc_del));
	q_params.params.cfc_del.cid_index = FIRST_TX_COS_INDEX;
	वापस bnx2x_queue_state_change(bp, &q_params);
पूर्ण

अटल व्योम bnx2x_reset_func(काष्ठा bnx2x *bp)
अणु
	पूर्णांक port = BP_PORT(bp);
	पूर्णांक func = BP_FUNC(bp);
	पूर्णांक i;

	/* Disable the function in the FW */
	REG_WR8(bp, BAR_XSTRORM_INTMEM + XSTORM_FUNC_EN_OFFSET(func), 0);
	REG_WR8(bp, BAR_CSTRORM_INTMEM + CSTORM_FUNC_EN_OFFSET(func), 0);
	REG_WR8(bp, BAR_TSTRORM_INTMEM + TSTORM_FUNC_EN_OFFSET(func), 0);
	REG_WR8(bp, BAR_USTRORM_INTMEM + USTORM_FUNC_EN_OFFSET(func), 0);

	/* FP SBs */
	क्रम_each_eth_queue(bp, i) अणु
		काष्ठा bnx2x_fastpath *fp = &bp->fp[i];
		REG_WR8(bp, BAR_CSTRORM_INTMEM +
			   CSTORM_STATUS_BLOCK_DATA_STATE_OFFSET(fp->fw_sb_id),
			   SB_DISABLED);
	पूर्ण

	अगर (CNIC_LOADED(bp))
		/* CNIC SB */
		REG_WR8(bp, BAR_CSTRORM_INTMEM +
			CSTORM_STATUS_BLOCK_DATA_STATE_OFFSET
			(bnx2x_cnic_fw_sb_id(bp)), SB_DISABLED);

	/* SP SB */
	REG_WR8(bp, BAR_CSTRORM_INTMEM +
		CSTORM_SP_STATUS_BLOCK_DATA_STATE_OFFSET(func),
		SB_DISABLED);

	क्रम (i = 0; i < XSTORM_SPQ_DATA_SIZE / 4; i++)
		REG_WR(bp, BAR_XSTRORM_INTMEM + XSTORM_SPQ_DATA_OFFSET(func),
		       0);

	/* Configure IGU */
	अगर (bp->common.पूर्णांक_block == INT_BLOCK_HC) अणु
		REG_WR(bp, HC_REG_LEADING_EDGE_0 + port*8, 0);
		REG_WR(bp, HC_REG_TRAILING_EDGE_0 + port*8, 0);
	पूर्ण अन्यथा अणु
		REG_WR(bp, IGU_REG_LEADING_EDGE_LATCH, 0);
		REG_WR(bp, IGU_REG_TRAILING_EDGE_LATCH, 0);
	पूर्ण

	अगर (CNIC_LOADED(bp)) अणु
		/* Disable Timer scan */
		REG_WR(bp, TM_REG_EN_LINEAR0_TIMER + port*4, 0);
		/*
		 * Wait क्रम at least 10ms and up to 2 second क्रम the समयrs
		 * scan to complete
		 */
		क्रम (i = 0; i < 200; i++) अणु
			usleep_range(10000, 20000);
			अगर (!REG_RD(bp, TM_REG_LIN0_SCAN_ON + port*4))
				अवरोध;
		पूर्ण
	पूर्ण
	/* Clear ILT */
	bnx2x_clear_func_ilt(bp, func);

	/* Timers workaround bug क्रम E2: अगर this is vnic-3,
	 * we need to set the entire ilt range क्रम this समयrs.
	 */
	अगर (!CHIP_IS_E1x(bp) && BP_VN(bp) == 3) अणु
		काष्ठा ilt_client_info ilt_cli;
		/* use dummy TM client */
		स_रखो(&ilt_cli, 0, माप(काष्ठा ilt_client_info));
		ilt_cli.start = 0;
		ilt_cli.end = ILT_NUM_PAGE_ENTRIES - 1;
		ilt_cli.client_num = ILT_CLIENT_TM;

		bnx2x_ilt_boundry_init_op(bp, &ilt_cli, 0, INITOP_CLEAR);
	पूर्ण

	/* this assumes that reset_port() called beक्रमe reset_func()*/
	अगर (!CHIP_IS_E1x(bp))
		bnx2x_pf_disable(bp);

	bp->dmae_पढ़ोy = 0;
पूर्ण

अटल व्योम bnx2x_reset_port(काष्ठा bnx2x *bp)
अणु
	पूर्णांक port = BP_PORT(bp);
	u32 val;

	/* Reset physical Link */
	bnx2x__link_reset(bp);

	REG_WR(bp, NIG_REG_MASK_INTERRUPT_PORT0 + port*4, 0);

	/* Do not rcv packets to BRB */
	REG_WR(bp, NIG_REG_LLH0_BRB1_DRV_MASK + port*4, 0x0);
	/* Do not direct rcv packets that are not क्रम MCP to the BRB */
	REG_WR(bp, (port ? NIG_REG_LLH1_BRB1_NOT_MCP :
			   NIG_REG_LLH0_BRB1_NOT_MCP), 0x0);

	/* Configure AEU */
	REG_WR(bp, MISC_REG_AEU_MASK_ATTN_FUNC_0 + port*4, 0);

	msleep(100);
	/* Check क्रम BRB port occupancy */
	val = REG_RD(bp, BRB1_REG_PORT_NUM_OCC_BLOCKS_0 + port*4);
	अगर (val)
		DP(NETIF_MSG_IFDOWN,
		   "BRB1 is not empty  %d blocks are occupied\n", val);

	/* TODO: Close Doorbell port? */
पूर्ण

अटल पूर्णांक bnx2x_reset_hw(काष्ठा bnx2x *bp, u32 load_code)
अणु
	काष्ठा bnx2x_func_state_params func_params = अणुशून्यपूर्ण;

	/* Prepare parameters क्रम function state transitions */
	__set_bit(RAMROD_COMP_WAIT, &func_params.ramrod_flags);

	func_params.f_obj = &bp->func_obj;
	func_params.cmd = BNX2X_F_CMD_HW_RESET;

	func_params.params.hw_init.load_phase = load_code;

	वापस bnx2x_func_state_change(bp, &func_params);
पूर्ण

अटल पूर्णांक bnx2x_func_stop(काष्ठा bnx2x *bp)
अणु
	काष्ठा bnx2x_func_state_params func_params = अणुशून्यपूर्ण;
	पूर्णांक rc;

	/* Prepare parameters क्रम function state transitions */
	__set_bit(RAMROD_COMP_WAIT, &func_params.ramrod_flags);
	func_params.f_obj = &bp->func_obj;
	func_params.cmd = BNX2X_F_CMD_STOP;

	/*
	 * Try to stop the function the 'good way'. If fails (in हाल
	 * of a parity error during bnx2x_chip_cleanup()) and we are
	 * not in a debug mode, perक्रमm a state transaction in order to
	 * enable further HW_RESET transaction.
	 */
	rc = bnx2x_func_state_change(bp, &func_params);
	अगर (rc) अणु
#अगर_घोषित BNX2X_STOP_ON_ERROR
		वापस rc;
#अन्यथा
		BNX2X_ERR("FUNC_STOP ramrod failed. Running a dry transaction\n");
		__set_bit(RAMROD_DRV_CLR_ONLY, &func_params.ramrod_flags);
		वापस bnx2x_func_state_change(bp, &func_params);
#पूर्ण_अगर
	पूर्ण

	वापस 0;
पूर्ण

/**
 * bnx2x_send_unload_req - request unload mode from the MCP.
 *
 * @bp:			driver handle
 * @unload_mode:	requested function's unload mode
 *
 * Return unload mode वापसed by the MCP: COMMON, PORT or FUNC.
 */
u32 bnx2x_send_unload_req(काष्ठा bnx2x *bp, पूर्णांक unload_mode)
अणु
	u32 reset_code = 0;
	पूर्णांक port = BP_PORT(bp);

	/* Select the UNLOAD request mode */
	अगर (unload_mode == UNLOAD_NORMAL)
		reset_code = DRV_MSG_CODE_UNLOAD_REQ_WOL_DIS;

	अन्यथा अगर (bp->flags & NO_WOL_FLAG)
		reset_code = DRV_MSG_CODE_UNLOAD_REQ_WOL_MCP;

	अन्यथा अगर (bp->wol) अणु
		u32 emac_base = port ? GRCBASE_EMAC1 : GRCBASE_EMAC0;
		u8 *mac_addr = bp->dev->dev_addr;
		काष्ठा pci_dev *pdev = bp->pdev;
		u32 val;
		u16 pmc;

		/* The mac address is written to entries 1-4 to
		 * preserve entry 0 which is used by the PMF
		 */
		u8 entry = (BP_VN(bp) + 1)*8;

		val = (mac_addr[0] << 8) | mac_addr[1];
		EMAC_WR(bp, EMAC_REG_EMAC_MAC_MATCH + entry, val);

		val = (mac_addr[2] << 24) | (mac_addr[3] << 16) |
		      (mac_addr[4] << 8) | mac_addr[5];
		EMAC_WR(bp, EMAC_REG_EMAC_MAC_MATCH + entry + 4, val);

		/* Enable the PME and clear the status */
		pci_पढ़ो_config_word(pdev, pdev->pm_cap + PCI_PM_CTRL, &pmc);
		pmc |= PCI_PM_CTRL_PME_ENABLE | PCI_PM_CTRL_PME_STATUS;
		pci_ग_लिखो_config_word(pdev, pdev->pm_cap + PCI_PM_CTRL, pmc);

		reset_code = DRV_MSG_CODE_UNLOAD_REQ_WOL_EN;

	पूर्ण अन्यथा
		reset_code = DRV_MSG_CODE_UNLOAD_REQ_WOL_DIS;

	/* Send the request to the MCP */
	अगर (!BP_NOMCP(bp))
		reset_code = bnx2x_fw_command(bp, reset_code, 0);
	अन्यथा अणु
		पूर्णांक path = BP_PATH(bp);

		DP(NETIF_MSG_IFDOWN, "NO MCP - load counts[%d]      %d, %d, %d\n",
		   path, bnx2x_load_count[path][0], bnx2x_load_count[path][1],
		   bnx2x_load_count[path][2]);
		bnx2x_load_count[path][0]--;
		bnx2x_load_count[path][1 + port]--;
		DP(NETIF_MSG_IFDOWN, "NO MCP - new load counts[%d]  %d, %d, %d\n",
		   path, bnx2x_load_count[path][0], bnx2x_load_count[path][1],
		   bnx2x_load_count[path][2]);
		अगर (bnx2x_load_count[path][0] == 0)
			reset_code = FW_MSG_CODE_DRV_UNLOAD_COMMON;
		अन्यथा अगर (bnx2x_load_count[path][1 + port] == 0)
			reset_code = FW_MSG_CODE_DRV_UNLOAD_PORT;
		अन्यथा
			reset_code = FW_MSG_CODE_DRV_UNLOAD_FUNCTION;
	पूर्ण

	वापस reset_code;
पूर्ण

/**
 * bnx2x_send_unload_करोne - send UNLOAD_DONE command to the MCP.
 *
 * @bp:		driver handle
 * @keep_link:		true अगरf link should be kept up
 */
व्योम bnx2x_send_unload_करोne(काष्ठा bnx2x *bp, bool keep_link)
अणु
	u32 reset_param = keep_link ? DRV_MSG_CODE_UNLOAD_SKIP_LINK_RESET : 0;

	/* Report UNLOAD_DONE to MCP */
	अगर (!BP_NOMCP(bp))
		bnx2x_fw_command(bp, DRV_MSG_CODE_UNLOAD_DONE, reset_param);
पूर्ण

अटल पूर्णांक bnx2x_func_रुको_started(काष्ठा bnx2x *bp)
अणु
	पूर्णांक tout = 50;
	पूर्णांक msix = (bp->flags & USING_MSIX_FLAG) ? 1 : 0;

	अगर (!bp->port.pmf)
		वापस 0;

	/*
	 * (assumption: No Attention from MCP at this stage)
	 * PMF probably in the middle of TX disable/enable transaction
	 * 1. Sync IRS क्रम शेष SB
	 * 2. Sync SP queue - this guarantees us that attention handling started
	 * 3. Wait, that TX disable/enable transaction completes
	 *
	 * 1+2 guarantee that अगर DCBx attention was scheduled it alपढ़ोy changed
	 * pending bit of transaction from STARTED-->TX_STOPPED, अगर we alपढ़ोy
	 * received completion क्रम the transaction the state is TX_STOPPED.
	 * State will वापस to STARTED after completion of TX_STOPPED-->STARTED
	 * transaction.
	 */

	/* make sure शेष SB ISR is करोne */
	अगर (msix)
		synchronize_irq(bp->msix_table[0].vector);
	अन्यथा
		synchronize_irq(bp->pdev->irq);

	flush_workqueue(bnx2x_wq);
	flush_workqueue(bnx2x_iov_wq);

	जबतक (bnx2x_func_get_state(bp, &bp->func_obj) !=
				BNX2X_F_STATE_STARTED && tout--)
		msleep(20);

	अगर (bnx2x_func_get_state(bp, &bp->func_obj) !=
						BNX2X_F_STATE_STARTED) अणु
#अगर_घोषित BNX2X_STOP_ON_ERROR
		BNX2X_ERR("Wrong function state\n");
		वापस -EBUSY;
#अन्यथा
		/*
		 * Failed to complete the transaction in a "good way"
		 * Force both transactions with CLR bit
		 */
		काष्ठा bnx2x_func_state_params func_params = अणुशून्यपूर्ण;

		DP(NETIF_MSG_IFDOWN,
		   "Hmmm... Unexpected function state! Forcing STARTED-->TX_STOPPED-->STARTED\n");

		func_params.f_obj = &bp->func_obj;
		__set_bit(RAMROD_DRV_CLR_ONLY,
					&func_params.ramrod_flags);

		/* STARTED-->TX_ST0PPED */
		func_params.cmd = BNX2X_F_CMD_TX_STOP;
		bnx2x_func_state_change(bp, &func_params);

		/* TX_ST0PPED-->STARTED */
		func_params.cmd = BNX2X_F_CMD_TX_START;
		वापस bnx2x_func_state_change(bp, &func_params);
#पूर्ण_अगर
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bnx2x_disable_ptp(काष्ठा bnx2x *bp)
अणु
	पूर्णांक port = BP_PORT(bp);

	/* Disable sending PTP packets to host */
	REG_WR(bp, port ? NIG_REG_P1_LLH_PTP_TO_HOST :
	       NIG_REG_P0_LLH_PTP_TO_HOST, 0x0);

	/* Reset PTP event detection rules */
	REG_WR(bp, port ? NIG_REG_P1_LLH_PTP_PARAM_MASK :
	       NIG_REG_P0_LLH_PTP_PARAM_MASK, 0x7FF);
	REG_WR(bp, port ? NIG_REG_P1_LLH_PTP_RULE_MASK :
	       NIG_REG_P0_LLH_PTP_RULE_MASK, 0x3FFF);
	REG_WR(bp, port ? NIG_REG_P1_TLLH_PTP_PARAM_MASK :
	       NIG_REG_P0_TLLH_PTP_PARAM_MASK, 0x7FF);
	REG_WR(bp, port ? NIG_REG_P1_TLLH_PTP_RULE_MASK :
	       NIG_REG_P0_TLLH_PTP_RULE_MASK, 0x3FFF);

	/* Disable the PTP feature */
	REG_WR(bp, port ? NIG_REG_P1_PTP_EN :
	       NIG_REG_P0_PTP_EN, 0x0);
पूर्ण

/* Called during unload, to stop PTP-related stuff */
अटल व्योम bnx2x_stop_ptp(काष्ठा bnx2x *bp)
अणु
	/* Cancel PTP work queue. Should be करोne after the Tx queues are
	 * drained to prevent additional scheduling.
	 */
	cancel_work_sync(&bp->ptp_task);

	अगर (bp->ptp_tx_skb) अणु
		dev_kमुक्त_skb_any(bp->ptp_tx_skb);
		bp->ptp_tx_skb = शून्य;
	पूर्ण

	/* Disable PTP in HW */
	bnx2x_disable_ptp(bp);

	DP(BNX2X_MSG_PTP, "PTP stop ended successfully\n");
पूर्ण

व्योम bnx2x_chip_cleanup(काष्ठा bnx2x *bp, पूर्णांक unload_mode, bool keep_link)
अणु
	पूर्णांक port = BP_PORT(bp);
	पूर्णांक i, rc = 0;
	u8 cos;
	काष्ठा bnx2x_mcast_ramrod_params rparam = अणुशून्यपूर्ण;
	u32 reset_code;

	/* Wait until tx fastpath tasks complete */
	क्रम_each_tx_queue(bp, i) अणु
		काष्ठा bnx2x_fastpath *fp = &bp->fp[i];

		क्रम_each_cos_in_tx_queue(fp, cos)
			rc = bnx2x_clean_tx_queue(bp, fp->txdata_ptr[cos]);
#अगर_घोषित BNX2X_STOP_ON_ERROR
		अगर (rc)
			वापस;
#पूर्ण_अगर
	पूर्ण

	/* Give HW समय to discard old tx messages */
	usleep_range(1000, 2000);

	/* Clean all ETH MACs */
	rc = bnx2x_del_all_macs(bp, &bp->sp_objs[0].mac_obj, BNX2X_ETH_MAC,
				false);
	अगर (rc < 0)
		BNX2X_ERR("Failed to delete all ETH macs: %d\n", rc);

	/* Clean up UC list  */
	rc = bnx2x_del_all_macs(bp, &bp->sp_objs[0].mac_obj, BNX2X_UC_LIST_MAC,
				true);
	अगर (rc < 0)
		BNX2X_ERR("Failed to schedule DEL commands for UC MACs list: %d\n",
			  rc);

	/* The whole *vlan_obj काष्ठाure may be not initialized अगर VLAN
	 * filtering offload is not supported by hardware. Currently this is
	 * true क्रम all hardware covered by CHIP_IS_E1x().
	 */
	अगर (!CHIP_IS_E1x(bp)) अणु
		/* Remove all currently configured VLANs */
		rc = bnx2x_del_all_vlans(bp);
		अगर (rc < 0)
			BNX2X_ERR("Failed to delete all VLANs\n");
	पूर्ण

	/* Disable LLH */
	अगर (!CHIP_IS_E1(bp))
		REG_WR(bp, NIG_REG_LLH0_FUNC_EN + port*8, 0);

	/* Set "drop all" (stop Rx).
	 * We need to take a netअगर_addr_lock() here in order to prevent
	 * a race between the completion code and this code.
	 */
	netअगर_addr_lock_bh(bp->dev);
	/* Schedule the rx_mode command */
	अगर (test_bit(BNX2X_FILTER_RX_MODE_PENDING, &bp->sp_state))
		set_bit(BNX2X_FILTER_RX_MODE_SCHED, &bp->sp_state);
	अन्यथा अगर (bp->slowpath)
		bnx2x_set_storm_rx_mode(bp);

	/* Cleanup multicast configuration */
	rparam.mcast_obj = &bp->mcast_obj;
	rc = bnx2x_config_mcast(bp, &rparam, BNX2X_MCAST_CMD_DEL);
	अगर (rc < 0)
		BNX2X_ERR("Failed to send DEL multicast command: %d\n", rc);

	netअगर_addr_unlock_bh(bp->dev);

	bnx2x_iov_chip_cleanup(bp);

	/*
	 * Send the UNLOAD_REQUEST to the MCP. This will वापस अगर
	 * this function should perक्रमm FUNC, PORT or COMMON HW
	 * reset.
	 */
	reset_code = bnx2x_send_unload_req(bp, unload_mode);

	/*
	 * (assumption: No Attention from MCP at this stage)
	 * PMF probably in the middle of TX disable/enable transaction
	 */
	rc = bnx2x_func_रुको_started(bp);
	अगर (rc) अणु
		BNX2X_ERR("bnx2x_func_wait_started failed\n");
#अगर_घोषित BNX2X_STOP_ON_ERROR
		वापस;
#पूर्ण_अगर
	पूर्ण

	/* Close multi and leading connections
	 * Completions क्रम ramrods are collected in a synchronous way
	 */
	क्रम_each_eth_queue(bp, i)
		अगर (bnx2x_stop_queue(bp, i))
#अगर_घोषित BNX2X_STOP_ON_ERROR
			वापस;
#अन्यथा
			जाओ unload_error;
#पूर्ण_अगर

	अगर (CNIC_LOADED(bp)) अणु
		क्रम_each_cnic_queue(bp, i)
			अगर (bnx2x_stop_queue(bp, i))
#अगर_घोषित BNX2X_STOP_ON_ERROR
				वापस;
#अन्यथा
				जाओ unload_error;
#पूर्ण_अगर
	पूर्ण

	/* If SP settings didn't get completed so far - something
	 * very wrong has happen.
	 */
	अगर (!bnx2x_रुको_sp_comp(bp, ~0x0UL))
		BNX2X_ERR("Hmmm... Common slow path ramrods got stuck!\n");

#अगर_अघोषित BNX2X_STOP_ON_ERROR
unload_error:
#पूर्ण_अगर
	rc = bnx2x_func_stop(bp);
	अगर (rc) अणु
		BNX2X_ERR("Function stop failed!\n");
#अगर_घोषित BNX2X_STOP_ON_ERROR
		वापस;
#पूर्ण_अगर
	पूर्ण

	/* stop_ptp should be after the Tx queues are drained to prevent
	 * scheduling to the cancelled PTP work queue. It should also be after
	 * function stop ramrod is sent, since as part of this ramrod FW access
	 * PTP रेजिस्टरs.
	 */
	अगर (bp->flags & PTP_SUPPORTED) अणु
		bnx2x_stop_ptp(bp);
		अगर (bp->ptp_घड़ी) अणु
			ptp_घड़ी_unरेजिस्टर(bp->ptp_घड़ी);
			bp->ptp_घड़ी = शून्य;
		पूर्ण
	पूर्ण

	/* Disable HW पूर्णांकerrupts, NAPI */
	bnx2x_netअगर_stop(bp, 1);
	/* Delete all NAPI objects */
	bnx2x_del_all_napi(bp);
	अगर (CNIC_LOADED(bp))
		bnx2x_del_all_napi_cnic(bp);

	/* Release IRQs */
	bnx2x_मुक्त_irq(bp);

	/* Reset the chip, unless PCI function is offline. If we reach this
	 * poपूर्णांक following a PCI error handling, it means device is really
	 * in a bad state and we're about to हटाओ it, so reset the chip
	 * is not a good idea.
	 */
	अगर (!pci_channel_offline(bp->pdev)) अणु
		rc = bnx2x_reset_hw(bp, reset_code);
		अगर (rc)
			BNX2X_ERR("HW_RESET failed\n");
	पूर्ण

	/* Report UNLOAD_DONE to MCP */
	bnx2x_send_unload_करोne(bp, keep_link);
पूर्ण

व्योम bnx2x_disable_बंद_the_gate(काष्ठा bnx2x *bp)
अणु
	u32 val;

	DP(NETIF_MSG_IFDOWN, "Disabling \"close the gates\"\n");

	अगर (CHIP_IS_E1(bp)) अणु
		पूर्णांक port = BP_PORT(bp);
		u32 addr = port ? MISC_REG_AEU_MASK_ATTN_FUNC_1 :
			MISC_REG_AEU_MASK_ATTN_FUNC_0;

		val = REG_RD(bp, addr);
		val &= ~(0x300);
		REG_WR(bp, addr, val);
	पूर्ण अन्यथा अणु
		val = REG_RD(bp, MISC_REG_AEU_GENERAL_MASK);
		val &= ~(MISC_AEU_GENERAL_MASK_REG_AEU_PXP_CLOSE_MASK |
			 MISC_AEU_GENERAL_MASK_REG_AEU_NIG_CLOSE_MASK);
		REG_WR(bp, MISC_REG_AEU_GENERAL_MASK, val);
	पूर्ण
पूर्ण

/* Close gates #2, #3 and #4: */
अटल व्योम bnx2x_set_234_gates(काष्ठा bnx2x *bp, bool बंद)
अणु
	u32 val;

	/* Gates #2 and #4a are बंदd/खोलोed क्रम "not E1" only */
	अगर (!CHIP_IS_E1(bp)) अणु
		/* #4 */
		REG_WR(bp, PXP_REG_HST_DISCARD_DOORBELLS, !!बंद);
		/* #2 */
		REG_WR(bp, PXP_REG_HST_DISCARD_INTERNAL_WRITES, !!बंद);
	पूर्ण

	/* #3 */
	अगर (CHIP_IS_E1x(bp)) अणु
		/* Prevent पूर्णांकerrupts from HC on both ports */
		val = REG_RD(bp, HC_REG_CONFIG_1);
		REG_WR(bp, HC_REG_CONFIG_1,
		       (!बंद) ? (val | HC_CONFIG_1_REG_BLOCK_DISABLE_1) :
		       (val & ~(u32)HC_CONFIG_1_REG_BLOCK_DISABLE_1));

		val = REG_RD(bp, HC_REG_CONFIG_0);
		REG_WR(bp, HC_REG_CONFIG_0,
		       (!बंद) ? (val | HC_CONFIG_0_REG_BLOCK_DISABLE_0) :
		       (val & ~(u32)HC_CONFIG_0_REG_BLOCK_DISABLE_0));
	पूर्ण अन्यथा अणु
		/* Prevent incoming पूर्णांकerrupts in IGU */
		val = REG_RD(bp, IGU_REG_BLOCK_CONFIGURATION);

		REG_WR(bp, IGU_REG_BLOCK_CONFIGURATION,
		       (!बंद) ?
		       (val | IGU_BLOCK_CONFIGURATION_REG_BLOCK_ENABLE) :
		       (val & ~(u32)IGU_BLOCK_CONFIGURATION_REG_BLOCK_ENABLE));
	पूर्ण

	DP(NETIF_MSG_HW | NETIF_MSG_IFUP, "%s gates #2, #3 and #4\n",
		बंद ? "closing" : "opening");
पूर्ण

#घोषणा SHARED_MF_CLP_MAGIC  0x80000000 /* `magic' bit */

अटल व्योम bnx2x_clp_reset_prep(काष्ठा bnx2x *bp, u32 *magic_val)
अणु
	/* Do some magic... */
	u32 val = MF_CFG_RD(bp, shared_mf_config.clp_mb);
	*magic_val = val & SHARED_MF_CLP_MAGIC;
	MF_CFG_WR(bp, shared_mf_config.clp_mb, val | SHARED_MF_CLP_MAGIC);
पूर्ण

/**
 * bnx2x_clp_reset_करोne - restore the value of the `magic' bit.
 *
 * @bp:		driver handle
 * @magic_val:	old value of the `magic' bit.
 */
अटल व्योम bnx2x_clp_reset_करोne(काष्ठा bnx2x *bp, u32 magic_val)
अणु
	/* Restore the `magic' bit value... */
	u32 val = MF_CFG_RD(bp, shared_mf_config.clp_mb);
	MF_CFG_WR(bp, shared_mf_config.clp_mb,
		(val & (~SHARED_MF_CLP_MAGIC)) | magic_val);
पूर्ण

/**
 * bnx2x_reset_mcp_prep - prepare क्रम MCP reset.
 *
 * @bp:		driver handle
 * @magic_val:	old value of 'magic' bit.
 *
 * Takes care of CLP configurations.
 */
अटल व्योम bnx2x_reset_mcp_prep(काष्ठा bnx2x *bp, u32 *magic_val)
अणु
	u32 shmem;
	u32 validity_offset;

	DP(NETIF_MSG_HW | NETIF_MSG_IFUP, "Starting\n");

	/* Set `magic' bit in order to save MF config */
	अगर (!CHIP_IS_E1(bp))
		bnx2x_clp_reset_prep(bp, magic_val);

	/* Get shmem offset */
	shmem = REG_RD(bp, MISC_REG_SHARED_MEM_ADDR);
	validity_offset =
		दुरत्व(काष्ठा shmem_region, validity_map[BP_PORT(bp)]);

	/* Clear validity map flags */
	अगर (shmem > 0)
		REG_WR(bp, shmem + validity_offset, 0);
पूर्ण

#घोषणा MCP_TIMEOUT      5000   /* 5 seconds (in ms) */
#घोषणा MCP_ONE_TIMEOUT  100    /* 100 ms */

/**
 * bnx2x_mcp_रुको_one - रुको क्रम MCP_ONE_TIMEOUT
 *
 * @bp:	driver handle
 */
अटल व्योम bnx2x_mcp_रुको_one(काष्ठा bnx2x *bp)
अणु
	/* special handling क्रम emulation and FPGA,
	   रुको 10 बार दीर्घer */
	अगर (CHIP_REV_IS_SLOW(bp))
		msleep(MCP_ONE_TIMEOUT*10);
	अन्यथा
		msleep(MCP_ONE_TIMEOUT);
पूर्ण

/*
 * initializes bp->common.shmem_base and रुकोs क्रम validity signature to appear
 */
अटल पूर्णांक bnx2x_init_shmem(काष्ठा bnx2x *bp)
अणु
	पूर्णांक cnt = 0;
	u32 val = 0;

	करो अणु
		bp->common.shmem_base = REG_RD(bp, MISC_REG_SHARED_MEM_ADDR);

		/* If we पढ़ो all 0xFFs, means we are in PCI error state and
		 * should bail out to aव्योम crashes on adapter's FW पढ़ोs.
		 */
		अगर (bp->common.shmem_base == 0xFFFFFFFF) अणु
			bp->flags |= NO_MCP_FLAG;
			वापस -ENODEV;
		पूर्ण

		अगर (bp->common.shmem_base) अणु
			val = SHMEM_RD(bp, validity_map[BP_PORT(bp)]);
			अगर (val & SHR_MEM_VALIDITY_MB)
				वापस 0;
		पूर्ण

		bnx2x_mcp_रुको_one(bp);

	पूर्ण जबतक (cnt++ < (MCP_TIMEOUT / MCP_ONE_TIMEOUT));

	BNX2X_ERR("BAD MCP validity signature\n");

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक bnx2x_reset_mcp_comp(काष्ठा bnx2x *bp, u32 magic_val)
अणु
	पूर्णांक rc = bnx2x_init_shmem(bp);

	/* Restore the `magic' bit value */
	अगर (!CHIP_IS_E1(bp))
		bnx2x_clp_reset_करोne(bp, magic_val);

	वापस rc;
पूर्ण

अटल व्योम bnx2x_pxp_prep(काष्ठा bnx2x *bp)
अणु
	अगर (!CHIP_IS_E1(bp)) अणु
		REG_WR(bp, PXP2_REG_RD_START_INIT, 0);
		REG_WR(bp, PXP2_REG_RQ_RBC_DONE, 0);
	पूर्ण
पूर्ण

/*
 * Reset the whole chip except क्रम:
 *      - PCIE core
 *      - PCI Glue, PSWHST, PXP/PXP2 RF (all controlled by
 *              one reset bit)
 *      - IGU
 *      - MISC (including AEU)
 *      - GRC
 *      - RBCN, RBCP
 */
अटल व्योम bnx2x_process_समाप्त_chip_reset(काष्ठा bnx2x *bp, bool global)
अणु
	u32 not_reset_mask1, reset_mask1, not_reset_mask2, reset_mask2;
	u32 global_bits2, stay_reset2;

	/*
	 * Bits that have to be set in reset_mask2 अगर we want to reset 'global'
	 * (per chip) blocks.
	 */
	global_bits2 =
		MISC_REGISTERS_RESET_REG_2_RST_MCP_N_RESET_CMN_CPU |
		MISC_REGISTERS_RESET_REG_2_RST_MCP_N_RESET_CMN_CORE;

	/* Don't reset the following blocks.
	 * Important: per port blocks (such as EMAC, BMAC, UMAC) can't be
	 *            reset, as in 4 port device they might still be owned
	 *            by the MCP (there is only one leader per path).
	 */
	not_reset_mask1 =
		MISC_REGISTERS_RESET_REG_1_RST_HC |
		MISC_REGISTERS_RESET_REG_1_RST_PXPV |
		MISC_REGISTERS_RESET_REG_1_RST_PXP;

	not_reset_mask2 =
		MISC_REGISTERS_RESET_REG_2_RST_PCI_MDIO |
		MISC_REGISTERS_RESET_REG_2_RST_EMAC0_HARD_CORE |
		MISC_REGISTERS_RESET_REG_2_RST_EMAC1_HARD_CORE |
		MISC_REGISTERS_RESET_REG_2_RST_MISC_CORE |
		MISC_REGISTERS_RESET_REG_2_RST_RBCN |
		MISC_REGISTERS_RESET_REG_2_RST_GRC  |
		MISC_REGISTERS_RESET_REG_2_RST_MCP_N_RESET_REG_HARD_CORE |
		MISC_REGISTERS_RESET_REG_2_RST_MCP_N_HARD_CORE_RST_B |
		MISC_REGISTERS_RESET_REG_2_RST_ATC |
		MISC_REGISTERS_RESET_REG_2_PGLC |
		MISC_REGISTERS_RESET_REG_2_RST_BMAC0 |
		MISC_REGISTERS_RESET_REG_2_RST_BMAC1 |
		MISC_REGISTERS_RESET_REG_2_RST_EMAC0 |
		MISC_REGISTERS_RESET_REG_2_RST_EMAC1 |
		MISC_REGISTERS_RESET_REG_2_UMAC0 |
		MISC_REGISTERS_RESET_REG_2_UMAC1;

	/*
	 * Keep the following blocks in reset:
	 *  - all xxMACs are handled by the bnx2x_link code.
	 */
	stay_reset2 =
		MISC_REGISTERS_RESET_REG_2_XMAC |
		MISC_REGISTERS_RESET_REG_2_XMAC_SOFT;

	/* Full reset masks according to the chip */
	reset_mask1 = 0xffffffff;

	अगर (CHIP_IS_E1(bp))
		reset_mask2 = 0xffff;
	अन्यथा अगर (CHIP_IS_E1H(bp))
		reset_mask2 = 0x1ffff;
	अन्यथा अगर (CHIP_IS_E2(bp))
		reset_mask2 = 0xfffff;
	अन्यथा /* CHIP_IS_E3 */
		reset_mask2 = 0x3ffffff;

	/* Don't reset global blocks unless we need to */
	अगर (!global)
		reset_mask2 &= ~global_bits2;

	/*
	 * In हाल of attention in the QM, we need to reset PXP
	 * (MISC_REGISTERS_RESET_REG_2_RST_PXP_RQ_RD_WR) beक्रमe QM
	 * because otherwise QM reset would release 'close the gates' लघुly
	 * beक्रमe resetting the PXP, then the PSWRQ would send a ग_लिखो
	 * request to PGLUE. Then when PXP is reset, PGLUE would try to
	 * पढ़ो the payload data from PSWWR, but PSWWR would not
	 * respond. The ग_लिखो queue in PGLUE would stuck, dmae commands
	 * would not वापस. Thereक्रमe it's important to reset the second
	 * reset रेजिस्टर (containing the
	 * MISC_REGISTERS_RESET_REG_2_RST_PXP_RQ_RD_WR bit) beक्रमe the
	 * first one (containing the MISC_REGISTERS_RESET_REG_1_RST_QM
	 * bit).
	 */
	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_2_CLEAR,
	       reset_mask2 & (~not_reset_mask2));

	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_1_CLEAR,
	       reset_mask1 & (~not_reset_mask1));

	barrier();

	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_2_SET,
	       reset_mask2 & (~stay_reset2));

	barrier();

	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_1_SET, reset_mask1);
पूर्ण

/**
 * bnx2x_er_poll_igu_vq - poll क्रम pending ग_लिखोs bit.
 * It should get cleared in no more than 1s.
 *
 * @bp:	driver handle
 *
 * It should get cleared in no more than 1s. Returns 0 अगर
 * pending ग_लिखोs bit माला_लो cleared.
 */
अटल पूर्णांक bnx2x_er_poll_igu_vq(काष्ठा bnx2x *bp)
अणु
	u32 cnt = 1000;
	u32 pend_bits = 0;

	करो अणु
		pend_bits  = REG_RD(bp, IGU_REG_PENDING_BITS_STATUS);

		अगर (pend_bits == 0)
			अवरोध;

		usleep_range(1000, 2000);
	पूर्ण जबतक (cnt-- > 0);

	अगर (cnt <= 0) अणु
		BNX2X_ERR("Still pending IGU requests pend_bits=%x!\n",
			  pend_bits);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_process_समाप्त(काष्ठा bnx2x *bp, bool global)
अणु
	पूर्णांक cnt = 1000;
	u32 val = 0;
	u32 sr_cnt, blk_cnt, port_is_idle_0, port_is_idle_1, pgl_exp_rom2;
	u32 tags_63_32 = 0;

	/* Empty the Tetris buffer, रुको क्रम 1s */
	करो अणु
		sr_cnt  = REG_RD(bp, PXP2_REG_RD_SR_CNT);
		blk_cnt = REG_RD(bp, PXP2_REG_RD_BLK_CNT);
		port_is_idle_0 = REG_RD(bp, PXP2_REG_RD_PORT_IS_IDLE_0);
		port_is_idle_1 = REG_RD(bp, PXP2_REG_RD_PORT_IS_IDLE_1);
		pgl_exp_rom2 = REG_RD(bp, PXP2_REG_PGL_EXP_ROM2);
		अगर (CHIP_IS_E3(bp))
			tags_63_32 = REG_RD(bp, PGLUE_B_REG_TAGS_63_32);

		अगर ((sr_cnt == 0x7e) && (blk_cnt == 0xa0) &&
		    ((port_is_idle_0 & 0x1) == 0x1) &&
		    ((port_is_idle_1 & 0x1) == 0x1) &&
		    (pgl_exp_rom2 == 0xffffffff) &&
		    (!CHIP_IS_E3(bp) || (tags_63_32 == 0xffffffff)))
			अवरोध;
		usleep_range(1000, 2000);
	पूर्ण जबतक (cnt-- > 0);

	अगर (cnt <= 0) अणु
		BNX2X_ERR("Tetris buffer didn't get empty or there are still outstanding read requests after 1s!\n");
		BNX2X_ERR("sr_cnt=0x%08x, blk_cnt=0x%08x, port_is_idle_0=0x%08x, port_is_idle_1=0x%08x, pgl_exp_rom2=0x%08x\n",
			  sr_cnt, blk_cnt, port_is_idle_0, port_is_idle_1,
			  pgl_exp_rom2);
		वापस -EAGAIN;
	पूर्ण

	barrier();

	/* Close gates #2, #3 and #4 */
	bnx2x_set_234_gates(bp, true);

	/* Poll क्रम IGU VQs क्रम 57712 and newer chips */
	अगर (!CHIP_IS_E1x(bp) && bnx2x_er_poll_igu_vq(bp))
		वापस -EAGAIN;

	/* TBD: Indicate that "process kill" is in progress to MCP */

	/* Clear "unprepared" bit */
	REG_WR(bp, MISC_REG_UNPREPARED, 0);
	barrier();

	/* Wait क्रम 1ms to empty GLUE and PCI-E core queues,
	 * PSWHST, GRC and PSWRD Tetris buffer.
	 */
	usleep_range(1000, 2000);

	/* Prepare to chip reset: */
	/* MCP */
	अगर (global)
		bnx2x_reset_mcp_prep(bp, &val);

	/* PXP */
	bnx2x_pxp_prep(bp);
	barrier();

	/* reset the chip */
	bnx2x_process_समाप्त_chip_reset(bp, global);
	barrier();

	/* clear errors in PGB */
	अगर (!CHIP_IS_E1x(bp))
		REG_WR(bp, PGLUE_B_REG_LATCHED_ERRORS_CLR, 0x7f);

	/* Recover after reset: */
	/* MCP */
	अगर (global && bnx2x_reset_mcp_comp(bp, val))
		वापस -EAGAIN;

	/* TBD: Add resetting the NO_MCP mode DB here */

	/* Open the gates #2, #3 and #4 */
	bnx2x_set_234_gates(bp, false);

	/* TBD: IGU/AEU preparation bring back the AEU/IGU to a
	 * reset state, re-enable attentions. */

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_leader_reset(काष्ठा bnx2x *bp)
अणु
	पूर्णांक rc = 0;
	bool global = bnx2x_reset_is_global(bp);
	u32 load_code;

	/* अगर not going to reset MCP - load "fake" driver to reset HW जबतक
	 * driver is owner of the HW
	 */
	अगर (!global && !BP_NOMCP(bp)) अणु
		load_code = bnx2x_fw_command(bp, DRV_MSG_CODE_LOAD_REQ,
					     DRV_MSG_CODE_LOAD_REQ_WITH_LFA);
		अगर (!load_code) अणु
			BNX2X_ERR("MCP response failure, aborting\n");
			rc = -EAGAIN;
			जाओ निकास_leader_reset;
		पूर्ण
		अगर ((load_code != FW_MSG_CODE_DRV_LOAD_COMMON_CHIP) &&
		    (load_code != FW_MSG_CODE_DRV_LOAD_COMMON)) अणु
			BNX2X_ERR("MCP unexpected resp, aborting\n");
			rc = -EAGAIN;
			जाओ निकास_leader_reset2;
		पूर्ण
		load_code = bnx2x_fw_command(bp, DRV_MSG_CODE_LOAD_DONE, 0);
		अगर (!load_code) अणु
			BNX2X_ERR("MCP response failure, aborting\n");
			rc = -EAGAIN;
			जाओ निकास_leader_reset2;
		पूर्ण
	पूर्ण

	/* Try to recover after the failure */
	अगर (bnx2x_process_समाप्त(bp, global)) अणु
		BNX2X_ERR("Something bad had happen on engine %d! Aii!\n",
			  BP_PATH(bp));
		rc = -EAGAIN;
		जाओ निकास_leader_reset2;
	पूर्ण

	/*
	 * Clear RESET_IN_PROGRES and RESET_GLOBAL bits and update the driver
	 * state.
	 */
	bnx2x_set_reset_करोne(bp);
	अगर (global)
		bnx2x_clear_reset_global(bp);

निकास_leader_reset2:
	/* unload "fake driver" अगर it was loaded */
	अगर (!global && !BP_NOMCP(bp)) अणु
		bnx2x_fw_command(bp, DRV_MSG_CODE_UNLOAD_REQ_WOL_MCP, 0);
		bnx2x_fw_command(bp, DRV_MSG_CODE_UNLOAD_DONE, 0);
	पूर्ण
निकास_leader_reset:
	bp->is_leader = 0;
	bnx2x_release_leader_lock(bp);
	smp_mb();
	वापस rc;
पूर्ण

अटल व्योम bnx2x_recovery_failed(काष्ठा bnx2x *bp)
अणु
	netdev_err(bp->dev, "Recovery has failed. Power cycle is needed.\n");

	/* Disconnect this device */
	netअगर_device_detach(bp->dev);

	/*
	 * Block अगरup क्रम all function on this engine until "process kill"
	 * or घातer cycle.
	 */
	bnx2x_set_reset_in_progress(bp);

	/* Shut करोwn the घातer */
	bnx2x_set_घातer_state(bp, PCI_D3hot);

	bp->recovery_state = BNX2X_RECOVERY_FAILED;

	smp_mb();
पूर्ण

/*
 * Assumption: runs under rtnl lock. This together with the fact
 * that it's called only from bnx2x_sp_rtnl() ensure that it
 * will never be called when netअगर_running(bp->dev) is false.
 */
अटल व्योम bnx2x_parity_recover(काष्ठा bnx2x *bp)
अणु
	u32 error_recovered, error_unrecovered;
	bool is_parity, global = false;
#अगर_घोषित CONFIG_BNX2X_SRIOV
	पूर्णांक vf_idx;

	क्रम (vf_idx = 0; vf_idx < bp->requested_nr_virtfn; vf_idx++) अणु
		काष्ठा bnx2x_virtf *vf = BP_VF(bp, vf_idx);

		अगर (vf)
			vf->state = VF_LOST;
	पूर्ण
#पूर्ण_अगर
	DP(NETIF_MSG_HW, "Handling parity\n");
	जबतक (1) अणु
		चयन (bp->recovery_state) अणु
		हाल BNX2X_RECOVERY_INIT:
			DP(NETIF_MSG_HW, "State is BNX2X_RECOVERY_INIT\n");
			is_parity = bnx2x_chk_parity_attn(bp, &global, false);
			WARN_ON(!is_parity);

			/* Try to get a LEADER_LOCK HW lock */
			अगर (bnx2x_trylock_leader_lock(bp)) अणु
				bnx2x_set_reset_in_progress(bp);
				/*
				 * Check अगर there is a global attention and अगर
				 * there was a global attention, set the global
				 * reset bit.
				 */

				अगर (global)
					bnx2x_set_reset_global(bp);

				bp->is_leader = 1;
			पूर्ण

			/* Stop the driver */
			/* If पूर्णांकerface has been हटाओd - अवरोध */
			अगर (bnx2x_nic_unload(bp, UNLOAD_RECOVERY, false))
				वापस;

			bp->recovery_state = BNX2X_RECOVERY_WAIT;

			/* Ensure "is_leader", MCP command sequence and
			 * "recovery_state" update values are seen on other
			 * CPUs.
			 */
			smp_mb();
			अवरोध;

		हाल BNX2X_RECOVERY_WAIT:
			DP(NETIF_MSG_HW, "State is BNX2X_RECOVERY_WAIT\n");
			अगर (bp->is_leader) अणु
				पूर्णांक other_engine = BP_PATH(bp) ? 0 : 1;
				bool other_load_status =
					bnx2x_get_load_status(bp, other_engine);
				bool load_status =
					bnx2x_get_load_status(bp, BP_PATH(bp));
				global = bnx2x_reset_is_global(bp);

				/*
				 * In हाल of a parity in a global block, let
				 * the first leader that perक्रमms a
				 * leader_reset() reset the global blocks in
				 * order to clear global attentions. Otherwise
				 * the gates will reमुख्य बंदd क्रम that
				 * engine.
				 */
				अगर (load_status ||
				    (global && other_load_status)) अणु
					/* Wait until all other functions get
					 * करोwn.
					 */
					schedule_delayed_work(&bp->sp_rtnl_task,
								HZ/10);
					वापस;
				पूर्ण अन्यथा अणु
					/* If all other functions got करोwn -
					 * try to bring the chip back to
					 * normal. In any हाल it's an निकास
					 * poपूर्णांक क्रम a leader.
					 */
					अगर (bnx2x_leader_reset(bp)) अणु
						bnx2x_recovery_failed(bp);
						वापस;
					पूर्ण

					/* If we are here, means that the
					 * leader has succeeded and करोesn't
					 * want to be a leader any more. Try
					 * to जारी as a none-leader.
					 */
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु /* non-leader */
				अगर (!bnx2x_reset_is_करोne(bp, BP_PATH(bp))) अणु
					/* Try to get a LEADER_LOCK HW lock as
					 * दीर्घ as a क्रमmer leader may have
					 * been unloaded by the user or
					 * released a leadership by another
					 * reason.
					 */
					अगर (bnx2x_trylock_leader_lock(bp)) अणु
						/* I'm a leader now! Restart a
						 * चयन हाल.
						 */
						bp->is_leader = 1;
						अवरोध;
					पूर्ण

					schedule_delayed_work(&bp->sp_rtnl_task,
								HZ/10);
					वापस;

				पूर्ण अन्यथा अणु
					/*
					 * If there was a global attention, रुको
					 * क्रम it to be cleared.
					 */
					अगर (bnx2x_reset_is_global(bp)) अणु
						schedule_delayed_work(
							&bp->sp_rtnl_task,
							HZ/10);
						वापस;
					पूर्ण

					error_recovered =
					  bp->eth_stats.recoverable_error;
					error_unrecovered =
					  bp->eth_stats.unrecoverable_error;
					bp->recovery_state =
						BNX2X_RECOVERY_NIC_LOADING;
					अगर (bnx2x_nic_load(bp, LOAD_NORMAL)) अणु
						error_unrecovered++;
						netdev_err(bp->dev,
							   "Recovery failed. Power cycle needed\n");
						/* Disconnect this device */
						netअगर_device_detach(bp->dev);
						/* Shut करोwn the घातer */
						bnx2x_set_घातer_state(
							bp, PCI_D3hot);
						smp_mb();
					पूर्ण अन्यथा अणु
						bp->recovery_state =
							BNX2X_RECOVERY_DONE;
						error_recovered++;
						smp_mb();
					पूर्ण
					bp->eth_stats.recoverable_error =
						error_recovered;
					bp->eth_stats.unrecoverable_error =
						error_unrecovered;

					वापस;
				पूर्ण
			पूर्ण
		शेष:
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_udp_port_update(काष्ठा bnx2x *bp)
अणु
	काष्ठा bnx2x_func_चयन_update_params *चयन_update_params;
	काष्ठा bnx2x_func_state_params func_params = अणुशून्यपूर्ण;
	u16 vxlan_port = 0, geneve_port = 0;
	पूर्णांक rc;

	चयन_update_params = &func_params.params.चयन_update;

	/* Prepare parameters क्रम function state transitions */
	__set_bit(RAMROD_COMP_WAIT, &func_params.ramrod_flags);
	__set_bit(RAMROD_RETRY, &func_params.ramrod_flags);

	func_params.f_obj = &bp->func_obj;
	func_params.cmd = BNX2X_F_CMD_SWITCH_UPDATE;

	/* Function parameters */
	__set_bit(BNX2X_F_UPDATE_TUNNEL_CFG_CHNG,
		  &चयन_update_params->changes);

	अगर (bp->udp_tunnel_ports[BNX2X_UDP_PORT_GENEVE]) अणु
		geneve_port = bp->udp_tunnel_ports[BNX2X_UDP_PORT_GENEVE];
		चयन_update_params->geneve_dst_port = geneve_port;
	पूर्ण

	अगर (bp->udp_tunnel_ports[BNX2X_UDP_PORT_VXLAN]) अणु
		vxlan_port = bp->udp_tunnel_ports[BNX2X_UDP_PORT_VXLAN];
		चयन_update_params->vxlan_dst_port = vxlan_port;
	पूर्ण

	/* Re-enable inner-rss क्रम the offloaded UDP tunnels */
	__set_bit(BNX2X_F_UPDATE_TUNNEL_INNER_RSS,
		  &चयन_update_params->changes);

	rc = bnx2x_func_state_change(bp, &func_params);
	अगर (rc)
		BNX2X_ERR("failed to set UDP dst port to %04x %04x (rc = 0x%x)\n",
			  vxlan_port, geneve_port, rc);
	अन्यथा
		DP(BNX2X_MSG_SP,
		   "Configured UDP ports: Vxlan [%04x] Geneve [%04x]\n",
		   vxlan_port, geneve_port);

	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_udp_tunnel_sync(काष्ठा net_device *netdev, अचिन्हित पूर्णांक table)
अणु
	काष्ठा bnx2x *bp = netdev_priv(netdev);
	काष्ठा udp_tunnel_info ti;

	udp_tunnel_nic_get_port(netdev, table, 0, &ti);
	bp->udp_tunnel_ports[table] = be16_to_cpu(ti.port);

	वापस bnx2x_udp_port_update(bp);
पूर्ण

अटल स्थिर काष्ठा udp_tunnel_nic_info bnx2x_udp_tunnels = अणु
	.sync_table	= bnx2x_udp_tunnel_sync,
	.flags		= UDP_TUNNEL_NIC_INFO_MAY_SLEEP |
			  UDP_TUNNEL_NIC_INFO_OPEN_ONLY,
	.tables		= अणु
		अणु .n_entries = 1, .tunnel_types = UDP_TUNNEL_TYPE_VXLAN,  पूर्ण,
		अणु .n_entries = 1, .tunnel_types = UDP_TUNNEL_TYPE_GENEVE, पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक bnx2x_बंद(काष्ठा net_device *dev);

/* bnx2x_nic_unload() flushes the bnx2x_wq, thus reset task is
 * scheduled on a general queue in order to prevent a dead lock.
 */
अटल व्योम bnx2x_sp_rtnl_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bnx2x *bp = container_of(work, काष्ठा bnx2x, sp_rtnl_task.work);

	rtnl_lock();

	अगर (!netअगर_running(bp->dev)) अणु
		rtnl_unlock();
		वापस;
	पूर्ण

	अगर (unlikely(bp->recovery_state != BNX2X_RECOVERY_DONE)) अणु
#अगर_घोषित BNX2X_STOP_ON_ERROR
		BNX2X_ERR("recovery flow called but STOP_ON_ERROR defined so reset not done to allow debug dump,\n"
			  "you will need to reboot when done\n");
		जाओ sp_rtnl_not_reset;
#पूर्ण_अगर
		/*
		 * Clear all pending SP commands as we are going to reset the
		 * function anyway.
		 */
		bp->sp_rtnl_state = 0;
		smp_mb();

		bnx2x_parity_recover(bp);

		rtnl_unlock();
		वापस;
	पूर्ण

	अगर (test_and_clear_bit(BNX2X_SP_RTNL_TX_TIMEOUT, &bp->sp_rtnl_state)) अणु
#अगर_घोषित BNX2X_STOP_ON_ERROR
		BNX2X_ERR("recovery flow called but STOP_ON_ERROR defined so reset not done to allow debug dump,\n"
			  "you will need to reboot when done\n");
		जाओ sp_rtnl_not_reset;
#पूर्ण_अगर

		/*
		 * Clear all pending SP commands as we are going to reset the
		 * function anyway.
		 */
		bp->sp_rtnl_state = 0;
		smp_mb();

		/* Immediately indicate link as करोwn */
		bp->link_vars.link_up = 0;
		bp->क्रमce_link_करोwn = true;
		netअगर_carrier_off(bp->dev);
		BNX2X_ERR("Indicating link is down due to Tx-timeout\n");

		bnx2x_nic_unload(bp, UNLOAD_NORMAL, true);
		/* When ret value shows failure of allocation failure,
		 * the nic is rebooted again. If खोलो still fails, a error
		 * message to notअगरy the user.
		 */
		अगर (bnx2x_nic_load(bp, LOAD_NORMAL) == -ENOMEM) अणु
			bnx2x_nic_unload(bp, UNLOAD_NORMAL, true);
			अगर (bnx2x_nic_load(bp, LOAD_NORMAL))
				BNX2X_ERR("Open the NIC fails again!\n");
		पूर्ण
		rtnl_unlock();
		वापस;
	पूर्ण
#अगर_घोषित BNX2X_STOP_ON_ERROR
sp_rtnl_not_reset:
#पूर्ण_अगर
	अगर (test_and_clear_bit(BNX2X_SP_RTNL_SETUP_TC, &bp->sp_rtnl_state))
		bnx2x_setup_tc(bp->dev, bp->dcbx_port_params.ets.num_of_cos);
	अगर (test_and_clear_bit(BNX2X_SP_RTNL_AFEX_F_UPDATE, &bp->sp_rtnl_state))
		bnx2x_after_function_update(bp);
	/*
	 * in हाल of fan failure we need to reset id अगर the "stop on error"
	 * debug flag is set, since we trying to prevent permanent overheating
	 * damage
	 */
	अगर (test_and_clear_bit(BNX2X_SP_RTNL_FAN_FAILURE, &bp->sp_rtnl_state)) अणु
		DP(NETIF_MSG_HW, "fan failure detected. Unloading driver\n");
		netअगर_device_detach(bp->dev);
		bnx2x_बंद(bp->dev);
		rtnl_unlock();
		वापस;
	पूर्ण

	अगर (test_and_clear_bit(BNX2X_SP_RTNL_VFPF_MCAST, &bp->sp_rtnl_state)) अणु
		DP(BNX2X_MSG_SP,
		   "sending set mcast vf pf channel message from rtnl sp-task\n");
		bnx2x_vfpf_set_mcast(bp->dev);
	पूर्ण
	अगर (test_and_clear_bit(BNX2X_SP_RTNL_VFPF_CHANNEL_DOWN,
			       &bp->sp_rtnl_state))अणु
		अगर (netअगर_carrier_ok(bp->dev)) अणु
			bnx2x_tx_disable(bp);
			BNX2X_ERR("PF indicated channel is not servicable anymore. This means this VF device is no longer operational\n");
		पूर्ण
	पूर्ण

	अगर (test_and_clear_bit(BNX2X_SP_RTNL_RX_MODE, &bp->sp_rtnl_state)) अणु
		DP(BNX2X_MSG_SP, "Handling Rx Mode setting\n");
		bnx2x_set_rx_mode_inner(bp);
	पूर्ण

	अगर (test_and_clear_bit(BNX2X_SP_RTNL_HYPERVISOR_VLAN,
			       &bp->sp_rtnl_state))
		bnx2x_pf_set_vfs_vlan(bp);

	अगर (test_and_clear_bit(BNX2X_SP_RTNL_TX_STOP, &bp->sp_rtnl_state)) अणु
		bnx2x_dcbx_stop_hw_tx(bp);
		bnx2x_dcbx_resume_hw_tx(bp);
	पूर्ण

	अगर (test_and_clear_bit(BNX2X_SP_RTNL_GET_DRV_VERSION,
			       &bp->sp_rtnl_state))
		bnx2x_update_mng_version(bp);

	अगर (test_and_clear_bit(BNX2X_SP_RTNL_UPDATE_SVID, &bp->sp_rtnl_state))
		bnx2x_handle_update_svid_cmd(bp);

	/* work which needs rtnl lock not-taken (as it takes the lock itself and
	 * can be called from other contexts as well)
	 */
	rtnl_unlock();

	/* enable SR-IOV अगर applicable */
	अगर (IS_SRIOV(bp) && test_and_clear_bit(BNX2X_SP_RTNL_ENABLE_SRIOV,
					       &bp->sp_rtnl_state)) अणु
		bnx2x_disable_sriov(bp);
		bnx2x_enable_sriov(bp);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_period_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bnx2x *bp = container_of(work, काष्ठा bnx2x, period_task.work);

	अगर (!netअगर_running(bp->dev))
		जाओ period_task_निकास;

	अगर (CHIP_REV_IS_SLOW(bp)) अणु
		BNX2X_ERR("period task called on emulation, ignoring\n");
		जाओ period_task_निकास;
	पूर्ण

	bnx2x_acquire_phy_lock(bp);
	/*
	 * The barrier is needed to ensure the ordering between the writing to
	 * the bp->port.pmf in the bnx2x_nic_load() or bnx2x_pmf_update() and
	 * the पढ़ोing here.
	 */
	smp_mb();
	अगर (bp->port.pmf) अणु
		bnx2x_period_func(&bp->link_params, &bp->link_vars);

		/* Re-queue task in 1 sec */
		queue_delayed_work(bnx2x_wq, &bp->period_task, 1*HZ);
	पूर्ण

	bnx2x_release_phy_lock(bp);
period_task_निकास:
	वापस;
पूर्ण

/*
 * Init service functions
 */

अटल u32 bnx2x_get_pretend_reg(काष्ठा bnx2x *bp)
अणु
	u32 base = PXP2_REG_PGL_PRETEND_FUNC_F0;
	u32 stride = PXP2_REG_PGL_PRETEND_FUNC_F1 - base;
	वापस base + (BP_ABS_FUNC(bp)) * stride;
पूर्ण

अटल bool bnx2x_prev_unload_बंद_umac(काष्ठा bnx2x *bp,
					 u8 port, u32 reset_reg,
					 काष्ठा bnx2x_mac_vals *vals)
अणु
	u32 mask = MISC_REGISTERS_RESET_REG_2_UMAC0 << port;
	u32 base_addr;

	अगर (!(mask & reset_reg))
		वापस false;

	BNX2X_DEV_INFO("Disable umac Rx %02x\n", port);
	base_addr = port ? GRCBASE_UMAC1 : GRCBASE_UMAC0;
	vals->umac_addr[port] = base_addr + UMAC_REG_COMMAND_CONFIG;
	vals->umac_val[port] = REG_RD(bp, vals->umac_addr[port]);
	REG_WR(bp, vals->umac_addr[port], 0);

	वापस true;
पूर्ण

अटल व्योम bnx2x_prev_unload_बंद_mac(काष्ठा bnx2x *bp,
					काष्ठा bnx2x_mac_vals *vals)
अणु
	u32 val, base_addr, offset, mask, reset_reg;
	bool mac_stopped = false;
	u8 port = BP_PORT(bp);

	/* reset addresses as they also mark which values were changed */
	स_रखो(vals, 0, माप(*vals));

	reset_reg = REG_RD(bp, MISC_REG_RESET_REG_2);

	अगर (!CHIP_IS_E3(bp)) अणु
		val = REG_RD(bp, NIG_REG_BMAC0_REGS_OUT_EN + port * 4);
		mask = MISC_REGISTERS_RESET_REG_2_RST_BMAC0 << port;
		अगर ((mask & reset_reg) && val) अणु
			u32 wb_data[2];
			BNX2X_DEV_INFO("Disable bmac Rx\n");
			base_addr = BP_PORT(bp) ? NIG_REG_INGRESS_BMAC1_MEM
						: NIG_REG_INGRESS_BMAC0_MEM;
			offset = CHIP_IS_E2(bp) ? BIGMAC2_REGISTER_BMAC_CONTROL
						: BIGMAC_REGISTER_BMAC_CONTROL;

			/*
			 * use rd/wr since we cannot use dmae. This is safe
			 * since MCP won't access the bus due to the request
			 * to unload, and no function on the path can be
			 * loaded at this समय.
			 */
			wb_data[0] = REG_RD(bp, base_addr + offset);
			wb_data[1] = REG_RD(bp, base_addr + offset + 0x4);
			vals->bmac_addr = base_addr + offset;
			vals->bmac_val[0] = wb_data[0];
			vals->bmac_val[1] = wb_data[1];
			wb_data[0] &= ~BMAC_CONTROL_RX_ENABLE;
			REG_WR(bp, vals->bmac_addr, wb_data[0]);
			REG_WR(bp, vals->bmac_addr + 0x4, wb_data[1]);
		पूर्ण
		BNX2X_DEV_INFO("Disable emac Rx\n");
		vals->emac_addr = NIG_REG_NIG_EMAC0_EN + BP_PORT(bp)*4;
		vals->emac_val = REG_RD(bp, vals->emac_addr);
		REG_WR(bp, vals->emac_addr, 0);
		mac_stopped = true;
	पूर्ण अन्यथा अणु
		अगर (reset_reg & MISC_REGISTERS_RESET_REG_2_XMAC) अणु
			BNX2X_DEV_INFO("Disable xmac Rx\n");
			base_addr = BP_PORT(bp) ? GRCBASE_XMAC1 : GRCBASE_XMAC0;
			val = REG_RD(bp, base_addr + XMAC_REG_PFC_CTRL_HI);
			REG_WR(bp, base_addr + XMAC_REG_PFC_CTRL_HI,
			       val & ~(1 << 1));
			REG_WR(bp, base_addr + XMAC_REG_PFC_CTRL_HI,
			       val | (1 << 1));
			vals->xmac_addr = base_addr + XMAC_REG_CTRL;
			vals->xmac_val = REG_RD(bp, vals->xmac_addr);
			REG_WR(bp, vals->xmac_addr, 0);
			mac_stopped = true;
		पूर्ण

		mac_stopped |= bnx2x_prev_unload_बंद_umac(bp, 0,
							    reset_reg, vals);
		mac_stopped |= bnx2x_prev_unload_बंद_umac(bp, 1,
							    reset_reg, vals);
	पूर्ण

	अगर (mac_stopped)
		msleep(20);
पूर्ण

#घोषणा BNX2X_PREV_UNDI_PROD_ADDR(p) (BAR_TSTRORM_INTMEM + 0x1508 + ((p) << 4))
#घोषणा BNX2X_PREV_UNDI_PROD_ADDR_H(f) (BAR_TSTRORM_INTMEM + \
					0x1848 + ((f) << 4))
#घोषणा BNX2X_PREV_UNDI_RCQ(val)	((val) & 0xffff)
#घोषणा BNX2X_PREV_UNDI_BD(val)		((val) >> 16 & 0xffff)
#घोषणा BNX2X_PREV_UNDI_PROD(rcq, bd)	((bd) << 16 | (rcq))

#घोषणा BCM_5710_UNDI_FW_MF_MAJOR	(0x07)
#घोषणा BCM_5710_UNDI_FW_MF_MINOR	(0x08)
#घोषणा BCM_5710_UNDI_FW_MF_VERS	(0x05)

अटल bool bnx2x_prev_is_after_undi(काष्ठा bnx2x *bp)
अणु
	/* UNDI marks its presence in DORQ -
	 * it initializes CID offset क्रम normal bell to 0x7
	 */
	अगर (!(REG_RD(bp, MISC_REG_RESET_REG_1) &
	    MISC_REGISTERS_RESET_REG_1_RST_DORQ))
		वापस false;

	अगर (REG_RD(bp, DORQ_REG_NORM_CID_OFST) == 0x7) अणु
		BNX2X_DEV_INFO("UNDI previously loaded\n");
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम bnx2x_prev_unload_undi_inc(काष्ठा bnx2x *bp, u8 inc)
अणु
	u16 rcq, bd;
	u32 addr, पंचांगp_reg;

	अगर (BP_FUNC(bp) < 2)
		addr = BNX2X_PREV_UNDI_PROD_ADDR(BP_PORT(bp));
	अन्यथा
		addr = BNX2X_PREV_UNDI_PROD_ADDR_H(BP_FUNC(bp) - 2);

	पंचांगp_reg = REG_RD(bp, addr);
	rcq = BNX2X_PREV_UNDI_RCQ(पंचांगp_reg) + inc;
	bd = BNX2X_PREV_UNDI_BD(पंचांगp_reg) + inc;

	पंचांगp_reg = BNX2X_PREV_UNDI_PROD(rcq, bd);
	REG_WR(bp, addr, पंचांगp_reg);

	BNX2X_DEV_INFO("UNDI producer [%d/%d][%08x] rings bd -> 0x%04x, rcq -> 0x%04x\n",
		       BP_PORT(bp), BP_FUNC(bp), addr, bd, rcq);
पूर्ण

अटल पूर्णांक bnx2x_prev_mcp_करोne(काष्ठा bnx2x *bp)
अणु
	u32 rc = bnx2x_fw_command(bp, DRV_MSG_CODE_UNLOAD_DONE,
				  DRV_MSG_CODE_UNLOAD_SKIP_LINK_RESET);
	अगर (!rc) अणु
		BNX2X_ERR("MCP response failure, aborting\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा bnx2x_prev_path_list *
		bnx2x_prev_path_get_entry(काष्ठा bnx2x *bp)
अणु
	काष्ठा bnx2x_prev_path_list *पंचांगp_list;

	list_क्रम_each_entry(पंचांगp_list, &bnx2x_prev_list, list)
		अगर (PCI_SLOT(bp->pdev->devfn) == पंचांगp_list->slot &&
		    bp->pdev->bus->number == पंचांगp_list->bus &&
		    BP_PATH(bp) == पंचांगp_list->path)
			वापस पंचांगp_list;

	वापस शून्य;
पूर्ण

अटल पूर्णांक bnx2x_prev_path_mark_eeh(काष्ठा bnx2x *bp)
अणु
	काष्ठा bnx2x_prev_path_list *पंचांगp_list;
	पूर्णांक rc;

	rc = करोwn_पूर्णांकerruptible(&bnx2x_prev_sem);
	अगर (rc) अणु
		BNX2X_ERR("Received %d when tried to take lock\n", rc);
		वापस rc;
	पूर्ण

	पंचांगp_list = bnx2x_prev_path_get_entry(bp);
	अगर (पंचांगp_list) अणु
		पंचांगp_list->aer = 1;
		rc = 0;
	पूर्ण अन्यथा अणु
		BNX2X_ERR("path %d: Entry does not exist for eeh; Flow occurs before initial insmod is over ?\n",
			  BP_PATH(bp));
	पूर्ण

	up(&bnx2x_prev_sem);

	वापस rc;
पूर्ण

अटल bool bnx2x_prev_is_path_marked(काष्ठा bnx2x *bp)
अणु
	काष्ठा bnx2x_prev_path_list *पंचांगp_list;
	bool rc = false;

	अगर (करोwn_trylock(&bnx2x_prev_sem))
		वापस false;

	पंचांगp_list = bnx2x_prev_path_get_entry(bp);
	अगर (पंचांगp_list) अणु
		अगर (पंचांगp_list->aer) अणु
			DP(NETIF_MSG_HW, "Path %d was marked by AER\n",
			   BP_PATH(bp));
		पूर्ण अन्यथा अणु
			rc = true;
			BNX2X_DEV_INFO("Path %d was already cleaned from previous drivers\n",
				       BP_PATH(bp));
		पूर्ण
	पूर्ण

	up(&bnx2x_prev_sem);

	वापस rc;
पूर्ण

bool bnx2x_port_after_undi(काष्ठा bnx2x *bp)
अणु
	काष्ठा bnx2x_prev_path_list *entry;
	bool val;

	करोwn(&bnx2x_prev_sem);

	entry = bnx2x_prev_path_get_entry(bp);
	val = !!(entry && (entry->undi & (1 << BP_PORT(bp))));

	up(&bnx2x_prev_sem);

	वापस val;
पूर्ण

अटल पूर्णांक bnx2x_prev_mark_path(काष्ठा bnx2x *bp, bool after_undi)
अणु
	काष्ठा bnx2x_prev_path_list *पंचांगp_list;
	पूर्णांक rc;

	rc = करोwn_पूर्णांकerruptible(&bnx2x_prev_sem);
	अगर (rc) अणु
		BNX2X_ERR("Received %d when tried to take lock\n", rc);
		वापस rc;
	पूर्ण

	/* Check whether the entry क्रम this path alपढ़ोy exists */
	पंचांगp_list = bnx2x_prev_path_get_entry(bp);
	अगर (पंचांगp_list) अणु
		अगर (!पंचांगp_list->aer) अणु
			BNX2X_ERR("Re-Marking the path.\n");
		पूर्ण अन्यथा अणु
			DP(NETIF_MSG_HW, "Removing AER indication from path %d\n",
			   BP_PATH(bp));
			पंचांगp_list->aer = 0;
		पूर्ण
		up(&bnx2x_prev_sem);
		वापस 0;
	पूर्ण
	up(&bnx2x_prev_sem);

	/* Create an entry क्रम this path and add it */
	पंचांगp_list = kदो_स्मृति(माप(काष्ठा bnx2x_prev_path_list), GFP_KERNEL);
	अगर (!पंचांगp_list) अणु
		BNX2X_ERR("Failed to allocate 'bnx2x_prev_path_list'\n");
		वापस -ENOMEM;
	पूर्ण

	पंचांगp_list->bus = bp->pdev->bus->number;
	पंचांगp_list->slot = PCI_SLOT(bp->pdev->devfn);
	पंचांगp_list->path = BP_PATH(bp);
	पंचांगp_list->aer = 0;
	पंचांगp_list->undi = after_undi ? (1 << BP_PORT(bp)) : 0;

	rc = करोwn_पूर्णांकerruptible(&bnx2x_prev_sem);
	अगर (rc) अणु
		BNX2X_ERR("Received %d when tried to take lock\n", rc);
		kमुक्त(पंचांगp_list);
	पूर्ण अन्यथा अणु
		DP(NETIF_MSG_HW, "Marked path [%d] - finished previous unload\n",
		   BP_PATH(bp));
		list_add(&पंचांगp_list->list, &bnx2x_prev_list);
		up(&bnx2x_prev_sem);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_करो_flr(काष्ठा bnx2x *bp)
अणु
	काष्ठा pci_dev *dev = bp->pdev;

	अगर (CHIP_IS_E1x(bp)) अणु
		BNX2X_DEV_INFO("FLR not supported in E1/E1H\n");
		वापस -EINVAL;
	पूर्ण

	/* only bootcode REQ_BC_VER_4_INITIATE_FLR and onwards support flr */
	अगर (bp->common.bc_ver < REQ_BC_VER_4_INITIATE_FLR) अणु
		BNX2X_ERR("FLR not supported by BC_VER: 0x%x\n",
			  bp->common.bc_ver);
		वापस -EINVAL;
	पूर्ण

	अगर (!pci_रुको_क्रम_pending_transaction(dev))
		dev_err(&dev->dev, "transaction is not cleared; proceeding with reset anyway\n");

	BNX2X_DEV_INFO("Initiating FLR\n");
	bnx2x_fw_command(bp, DRV_MSG_CODE_INITIATE_FLR, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_prev_unload_uncommon(काष्ठा bnx2x *bp)
अणु
	पूर्णांक rc;

	BNX2X_DEV_INFO("Uncommon unload Flow\n");

	/* Test अगर previous unload process was alपढ़ोy finished क्रम this path */
	अगर (bnx2x_prev_is_path_marked(bp))
		वापस bnx2x_prev_mcp_करोne(bp);

	BNX2X_DEV_INFO("Path is unmarked\n");

	/* Cannot proceed with FLR अगर UNDI is loaded, since FW करोes not match */
	अगर (bnx2x_prev_is_after_undi(bp))
		जाओ out;

	/* If function has FLR capabilities, and existing FW version matches
	 * the one required, then FLR will be sufficient to clean any residue
	 * left by previous driver
	 */
	rc = bnx2x_compare_fw_ver(bp, FW_MSG_CODE_DRV_LOAD_FUNCTION, false);

	अगर (!rc) अणु
		/* fw version is good */
		BNX2X_DEV_INFO("FW version matches our own. Attempting FLR\n");
		rc = bnx2x_करो_flr(bp);
	पूर्ण

	अगर (!rc) अणु
		/* FLR was perक्रमmed */
		BNX2X_DEV_INFO("FLR successful\n");
		वापस 0;
	पूर्ण

	BNX2X_DEV_INFO("Could not FLR\n");

out:
	/* Close the MCP request, वापस failure*/
	rc = bnx2x_prev_mcp_करोne(bp);
	अगर (!rc)
		rc = BNX2X_PREV_WAIT_NEEDED;

	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_prev_unload_common(काष्ठा bnx2x *bp)
अणु
	u32 reset_reg, पंचांगp_reg = 0, rc;
	bool prev_undi = false;
	काष्ठा bnx2x_mac_vals mac_vals;

	/* It is possible a previous function received 'common' answer,
	 * but hasn't loaded yet, thereक्रमe creating a scenario of
	 * multiple functions receiving 'common' on the same path.
	 */
	BNX2X_DEV_INFO("Common unload Flow\n");

	स_रखो(&mac_vals, 0, माप(mac_vals));

	अगर (bnx2x_prev_is_path_marked(bp))
		वापस bnx2x_prev_mcp_करोne(bp);

	reset_reg = REG_RD(bp, MISC_REG_RESET_REG_1);

	/* Reset should be perक्रमmed after BRB is emptied */
	अगर (reset_reg & MISC_REGISTERS_RESET_REG_1_RST_BRB1) अणु
		u32 समयr_count = 1000;

		/* Close the MAC Rx to prevent BRB from filling up */
		bnx2x_prev_unload_बंद_mac(bp, &mac_vals);

		/* बंद LLH filters क्रम both ports towards the BRB */
		bnx2x_set_rx_filter(&bp->link_params, 0);
		bp->link_params.port ^= 1;
		bnx2x_set_rx_filter(&bp->link_params, 0);
		bp->link_params.port ^= 1;

		/* Check अगर the UNDI driver was previously loaded */
		अगर (bnx2x_prev_is_after_undi(bp)) अणु
			prev_undi = true;
			/* clear the UNDI indication */
			REG_WR(bp, DORQ_REG_NORM_CID_OFST, 0);
			/* clear possible idle check errors */
			REG_RD(bp, NIG_REG_NIG_INT_STS_CLR_0);
		पूर्ण
		अगर (!CHIP_IS_E1x(bp))
			/* block FW from writing to host */
			REG_WR(bp, PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER, 0);

		/* रुको until BRB is empty */
		पंचांगp_reg = REG_RD(bp, BRB1_REG_NUM_OF_FULL_BLOCKS);
		जबतक (समयr_count) अणु
			u32 prev_brb = पंचांगp_reg;

			पंचांगp_reg = REG_RD(bp, BRB1_REG_NUM_OF_FULL_BLOCKS);
			अगर (!पंचांगp_reg)
				अवरोध;

			BNX2X_DEV_INFO("BRB still has 0x%08x\n", पंचांगp_reg);

			/* reset समयr as दीर्घ as BRB actually माला_लो emptied */
			अगर (prev_brb > पंचांगp_reg)
				समयr_count = 1000;
			अन्यथा
				समयr_count--;

			/* If UNDI resides in memory, manually increment it */
			अगर (prev_undi)
				bnx2x_prev_unload_undi_inc(bp, 1);

			udelay(10);
		पूर्ण

		अगर (!समयr_count)
			BNX2X_ERR("Failed to empty BRB, hope for the best\n");
	पूर्ण

	/* No packets are in the pipeline, path is पढ़ोy क्रम reset */
	bnx2x_reset_common(bp);

	अगर (mac_vals.xmac_addr)
		REG_WR(bp, mac_vals.xmac_addr, mac_vals.xmac_val);
	अगर (mac_vals.umac_addr[0])
		REG_WR(bp, mac_vals.umac_addr[0], mac_vals.umac_val[0]);
	अगर (mac_vals.umac_addr[1])
		REG_WR(bp, mac_vals.umac_addr[1], mac_vals.umac_val[1]);
	अगर (mac_vals.emac_addr)
		REG_WR(bp, mac_vals.emac_addr, mac_vals.emac_val);
	अगर (mac_vals.bmac_addr) अणु
		REG_WR(bp, mac_vals.bmac_addr, mac_vals.bmac_val[0]);
		REG_WR(bp, mac_vals.bmac_addr + 4, mac_vals.bmac_val[1]);
	पूर्ण

	rc = bnx2x_prev_mark_path(bp, prev_undi);
	अगर (rc) अणु
		bnx2x_prev_mcp_करोne(bp);
		वापस rc;
	पूर्ण

	वापस bnx2x_prev_mcp_करोne(bp);
पूर्ण

अटल पूर्णांक bnx2x_prev_unload(काष्ठा bnx2x *bp)
अणु
	पूर्णांक समय_counter = 10;
	u32 rc, fw, hw_lock_reg, hw_lock_val;
	BNX2X_DEV_INFO("Entering Previous Unload Flow\n");

	/* clear hw from errors which may have resulted from an पूर्णांकerrupted
	 * dmae transaction.
	 */
	bnx2x_clean_pglue_errors(bp);

	/* Release previously held locks */
	hw_lock_reg = (BP_FUNC(bp) <= 5) ?
		      (MISC_REG_DRIVER_CONTROL_1 + BP_FUNC(bp) * 8) :
		      (MISC_REG_DRIVER_CONTROL_7 + (BP_FUNC(bp) - 6) * 8);

	hw_lock_val = REG_RD(bp, hw_lock_reg);
	अगर (hw_lock_val) अणु
		अगर (hw_lock_val & HW_LOCK_RESOURCE_NVRAM) अणु
			BNX2X_DEV_INFO("Release Previously held NVRAM lock\n");
			REG_WR(bp, MCP_REG_MCPR_NVM_SW_ARB,
			       (MCPR_NVM_SW_ARB_ARB_REQ_CLR1 << BP_PORT(bp)));
		पूर्ण

		BNX2X_DEV_INFO("Release Previously held hw lock\n");
		REG_WR(bp, hw_lock_reg, 0xffffffff);
	पूर्ण अन्यथा
		BNX2X_DEV_INFO("No need to release hw/nvram locks\n");

	अगर (MCPR_ACCESS_LOCK_LOCK & REG_RD(bp, MCP_REG_MCPR_ACCESS_LOCK)) अणु
		BNX2X_DEV_INFO("Release previously held alr\n");
		bnx2x_release_alr(bp);
	पूर्ण

	करो अणु
		पूर्णांक aer = 0;
		/* Lock MCP using an unload request */
		fw = bnx2x_fw_command(bp, DRV_MSG_CODE_UNLOAD_REQ_WOL_DIS, 0);
		अगर (!fw) अणु
			BNX2X_ERR("MCP response failure, aborting\n");
			rc = -EBUSY;
			अवरोध;
		पूर्ण

		rc = करोwn_पूर्णांकerruptible(&bnx2x_prev_sem);
		अगर (rc) अणु
			BNX2X_ERR("Cannot check for AER; Received %d when tried to take lock\n",
				  rc);
		पूर्ण अन्यथा अणु
			/* If Path is marked by EEH, ignore unload status */
			aer = !!(bnx2x_prev_path_get_entry(bp) &&
				 bnx2x_prev_path_get_entry(bp)->aer);
			up(&bnx2x_prev_sem);
		पूर्ण

		अगर (fw == FW_MSG_CODE_DRV_UNLOAD_COMMON || aer) अणु
			rc = bnx2x_prev_unload_common(bp);
			अवरोध;
		पूर्ण

		/* non-common reply from MCP might require looping */
		rc = bnx2x_prev_unload_uncommon(bp);
		अगर (rc != BNX2X_PREV_WAIT_NEEDED)
			अवरोध;

		msleep(20);
	पूर्ण जबतक (--समय_counter);

	अगर (!समय_counter || rc) अणु
		BNX2X_DEV_INFO("Unloading previous driver did not occur, Possibly due to MF UNDI\n");
		rc = -EPROBE_DEFER;
	पूर्ण

	/* Mark function अगर its port was used to boot from SAN */
	अगर (bnx2x_port_after_undi(bp))
		bp->link_params.feature_config_flags |=
			FEATURE_CONFIG_BOOT_FROM_SAN;

	BNX2X_DEV_INFO("Finished Previous Unload Flow [%d]\n", rc);

	वापस rc;
पूर्ण

अटल व्योम bnx2x_get_common_hwinfo(काष्ठा bnx2x *bp)
अणु
	u32 val, val2, val3, val4, id, boot_mode;
	u16 pmc;

	/* Get the chip revision id and number. */
	/* chip num:16-31, rev:12-15, metal:4-11, bond_id:0-3 */
	val = REG_RD(bp, MISC_REG_CHIP_NUM);
	id = ((val & 0xffff) << 16);
	val = REG_RD(bp, MISC_REG_CHIP_REV);
	id |= ((val & 0xf) << 12);

	/* Metal is पढ़ो from PCI regs, but we can't access >=0x400 from
	 * the configuration space (so we need to reg_rd)
	 */
	val = REG_RD(bp, PCICFG_OFFSET + PCI_ID_VAL3);
	id |= (((val >> 24) & 0xf) << 4);
	val = REG_RD(bp, MISC_REG_BOND_ID);
	id |= (val & 0xf);
	bp->common.chip_id = id;

	/* क्रमce 57811 according to MISC रेजिस्टर */
	अगर (REG_RD(bp, MISC_REG_CHIP_TYPE) & MISC_REG_CHIP_TYPE_57811_MASK) अणु
		अगर (CHIP_IS_57810(bp))
			bp->common.chip_id = (CHIP_NUM_57811 << 16) |
				(bp->common.chip_id & 0x0000FFFF);
		अन्यथा अगर (CHIP_IS_57810_MF(bp))
			bp->common.chip_id = (CHIP_NUM_57811_MF << 16) |
				(bp->common.chip_id & 0x0000FFFF);
		bp->common.chip_id |= 0x1;
	पूर्ण

	/* Set करोorbell size */
	bp->db_size = (1 << BNX2X_DB_SHIFT);

	अगर (!CHIP_IS_E1x(bp)) अणु
		val = REG_RD(bp, MISC_REG_PORT4MODE_EN_OVWR);
		अगर ((val & 1) == 0)
			val = REG_RD(bp, MISC_REG_PORT4MODE_EN);
		अन्यथा
			val = (val >> 1) & 1;
		BNX2X_DEV_INFO("chip is in %s\n", val ? "4_PORT_MODE" :
						       "2_PORT_MODE");
		bp->common.chip_port_mode = val ? CHIP_4_PORT_MODE :
						 CHIP_2_PORT_MODE;

		अगर (CHIP_MODE_IS_4_PORT(bp))
			bp->pfid = (bp->pf_num >> 1);	/* 0..3 */
		अन्यथा
			bp->pfid = (bp->pf_num & 0x6);	/* 0, 2, 4, 6 */
	पूर्ण अन्यथा अणु
		bp->common.chip_port_mode = CHIP_PORT_MODE_NONE; /* N/A */
		bp->pfid = bp->pf_num;			/* 0..7 */
	पूर्ण

	BNX2X_DEV_INFO("pf_id: %x", bp->pfid);

	bp->link_params.chip_id = bp->common.chip_id;
	BNX2X_DEV_INFO("chip ID is 0x%x\n", id);

	val = (REG_RD(bp, 0x2874) & 0x55);
	अगर ((bp->common.chip_id & 0x1) ||
	    (CHIP_IS_E1(bp) && val) || (CHIP_IS_E1H(bp) && (val == 0x55))) अणु
		bp->flags |= ONE_PORT_FLAG;
		BNX2X_DEV_INFO("single port device\n");
	पूर्ण

	val = REG_RD(bp, MCP_REG_MCPR_NVM_CFG4);
	bp->common.flash_size = (BNX2X_NVRAM_1MB_SIZE <<
				 (val & MCPR_NVM_CFG4_FLASH_SIZE));
	BNX2X_DEV_INFO("flash_size 0x%x (%d)\n",
		       bp->common.flash_size, bp->common.flash_size);

	bnx2x_init_shmem(bp);

	bp->common.shmem2_base = REG_RD(bp, (BP_PATH(bp) ?
					MISC_REG_GENERIC_CR_1 :
					MISC_REG_GENERIC_CR_0));

	bp->link_params.shmem_base = bp->common.shmem_base;
	bp->link_params.shmem2_base = bp->common.shmem2_base;
	अगर (SHMEM2_RD(bp, size) >
	    (u32)दुरत्व(काष्ठा shmem2_region, lfa_host_addr[BP_PORT(bp)]))
		bp->link_params.lfa_base =
		REG_RD(bp, bp->common.shmem2_base +
		       (u32)दुरत्व(काष्ठा shmem2_region,
				     lfa_host_addr[BP_PORT(bp)]));
	अन्यथा
		bp->link_params.lfa_base = 0;
	BNX2X_DEV_INFO("shmem offset 0x%x  shmem2 offset 0x%x\n",
		       bp->common.shmem_base, bp->common.shmem2_base);

	अगर (!bp->common.shmem_base) अणु
		BNX2X_DEV_INFO("MCP not active\n");
		bp->flags |= NO_MCP_FLAG;
		वापस;
	पूर्ण

	bp->common.hw_config = SHMEM_RD(bp, dev_info.shared_hw_config.config);
	BNX2X_DEV_INFO("hw_config 0x%08x\n", bp->common.hw_config);

	bp->link_params.hw_led_mode = ((bp->common.hw_config &
					SHARED_HW_CFG_LED_MODE_MASK) >>
				       SHARED_HW_CFG_LED_MODE_SHIFT);

	bp->link_params.feature_config_flags = 0;
	val = SHMEM_RD(bp, dev_info.shared_feature_config.config);
	अगर (val & SHARED_FEAT_CFG_OVERRIDE_PREEMPHASIS_CFG_ENABLED)
		bp->link_params.feature_config_flags |=
				FEATURE_CONFIG_OVERRIDE_PREEMPHASIS_ENABLED;
	अन्यथा
		bp->link_params.feature_config_flags &=
				~FEATURE_CONFIG_OVERRIDE_PREEMPHASIS_ENABLED;

	val = SHMEM_RD(bp, dev_info.bc_rev) >> 8;
	bp->common.bc_ver = val;
	BNX2X_DEV_INFO("bc_ver %X\n", val);
	अगर (val < BNX2X_BC_VER) अणु
		/* क्रम now only warn
		 * later we might need to enक्रमce this */
		BNX2X_ERR("This driver needs bc_ver %X but found %X, please upgrade BC\n",
			  BNX2X_BC_VER, val);
	पूर्ण
	bp->link_params.feature_config_flags |=
				(val >= REQ_BC_VER_4_VRFY_FIRST_PHY_OPT_MDL) ?
				FEATURE_CONFIG_BC_SUPPORTS_OPT_MDL_VRFY : 0;

	bp->link_params.feature_config_flags |=
		(val >= REQ_BC_VER_4_VRFY_SPECIFIC_PHY_OPT_MDL) ?
		FEATURE_CONFIG_BC_SUPPORTS_DUAL_PHY_OPT_MDL_VRFY : 0;
	bp->link_params.feature_config_flags |=
		(val >= REQ_BC_VER_4_VRFY_AFEX_SUPPORTED) ?
		FEATURE_CONFIG_BC_SUPPORTS_AFEX : 0;
	bp->link_params.feature_config_flags |=
		(val >= REQ_BC_VER_4_SFP_TX_DISABLE_SUPPORTED) ?
		FEATURE_CONFIG_BC_SUPPORTS_SFP_TX_DISABLED : 0;

	bp->link_params.feature_config_flags |=
		(val >= REQ_BC_VER_4_MT_SUPPORTED) ?
		FEATURE_CONFIG_MT_SUPPORT : 0;

	bp->flags |= (val >= REQ_BC_VER_4_PFC_STATS_SUPPORTED) ?
			BC_SUPPORTS_PFC_STATS : 0;

	bp->flags |= (val >= REQ_BC_VER_4_FCOE_FEATURES) ?
			BC_SUPPORTS_FCOE_FEATURES : 0;

	bp->flags |= (val >= REQ_BC_VER_4_DCBX_ADMIN_MSG_NON_PMF) ?
			BC_SUPPORTS_DCBX_MSG_NON_PMF : 0;

	bp->flags |= (val >= REQ_BC_VER_4_RMMOD_CMD) ?
			BC_SUPPORTS_RMMOD_CMD : 0;

	boot_mode = SHMEM_RD(bp,
			dev_info.port_feature_config[BP_PORT(bp)].mba_config) &
			PORT_FEATURE_MBA_BOOT_AGENT_TYPE_MASK;
	चयन (boot_mode) अणु
	हाल PORT_FEATURE_MBA_BOOT_AGENT_TYPE_PXE:
		bp->common.boot_mode = FEATURE_ETH_BOOTMODE_PXE;
		अवरोध;
	हाल PORT_FEATURE_MBA_BOOT_AGENT_TYPE_ISCSIB:
		bp->common.boot_mode = FEATURE_ETH_BOOTMODE_ISCSI;
		अवरोध;
	हाल PORT_FEATURE_MBA_BOOT_AGENT_TYPE_FCOE_BOOT:
		bp->common.boot_mode = FEATURE_ETH_BOOTMODE_FCOE;
		अवरोध;
	हाल PORT_FEATURE_MBA_BOOT_AGENT_TYPE_NONE:
		bp->common.boot_mode = FEATURE_ETH_BOOTMODE_NONE;
		अवरोध;
	पूर्ण

	pci_पढ़ो_config_word(bp->pdev, bp->pdev->pm_cap + PCI_PM_PMC, &pmc);
	bp->flags |= (pmc & PCI_PM_CAP_PME_D3cold) ? 0 : NO_WOL_FLAG;

	BNX2X_DEV_INFO("%sWoL capable\n",
		       (bp->flags & NO_WOL_FLAG) ? "not " : "");

	val = SHMEM_RD(bp, dev_info.shared_hw_config.part_num);
	val2 = SHMEM_RD(bp, dev_info.shared_hw_config.part_num[4]);
	val3 = SHMEM_RD(bp, dev_info.shared_hw_config.part_num[8]);
	val4 = SHMEM_RD(bp, dev_info.shared_hw_config.part_num[12]);

	dev_info(&bp->pdev->dev, "part number %X-%X-%X-%X\n",
		 val, val2, val3, val4);
पूर्ण

#घोषणा IGU_FID(val)	GET_FIELD((val), IGU_REG_MAPPING_MEMORY_FID)
#घोषणा IGU_VEC(val)	GET_FIELD((val), IGU_REG_MAPPING_MEMORY_VECTOR)

अटल पूर्णांक bnx2x_get_igu_cam_info(काष्ठा bnx2x *bp)
अणु
	पूर्णांक pfid = BP_FUNC(bp);
	पूर्णांक igu_sb_id;
	u32 val;
	u8 fid, igu_sb_cnt = 0;

	bp->igu_base_sb = 0xff;
	अगर (CHIP_INT_MODE_IS_BC(bp)) अणु
		पूर्णांक vn = BP_VN(bp);
		igu_sb_cnt = bp->igu_sb_cnt;
		bp->igu_base_sb = (CHIP_MODE_IS_4_PORT(bp) ? pfid : vn) *
			FP_SB_MAX_E1x;

		bp->igu_dsb_id =  E1HVN_MAX * FP_SB_MAX_E1x +
			(CHIP_MODE_IS_4_PORT(bp) ? pfid : vn);

		वापस 0;
	पूर्ण

	/* IGU in normal mode - पढ़ो CAM */
	क्रम (igu_sb_id = 0; igu_sb_id < IGU_REG_MAPPING_MEMORY_SIZE;
	     igu_sb_id++) अणु
		val = REG_RD(bp, IGU_REG_MAPPING_MEMORY + igu_sb_id * 4);
		अगर (!(val & IGU_REG_MAPPING_MEMORY_VALID))
			जारी;
		fid = IGU_FID(val);
		अगर ((fid & IGU_FID_ENCODE_IS_PF)) अणु
			अगर ((fid & IGU_FID_PF_NUM_MASK) != pfid)
				जारी;
			अगर (IGU_VEC(val) == 0)
				/* शेष status block */
				bp->igu_dsb_id = igu_sb_id;
			अन्यथा अणु
				अगर (bp->igu_base_sb == 0xff)
					bp->igu_base_sb = igu_sb_id;
				igu_sb_cnt++;
			पूर्ण
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_PCI_MSI
	/* Due to new PF resource allocation by MFW T7.4 and above, it's
	 * optional that number of CAM entries will not be equal to the value
	 * advertised in PCI.
	 * Driver should use the minimal value of both as the actual status
	 * block count
	 */
	bp->igu_sb_cnt = min_t(पूर्णांक, bp->igu_sb_cnt, igu_sb_cnt);
#पूर्ण_अगर

	अगर (igu_sb_cnt == 0) अणु
		BNX2X_ERR("CAM configuration error\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bnx2x_link_settings_supported(काष्ठा bnx2x *bp, u32 चयन_cfg)
अणु
	पूर्णांक cfg_size = 0, idx, port = BP_PORT(bp);

	/* Aggregation of supported attributes of all बाह्यal phys */
	bp->port.supported[0] = 0;
	bp->port.supported[1] = 0;
	चयन (bp->link_params.num_phys) अणु
	हाल 1:
		bp->port.supported[0] = bp->link_params.phy[INT_PHY].supported;
		cfg_size = 1;
		अवरोध;
	हाल 2:
		bp->port.supported[0] = bp->link_params.phy[EXT_PHY1].supported;
		cfg_size = 1;
		अवरोध;
	हाल 3:
		अगर (bp->link_params.multi_phy_config &
		    PORT_HW_CFG_PHY_SWAPPED_ENABLED) अणु
			bp->port.supported[1] =
				bp->link_params.phy[EXT_PHY1].supported;
			bp->port.supported[0] =
				bp->link_params.phy[EXT_PHY2].supported;
		पूर्ण अन्यथा अणु
			bp->port.supported[0] =
				bp->link_params.phy[EXT_PHY1].supported;
			bp->port.supported[1] =
				bp->link_params.phy[EXT_PHY2].supported;
		पूर्ण
		cfg_size = 2;
		अवरोध;
	पूर्ण

	अगर (!(bp->port.supported[0] || bp->port.supported[1])) अणु
		BNX2X_ERR("NVRAM config error. BAD phy config. PHY1 config 0x%x, PHY2 config 0x%x\n",
			   SHMEM_RD(bp,
			   dev_info.port_hw_config[port].बाह्यal_phy_config),
			   SHMEM_RD(bp,
			   dev_info.port_hw_config[port].बाह्यal_phy_config2));
		वापस;
	पूर्ण

	अगर (CHIP_IS_E3(bp))
		bp->port.phy_addr = REG_RD(bp, MISC_REG_WC0_CTRL_PHY_ADDR);
	अन्यथा अणु
		चयन (चयन_cfg) अणु
		हाल SWITCH_CFG_1G:
			bp->port.phy_addr = REG_RD(
				bp, NIG_REG_SERDES0_CTRL_PHY_ADDR + port*0x10);
			अवरोध;
		हाल SWITCH_CFG_10G:
			bp->port.phy_addr = REG_RD(
				bp, NIG_REG_XGXS0_CTRL_PHY_ADDR + port*0x18);
			अवरोध;
		शेष:
			BNX2X_ERR("BAD switch_cfg link_config 0x%x\n",
				  bp->port.link_config[0]);
			वापस;
		पूर्ण
	पूर्ण
	BNX2X_DEV_INFO("phy_addr 0x%x\n", bp->port.phy_addr);
	/* mask what we support according to speed_cap_mask per configuration */
	क्रम (idx = 0; idx < cfg_size; idx++) अणु
		अगर (!(bp->link_params.speed_cap_mask[idx] &
				PORT_HW_CFG_SPEED_CAPABILITY_D0_10M_HALF))
			bp->port.supported[idx] &= ~SUPPORTED_10baseT_Half;

		अगर (!(bp->link_params.speed_cap_mask[idx] &
				PORT_HW_CFG_SPEED_CAPABILITY_D0_10M_FULL))
			bp->port.supported[idx] &= ~SUPPORTED_10baseT_Full;

		अगर (!(bp->link_params.speed_cap_mask[idx] &
				PORT_HW_CFG_SPEED_CAPABILITY_D0_100M_HALF))
			bp->port.supported[idx] &= ~SUPPORTED_100baseT_Half;

		अगर (!(bp->link_params.speed_cap_mask[idx] &
				PORT_HW_CFG_SPEED_CAPABILITY_D0_100M_FULL))
			bp->port.supported[idx] &= ~SUPPORTED_100baseT_Full;

		अगर (!(bp->link_params.speed_cap_mask[idx] &
					PORT_HW_CFG_SPEED_CAPABILITY_D0_1G))
			bp->port.supported[idx] &= ~(SUPPORTED_1000baseT_Half |
						     SUPPORTED_1000baseT_Full);

		अगर (!(bp->link_params.speed_cap_mask[idx] &
					PORT_HW_CFG_SPEED_CAPABILITY_D0_2_5G))
			bp->port.supported[idx] &= ~SUPPORTED_2500baseX_Full;

		अगर (!(bp->link_params.speed_cap_mask[idx] &
					PORT_HW_CFG_SPEED_CAPABILITY_D0_10G))
			bp->port.supported[idx] &= ~SUPPORTED_10000baseT_Full;

		अगर (!(bp->link_params.speed_cap_mask[idx] &
					PORT_HW_CFG_SPEED_CAPABILITY_D0_20G))
			bp->port.supported[idx] &= ~SUPPORTED_20000baseKR2_Full;
	पूर्ण

	BNX2X_DEV_INFO("supported 0x%x 0x%x\n", bp->port.supported[0],
		       bp->port.supported[1]);
पूर्ण

अटल व्योम bnx2x_link_settings_requested(काष्ठा bnx2x *bp)
अणु
	u32 link_config, idx, cfg_size = 0;
	bp->port.advertising[0] = 0;
	bp->port.advertising[1] = 0;
	चयन (bp->link_params.num_phys) अणु
	हाल 1:
	हाल 2:
		cfg_size = 1;
		अवरोध;
	हाल 3:
		cfg_size = 2;
		अवरोध;
	पूर्ण
	क्रम (idx = 0; idx < cfg_size; idx++) अणु
		bp->link_params.req_duplex[idx] = DUPLEX_FULL;
		link_config = bp->port.link_config[idx];
		चयन (link_config & PORT_FEATURE_LINK_SPEED_MASK) अणु
		हाल PORT_FEATURE_LINK_SPEED_AUTO:
			अगर (bp->port.supported[idx] & SUPPORTED_Autoneg) अणु
				bp->link_params.req_line_speed[idx] =
					SPEED_AUTO_NEG;
				bp->port.advertising[idx] |=
					bp->port.supported[idx];
				अगर (bp->link_params.phy[EXT_PHY1].type ==
				    PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84833)
					bp->port.advertising[idx] |=
					(SUPPORTED_100baseT_Half |
					 SUPPORTED_100baseT_Full);
			पूर्ण अन्यथा अणु
				/* क्रमce 10G, no AN */
				bp->link_params.req_line_speed[idx] =
					SPEED_10000;
				bp->port.advertising[idx] |=
					(ADVERTISED_10000baseT_Full |
					 ADVERTISED_FIBRE);
				जारी;
			पूर्ण
			अवरोध;

		हाल PORT_FEATURE_LINK_SPEED_10M_FULL:
			अगर (bp->port.supported[idx] & SUPPORTED_10baseT_Full) अणु
				bp->link_params.req_line_speed[idx] =
					SPEED_10;
				bp->port.advertising[idx] |=
					(ADVERTISED_10baseT_Full |
					 ADVERTISED_TP);
			पूर्ण अन्यथा अणु
				BNX2X_ERR("NVRAM config error. Invalid link_config 0x%x  speed_cap_mask 0x%x\n",
					    link_config,
				    bp->link_params.speed_cap_mask[idx]);
				वापस;
			पूर्ण
			अवरोध;

		हाल PORT_FEATURE_LINK_SPEED_10M_HALF:
			अगर (bp->port.supported[idx] & SUPPORTED_10baseT_Half) अणु
				bp->link_params.req_line_speed[idx] =
					SPEED_10;
				bp->link_params.req_duplex[idx] =
					DUPLEX_HALF;
				bp->port.advertising[idx] |=
					(ADVERTISED_10baseT_Half |
					 ADVERTISED_TP);
			पूर्ण अन्यथा अणु
				BNX2X_ERR("NVRAM config error. Invalid link_config 0x%x  speed_cap_mask 0x%x\n",
					    link_config,
					  bp->link_params.speed_cap_mask[idx]);
				वापस;
			पूर्ण
			अवरोध;

		हाल PORT_FEATURE_LINK_SPEED_100M_FULL:
			अगर (bp->port.supported[idx] &
			    SUPPORTED_100baseT_Full) अणु
				bp->link_params.req_line_speed[idx] =
					SPEED_100;
				bp->port.advertising[idx] |=
					(ADVERTISED_100baseT_Full |
					 ADVERTISED_TP);
			पूर्ण अन्यथा अणु
				BNX2X_ERR("NVRAM config error. Invalid link_config 0x%x  speed_cap_mask 0x%x\n",
					    link_config,
					  bp->link_params.speed_cap_mask[idx]);
				वापस;
			पूर्ण
			अवरोध;

		हाल PORT_FEATURE_LINK_SPEED_100M_HALF:
			अगर (bp->port.supported[idx] &
			    SUPPORTED_100baseT_Half) अणु
				bp->link_params.req_line_speed[idx] =
								SPEED_100;
				bp->link_params.req_duplex[idx] =
								DUPLEX_HALF;
				bp->port.advertising[idx] |=
					(ADVERTISED_100baseT_Half |
					 ADVERTISED_TP);
			पूर्ण अन्यथा अणु
				BNX2X_ERR("NVRAM config error. Invalid link_config 0x%x  speed_cap_mask 0x%x\n",
				    link_config,
				    bp->link_params.speed_cap_mask[idx]);
				वापस;
			पूर्ण
			अवरोध;

		हाल PORT_FEATURE_LINK_SPEED_1G:
			अगर (bp->port.supported[idx] &
			    SUPPORTED_1000baseT_Full) अणु
				bp->link_params.req_line_speed[idx] =
					SPEED_1000;
				bp->port.advertising[idx] |=
					(ADVERTISED_1000baseT_Full |
					 ADVERTISED_TP);
			पूर्ण अन्यथा अगर (bp->port.supported[idx] &
				   SUPPORTED_1000baseKX_Full) अणु
				bp->link_params.req_line_speed[idx] =
					SPEED_1000;
				bp->port.advertising[idx] |=
					ADVERTISED_1000baseKX_Full;
			पूर्ण अन्यथा अणु
				BNX2X_ERR("NVRAM config error. Invalid link_config 0x%x  speed_cap_mask 0x%x\n",
				    link_config,
				    bp->link_params.speed_cap_mask[idx]);
				वापस;
			पूर्ण
			अवरोध;

		हाल PORT_FEATURE_LINK_SPEED_2_5G:
			अगर (bp->port.supported[idx] &
			    SUPPORTED_2500baseX_Full) अणु
				bp->link_params.req_line_speed[idx] =
					SPEED_2500;
				bp->port.advertising[idx] |=
					(ADVERTISED_2500baseX_Full |
						ADVERTISED_TP);
			पूर्ण अन्यथा अणु
				BNX2X_ERR("NVRAM config error. Invalid link_config 0x%x  speed_cap_mask 0x%x\n",
				    link_config,
				    bp->link_params.speed_cap_mask[idx]);
				वापस;
			पूर्ण
			अवरोध;

		हाल PORT_FEATURE_LINK_SPEED_10G_CX4:
			अगर (bp->port.supported[idx] &
			    SUPPORTED_10000baseT_Full) अणु
				bp->link_params.req_line_speed[idx] =
					SPEED_10000;
				bp->port.advertising[idx] |=
					(ADVERTISED_10000baseT_Full |
						ADVERTISED_FIBRE);
			पूर्ण अन्यथा अगर (bp->port.supported[idx] &
				   SUPPORTED_10000baseKR_Full) अणु
				bp->link_params.req_line_speed[idx] =
					SPEED_10000;
				bp->port.advertising[idx] |=
					(ADVERTISED_10000baseKR_Full |
						ADVERTISED_FIBRE);
			पूर्ण अन्यथा अणु
				BNX2X_ERR("NVRAM config error. Invalid link_config 0x%x  speed_cap_mask 0x%x\n",
				    link_config,
				    bp->link_params.speed_cap_mask[idx]);
				वापस;
			पूर्ण
			अवरोध;
		हाल PORT_FEATURE_LINK_SPEED_20G:
			bp->link_params.req_line_speed[idx] = SPEED_20000;

			अवरोध;
		शेष:
			BNX2X_ERR("NVRAM config error. BAD link speed link_config 0x%x\n",
				  link_config);
				bp->link_params.req_line_speed[idx] =
							SPEED_AUTO_NEG;
				bp->port.advertising[idx] =
						bp->port.supported[idx];
			अवरोध;
		पूर्ण

		bp->link_params.req_flow_ctrl[idx] = (link_config &
					 PORT_FEATURE_FLOW_CONTROL_MASK);
		अगर (bp->link_params.req_flow_ctrl[idx] ==
		    BNX2X_FLOW_CTRL_AUTO) अणु
			अगर (!(bp->port.supported[idx] & SUPPORTED_Autoneg))
				bp->link_params.req_flow_ctrl[idx] =
							BNX2X_FLOW_CTRL_NONE;
			अन्यथा
				bnx2x_set_requested_fc(bp);
		पूर्ण

		BNX2X_DEV_INFO("req_line_speed %d  req_duplex %d req_flow_ctrl 0x%x advertising 0x%x\n",
			       bp->link_params.req_line_speed[idx],
			       bp->link_params.req_duplex[idx],
			       bp->link_params.req_flow_ctrl[idx],
			       bp->port.advertising[idx]);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_set_mac_buf(u8 *mac_buf, u32 mac_lo, u16 mac_hi)
अणु
	__be16 mac_hi_be = cpu_to_be16(mac_hi);
	__be32 mac_lo_be = cpu_to_be32(mac_lo);
	स_नकल(mac_buf, &mac_hi_be, माप(mac_hi_be));
	स_नकल(mac_buf + माप(mac_hi_be), &mac_lo_be, माप(mac_lo_be));
पूर्ण

अटल व्योम bnx2x_get_port_hwinfo(काष्ठा bnx2x *bp)
अणु
	पूर्णांक port = BP_PORT(bp);
	u32 config;
	u32 ext_phy_type, ext_phy_config, eee_mode;

	bp->link_params.bp = bp;
	bp->link_params.port = port;

	bp->link_params.lane_config =
		SHMEM_RD(bp, dev_info.port_hw_config[port].lane_config);

	bp->link_params.speed_cap_mask[0] =
		SHMEM_RD(bp,
			 dev_info.port_hw_config[port].speed_capability_mask) &
		PORT_HW_CFG_SPEED_CAPABILITY_D0_MASK;
	bp->link_params.speed_cap_mask[1] =
		SHMEM_RD(bp,
			 dev_info.port_hw_config[port].speed_capability_mask2) &
		PORT_HW_CFG_SPEED_CAPABILITY_D0_MASK;
	bp->port.link_config[0] =
		SHMEM_RD(bp, dev_info.port_feature_config[port].link_config);

	bp->port.link_config[1] =
		SHMEM_RD(bp, dev_info.port_feature_config[port].link_config2);

	bp->link_params.multi_phy_config =
		SHMEM_RD(bp, dev_info.port_hw_config[port].multi_phy_config);
	/* If the device is capable of WoL, set the शेष state according
	 * to the HW
	 */
	config = SHMEM_RD(bp, dev_info.port_feature_config[port].config);
	bp->wol = (!(bp->flags & NO_WOL_FLAG) &&
		   (config & PORT_FEATURE_WOL_ENABLED));

	अगर ((config & PORT_FEAT_CFG_STORAGE_PERSONALITY_MASK) ==
	    PORT_FEAT_CFG_STORAGE_PERSONALITY_FCOE && !IS_MF(bp))
		bp->flags |= NO_ISCSI_FLAG;
	अगर ((config & PORT_FEAT_CFG_STORAGE_PERSONALITY_MASK) ==
	    PORT_FEAT_CFG_STORAGE_PERSONALITY_ISCSI && !(IS_MF(bp)))
		bp->flags |= NO_FCOE_FLAG;

	BNX2X_DEV_INFO("lane_config 0x%08x  speed_cap_mask0 0x%08x  link_config0 0x%08x\n",
		       bp->link_params.lane_config,
		       bp->link_params.speed_cap_mask[0],
		       bp->port.link_config[0]);

	bp->link_params.चयन_cfg = (bp->port.link_config[0] &
				      PORT_FEATURE_CONNECTED_SWITCH_MASK);
	bnx2x_phy_probe(&bp->link_params);
	bnx2x_link_settings_supported(bp, bp->link_params.चयन_cfg);

	bnx2x_link_settings_requested(bp);

	/*
	 * If connected directly, work with the पूर्णांकernal PHY, otherwise, work
	 * with the बाह्यal PHY
	 */
	ext_phy_config =
		SHMEM_RD(bp,
			 dev_info.port_hw_config[port].बाह्यal_phy_config);
	ext_phy_type = XGXS_EXT_PHY_TYPE(ext_phy_config);
	अगर (ext_phy_type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_सूचीECT)
		bp->mdio.prtad = bp->port.phy_addr;

	अन्यथा अगर ((ext_phy_type != PORT_HW_CFG_XGXS_EXT_PHY_TYPE_FAILURE) &&
		 (ext_phy_type != PORT_HW_CFG_XGXS_EXT_PHY_TYPE_NOT_CONN))
		bp->mdio.prtad =
			XGXS_EXT_PHY_ADDR(ext_phy_config);

	/* Configure link feature according to nvram value */
	eee_mode = (((SHMEM_RD(bp, dev_info.
		      port_feature_config[port].eee_घातer_mode)) &
		     PORT_FEAT_CFG_EEE_POWER_MODE_MASK) >>
		    PORT_FEAT_CFG_EEE_POWER_MODE_SHIFT);
	अगर (eee_mode != PORT_FEAT_CFG_EEE_POWER_MODE_DISABLED) अणु
		bp->link_params.eee_mode = EEE_MODE_ADV_LPI |
					   EEE_MODE_ENABLE_LPI |
					   EEE_MODE_OUTPUT_TIME;
	पूर्ण अन्यथा अणु
		bp->link_params.eee_mode = 0;
	पूर्ण
पूर्ण

व्योम bnx2x_get_iscsi_info(काष्ठा bnx2x *bp)
अणु
	u32 no_flags = NO_ISCSI_FLAG;
	पूर्णांक port = BP_PORT(bp);
	u32 max_iscsi_conn = FW_ENCODE_32BIT_PATTERN ^ SHMEM_RD(bp,
				drv_lic_key[port].max_iscsi_conn);

	अगर (!CNIC_SUPPORT(bp)) अणु
		bp->flags |= no_flags;
		वापस;
	पूर्ण

	/* Get the number of maximum allowed iSCSI connections */
	bp->cnic_eth_dev.max_iscsi_conn =
		(max_iscsi_conn & BNX2X_MAX_ISCSI_INIT_CONN_MASK) >>
		BNX2X_MAX_ISCSI_INIT_CONN_SHIFT;

	BNX2X_DEV_INFO("max_iscsi_conn 0x%x\n",
		       bp->cnic_eth_dev.max_iscsi_conn);

	/*
	 * If maximum allowed number of connections is zero -
	 * disable the feature.
	 */
	अगर (!bp->cnic_eth_dev.max_iscsi_conn)
		bp->flags |= no_flags;
पूर्ण

अटल व्योम bnx2x_get_ext_wwn_info(काष्ठा bnx2x *bp, पूर्णांक func)
अणु
	/* Port info */
	bp->cnic_eth_dev.fcoe_wwn_port_name_hi =
		MF_CFG_RD(bp, func_ext_config[func].fcoe_wwn_port_name_upper);
	bp->cnic_eth_dev.fcoe_wwn_port_name_lo =
		MF_CFG_RD(bp, func_ext_config[func].fcoe_wwn_port_name_lower);

	/* Node info */
	bp->cnic_eth_dev.fcoe_wwn_node_name_hi =
		MF_CFG_RD(bp, func_ext_config[func].fcoe_wwn_node_name_upper);
	bp->cnic_eth_dev.fcoe_wwn_node_name_lo =
		MF_CFG_RD(bp, func_ext_config[func].fcoe_wwn_node_name_lower);
पूर्ण

अटल पूर्णांक bnx2x_shared_fcoe_funcs(काष्ठा bnx2x *bp)
अणु
	u8 count = 0;

	अगर (IS_MF(bp)) अणु
		u8 fid;

		/* iterate over असलolute function ids क्रम this path: */
		क्रम (fid = BP_PATH(bp); fid < E2_FUNC_MAX * 2; fid += 2) अणु
			अगर (IS_MF_SD(bp)) अणु
				u32 cfg = MF_CFG_RD(bp,
						    func_mf_config[fid].config);

				अगर (!(cfg & FUNC_MF_CFG_FUNC_HIDE) &&
				    ((cfg & FUNC_MF_CFG_PROTOCOL_MASK) ==
					    FUNC_MF_CFG_PROTOCOL_FCOE))
					count++;
			पूर्ण अन्यथा अणु
				u32 cfg = MF_CFG_RD(bp,
						    func_ext_config[fid].
								      func_cfg);

				अगर ((cfg & MACP_FUNC_CFG_FLAGS_ENABLED) &&
				    (cfg & MACP_FUNC_CFG_FLAGS_FCOE_OFFLOAD))
					count++;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु /* SF */
		पूर्णांक port, port_cnt = CHIP_MODE_IS_4_PORT(bp) ? 2 : 1;

		क्रम (port = 0; port < port_cnt; port++) अणु
			u32 lic = SHMEM_RD(bp,
					   drv_lic_key[port].max_fcoe_conn) ^
				  FW_ENCODE_32BIT_PATTERN;
			अगर (lic)
				count++;
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण

अटल व्योम bnx2x_get_fcoe_info(काष्ठा bnx2x *bp)
अणु
	पूर्णांक port = BP_PORT(bp);
	पूर्णांक func = BP_ABS_FUNC(bp);
	u32 max_fcoe_conn = FW_ENCODE_32BIT_PATTERN ^ SHMEM_RD(bp,
				drv_lic_key[port].max_fcoe_conn);
	u8 num_fcoe_func = bnx2x_shared_fcoe_funcs(bp);

	अगर (!CNIC_SUPPORT(bp)) अणु
		bp->flags |= NO_FCOE_FLAG;
		वापस;
	पूर्ण

	/* Get the number of maximum allowed FCoE connections */
	bp->cnic_eth_dev.max_fcoe_conn =
		(max_fcoe_conn & BNX2X_MAX_FCOE_INIT_CONN_MASK) >>
		BNX2X_MAX_FCOE_INIT_CONN_SHIFT;

	/* Calculate the number of maximum allowed FCoE tasks */
	bp->cnic_eth_dev.max_fcoe_exchanges = MAX_NUM_FCOE_TASKS_PER_ENGINE;

	/* check अगर FCoE resources must be shared between dअगरferent functions */
	अगर (num_fcoe_func)
		bp->cnic_eth_dev.max_fcoe_exchanges /= num_fcoe_func;

	/* Read the WWN: */
	अगर (!IS_MF(bp)) अणु
		/* Port info */
		bp->cnic_eth_dev.fcoe_wwn_port_name_hi =
			SHMEM_RD(bp,
				 dev_info.port_hw_config[port].
				 fcoe_wwn_port_name_upper);
		bp->cnic_eth_dev.fcoe_wwn_port_name_lo =
			SHMEM_RD(bp,
				 dev_info.port_hw_config[port].
				 fcoe_wwn_port_name_lower);

		/* Node info */
		bp->cnic_eth_dev.fcoe_wwn_node_name_hi =
			SHMEM_RD(bp,
				 dev_info.port_hw_config[port].
				 fcoe_wwn_node_name_upper);
		bp->cnic_eth_dev.fcoe_wwn_node_name_lo =
			SHMEM_RD(bp,
				 dev_info.port_hw_config[port].
				 fcoe_wwn_node_name_lower);
	पूर्ण अन्यथा अगर (!IS_MF_SD(bp)) अणु
		/* Read the WWN info only अगर the FCoE feature is enabled क्रम
		 * this function.
		 */
		अगर (BNX2X_HAS_MF_EXT_PROTOCOL_FCOE(bp))
			bnx2x_get_ext_wwn_info(bp, func);
	पूर्ण अन्यथा अणु
		अगर (BNX2X_IS_MF_SD_PROTOCOL_FCOE(bp) && !CHIP_IS_E1x(bp))
			bnx2x_get_ext_wwn_info(bp, func);
	पूर्ण

	BNX2X_DEV_INFO("max_fcoe_conn 0x%x\n", bp->cnic_eth_dev.max_fcoe_conn);

	/*
	 * If maximum allowed number of connections is zero -
	 * disable the feature.
	 */
	अगर (!bp->cnic_eth_dev.max_fcoe_conn) अणु
		bp->flags |= NO_FCOE_FLAG;
		eth_zero_addr(bp->fip_mac);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_get_cnic_info(काष्ठा bnx2x *bp)
अणु
	/*
	 * iSCSI may be dynamically disabled but पढ़ोing
	 * info here we will decrease memory usage by driver
	 * अगर the feature is disabled क्रम good
	 */
	bnx2x_get_iscsi_info(bp);
	bnx2x_get_fcoe_info(bp);
पूर्ण

अटल व्योम bnx2x_get_cnic_mac_hwinfo(काष्ठा bnx2x *bp)
अणु
	u32 val, val2;
	पूर्णांक func = BP_ABS_FUNC(bp);
	पूर्णांक port = BP_PORT(bp);
	u8 *iscsi_mac = bp->cnic_eth_dev.iscsi_mac;
	u8 *fip_mac = bp->fip_mac;

	अगर (IS_MF(bp)) अणु
		/* iSCSI and FCoE NPAR MACs: अगर there is no either iSCSI or
		 * FCoE MAC then the appropriate feature should be disabled.
		 * In non SD mode features configuration comes from काष्ठा
		 * func_ext_config.
		 */
		अगर (!IS_MF_SD(bp)) अणु
			u32 cfg = MF_CFG_RD(bp, func_ext_config[func].func_cfg);
			अगर (cfg & MACP_FUNC_CFG_FLAGS_ISCSI_OFFLOAD) अणु
				val2 = MF_CFG_RD(bp, func_ext_config[func].
						 iscsi_mac_addr_upper);
				val = MF_CFG_RD(bp, func_ext_config[func].
						iscsi_mac_addr_lower);
				bnx2x_set_mac_buf(iscsi_mac, val, val2);
				BNX2X_DEV_INFO
					("Read iSCSI MAC: %pM\n", iscsi_mac);
			पूर्ण अन्यथा अणु
				bp->flags |= NO_ISCSI_OOO_FLAG | NO_ISCSI_FLAG;
			पूर्ण

			अगर (cfg & MACP_FUNC_CFG_FLAGS_FCOE_OFFLOAD) अणु
				val2 = MF_CFG_RD(bp, func_ext_config[func].
						 fcoe_mac_addr_upper);
				val = MF_CFG_RD(bp, func_ext_config[func].
						fcoe_mac_addr_lower);
				bnx2x_set_mac_buf(fip_mac, val, val2);
				BNX2X_DEV_INFO
					("Read FCoE L2 MAC: %pM\n", fip_mac);
			पूर्ण अन्यथा अणु
				bp->flags |= NO_FCOE_FLAG;
			पूर्ण

			bp->mf_ext_config = cfg;

		पूर्ण अन्यथा अणु /* SD MODE */
			अगर (BNX2X_IS_MF_SD_PROTOCOL_ISCSI(bp)) अणु
				/* use primary mac as iscsi mac */
				स_नकल(iscsi_mac, bp->dev->dev_addr, ETH_ALEN);

				BNX2X_DEV_INFO("SD ISCSI MODE\n");
				BNX2X_DEV_INFO
					("Read iSCSI MAC: %pM\n", iscsi_mac);
			पूर्ण अन्यथा अगर (BNX2X_IS_MF_SD_PROTOCOL_FCOE(bp)) अणु
				/* use primary mac as fip mac */
				स_नकल(fip_mac, bp->dev->dev_addr, ETH_ALEN);
				BNX2X_DEV_INFO("SD FCoE MODE\n");
				BNX2X_DEV_INFO
					("Read FIP MAC: %pM\n", fip_mac);
			पूर्ण
		पूर्ण

		/* If this is a storage-only पूर्णांकerface, use SAN mac as
		 * primary MAC. Notice that क्रम SD this is alपढ़ोy the हाल,
		 * as the SAN mac was copied from the primary MAC.
		 */
		अगर (IS_MF_FCOE_AFEX(bp))
			स_नकल(bp->dev->dev_addr, fip_mac, ETH_ALEN);
	पूर्ण अन्यथा अणु
		val2 = SHMEM_RD(bp, dev_info.port_hw_config[port].
				iscsi_mac_upper);
		val = SHMEM_RD(bp, dev_info.port_hw_config[port].
			       iscsi_mac_lower);
		bnx2x_set_mac_buf(iscsi_mac, val, val2);

		val2 = SHMEM_RD(bp, dev_info.port_hw_config[port].
				fcoe_fip_mac_upper);
		val = SHMEM_RD(bp, dev_info.port_hw_config[port].
			       fcoe_fip_mac_lower);
		bnx2x_set_mac_buf(fip_mac, val, val2);
	पूर्ण

	/* Disable iSCSI OOO अगर MAC configuration is invalid. */
	अगर (!is_valid_ether_addr(iscsi_mac)) अणु
		bp->flags |= NO_ISCSI_OOO_FLAG | NO_ISCSI_FLAG;
		eth_zero_addr(iscsi_mac);
	पूर्ण

	/* Disable FCoE अगर MAC configuration is invalid. */
	अगर (!is_valid_ether_addr(fip_mac)) अणु
		bp->flags |= NO_FCOE_FLAG;
		eth_zero_addr(bp->fip_mac);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_get_mac_hwinfo(काष्ठा bnx2x *bp)
अणु
	u32 val, val2;
	पूर्णांक func = BP_ABS_FUNC(bp);
	पूर्णांक port = BP_PORT(bp);

	/* Zero primary MAC configuration */
	eth_zero_addr(bp->dev->dev_addr);

	अगर (BP_NOMCP(bp)) अणु
		BNX2X_ERROR("warning: random MAC workaround active\n");
		eth_hw_addr_अक्रमom(bp->dev);
	पूर्ण अन्यथा अगर (IS_MF(bp)) अणु
		val2 = MF_CFG_RD(bp, func_mf_config[func].mac_upper);
		val = MF_CFG_RD(bp, func_mf_config[func].mac_lower);
		अगर ((val2 != FUNC_MF_CFG_UPPERMAC_DEFAULT) &&
		    (val != FUNC_MF_CFG_LOWERMAC_DEFAULT))
			bnx2x_set_mac_buf(bp->dev->dev_addr, val, val2);

		अगर (CNIC_SUPPORT(bp))
			bnx2x_get_cnic_mac_hwinfo(bp);
	पूर्ण अन्यथा अणु
		/* in SF पढ़ो MACs from port configuration */
		val2 = SHMEM_RD(bp, dev_info.port_hw_config[port].mac_upper);
		val = SHMEM_RD(bp, dev_info.port_hw_config[port].mac_lower);
		bnx2x_set_mac_buf(bp->dev->dev_addr, val, val2);

		अगर (CNIC_SUPPORT(bp))
			bnx2x_get_cnic_mac_hwinfo(bp);
	पूर्ण

	अगर (!BP_NOMCP(bp)) अणु
		/* Read physical port identअगरier from shmem */
		val2 = SHMEM_RD(bp, dev_info.port_hw_config[port].mac_upper);
		val = SHMEM_RD(bp, dev_info.port_hw_config[port].mac_lower);
		bnx2x_set_mac_buf(bp->phys_port_id, val, val2);
		bp->flags |= HAS_PHYS_PORT_ID;
	पूर्ण

	स_नकल(bp->link_params.mac_addr, bp->dev->dev_addr, ETH_ALEN);

	अगर (!is_valid_ether_addr(bp->dev->dev_addr))
		dev_err(&bp->pdev->dev,
			"bad Ethernet MAC address configuration: %pM\n"
			"change it manually before bringing up the appropriate network interface\n",
			bp->dev->dev_addr);
पूर्ण

अटल bool bnx2x_get_dropless_info(काष्ठा bnx2x *bp)
अणु
	पूर्णांक पंचांगp;
	u32 cfg;

	अगर (IS_VF(bp))
		वापस false;

	अगर (IS_MF(bp) && !CHIP_IS_E1x(bp)) अणु
		/* Take function: पंचांगp = func */
		पंचांगp = BP_ABS_FUNC(bp);
		cfg = MF_CFG_RD(bp, func_ext_config[पंचांगp].func_cfg);
		cfg = !!(cfg & MACP_FUNC_CFG_PAUSE_ON_HOST_RING);
	पूर्ण अन्यथा अणु
		/* Take port: पंचांगp = port */
		पंचांगp = BP_PORT(bp);
		cfg = SHMEM_RD(bp,
			       dev_info.port_hw_config[पंचांगp].generic_features);
		cfg = !!(cfg & PORT_HW_CFG_PAUSE_ON_HOST_RING_ENABLED);
	पूर्ण
	वापस cfg;
पूर्ण

अटल व्योम validate_set_si_mode(काष्ठा bnx2x *bp)
अणु
	u8 func = BP_ABS_FUNC(bp);
	u32 val;

	val = MF_CFG_RD(bp, func_mf_config[func].mac_upper);

	/* check क्रम legal mac (upper bytes) */
	अगर (val != 0xffff) अणु
		bp->mf_mode = MULTI_FUNCTION_SI;
		bp->mf_config[BP_VN(bp)] =
			MF_CFG_RD(bp, func_mf_config[func].config);
	पूर्ण अन्यथा
		BNX2X_DEV_INFO("illegal MAC address for SI\n");
पूर्ण

अटल पूर्णांक bnx2x_get_hwinfo(काष्ठा bnx2x *bp)
अणु
	पूर्णांक /*असल*/func = BP_ABS_FUNC(bp);
	पूर्णांक vn;
	u32 val = 0, val2 = 0;
	पूर्णांक rc = 0;

	/* Validate that chip access is feasible */
	अगर (REG_RD(bp, MISC_REG_CHIP_NUM) == 0xffffffff) अणु
		dev_err(&bp->pdev->dev,
			"Chip read returns all Fs. Preventing probe from continuing\n");
		वापस -EINVAL;
	पूर्ण

	bnx2x_get_common_hwinfo(bp);

	/*
	 * initialize IGU parameters
	 */
	अगर (CHIP_IS_E1x(bp)) अणु
		bp->common.पूर्णांक_block = INT_BLOCK_HC;

		bp->igu_dsb_id = DEF_SB_IGU_ID;
		bp->igu_base_sb = 0;
	पूर्ण अन्यथा अणु
		bp->common.पूर्णांक_block = INT_BLOCK_IGU;

		/* करो not allow device reset during IGU info processing */
		bnx2x_acquire_hw_lock(bp, HW_LOCK_RESOURCE_RESET);

		val = REG_RD(bp, IGU_REG_BLOCK_CONFIGURATION);

		अगर (val & IGU_BLOCK_CONFIGURATION_REG_BACKWARD_COMP_EN) अणु
			पूर्णांक tout = 5000;

			BNX2X_DEV_INFO("FORCING Normal Mode\n");

			val &= ~(IGU_BLOCK_CONFIGURATION_REG_BACKWARD_COMP_EN);
			REG_WR(bp, IGU_REG_BLOCK_CONFIGURATION, val);
			REG_WR(bp, IGU_REG_RESET_MEMORIES, 0x7f);

			जबतक (tout && REG_RD(bp, IGU_REG_RESET_MEMORIES)) अणु
				tout--;
				usleep_range(1000, 2000);
			पूर्ण

			अगर (REG_RD(bp, IGU_REG_RESET_MEMORIES)) अणु
				dev_err(&bp->pdev->dev,
					"FORCING Normal Mode failed!!!\n");
				bnx2x_release_hw_lock(bp,
						      HW_LOCK_RESOURCE_RESET);
				वापस -EPERM;
			पूर्ण
		पूर्ण

		अगर (val & IGU_BLOCK_CONFIGURATION_REG_BACKWARD_COMP_EN) अणु
			BNX2X_DEV_INFO("IGU Backward Compatible Mode\n");
			bp->common.पूर्णांक_block |= INT_BLOCK_MODE_BW_COMP;
		पूर्ण अन्यथा
			BNX2X_DEV_INFO("IGU Normal Mode\n");

		rc = bnx2x_get_igu_cam_info(bp);
		bnx2x_release_hw_lock(bp, HW_LOCK_RESOURCE_RESET);
		अगर (rc)
			वापस rc;
	पूर्ण

	/*
	 * set base FW non-शेष (fast path) status block id, this value is
	 * used to initialize the fw_sb_id saved on the fp/queue काष्ठाure to
	 * determine the id used by the FW.
	 */
	अगर (CHIP_IS_E1x(bp))
		bp->base_fw_ndsb = BP_PORT(bp) * FP_SB_MAX_E1x + BP_L_ID(bp);
	अन्यथा /*
	      * 57712 - we currently use one FW SB per IGU SB (Rx and Tx of
	      * the same queue are indicated on the same IGU SB). So we prefer
	      * FW and IGU SBs to be the same value.
	      */
		bp->base_fw_ndsb = bp->igu_base_sb;

	BNX2X_DEV_INFO("igu_dsb_id %d  igu_base_sb %d  igu_sb_cnt %d\n"
		       "base_fw_ndsb %d\n", bp->igu_dsb_id, bp->igu_base_sb,
		       bp->igu_sb_cnt, bp->base_fw_ndsb);

	/*
	 * Initialize MF configuration
	 */
	bp->mf_ov = 0;
	bp->mf_mode = 0;
	bp->mf_sub_mode = 0;
	vn = BP_VN(bp);

	अगर (!CHIP_IS_E1(bp) && !BP_NOMCP(bp)) अणु
		BNX2X_DEV_INFO("shmem2base 0x%x, size %d, mfcfg offset %d\n",
			       bp->common.shmem2_base, SHMEM2_RD(bp, size),
			      (u32)दुरत्व(काष्ठा shmem2_region, mf_cfg_addr));

		अगर (SHMEM2_HAS(bp, mf_cfg_addr))
			bp->common.mf_cfg_base = SHMEM2_RD(bp, mf_cfg_addr);
		अन्यथा
			bp->common.mf_cfg_base = bp->common.shmem_base +
				दुरत्व(काष्ठा shmem_region, func_mb) +
				E1H_FUNC_MAX * माप(काष्ठा drv_func_mb);
		/*
		 * get mf configuration:
		 * 1. Existence of MF configuration
		 * 2. MAC address must be legal (check only upper bytes)
		 *    क्रम  Switch-Independent mode;
		 *    OVLAN must be legal क्रम Switch-Dependent mode
		 * 3. SF_MODE configures specअगरic MF mode
		 */
		अगर (bp->common.mf_cfg_base != SHMEM_MF_CFG_ADDR_NONE) अणु
			/* get mf configuration */
			val = SHMEM_RD(bp,
				       dev_info.shared_feature_config.config);
			val &= SHARED_FEAT_CFG_FORCE_SF_MODE_MASK;

			चयन (val) अणु
			हाल SHARED_FEAT_CFG_FORCE_SF_MODE_SWITCH_INDEPT:
				validate_set_si_mode(bp);
				अवरोध;
			हाल SHARED_FEAT_CFG_FORCE_SF_MODE_AFEX_MODE:
				अगर ((!CHIP_IS_E1x(bp)) &&
				    (MF_CFG_RD(bp, func_mf_config[func].
					       mac_upper) != 0xffff) &&
				    (SHMEM2_HAS(bp,
						afex_driver_support))) अणु
					bp->mf_mode = MULTI_FUNCTION_AFEX;
					bp->mf_config[vn] = MF_CFG_RD(bp,
						func_mf_config[func].config);
				पूर्ण अन्यथा अणु
					BNX2X_DEV_INFO("can not configure afex mode\n");
				पूर्ण
				अवरोध;
			हाल SHARED_FEAT_CFG_FORCE_SF_MODE_MF_ALLOWED:
				/* get OV configuration */
				val = MF_CFG_RD(bp,
					func_mf_config[FUNC_0].e1hov_tag);
				val &= FUNC_MF_CFG_E1HOV_TAG_MASK;

				अगर (val != FUNC_MF_CFG_E1HOV_TAG_DEFAULT) अणु
					bp->mf_mode = MULTI_FUNCTION_SD;
					bp->mf_config[vn] = MF_CFG_RD(bp,
						func_mf_config[func].config);
				पूर्ण अन्यथा
					BNX2X_DEV_INFO("illegal OV for SD\n");
				अवरोध;
			हाल SHARED_FEAT_CFG_FORCE_SF_MODE_BD_MODE:
				bp->mf_mode = MULTI_FUNCTION_SD;
				bp->mf_sub_mode = SUB_MF_MODE_BD;
				bp->mf_config[vn] =
					MF_CFG_RD(bp,
						  func_mf_config[func].config);

				अगर (SHMEM2_HAS(bp, mtu_size)) अणु
					पूर्णांक mtu_idx = BP_FW_MB_IDX(bp);
					u16 mtu_size;
					u32 mtu;

					mtu = SHMEM2_RD(bp, mtu_size[mtu_idx]);
					mtu_size = (u16)mtu;
					DP(NETIF_MSG_IFUP, "Read MTU size %04x [%08x]\n",
					   mtu_size, mtu);

					/* अगर valid: update device mtu */
					अगर ((mtu_size >= ETH_MIN_PACKET_SIZE) &&
					    (mtu_size <=
					     ETH_MAX_JUMBO_PACKET_SIZE))
						bp->dev->mtu = mtu_size;
				पूर्ण
				अवरोध;
			हाल SHARED_FEAT_CFG_FORCE_SF_MODE_UFP_MODE:
				bp->mf_mode = MULTI_FUNCTION_SD;
				bp->mf_sub_mode = SUB_MF_MODE_UFP;
				bp->mf_config[vn] =
					MF_CFG_RD(bp,
						  func_mf_config[func].config);
				अवरोध;
			हाल SHARED_FEAT_CFG_FORCE_SF_MODE_FORCED_SF:
				bp->mf_config[vn] = 0;
				अवरोध;
			हाल SHARED_FEAT_CFG_FORCE_SF_MODE_EXTENDED_MODE:
				val2 = SHMEM_RD(bp,
					dev_info.shared_hw_config.config_3);
				val2 &= SHARED_HW_CFG_EXTENDED_MF_MODE_MASK;
				चयन (val2) अणु
				हाल SHARED_HW_CFG_EXTENDED_MF_MODE_NPAR1_DOT_5:
					validate_set_si_mode(bp);
					bp->mf_sub_mode =
							SUB_MF_MODE_NPAR1_DOT_5;
					अवरोध;
				शेष:
					/* Unknown configuration */
					bp->mf_config[vn] = 0;
					BNX2X_DEV_INFO("unknown extended MF mode 0x%x\n",
						       val);
				पूर्ण
				अवरोध;
			शेष:
				/* Unknown configuration: reset mf_config */
				bp->mf_config[vn] = 0;
				BNX2X_DEV_INFO("unknown MF mode 0x%x\n", val);
			पूर्ण
		पूर्ण

		BNX2X_DEV_INFO("%s function mode\n",
			       IS_MF(bp) ? "multi" : "single");

		चयन (bp->mf_mode) अणु
		हाल MULTI_FUNCTION_SD:
			val = MF_CFG_RD(bp, func_mf_config[func].e1hov_tag) &
			      FUNC_MF_CFG_E1HOV_TAG_MASK;
			अगर (val != FUNC_MF_CFG_E1HOV_TAG_DEFAULT) अणु
				bp->mf_ov = val;
				bp->path_has_ovlan = true;

				BNX2X_DEV_INFO("MF OV for func %d is %d (0x%04x)\n",
					       func, bp->mf_ov, bp->mf_ov);
			पूर्ण अन्यथा अगर ((bp->mf_sub_mode == SUB_MF_MODE_UFP) ||
				   (bp->mf_sub_mode == SUB_MF_MODE_BD)) अणु
				dev_err(&bp->pdev->dev,
					"Unexpected - no valid MF OV for func %d in UFP/BD mode\n",
					func);
				bp->path_has_ovlan = true;
			पूर्ण अन्यथा अणु
				dev_err(&bp->pdev->dev,
					"No valid MF OV for func %d, aborting\n",
					func);
				वापस -EPERM;
			पूर्ण
			अवरोध;
		हाल MULTI_FUNCTION_AFEX:
			BNX2X_DEV_INFO("func %d is in MF afex mode\n", func);
			अवरोध;
		हाल MULTI_FUNCTION_SI:
			BNX2X_DEV_INFO("func %d is in MF switch-independent mode\n",
				       func);
			अवरोध;
		शेष:
			अगर (vn) अणु
				dev_err(&bp->pdev->dev,
					"VN %d is in a single function mode, aborting\n",
					vn);
				वापस -EPERM;
			पूर्ण
			अवरोध;
		पूर्ण

		/* check अगर other port on the path needs ovlan:
		 * Since MF configuration is shared between ports
		 * Possible mixed modes are only
		 * अणुSF, SIपूर्ण अणुSF, SDपूर्ण अणुSD, SFपूर्ण अणुSI, SFपूर्ण
		 */
		अगर (CHIP_MODE_IS_4_PORT(bp) &&
		    !bp->path_has_ovlan &&
		    !IS_MF(bp) &&
		    bp->common.mf_cfg_base != SHMEM_MF_CFG_ADDR_NONE) अणु
			u8 other_port = !BP_PORT(bp);
			u8 other_func = BP_PATH(bp) + 2*other_port;
			val = MF_CFG_RD(bp,
					func_mf_config[other_func].e1hov_tag);
			अगर (val != FUNC_MF_CFG_E1HOV_TAG_DEFAULT)
				bp->path_has_ovlan = true;
		पूर्ण
	पूर्ण

	/* adjust igu_sb_cnt to MF क्रम E1H */
	अगर (CHIP_IS_E1H(bp) && IS_MF(bp))
		bp->igu_sb_cnt = min_t(u8, bp->igu_sb_cnt, E1H_MAX_MF_SB_COUNT);

	/* port info */
	bnx2x_get_port_hwinfo(bp);

	/* Get MAC addresses */
	bnx2x_get_mac_hwinfo(bp);

	bnx2x_get_cnic_info(bp);

	वापस rc;
पूर्ण

अटल व्योम bnx2x_पढ़ो_fwinfo(काष्ठा bnx2x *bp)
अणु
	पूर्णांक cnt, i, block_end, rodi;
	अक्षर vpd_start[BNX2X_VPD_LEN+1];
	अक्षर str_id_reg[VENDOR_ID_LEN+1];
	अक्षर str_id_cap[VENDOR_ID_LEN+1];
	अक्षर *vpd_data;
	अक्षर *vpd_extended_data = शून्य;
	u8 len;

	cnt = pci_पढ़ो_vpd(bp->pdev, 0, BNX2X_VPD_LEN, vpd_start);
	स_रखो(bp->fw_ver, 0, माप(bp->fw_ver));

	अगर (cnt < BNX2X_VPD_LEN)
		जाओ out_not_found;

	/* VPD RO tag should be first tag after identअगरier string, hence
	 * we should be able to find it in first BNX2X_VPD_LEN अक्षरs
	 */
	i = pci_vpd_find_tag(vpd_start, BNX2X_VPD_LEN, PCI_VPD_LRDT_RO_DATA);
	अगर (i < 0)
		जाओ out_not_found;

	block_end = i + PCI_VPD_LRDT_TAG_SIZE +
		    pci_vpd_lrdt_size(&vpd_start[i]);

	i += PCI_VPD_LRDT_TAG_SIZE;

	अगर (block_end > BNX2X_VPD_LEN) अणु
		vpd_extended_data = kदो_स्मृति(block_end, GFP_KERNEL);
		अगर (vpd_extended_data  == शून्य)
			जाओ out_not_found;

		/* पढ़ो rest of vpd image पूर्णांकo vpd_extended_data */
		स_नकल(vpd_extended_data, vpd_start, BNX2X_VPD_LEN);
		cnt = pci_पढ़ो_vpd(bp->pdev, BNX2X_VPD_LEN,
				   block_end - BNX2X_VPD_LEN,
				   vpd_extended_data + BNX2X_VPD_LEN);
		अगर (cnt < (block_end - BNX2X_VPD_LEN))
			जाओ out_not_found;
		vpd_data = vpd_extended_data;
	पूर्ण अन्यथा
		vpd_data = vpd_start;

	/* now vpd_data holds full vpd content in both हालs */

	rodi = pci_vpd_find_info_keyword(vpd_data, i, block_end,
				   PCI_VPD_RO_KEYWORD_MFR_ID);
	अगर (rodi < 0)
		जाओ out_not_found;

	len = pci_vpd_info_field_size(&vpd_data[rodi]);

	अगर (len != VENDOR_ID_LEN)
		जाओ out_not_found;

	rodi += PCI_VPD_INFO_FLD_HDR_SIZE;

	/* venकरोr specअगरic info */
	snम_लिखो(str_id_reg, VENDOR_ID_LEN + 1, "%04x", PCI_VENDOR_ID_DELL);
	snम_लिखो(str_id_cap, VENDOR_ID_LEN + 1, "%04X", PCI_VENDOR_ID_DELL);
	अगर (!म_भेदन(str_id_reg, &vpd_data[rodi], VENDOR_ID_LEN) ||
	    !म_भेदन(str_id_cap, &vpd_data[rodi], VENDOR_ID_LEN)) अणु

		rodi = pci_vpd_find_info_keyword(vpd_data, i, block_end,
						PCI_VPD_RO_KEYWORD_VENDOR0);
		अगर (rodi >= 0) अणु
			len = pci_vpd_info_field_size(&vpd_data[rodi]);

			rodi += PCI_VPD_INFO_FLD_HDR_SIZE;

			अगर (len < 32 && (len + rodi) <= BNX2X_VPD_LEN) अणु
				स_नकल(bp->fw_ver, &vpd_data[rodi], len);
				bp->fw_ver[len] = ' ';
			पूर्ण
		पूर्ण
		kमुक्त(vpd_extended_data);
		वापस;
	पूर्ण
out_not_found:
	kमुक्त(vpd_extended_data);
	वापस;
पूर्ण

अटल व्योम bnx2x_set_modes_biपंचांगap(काष्ठा bnx2x *bp)
अणु
	u32 flags = 0;

	अगर (CHIP_REV_IS_FPGA(bp))
		SET_FLAGS(flags, MODE_FPGA);
	अन्यथा अगर (CHIP_REV_IS_EMUL(bp))
		SET_FLAGS(flags, MODE_EMUL);
	अन्यथा
		SET_FLAGS(flags, MODE_ASIC);

	अगर (CHIP_MODE_IS_4_PORT(bp))
		SET_FLAGS(flags, MODE_PORT4);
	अन्यथा
		SET_FLAGS(flags, MODE_PORT2);

	अगर (CHIP_IS_E2(bp))
		SET_FLAGS(flags, MODE_E2);
	अन्यथा अगर (CHIP_IS_E3(bp)) अणु
		SET_FLAGS(flags, MODE_E3);
		अगर (CHIP_REV(bp) == CHIP_REV_Ax)
			SET_FLAGS(flags, MODE_E3_A0);
		अन्यथा /*अगर (CHIP_REV(bp) == CHIP_REV_Bx)*/
			SET_FLAGS(flags, MODE_E3_B0 | MODE_COS3);
	पूर्ण

	अगर (IS_MF(bp)) अणु
		SET_FLAGS(flags, MODE_MF);
		चयन (bp->mf_mode) अणु
		हाल MULTI_FUNCTION_SD:
			SET_FLAGS(flags, MODE_MF_SD);
			अवरोध;
		हाल MULTI_FUNCTION_SI:
			SET_FLAGS(flags, MODE_MF_SI);
			अवरोध;
		हाल MULTI_FUNCTION_AFEX:
			SET_FLAGS(flags, MODE_MF_AFEX);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा
		SET_FLAGS(flags, MODE_SF);

#अगर defined(__LITTLE_ENDIAN)
	SET_FLAGS(flags, MODE_LITTLE_ENDIAN);
#अन्यथा /*(__BIG_ENDIAN)*/
	SET_FLAGS(flags, MODE_BIG_ENDIAN);
#पूर्ण_अगर
	INIT_MODE_FLAGS(bp) = flags;
पूर्ण

अटल पूर्णांक bnx2x_init_bp(काष्ठा bnx2x *bp)
अणु
	पूर्णांक func;
	पूर्णांक rc;

	mutex_init(&bp->port.phy_mutex);
	mutex_init(&bp->fw_mb_mutex);
	mutex_init(&bp->drv_info_mutex);
	sema_init(&bp->stats_lock, 1);
	bp->drv_info_mng_owner = false;
	INIT_LIST_HEAD(&bp->vlan_reg);

	INIT_DELAYED_WORK(&bp->sp_task, bnx2x_sp_task);
	INIT_DELAYED_WORK(&bp->sp_rtnl_task, bnx2x_sp_rtnl_task);
	INIT_DELAYED_WORK(&bp->period_task, bnx2x_period_task);
	INIT_DELAYED_WORK(&bp->iov_task, bnx2x_iov_task);
	अगर (IS_PF(bp)) अणु
		rc = bnx2x_get_hwinfo(bp);
		अगर (rc)
			वापस rc;
	पूर्ण अन्यथा अणु
		eth_zero_addr(bp->dev->dev_addr);
	पूर्ण

	bnx2x_set_modes_biपंचांगap(bp);

	rc = bnx2x_alloc_mem_bp(bp);
	अगर (rc)
		वापस rc;

	bnx2x_पढ़ो_fwinfo(bp);

	func = BP_FUNC(bp);

	/* need to reset chip अगर undi was active */
	अगर (IS_PF(bp) && !BP_NOMCP(bp)) अणु
		/* init fw_seq */
		bp->fw_seq =
			SHMEM_RD(bp, func_mb[BP_FW_MB_IDX(bp)].drv_mb_header) &
							DRV_MSG_SEQ_NUMBER_MASK;
		BNX2X_DEV_INFO("fw_seq 0x%08x\n", bp->fw_seq);

		rc = bnx2x_prev_unload(bp);
		अगर (rc) अणु
			bnx2x_मुक्त_mem_bp(bp);
			वापस rc;
		पूर्ण
	पूर्ण

	अगर (CHIP_REV_IS_FPGA(bp))
		dev_err(&bp->pdev->dev, "FPGA detected\n");

	अगर (BP_NOMCP(bp) && (func == 0))
		dev_err(&bp->pdev->dev, "MCP disabled, must load devices in order!\n");

	bp->disable_tpa = disable_tpa;
	bp->disable_tpa |= !!IS_MF_STORAGE_ONLY(bp);
	/* Reduce memory usage in kdump environment by disabling TPA */
	bp->disable_tpa |= is_kdump_kernel();

	/* Set TPA flags */
	अगर (bp->disable_tpa) अणु
		bp->dev->hw_features &= ~(NETIF_F_LRO | NETIF_F_GRO_HW);
		bp->dev->features &= ~(NETIF_F_LRO | NETIF_F_GRO_HW);
	पूर्ण

	अगर (CHIP_IS_E1(bp))
		bp->dropless_fc = false;
	अन्यथा
		bp->dropless_fc = dropless_fc | bnx2x_get_dropless_info(bp);

	bp->mrrs = mrrs;

	bp->tx_ring_size = IS_MF_STORAGE_ONLY(bp) ? 0 : MAX_TX_AVAIL;
	अगर (IS_VF(bp))
		bp->rx_ring_size = MAX_RX_AVAIL;

	/* make sure that the numbers are in the right granularity */
	bp->tx_ticks = (50 / BNX2X_BTR) * BNX2X_BTR;
	bp->rx_ticks = (25 / BNX2X_BTR) * BNX2X_BTR;

	bp->current_पूर्णांकerval = CHIP_REV_IS_SLOW(bp) ? 5*HZ : HZ;

	समयr_setup(&bp->समयr, bnx2x_समयr, 0);
	bp->समयr.expires = jअगरfies + bp->current_पूर्णांकerval;

	अगर (SHMEM2_HAS(bp, dcbx_lldp_params_offset) &&
	    SHMEM2_HAS(bp, dcbx_lldp_dcbx_stat_offset) &&
	    SHMEM2_HAS(bp, dcbx_en) &&
	    SHMEM2_RD(bp, dcbx_lldp_params_offset) &&
	    SHMEM2_RD(bp, dcbx_lldp_dcbx_stat_offset) &&
	    SHMEM2_RD(bp, dcbx_en[BP_PORT(bp)])) अणु
		bnx2x_dcbx_set_state(bp, true, BNX2X_DCBX_ENABLED_ON_NEG_ON);
		bnx2x_dcbx_init_params(bp);
	पूर्ण अन्यथा अणु
		bnx2x_dcbx_set_state(bp, false, BNX2X_DCBX_ENABLED_OFF);
	पूर्ण

	अगर (CHIP_IS_E1x(bp))
		bp->cnic_base_cl_id = FP_SB_MAX_E1x;
	अन्यथा
		bp->cnic_base_cl_id = FP_SB_MAX_E2;

	/* multiple tx priority */
	अगर (IS_VF(bp))
		bp->max_cos = 1;
	अन्यथा अगर (CHIP_IS_E1x(bp))
		bp->max_cos = BNX2X_MULTI_TX_COS_E1X;
	अन्यथा अगर (CHIP_IS_E2(bp) || CHIP_IS_E3A0(bp))
		bp->max_cos = BNX2X_MULTI_TX_COS_E2_E3A0;
	अन्यथा अगर (CHIP_IS_E3B0(bp))
		bp->max_cos = BNX2X_MULTI_TX_COS_E3B0;
	अन्यथा
		BNX2X_ERR("unknown chip %x revision %x\n",
			  CHIP_NUM(bp), CHIP_REV(bp));
	BNX2X_DEV_INFO("set bp->max_cos to %d\n", bp->max_cos);

	/* We need at least one शेष status block क्रम slow-path events,
	 * second status block क्रम the L2 queue, and a third status block क्रम
	 * CNIC अगर supported.
	 */
	अगर (IS_VF(bp))
		bp->min_msix_vec_cnt = 1;
	अन्यथा अगर (CNIC_SUPPORT(bp))
		bp->min_msix_vec_cnt = 3;
	अन्यथा /* PF w/o cnic */
		bp->min_msix_vec_cnt = 2;
	BNX2X_DEV_INFO("bp->min_msix_vec_cnt %d", bp->min_msix_vec_cnt);

	bp->dump_preset_idx = 1;

	वापस rc;
पूर्ण

/****************************************************************************
* General service functions
****************************************************************************/

/*
 * net_device service functions
 */

/* called with rtnl_lock */
अटल पूर्णांक bnx2x_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	पूर्णांक rc;

	bp->stats_init = true;

	netअगर_carrier_off(dev);

	bnx2x_set_घातer_state(bp, PCI_D0);

	/* If parity had happen during the unload, then attentions
	 * and/or RECOVERY_IN_PROGRES may still be set. In this हाल we
	 * want the first function loaded on the current engine to
	 * complete the recovery.
	 * Parity recovery is only relevant क्रम PF driver.
	 */
	अगर (IS_PF(bp)) अणु
		पूर्णांक other_engine = BP_PATH(bp) ? 0 : 1;
		bool other_load_status, load_status;
		bool global = false;

		other_load_status = bnx2x_get_load_status(bp, other_engine);
		load_status = bnx2x_get_load_status(bp, BP_PATH(bp));
		अगर (!bnx2x_reset_is_करोne(bp, BP_PATH(bp)) ||
		    bnx2x_chk_parity_attn(bp, &global, true)) अणु
			करो अणु
				/* If there are attentions and they are in a
				 * global blocks, set the GLOBAL_RESET bit
				 * regardless whether it will be this function
				 * that will complete the recovery or not.
				 */
				अगर (global)
					bnx2x_set_reset_global(bp);

				/* Only the first function on the current
				 * engine should try to recover in खोलो. In हाल
				 * of attentions in global blocks only the first
				 * in the chip should try to recover.
				 */
				अगर ((!load_status &&
				     (!global || !other_load_status)) &&
				      bnx2x_trylock_leader_lock(bp) &&
				      !bnx2x_leader_reset(bp)) अणु
					netdev_info(bp->dev,
						    "Recovered in open\n");
					अवरोध;
				पूर्ण

				/* recovery has failed... */
				bnx2x_set_घातer_state(bp, PCI_D3hot);
				bp->recovery_state = BNX2X_RECOVERY_FAILED;

				BNX2X_ERR("Recovery flow hasn't been properly completed yet. Try again later.\n"
					  "If you still see this message after a few retries then power cycle is required.\n");

				वापस -EAGAIN;
			पूर्ण जबतक (0);
		पूर्ण
	पूर्ण

	bp->recovery_state = BNX2X_RECOVERY_DONE;
	rc = bnx2x_nic_load(bp, LOAD_OPEN);
	अगर (rc)
		वापस rc;

	वापस 0;
पूर्ण

/* called with rtnl_lock */
अटल पूर्णांक bnx2x_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);

	/* Unload the driver, release IRQs */
	bnx2x_nic_unload(bp, UNLOAD_CLOSE, false);

	वापस 0;
पूर्ण

काष्ठा bnx2x_mcast_list_elem_group
अणु
	काष्ठा list_head mcast_group_link;
	काष्ठा bnx2x_mcast_list_elem mcast_elems[];
पूर्ण;

#घोषणा MCAST_ELEMS_PER_PG \
	((PAGE_SIZE - माप(काष्ठा bnx2x_mcast_list_elem_group)) / \
	माप(काष्ठा bnx2x_mcast_list_elem))

अटल व्योम bnx2x_मुक्त_mcast_macs_list(काष्ठा list_head *mcast_group_list)
अणु
	काष्ठा bnx2x_mcast_list_elem_group *current_mcast_group;

	जबतक (!list_empty(mcast_group_list)) अणु
		current_mcast_group = list_first_entry(mcast_group_list,
				      काष्ठा bnx2x_mcast_list_elem_group,
				      mcast_group_link);
		list_del(&current_mcast_group->mcast_group_link);
		मुक्त_page((अचिन्हित दीर्घ)current_mcast_group);
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_init_mcast_macs_list(काष्ठा bnx2x *bp,
				      काष्ठा bnx2x_mcast_ramrod_params *p,
				      काष्ठा list_head *mcast_group_list)
अणु
	काष्ठा bnx2x_mcast_list_elem *mc_mac;
	काष्ठा netdev_hw_addr *ha;
	काष्ठा bnx2x_mcast_list_elem_group *current_mcast_group = शून्य;
	पूर्णांक mc_count = netdev_mc_count(bp->dev);
	पूर्णांक offset = 0;

	INIT_LIST_HEAD(&p->mcast_list);
	netdev_क्रम_each_mc_addr(ha, bp->dev) अणु
		अगर (!offset) अणु
			current_mcast_group =
				(काष्ठा bnx2x_mcast_list_elem_group *)
				__get_मुक्त_page(GFP_ATOMIC);
			अगर (!current_mcast_group) अणु
				bnx2x_मुक्त_mcast_macs_list(mcast_group_list);
				BNX2X_ERR("Failed to allocate mc MAC list\n");
				वापस -ENOMEM;
			पूर्ण
			list_add(&current_mcast_group->mcast_group_link,
				 mcast_group_list);
		पूर्ण
		mc_mac = &current_mcast_group->mcast_elems[offset];
		mc_mac->mac = bnx2x_mc_addr(ha);
		list_add_tail(&mc_mac->link, &p->mcast_list);
		offset++;
		अगर (offset == MCAST_ELEMS_PER_PG)
			offset = 0;
	पूर्ण
	p->mcast_list_len = mc_count;
	वापस 0;
पूर्ण

/**
 * bnx2x_set_uc_list - configure a new unicast MACs list.
 *
 * @bp: driver handle
 *
 * We will use zero (0) as a MAC type क्रम these MACs.
 */
अटल पूर्णांक bnx2x_set_uc_list(काष्ठा bnx2x *bp)
अणु
	पूर्णांक rc;
	काष्ठा net_device *dev = bp->dev;
	काष्ठा netdev_hw_addr *ha;
	काष्ठा bnx2x_vlan_mac_obj *mac_obj = &bp->sp_objs->mac_obj;
	अचिन्हित दीर्घ ramrod_flags = 0;

	/* First schedule a cleanup up of old configuration */
	rc = bnx2x_del_all_macs(bp, mac_obj, BNX2X_UC_LIST_MAC, false);
	अगर (rc < 0) अणु
		BNX2X_ERR("Failed to schedule DELETE operations: %d\n", rc);
		वापस rc;
	पूर्ण

	netdev_क्रम_each_uc_addr(ha, dev) अणु
		rc = bnx2x_set_mac_one(bp, bnx2x_uc_addr(ha), mac_obj, true,
				       BNX2X_UC_LIST_MAC, &ramrod_flags);
		अगर (rc == -EEXIST) अणु
			DP(BNX2X_MSG_SP,
			   "Failed to schedule ADD operations: %d\n", rc);
			/* करो not treat adding same MAC as error */
			rc = 0;

		पूर्ण अन्यथा अगर (rc < 0) अणु

			BNX2X_ERR("Failed to schedule ADD operations: %d\n",
				  rc);
			वापस rc;
		पूर्ण
	पूर्ण

	/* Execute the pending commands */
	__set_bit(RAMROD_CONT, &ramrod_flags);
	वापस bnx2x_set_mac_one(bp, शून्य, mac_obj, false /* करोn't care */,
				 BNX2X_UC_LIST_MAC, &ramrod_flags);
पूर्ण

अटल पूर्णांक bnx2x_set_mc_list_e1x(काष्ठा bnx2x *bp)
अणु
	LIST_HEAD(mcast_group_list);
	काष्ठा net_device *dev = bp->dev;
	काष्ठा bnx2x_mcast_ramrod_params rparam = अणुशून्यपूर्ण;
	पूर्णांक rc = 0;

	rparam.mcast_obj = &bp->mcast_obj;

	/* first, clear all configured multicast MACs */
	rc = bnx2x_config_mcast(bp, &rparam, BNX2X_MCAST_CMD_DEL);
	अगर (rc < 0) अणु
		BNX2X_ERR("Failed to clear multicast configuration: %d\n", rc);
		वापस rc;
	पूर्ण

	/* then, configure a new MACs list */
	अगर (netdev_mc_count(dev)) अणु
		rc = bnx2x_init_mcast_macs_list(bp, &rparam, &mcast_group_list);
		अगर (rc)
			वापस rc;

		/* Now add the new MACs */
		rc = bnx2x_config_mcast(bp, &rparam,
					BNX2X_MCAST_CMD_ADD);
		अगर (rc < 0)
			BNX2X_ERR("Failed to set a new multicast configuration: %d\n",
				  rc);

		bnx2x_मुक्त_mcast_macs_list(&mcast_group_list);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_set_mc_list(काष्ठा bnx2x *bp)
अणु
	LIST_HEAD(mcast_group_list);
	काष्ठा bnx2x_mcast_ramrod_params rparam = अणुशून्यपूर्ण;
	काष्ठा net_device *dev = bp->dev;
	पूर्णांक rc = 0;

	/* On older adapters, we need to flush and re-add filters */
	अगर (CHIP_IS_E1x(bp))
		वापस bnx2x_set_mc_list_e1x(bp);

	rparam.mcast_obj = &bp->mcast_obj;

	अगर (netdev_mc_count(dev)) अणु
		rc = bnx2x_init_mcast_macs_list(bp, &rparam, &mcast_group_list);
		अगर (rc)
			वापस rc;

		/* Override the curently configured set of mc filters */
		rc = bnx2x_config_mcast(bp, &rparam,
					BNX2X_MCAST_CMD_SET);
		अगर (rc < 0)
			BNX2X_ERR("Failed to set a new multicast configuration: %d\n",
				  rc);

		bnx2x_मुक्त_mcast_macs_list(&mcast_group_list);
	पूर्ण अन्यथा अणु
		/* If no mc addresses are required, flush the configuration */
		rc = bnx2x_config_mcast(bp, &rparam, BNX2X_MCAST_CMD_DEL);
		अगर (rc < 0)
			BNX2X_ERR("Failed to clear multicast configuration %d\n",
				  rc);
	पूर्ण

	वापस rc;
पूर्ण

/* If bp->state is OPEN, should be called with netअगर_addr_lock_bh() */
अटल व्योम bnx2x_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);

	अगर (bp->state != BNX2X_STATE_OPEN) अणु
		DP(NETIF_MSG_IFUP, "state is %x, returning\n", bp->state);
		वापस;
	पूर्ण अन्यथा अणु
		/* Schedule an SP task to handle rest of change */
		bnx2x_schedule_sp_rtnl(bp, BNX2X_SP_RTNL_RX_MODE,
				       NETIF_MSG_IFUP);
	पूर्ण
पूर्ण

व्योम bnx2x_set_rx_mode_inner(काष्ठा bnx2x *bp)
अणु
	u32 rx_mode = BNX2X_RX_MODE_NORMAL;

	DP(NETIF_MSG_IFUP, "dev->flags = %x\n", bp->dev->flags);

	netअगर_addr_lock_bh(bp->dev);

	अगर (bp->dev->flags & IFF_PROMISC) अणु
		rx_mode = BNX2X_RX_MODE_PROMISC;
	पूर्ण अन्यथा अगर ((bp->dev->flags & IFF_ALLMULTI) ||
		   ((netdev_mc_count(bp->dev) > BNX2X_MAX_MULTICAST) &&
		    CHIP_IS_E1(bp))) अणु
		rx_mode = BNX2X_RX_MODE_ALLMULTI;
	पूर्ण अन्यथा अणु
		अगर (IS_PF(bp)) अणु
			/* some multicasts */
			अगर (bnx2x_set_mc_list(bp) < 0)
				rx_mode = BNX2X_RX_MODE_ALLMULTI;

			/* release bh lock, as bnx2x_set_uc_list might sleep */
			netअगर_addr_unlock_bh(bp->dev);
			अगर (bnx2x_set_uc_list(bp) < 0)
				rx_mode = BNX2X_RX_MODE_PROMISC;
			netअगर_addr_lock_bh(bp->dev);
		पूर्ण अन्यथा अणु
			/* configuring mcast to a vf involves sleeping (when we
			 * रुको क्रम the pf's response).
			 */
			bnx2x_schedule_sp_rtnl(bp,
					       BNX2X_SP_RTNL_VFPF_MCAST, 0);
		पूर्ण
	पूर्ण

	bp->rx_mode = rx_mode;
	/* handle ISCSI SD mode */
	अगर (IS_MF_ISCSI_ONLY(bp))
		bp->rx_mode = BNX2X_RX_MODE_NONE;

	/* Schedule the rx_mode command */
	अगर (test_bit(BNX2X_FILTER_RX_MODE_PENDING, &bp->sp_state)) अणु
		set_bit(BNX2X_FILTER_RX_MODE_SCHED, &bp->sp_state);
		netअगर_addr_unlock_bh(bp->dev);
		वापस;
	पूर्ण

	अगर (IS_PF(bp)) अणु
		bnx2x_set_storm_rx_mode(bp);
		netअगर_addr_unlock_bh(bp->dev);
	पूर्ण अन्यथा अणु
		/* VF will need to request the PF to make this change, and so
		 * the VF needs to release the bottom-half lock prior to the
		 * request (as it will likely require sleep on the VF side)
		 */
		netअगर_addr_unlock_bh(bp->dev);
		bnx2x_vfpf_storm_rx_mode(bp);
	पूर्ण
पूर्ण

/* called with rtnl_lock */
अटल पूर्णांक bnx2x_mdio_पढ़ो(काष्ठा net_device *netdev, पूर्णांक prtad,
			   पूर्णांक devad, u16 addr)
अणु
	काष्ठा bnx2x *bp = netdev_priv(netdev);
	u16 value;
	पूर्णांक rc;

	DP(NETIF_MSG_LINK, "mdio_read: prtad 0x%x, devad 0x%x, addr 0x%x\n",
	   prtad, devad, addr);

	/* The HW expects dअगरferent devad अगर CL22 is used */
	devad = (devad == MDIO_DEVAD_NONE) ? DEFAULT_PHY_DEV_ADDR : devad;

	bnx2x_acquire_phy_lock(bp);
	rc = bnx2x_phy_पढ़ो(&bp->link_params, prtad, devad, addr, &value);
	bnx2x_release_phy_lock(bp);
	DP(NETIF_MSG_LINK, "mdio_read_val 0x%x rc = 0x%x\n", value, rc);

	अगर (!rc)
		rc = value;
	वापस rc;
पूर्ण

/* called with rtnl_lock */
अटल पूर्णांक bnx2x_mdio_ग_लिखो(काष्ठा net_device *netdev, पूर्णांक prtad, पूर्णांक devad,
			    u16 addr, u16 value)
अणु
	काष्ठा bnx2x *bp = netdev_priv(netdev);
	पूर्णांक rc;

	DP(NETIF_MSG_LINK,
	   "mdio_write: prtad 0x%x, devad 0x%x, addr 0x%x, value 0x%x\n",
	   prtad, devad, addr, value);

	/* The HW expects dअगरferent devad अगर CL22 is used */
	devad = (devad == MDIO_DEVAD_NONE) ? DEFAULT_PHY_DEV_ADDR : devad;

	bnx2x_acquire_phy_lock(bp);
	rc = bnx2x_phy_ग_लिखो(&bp->link_params, prtad, devad, addr, value);
	bnx2x_release_phy_lock(bp);
	वापस rc;
पूर्ण

/* called with rtnl_lock */
अटल पूर्णांक bnx2x_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	काष्ठा mii_ioctl_data *mdio = अगर_mii(अगरr);

	अगर (!netअगर_running(dev))
		वापस -EAGAIN;

	चयन (cmd) अणु
	हाल SIOCSHWTSTAMP:
		वापस bnx2x_hwtstamp_ioctl(bp, अगरr);
	शेष:
		DP(NETIF_MSG_LINK, "ioctl: phy id 0x%x, reg 0x%x, val_in 0x%x\n",
		   mdio->phy_id, mdio->reg_num, mdio->val_in);
		वापस mdio_mii_ioctl(&bp->mdio, mdio, cmd);
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_validate_addr(काष्ठा net_device *dev)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);

	/* query the bulletin board क्रम mac address configured by the PF */
	अगर (IS_VF(bp))
		bnx2x_sample_bulletin(bp);

	अगर (!is_valid_ether_addr(dev->dev_addr)) अणु
		BNX2X_ERR("Non-valid Ethernet address\n");
		वापस -EADDRNOTAVAIL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_get_phys_port_id(काष्ठा net_device *netdev,
				  काष्ठा netdev_phys_item_id *ppid)
अणु
	काष्ठा bnx2x *bp = netdev_priv(netdev);

	अगर (!(bp->flags & HAS_PHYS_PORT_ID))
		वापस -EOPNOTSUPP;

	ppid->id_len = माप(bp->phys_port_id);
	स_नकल(ppid->id, bp->phys_port_id, ppid->id_len);

	वापस 0;
पूर्ण

अटल netdev_features_t bnx2x_features_check(काष्ठा sk_buff *skb,
					      काष्ठा net_device *dev,
					      netdev_features_t features)
अणु
	/*
	 * A skb with gso_size + header length > 9700 will cause a
	 * firmware panic. Drop GSO support.
	 *
	 * Eventually the upper layer should not pass these packets करोwn.
	 *
	 * For speed, अगर the gso_size is <= 9000, assume there will
	 * not be 700 bytes of headers and pass it through. Only करो a
	 * full (slow) validation अगर the gso_size is > 9000.
	 *
	 * (Due to the way SKB_BY_FRAGS works this will also करो a full
	 * validation in that हाल.)
	 */
	अगर (unlikely(skb_is_gso(skb) &&
		     (skb_shinfo(skb)->gso_size > 9000) &&
		     !skb_gso_validate_mac_len(skb, 9700)))
		features &= ~NETIF_F_GSO_MASK;

	features = vlan_features_check(skb, features);
	वापस vxlan_features_check(skb, features);
पूर्ण

अटल पूर्णांक __bnx2x_vlan_configure_vid(काष्ठा bnx2x *bp, u16 vid, bool add)
अणु
	पूर्णांक rc;

	अगर (IS_PF(bp)) अणु
		अचिन्हित दीर्घ ramrod_flags = 0;

		__set_bit(RAMROD_COMP_WAIT, &ramrod_flags);
		rc = bnx2x_set_vlan_one(bp, vid, &bp->sp_objs->vlan_obj,
					add, &ramrod_flags);
	पूर्ण अन्यथा अणु
		rc = bnx2x_vfpf_update_vlan(bp, vid, bp->fp->index, add);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_vlan_configure_vid_list(काष्ठा bnx2x *bp)
अणु
	काष्ठा bnx2x_vlan_entry *vlan;
	पूर्णांक rc = 0;

	/* Configure all non-configured entries */
	list_क्रम_each_entry(vlan, &bp->vlan_reg, link) अणु
		अगर (vlan->hw)
			जारी;

		अगर (bp->vlan_cnt >= bp->vlan_credit)
			वापस -ENOBUFS;

		rc = __bnx2x_vlan_configure_vid(bp, vlan->vid, true);
		अगर (rc) अणु
			BNX2X_ERR("Unable to config VLAN %d\n", vlan->vid);
			वापस rc;
		पूर्ण

		DP(NETIF_MSG_IFUP, "HW configured for VLAN %d\n", vlan->vid);
		vlan->hw = true;
		bp->vlan_cnt++;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bnx2x_vlan_configure(काष्ठा bnx2x *bp, bool set_rx_mode)
अणु
	bool need_accept_any_vlan;

	need_accept_any_vlan = !!bnx2x_vlan_configure_vid_list(bp);

	अगर (bp->accept_any_vlan != need_accept_any_vlan) अणु
		bp->accept_any_vlan = need_accept_any_vlan;
		DP(NETIF_MSG_IFUP, "Accept all VLAN %s\n",
		   bp->accept_any_vlan ? "raised" : "cleared");
		अगर (set_rx_mode) अणु
			अगर (IS_PF(bp))
				bnx2x_set_rx_mode_inner(bp);
			अन्यथा
				bnx2x_vfpf_storm_rx_mode(bp);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक bnx2x_vlan_reconfigure_vid(काष्ठा bnx2x *bp)
अणु
	/* Don't set rx mode here. Our caller will करो it. */
	bnx2x_vlan_configure(bp, false);

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_vlan_rx_add_vid(काष्ठा net_device *dev, __be16 proto, u16 vid)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	काष्ठा bnx2x_vlan_entry *vlan;

	DP(NETIF_MSG_IFUP, "Adding VLAN %d\n", vid);

	vlan = kदो_स्मृति(माप(*vlan), GFP_KERNEL);
	अगर (!vlan)
		वापस -ENOMEM;

	vlan->vid = vid;
	vlan->hw = false;
	list_add_tail(&vlan->link, &bp->vlan_reg);

	अगर (netअगर_running(dev))
		bnx2x_vlan_configure(bp, true);

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_vlan_rx_समाप्त_vid(काष्ठा net_device *dev, __be16 proto, u16 vid)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	काष्ठा bnx2x_vlan_entry *vlan;
	bool found = false;
	पूर्णांक rc = 0;

	DP(NETIF_MSG_IFUP, "Removing VLAN %d\n", vid);

	list_क्रम_each_entry(vlan, &bp->vlan_reg, link)
		अगर (vlan->vid == vid) अणु
			found = true;
			अवरोध;
		पूर्ण

	अगर (!found) अणु
		BNX2X_ERR("Unable to kill VLAN %d - not found\n", vid);
		वापस -EINVAL;
	पूर्ण

	अगर (netअगर_running(dev) && vlan->hw) अणु
		rc = __bnx2x_vlan_configure_vid(bp, vid, false);
		DP(NETIF_MSG_IFUP, "HW deconfigured for VLAN %d\n", vid);
		bp->vlan_cnt--;
	पूर्ण

	list_del(&vlan->link);
	kमुक्त(vlan);

	अगर (netअगर_running(dev))
		bnx2x_vlan_configure(bp, true);

	DP(NETIF_MSG_IFUP, "Removing VLAN result %d\n", rc);

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा net_device_ops bnx2x_netdev_ops = अणु
	.nकरो_खोलो		= bnx2x_खोलो,
	.nकरो_stop		= bnx2x_बंद,
	.nकरो_start_xmit		= bnx2x_start_xmit,
	.nकरो_select_queue	= bnx2x_select_queue,
	.nकरो_set_rx_mode	= bnx2x_set_rx_mode,
	.nकरो_set_mac_address	= bnx2x_change_mac_addr,
	.nकरो_validate_addr	= bnx2x_validate_addr,
	.nकरो_करो_ioctl		= bnx2x_ioctl,
	.nकरो_change_mtu		= bnx2x_change_mtu,
	.nकरो_fix_features	= bnx2x_fix_features,
	.nकरो_set_features	= bnx2x_set_features,
	.nकरो_tx_समयout		= bnx2x_tx_समयout,
	.nकरो_vlan_rx_add_vid	= bnx2x_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= bnx2x_vlan_rx_समाप्त_vid,
	.nकरो_setup_tc		= __bnx2x_setup_tc,
#अगर_घोषित CONFIG_BNX2X_SRIOV
	.nकरो_set_vf_mac		= bnx2x_set_vf_mac,
	.nकरो_set_vf_vlan	= bnx2x_set_vf_vlan,
	.nकरो_get_vf_config	= bnx2x_get_vf_config,
	.nकरो_set_vf_spoofchk	= bnx2x_set_vf_spoofchk,
#पूर्ण_अगर
#अगर_घोषित NETDEV_FCOE_WWNN
	.nकरो_fcoe_get_wwn	= bnx2x_fcoe_get_wwn,
#पूर्ण_अगर

	.nकरो_get_phys_port_id	= bnx2x_get_phys_port_id,
	.nकरो_set_vf_link_state	= bnx2x_set_vf_link_state,
	.nकरो_features_check	= bnx2x_features_check,
पूर्ण;

अटल पूर्णांक bnx2x_set_coherency_mask(काष्ठा bnx2x *bp)
अणु
	काष्ठा device *dev = &bp->pdev->dev;

	अगर (dma_set_mask_and_coherent(dev, DMA_BIT_MASK(64)) != 0 &&
	    dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32)) != 0) अणु
		dev_err(dev, "System does not support DMA, aborting\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bnx2x_disable_pcie_error_reporting(काष्ठा bnx2x *bp)
अणु
	अगर (bp->flags & AER_ENABLED) अणु
		pci_disable_pcie_error_reporting(bp->pdev);
		bp->flags &= ~AER_ENABLED;
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_init_dev(काष्ठा bnx2x *bp, काष्ठा pci_dev *pdev,
			  काष्ठा net_device *dev, अचिन्हित दीर्घ board_type)
अणु
	पूर्णांक rc;
	u32 pci_cfg_dword;
	bool chip_is_e1x = (board_type == BCM57710 ||
			    board_type == BCM57711 ||
			    board_type == BCM57711E);

	SET_NETDEV_DEV(dev, &pdev->dev);

	bp->dev = dev;
	bp->pdev = pdev;

	rc = pci_enable_device(pdev);
	अगर (rc) अणु
		dev_err(&bp->pdev->dev,
			"Cannot enable PCI device, aborting\n");
		जाओ err_out;
	पूर्ण

	अगर (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM)) अणु
		dev_err(&bp->pdev->dev,
			"Cannot find PCI device base address, aborting\n");
		rc = -ENODEV;
		जाओ err_out_disable;
	पूर्ण

	अगर (IS_PF(bp) && !(pci_resource_flags(pdev, 2) & IORESOURCE_MEM)) अणु
		dev_err(&bp->pdev->dev, "Cannot find second PCI device base address, aborting\n");
		rc = -ENODEV;
		जाओ err_out_disable;
	पूर्ण

	pci_पढ़ो_config_dword(pdev, PCICFG_REVISION_ID_OFFSET, &pci_cfg_dword);
	अगर ((pci_cfg_dword & PCICFG_REVESION_ID_MASK) ==
	    PCICFG_REVESION_ID_ERROR_VAL) अणु
		pr_err("PCI device error, probably due to fan failure, aborting\n");
		rc = -ENODEV;
		जाओ err_out_disable;
	पूर्ण

	अगर (atomic_पढ़ो(&pdev->enable_cnt) == 1) अणु
		rc = pci_request_regions(pdev, DRV_MODULE_NAME);
		अगर (rc) अणु
			dev_err(&bp->pdev->dev,
				"Cannot obtain PCI resources, aborting\n");
			जाओ err_out_disable;
		पूर्ण

		pci_set_master(pdev);
		pci_save_state(pdev);
	पूर्ण

	अगर (IS_PF(bp)) अणु
		अगर (!pdev->pm_cap) अणु
			dev_err(&bp->pdev->dev,
				"Cannot find power management capability, aborting\n");
			rc = -EIO;
			जाओ err_out_release;
		पूर्ण
	पूर्ण

	अगर (!pci_is_pcie(pdev)) अणु
		dev_err(&bp->pdev->dev, "Not PCI Express, aborting\n");
		rc = -EIO;
		जाओ err_out_release;
	पूर्ण

	rc = bnx2x_set_coherency_mask(bp);
	अगर (rc)
		जाओ err_out_release;

	dev->mem_start = pci_resource_start(pdev, 0);
	dev->base_addr = dev->mem_start;
	dev->mem_end = pci_resource_end(pdev, 0);

	dev->irq = pdev->irq;

	bp->regview = pci_ioremap_bar(pdev, 0);
	अगर (!bp->regview) अणु
		dev_err(&bp->pdev->dev,
			"Cannot map register space, aborting\n");
		rc = -ENOMEM;
		जाओ err_out_release;
	पूर्ण

	/* In E1/E1H use pci device function given by kernel.
	 * In E2/E3 पढ़ो physical function from ME रेजिस्टर since these chips
	 * support Physical Device Assignment where kernel BDF maybe arbitrary
	 * (depending on hypervisor).
	 */
	अगर (chip_is_e1x) अणु
		bp->pf_num = PCI_FUNC(pdev->devfn);
	पूर्ण अन्यथा अणु
		/* chip is E2/3*/
		pci_पढ़ो_config_dword(bp->pdev,
				      PCICFG_ME_REGISTER, &pci_cfg_dword);
		bp->pf_num = (u8)((pci_cfg_dword & ME_REG_ABS_PF_NUM) >>
				  ME_REG_ABS_PF_NUM_SHIFT);
	पूर्ण
	BNX2X_DEV_INFO("me reg PF num: %d\n", bp->pf_num);

	/* clean indirect addresses */
	pci_ग_लिखो_config_dword(bp->pdev, PCICFG_GRC_ADDRESS,
			       PCICFG_VENDOR_ID_OFFSET);

	/* Set PCIe reset type to fundamental क्रम EEH recovery */
	pdev->needs_freset = 1;

	/* AER (Advanced Error reporting) configuration */
	rc = pci_enable_pcie_error_reporting(pdev);
	अगर (!rc)
		bp->flags |= AER_ENABLED;
	अन्यथा
		BNX2X_DEV_INFO("Failed To configure PCIe AER [%d]\n", rc);

	/*
	 * Clean the following indirect addresses क्रम all functions since it
	 * is not used by the driver.
	 */
	अगर (IS_PF(bp)) अणु
		REG_WR(bp, PXP2_REG_PGL_ADDR_88_F0, 0);
		REG_WR(bp, PXP2_REG_PGL_ADDR_8C_F0, 0);
		REG_WR(bp, PXP2_REG_PGL_ADDR_90_F0, 0);
		REG_WR(bp, PXP2_REG_PGL_ADDR_94_F0, 0);

		अगर (chip_is_e1x) अणु
			REG_WR(bp, PXP2_REG_PGL_ADDR_88_F1, 0);
			REG_WR(bp, PXP2_REG_PGL_ADDR_8C_F1, 0);
			REG_WR(bp, PXP2_REG_PGL_ADDR_90_F1, 0);
			REG_WR(bp, PXP2_REG_PGL_ADDR_94_F1, 0);
		पूर्ण

		/* Enable पूर्णांकernal target-पढ़ो (in हाल we are probed after PF
		 * FLR). Must be करोne prior to any BAR पढ़ो access. Only क्रम
		 * 57712 and up
		 */
		अगर (!chip_is_e1x)
			REG_WR(bp,
			       PGLUE_B_REG_INTERNAL_PFID_ENABLE_TARGET_READ, 1);
	पूर्ण

	dev->watchकरोg_समयo = TX_TIMEOUT;

	dev->netdev_ops = &bnx2x_netdev_ops;
	bnx2x_set_ethtool_ops(bp, dev);

	dev->priv_flags |= IFF_UNICAST_FLT;

	dev->hw_features = NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
		NETIF_F_TSO | NETIF_F_TSO_ECN | NETIF_F_TSO6 |
		NETIF_F_RXCSUM | NETIF_F_LRO | NETIF_F_GRO | NETIF_F_GRO_HW |
		NETIF_F_RXHASH | NETIF_F_HW_VLAN_CTAG_TX;
	अगर (!chip_is_e1x) अणु
		dev->hw_features |= NETIF_F_GSO_GRE | NETIF_F_GSO_GRE_CSUM |
				    NETIF_F_GSO_IPXIP4 |
				    NETIF_F_GSO_UDP_TUNNEL |
				    NETIF_F_GSO_UDP_TUNNEL_CSUM |
				    NETIF_F_GSO_PARTIAL;

		dev->hw_enc_features =
			NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM | NETIF_F_SG |
			NETIF_F_TSO | NETIF_F_TSO_ECN | NETIF_F_TSO6 |
			NETIF_F_GSO_IPXIP4 |
			NETIF_F_GSO_GRE | NETIF_F_GSO_GRE_CSUM |
			NETIF_F_GSO_UDP_TUNNEL | NETIF_F_GSO_UDP_TUNNEL_CSUM |
			NETIF_F_GSO_PARTIAL;

		dev->gso_partial_features = NETIF_F_GSO_GRE_CSUM |
					    NETIF_F_GSO_UDP_TUNNEL_CSUM;

		अगर (IS_PF(bp))
			dev->udp_tunnel_nic_info = &bnx2x_udp_tunnels;
	पूर्ण

	dev->vlan_features = NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
		NETIF_F_TSO | NETIF_F_TSO_ECN | NETIF_F_TSO6 | NETIF_F_HIGHDMA;

	अगर (IS_PF(bp)) अणु
		अगर (chip_is_e1x)
			bp->accept_any_vlan = true;
		अन्यथा
			dev->hw_features |= NETIF_F_HW_VLAN_CTAG_FILTER;
	पूर्ण
	/* For VF we'll know whether to enable VLAN filtering after
	 * getting a response to CHANNEL_TLV_ACQUIRE from PF.
	 */

	dev->features |= dev->hw_features | NETIF_F_HW_VLAN_CTAG_RX;
	dev->features |= NETIF_F_HIGHDMA;
	अगर (dev->features & NETIF_F_LRO)
		dev->features &= ~NETIF_F_GRO_HW;

	/* Add Loopback capability to the device */
	dev->hw_features |= NETIF_F_LOOPBACK;

#अगर_घोषित BCM_DCBNL
	dev->dcbnl_ops = &bnx2x_dcbnl_ops;
#पूर्ण_अगर

	/* MTU range, 46 - 9600 */
	dev->min_mtu = ETH_MIN_PACKET_SIZE;
	dev->max_mtu = ETH_MAX_JUMBO_PACKET_SIZE;

	/* get_port_hwinfo() will set prtad and mmds properly */
	bp->mdio.prtad = MDIO_PRTAD_NONE;
	bp->mdio.mmds = 0;
	bp->mdio.mode_support = MDIO_SUPPORTS_C45 | MDIO_EMULATE_C22;
	bp->mdio.dev = dev;
	bp->mdio.mdio_पढ़ो = bnx2x_mdio_पढ़ो;
	bp->mdio.mdio_ग_लिखो = bnx2x_mdio_ग_लिखो;

	वापस 0;

err_out_release:
	अगर (atomic_पढ़ो(&pdev->enable_cnt) == 1)
		pci_release_regions(pdev);

err_out_disable:
	pci_disable_device(pdev);

err_out:
	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_check_firmware(काष्ठा bnx2x *bp)
अणु
	स्थिर काष्ठा firmware *firmware = bp->firmware;
	काष्ठा bnx2x_fw_file_hdr *fw_hdr;
	काष्ठा bnx2x_fw_file_section *sections;
	u32 offset, len, num_ops;
	__be16 *ops_offsets;
	पूर्णांक i;
	स्थिर u8 *fw_ver;

	अगर (firmware->size < माप(काष्ठा bnx2x_fw_file_hdr)) अणु
		BNX2X_ERR("Wrong FW size\n");
		वापस -EINVAL;
	पूर्ण

	fw_hdr = (काष्ठा bnx2x_fw_file_hdr *)firmware->data;
	sections = (काष्ठा bnx2x_fw_file_section *)fw_hdr;

	/* Make sure none of the offsets and sizes make us पढ़ो beyond
	 * the end of the firmware data */
	क्रम (i = 0; i < माप(*fw_hdr) / माप(*sections); i++) अणु
		offset = be32_to_cpu(sections[i].offset);
		len = be32_to_cpu(sections[i].len);
		अगर (offset + len > firmware->size) अणु
			BNX2X_ERR("Section %d length is out of bounds\n", i);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Likewise क्रम the init_ops offsets */
	offset = be32_to_cpu(fw_hdr->init_ops_offsets.offset);
	ops_offsets = (__क्रमce __be16 *)(firmware->data + offset);
	num_ops = be32_to_cpu(fw_hdr->init_ops.len) / माप(काष्ठा raw_op);

	क्रम (i = 0; i < be32_to_cpu(fw_hdr->init_ops_offsets.len) / 2; i++) अणु
		अगर (be16_to_cpu(ops_offsets[i]) > num_ops) अणु
			BNX2X_ERR("Section offset %d is out of bounds\n", i);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Check FW version */
	offset = be32_to_cpu(fw_hdr->fw_version.offset);
	fw_ver = firmware->data + offset;
	अगर ((fw_ver[0] != BCM_5710_FW_MAJOR_VERSION) ||
	    (fw_ver[1] != BCM_5710_FW_MINOR_VERSION) ||
	    (fw_ver[2] != BCM_5710_FW_REVISION_VERSION) ||
	    (fw_ver[3] != BCM_5710_FW_ENGINEERING_VERSION)) अणु
		BNX2X_ERR("Bad FW version:%d.%d.%d.%d. Should be %d.%d.%d.%d\n",
		       fw_ver[0], fw_ver[1], fw_ver[2], fw_ver[3],
		       BCM_5710_FW_MAJOR_VERSION,
		       BCM_5710_FW_MINOR_VERSION,
		       BCM_5710_FW_REVISION_VERSION,
		       BCM_5710_FW_ENGINEERING_VERSION);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम be32_to_cpu_n(स्थिर u8 *_source, u8 *_target, u32 n)
अणु
	स्थिर __be32 *source = (स्थिर __be32 *)_source;
	u32 *target = (u32 *)_target;
	u32 i;

	क्रम (i = 0; i < n/4; i++)
		target[i] = be32_to_cpu(source[i]);
पूर्ण

/*
   Ops array is stored in the following क्रमmat:
   अणुop(8bit), offset(24bit, big endian), data(32bit, big endian)पूर्ण
 */
अटल व्योम bnx2x_prep_ops(स्थिर u8 *_source, u8 *_target, u32 n)
अणु
	स्थिर __be32 *source = (स्थिर __be32 *)_source;
	काष्ठा raw_op *target = (काष्ठा raw_op *)_target;
	u32 i, j, पंचांगp;

	क्रम (i = 0, j = 0; i < n/8; i++, j += 2) अणु
		पंचांगp = be32_to_cpu(source[j]);
		target[i].op = (पंचांगp >> 24) & 0xff;
		target[i].offset = पंचांगp & 0xffffff;
		target[i].raw_data = be32_to_cpu(source[j + 1]);
	पूर्ण
पूर्ण

/* IRO array is stored in the following क्रमmat:
 * अणुbase(24bit), m1(16bit), m2(16bit), m3(16bit), size(16bit) पूर्ण
 */
अटल व्योम bnx2x_prep_iro(स्थिर u8 *_source, u8 *_target, u32 n)
अणु
	स्थिर __be32 *source = (स्थिर __be32 *)_source;
	काष्ठा iro *target = (काष्ठा iro *)_target;
	u32 i, j, पंचांगp;

	क्रम (i = 0, j = 0; i < n/माप(काष्ठा iro); i++) अणु
		target[i].base = be32_to_cpu(source[j]);
		j++;
		पंचांगp = be32_to_cpu(source[j]);
		target[i].m1 = (पंचांगp >> 16) & 0xffff;
		target[i].m2 = पंचांगp & 0xffff;
		j++;
		पंचांगp = be32_to_cpu(source[j]);
		target[i].m3 = (पंचांगp >> 16) & 0xffff;
		target[i].size = पंचांगp & 0xffff;
		j++;
	पूर्ण
पूर्ण

अटल व्योम be16_to_cpu_n(स्थिर u8 *_source, u8 *_target, u32 n)
अणु
	स्थिर __be16 *source = (स्थिर __be16 *)_source;
	u16 *target = (u16 *)_target;
	u32 i;

	क्रम (i = 0; i < n/2; i++)
		target[i] = be16_to_cpu(source[i]);
पूर्ण

#घोषणा BNX2X_ALLOC_AND_SET(arr, lbl, func)				\
करो अणु									\
	u32 len = be32_to_cpu(fw_hdr->arr.len);				\
	bp->arr = kदो_स्मृति(len, GFP_KERNEL);				\
	अगर (!bp->arr)							\
		जाओ lbl;						\
	func(bp->firmware->data + be32_to_cpu(fw_hdr->arr.offset),	\
	     (u8 *)bp->arr, len);					\
पूर्ण जबतक (0)

अटल पूर्णांक bnx2x_init_firmware(काष्ठा bnx2x *bp)
अणु
	स्थिर अक्षर *fw_file_name;
	काष्ठा bnx2x_fw_file_hdr *fw_hdr;
	पूर्णांक rc;

	अगर (bp->firmware)
		वापस 0;

	अगर (CHIP_IS_E1(bp))
		fw_file_name = FW_खाता_NAME_E1;
	अन्यथा अगर (CHIP_IS_E1H(bp))
		fw_file_name = FW_खाता_NAME_E1H;
	अन्यथा अगर (!CHIP_IS_E1x(bp))
		fw_file_name = FW_खाता_NAME_E2;
	अन्यथा अणु
		BNX2X_ERR("Unsupported chip revision\n");
		वापस -EINVAL;
	पूर्ण
	BNX2X_DEV_INFO("Loading %s\n", fw_file_name);

	rc = request_firmware(&bp->firmware, fw_file_name, &bp->pdev->dev);
	अगर (rc) अणु
		BNX2X_ERR("Can't load firmware file %s\n",
			  fw_file_name);
		जाओ request_firmware_निकास;
	पूर्ण

	rc = bnx2x_check_firmware(bp);
	अगर (rc) अणु
		BNX2X_ERR("Corrupt firmware file %s\n", fw_file_name);
		जाओ request_firmware_निकास;
	पूर्ण

	fw_hdr = (काष्ठा bnx2x_fw_file_hdr *)bp->firmware->data;

	/* Initialize the poपूर्णांकers to the init arrays */
	/* Blob */
	rc = -ENOMEM;
	BNX2X_ALLOC_AND_SET(init_data, request_firmware_निकास, be32_to_cpu_n);

	/* Opcodes */
	BNX2X_ALLOC_AND_SET(init_ops, init_ops_alloc_err, bnx2x_prep_ops);

	/* Offsets */
	BNX2X_ALLOC_AND_SET(init_ops_offsets, init_offsets_alloc_err,
			    be16_to_cpu_n);

	/* STORMs firmware */
	INIT_TSEM_INT_TABLE_DATA(bp) = bp->firmware->data +
			be32_to_cpu(fw_hdr->tsem_पूर्णांक_table_data.offset);
	INIT_TSEM_PRAM_DATA(bp)      = bp->firmware->data +
			be32_to_cpu(fw_hdr->tsem_pram_data.offset);
	INIT_USEM_INT_TABLE_DATA(bp) = bp->firmware->data +
			be32_to_cpu(fw_hdr->usem_पूर्णांक_table_data.offset);
	INIT_USEM_PRAM_DATA(bp)      = bp->firmware->data +
			be32_to_cpu(fw_hdr->usem_pram_data.offset);
	INIT_XSEM_INT_TABLE_DATA(bp) = bp->firmware->data +
			be32_to_cpu(fw_hdr->xsem_पूर्णांक_table_data.offset);
	INIT_XSEM_PRAM_DATA(bp)      = bp->firmware->data +
			be32_to_cpu(fw_hdr->xsem_pram_data.offset);
	INIT_CSEM_INT_TABLE_DATA(bp) = bp->firmware->data +
			be32_to_cpu(fw_hdr->csem_पूर्णांक_table_data.offset);
	INIT_CSEM_PRAM_DATA(bp)      = bp->firmware->data +
			be32_to_cpu(fw_hdr->csem_pram_data.offset);
	/* IRO */
	BNX2X_ALLOC_AND_SET(iro_arr, iro_alloc_err, bnx2x_prep_iro);

	वापस 0;

iro_alloc_err:
	kमुक्त(bp->init_ops_offsets);
init_offsets_alloc_err:
	kमुक्त(bp->init_ops);
init_ops_alloc_err:
	kमुक्त(bp->init_data);
request_firmware_निकास:
	release_firmware(bp->firmware);
	bp->firmware = शून्य;

	वापस rc;
पूर्ण

अटल व्योम bnx2x_release_firmware(काष्ठा bnx2x *bp)
अणु
	kमुक्त(bp->init_ops_offsets);
	kमुक्त(bp->init_ops);
	kमुक्त(bp->init_data);
	release_firmware(bp->firmware);
	bp->firmware = शून्य;
पूर्ण

अटल काष्ठा bnx2x_func_sp_drv_ops bnx2x_func_sp_drv = अणु
	.init_hw_cmn_chip = bnx2x_init_hw_common_chip,
	.init_hw_cmn      = bnx2x_init_hw_common,
	.init_hw_port     = bnx2x_init_hw_port,
	.init_hw_func     = bnx2x_init_hw_func,

	.reset_hw_cmn     = bnx2x_reset_common,
	.reset_hw_port    = bnx2x_reset_port,
	.reset_hw_func    = bnx2x_reset_func,

	.gunzip_init      = bnx2x_gunzip_init,
	.gunzip_end       = bnx2x_gunzip_end,

	.init_fw          = bnx2x_init_firmware,
	.release_fw       = bnx2x_release_firmware,
पूर्ण;

व्योम bnx2x__init_func_obj(काष्ठा bnx2x *bp)
अणु
	/* Prepare DMAE related driver resources */
	bnx2x_setup_dmae(bp);

	bnx2x_init_func_obj(bp, &bp->func_obj,
			    bnx2x_sp(bp, func_rdata),
			    bnx2x_sp_mapping(bp, func_rdata),
			    bnx2x_sp(bp, func_afex_rdata),
			    bnx2x_sp_mapping(bp, func_afex_rdata),
			    &bnx2x_func_sp_drv);
पूर्ण

/* must be called after sriov-enable */
अटल पूर्णांक bnx2x_set_qm_cid_count(काष्ठा bnx2x *bp)
अणु
	पूर्णांक cid_count = BNX2X_L2_MAX_CID(bp);

	अगर (IS_SRIOV(bp))
		cid_count += BNX2X_VF_CIDS;

	अगर (CNIC_SUPPORT(bp))
		cid_count += CNIC_CID_MAX;

	वापस roundup(cid_count, QM_CID_ROUND);
पूर्ण

/**
 * bnx2x_get_num_none_def_sbs - वापस the number of none शेष SBs
 * @pdev: pci device
 * @cnic_cnt: count
 *
 */
अटल पूर्णांक bnx2x_get_num_non_def_sbs(काष्ठा pci_dev *pdev, पूर्णांक cnic_cnt)
अणु
	पूर्णांक index;
	u16 control = 0;

	/*
	 * If MSI-X is not supported - वापस number of SBs needed to support
	 * one fast path queue: one FP queue + SB क्रम CNIC
	 */
	अगर (!pdev->msix_cap) अणु
		dev_info(&pdev->dev, "no msix capability found\n");
		वापस 1 + cnic_cnt;
	पूर्ण
	dev_info(&pdev->dev, "msix capability found\n");

	/*
	 * The value in the PCI configuration space is the index of the last
	 * entry, namely one less than the actual size of the table, which is
	 * exactly what we want to वापस from this function: number of all SBs
	 * without the शेष SB.
	 * For VFs there is no शेष SB, then we वापस (index+1).
	 */
	pci_पढ़ो_config_word(pdev, pdev->msix_cap + PCI_MSIX_FLAGS, &control);

	index = control & PCI_MSIX_FLAGS_QSIZE;

	वापस index;
पूर्ण

अटल पूर्णांक set_max_cos_est(पूर्णांक chip_id)
अणु
	चयन (chip_id) अणु
	हाल BCM57710:
	हाल BCM57711:
	हाल BCM57711E:
		वापस BNX2X_MULTI_TX_COS_E1X;
	हाल BCM57712:
	हाल BCM57712_MF:
		वापस BNX2X_MULTI_TX_COS_E2_E3A0;
	हाल BCM57800:
	हाल BCM57800_MF:
	हाल BCM57810:
	हाल BCM57810_MF:
	हाल BCM57840_4_10:
	हाल BCM57840_2_20:
	हाल BCM57840_O:
	हाल BCM57840_MFO:
	हाल BCM57840_MF:
	हाल BCM57811:
	हाल BCM57811_MF:
		वापस BNX2X_MULTI_TX_COS_E3B0;
	हाल BCM57712_VF:
	हाल BCM57800_VF:
	हाल BCM57810_VF:
	हाल BCM57840_VF:
	हाल BCM57811_VF:
		वापस 1;
	शेष:
		pr_err("Unknown board_type (%d), aborting\n", chip_id);
		वापस -ENODEV;
	पूर्ण
पूर्ण

अटल पूर्णांक set_is_vf(पूर्णांक chip_id)
अणु
	चयन (chip_id) अणु
	हाल BCM57712_VF:
	हाल BCM57800_VF:
	हाल BCM57810_VF:
	हाल BCM57840_VF:
	हाल BCM57811_VF:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/* nig_tsgen रेजिस्टरs relative address */
#घोषणा tsgen_ctrl 0x0
#घोषणा tsgen_मुक्तcount 0x10
#घोषणा tsgen_synस_समय_t0 0x20
#घोषणा tsgen_offset_t0 0x28
#घोषणा tsgen_drअगरt_t0 0x30
#घोषणा tsgen_synस_समय_t1 0x58
#घोषणा tsgen_offset_t1 0x60
#घोषणा tsgen_drअगरt_t1 0x68

/* FW workaround क्रम setting drअगरt */
अटल पूर्णांक bnx2x_send_update_drअगरt_ramrod(काष्ठा bnx2x *bp, पूर्णांक drअगरt_dir,
					  पूर्णांक best_val, पूर्णांक best_period)
अणु
	काष्ठा bnx2x_func_state_params func_params = अणुशून्यपूर्ण;
	काष्ठा bnx2x_func_set_बारync_params *set_बारync_params =
		&func_params.params.set_बारync;

	/* Prepare parameters क्रम function state transitions */
	__set_bit(RAMROD_COMP_WAIT, &func_params.ramrod_flags);
	__set_bit(RAMROD_RETRY, &func_params.ramrod_flags);

	func_params.f_obj = &bp->func_obj;
	func_params.cmd = BNX2X_F_CMD_SET_TIMESYNC;

	/* Function parameters */
	set_बारync_params->drअगरt_adjust_cmd = TS_DRIFT_ADJUST_SET;
	set_बारync_params->offset_cmd = TS_OFFSET_KEEP;
	set_बारync_params->add_sub_drअगरt_adjust_value =
		drअगरt_dir ? TS_ADD_VALUE : TS_SUB_VALUE;
	set_बारync_params->drअगरt_adjust_value = best_val;
	set_बारync_params->drअगरt_adjust_period = best_period;

	वापस bnx2x_func_state_change(bp, &func_params);
पूर्ण

अटल पूर्णांक bnx2x_ptp_adjfreq(काष्ठा ptp_घड़ी_info *ptp, s32 ppb)
अणु
	काष्ठा bnx2x *bp = container_of(ptp, काष्ठा bnx2x, ptp_घड़ी_info);
	पूर्णांक rc;
	पूर्णांक drअगरt_dir = 1;
	पूर्णांक val, period, period1, period2, dअगर, dअगर1, dअगर2;
	पूर्णांक best_dअगर = BNX2X_MAX_PHC_DRIFT, best_period = 0, best_val = 0;

	DP(BNX2X_MSG_PTP, "PTP adjfreq called, ppb = %d\n", ppb);

	अगर (!netअगर_running(bp->dev)) अणु
		DP(BNX2X_MSG_PTP,
		   "PTP adjfreq called while the interface is down\n");
		वापस -ENETDOWN;
	पूर्ण

	अगर (ppb < 0) अणु
		ppb = -ppb;
		drअगरt_dir = 0;
	पूर्ण

	अगर (ppb == 0) अणु
		best_val = 1;
		best_period = 0x1FFFFFF;
	पूर्ण अन्यथा अगर (ppb >= BNX2X_MAX_PHC_DRIFT) अणु
		best_val = 31;
		best_period = 1;
	पूर्ण अन्यथा अणु
		/* Changed not to allow val = 8, 16, 24 as these values
		 * are not supported in workaround.
		 */
		क्रम (val = 0; val <= 31; val++) अणु
			अगर ((val & 0x7) == 0)
				जारी;
			period1 = val * 1000000 / ppb;
			period2 = period1 + 1;
			अगर (period1 != 0)
				dअगर1 = ppb - (val * 1000000 / period1);
			अन्यथा
				dअगर1 = BNX2X_MAX_PHC_DRIFT;
			अगर (dअगर1 < 0)
				dअगर1 = -dअगर1;
			dअगर2 = ppb - (val * 1000000 / period2);
			अगर (dअगर2 < 0)
				dअगर2 = -dअगर2;
			dअगर = (dअगर1 < dअगर2) ? dअगर1 : dअगर2;
			period = (dअगर1 < dअगर2) ? period1 : period2;
			अगर (dअगर < best_dअगर) अणु
				best_dअगर = dअगर;
				best_val = val;
				best_period = period;
			पूर्ण
		पूर्ण
	पूर्ण

	rc = bnx2x_send_update_drअगरt_ramrod(bp, drअगरt_dir, best_val,
					    best_period);
	अगर (rc) अणु
		BNX2X_ERR("Failed to set drift\n");
		वापस -EFAULT;
	पूर्ण

	DP(BNX2X_MSG_PTP, "Configured val = %d, period = %d\n", best_val,
	   best_period);

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_ptp_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	काष्ठा bnx2x *bp = container_of(ptp, काष्ठा bnx2x, ptp_घड़ी_info);

	अगर (!netअगर_running(bp->dev)) अणु
		DP(BNX2X_MSG_PTP,
		   "PTP adjtime called while the interface is down\n");
		वापस -ENETDOWN;
	पूर्ण

	DP(BNX2X_MSG_PTP, "PTP adjtime called, delta = %llx\n", delta);

	समयcounter_adjसमय(&bp->समयcounter, delta);

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_ptp_समय_लो(काष्ठा ptp_घड़ी_info *ptp, काष्ठा बारpec64 *ts)
अणु
	काष्ठा bnx2x *bp = container_of(ptp, काष्ठा bnx2x, ptp_घड़ी_info);
	u64 ns;

	अगर (!netअगर_running(bp->dev)) अणु
		DP(BNX2X_MSG_PTP,
		   "PTP gettime called while the interface is down\n");
		वापस -ENETDOWN;
	पूर्ण

	ns = समयcounter_पढ़ो(&bp->समयcounter);

	DP(BNX2X_MSG_PTP, "PTP gettime called, ns = %llu\n", ns);

	*ts = ns_to_बारpec64(ns);

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_ptp_समय_रखो(काष्ठा ptp_घड़ी_info *ptp,
			     स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा bnx2x *bp = container_of(ptp, काष्ठा bnx2x, ptp_घड़ी_info);
	u64 ns;

	अगर (!netअगर_running(bp->dev)) अणु
		DP(BNX2X_MSG_PTP,
		   "PTP settime called while the interface is down\n");
		वापस -ENETDOWN;
	पूर्ण

	ns = बारpec64_to_ns(ts);

	DP(BNX2X_MSG_PTP, "PTP settime called, ns = %llu\n", ns);

	/* Re-init the समयcounter */
	समयcounter_init(&bp->समयcounter, &bp->cyclecounter, ns);

	वापस 0;
पूर्ण

/* Enable (or disable) ancillary features of the phc subप्रणाली */
अटल पूर्णांक bnx2x_ptp_enable(काष्ठा ptp_घड़ी_info *ptp,
			    काष्ठा ptp_घड़ी_request *rq, पूर्णांक on)
अणु
	काष्ठा bnx2x *bp = container_of(ptp, काष्ठा bnx2x, ptp_घड़ी_info);

	BNX2X_ERR("PHC ancillary features are not supported\n");
	वापस -ENOTSUPP;
पूर्ण

व्योम bnx2x_रेजिस्टर_phc(काष्ठा bnx2x *bp)
अणु
	/* Fill the ptp_घड़ी_info काष्ठा and रेजिस्टर PTP घड़ी*/
	bp->ptp_घड़ी_info.owner = THIS_MODULE;
	snम_लिखो(bp->ptp_घड़ी_info.name, 16, "%s", bp->dev->name);
	bp->ptp_घड़ी_info.max_adj = BNX2X_MAX_PHC_DRIFT; /* In PPB */
	bp->ptp_घड़ी_info.n_alarm = 0;
	bp->ptp_घड़ी_info.n_ext_ts = 0;
	bp->ptp_घड़ी_info.n_per_out = 0;
	bp->ptp_घड़ी_info.pps = 0;
	bp->ptp_घड़ी_info.adjfreq = bnx2x_ptp_adjfreq;
	bp->ptp_घड़ी_info.adjसमय = bnx2x_ptp_adjसमय;
	bp->ptp_घड़ी_info.समय_लो64 = bnx2x_ptp_समय_लो;
	bp->ptp_घड़ी_info.समय_रखो64 = bnx2x_ptp_समय_रखो;
	bp->ptp_घड़ी_info.enable = bnx2x_ptp_enable;

	bp->ptp_घड़ी = ptp_घड़ी_रेजिस्टर(&bp->ptp_घड़ी_info, &bp->pdev->dev);
	अगर (IS_ERR(bp->ptp_घड़ी)) अणु
		bp->ptp_घड़ी = शून्य;
		BNX2X_ERR("PTP clock registration failed\n");
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_init_one(काष्ठा pci_dev *pdev,
				    स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *dev = शून्य;
	काष्ठा bnx2x *bp;
	पूर्णांक rc, max_non_def_sbs;
	पूर्णांक rx_count, tx_count, rss_count, करोorbell_size;
	पूर्णांक max_cos_est;
	bool is_vf;
	पूर्णांक cnic_cnt;

	/* Management FW 'remembers' living पूर्णांकerfaces. Allow it some समय
	 * to क्रमget previously living पूर्णांकerfaces, allowing a proper re-load.
	 */
	अगर (is_kdump_kernel()) अणु
		kसमय_प्रकार now = kसमय_get_bootसमय();
		kसमय_प्रकार fw_पढ़ोy_समय = kसमय_set(5, 0);

		अगर (kसमय_beक्रमe(now, fw_पढ़ोy_समय))
			msleep(kसमय_ms_delta(fw_पढ़ोy_समय, now));
	पूर्ण

	/* An estimated maximum supported CoS number according to the chip
	 * version.
	 * We will try to roughly estimate the maximum number of CoSes this chip
	 * may support in order to minimize the memory allocated क्रम Tx
	 * netdev_queue's. This number will be accurately calculated during the
	 * initialization of bp->max_cos based on the chip versions AND chip
	 * revision in the bnx2x_init_bp().
	 */
	max_cos_est = set_max_cos_est(ent->driver_data);
	अगर (max_cos_est < 0)
		वापस max_cos_est;
	is_vf = set_is_vf(ent->driver_data);
	cnic_cnt = is_vf ? 0 : 1;

	max_non_def_sbs = bnx2x_get_num_non_def_sbs(pdev, cnic_cnt);

	/* add another SB क्रम VF as it has no शेष SB */
	max_non_def_sbs += is_vf ? 1 : 0;

	/* Maximum number of RSS queues: one IGU SB goes to CNIC */
	rss_count = max_non_def_sbs - cnic_cnt;

	अगर (rss_count < 1)
		वापस -EINVAL;

	/* Maximum number of netdev Rx queues: RSS + FCoE L2 */
	rx_count = rss_count + cnic_cnt;

	/* Maximum number of netdev Tx queues:
	 * Maximum TSS queues * Maximum supported number of CoS  + FCoE L2
	 */
	tx_count = rss_count * max_cos_est + cnic_cnt;

	/* dev zeroed in init_etherdev */
	dev = alloc_etherdev_mqs(माप(*bp), tx_count, rx_count);
	अगर (!dev)
		वापस -ENOMEM;

	bp = netdev_priv(dev);

	bp->flags = 0;
	अगर (is_vf)
		bp->flags |= IS_VF_FLAG;

	bp->igu_sb_cnt = max_non_def_sbs;
	bp->igu_base_addr = IS_VF(bp) ? PXP_VF_ADDR_IGU_START : BAR_IGU_INTMEM;
	bp->msg_enable = debug;
	bp->cnic_support = cnic_cnt;
	bp->cnic_probe = bnx2x_cnic_probe;

	pci_set_drvdata(pdev, dev);

	rc = bnx2x_init_dev(bp, pdev, dev, ent->driver_data);
	अगर (rc < 0) अणु
		मुक्त_netdev(dev);
		वापस rc;
	पूर्ण

	BNX2X_DEV_INFO("This is a %s function\n",
		       IS_PF(bp) ? "physical" : "virtual");
	BNX2X_DEV_INFO("Cnic support is %s\n", CNIC_SUPPORT(bp) ? "on" : "off");
	BNX2X_DEV_INFO("Max num of status blocks %d\n", max_non_def_sbs);
	BNX2X_DEV_INFO("Allocated netdev with %d tx and %d rx queues\n",
		       tx_count, rx_count);

	rc = bnx2x_init_bp(bp);
	अगर (rc)
		जाओ init_one_निकास;

	/* Map करोorbells here as we need the real value of bp->max_cos which
	 * is initialized in bnx2x_init_bp() to determine the number of
	 * l2 connections.
	 */
	अगर (IS_VF(bp)) अणु
		bp->करोorbells = bnx2x_vf_करोorbells(bp);
		rc = bnx2x_vf_pci_alloc(bp);
		अगर (rc)
			जाओ init_one_मुक्तmem;
	पूर्ण अन्यथा अणु
		करोorbell_size = BNX2X_L2_MAX_CID(bp) * (1 << BNX2X_DB_SHIFT);
		अगर (करोorbell_size > pci_resource_len(pdev, 2)) अणु
			dev_err(&bp->pdev->dev,
				"Cannot map doorbells, bar size too small, aborting\n");
			rc = -ENOMEM;
			जाओ init_one_मुक्तmem;
		पूर्ण
		bp->करोorbells = ioremap(pci_resource_start(pdev, 2),
						करोorbell_size);
	पूर्ण
	अगर (!bp->करोorbells) अणु
		dev_err(&bp->pdev->dev,
			"Cannot map doorbell space, aborting\n");
		rc = -ENOMEM;
		जाओ init_one_मुक्तmem;
	पूर्ण

	अगर (IS_VF(bp)) अणु
		rc = bnx2x_vfpf_acquire(bp, tx_count, rx_count);
		अगर (rc)
			जाओ init_one_मुक्तmem;

#अगर_घोषित CONFIG_BNX2X_SRIOV
		/* VF with OLD Hypervisor or old PF करो not support filtering */
		अगर (bp->acquire_resp.pfdev_info.pf_cap & PFVF_CAP_VLAN_FILTER) अणु
			dev->hw_features |= NETIF_F_HW_VLAN_CTAG_FILTER;
			dev->features |= NETIF_F_HW_VLAN_CTAG_FILTER;
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	/* Enable SRIOV अगर capability found in configuration space */
	rc = bnx2x_iov_init_one(bp, पूर्णांक_mode, BNX2X_MAX_NUM_OF_VFS);
	अगर (rc)
		जाओ init_one_मुक्तmem;

	/* calc qm_cid_count */
	bp->qm_cid_count = bnx2x_set_qm_cid_count(bp);
	BNX2X_DEV_INFO("qm_cid_count %d\n", bp->qm_cid_count);

	/* disable FCOE L2 queue क्रम E1x*/
	अगर (CHIP_IS_E1x(bp))
		bp->flags |= NO_FCOE_FLAG;

	/* Set bp->num_queues क्रम MSI-X mode*/
	bnx2x_set_num_queues(bp);

	/* Configure पूर्णांकerrupt mode: try to enable MSI-X/MSI अगर
	 * needed.
	 */
	rc = bnx2x_set_पूर्णांक_mode(bp);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Cannot set interrupts\n");
		जाओ init_one_मुक्तmem;
	पूर्ण
	BNX2X_DEV_INFO("set interrupts successfully\n");

	/* रेजिस्टर the net device */
	rc = रेजिस्टर_netdev(dev);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Cannot register net device\n");
		जाओ init_one_मुक्तmem;
	पूर्ण
	BNX2X_DEV_INFO("device name after netdev register %s\n", dev->name);

	अगर (!NO_FCOE(bp)) अणु
		/* Add storage MAC address */
		rtnl_lock();
		dev_addr_add(bp->dev, bp->fip_mac, NETDEV_HW_ADDR_T_SAN);
		rtnl_unlock();
	पूर्ण
	BNX2X_DEV_INFO(
	       "%s (%c%d) PCI-E found at mem %lx, IRQ %d, node addr %pM\n",
	       board_info[ent->driver_data].name,
	       (CHIP_REV(bp) >> 12) + 'A', (CHIP_METAL(bp) >> 4),
	       dev->base_addr, bp->pdev->irq, dev->dev_addr);
	pcie_prपूर्णांक_link_status(bp->pdev);

	अगर (!IS_MF_SD_STORAGE_PERSONALITY_ONLY(bp))
		bnx2x_set_os_driver_state(bp, OS_DRIVER_STATE_DISABLED);

	वापस 0;

init_one_मुक्तmem:
	bnx2x_मुक्त_mem_bp(bp);

init_one_निकास:
	bnx2x_disable_pcie_error_reporting(bp);

	अगर (bp->regview)
		iounmap(bp->regview);

	अगर (IS_PF(bp) && bp->करोorbells)
		iounmap(bp->करोorbells);

	मुक्त_netdev(dev);

	अगर (atomic_पढ़ो(&pdev->enable_cnt) == 1)
		pci_release_regions(pdev);

	pci_disable_device(pdev);

	वापस rc;
पूर्ण

अटल व्योम __bnx2x_हटाओ(काष्ठा pci_dev *pdev,
			   काष्ठा net_device *dev,
			   काष्ठा bnx2x *bp,
			   bool हटाओ_netdev)
अणु
	/* Delete storage MAC address */
	अगर (!NO_FCOE(bp)) अणु
		rtnl_lock();
		dev_addr_del(bp->dev, bp->fip_mac, NETDEV_HW_ADDR_T_SAN);
		rtnl_unlock();
	पूर्ण

#अगर_घोषित BCM_DCBNL
	/* Delete app tlvs from dcbnl */
	bnx2x_dcbnl_update_applist(bp, true);
#पूर्ण_अगर

	अगर (IS_PF(bp) &&
	    !BP_NOMCP(bp) &&
	    (bp->flags & BC_SUPPORTS_RMMOD_CMD))
		bnx2x_fw_command(bp, DRV_MSG_CODE_RMMOD, 0);

	/* Close the पूर्णांकerface - either directly or implicitly */
	अगर (हटाओ_netdev) अणु
		unरेजिस्टर_netdev(dev);
	पूर्ण अन्यथा अणु
		rtnl_lock();
		dev_बंद(dev);
		rtnl_unlock();
	पूर्ण

	bnx2x_iov_हटाओ_one(bp);

	/* Power on: we can't let PCI layer ग_लिखो to us जबतक we are in D3 */
	अगर (IS_PF(bp)) अणु
		bnx2x_set_घातer_state(bp, PCI_D0);
		bnx2x_set_os_driver_state(bp, OS_DRIVER_STATE_NOT_LOADED);

		/* Set endianity रेजिस्टरs to reset values in हाल next driver
		 * boots in dअगरferent endianty environment.
		 */
		bnx2x_reset_endianity(bp);
	पूर्ण

	/* Disable MSI/MSI-X */
	bnx2x_disable_msi(bp);

	/* Power off */
	अगर (IS_PF(bp))
		bnx2x_set_घातer_state(bp, PCI_D3hot);

	/* Make sure RESET task is not scheduled beक्रमe continuing */
	cancel_delayed_work_sync(&bp->sp_rtnl_task);

	/* send message via vfpf channel to release the resources of this vf */
	अगर (IS_VF(bp))
		bnx2x_vfpf_release(bp);

	/* Assumes no further PCIe PM changes will occur */
	अगर (प्रणाली_state == SYSTEM_POWER_OFF) अणु
		pci_wake_from_d3(pdev, bp->wol);
		pci_set_घातer_state(pdev, PCI_D3hot);
	पूर्ण

	bnx2x_disable_pcie_error_reporting(bp);
	अगर (हटाओ_netdev) अणु
		अगर (bp->regview)
			iounmap(bp->regview);

		/* For vfs, करोorbells are part of the regview and were unmapped
		 * aदीर्घ with it. FW is only loaded by PF.
		 */
		अगर (IS_PF(bp)) अणु
			अगर (bp->करोorbells)
				iounmap(bp->करोorbells);

			bnx2x_release_firmware(bp);
		पूर्ण अन्यथा अणु
			bnx2x_vf_pci_dealloc(bp);
		पूर्ण
		bnx2x_मुक्त_mem_bp(bp);

		मुक्त_netdev(dev);

		अगर (atomic_पढ़ो(&pdev->enable_cnt) == 1)
			pci_release_regions(pdev);

		pci_disable_device(pdev);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा bnx2x *bp;

	अगर (!dev) अणु
		dev_err(&pdev->dev, "BAD net device from bnx2x_init_one\n");
		वापस;
	पूर्ण
	bp = netdev_priv(dev);

	__bnx2x_हटाओ(pdev, dev, bp, true);
पूर्ण

अटल पूर्णांक bnx2x_eeh_nic_unload(काष्ठा bnx2x *bp)
अणु
	bp->state = BNX2X_STATE_CLOSING_WAIT4_HALT;

	bp->rx_mode = BNX2X_RX_MODE_NONE;

	अगर (CNIC_LOADED(bp))
		bnx2x_cnic_notअगरy(bp, CNIC_CTL_STOP_CMD);

	/* Stop Tx */
	bnx2x_tx_disable(bp);
	/* Delete all NAPI objects */
	bnx2x_del_all_napi(bp);
	अगर (CNIC_LOADED(bp))
		bnx2x_del_all_napi_cnic(bp);
	netdev_reset_tc(bp->dev);

	del_समयr_sync(&bp->समयr);
	cancel_delayed_work_sync(&bp->sp_task);
	cancel_delayed_work_sync(&bp->period_task);

	अगर (!करोwn_समयout(&bp->stats_lock, HZ / 10)) अणु
		bp->stats_state = STATS_STATE_DISABLED;
		up(&bp->stats_lock);
	पूर्ण

	bnx2x_save_statistics(bp);

	netअगर_carrier_off(bp->dev);

	वापस 0;
पूर्ण

/**
 * bnx2x_io_error_detected - called when PCI error is detected
 * @pdev: Poपूर्णांकer to PCI device
 * @state: The current pci connection state
 *
 * This function is called after a PCI bus error affecting
 * this device has been detected.
 */
अटल pci_ers_result_t bnx2x_io_error_detected(काष्ठा pci_dev *pdev,
						pci_channel_state_t state)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा bnx2x *bp = netdev_priv(dev);

	rtnl_lock();

	BNX2X_ERR("IO error detected\n");

	netअगर_device_detach(dev);

	अगर (state == pci_channel_io_perm_failure) अणु
		rtnl_unlock();
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	अगर (netअगर_running(dev))
		bnx2x_eeh_nic_unload(bp);

	bnx2x_prev_path_mark_eeh(bp);

	pci_disable_device(pdev);

	rtnl_unlock();

	/* Request a slot reset */
	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

/**
 * bnx2x_io_slot_reset - called after the PCI bus has been reset
 * @pdev: Poपूर्णांकer to PCI device
 *
 * Restart the card from scratch, as अगर from a cold-boot.
 */
अटल pci_ers_result_t bnx2x_io_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा bnx2x *bp = netdev_priv(dev);
	पूर्णांक i;

	rtnl_lock();
	BNX2X_ERR("IO slot reset initializing...\n");
	अगर (pci_enable_device(pdev)) अणु
		dev_err(&pdev->dev,
			"Cannot re-enable PCI device after reset\n");
		rtnl_unlock();
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	pci_set_master(pdev);
	pci_restore_state(pdev);
	pci_save_state(pdev);

	अगर (netअगर_running(dev))
		bnx2x_set_घातer_state(bp, PCI_D0);

	अगर (netअगर_running(dev)) अणु
		BNX2X_ERR("IO slot reset --> driver unload\n");

		/* MCP should have been reset; Need to रुको क्रम validity */
		अगर (bnx2x_init_shmem(bp)) अणु
			rtnl_unlock();
			वापस PCI_ERS_RESULT_DISCONNECT;
		पूर्ण

		अगर (IS_PF(bp) && SHMEM2_HAS(bp, drv_capabilities_flag)) अणु
			u32 v;

			v = SHMEM2_RD(bp,
				      drv_capabilities_flag[BP_FW_MB_IDX(bp)]);
			SHMEM2_WR(bp, drv_capabilities_flag[BP_FW_MB_IDX(bp)],
				  v & ~DRV_FLAGS_CAPABILITIES_LOADED_L2);
		पूर्ण
		bnx2x_drain_tx_queues(bp);
		bnx2x_send_unload_req(bp, UNLOAD_RECOVERY);
		bnx2x_netअगर_stop(bp, 1);
		bnx2x_मुक्त_irq(bp);

		/* Report UNLOAD_DONE to MCP */
		bnx2x_send_unload_करोne(bp, true);

		bp->sp_state = 0;
		bp->port.pmf = 0;

		bnx2x_prev_unload(bp);

		/* We should have reseted the engine, so It's fair to
		 * assume the FW will no दीर्घer ग_लिखो to the bnx2x driver.
		 */
		bnx2x_squeeze_objects(bp);
		bnx2x_मुक्त_skbs(bp);
		क्रम_each_rx_queue(bp, i)
			bnx2x_मुक्त_rx_sge_range(bp, bp->fp + i, NUM_RX_SGE);
		bnx2x_मुक्त_fp_mem(bp);
		bnx2x_मुक्त_mem(bp);

		bp->state = BNX2X_STATE_CLOSED;
	पूर्ण

	rtnl_unlock();

	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

/**
 * bnx2x_io_resume - called when traffic can start flowing again
 * @pdev: Poपूर्णांकer to PCI device
 *
 * This callback is called when the error recovery driver tells us that
 * its OK to resume normal operation.
 */
अटल व्योम bnx2x_io_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा bnx2x *bp = netdev_priv(dev);

	अगर (bp->recovery_state != BNX2X_RECOVERY_DONE) अणु
		netdev_err(bp->dev, "Handling parity error recovery. Try again later\n");
		वापस;
	पूर्ण

	rtnl_lock();

	bp->fw_seq = SHMEM_RD(bp, func_mb[BP_FW_MB_IDX(bp)].drv_mb_header) &
							DRV_MSG_SEQ_NUMBER_MASK;

	अगर (netअगर_running(dev))
		bnx2x_nic_load(bp, LOAD_NORMAL);

	netअगर_device_attach(dev);

	rtnl_unlock();
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers bnx2x_err_handler = अणु
	.error_detected = bnx2x_io_error_detected,
	.slot_reset     = bnx2x_io_slot_reset,
	.resume         = bnx2x_io_resume,
पूर्ण;

अटल व्योम bnx2x_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा bnx2x *bp;

	अगर (!dev)
		वापस;

	bp = netdev_priv(dev);
	अगर (!bp)
		वापस;

	rtnl_lock();
	netअगर_device_detach(dev);
	rtnl_unlock();

	/* Don't हटाओ the netdevice, as there are scenarios which will cause
	 * the kernel to hang, e.g., when trying to हटाओ bnx2i जबतक the
	 * rootfs is mounted from SAN.
	 */
	__bnx2x_हटाओ(pdev, dev, bp, false);
पूर्ण

अटल काष्ठा pci_driver bnx2x_pci_driver = अणु
	.name        = DRV_MODULE_NAME,
	.id_table    = bnx2x_pci_tbl,
	.probe       = bnx2x_init_one,
	.हटाओ      = bnx2x_हटाओ_one,
	.driver.pm   = &bnx2x_pm_ops,
	.err_handler = &bnx2x_err_handler,
#अगर_घोषित CONFIG_BNX2X_SRIOV
	.sriov_configure = bnx2x_sriov_configure,
#पूर्ण_अगर
	.shutकरोwn    = bnx2x_shutकरोwn,
पूर्ण;

अटल पूर्णांक __init bnx2x_init(व्योम)
अणु
	पूर्णांक ret;

	bnx2x_wq = create_singlethपढ़ो_workqueue("bnx2x");
	अगर (bnx2x_wq == शून्य) अणु
		pr_err("Cannot create workqueue\n");
		वापस -ENOMEM;
	पूर्ण
	bnx2x_iov_wq = create_singlethपढ़ो_workqueue("bnx2x_iov");
	अगर (!bnx2x_iov_wq) अणु
		pr_err("Cannot create iov workqueue\n");
		destroy_workqueue(bnx2x_wq);
		वापस -ENOMEM;
	पूर्ण

	ret = pci_रेजिस्टर_driver(&bnx2x_pci_driver);
	अगर (ret) अणु
		pr_err("Cannot register driver\n");
		destroy_workqueue(bnx2x_wq);
		destroy_workqueue(bnx2x_iov_wq);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम __निकास bnx2x_cleanup(व्योम)
अणु
	काष्ठा list_head *pos, *q;

	pci_unरेजिस्टर_driver(&bnx2x_pci_driver);

	destroy_workqueue(bnx2x_wq);
	destroy_workqueue(bnx2x_iov_wq);

	/* Free globally allocated resources */
	list_क्रम_each_safe(pos, q, &bnx2x_prev_list) अणु
		काष्ठा bnx2x_prev_path_list *पंचांगp =
			list_entry(pos, काष्ठा bnx2x_prev_path_list, list);
		list_del(pos);
		kमुक्त(पंचांगp);
	पूर्ण
पूर्ण

व्योम bnx2x_notअगरy_link_changed(काष्ठा bnx2x *bp)
अणु
	REG_WR(bp, MISC_REG_AEU_GENERAL_ATTN_12 + BP_FUNC(bp)*माप(u32), 1);
पूर्ण

module_init(bnx2x_init);
module_निकास(bnx2x_cleanup);

/**
 * bnx2x_set_iscsi_eth_mac_addr - set iSCSI MAC(s).
 * @bp:		driver handle
 *
 * This function will रुको until the ramrod completion वापसs.
 * Return 0 अगर success, -ENODEV अगर ramrod करोesn't वापस.
 */
अटल पूर्णांक bnx2x_set_iscsi_eth_mac_addr(काष्ठा bnx2x *bp)
अणु
	अचिन्हित दीर्घ ramrod_flags = 0;

	__set_bit(RAMROD_COMP_WAIT, &ramrod_flags);
	वापस bnx2x_set_mac_one(bp, bp->cnic_eth_dev.iscsi_mac,
				 &bp->iscsi_l2_mac_obj, true,
				 BNX2X_ISCSI_ETH_MAC, &ramrod_flags);
पूर्ण

/* count denotes the number of new completions we have seen */
अटल व्योम bnx2x_cnic_sp_post(काष्ठा bnx2x *bp, पूर्णांक count)
अणु
	काष्ठा eth_spe *spe;
	पूर्णांक cxt_index, cxt_offset;

#अगर_घोषित BNX2X_STOP_ON_ERROR
	अगर (unlikely(bp->panic))
		वापस;
#पूर्ण_अगर

	spin_lock_bh(&bp->spq_lock);
	BUG_ON(bp->cnic_spq_pending < count);
	bp->cnic_spq_pending -= count;

	क्रम (; bp->cnic_kwq_pending; bp->cnic_kwq_pending--) अणु
		u16 type =  (le16_to_cpu(bp->cnic_kwq_cons->hdr.type)
				& SPE_HDR_CONN_TYPE) >>
				SPE_HDR_CONN_TYPE_SHIFT;
		u8 cmd = (le32_to_cpu(bp->cnic_kwq_cons->hdr.conn_and_cmd_data)
				>> SPE_HDR_CMD_ID_SHIFT) & 0xff;

		/* Set validation क्रम iSCSI L2 client beक्रमe sending SETUP
		 *  ramrod
		 */
		अगर (type == ETH_CONNECTION_TYPE) अणु
			अगर (cmd == RAMROD_CMD_ID_ETH_CLIENT_SETUP) अणु
				cxt_index = BNX2X_ISCSI_ETH_CID(bp) /
					ILT_PAGE_CIDS;
				cxt_offset = BNX2X_ISCSI_ETH_CID(bp) -
					(cxt_index * ILT_PAGE_CIDS);
				bnx2x_set_ctx_validation(bp,
					&bp->context[cxt_index].
							 vcxt[cxt_offset].eth,
					BNX2X_ISCSI_ETH_CID(bp));
			पूर्ण
		पूर्ण

		/*
		 * There may be not more than 8 L2, not more than 8 L5 SPEs
		 * and in the air. We also check that number of outstanding
		 * COMMON ramrods is not more than the EQ and SPQ can
		 * accommodate.
		 */
		अगर (type == ETH_CONNECTION_TYPE) अणु
			अगर (!atomic_पढ़ो(&bp->cq_spq_left))
				अवरोध;
			अन्यथा
				atomic_dec(&bp->cq_spq_left);
		पूर्ण अन्यथा अगर (type == NONE_CONNECTION_TYPE) अणु
			अगर (!atomic_पढ़ो(&bp->eq_spq_left))
				अवरोध;
			अन्यथा
				atomic_dec(&bp->eq_spq_left);
		पूर्ण अन्यथा अगर ((type == ISCSI_CONNECTION_TYPE) ||
			   (type == FCOE_CONNECTION_TYPE)) अणु
			अगर (bp->cnic_spq_pending >=
			    bp->cnic_eth_dev.max_kwqe_pending)
				अवरोध;
			अन्यथा
				bp->cnic_spq_pending++;
		पूर्ण अन्यथा अणु
			BNX2X_ERR("Unknown SPE type: %d\n", type);
			bnx2x_panic();
			अवरोध;
		पूर्ण

		spe = bnx2x_sp_get_next(bp);
		*spe = *bp->cnic_kwq_cons;

		DP(BNX2X_MSG_SP, "pending on SPQ %d, on KWQ %d count %d\n",
		   bp->cnic_spq_pending, bp->cnic_kwq_pending, count);

		अगर (bp->cnic_kwq_cons == bp->cnic_kwq_last)
			bp->cnic_kwq_cons = bp->cnic_kwq;
		अन्यथा
			bp->cnic_kwq_cons++;
	पूर्ण
	bnx2x_sp_prod_update(bp);
	spin_unlock_bh(&bp->spq_lock);
पूर्ण

अटल पूर्णांक bnx2x_cnic_sp_queue(काष्ठा net_device *dev,
			       काष्ठा kwqe_16 *kwqes[], u32 count)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	पूर्णांक i;

#अगर_घोषित BNX2X_STOP_ON_ERROR
	अगर (unlikely(bp->panic)) अणु
		BNX2X_ERR("Can't post to SP queue while panic\n");
		वापस -EIO;
	पूर्ण
#पूर्ण_अगर

	अगर ((bp->recovery_state != BNX2X_RECOVERY_DONE) &&
	    (bp->recovery_state != BNX2X_RECOVERY_NIC_LOADING)) अणु
		BNX2X_ERR("Handling parity error recovery. Try again later\n");
		वापस -EAGAIN;
	पूर्ण

	spin_lock_bh(&bp->spq_lock);

	क्रम (i = 0; i < count; i++) अणु
		काष्ठा eth_spe *spe = (काष्ठा eth_spe *)kwqes[i];

		अगर (bp->cnic_kwq_pending == MAX_SP_DESC_CNT)
			अवरोध;

		*bp->cnic_kwq_prod = *spe;

		bp->cnic_kwq_pending++;

		DP(BNX2X_MSG_SP, "L5 SPQE %x %x %x:%x pos %d\n",
		   spe->hdr.conn_and_cmd_data, spe->hdr.type,
		   spe->data.update_data_addr.hi,
		   spe->data.update_data_addr.lo,
		   bp->cnic_kwq_pending);

		अगर (bp->cnic_kwq_prod == bp->cnic_kwq_last)
			bp->cnic_kwq_prod = bp->cnic_kwq;
		अन्यथा
			bp->cnic_kwq_prod++;
	पूर्ण

	spin_unlock_bh(&bp->spq_lock);

	अगर (bp->cnic_spq_pending < bp->cnic_eth_dev.max_kwqe_pending)
		bnx2x_cnic_sp_post(bp, 0);

	वापस i;
पूर्ण

अटल पूर्णांक bnx2x_cnic_ctl_send(काष्ठा bnx2x *bp, काष्ठा cnic_ctl_info *ctl)
अणु
	काष्ठा cnic_ops *c_ops;
	पूर्णांक rc = 0;

	mutex_lock(&bp->cnic_mutex);
	c_ops = rcu_dereference_रक्षित(bp->cnic_ops,
					  lockdep_is_held(&bp->cnic_mutex));
	अगर (c_ops)
		rc = c_ops->cnic_ctl(bp->cnic_data, ctl);
	mutex_unlock(&bp->cnic_mutex);

	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_cnic_ctl_send_bh(काष्ठा bnx2x *bp, काष्ठा cnic_ctl_info *ctl)
अणु
	काष्ठा cnic_ops *c_ops;
	पूर्णांक rc = 0;

	rcu_पढ़ो_lock();
	c_ops = rcu_dereference(bp->cnic_ops);
	अगर (c_ops)
		rc = c_ops->cnic_ctl(bp->cnic_data, ctl);
	rcu_पढ़ो_unlock();

	वापस rc;
पूर्ण

/*
 * क्रम commands that have no data
 */
पूर्णांक bnx2x_cnic_notअगरy(काष्ठा bnx2x *bp, पूर्णांक cmd)
अणु
	काष्ठा cnic_ctl_info ctl = अणु0पूर्ण;

	ctl.cmd = cmd;

	वापस bnx2x_cnic_ctl_send(bp, &ctl);
पूर्ण

अटल व्योम bnx2x_cnic_cfc_comp(काष्ठा bnx2x *bp, पूर्णांक cid, u8 err)
अणु
	काष्ठा cnic_ctl_info ctl = अणु0पूर्ण;

	/* first we tell CNIC and only then we count this as a completion */
	ctl.cmd = CNIC_CTL_COMPLETION_CMD;
	ctl.data.comp.cid = cid;
	ctl.data.comp.error = err;

	bnx2x_cnic_ctl_send_bh(bp, &ctl);
	bnx2x_cnic_sp_post(bp, 0);
पूर्ण

/* Called with netअगर_addr_lock_bh() taken.
 * Sets an rx_mode config क्रम an iSCSI ETH client.
 * Doesn't block.
 * Completion should be checked outside.
 */
अटल व्योम bnx2x_set_iscsi_eth_rx_mode(काष्ठा bnx2x *bp, bool start)
अणु
	अचिन्हित दीर्घ accept_flags = 0, ramrod_flags = 0;
	u8 cl_id = bnx2x_cnic_eth_cl_id(bp, BNX2X_ISCSI_ETH_CL_ID_IDX);
	पूर्णांक sched_state = BNX2X_FILTER_ISCSI_ETH_STOP_SCHED;

	अगर (start) अणु
		/* Start accepting on iSCSI L2 ring. Accept all multicasts
		 * because it's the only way क्रम UIO Queue to accept
		 * multicasts (in non-promiscuous mode only one Queue per
		 * function will receive multicast packets (leading in our
		 * हाल).
		 */
		__set_bit(BNX2X_ACCEPT_UNICAST, &accept_flags);
		__set_bit(BNX2X_ACCEPT_ALL_MULTICAST, &accept_flags);
		__set_bit(BNX2X_ACCEPT_BROADCAST, &accept_flags);
		__set_bit(BNX2X_ACCEPT_ANY_VLAN, &accept_flags);

		/* Clear STOP_PENDING bit अगर START is requested */
		clear_bit(BNX2X_FILTER_ISCSI_ETH_STOP_SCHED, &bp->sp_state);

		sched_state = BNX2X_FILTER_ISCSI_ETH_START_SCHED;
	पूर्ण अन्यथा
		/* Clear START_PENDING bit अगर STOP is requested */
		clear_bit(BNX2X_FILTER_ISCSI_ETH_START_SCHED, &bp->sp_state);

	अगर (test_bit(BNX2X_FILTER_RX_MODE_PENDING, &bp->sp_state))
		set_bit(sched_state, &bp->sp_state);
	अन्यथा अणु
		__set_bit(RAMROD_RX, &ramrod_flags);
		bnx2x_set_q_rx_mode(bp, cl_id, 0, accept_flags, 0,
				    ramrod_flags);
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_drv_ctl(काष्ठा net_device *dev, काष्ठा drv_ctl_info *ctl)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	पूर्णांक rc = 0;

	चयन (ctl->cmd) अणु
	हाल DRV_CTL_CTXTBL_WR_CMD: अणु
		u32 index = ctl->data.io.offset;
		dma_addr_t addr = ctl->data.io.dma_addr;

		bnx2x_ilt_wr(bp, index, addr);
		अवरोध;
	पूर्ण

	हाल DRV_CTL_RET_L5_SPQ_CREDIT_CMD: अणु
		पूर्णांक count = ctl->data.credit.credit_count;

		bnx2x_cnic_sp_post(bp, count);
		अवरोध;
	पूर्ण

	/* rtnl_lock is held.  */
	हाल DRV_CTL_START_L2_CMD: अणु
		काष्ठा cnic_eth_dev *cp = &bp->cnic_eth_dev;
		अचिन्हित दीर्घ sp_bits = 0;

		/* Configure the iSCSI classअगरication object */
		bnx2x_init_mac_obj(bp, &bp->iscsi_l2_mac_obj,
				   cp->iscsi_l2_client_id,
				   cp->iscsi_l2_cid, BP_FUNC(bp),
				   bnx2x_sp(bp, mac_rdata),
				   bnx2x_sp_mapping(bp, mac_rdata),
				   BNX2X_FILTER_MAC_PENDING,
				   &bp->sp_state, BNX2X_OBJ_TYPE_RX,
				   &bp->macs_pool);

		/* Set iSCSI MAC address */
		rc = bnx2x_set_iscsi_eth_mac_addr(bp);
		अगर (rc)
			अवरोध;

		barrier();

		/* Start accepting on iSCSI L2 ring */

		netअगर_addr_lock_bh(dev);
		bnx2x_set_iscsi_eth_rx_mode(bp, true);
		netअगर_addr_unlock_bh(dev);

		/* bits to रुको on */
		__set_bit(BNX2X_FILTER_RX_MODE_PENDING, &sp_bits);
		__set_bit(BNX2X_FILTER_ISCSI_ETH_START_SCHED, &sp_bits);

		अगर (!bnx2x_रुको_sp_comp(bp, sp_bits))
			BNX2X_ERR("rx_mode completion timed out!\n");

		अवरोध;
	पूर्ण

	/* rtnl_lock is held.  */
	हाल DRV_CTL_STOP_L2_CMD: अणु
		अचिन्हित दीर्घ sp_bits = 0;

		/* Stop accepting on iSCSI L2 ring */
		netअगर_addr_lock_bh(dev);
		bnx2x_set_iscsi_eth_rx_mode(bp, false);
		netअगर_addr_unlock_bh(dev);

		/* bits to रुको on */
		__set_bit(BNX2X_FILTER_RX_MODE_PENDING, &sp_bits);
		__set_bit(BNX2X_FILTER_ISCSI_ETH_STOP_SCHED, &sp_bits);

		अगर (!bnx2x_रुको_sp_comp(bp, sp_bits))
			BNX2X_ERR("rx_mode completion timed out!\n");

		barrier();

		/* Unset iSCSI L2 MAC */
		rc = bnx2x_del_all_macs(bp, &bp->iscsi_l2_mac_obj,
					BNX2X_ISCSI_ETH_MAC, true);
		अवरोध;
	पूर्ण
	हाल DRV_CTL_RET_L2_SPQ_CREDIT_CMD: अणु
		पूर्णांक count = ctl->data.credit.credit_count;

		smp_mb__beक्रमe_atomic();
		atomic_add(count, &bp->cq_spq_left);
		smp_mb__after_atomic();
		अवरोध;
	पूर्ण
	हाल DRV_CTL_ULP_REGISTER_CMD: अणु
		पूर्णांक ulp_type = ctl->data.रेजिस्टर_data.ulp_type;

		अगर (CHIP_IS_E3(bp)) अणु
			पूर्णांक idx = BP_FW_MB_IDX(bp);
			u32 cap = SHMEM2_RD(bp, drv_capabilities_flag[idx]);
			पूर्णांक path = BP_PATH(bp);
			पूर्णांक port = BP_PORT(bp);
			पूर्णांक i;
			u32 scratch_offset;
			u32 *host_addr;

			/* first ग_लिखो capability to shmem2 */
			अगर (ulp_type == CNIC_ULP_ISCSI)
				cap |= DRV_FLAGS_CAPABILITIES_LOADED_ISCSI;
			अन्यथा अगर (ulp_type == CNIC_ULP_FCOE)
				cap |= DRV_FLAGS_CAPABILITIES_LOADED_FCOE;
			SHMEM2_WR(bp, drv_capabilities_flag[idx], cap);

			अगर ((ulp_type != CNIC_ULP_FCOE) ||
			    (!SHMEM2_HAS(bp, ncsi_oem_data_addr)) ||
			    (!(bp->flags &  BC_SUPPORTS_FCOE_FEATURES)))
				अवरोध;

			/* अगर reached here - should ग_लिखो fcoe capabilities */
			scratch_offset = SHMEM2_RD(bp, ncsi_oem_data_addr);
			अगर (!scratch_offset)
				अवरोध;
			scratch_offset += दुरत्व(काष्ठा glob_ncsi_oem_data,
						   fcoe_features[path][port]);
			host_addr = (u32 *) &(ctl->data.रेजिस्टर_data.
					      fcoe_features);
			क्रम (i = 0; i < माप(काष्ठा fcoe_capabilities);
			     i += 4)
				REG_WR(bp, scratch_offset + i,
				       *(host_addr + i/4));
		पूर्ण
		bnx2x_schedule_sp_rtnl(bp, BNX2X_SP_RTNL_GET_DRV_VERSION, 0);
		अवरोध;
	पूर्ण

	हाल DRV_CTL_ULP_UNREGISTER_CMD: अणु
		पूर्णांक ulp_type = ctl->data.ulp_type;

		अगर (CHIP_IS_E3(bp)) अणु
			पूर्णांक idx = BP_FW_MB_IDX(bp);
			u32 cap;

			cap = SHMEM2_RD(bp, drv_capabilities_flag[idx]);
			अगर (ulp_type == CNIC_ULP_ISCSI)
				cap &= ~DRV_FLAGS_CAPABILITIES_LOADED_ISCSI;
			अन्यथा अगर (ulp_type == CNIC_ULP_FCOE)
				cap &= ~DRV_FLAGS_CAPABILITIES_LOADED_FCOE;
			SHMEM2_WR(bp, drv_capabilities_flag[idx], cap);
		पूर्ण
		bnx2x_schedule_sp_rtnl(bp, BNX2X_SP_RTNL_GET_DRV_VERSION, 0);
		अवरोध;
	पूर्ण

	शेष:
		BNX2X_ERR("unknown command %x\n", ctl->cmd);
		rc = -EINVAL;
	पूर्ण

	/* For storage-only पूर्णांकerfaces, change driver state */
	अगर (IS_MF_SD_STORAGE_PERSONALITY_ONLY(bp)) अणु
		चयन (ctl->drv_state) अणु
		हाल DRV_NOP:
			अवरोध;
		हाल DRV_ACTIVE:
			bnx2x_set_os_driver_state(bp,
						  OS_DRIVER_STATE_ACTIVE);
			अवरोध;
		हाल DRV_INACTIVE:
			bnx2x_set_os_driver_state(bp,
						  OS_DRIVER_STATE_DISABLED);
			अवरोध;
		हाल DRV_UNLOADED:
			bnx2x_set_os_driver_state(bp,
						  OS_DRIVER_STATE_NOT_LOADED);
			अवरोध;
		शेष:
		BNX2X_ERR("Unknown cnic driver state: %d\n", ctl->drv_state);
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_get_fc_npiv(काष्ठा net_device *dev,
			     काष्ठा cnic_fc_npiv_tbl *cnic_tbl)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	काष्ठा bdn_fc_npiv_tbl *tbl = शून्य;
	u32 offset, entries;
	पूर्णांक rc = -EINVAL;
	पूर्णांक i;

	अगर (!SHMEM2_HAS(bp, fc_npiv_nvram_tbl_addr[0]))
		जाओ out;

	DP(BNX2X_MSG_MCP, "About to read the FC-NPIV table\n");

	tbl = kदो_स्मृति(माप(*tbl), GFP_KERNEL);
	अगर (!tbl) अणु
		BNX2X_ERR("Failed to allocate fc_npiv table\n");
		जाओ out;
	पूर्ण

	offset = SHMEM2_RD(bp, fc_npiv_nvram_tbl_addr[BP_PORT(bp)]);
	अगर (!offset) अणु
		DP(BNX2X_MSG_MCP, "No FC-NPIV in NVRAM\n");
		जाओ out;
	पूर्ण
	DP(BNX2X_MSG_MCP, "Offset of FC-NPIV in NVRAM: %08x\n", offset);

	/* Read the table contents from nvram */
	अगर (bnx2x_nvram_पढ़ो(bp, offset, (u8 *)tbl, माप(*tbl))) अणु
		BNX2X_ERR("Failed to read FC-NPIV table\n");
		जाओ out;
	पूर्ण

	/* Since bnx2x_nvram_पढ़ो() वापसs data in be32, we need to convert
	 * the number of entries back to cpu endianness.
	 */
	entries = tbl->fc_npiv_cfg.num_of_npiv;
	entries = (__क्रमce u32)be32_to_cpu((__क्रमce __be32)entries);
	tbl->fc_npiv_cfg.num_of_npiv = entries;

	अगर (!tbl->fc_npiv_cfg.num_of_npiv) अणु
		DP(BNX2X_MSG_MCP,
		   "No FC-NPIV table [valid, simply not present]\n");
		जाओ out;
	पूर्ण अन्यथा अगर (tbl->fc_npiv_cfg.num_of_npiv > MAX_NUMBER_NPIV) अणु
		BNX2X_ERR("FC-NPIV table with bad length 0x%08x\n",
			  tbl->fc_npiv_cfg.num_of_npiv);
		जाओ out;
	पूर्ण अन्यथा अणु
		DP(BNX2X_MSG_MCP, "Read 0x%08x entries from NVRAM\n",
		   tbl->fc_npiv_cfg.num_of_npiv);
	पूर्ण

	/* Copy the data पूर्णांकo cnic-provided काष्ठा */
	cnic_tbl->count = tbl->fc_npiv_cfg.num_of_npiv;
	क्रम (i = 0; i < cnic_tbl->count; i++) अणु
		स_नकल(cnic_tbl->wwpn[i], tbl->settings[i].npiv_wwpn, 8);
		स_नकल(cnic_tbl->wwnn[i], tbl->settings[i].npiv_wwnn, 8);
	पूर्ण

	rc = 0;
out:
	kमुक्त(tbl);
	वापस rc;
पूर्ण

व्योम bnx2x_setup_cnic_irq_info(काष्ठा bnx2x *bp)
अणु
	काष्ठा cnic_eth_dev *cp = &bp->cnic_eth_dev;

	अगर (bp->flags & USING_MSIX_FLAG) अणु
		cp->drv_state |= CNIC_DRV_STATE_USING_MSIX;
		cp->irq_arr[0].irq_flags |= CNIC_IRQ_FL_MSIX;
		cp->irq_arr[0].vector = bp->msix_table[1].vector;
	पूर्ण अन्यथा अणु
		cp->drv_state &= ~CNIC_DRV_STATE_USING_MSIX;
		cp->irq_arr[0].irq_flags &= ~CNIC_IRQ_FL_MSIX;
	पूर्ण
	अगर (!CHIP_IS_E1x(bp))
		cp->irq_arr[0].status_blk = (व्योम *)bp->cnic_sb.e2_sb;
	अन्यथा
		cp->irq_arr[0].status_blk = (व्योम *)bp->cnic_sb.e1x_sb;

	cp->irq_arr[0].status_blk_num =  bnx2x_cnic_fw_sb_id(bp);
	cp->irq_arr[0].status_blk_num2 = bnx2x_cnic_igu_sb_id(bp);
	cp->irq_arr[1].status_blk = bp->def_status_blk;
	cp->irq_arr[1].status_blk_num = DEF_SB_ID;
	cp->irq_arr[1].status_blk_num2 = DEF_SB_IGU_ID;

	cp->num_irq = 2;
पूर्ण

व्योम bnx2x_setup_cnic_info(काष्ठा bnx2x *bp)
अणु
	काष्ठा cnic_eth_dev *cp = &bp->cnic_eth_dev;

	cp->ctx_tbl_offset = FUNC_ILT_BASE(BP_FUNC(bp)) +
			     bnx2x_cid_ilt_lines(bp);
	cp->starting_cid = bnx2x_cid_ilt_lines(bp) * ILT_PAGE_CIDS;
	cp->fcoe_init_cid = BNX2X_FCOE_ETH_CID(bp);
	cp->iscsi_l2_cid = BNX2X_ISCSI_ETH_CID(bp);

	DP(NETIF_MSG_IFUP, "BNX2X_1st_NON_L2_ETH_CID(bp) %x, cp->starting_cid %x, cp->fcoe_init_cid %x, cp->iscsi_l2_cid %x\n",
	   BNX2X_1st_NON_L2_ETH_CID(bp), cp->starting_cid, cp->fcoe_init_cid,
	   cp->iscsi_l2_cid);

	अगर (NO_ISCSI_OOO(bp))
		cp->drv_state |= CNIC_DRV_STATE_NO_ISCSI_OOO;
पूर्ण

अटल पूर्णांक bnx2x_रेजिस्टर_cnic(काष्ठा net_device *dev, काष्ठा cnic_ops *ops,
			       व्योम *data)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	काष्ठा cnic_eth_dev *cp = &bp->cnic_eth_dev;
	पूर्णांक rc;

	DP(NETIF_MSG_IFUP, "Register_cnic called\n");

	अगर (ops == शून्य) अणु
		BNX2X_ERR("NULL ops received\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!CNIC_SUPPORT(bp)) अणु
		BNX2X_ERR("Can't register CNIC when not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!CNIC_LOADED(bp)) अणु
		rc = bnx2x_load_cnic(bp);
		अगर (rc) अणु
			BNX2X_ERR("CNIC-related load failed\n");
			वापस rc;
		पूर्ण
	पूर्ण

	bp->cnic_enabled = true;

	bp->cnic_kwq = kzalloc(PAGE_SIZE, GFP_KERNEL);
	अगर (!bp->cnic_kwq)
		वापस -ENOMEM;

	bp->cnic_kwq_cons = bp->cnic_kwq;
	bp->cnic_kwq_prod = bp->cnic_kwq;
	bp->cnic_kwq_last = bp->cnic_kwq + MAX_SP_DESC_CNT;

	bp->cnic_spq_pending = 0;
	bp->cnic_kwq_pending = 0;

	bp->cnic_data = data;

	cp->num_irq = 0;
	cp->drv_state |= CNIC_DRV_STATE_REGD;
	cp->iro_arr = bp->iro_arr;

	bnx2x_setup_cnic_irq_info(bp);

	rcu_assign_poपूर्णांकer(bp->cnic_ops, ops);

	/* Schedule driver to पढ़ो CNIC driver versions */
	bnx2x_schedule_sp_rtnl(bp, BNX2X_SP_RTNL_GET_DRV_VERSION, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_unरेजिस्टर_cnic(काष्ठा net_device *dev)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	काष्ठा cnic_eth_dev *cp = &bp->cnic_eth_dev;

	mutex_lock(&bp->cnic_mutex);
	cp->drv_state = 0;
	RCU_INIT_POINTER(bp->cnic_ops, शून्य);
	mutex_unlock(&bp->cnic_mutex);
	synchronize_rcu();
	bp->cnic_enabled = false;
	kमुक्त(bp->cnic_kwq);
	bp->cnic_kwq = शून्य;

	वापस 0;
पूर्ण

अटल काष्ठा cnic_eth_dev *bnx2x_cnic_probe(काष्ठा net_device *dev)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	काष्ठा cnic_eth_dev *cp = &bp->cnic_eth_dev;

	/* If both iSCSI and FCoE are disabled - वापस शून्य in
	 * order to indicate CNIC that it should not try to work
	 * with this device.
	 */
	अगर (NO_ISCSI(bp) && NO_FCOE(bp))
		वापस शून्य;

	cp->drv_owner = THIS_MODULE;
	cp->chip_id = CHIP_ID(bp);
	cp->pdev = bp->pdev;
	cp->io_base = bp->regview;
	cp->io_base2 = bp->करोorbells;
	cp->max_kwqe_pending = 8;
	cp->ctx_blk_size = CDU_ILT_PAGE_SZ;
	cp->ctx_tbl_offset = FUNC_ILT_BASE(BP_FUNC(bp)) +
			     bnx2x_cid_ilt_lines(bp);
	cp->ctx_tbl_len = CNIC_ILT_LINES;
	cp->starting_cid = bnx2x_cid_ilt_lines(bp) * ILT_PAGE_CIDS;
	cp->drv_submit_kwqes_16 = bnx2x_cnic_sp_queue;
	cp->drv_ctl = bnx2x_drv_ctl;
	cp->drv_get_fc_npiv_tbl = bnx2x_get_fc_npiv;
	cp->drv_रेजिस्टर_cnic = bnx2x_रेजिस्टर_cnic;
	cp->drv_unरेजिस्टर_cnic = bnx2x_unरेजिस्टर_cnic;
	cp->fcoe_init_cid = BNX2X_FCOE_ETH_CID(bp);
	cp->iscsi_l2_client_id =
		bnx2x_cnic_eth_cl_id(bp, BNX2X_ISCSI_ETH_CL_ID_IDX);
	cp->iscsi_l2_cid = BNX2X_ISCSI_ETH_CID(bp);

	अगर (NO_ISCSI_OOO(bp))
		cp->drv_state |= CNIC_DRV_STATE_NO_ISCSI_OOO;

	अगर (NO_ISCSI(bp))
		cp->drv_state |= CNIC_DRV_STATE_NO_ISCSI;

	अगर (NO_FCOE(bp))
		cp->drv_state |= CNIC_DRV_STATE_NO_FCOE;

	BNX2X_DEV_INFO(
		"page_size %d, tbl_offset %d, tbl_lines %d, starting cid %d\n",
	   cp->ctx_blk_size,
	   cp->ctx_tbl_offset,
	   cp->ctx_tbl_len,
	   cp->starting_cid);
	वापस cp;
पूर्ण

अटल u32 bnx2x_rx_ustorm_prods_offset(काष्ठा bnx2x_fastpath *fp)
अणु
	काष्ठा bnx2x *bp = fp->bp;
	u32 offset = BAR_USTRORM_INTMEM;

	अगर (IS_VF(bp))
		वापस bnx2x_vf_ustorm_prods_offset(bp, fp);
	अन्यथा अगर (!CHIP_IS_E1x(bp))
		offset += USTORM_RX_PRODS_E2_OFFSET(fp->cl_qzone_id);
	अन्यथा
		offset += USTORM_RX_PRODS_E1X_OFFSET(BP_PORT(bp), fp->cl_id);

	वापस offset;
पूर्ण

/* called only on E1H or E2.
 * When pretending to be PF, the pretend value is the function number 0...7
 * When pretending to be VF, the pretend val is the PF-num:VF-valid:ABS-VFID
 * combination
 */
पूर्णांक bnx2x_pretend_func(काष्ठा bnx2x *bp, u16 pretend_func_val)
अणु
	u32 pretend_reg;

	अगर (CHIP_IS_E1H(bp) && pretend_func_val >= E1H_FUNC_MAX)
		वापस -1;

	/* get my own pretend रेजिस्टर */
	pretend_reg = bnx2x_get_pretend_reg(bp);
	REG_WR(bp, pretend_reg, pretend_func_val);
	REG_RD(bp, pretend_reg);
	वापस 0;
पूर्ण

अटल व्योम bnx2x_ptp_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bnx2x *bp = container_of(work, काष्ठा bnx2x, ptp_task);
	पूर्णांक port = BP_PORT(bp);
	u32 val_seq;
	u64 बारtamp, ns;
	काष्ठा skb_shared_hwtstamps shhwtstamps;
	bool bail = true;
	पूर्णांक i;

	/* FW may take a जबतक to complete बारtamping; try a bit and अगर it's
	 * still not complete, may indicate an error state - bail out then.
	 */
	क्रम (i = 0; i < 10; i++) अणु
		/* Read Tx बारtamp रेजिस्टरs */
		val_seq = REG_RD(bp, port ? NIG_REG_P1_TLLH_PTP_BUF_SEQID :
				 NIG_REG_P0_TLLH_PTP_BUF_SEQID);
		अगर (val_seq & 0x10000) अणु
			bail = false;
			अवरोध;
		पूर्ण
		msleep(1 << i);
	पूर्ण

	अगर (!bail) अणु
		/* There is a valid बारtamp value */
		बारtamp = REG_RD(bp, port ? NIG_REG_P1_TLLH_PTP_BUF_TS_MSB :
				   NIG_REG_P0_TLLH_PTP_BUF_TS_MSB);
		बारtamp <<= 32;
		बारtamp |= REG_RD(bp, port ? NIG_REG_P1_TLLH_PTP_BUF_TS_LSB :
				    NIG_REG_P0_TLLH_PTP_BUF_TS_LSB);
		/* Reset बारtamp रेजिस्टर to allow new बारtamp */
		REG_WR(bp, port ? NIG_REG_P1_TLLH_PTP_BUF_SEQID :
		       NIG_REG_P0_TLLH_PTP_BUF_SEQID, 0x10000);
		ns = समयcounter_cyc2समय(&bp->समयcounter, बारtamp);

		स_रखो(&shhwtstamps, 0, माप(shhwtstamps));
		shhwtstamps.hwtstamp = ns_to_kसमय(ns);
		skb_tstamp_tx(bp->ptp_tx_skb, &shhwtstamps);

		DP(BNX2X_MSG_PTP, "Tx timestamp, timestamp cycles = %llu, ns = %llu\n",
		   बारtamp, ns);
	पूर्ण अन्यथा अणु
		DP(BNX2X_MSG_PTP,
		   "Tx timestamp is not recorded (register read=%u)\n",
		   val_seq);
		bp->eth_stats.ptp_skip_tx_ts++;
	पूर्ण

	dev_kमुक्त_skb_any(bp->ptp_tx_skb);
	bp->ptp_tx_skb = शून्य;
पूर्ण

व्योम bnx2x_set_rx_ts(काष्ठा bnx2x *bp, काष्ठा sk_buff *skb)
अणु
	पूर्णांक port = BP_PORT(bp);
	u64 बारtamp, ns;

	बारtamp = REG_RD(bp, port ? NIG_REG_P1_LLH_PTP_HOST_BUF_TS_MSB :
			    NIG_REG_P0_LLH_PTP_HOST_BUF_TS_MSB);
	बारtamp <<= 32;
	बारtamp |= REG_RD(bp, port ? NIG_REG_P1_LLH_PTP_HOST_BUF_TS_LSB :
			    NIG_REG_P0_LLH_PTP_HOST_BUF_TS_LSB);

	/* Reset बारtamp रेजिस्टर to allow new बारtamp */
	REG_WR(bp, port ? NIG_REG_P1_LLH_PTP_HOST_BUF_SEQID :
	       NIG_REG_P0_LLH_PTP_HOST_BUF_SEQID, 0x10000);

	ns = समयcounter_cyc2समय(&bp->समयcounter, बारtamp);

	skb_hwtstamps(skb)->hwtstamp = ns_to_kसमय(ns);

	DP(BNX2X_MSG_PTP, "Rx timestamp, timestamp cycles = %llu, ns = %llu\n",
	   बारtamp, ns);
पूर्ण

/* Read the PHC */
अटल u64 bnx2x_cyclecounter_पढ़ो(स्थिर काष्ठा cyclecounter *cc)
अणु
	काष्ठा bnx2x *bp = container_of(cc, काष्ठा bnx2x, cyclecounter);
	पूर्णांक port = BP_PORT(bp);
	u32 wb_data[2];
	u64 phc_cycles;

	REG_RD_DMAE(bp, port ? NIG_REG_TIMESYNC_GEN_REG + tsgen_synस_समय_t1 :
		    NIG_REG_TIMESYNC_GEN_REG + tsgen_synस_समय_t0, wb_data, 2);
	phc_cycles = wb_data[1];
	phc_cycles = (phc_cycles << 32) + wb_data[0];

	DP(BNX2X_MSG_PTP, "PHC read cycles = %llu\n", phc_cycles);

	वापस phc_cycles;
पूर्ण

अटल व्योम bnx2x_init_cyclecounter(काष्ठा bnx2x *bp)
अणु
	स_रखो(&bp->cyclecounter, 0, माप(bp->cyclecounter));
	bp->cyclecounter.पढ़ो = bnx2x_cyclecounter_पढ़ो;
	bp->cyclecounter.mask = CYCLECOUNTER_MASK(64);
	bp->cyclecounter.shअगरt = 0;
	bp->cyclecounter.mult = 1;
पूर्ण

अटल पूर्णांक bnx2x_send_reset_बारync_ramrod(काष्ठा bnx2x *bp)
अणु
	काष्ठा bnx2x_func_state_params func_params = अणुशून्यपूर्ण;
	काष्ठा bnx2x_func_set_बारync_params *set_बारync_params =
		&func_params.params.set_बारync;

	/* Prepare parameters क्रम function state transitions */
	__set_bit(RAMROD_COMP_WAIT, &func_params.ramrod_flags);
	__set_bit(RAMROD_RETRY, &func_params.ramrod_flags);

	func_params.f_obj = &bp->func_obj;
	func_params.cmd = BNX2X_F_CMD_SET_TIMESYNC;

	/* Function parameters */
	set_बारync_params->drअगरt_adjust_cmd = TS_DRIFT_ADJUST_RESET;
	set_बारync_params->offset_cmd = TS_OFFSET_KEEP;

	वापस bnx2x_func_state_change(bp, &func_params);
पूर्ण

अटल पूर्णांक bnx2x_enable_ptp_packets(काष्ठा bnx2x *bp)
अणु
	काष्ठा bnx2x_queue_state_params q_params;
	पूर्णांक rc, i;

	/* send queue update ramrod to enable PTP packets */
	स_रखो(&q_params, 0, माप(q_params));
	__set_bit(RAMROD_COMP_WAIT, &q_params.ramrod_flags);
	q_params.cmd = BNX2X_Q_CMD_UPDATE;
	__set_bit(BNX2X_Q_UPDATE_PTP_PKTS_CHNG,
		  &q_params.params.update.update_flags);
	__set_bit(BNX2X_Q_UPDATE_PTP_PKTS,
		  &q_params.params.update.update_flags);

	/* send the ramrod on all the queues of the PF */
	क्रम_each_eth_queue(bp, i) अणु
		काष्ठा bnx2x_fastpath *fp = &bp->fp[i];

		/* Set the appropriate Queue object */
		q_params.q_obj = &bnx2x_sp_obj(bp, fp).q_obj;

		/* Update the Queue state */
		rc = bnx2x_queue_state_change(bp, &q_params);
		अगर (rc) अणु
			BNX2X_ERR("Failed to enable PTP packets\n");
			वापस rc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा BNX2X_P2P_DETECT_PARAM_MASK 0x5F5
#घोषणा BNX2X_P2P_DETECT_RULE_MASK 0x3DBB
#घोषणा BNX2X_PTP_TX_ON_PARAM_MASK (BNX2X_P2P_DETECT_PARAM_MASK & 0x6AA)
#घोषणा BNX2X_PTP_TX_ON_RULE_MASK (BNX2X_P2P_DETECT_RULE_MASK & 0x3EEE)
#घोषणा BNX2X_PTP_V1_L4_PARAM_MASK (BNX2X_P2P_DETECT_PARAM_MASK & 0x7EE)
#घोषणा BNX2X_PTP_V1_L4_RULE_MASK (BNX2X_P2P_DETECT_RULE_MASK & 0x3FFE)
#घोषणा BNX2X_PTP_V2_L4_PARAM_MASK (BNX2X_P2P_DETECT_PARAM_MASK & 0x7EA)
#घोषणा BNX2X_PTP_V2_L4_RULE_MASK (BNX2X_P2P_DETECT_RULE_MASK & 0x3FEE)
#घोषणा BNX2X_PTP_V2_L2_PARAM_MASK (BNX2X_P2P_DETECT_PARAM_MASK & 0x6BF)
#घोषणा BNX2X_PTP_V2_L2_RULE_MASK (BNX2X_P2P_DETECT_RULE_MASK & 0x3EFF)
#घोषणा BNX2X_PTP_V2_PARAM_MASK (BNX2X_P2P_DETECT_PARAM_MASK & 0x6AA)
#घोषणा BNX2X_PTP_V2_RULE_MASK (BNX2X_P2P_DETECT_RULE_MASK & 0x3EEE)

पूर्णांक bnx2x_configure_ptp_filters(काष्ठा bnx2x *bp)
अणु
	पूर्णांक port = BP_PORT(bp);
	u32 param, rule;
	पूर्णांक rc;

	अगर (!bp->hwtstamp_ioctl_called)
		वापस 0;

	param = port ? NIG_REG_P1_TLLH_PTP_PARAM_MASK :
		NIG_REG_P0_TLLH_PTP_PARAM_MASK;
	rule = port ? NIG_REG_P1_TLLH_PTP_RULE_MASK :
		NIG_REG_P0_TLLH_PTP_RULE_MASK;
	चयन (bp->tx_type) अणु
	हाल HWTSTAMP_TX_ON:
		bp->flags |= TX_TIMESTAMPING_EN;
		REG_WR(bp, param, BNX2X_PTP_TX_ON_PARAM_MASK);
		REG_WR(bp, rule, BNX2X_PTP_TX_ON_RULE_MASK);
		अवरोध;
	हाल HWTSTAMP_TX_ONESTEP_SYNC:
	हाल HWTSTAMP_TX_ONESTEP_P2P:
		BNX2X_ERR("One-step timestamping is not supported\n");
		वापस -दुस्फल;
	पूर्ण

	param = port ? NIG_REG_P1_LLH_PTP_PARAM_MASK :
		NIG_REG_P0_LLH_PTP_PARAM_MASK;
	rule = port ? NIG_REG_P1_LLH_PTP_RULE_MASK :
		NIG_REG_P0_LLH_PTP_RULE_MASK;
	चयन (bp->rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		अवरोध;
	हाल HWTSTAMP_FILTER_ALL:
	हाल HWTSTAMP_FILTER_SOME:
	हाल HWTSTAMP_FILTER_NTP_ALL:
		bp->rx_filter = HWTSTAMP_FILTER_NONE;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
		bp->rx_filter = HWTSTAMP_FILTER_PTP_V1_L4_EVENT;
		/* Initialize PTP detection क्रम UDP/IPv4 events */
		REG_WR(bp, param, BNX2X_PTP_V1_L4_PARAM_MASK);
		REG_WR(bp, rule, BNX2X_PTP_V1_L4_RULE_MASK);
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
		bp->rx_filter = HWTSTAMP_FILTER_PTP_V2_L4_EVENT;
		/* Initialize PTP detection क्रम UDP/IPv4 or UDP/IPv6 events */
		REG_WR(bp, param, BNX2X_PTP_V2_L4_PARAM_MASK);
		REG_WR(bp, rule, BNX2X_PTP_V2_L4_RULE_MASK);
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
		bp->rx_filter = HWTSTAMP_FILTER_PTP_V2_L2_EVENT;
		/* Initialize PTP detection L2 events */
		REG_WR(bp, param, BNX2X_PTP_V2_L2_PARAM_MASK);
		REG_WR(bp, rule, BNX2X_PTP_V2_L2_RULE_MASK);

		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
		bp->rx_filter = HWTSTAMP_FILTER_PTP_V2_EVENT;
		/* Initialize PTP detection L2, UDP/IPv4 or UDP/IPv6 events */
		REG_WR(bp, param, BNX2X_PTP_V2_PARAM_MASK);
		REG_WR(bp, rule, BNX2X_PTP_V2_RULE_MASK);
		अवरोध;
	पूर्ण

	/* Indicate to FW that this PF expects recorded PTP packets */
	rc = bnx2x_enable_ptp_packets(bp);
	अगर (rc)
		वापस rc;

	/* Enable sending PTP packets to host */
	REG_WR(bp, port ? NIG_REG_P1_LLH_PTP_TO_HOST :
	       NIG_REG_P0_LLH_PTP_TO_HOST, 0x1);

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_hwtstamp_ioctl(काष्ठा bnx2x *bp, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा hwtstamp_config config;
	पूर्णांक rc;

	DP(BNX2X_MSG_PTP, "HWTSTAMP IOCTL called\n");

	अगर (copy_from_user(&config, अगरr->अगरr_data, माप(config)))
		वापस -EFAULT;

	DP(BNX2X_MSG_PTP, "Requested tx_type: %d, requested rx_filters = %d\n",
	   config.tx_type, config.rx_filter);

	अगर (config.flags) अणु
		BNX2X_ERR("config.flags is reserved for future use\n");
		वापस -EINVAL;
	पूर्ण

	bp->hwtstamp_ioctl_called = true;
	bp->tx_type = config.tx_type;
	bp->rx_filter = config.rx_filter;

	rc = bnx2x_configure_ptp_filters(bp);
	अगर (rc)
		वापस rc;

	config.rx_filter = bp->rx_filter;

	वापस copy_to_user(अगरr->अगरr_data, &config, माप(config)) ?
		-EFAULT : 0;
पूर्ण

/* Configures HW क्रम PTP */
अटल पूर्णांक bnx2x_configure_ptp(काष्ठा bnx2x *bp)
अणु
	पूर्णांक rc, port = BP_PORT(bp);
	u32 wb_data[2];

	/* Reset PTP event detection rules - will be configured in the IOCTL */
	REG_WR(bp, port ? NIG_REG_P1_LLH_PTP_PARAM_MASK :
	       NIG_REG_P0_LLH_PTP_PARAM_MASK, 0x7FF);
	REG_WR(bp, port ? NIG_REG_P1_LLH_PTP_RULE_MASK :
	       NIG_REG_P0_LLH_PTP_RULE_MASK, 0x3FFF);
	REG_WR(bp, port ? NIG_REG_P1_TLLH_PTP_PARAM_MASK :
	       NIG_REG_P0_TLLH_PTP_PARAM_MASK, 0x7FF);
	REG_WR(bp, port ? NIG_REG_P1_TLLH_PTP_RULE_MASK :
	       NIG_REG_P0_TLLH_PTP_RULE_MASK, 0x3FFF);

	/* Disable PTP packets to host - will be configured in the IOCTL*/
	REG_WR(bp, port ? NIG_REG_P1_LLH_PTP_TO_HOST :
	       NIG_REG_P0_LLH_PTP_TO_HOST, 0x0);

	/* Enable the PTP feature */
	REG_WR(bp, port ? NIG_REG_P1_PTP_EN :
	       NIG_REG_P0_PTP_EN, 0x3F);

	/* Enable the मुक्त-running counter */
	wb_data[0] = 0;
	wb_data[1] = 0;
	REG_WR_DMAE(bp, NIG_REG_TIMESYNC_GEN_REG + tsgen_ctrl, wb_data, 2);

	/* Reset drअगरt रेजिस्टर (offset रेजिस्टर is not reset) */
	rc = bnx2x_send_reset_बारync_ramrod(bp);
	अगर (rc) अणु
		BNX2X_ERR("Failed to reset PHC drift register\n");
		वापस -EFAULT;
	पूर्ण

	/* Reset possibly old बारtamps */
	REG_WR(bp, port ? NIG_REG_P1_LLH_PTP_HOST_BUF_SEQID :
	       NIG_REG_P0_LLH_PTP_HOST_BUF_SEQID, 0x10000);
	REG_WR(bp, port ? NIG_REG_P1_TLLH_PTP_BUF_SEQID :
	       NIG_REG_P0_TLLH_PTP_BUF_SEQID, 0x10000);

	वापस 0;
पूर्ण

/* Called during load, to initialize PTP-related stuff */
व्योम bnx2x_init_ptp(काष्ठा bnx2x *bp)
अणु
	पूर्णांक rc;

	/* Configure PTP in HW */
	rc = bnx2x_configure_ptp(bp);
	अगर (rc) अणु
		BNX2X_ERR("Stopping PTP initialization\n");
		वापस;
	पूर्ण

	/* Init work queue क्रम Tx बारtamping */
	INIT_WORK(&bp->ptp_task, bnx2x_ptp_task);

	/* Init cyclecounter and समयcounter. This is करोne only in the first
	 * load. If करोne in every load, PTP application will fail when करोing
	 * unload / load (e.g. MTU change) जबतक it is running.
	 */
	अगर (!bp->समयcounter_init_करोne) अणु
		bnx2x_init_cyclecounter(bp);
		समयcounter_init(&bp->समयcounter, &bp->cyclecounter,
				 kसमय_प्रकारo_ns(kसमय_get_real()));
		bp->समयcounter_init_करोne = true;
	पूर्ण

	DP(BNX2X_MSG_PTP, "PTP initialization ended successfully\n");
पूर्ण
