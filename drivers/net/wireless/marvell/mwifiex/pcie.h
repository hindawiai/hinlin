<शैली गुरु>
/* @file mwअगरiex_pcie.h
 *
 * @brief This file contains definitions क्रम PCI-E पूर्णांकerface.
 * driver.
 *
 * Copyright 2011-2020 NXP
 *
 * This software file (the "File") is distributed by NXP
 * under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modअगरy this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available by writing to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fअगरth Floor, Boston, MA 02110-1301 USA or on the
 * worldwide web at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 * THE खाता IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 */

#अगर_अघोषित	_MWIFIEX_PCIE_H
#घोषणा	_MWIFIEX_PCIE_H

#समावेश    <linux/completion.h>
#समावेश    <linux/pci.h>
#समावेश    <linux/पूर्णांकerrupt.h>

#समावेश    "decl.h"
#समावेश    "main.h"

#घोषणा PCIE8766_DEFAULT_FW_NAME "mrvl/pcie8766_uapsta.bin"
#घोषणा PCIE8897_DEFAULT_FW_NAME "mrvl/pcie8897_uapsta.bin"
#घोषणा PCIE8897_A0_FW_NAME "mrvl/pcie8897_uapsta_a0.bin"
#घोषणा PCIE8897_B0_FW_NAME "mrvl/pcie8897_uapsta.bin"
#घोषणा PCIEUART8997_FW_NAME_V4 "mrvl/pcieuart8997_combo_v4.bin"
#घोषणा PCIEUSB8997_FW_NAME_V4 "mrvl/pcieusb8997_combo_v4.bin"

#घोषणा PCIE_VENDOR_ID_MARVELL              (0x11ab)
#घोषणा PCIE_VENDOR_ID_V2_MARVELL           (0x1b4b)
#घोषणा PCIE_DEVICE_ID_MARVELL_88W8766P		(0x2b30)
#घोषणा PCIE_DEVICE_ID_MARVELL_88W8897		(0x2b38)
#घोषणा PCIE_DEVICE_ID_MARVELL_88W8997		(0x2b42)

#घोषणा PCIE8897_A0	0x1100
#घोषणा PCIE8897_B0	0x1200
#घोषणा PCIE8997_A0	0x10
#घोषणा PCIE8997_A1	0x11
#घोषणा CHIP_VER_PCIEUART	0x3
#घोषणा CHIP_MAGIC_VALUE	0x24

/* Constants क्रम Buffer Descriptor (BD) rings */
#घोषणा MWIFIEX_MAX_TXRX_BD			0x20
#घोषणा MWIFIEX_TXBD_MASK			0x3F
#घोषणा MWIFIEX_RXBD_MASK			0x3F

#घोषणा MWIFIEX_MAX_EVT_BD			0x08
#घोषणा MWIFIEX_EVTBD_MASK			0x0f

/* PCIE INTERNAL REGISTERS */
#घोषणा PCIE_SCRATCH_0_REG				0xC10
#घोषणा PCIE_SCRATCH_1_REG				0xC14
#घोषणा PCIE_CPU_INT_EVENT				0xC18
#घोषणा PCIE_CPU_INT_STATUS				0xC1C
#घोषणा PCIE_HOST_INT_STATUS				0xC30
#घोषणा PCIE_HOST_INT_MASK				0xC34
#घोषणा PCIE_HOST_INT_STATUS_MASK			0xC3C
#घोषणा PCIE_SCRATCH_2_REG				0xC40
#घोषणा PCIE_SCRATCH_3_REG				0xC44
#घोषणा PCIE_SCRATCH_4_REG				0xCD0
#घोषणा PCIE_SCRATCH_5_REG				0xCD4
#घोषणा PCIE_SCRATCH_6_REG				0xCD8
#घोषणा PCIE_SCRATCH_7_REG				0xCDC
#घोषणा PCIE_SCRATCH_8_REG				0xCE0
#घोषणा PCIE_SCRATCH_9_REG				0xCE4
#घोषणा PCIE_SCRATCH_10_REG				0xCE8
#घोषणा PCIE_SCRATCH_11_REG				0xCEC
#घोषणा PCIE_SCRATCH_12_REG				0xCF0
#घोषणा PCIE_SCRATCH_13_REG				0xCF4
#घोषणा PCIE_SCRATCH_14_REG				0xCF8
#घोषणा PCIE_SCRATCH_15_REG				0xCFC
#घोषणा PCIE_RD_DATA_PTR_Q0_Q1                          0xC08C
#घोषणा PCIE_WR_DATA_PTR_Q0_Q1                          0xC05C

#घोषणा CPU_INTR_DNLD_RDY				BIT(0)
#घोषणा CPU_INTR_DOOR_BELL				BIT(1)
#घोषणा CPU_INTR_SLEEP_CFM_DONE			BIT(2)
#घोषणा CPU_INTR_RESET					BIT(3)
#घोषणा CPU_INTR_EVENT_DONE				BIT(5)

#घोषणा HOST_INTR_DNLD_DONE				BIT(0)
#घोषणा HOST_INTR_UPLD_RDY				BIT(1)
#घोषणा HOST_INTR_CMD_DONE				BIT(2)
#घोषणा HOST_INTR_EVENT_RDY				BIT(3)
#घोषणा HOST_INTR_MASK					(HOST_INTR_DNLD_DONE | \
							 HOST_INTR_UPLD_RDY  | \
							 HOST_INTR_CMD_DONE  | \
							 HOST_INTR_EVENT_RDY)

#घोषणा MWIFIEX_BD_FLAG_ROLLOVER_IND			BIT(7)
#घोषणा MWIFIEX_BD_FLAG_FIRST_DESC			BIT(0)
#घोषणा MWIFIEX_BD_FLAG_LAST_DESC			BIT(1)
#घोषणा MWIFIEX_BD_FLAG_SOP				BIT(0)
#घोषणा MWIFIEX_BD_FLAG_EOP				BIT(1)
#घोषणा MWIFIEX_BD_FLAG_XS_SOP				BIT(2)
#घोषणा MWIFIEX_BD_FLAG_XS_EOP				BIT(3)
#घोषणा MWIFIEX_BD_FLAG_EVT_ROLLOVER_IND		BIT(7)
#घोषणा MWIFIEX_BD_FLAG_RX_ROLLOVER_IND			BIT(10)
#घोषणा MWIFIEX_BD_FLAG_TX_START_PTR			BIT(16)
#घोषणा MWIFIEX_BD_FLAG_TX_ROLLOVER_IND			BIT(26)

/* Max retry number of command ग_लिखो */
#घोषणा MAX_WRITE_IOMEM_RETRY				2
/* Define PCIE block size क्रम firmware करोwnload */
#घोषणा MWIFIEX_PCIE_BLOCK_SIZE_FW_DNLD		256
/* FW awake cookie after FW पढ़ोy */
#घोषणा FW_AWAKE_COOKIE						(0xAA55AA55)
#घोषणा MWIFIEX_DEF_SLEEP_COOKIE			0xBEEFBEEF
#घोषणा MWIFIEX_SLEEP_COOKIE_SIZE			4
#घोषणा MWIFIEX_MAX_DELAY_COUNT				100

#घोषणा MWIFIEX_PCIE_FLR_HAPPENS 0xFEDCBABA

काष्ठा mwअगरiex_pcie_card_reg अणु
	u16 cmd_addr_lo;
	u16 cmd_addr_hi;
	u16 fw_status;
	u16 cmd_size;
	u16 cmdrsp_addr_lo;
	u16 cmdrsp_addr_hi;
	u16 tx_rdptr;
	u16 tx_wrptr;
	u16 rx_rdptr;
	u16 rx_wrptr;
	u16 evt_rdptr;
	u16 evt_wrptr;
	u16 drv_rdy;
	u16 tx_start_ptr;
	u32 tx_mask;
	u32 tx_wrap_mask;
	u32 rx_mask;
	u32 rx_wrap_mask;
	u32 tx_rollover_ind;
	u32 rx_rollover_ind;
	u32 evt_rollover_ind;
	u8 ring_flag_sop;
	u8 ring_flag_eop;
	u8 ring_flag_xs_sop;
	u8 ring_flag_xs_eop;
	u32 ring_tx_start_ptr;
	u8 pfu_enabled;
	u8 sleep_cookie;
	u16 fw_dump_ctrl;
	u16 fw_dump_start;
	u16 fw_dump_end;
	u8 fw_dump_host_पढ़ोy;
	u8 fw_dump_पढ़ो_करोne;
	u8 msix_support;
पूर्ण;

काष्ठा mwअगरiex_pcie_device अणु
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg;
	u16 blksz_fw_dl;
	u16 tx_buf_size;
	bool can_dump_fw;
	काष्ठा memory_type_mapping *mem_type_mapping_tbl;
	u8 num_mem_types;
	bool can_ext_scan;
पूर्ण;

काष्ठा mwअगरiex_evt_buf_desc अणु
	u64 paddr;
	u16 len;
	u16 flags;
पूर्ण __packed;

काष्ठा mwअगरiex_pcie_buf_desc अणु
	u64 paddr;
	u16 len;
	u16 flags;
पूर्ण __packed;

काष्ठा mwअगरiex_pfu_buf_desc अणु
	u16 flags;
	u16 offset;
	u16 frag_len;
	u16 len;
	u64 paddr;
	u32 reserved;
पूर्ण __packed;

#घोषणा MWIFIEX_NUM_MSIX_VECTORS   4

काष्ठा mwअगरiex_msix_context अणु
	काष्ठा pci_dev *dev;
	u16 msg_id;
पूर्ण;

काष्ठा pcie_service_card अणु
	काष्ठा pci_dev *dev;
	काष्ठा mwअगरiex_adapter *adapter;
	काष्ठा mwअगरiex_pcie_device pcie;
	काष्ठा completion fw_करोne;

	u8 txbd_flush;
	u32 txbd_wrptr;
	u32 txbd_rdptr;
	u32 txbd_ring_size;
	u8 *txbd_ring_vbase;
	dma_addr_t txbd_ring_pbase;
	व्योम *txbd_ring[MWIFIEX_MAX_TXRX_BD];
	काष्ठा sk_buff *tx_buf_list[MWIFIEX_MAX_TXRX_BD];

	u32 rxbd_wrptr;
	u32 rxbd_rdptr;
	u32 rxbd_ring_size;
	u8 *rxbd_ring_vbase;
	dma_addr_t rxbd_ring_pbase;
	व्योम *rxbd_ring[MWIFIEX_MAX_TXRX_BD];
	काष्ठा sk_buff *rx_buf_list[MWIFIEX_MAX_TXRX_BD];

	u32 evtbd_wrptr;
	u32 evtbd_rdptr;
	u32 evtbd_ring_size;
	u8 *evtbd_ring_vbase;
	dma_addr_t evtbd_ring_pbase;
	व्योम *evtbd_ring[MWIFIEX_MAX_EVT_BD];
	काष्ठा sk_buff *evt_buf_list[MWIFIEX_MAX_EVT_BD];

	काष्ठा sk_buff *cmd_buf;
	काष्ठा sk_buff *cmdrsp_buf;
	u8 *sleep_cookie_vbase;
	dma_addr_t sleep_cookie_pbase;
	व्योम __iomem *pci_mmap;
	व्योम __iomem *pci_mmap1;
	पूर्णांक msi_enable;
	पूर्णांक msix_enable;
#अगर_घोषित CONFIG_PCI
	काष्ठा msix_entry msix_entries[MWIFIEX_NUM_MSIX_VECTORS];
#पूर्ण_अगर
	काष्ठा mwअगरiex_msix_context msix_ctx[MWIFIEX_NUM_MSIX_VECTORS];
	काष्ठा mwअगरiex_msix_context share_irq_ctx;
	काष्ठा work_काष्ठा work;
	अचिन्हित दीर्घ work_flags;

	bool pci_reset_ongoing;
पूर्ण;

अटल अंतरभूत पूर्णांक
mwअगरiex_pcie_txbd_empty(काष्ठा pcie_service_card *card, u32 rdptr)
अणु
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg = card->pcie.reg;

	चयन (card->dev->device) अणु
	हाल PCIE_DEVICE_ID_MARVELL_88W8766P:
		अगर (((card->txbd_wrptr & reg->tx_mask) ==
		     (rdptr & reg->tx_mask)) &&
		    ((card->txbd_wrptr & reg->tx_rollover_ind) !=
		     (rdptr & reg->tx_rollover_ind)))
			वापस 1;
		अवरोध;
	हाल PCIE_DEVICE_ID_MARVELL_88W8897:
	हाल PCIE_DEVICE_ID_MARVELL_88W8997:
		अगर (((card->txbd_wrptr & reg->tx_mask) ==
		     (rdptr & reg->tx_mask)) &&
		    ((card->txbd_wrptr & reg->tx_rollover_ind) ==
			(rdptr & reg->tx_rollover_ind)))
			वापस 1;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
mwअगरiex_pcie_txbd_not_full(काष्ठा pcie_service_card *card)
अणु
	स्थिर काष्ठा mwअगरiex_pcie_card_reg *reg = card->pcie.reg;

	चयन (card->dev->device) अणु
	हाल PCIE_DEVICE_ID_MARVELL_88W8766P:
		अगर (((card->txbd_wrptr & reg->tx_mask) !=
		     (card->txbd_rdptr & reg->tx_mask)) ||
		    ((card->txbd_wrptr & reg->tx_rollover_ind) !=
		     (card->txbd_rdptr & reg->tx_rollover_ind)))
			वापस 1;
		अवरोध;
	हाल PCIE_DEVICE_ID_MARVELL_88W8897:
	हाल PCIE_DEVICE_ID_MARVELL_88W8997:
		अगर (((card->txbd_wrptr & reg->tx_mask) !=
		     (card->txbd_rdptr & reg->tx_mask)) ||
		    ((card->txbd_wrptr & reg->tx_rollover_ind) ==
		     (card->txbd_rdptr & reg->tx_rollover_ind)))
			वापस 1;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#पूर्ण_अगर /* _MWIFIEX_PCIE_H */
