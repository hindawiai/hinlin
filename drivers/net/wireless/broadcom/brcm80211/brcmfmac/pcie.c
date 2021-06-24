<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2014 Broadcom Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/firmware.h>
#समावेश <linux/pci.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/bcma/bcma.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <soc.h>
#समावेश <chipcommon.h>
#समावेश <brcmu_utils.h>
#समावेश <brcmu_wअगरi.h>
#समावेश <brcm_hw_ids.h>

/* Custom brcmf_err() that takes bus arg and passes it further */
#घोषणा brcmf_err(bus, fmt, ...)					\
	करो अणु								\
		अगर (IS_ENABLED(CONFIG_BRCMDBG) ||			\
		    IS_ENABLED(CONFIG_BRCM_TRACING) ||			\
		    net_ratelimit())					\
			__brcmf_err(bus, __func__, fmt, ##__VA_ARGS__);	\
	पूर्ण जबतक (0)

#समावेश "debug.h"
#समावेश "bus.h"
#समावेश "commonring.h"
#समावेश "msgbuf.h"
#समावेश "pcie.h"
#समावेश "firmware.h"
#समावेश "chip.h"
#समावेश "core.h"
#समावेश "common.h"


क्रमागत brcmf_pcie_state अणु
	BRCMFMAC_PCIE_STATE_DOWN,
	BRCMFMAC_PCIE_STATE_UP
पूर्ण;

BRCMF_FW_DEF(43602, "brcmfmac43602-pcie");
BRCMF_FW_DEF(4350, "brcmfmac4350-pcie");
BRCMF_FW_DEF(4350C, "brcmfmac4350c2-pcie");
BRCMF_FW_DEF(4356, "brcmfmac4356-pcie");
BRCMF_FW_DEF(43570, "brcmfmac43570-pcie");
BRCMF_FW_DEF(4358, "brcmfmac4358-pcie");
BRCMF_FW_DEF(4359, "brcmfmac4359-pcie");
BRCMF_FW_DEF(4364, "brcmfmac4364-pcie");
BRCMF_FW_DEF(4365B, "brcmfmac4365b-pcie");
BRCMF_FW_DEF(4365C, "brcmfmac4365c-pcie");
BRCMF_FW_DEF(4366B, "brcmfmac4366b-pcie");
BRCMF_FW_DEF(4366C, "brcmfmac4366c-pcie");
BRCMF_FW_DEF(4371, "brcmfmac4371-pcie");

अटल स्थिर काष्ठा brcmf_firmware_mapping brcmf_pcie_fwnames[] = अणु
	BRCMF_FW_ENTRY(BRCM_CC_43602_CHIP_ID, 0xFFFFFFFF, 43602),
	BRCMF_FW_ENTRY(BRCM_CC_43465_CHIP_ID, 0xFFFFFFF0, 4366C),
	BRCMF_FW_ENTRY(BRCM_CC_4350_CHIP_ID, 0x000000FF, 4350C),
	BRCMF_FW_ENTRY(BRCM_CC_4350_CHIP_ID, 0xFFFFFF00, 4350),
	BRCMF_FW_ENTRY(BRCM_CC_43525_CHIP_ID, 0xFFFFFFF0, 4365C),
	BRCMF_FW_ENTRY(BRCM_CC_4356_CHIP_ID, 0xFFFFFFFF, 4356),
	BRCMF_FW_ENTRY(BRCM_CC_43567_CHIP_ID, 0xFFFFFFFF, 43570),
	BRCMF_FW_ENTRY(BRCM_CC_43569_CHIP_ID, 0xFFFFFFFF, 43570),
	BRCMF_FW_ENTRY(BRCM_CC_43570_CHIP_ID, 0xFFFFFFFF, 43570),
	BRCMF_FW_ENTRY(BRCM_CC_4358_CHIP_ID, 0xFFFFFFFF, 4358),
	BRCMF_FW_ENTRY(BRCM_CC_4359_CHIP_ID, 0xFFFFFFFF, 4359),
	BRCMF_FW_ENTRY(BRCM_CC_4364_CHIP_ID, 0xFFFFFFFF, 4364),
	BRCMF_FW_ENTRY(BRCM_CC_4365_CHIP_ID, 0x0000000F, 4365B),
	BRCMF_FW_ENTRY(BRCM_CC_4365_CHIP_ID, 0xFFFFFFF0, 4365C),
	BRCMF_FW_ENTRY(BRCM_CC_4366_CHIP_ID, 0x0000000F, 4366B),
	BRCMF_FW_ENTRY(BRCM_CC_4366_CHIP_ID, 0xFFFFFFF0, 4366C),
	BRCMF_FW_ENTRY(BRCM_CC_43664_CHIP_ID, 0xFFFFFFF0, 4366C),
	BRCMF_FW_ENTRY(BRCM_CC_43666_CHIP_ID, 0xFFFFFFF0, 4366C),
	BRCMF_FW_ENTRY(BRCM_CC_4371_CHIP_ID, 0xFFFFFFFF, 4371),
पूर्ण;

#घोषणा BRCMF_PCIE_FW_UP_TIMEOUT		5000 /* msec */

#घोषणा BRCMF_PCIE_REG_MAP_SIZE			(32 * 1024)

/* backplane addres space accessed by BAR0 */
#घोषणा	BRCMF_PCIE_BAR0_WINDOW			0x80
#घोषणा BRCMF_PCIE_BAR0_REG_SIZE		0x1000
#घोषणा	BRCMF_PCIE_BAR0_WRAPPERBASE		0x70

#घोषणा BRCMF_PCIE_BAR0_WRAPBASE_DMP_OFFSET	0x1000
#घोषणा BRCMF_PCIE_BARO_PCIE_ENUM_OFFSET	0x2000

#घोषणा BRCMF_PCIE_ARMCR4REG_BANKIDX		0x40
#घोषणा BRCMF_PCIE_ARMCR4REG_BANKPDA		0x4C

#घोषणा BRCMF_PCIE_REG_INTSTATUS		0x90
#घोषणा BRCMF_PCIE_REG_INTMASK			0x94
#घोषणा BRCMF_PCIE_REG_SBMBX			0x98

#घोषणा BRCMF_PCIE_REG_LINK_STATUS_CTRL		0xBC

#घोषणा BRCMF_PCIE_PCIE2REG_INTMASK		0x24
#घोषणा BRCMF_PCIE_PCIE2REG_MAILBOXINT		0x48
#घोषणा BRCMF_PCIE_PCIE2REG_MAILBOXMASK		0x4C
#घोषणा BRCMF_PCIE_PCIE2REG_CONFIGADDR		0x120
#घोषणा BRCMF_PCIE_PCIE2REG_CONFIGDATA		0x124
#घोषणा BRCMF_PCIE_PCIE2REG_H2D_MAILBOX_0	0x140
#घोषणा BRCMF_PCIE_PCIE2REG_H2D_MAILBOX_1	0x144

#घोषणा BRCMF_PCIE2_INTA			0x01
#घोषणा BRCMF_PCIE2_INTB			0x02

#घोषणा BRCMF_PCIE_INT_0			0x01
#घोषणा BRCMF_PCIE_INT_1			0x02
#घोषणा BRCMF_PCIE_INT_DEF			(BRCMF_PCIE_INT_0 | \
						 BRCMF_PCIE_INT_1)

#घोषणा BRCMF_PCIE_MB_INT_FN0_0			0x0100
#घोषणा BRCMF_PCIE_MB_INT_FN0_1			0x0200
#घोषणा	BRCMF_PCIE_MB_INT_D2H0_DB0		0x10000
#घोषणा	BRCMF_PCIE_MB_INT_D2H0_DB1		0x20000
#घोषणा	BRCMF_PCIE_MB_INT_D2H1_DB0		0x40000
#घोषणा	BRCMF_PCIE_MB_INT_D2H1_DB1		0x80000
#घोषणा	BRCMF_PCIE_MB_INT_D2H2_DB0		0x100000
#घोषणा	BRCMF_PCIE_MB_INT_D2H2_DB1		0x200000
#घोषणा	BRCMF_PCIE_MB_INT_D2H3_DB0		0x400000
#घोषणा	BRCMF_PCIE_MB_INT_D2H3_DB1		0x800000

#घोषणा BRCMF_PCIE_MB_INT_D2H_DB		(BRCMF_PCIE_MB_INT_D2H0_DB0 | \
						 BRCMF_PCIE_MB_INT_D2H0_DB1 | \
						 BRCMF_PCIE_MB_INT_D2H1_DB0 | \
						 BRCMF_PCIE_MB_INT_D2H1_DB1 | \
						 BRCMF_PCIE_MB_INT_D2H2_DB0 | \
						 BRCMF_PCIE_MB_INT_D2H2_DB1 | \
						 BRCMF_PCIE_MB_INT_D2H3_DB0 | \
						 BRCMF_PCIE_MB_INT_D2H3_DB1)

#घोषणा BRCMF_PCIE_SHARED_VERSION_7		7
#घोषणा BRCMF_PCIE_MIN_SHARED_VERSION		5
#घोषणा BRCMF_PCIE_MAX_SHARED_VERSION		BRCMF_PCIE_SHARED_VERSION_7
#घोषणा BRCMF_PCIE_SHARED_VERSION_MASK		0x00FF
#घोषणा BRCMF_PCIE_SHARED_DMA_INDEX		0x10000
#घोषणा BRCMF_PCIE_SHARED_DMA_2B_IDX		0x100000
#घोषणा BRCMF_PCIE_SHARED_HOSTRDY_DB1		0x10000000

#घोषणा BRCMF_PCIE_FLAGS_HTOD_SPLIT		0x4000
#घोषणा BRCMF_PCIE_FLAGS_DTOH_SPLIT		0x8000

#घोषणा BRCMF_SHARED_MAX_RXBUFPOST_OFFSET	34
#घोषणा BRCMF_SHARED_RING_BASE_OFFSET		52
#घोषणा BRCMF_SHARED_RX_DATAOFFSET_OFFSET	36
#घोषणा BRCMF_SHARED_CONSOLE_ADDR_OFFSET	20
#घोषणा BRCMF_SHARED_HTOD_MB_DATA_ADDR_OFFSET	40
#घोषणा BRCMF_SHARED_DTOH_MB_DATA_ADDR_OFFSET	44
#घोषणा BRCMF_SHARED_RING_INFO_ADDR_OFFSET	48
#घोषणा BRCMF_SHARED_DMA_SCRATCH_LEN_OFFSET	52
#घोषणा BRCMF_SHARED_DMA_SCRATCH_ADDR_OFFSET	56
#घोषणा BRCMF_SHARED_DMA_RINGUPD_LEN_OFFSET	64
#घोषणा BRCMF_SHARED_DMA_RINGUPD_ADDR_OFFSET	68

#घोषणा BRCMF_RING_H2D_RING_COUNT_OFFSET	0
#घोषणा BRCMF_RING_D2H_RING_COUNT_OFFSET	1
#घोषणा BRCMF_RING_H2D_RING_MEM_OFFSET		4
#घोषणा BRCMF_RING_H2D_RING_STATE_OFFSET	8

#घोषणा BRCMF_RING_MEM_BASE_ADDR_OFFSET		8
#घोषणा BRCMF_RING_MAX_ITEM_OFFSET		4
#घोषणा BRCMF_RING_LEN_ITEMS_OFFSET		6
#घोषणा BRCMF_RING_MEM_SZ			16
#घोषणा BRCMF_RING_STATE_SZ			8

#घोषणा BRCMF_DEF_MAX_RXBUFPOST			255

#घोषणा BRCMF_CONSOLE_BUFADDR_OFFSET		8
#घोषणा BRCMF_CONSOLE_बफ_मानE_OFFSET		12
#घोषणा BRCMF_CONSOLE_WRITEIDX_OFFSET		16

#घोषणा BRCMF_DMA_D2H_SCRATCH_BUF_LEN		8
#घोषणा BRCMF_DMA_D2H_RINGUPD_BUF_LEN		1024

#घोषणा BRCMF_D2H_DEV_D3_ACK			0x00000001
#घोषणा BRCMF_D2H_DEV_DS_ENTER_REQ		0x00000002
#घोषणा BRCMF_D2H_DEV_DS_EXIT_NOTE		0x00000004
#घोषणा BRCMF_D2H_DEV_FWHALT			0x10000000

#घोषणा BRCMF_H2D_HOST_D3_INFORM		0x00000001
#घोषणा BRCMF_H2D_HOST_DS_ACK			0x00000002
#घोषणा BRCMF_H2D_HOST_D0_INFORM_IN_USE		0x00000008
#घोषणा BRCMF_H2D_HOST_D0_INFORM		0x00000010

#घोषणा BRCMF_PCIE_MBDATA_TIMEOUT		msecs_to_jअगरfies(2000)

#घोषणा BRCMF_PCIE_CFGREG_STATUS_CMD		0x4
#घोषणा BRCMF_PCIE_CFGREG_PM_CSR		0x4C
#घोषणा BRCMF_PCIE_CFGREG_MSI_CAP		0x58
#घोषणा BRCMF_PCIE_CFGREG_MSI_ADDR_L		0x5C
#घोषणा BRCMF_PCIE_CFGREG_MSI_ADDR_H		0x60
#घोषणा BRCMF_PCIE_CFGREG_MSI_DATA		0x64
#घोषणा BRCMF_PCIE_CFGREG_LINK_STATUS_CTRL	0xBC
#घोषणा BRCMF_PCIE_CFGREG_LINK_STATUS_CTRL2	0xDC
#घोषणा BRCMF_PCIE_CFGREG_RBAR_CTRL		0x228
#घोषणा BRCMF_PCIE_CFGREG_PML1_SUB_CTRL1	0x248
#घोषणा BRCMF_PCIE_CFGREG_REG_BAR2_CONFIG	0x4E0
#घोषणा BRCMF_PCIE_CFGREG_REG_BAR3_CONFIG	0x4F4
#घोषणा BRCMF_PCIE_LINK_STATUS_CTRL_ASPM_ENAB	3

/* Magic number at a magic location to find RAM size */
#घोषणा BRCMF_RAMSIZE_MAGIC			0x534d4152	/* SMAR */
#घोषणा BRCMF_RAMSIZE_OFFSET			0x6c


काष्ठा brcmf_pcie_console अणु
	u32 base_addr;
	u32 buf_addr;
	u32 bufsize;
	u32 पढ़ो_idx;
	u8 log_str[256];
	u8 log_idx;
पूर्ण;

काष्ठा brcmf_pcie_shared_info अणु
	u32 tcm_base_address;
	u32 flags;
	काष्ठा brcmf_pcie_ringbuf *commonrings[BRCMF_NROF_COMMON_MSGRINGS];
	काष्ठा brcmf_pcie_ringbuf *flowrings;
	u16 max_rxbufpost;
	u16 max_flowrings;
	u16 max_submissionrings;
	u16 max_completionrings;
	u32 rx_dataoffset;
	u32 htod_mb_data_addr;
	u32 dtoh_mb_data_addr;
	u32 ring_info_addr;
	काष्ठा brcmf_pcie_console console;
	व्योम *scratch;
	dma_addr_t scratch_dmahandle;
	व्योम *ringupd;
	dma_addr_t ringupd_dmahandle;
	u8 version;
पूर्ण;

काष्ठा brcmf_pcie_core_info अणु
	u32 base;
	u32 wrapbase;
पूर्ण;

काष्ठा brcmf_pciedev_info अणु
	क्रमागत brcmf_pcie_state state;
	bool in_irq;
	काष्ठा pci_dev *pdev;
	अक्षर fw_name[BRCMF_FW_NAME_LEN];
	अक्षर nvram_name[BRCMF_FW_NAME_LEN];
	व्योम __iomem *regs;
	व्योम __iomem *tcm;
	u32 ram_base;
	u32 ram_size;
	काष्ठा brcmf_chip *ci;
	u32 coreid;
	काष्ठा brcmf_pcie_shared_info shared;
	रुको_queue_head_t mbdata_resp_रुको;
	bool mbdata_completed;
	bool irq_allocated;
	bool wowl_enabled;
	u8 dma_idx_sz;
	व्योम *idxbuf;
	u32 idxbuf_sz;
	dma_addr_t idxbuf_dmahandle;
	u16 (*पढ़ो_ptr)(काष्ठा brcmf_pciedev_info *devinfo, u32 mem_offset);
	व्योम (*ग_लिखो_ptr)(काष्ठा brcmf_pciedev_info *devinfo, u32 mem_offset,
			  u16 value);
	काष्ठा brcmf_mp_device *settings;
पूर्ण;

काष्ठा brcmf_pcie_ringbuf अणु
	काष्ठा brcmf_commonring commonring;
	dma_addr_t dma_handle;
	u32 w_idx_addr;
	u32 r_idx_addr;
	काष्ठा brcmf_pciedev_info *devinfo;
	u8 id;
पूर्ण;

/**
 * काष्ठा brcmf_pcie_dhi_ringinfo - करोngle/host पूर्णांकerface shared ring info
 *
 * @ringmem: करोngle memory poपूर्णांकer to ring memory location
 * @h2d_w_idx_ptr: h2d ring ग_लिखो indices करोngle memory poपूर्णांकers
 * @h2d_r_idx_ptr: h2d ring पढ़ो indices करोngle memory poपूर्णांकers
 * @d2h_w_idx_ptr: d2h ring ग_लिखो indices करोngle memory poपूर्णांकers
 * @d2h_r_idx_ptr: d2h ring पढ़ो indices करोngle memory poपूर्णांकers
 * @h2d_w_idx_hostaddr: h2d ring ग_लिखो indices host memory poपूर्णांकers
 * @h2d_r_idx_hostaddr: h2d ring पढ़ो indices host memory poपूर्णांकers
 * @d2h_w_idx_hostaddr: d2h ring ग_लिखो indices host memory poपूर्णांकers
 * @d2h_r_idx_hostaddr: d2h ring reaD indices host memory poपूर्णांकers
 * @max_flowrings: maximum number of tx flow rings supported.
 * @max_submissionrings: maximum number of submission rings(h2d) supported.
 * @max_completionrings: maximum number of completion rings(d2h) supported.
 */
काष्ठा brcmf_pcie_dhi_ringinfo अणु
	__le32			ringmem;
	__le32			h2d_w_idx_ptr;
	__le32			h2d_r_idx_ptr;
	__le32			d2h_w_idx_ptr;
	__le32			d2h_r_idx_ptr;
	काष्ठा msgbuf_buf_addr	h2d_w_idx_hostaddr;
	काष्ठा msgbuf_buf_addr	h2d_r_idx_hostaddr;
	काष्ठा msgbuf_buf_addr	d2h_w_idx_hostaddr;
	काष्ठा msgbuf_buf_addr	d2h_r_idx_hostaddr;
	__le16			max_flowrings;
	__le16			max_submissionrings;
	__le16			max_completionrings;
पूर्ण;

अटल स्थिर u32 brcmf_ring_max_item[BRCMF_NROF_COMMON_MSGRINGS] = अणु
	BRCMF_H2D_MSGRING_CONTROL_SUBMIT_MAX_ITEM,
	BRCMF_H2D_MSGRING_RXPOST_SUBMIT_MAX_ITEM,
	BRCMF_D2H_MSGRING_CONTROL_COMPLETE_MAX_ITEM,
	BRCMF_D2H_MSGRING_TX_COMPLETE_MAX_ITEM,
	BRCMF_D2H_MSGRING_RX_COMPLETE_MAX_ITEM
पूर्ण;

अटल स्थिर u32 brcmf_ring_itemsize_pre_v7[BRCMF_NROF_COMMON_MSGRINGS] = अणु
	BRCMF_H2D_MSGRING_CONTROL_SUBMIT_ITEMSIZE,
	BRCMF_H2D_MSGRING_RXPOST_SUBMIT_ITEMSIZE,
	BRCMF_D2H_MSGRING_CONTROL_COMPLETE_ITEMSIZE,
	BRCMF_D2H_MSGRING_TX_COMPLETE_ITEMSIZE_PRE_V7,
	BRCMF_D2H_MSGRING_RX_COMPLETE_ITEMSIZE_PRE_V7
पूर्ण;

अटल स्थिर u32 brcmf_ring_itemsize[BRCMF_NROF_COMMON_MSGRINGS] = अणु
	BRCMF_H2D_MSGRING_CONTROL_SUBMIT_ITEMSIZE,
	BRCMF_H2D_MSGRING_RXPOST_SUBMIT_ITEMSIZE,
	BRCMF_D2H_MSGRING_CONTROL_COMPLETE_ITEMSIZE,
	BRCMF_D2H_MSGRING_TX_COMPLETE_ITEMSIZE,
	BRCMF_D2H_MSGRING_RX_COMPLETE_ITEMSIZE
पूर्ण;

अटल व्योम brcmf_pcie_setup(काष्ठा device *dev, पूर्णांक ret,
			     काष्ठा brcmf_fw_request *fwreq);
अटल काष्ठा brcmf_fw_request *
brcmf_pcie_prepare_fw_request(काष्ठा brcmf_pciedev_info *devinfo);

अटल u32
brcmf_pcie_पढ़ो_reg32(काष्ठा brcmf_pciedev_info *devinfo, u32 reg_offset)
अणु
	व्योम __iomem *address = devinfo->regs + reg_offset;

	वापस (ioपढ़ो32(address));
पूर्ण


अटल व्योम
brcmf_pcie_ग_लिखो_reg32(काष्ठा brcmf_pciedev_info *devinfo, u32 reg_offset,
		       u32 value)
अणु
	व्योम __iomem *address = devinfo->regs + reg_offset;

	ioग_लिखो32(value, address);
पूर्ण


अटल u8
brcmf_pcie_पढ़ो_tcm8(काष्ठा brcmf_pciedev_info *devinfo, u32 mem_offset)
अणु
	व्योम __iomem *address = devinfo->tcm + mem_offset;

	वापस (ioपढ़ो8(address));
पूर्ण


अटल u16
brcmf_pcie_पढ़ो_tcm16(काष्ठा brcmf_pciedev_info *devinfo, u32 mem_offset)
अणु
	व्योम __iomem *address = devinfo->tcm + mem_offset;

	वापस (ioपढ़ो16(address));
पूर्ण


अटल व्योम
brcmf_pcie_ग_लिखो_tcm16(काष्ठा brcmf_pciedev_info *devinfo, u32 mem_offset,
		       u16 value)
अणु
	व्योम __iomem *address = devinfo->tcm + mem_offset;

	ioग_लिखो16(value, address);
पूर्ण


अटल u16
brcmf_pcie_पढ़ो_idx(काष्ठा brcmf_pciedev_info *devinfo, u32 mem_offset)
अणु
	u16 *address = devinfo->idxbuf + mem_offset;

	वापस (*(address));
पूर्ण


अटल व्योम
brcmf_pcie_ग_लिखो_idx(काष्ठा brcmf_pciedev_info *devinfo, u32 mem_offset,
		     u16 value)
अणु
	u16 *address = devinfo->idxbuf + mem_offset;

	*(address) = value;
पूर्ण


अटल u32
brcmf_pcie_पढ़ो_tcm32(काष्ठा brcmf_pciedev_info *devinfo, u32 mem_offset)
अणु
	व्योम __iomem *address = devinfo->tcm + mem_offset;

	वापस (ioपढ़ो32(address));
पूर्ण


अटल व्योम
brcmf_pcie_ग_लिखो_tcm32(काष्ठा brcmf_pciedev_info *devinfo, u32 mem_offset,
		       u32 value)
अणु
	व्योम __iomem *address = devinfo->tcm + mem_offset;

	ioग_लिखो32(value, address);
पूर्ण


अटल u32
brcmf_pcie_पढ़ो_ram32(काष्ठा brcmf_pciedev_info *devinfo, u32 mem_offset)
अणु
	व्योम __iomem *addr = devinfo->tcm + devinfo->ci->rambase + mem_offset;

	वापस (ioपढ़ो32(addr));
पूर्ण


अटल व्योम
brcmf_pcie_ग_लिखो_ram32(काष्ठा brcmf_pciedev_info *devinfo, u32 mem_offset,
		       u32 value)
अणु
	व्योम __iomem *addr = devinfo->tcm + devinfo->ci->rambase + mem_offset;

	ioग_लिखो32(value, addr);
पूर्ण


अटल व्योम
brcmf_pcie_copy_mem_todev(काष्ठा brcmf_pciedev_info *devinfo, u32 mem_offset,
			  व्योम *srcaddr, u32 len)
अणु
	व्योम __iomem *address = devinfo->tcm + mem_offset;
	__le32 *src32;
	__le16 *src16;
	u8 *src8;

	अगर (((uदीर्घ)address & 4) || ((uदीर्घ)srcaddr & 4) || (len & 4)) अणु
		अगर (((uदीर्घ)address & 2) || ((uदीर्घ)srcaddr & 2) || (len & 2)) अणु
			src8 = (u8 *)srcaddr;
			जबतक (len) अणु
				ioग_लिखो8(*src8, address);
				address++;
				src8++;
				len--;
			पूर्ण
		पूर्ण अन्यथा अणु
			len = len / 2;
			src16 = (__le16 *)srcaddr;
			जबतक (len) अणु
				ioग_लिखो16(le16_to_cpu(*src16), address);
				address += 2;
				src16++;
				len--;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		len = len / 4;
		src32 = (__le32 *)srcaddr;
		जबतक (len) अणु
			ioग_लिखो32(le32_to_cpu(*src32), address);
			address += 4;
			src32++;
			len--;
		पूर्ण
	पूर्ण
पूर्ण


अटल व्योम
brcmf_pcie_copy_dev_tomem(काष्ठा brcmf_pciedev_info *devinfo, u32 mem_offset,
			  व्योम *dstaddr, u32 len)
अणु
	व्योम __iomem *address = devinfo->tcm + mem_offset;
	__le32 *dst32;
	__le16 *dst16;
	u8 *dst8;

	अगर (((uदीर्घ)address & 4) || ((uदीर्घ)dstaddr & 4) || (len & 4)) अणु
		अगर (((uदीर्घ)address & 2) || ((uदीर्घ)dstaddr & 2) || (len & 2)) अणु
			dst8 = (u8 *)dstaddr;
			जबतक (len) अणु
				*dst8 = ioपढ़ो8(address);
				address++;
				dst8++;
				len--;
			पूर्ण
		पूर्ण अन्यथा अणु
			len = len / 2;
			dst16 = (__le16 *)dstaddr;
			जबतक (len) अणु
				*dst16 = cpu_to_le16(ioपढ़ो16(address));
				address += 2;
				dst16++;
				len--;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		len = len / 4;
		dst32 = (__le32 *)dstaddr;
		जबतक (len) अणु
			*dst32 = cpu_to_le32(ioपढ़ो32(address));
			address += 4;
			dst32++;
			len--;
		पूर्ण
	पूर्ण
पूर्ण


#घोषणा WRITECC32(devinfo, reg, value) brcmf_pcie_ग_लिखो_reg32(devinfo, \
		CHIPCREGOFFS(reg), value)


अटल व्योम
brcmf_pcie_select_core(काष्ठा brcmf_pciedev_info *devinfo, u16 coreid)
अणु
	स्थिर काष्ठा pci_dev *pdev = devinfo->pdev;
	काष्ठा brcmf_bus *bus = dev_get_drvdata(&pdev->dev);
	काष्ठा brcmf_core *core;
	u32 bar0_win;

	core = brcmf_chip_get_core(devinfo->ci, coreid);
	अगर (core) अणु
		bar0_win = core->base;
		pci_ग_लिखो_config_dword(pdev, BRCMF_PCIE_BAR0_WINDOW, bar0_win);
		अगर (pci_पढ़ो_config_dword(pdev, BRCMF_PCIE_BAR0_WINDOW,
					  &bar0_win) == 0) अणु
			अगर (bar0_win != core->base) अणु
				bar0_win = core->base;
				pci_ग_लिखो_config_dword(pdev,
						       BRCMF_PCIE_BAR0_WINDOW,
						       bar0_win);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		brcmf_err(bus, "Unsupported core selected %x\n", coreid);
	पूर्ण
पूर्ण


अटल व्योम brcmf_pcie_reset_device(काष्ठा brcmf_pciedev_info *devinfo)
अणु
	काष्ठा brcmf_core *core;
	u16 cfg_offset[] = अणु BRCMF_PCIE_CFGREG_STATUS_CMD,
			     BRCMF_PCIE_CFGREG_PM_CSR,
			     BRCMF_PCIE_CFGREG_MSI_CAP,
			     BRCMF_PCIE_CFGREG_MSI_ADDR_L,
			     BRCMF_PCIE_CFGREG_MSI_ADDR_H,
			     BRCMF_PCIE_CFGREG_MSI_DATA,
			     BRCMF_PCIE_CFGREG_LINK_STATUS_CTRL2,
			     BRCMF_PCIE_CFGREG_RBAR_CTRL,
			     BRCMF_PCIE_CFGREG_PML1_SUB_CTRL1,
			     BRCMF_PCIE_CFGREG_REG_BAR2_CONFIG,
			     BRCMF_PCIE_CFGREG_REG_BAR3_CONFIG पूर्ण;
	u32 i;
	u32 val;
	u32 lsc;

	अगर (!devinfo->ci)
		वापस;

	/* Disable ASPM */
	brcmf_pcie_select_core(devinfo, BCMA_CORE_PCIE2);
	pci_पढ़ो_config_dword(devinfo->pdev, BRCMF_PCIE_REG_LINK_STATUS_CTRL,
			      &lsc);
	val = lsc & (~BRCMF_PCIE_LINK_STATUS_CTRL_ASPM_ENAB);
	pci_ग_लिखो_config_dword(devinfo->pdev, BRCMF_PCIE_REG_LINK_STATUS_CTRL,
			       val);

	/* Watchकरोg reset */
	brcmf_pcie_select_core(devinfo, BCMA_CORE_CHIPCOMMON);
	WRITECC32(devinfo, watchकरोg, 4);
	msleep(100);

	/* Restore ASPM */
	brcmf_pcie_select_core(devinfo, BCMA_CORE_PCIE2);
	pci_ग_लिखो_config_dword(devinfo->pdev, BRCMF_PCIE_REG_LINK_STATUS_CTRL,
			       lsc);

	core = brcmf_chip_get_core(devinfo->ci, BCMA_CORE_PCIE2);
	अगर (core->rev <= 13) अणु
		क्रम (i = 0; i < ARRAY_SIZE(cfg_offset); i++) अणु
			brcmf_pcie_ग_लिखो_reg32(devinfo,
					       BRCMF_PCIE_PCIE2REG_CONFIGADDR,
					       cfg_offset[i]);
			val = brcmf_pcie_पढ़ो_reg32(devinfo,
				BRCMF_PCIE_PCIE2REG_CONFIGDATA);
			brcmf_dbg(PCIE, "config offset 0x%04x, value 0x%04x\n",
				  cfg_offset[i], val);
			brcmf_pcie_ग_लिखो_reg32(devinfo,
					       BRCMF_PCIE_PCIE2REG_CONFIGDATA,
					       val);
		पूर्ण
	पूर्ण
पूर्ण


अटल व्योम brcmf_pcie_attach(काष्ठा brcmf_pciedev_info *devinfo)
अणु
	u32 config;

	/* BAR1 winकरोw may not be sized properly */
	brcmf_pcie_select_core(devinfo, BCMA_CORE_PCIE2);
	brcmf_pcie_ग_लिखो_reg32(devinfo, BRCMF_PCIE_PCIE2REG_CONFIGADDR, 0x4e0);
	config = brcmf_pcie_पढ़ो_reg32(devinfo, BRCMF_PCIE_PCIE2REG_CONFIGDATA);
	brcmf_pcie_ग_लिखो_reg32(devinfo, BRCMF_PCIE_PCIE2REG_CONFIGDATA, config);

	device_wakeup_enable(&devinfo->pdev->dev);
पूर्ण


अटल पूर्णांक brcmf_pcie_enter_करोwnload_state(काष्ठा brcmf_pciedev_info *devinfo)
अणु
	अगर (devinfo->ci->chip == BRCM_CC_43602_CHIP_ID) अणु
		brcmf_pcie_select_core(devinfo, BCMA_CORE_ARM_CR4);
		brcmf_pcie_ग_लिखो_reg32(devinfo, BRCMF_PCIE_ARMCR4REG_BANKIDX,
				       5);
		brcmf_pcie_ग_लिखो_reg32(devinfo, BRCMF_PCIE_ARMCR4REG_BANKPDA,
				       0);
		brcmf_pcie_ग_लिखो_reg32(devinfo, BRCMF_PCIE_ARMCR4REG_BANKIDX,
				       7);
		brcmf_pcie_ग_लिखो_reg32(devinfo, BRCMF_PCIE_ARMCR4REG_BANKPDA,
				       0);
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक brcmf_pcie_निकास_करोwnload_state(काष्ठा brcmf_pciedev_info *devinfo,
					  u32 resetपूर्णांकr)
अणु
	काष्ठा brcmf_core *core;

	अगर (devinfo->ci->chip == BRCM_CC_43602_CHIP_ID) अणु
		core = brcmf_chip_get_core(devinfo->ci, BCMA_CORE_INTERNAL_MEM);
		brcmf_chip_resetcore(core, 0, 0, 0);
	पूर्ण

	अगर (!brcmf_chip_set_active(devinfo->ci, resetपूर्णांकr))
		वापस -EINVAL;
	वापस 0;
पूर्ण


अटल पूर्णांक
brcmf_pcie_send_mb_data(काष्ठा brcmf_pciedev_info *devinfo, u32 htod_mb_data)
अणु
	काष्ठा brcmf_pcie_shared_info *shared;
	काष्ठा brcmf_core *core;
	u32 addr;
	u32 cur_htod_mb_data;
	u32 i;

	shared = &devinfo->shared;
	addr = shared->htod_mb_data_addr;
	cur_htod_mb_data = brcmf_pcie_पढ़ो_tcm32(devinfo, addr);

	अगर (cur_htod_mb_data != 0)
		brcmf_dbg(PCIE, "MB transaction is already pending 0x%04x\n",
			  cur_htod_mb_data);

	i = 0;
	जबतक (cur_htod_mb_data != 0) अणु
		msleep(10);
		i++;
		अगर (i > 100)
			वापस -EIO;
		cur_htod_mb_data = brcmf_pcie_पढ़ो_tcm32(devinfo, addr);
	पूर्ण

	brcmf_pcie_ग_लिखो_tcm32(devinfo, addr, htod_mb_data);
	pci_ग_लिखो_config_dword(devinfo->pdev, BRCMF_PCIE_REG_SBMBX, 1);

	/* Send mailbox पूर्णांकerrupt twice as a hardware workaround */
	core = brcmf_chip_get_core(devinfo->ci, BCMA_CORE_PCIE2);
	अगर (core->rev <= 13)
		pci_ग_लिखो_config_dword(devinfo->pdev, BRCMF_PCIE_REG_SBMBX, 1);

	वापस 0;
पूर्ण


अटल व्योम brcmf_pcie_handle_mb_data(काष्ठा brcmf_pciedev_info *devinfo)
अणु
	काष्ठा brcmf_pcie_shared_info *shared;
	u32 addr;
	u32 dtoh_mb_data;

	shared = &devinfo->shared;
	addr = shared->dtoh_mb_data_addr;
	dtoh_mb_data = brcmf_pcie_पढ़ो_tcm32(devinfo, addr);

	अगर (!dtoh_mb_data)
		वापस;

	brcmf_pcie_ग_लिखो_tcm32(devinfo, addr, 0);

	brcmf_dbg(PCIE, "D2H_MB_DATA: 0x%04x\n", dtoh_mb_data);
	अगर (dtoh_mb_data & BRCMF_D2H_DEV_DS_ENTER_REQ)  अणु
		brcmf_dbg(PCIE, "D2H_MB_DATA: DEEP SLEEP REQ\n");
		brcmf_pcie_send_mb_data(devinfo, BRCMF_H2D_HOST_DS_ACK);
		brcmf_dbg(PCIE, "D2H_MB_DATA: sent DEEP SLEEP ACK\n");
	पूर्ण
	अगर (dtoh_mb_data & BRCMF_D2H_DEV_DS_EXIT_NOTE)
		brcmf_dbg(PCIE, "D2H_MB_DATA: DEEP SLEEP EXIT\n");
	अगर (dtoh_mb_data & BRCMF_D2H_DEV_D3_ACK) अणु
		brcmf_dbg(PCIE, "D2H_MB_DATA: D3 ACK\n");
		devinfo->mbdata_completed = true;
		wake_up(&devinfo->mbdata_resp_रुको);
	पूर्ण
	अगर (dtoh_mb_data & BRCMF_D2H_DEV_FWHALT) अणु
		brcmf_dbg(PCIE, "D2H_MB_DATA: FW HALT\n");
		brcmf_fw_crashed(&devinfo->pdev->dev);
	पूर्ण
पूर्ण


अटल व्योम brcmf_pcie_bus_console_init(काष्ठा brcmf_pciedev_info *devinfo)
अणु
	काष्ठा brcmf_pcie_shared_info *shared;
	काष्ठा brcmf_pcie_console *console;
	u32 addr;

	shared = &devinfo->shared;
	console = &shared->console;
	addr = shared->tcm_base_address + BRCMF_SHARED_CONSOLE_ADDR_OFFSET;
	console->base_addr = brcmf_pcie_पढ़ो_tcm32(devinfo, addr);

	addr = console->base_addr + BRCMF_CONSOLE_BUFADDR_OFFSET;
	console->buf_addr = brcmf_pcie_पढ़ो_tcm32(devinfo, addr);
	addr = console->base_addr + BRCMF_CONSOLE_बफ_मानE_OFFSET;
	console->bufsize = brcmf_pcie_पढ़ो_tcm32(devinfo, addr);

	brcmf_dbg(FWCON, "Console: base %x, buf %x, size %d\n",
		  console->base_addr, console->buf_addr, console->bufsize);
पूर्ण

/**
 * brcmf_pcie_bus_console_पढ़ो - पढ़ोs firmware messages
 *
 * @devinfo: poपूर्णांकer to the device data काष्ठाure
 * @error: specअगरies अगर error has occurred (prपूर्णांकs messages unconditionally)
 */
अटल व्योम brcmf_pcie_bus_console_पढ़ो(काष्ठा brcmf_pciedev_info *devinfo,
					bool error)
अणु
	काष्ठा pci_dev *pdev = devinfo->pdev;
	काष्ठा brcmf_bus *bus = dev_get_drvdata(&pdev->dev);
	काष्ठा brcmf_pcie_console *console;
	u32 addr;
	u8 ch;
	u32 newidx;

	अगर (!error && !BRCMF_FWCON_ON())
		वापस;

	console = &devinfo->shared.console;
	addr = console->base_addr + BRCMF_CONSOLE_WRITEIDX_OFFSET;
	newidx = brcmf_pcie_पढ़ो_tcm32(devinfo, addr);
	जबतक (newidx != console->पढ़ो_idx) अणु
		addr = console->buf_addr + console->पढ़ो_idx;
		ch = brcmf_pcie_पढ़ो_tcm8(devinfo, addr);
		console->पढ़ो_idx++;
		अगर (console->पढ़ो_idx == console->bufsize)
			console->पढ़ो_idx = 0;
		अगर (ch == '\r')
			जारी;
		console->log_str[console->log_idx] = ch;
		console->log_idx++;
		अगर ((ch != '\n') &&
		    (console->log_idx == (माप(console->log_str) - 2))) अणु
			ch = '\n';
			console->log_str[console->log_idx] = ch;
			console->log_idx++;
		पूर्ण
		अगर (ch == '\n') अणु
			console->log_str[console->log_idx] = 0;
			अगर (error)
				__brcmf_err(bus, __func__, "CONSOLE: %s",
					    console->log_str);
			अन्यथा
				pr_debug("CONSOLE: %s", console->log_str);
			console->log_idx = 0;
		पूर्ण
	पूर्ण
पूर्ण


अटल व्योम brcmf_pcie_पूर्णांकr_disable(काष्ठा brcmf_pciedev_info *devinfo)
अणु
	brcmf_pcie_ग_लिखो_reg32(devinfo, BRCMF_PCIE_PCIE2REG_MAILBOXMASK, 0);
पूर्ण


अटल व्योम brcmf_pcie_पूर्णांकr_enable(काष्ठा brcmf_pciedev_info *devinfo)
अणु
	brcmf_pcie_ग_लिखो_reg32(devinfo, BRCMF_PCIE_PCIE2REG_MAILBOXMASK,
			       BRCMF_PCIE_MB_INT_D2H_DB |
			       BRCMF_PCIE_MB_INT_FN0_0 |
			       BRCMF_PCIE_MB_INT_FN0_1);
पूर्ण

अटल व्योम brcmf_pcie_hostपढ़ोy(काष्ठा brcmf_pciedev_info *devinfo)
अणु
	अगर (devinfo->shared.flags & BRCMF_PCIE_SHARED_HOSTRDY_DB1)
		brcmf_pcie_ग_लिखो_reg32(devinfo,
				       BRCMF_PCIE_PCIE2REG_H2D_MAILBOX_1, 1);
पूर्ण

अटल irqवापस_t brcmf_pcie_quick_check_isr(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा brcmf_pciedev_info *devinfo = (काष्ठा brcmf_pciedev_info *)arg;

	अगर (brcmf_pcie_पढ़ो_reg32(devinfo, BRCMF_PCIE_PCIE2REG_MAILBOXINT)) अणु
		brcmf_pcie_पूर्णांकr_disable(devinfo);
		brcmf_dbg(PCIE, "Enter\n");
		वापस IRQ_WAKE_THREAD;
	पूर्ण
	वापस IRQ_NONE;
पूर्ण


अटल irqवापस_t brcmf_pcie_isr_thपढ़ो(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा brcmf_pciedev_info *devinfo = (काष्ठा brcmf_pciedev_info *)arg;
	u32 status;

	devinfo->in_irq = true;
	status = brcmf_pcie_पढ़ो_reg32(devinfo, BRCMF_PCIE_PCIE2REG_MAILBOXINT);
	brcmf_dbg(PCIE, "Enter %x\n", status);
	अगर (status) अणु
		brcmf_pcie_ग_लिखो_reg32(devinfo, BRCMF_PCIE_PCIE2REG_MAILBOXINT,
				       status);
		अगर (status & (BRCMF_PCIE_MB_INT_FN0_0 |
			      BRCMF_PCIE_MB_INT_FN0_1))
			brcmf_pcie_handle_mb_data(devinfo);
		अगर (status & BRCMF_PCIE_MB_INT_D2H_DB) अणु
			अगर (devinfo->state == BRCMFMAC_PCIE_STATE_UP)
				brcmf_proto_msgbuf_rx_trigger(
							&devinfo->pdev->dev);
		पूर्ण
	पूर्ण
	brcmf_pcie_bus_console_पढ़ो(devinfo, false);
	अगर (devinfo->state == BRCMFMAC_PCIE_STATE_UP)
		brcmf_pcie_पूर्णांकr_enable(devinfo);
	devinfo->in_irq = false;
	वापस IRQ_HANDLED;
पूर्ण


अटल पूर्णांक brcmf_pcie_request_irq(काष्ठा brcmf_pciedev_info *devinfo)
अणु
	काष्ठा pci_dev *pdev = devinfo->pdev;
	काष्ठा brcmf_bus *bus = dev_get_drvdata(&pdev->dev);

	brcmf_pcie_पूर्णांकr_disable(devinfo);

	brcmf_dbg(PCIE, "Enter\n");

	pci_enable_msi(pdev);
	अगर (request_thपढ़ोed_irq(pdev->irq, brcmf_pcie_quick_check_isr,
				 brcmf_pcie_isr_thपढ़ो, IRQF_SHARED,
				 "brcmf_pcie_intr", devinfo)) अणु
		pci_disable_msi(pdev);
		brcmf_err(bus, "Failed to request IRQ %d\n", pdev->irq);
		वापस -EIO;
	पूर्ण
	devinfo->irq_allocated = true;
	वापस 0;
पूर्ण


अटल व्योम brcmf_pcie_release_irq(काष्ठा brcmf_pciedev_info *devinfo)
अणु
	काष्ठा pci_dev *pdev = devinfo->pdev;
	काष्ठा brcmf_bus *bus = dev_get_drvdata(&pdev->dev);
	u32 status;
	u32 count;

	अगर (!devinfo->irq_allocated)
		वापस;

	brcmf_pcie_पूर्णांकr_disable(devinfo);
	मुक्त_irq(pdev->irq, devinfo);
	pci_disable_msi(pdev);

	msleep(50);
	count = 0;
	जबतक ((devinfo->in_irq) && (count < 20)) अणु
		msleep(50);
		count++;
	पूर्ण
	अगर (devinfo->in_irq)
		brcmf_err(bus, "Still in IRQ (processing) !!!\n");

	status = brcmf_pcie_पढ़ो_reg32(devinfo, BRCMF_PCIE_PCIE2REG_MAILBOXINT);
	brcmf_pcie_ग_लिखो_reg32(devinfo, BRCMF_PCIE_PCIE2REG_MAILBOXINT, status);

	devinfo->irq_allocated = false;
पूर्ण


अटल पूर्णांक brcmf_pcie_ring_mb_ग_लिखो_rptr(व्योम *ctx)
अणु
	काष्ठा brcmf_pcie_ringbuf *ring = (काष्ठा brcmf_pcie_ringbuf *)ctx;
	काष्ठा brcmf_pciedev_info *devinfo = ring->devinfo;
	काष्ठा brcmf_commonring *commonring = &ring->commonring;

	अगर (devinfo->state != BRCMFMAC_PCIE_STATE_UP)
		वापस -EIO;

	brcmf_dbg(PCIE, "W r_ptr %d (%d), ring %d\n", commonring->r_ptr,
		  commonring->w_ptr, ring->id);

	devinfo->ग_लिखो_ptr(devinfo, ring->r_idx_addr, commonring->r_ptr);

	वापस 0;
पूर्ण


अटल पूर्णांक brcmf_pcie_ring_mb_ग_लिखो_wptr(व्योम *ctx)
अणु
	काष्ठा brcmf_pcie_ringbuf *ring = (काष्ठा brcmf_pcie_ringbuf *)ctx;
	काष्ठा brcmf_pciedev_info *devinfo = ring->devinfo;
	काष्ठा brcmf_commonring *commonring = &ring->commonring;

	अगर (devinfo->state != BRCMFMAC_PCIE_STATE_UP)
		वापस -EIO;

	brcmf_dbg(PCIE, "W w_ptr %d (%d), ring %d\n", commonring->w_ptr,
		  commonring->r_ptr, ring->id);

	devinfo->ग_लिखो_ptr(devinfo, ring->w_idx_addr, commonring->w_ptr);

	वापस 0;
पूर्ण


अटल पूर्णांक brcmf_pcie_ring_mb_ring_bell(व्योम *ctx)
अणु
	काष्ठा brcmf_pcie_ringbuf *ring = (काष्ठा brcmf_pcie_ringbuf *)ctx;
	काष्ठा brcmf_pciedev_info *devinfo = ring->devinfo;

	अगर (devinfo->state != BRCMFMAC_PCIE_STATE_UP)
		वापस -EIO;

	brcmf_dbg(PCIE, "RING !\n");
	/* Any arbitrary value will करो, lets use 1 */
	brcmf_pcie_ग_लिखो_reg32(devinfo, BRCMF_PCIE_PCIE2REG_H2D_MAILBOX_0, 1);

	वापस 0;
पूर्ण


अटल पूर्णांक brcmf_pcie_ring_mb_update_rptr(व्योम *ctx)
अणु
	काष्ठा brcmf_pcie_ringbuf *ring = (काष्ठा brcmf_pcie_ringbuf *)ctx;
	काष्ठा brcmf_pciedev_info *devinfo = ring->devinfo;
	काष्ठा brcmf_commonring *commonring = &ring->commonring;

	अगर (devinfo->state != BRCMFMAC_PCIE_STATE_UP)
		वापस -EIO;

	commonring->r_ptr = devinfo->पढ़ो_ptr(devinfo, ring->r_idx_addr);

	brcmf_dbg(PCIE, "R r_ptr %d (%d), ring %d\n", commonring->r_ptr,
		  commonring->w_ptr, ring->id);

	वापस 0;
पूर्ण


अटल पूर्णांक brcmf_pcie_ring_mb_update_wptr(व्योम *ctx)
अणु
	काष्ठा brcmf_pcie_ringbuf *ring = (काष्ठा brcmf_pcie_ringbuf *)ctx;
	काष्ठा brcmf_pciedev_info *devinfo = ring->devinfo;
	काष्ठा brcmf_commonring *commonring = &ring->commonring;

	अगर (devinfo->state != BRCMFMAC_PCIE_STATE_UP)
		वापस -EIO;

	commonring->w_ptr = devinfo->पढ़ो_ptr(devinfo, ring->w_idx_addr);

	brcmf_dbg(PCIE, "R w_ptr %d (%d), ring %d\n", commonring->w_ptr,
		  commonring->r_ptr, ring->id);

	वापस 0;
पूर्ण


अटल व्योम *
brcmf_pcie_init_dmabuffer_क्रम_device(काष्ठा brcmf_pciedev_info *devinfo,
				     u32 size, u32 tcm_dma_phys_addr,
				     dma_addr_t *dma_handle)
अणु
	व्योम *ring;
	u64 address;

	ring = dma_alloc_coherent(&devinfo->pdev->dev, size, dma_handle,
				  GFP_KERNEL);
	अगर (!ring)
		वापस शून्य;

	address = (u64)*dma_handle;
	brcmf_pcie_ग_लिखो_tcm32(devinfo, tcm_dma_phys_addr,
			       address & 0xffffffff);
	brcmf_pcie_ग_लिखो_tcm32(devinfo, tcm_dma_phys_addr + 4, address >> 32);

	वापस (ring);
पूर्ण


अटल काष्ठा brcmf_pcie_ringbuf *
brcmf_pcie_alloc_dma_and_ring(काष्ठा brcmf_pciedev_info *devinfo, u32 ring_id,
			      u32 tcm_ring_phys_addr)
अणु
	व्योम *dma_buf;
	dma_addr_t dma_handle;
	काष्ठा brcmf_pcie_ringbuf *ring;
	u32 size;
	u32 addr;
	स्थिर u32 *ring_itemsize_array;

	अगर (devinfo->shared.version < BRCMF_PCIE_SHARED_VERSION_7)
		ring_itemsize_array = brcmf_ring_itemsize_pre_v7;
	अन्यथा
		ring_itemsize_array = brcmf_ring_itemsize;

	size = brcmf_ring_max_item[ring_id] * ring_itemsize_array[ring_id];
	dma_buf = brcmf_pcie_init_dmabuffer_क्रम_device(devinfo, size,
			tcm_ring_phys_addr + BRCMF_RING_MEM_BASE_ADDR_OFFSET,
			&dma_handle);
	अगर (!dma_buf)
		वापस शून्य;

	addr = tcm_ring_phys_addr + BRCMF_RING_MAX_ITEM_OFFSET;
	brcmf_pcie_ग_लिखो_tcm16(devinfo, addr, brcmf_ring_max_item[ring_id]);
	addr = tcm_ring_phys_addr + BRCMF_RING_LEN_ITEMS_OFFSET;
	brcmf_pcie_ग_लिखो_tcm16(devinfo, addr, ring_itemsize_array[ring_id]);

	ring = kzalloc(माप(*ring), GFP_KERNEL);
	अगर (!ring) अणु
		dma_मुक्त_coherent(&devinfo->pdev->dev, size, dma_buf,
				  dma_handle);
		वापस शून्य;
	पूर्ण
	brcmf_commonring_config(&ring->commonring, brcmf_ring_max_item[ring_id],
				ring_itemsize_array[ring_id], dma_buf);
	ring->dma_handle = dma_handle;
	ring->devinfo = devinfo;
	brcmf_commonring_रेजिस्टर_cb(&ring->commonring,
				     brcmf_pcie_ring_mb_ring_bell,
				     brcmf_pcie_ring_mb_update_rptr,
				     brcmf_pcie_ring_mb_update_wptr,
				     brcmf_pcie_ring_mb_ग_लिखो_rptr,
				     brcmf_pcie_ring_mb_ग_लिखो_wptr, ring);

	वापस (ring);
पूर्ण


अटल व्योम brcmf_pcie_release_ringbuffer(काष्ठा device *dev,
					  काष्ठा brcmf_pcie_ringbuf *ring)
अणु
	व्योम *dma_buf;
	u32 size;

	अगर (!ring)
		वापस;

	dma_buf = ring->commonring.buf_addr;
	अगर (dma_buf) अणु
		size = ring->commonring.depth * ring->commonring.item_len;
		dma_मुक्त_coherent(dev, size, dma_buf, ring->dma_handle);
	पूर्ण
	kमुक्त(ring);
पूर्ण


अटल व्योम brcmf_pcie_release_ringbuffers(काष्ठा brcmf_pciedev_info *devinfo)
अणु
	u32 i;

	क्रम (i = 0; i < BRCMF_NROF_COMMON_MSGRINGS; i++) अणु
		brcmf_pcie_release_ringbuffer(&devinfo->pdev->dev,
					      devinfo->shared.commonrings[i]);
		devinfo->shared.commonrings[i] = शून्य;
	पूर्ण
	kमुक्त(devinfo->shared.flowrings);
	devinfo->shared.flowrings = शून्य;
	अगर (devinfo->idxbuf) अणु
		dma_मुक्त_coherent(&devinfo->pdev->dev,
				  devinfo->idxbuf_sz,
				  devinfo->idxbuf,
				  devinfo->idxbuf_dmahandle);
		devinfo->idxbuf = शून्य;
	पूर्ण
पूर्ण


अटल पूर्णांक brcmf_pcie_init_ringbuffers(काष्ठा brcmf_pciedev_info *devinfo)
अणु
	काष्ठा brcmf_bus *bus = dev_get_drvdata(&devinfo->pdev->dev);
	काष्ठा brcmf_pcie_ringbuf *ring;
	काष्ठा brcmf_pcie_ringbuf *rings;
	u32 d2h_w_idx_ptr;
	u32 d2h_r_idx_ptr;
	u32 h2d_w_idx_ptr;
	u32 h2d_r_idx_ptr;
	u32 ring_mem_ptr;
	u32 i;
	u64 address;
	u32 bufsz;
	u8 idx_offset;
	काष्ठा brcmf_pcie_dhi_ringinfo ringinfo;
	u16 max_flowrings;
	u16 max_submissionrings;
	u16 max_completionrings;

	स_नकल_fromio(&ringinfo, devinfo->tcm + devinfo->shared.ring_info_addr,
		      माप(ringinfo));
	अगर (devinfo->shared.version >= 6) अणु
		max_submissionrings = le16_to_cpu(ringinfo.max_submissionrings);
		max_flowrings = le16_to_cpu(ringinfo.max_flowrings);
		max_completionrings = le16_to_cpu(ringinfo.max_completionrings);
	पूर्ण अन्यथा अणु
		max_submissionrings = le16_to_cpu(ringinfo.max_flowrings);
		max_flowrings = max_submissionrings -
				BRCMF_NROF_H2D_COMMON_MSGRINGS;
		max_completionrings = BRCMF_NROF_D2H_COMMON_MSGRINGS;
	पूर्ण

	अगर (devinfo->dma_idx_sz != 0) अणु
		bufsz = (max_submissionrings + max_completionrings) *
			devinfo->dma_idx_sz * 2;
		devinfo->idxbuf = dma_alloc_coherent(&devinfo->pdev->dev, bufsz,
						     &devinfo->idxbuf_dmahandle,
						     GFP_KERNEL);
		अगर (!devinfo->idxbuf)
			devinfo->dma_idx_sz = 0;
	पूर्ण

	अगर (devinfo->dma_idx_sz == 0) अणु
		d2h_w_idx_ptr = le32_to_cpu(ringinfo.d2h_w_idx_ptr);
		d2h_r_idx_ptr = le32_to_cpu(ringinfo.d2h_r_idx_ptr);
		h2d_w_idx_ptr = le32_to_cpu(ringinfo.h2d_w_idx_ptr);
		h2d_r_idx_ptr = le32_to_cpu(ringinfo.h2d_r_idx_ptr);
		idx_offset = माप(u32);
		devinfo->ग_लिखो_ptr = brcmf_pcie_ग_लिखो_tcm16;
		devinfo->पढ़ो_ptr = brcmf_pcie_पढ़ो_tcm16;
		brcmf_dbg(PCIE, "Using TCM indices\n");
	पूर्ण अन्यथा अणु
		स_रखो(devinfo->idxbuf, 0, bufsz);
		devinfo->idxbuf_sz = bufsz;
		idx_offset = devinfo->dma_idx_sz;
		devinfo->ग_लिखो_ptr = brcmf_pcie_ग_लिखो_idx;
		devinfo->पढ़ो_ptr = brcmf_pcie_पढ़ो_idx;

		h2d_w_idx_ptr = 0;
		address = (u64)devinfo->idxbuf_dmahandle;
		ringinfo.h2d_w_idx_hostaddr.low_addr =
			cpu_to_le32(address & 0xffffffff);
		ringinfo.h2d_w_idx_hostaddr.high_addr =
			cpu_to_le32(address >> 32);

		h2d_r_idx_ptr = h2d_w_idx_ptr +
				max_submissionrings * idx_offset;
		address += max_submissionrings * idx_offset;
		ringinfo.h2d_r_idx_hostaddr.low_addr =
			cpu_to_le32(address & 0xffffffff);
		ringinfo.h2d_r_idx_hostaddr.high_addr =
			cpu_to_le32(address >> 32);

		d2h_w_idx_ptr = h2d_r_idx_ptr +
				max_submissionrings * idx_offset;
		address += max_submissionrings * idx_offset;
		ringinfo.d2h_w_idx_hostaddr.low_addr =
			cpu_to_le32(address & 0xffffffff);
		ringinfo.d2h_w_idx_hostaddr.high_addr =
			cpu_to_le32(address >> 32);

		d2h_r_idx_ptr = d2h_w_idx_ptr +
				max_completionrings * idx_offset;
		address += max_completionrings * idx_offset;
		ringinfo.d2h_r_idx_hostaddr.low_addr =
			cpu_to_le32(address & 0xffffffff);
		ringinfo.d2h_r_idx_hostaddr.high_addr =
			cpu_to_le32(address >> 32);

		स_नकल_toio(devinfo->tcm + devinfo->shared.ring_info_addr,
			    &ringinfo, माप(ringinfo));
		brcmf_dbg(PCIE, "Using host memory indices\n");
	पूर्ण

	ring_mem_ptr = le32_to_cpu(ringinfo.ringmem);

	क्रम (i = 0; i < BRCMF_NROF_H2D_COMMON_MSGRINGS; i++) अणु
		ring = brcmf_pcie_alloc_dma_and_ring(devinfo, i, ring_mem_ptr);
		अगर (!ring)
			जाओ fail;
		ring->w_idx_addr = h2d_w_idx_ptr;
		ring->r_idx_addr = h2d_r_idx_ptr;
		ring->id = i;
		devinfo->shared.commonrings[i] = ring;

		h2d_w_idx_ptr += idx_offset;
		h2d_r_idx_ptr += idx_offset;
		ring_mem_ptr += BRCMF_RING_MEM_SZ;
	पूर्ण

	क्रम (i = BRCMF_NROF_H2D_COMMON_MSGRINGS;
	     i < BRCMF_NROF_COMMON_MSGRINGS; i++) अणु
		ring = brcmf_pcie_alloc_dma_and_ring(devinfo, i, ring_mem_ptr);
		अगर (!ring)
			जाओ fail;
		ring->w_idx_addr = d2h_w_idx_ptr;
		ring->r_idx_addr = d2h_r_idx_ptr;
		ring->id = i;
		devinfo->shared.commonrings[i] = ring;

		d2h_w_idx_ptr += idx_offset;
		d2h_r_idx_ptr += idx_offset;
		ring_mem_ptr += BRCMF_RING_MEM_SZ;
	पूर्ण

	devinfo->shared.max_flowrings = max_flowrings;
	devinfo->shared.max_submissionrings = max_submissionrings;
	devinfo->shared.max_completionrings = max_completionrings;
	rings = kसुस्मृति(max_flowrings, माप(*ring), GFP_KERNEL);
	अगर (!rings)
		जाओ fail;

	brcmf_dbg(PCIE, "Nr of flowrings is %d\n", max_flowrings);

	क्रम (i = 0; i < max_flowrings; i++) अणु
		ring = &rings[i];
		ring->devinfo = devinfo;
		ring->id = i + BRCMF_H2D_MSGRING_FLOWRING_IDSTART;
		brcmf_commonring_रेजिस्टर_cb(&ring->commonring,
					     brcmf_pcie_ring_mb_ring_bell,
					     brcmf_pcie_ring_mb_update_rptr,
					     brcmf_pcie_ring_mb_update_wptr,
					     brcmf_pcie_ring_mb_ग_लिखो_rptr,
					     brcmf_pcie_ring_mb_ग_लिखो_wptr,
					     ring);
		ring->w_idx_addr = h2d_w_idx_ptr;
		ring->r_idx_addr = h2d_r_idx_ptr;
		h2d_w_idx_ptr += idx_offset;
		h2d_r_idx_ptr += idx_offset;
	पूर्ण
	devinfo->shared.flowrings = rings;

	वापस 0;

fail:
	brcmf_err(bus, "Allocating ring buffers failed\n");
	brcmf_pcie_release_ringbuffers(devinfo);
	वापस -ENOMEM;
पूर्ण


अटल व्योम
brcmf_pcie_release_scratchbuffers(काष्ठा brcmf_pciedev_info *devinfo)
अणु
	अगर (devinfo->shared.scratch)
		dma_मुक्त_coherent(&devinfo->pdev->dev,
				  BRCMF_DMA_D2H_SCRATCH_BUF_LEN,
				  devinfo->shared.scratch,
				  devinfo->shared.scratch_dmahandle);
	अगर (devinfo->shared.ringupd)
		dma_मुक्त_coherent(&devinfo->pdev->dev,
				  BRCMF_DMA_D2H_RINGUPD_BUF_LEN,
				  devinfo->shared.ringupd,
				  devinfo->shared.ringupd_dmahandle);
पूर्ण

अटल पूर्णांक brcmf_pcie_init_scratchbuffers(काष्ठा brcmf_pciedev_info *devinfo)
अणु
	काष्ठा brcmf_bus *bus = dev_get_drvdata(&devinfo->pdev->dev);
	u64 address;
	u32 addr;

	devinfo->shared.scratch =
		dma_alloc_coherent(&devinfo->pdev->dev,
				   BRCMF_DMA_D2H_SCRATCH_BUF_LEN,
				   &devinfo->shared.scratch_dmahandle,
				   GFP_KERNEL);
	अगर (!devinfo->shared.scratch)
		जाओ fail;

	addr = devinfo->shared.tcm_base_address +
	       BRCMF_SHARED_DMA_SCRATCH_ADDR_OFFSET;
	address = (u64)devinfo->shared.scratch_dmahandle;
	brcmf_pcie_ग_लिखो_tcm32(devinfo, addr, address & 0xffffffff);
	brcmf_pcie_ग_लिखो_tcm32(devinfo, addr + 4, address >> 32);
	addr = devinfo->shared.tcm_base_address +
	       BRCMF_SHARED_DMA_SCRATCH_LEN_OFFSET;
	brcmf_pcie_ग_लिखो_tcm32(devinfo, addr, BRCMF_DMA_D2H_SCRATCH_BUF_LEN);

	devinfo->shared.ringupd =
		dma_alloc_coherent(&devinfo->pdev->dev,
				   BRCMF_DMA_D2H_RINGUPD_BUF_LEN,
				   &devinfo->shared.ringupd_dmahandle,
				   GFP_KERNEL);
	अगर (!devinfo->shared.ringupd)
		जाओ fail;

	addr = devinfo->shared.tcm_base_address +
	       BRCMF_SHARED_DMA_RINGUPD_ADDR_OFFSET;
	address = (u64)devinfo->shared.ringupd_dmahandle;
	brcmf_pcie_ग_लिखो_tcm32(devinfo, addr, address & 0xffffffff);
	brcmf_pcie_ग_लिखो_tcm32(devinfo, addr + 4, address >> 32);
	addr = devinfo->shared.tcm_base_address +
	       BRCMF_SHARED_DMA_RINGUPD_LEN_OFFSET;
	brcmf_pcie_ग_लिखो_tcm32(devinfo, addr, BRCMF_DMA_D2H_RINGUPD_BUF_LEN);
	वापस 0;

fail:
	brcmf_err(bus, "Allocating scratch buffers failed\n");
	brcmf_pcie_release_scratchbuffers(devinfo);
	वापस -ENOMEM;
पूर्ण


अटल व्योम brcmf_pcie_करोwn(काष्ठा device *dev)
अणु
पूर्ण


अटल पूर्णांक brcmf_pcie_tx(काष्ठा device *dev, काष्ठा sk_buff *skb)
अणु
	वापस 0;
पूर्ण


अटल पूर्णांक brcmf_pcie_tx_ctlpkt(काष्ठा device *dev, अचिन्हित अक्षर *msg,
				uपूर्णांक len)
अणु
	वापस 0;
पूर्ण


अटल पूर्णांक brcmf_pcie_rx_ctlpkt(काष्ठा device *dev, अचिन्हित अक्षर *msg,
				uपूर्णांक len)
अणु
	वापस 0;
पूर्ण


अटल व्योम brcmf_pcie_wowl_config(काष्ठा device *dev, bool enabled)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev);
	काष्ठा brcmf_pciedev *buspub = bus_अगर->bus_priv.pcie;
	काष्ठा brcmf_pciedev_info *devinfo = buspub->devinfo;

	brcmf_dbg(PCIE, "Configuring WOWL, enabled=%d\n", enabled);
	devinfo->wowl_enabled = enabled;
पूर्ण


अटल माप_प्रकार brcmf_pcie_get_ramsize(काष्ठा device *dev)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev);
	काष्ठा brcmf_pciedev *buspub = bus_अगर->bus_priv.pcie;
	काष्ठा brcmf_pciedev_info *devinfo = buspub->devinfo;

	वापस devinfo->ci->ramsize - devinfo->ci->srsize;
पूर्ण


अटल पूर्णांक brcmf_pcie_get_memdump(काष्ठा device *dev, व्योम *data, माप_प्रकार len)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev);
	काष्ठा brcmf_pciedev *buspub = bus_अगर->bus_priv.pcie;
	काष्ठा brcmf_pciedev_info *devinfo = buspub->devinfo;

	brcmf_dbg(PCIE, "dump at 0x%08X: len=%zu\n", devinfo->ci->rambase, len);
	brcmf_pcie_copy_dev_tomem(devinfo, devinfo->ci->rambase, data, len);
	वापस 0;
पूर्ण

अटल
पूर्णांक brcmf_pcie_get_fwname(काष्ठा device *dev, स्थिर अक्षर *ext, u8 *fw_name)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev);
	काष्ठा brcmf_fw_request *fwreq;
	काष्ठा brcmf_fw_name fwnames[] = अणु
		अणु ext, fw_name पूर्ण,
	पूर्ण;

	fwreq = brcmf_fw_alloc_request(bus_अगर->chip, bus_अगर->chiprev,
				       brcmf_pcie_fwnames,
				       ARRAY_SIZE(brcmf_pcie_fwnames),
				       fwnames, ARRAY_SIZE(fwnames));
	अगर (!fwreq)
		वापस -ENOMEM;

	kमुक्त(fwreq);
	वापस 0;
पूर्ण

अटल पूर्णांक brcmf_pcie_reset(काष्ठा device *dev)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev);
	काष्ठा brcmf_pciedev *buspub = bus_अगर->bus_priv.pcie;
	काष्ठा brcmf_pciedev_info *devinfo = buspub->devinfo;
	काष्ठा brcmf_fw_request *fwreq;
	पूर्णांक err;

	brcmf_pcie_पूर्णांकr_disable(devinfo);

	brcmf_pcie_bus_console_पढ़ो(devinfo, true);

	brcmf_detach(dev);

	brcmf_pcie_release_irq(devinfo);
	brcmf_pcie_release_scratchbuffers(devinfo);
	brcmf_pcie_release_ringbuffers(devinfo);
	brcmf_pcie_reset_device(devinfo);

	fwreq = brcmf_pcie_prepare_fw_request(devinfo);
	अगर (!fwreq) अणु
		dev_err(dev, "Failed to prepare FW request\n");
		वापस -ENOMEM;
	पूर्ण

	err = brcmf_fw_get_firmwares(dev, fwreq, brcmf_pcie_setup);
	अगर (err) अणु
		dev_err(dev, "Failed to prepare FW request\n");
		kमुक्त(fwreq);
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा brcmf_bus_ops brcmf_pcie_bus_ops = अणु
	.txdata = brcmf_pcie_tx,
	.stop = brcmf_pcie_करोwn,
	.txctl = brcmf_pcie_tx_ctlpkt,
	.rxctl = brcmf_pcie_rx_ctlpkt,
	.wowl_config = brcmf_pcie_wowl_config,
	.get_ramsize = brcmf_pcie_get_ramsize,
	.get_memdump = brcmf_pcie_get_memdump,
	.get_fwname = brcmf_pcie_get_fwname,
	.reset = brcmf_pcie_reset,
पूर्ण;


अटल व्योम
brcmf_pcie_adjust_ramsize(काष्ठा brcmf_pciedev_info *devinfo, u8 *data,
			  u32 data_len)
अणु
	__le32 *field;
	u32 newsize;

	अगर (data_len < BRCMF_RAMSIZE_OFFSET + 8)
		वापस;

	field = (__le32 *)&data[BRCMF_RAMSIZE_OFFSET];
	अगर (le32_to_cpup(field) != BRCMF_RAMSIZE_MAGIC)
		वापस;
	field++;
	newsize = le32_to_cpup(field);

	brcmf_dbg(PCIE, "Found ramsize info in FW, adjusting to 0x%x\n",
		  newsize);
	devinfo->ci->ramsize = newsize;
पूर्ण


अटल पूर्णांक
brcmf_pcie_init_share_ram_info(काष्ठा brcmf_pciedev_info *devinfo,
			       u32 sharedram_addr)
अणु
	काष्ठा brcmf_bus *bus = dev_get_drvdata(&devinfo->pdev->dev);
	काष्ठा brcmf_pcie_shared_info *shared;
	u32 addr;

	shared = &devinfo->shared;
	shared->tcm_base_address = sharedram_addr;

	shared->flags = brcmf_pcie_पढ़ो_tcm32(devinfo, sharedram_addr);
	shared->version = (u8)(shared->flags & BRCMF_PCIE_SHARED_VERSION_MASK);
	brcmf_dbg(PCIE, "PCIe protocol version %d\n", shared->version);
	अगर ((shared->version > BRCMF_PCIE_MAX_SHARED_VERSION) ||
	    (shared->version < BRCMF_PCIE_MIN_SHARED_VERSION)) अणु
		brcmf_err(bus, "Unsupported PCIE version %d\n",
			  shared->version);
		वापस -EINVAL;
	पूर्ण

	/* check firmware support dma indicies */
	अगर (shared->flags & BRCMF_PCIE_SHARED_DMA_INDEX) अणु
		अगर (shared->flags & BRCMF_PCIE_SHARED_DMA_2B_IDX)
			devinfo->dma_idx_sz = माप(u16);
		अन्यथा
			devinfo->dma_idx_sz = माप(u32);
	पूर्ण

	addr = sharedram_addr + BRCMF_SHARED_MAX_RXBUFPOST_OFFSET;
	shared->max_rxbufpost = brcmf_pcie_पढ़ो_tcm16(devinfo, addr);
	अगर (shared->max_rxbufpost == 0)
		shared->max_rxbufpost = BRCMF_DEF_MAX_RXBUFPOST;

	addr = sharedram_addr + BRCMF_SHARED_RX_DATAOFFSET_OFFSET;
	shared->rx_dataoffset = brcmf_pcie_पढ़ो_tcm32(devinfo, addr);

	addr = sharedram_addr + BRCMF_SHARED_HTOD_MB_DATA_ADDR_OFFSET;
	shared->htod_mb_data_addr = brcmf_pcie_पढ़ो_tcm32(devinfo, addr);

	addr = sharedram_addr + BRCMF_SHARED_DTOH_MB_DATA_ADDR_OFFSET;
	shared->dtoh_mb_data_addr = brcmf_pcie_पढ़ो_tcm32(devinfo, addr);

	addr = sharedram_addr + BRCMF_SHARED_RING_INFO_ADDR_OFFSET;
	shared->ring_info_addr = brcmf_pcie_पढ़ो_tcm32(devinfo, addr);

	brcmf_dbg(PCIE, "max rx buf post %d, rx dataoffset %d\n",
		  shared->max_rxbufpost, shared->rx_dataoffset);

	brcmf_pcie_bus_console_init(devinfo);

	वापस 0;
पूर्ण


अटल पूर्णांक brcmf_pcie_करोwnload_fw_nvram(काष्ठा brcmf_pciedev_info *devinfo,
					स्थिर काष्ठा firmware *fw, व्योम *nvram,
					u32 nvram_len)
अणु
	काष्ठा brcmf_bus *bus = dev_get_drvdata(&devinfo->pdev->dev);
	u32 sharedram_addr;
	u32 sharedram_addr_written;
	u32 loop_counter;
	पूर्णांक err;
	u32 address;
	u32 resetपूर्णांकr;

	brcmf_dbg(PCIE, "Halt ARM.\n");
	err = brcmf_pcie_enter_करोwnload_state(devinfo);
	अगर (err)
		वापस err;

	brcmf_dbg(PCIE, "Download FW %s\n", devinfo->fw_name);
	brcmf_pcie_copy_mem_todev(devinfo, devinfo->ci->rambase,
				  (व्योम *)fw->data, fw->size);

	resetपूर्णांकr = get_unaligned_le32(fw->data);
	release_firmware(fw);

	/* reset last 4 bytes of RAM address. to be used क्रम shared
	 * area. This identअगरies when FW is running
	 */
	brcmf_pcie_ग_लिखो_ram32(devinfo, devinfo->ci->ramsize - 4, 0);

	अगर (nvram) अणु
		brcmf_dbg(PCIE, "Download NVRAM %s\n", devinfo->nvram_name);
		address = devinfo->ci->rambase + devinfo->ci->ramsize -
			  nvram_len;
		brcmf_pcie_copy_mem_todev(devinfo, address, nvram, nvram_len);
		brcmf_fw_nvram_मुक्त(nvram);
	पूर्ण अन्यथा अणु
		brcmf_dbg(PCIE, "No matching NVRAM file found %s\n",
			  devinfo->nvram_name);
	पूर्ण

	sharedram_addr_written = brcmf_pcie_पढ़ो_ram32(devinfo,
						       devinfo->ci->ramsize -
						       4);
	brcmf_dbg(PCIE, "Bring ARM in running state\n");
	err = brcmf_pcie_निकास_करोwnload_state(devinfo, resetपूर्णांकr);
	अगर (err)
		वापस err;

	brcmf_dbg(PCIE, "Wait for FW init\n");
	sharedram_addr = sharedram_addr_written;
	loop_counter = BRCMF_PCIE_FW_UP_TIMEOUT / 50;
	जबतक ((sharedram_addr == sharedram_addr_written) && (loop_counter)) अणु
		msleep(50);
		sharedram_addr = brcmf_pcie_पढ़ो_ram32(devinfo,
						       devinfo->ci->ramsize -
						       4);
		loop_counter--;
	पूर्ण
	अगर (sharedram_addr == sharedram_addr_written) अणु
		brcmf_err(bus, "FW failed to initialize\n");
		वापस -ENODEV;
	पूर्ण
	अगर (sharedram_addr < devinfo->ci->rambase ||
	    sharedram_addr >= devinfo->ci->rambase + devinfo->ci->ramsize) अणु
		brcmf_err(bus, "Invalid shared RAM address 0x%08x\n",
			  sharedram_addr);
		वापस -ENODEV;
	पूर्ण
	brcmf_dbg(PCIE, "Shared RAM addr: 0x%08x\n", sharedram_addr);

	वापस (brcmf_pcie_init_share_ram_info(devinfo, sharedram_addr));
पूर्ण


अटल पूर्णांक brcmf_pcie_get_resource(काष्ठा brcmf_pciedev_info *devinfo)
अणु
	काष्ठा pci_dev *pdev = devinfo->pdev;
	काष्ठा brcmf_bus *bus = dev_get_drvdata(&pdev->dev);
	पूर्णांक err;
	phys_addr_t  bar0_addr, bar1_addr;
	uदीर्घ bar1_size;

	err = pci_enable_device(pdev);
	अगर (err) अणु
		brcmf_err(bus, "pci_enable_device failed err=%d\n", err);
		वापस err;
	पूर्ण

	pci_set_master(pdev);

	/* Bar-0 mapped address */
	bar0_addr = pci_resource_start(pdev, 0);
	/* Bar-1 mapped address */
	bar1_addr = pci_resource_start(pdev, 2);
	/* पढ़ो Bar-1 mapped memory range */
	bar1_size = pci_resource_len(pdev, 2);
	अगर ((bar1_size == 0) || (bar1_addr == 0)) अणु
		brcmf_err(bus, "BAR1 Not enabled, device size=%ld, addr=%#016llx\n",
			  bar1_size, (अचिन्हित दीर्घ दीर्घ)bar1_addr);
		वापस -EINVAL;
	पूर्ण

	devinfo->regs = ioremap(bar0_addr, BRCMF_PCIE_REG_MAP_SIZE);
	devinfo->tcm = ioremap(bar1_addr, bar1_size);

	अगर (!devinfo->regs || !devinfo->tcm) अणु
		brcmf_err(bus, "ioremap() failed (%p,%p)\n", devinfo->regs,
			  devinfo->tcm);
		वापस -EINVAL;
	पूर्ण
	brcmf_dbg(PCIE, "Phys addr : reg space = %p base addr %#016llx\n",
		  devinfo->regs, (अचिन्हित दीर्घ दीर्घ)bar0_addr);
	brcmf_dbg(PCIE, "Phys addr : mem space = %p base addr %#016llx size 0x%x\n",
		  devinfo->tcm, (अचिन्हित दीर्घ दीर्घ)bar1_addr,
		  (अचिन्हित पूर्णांक)bar1_size);

	वापस 0;
पूर्ण


अटल व्योम brcmf_pcie_release_resource(काष्ठा brcmf_pciedev_info *devinfo)
अणु
	अगर (devinfo->tcm)
		iounmap(devinfo->tcm);
	अगर (devinfo->regs)
		iounmap(devinfo->regs);

	pci_disable_device(devinfo->pdev);
पूर्ण


अटल u32 brcmf_pcie_buscore_prep_addr(स्थिर काष्ठा pci_dev *pdev, u32 addr)
अणु
	u32 ret_addr;

	ret_addr = addr & (BRCMF_PCIE_BAR0_REG_SIZE - 1);
	addr &= ~(BRCMF_PCIE_BAR0_REG_SIZE - 1);
	pci_ग_लिखो_config_dword(pdev, BRCMF_PCIE_BAR0_WINDOW, addr);

	वापस ret_addr;
पूर्ण


अटल u32 brcmf_pcie_buscore_पढ़ो32(व्योम *ctx, u32 addr)
अणु
	काष्ठा brcmf_pciedev_info *devinfo = (काष्ठा brcmf_pciedev_info *)ctx;

	addr = brcmf_pcie_buscore_prep_addr(devinfo->pdev, addr);
	वापस brcmf_pcie_पढ़ो_reg32(devinfo, addr);
पूर्ण


अटल व्योम brcmf_pcie_buscore_ग_लिखो32(व्योम *ctx, u32 addr, u32 value)
अणु
	काष्ठा brcmf_pciedev_info *devinfo = (काष्ठा brcmf_pciedev_info *)ctx;

	addr = brcmf_pcie_buscore_prep_addr(devinfo->pdev, addr);
	brcmf_pcie_ग_लिखो_reg32(devinfo, addr, value);
पूर्ण


अटल पूर्णांक brcmf_pcie_buscoreprep(व्योम *ctx)
अणु
	वापस brcmf_pcie_get_resource(ctx);
पूर्ण


अटल पूर्णांक brcmf_pcie_buscore_reset(व्योम *ctx, काष्ठा brcmf_chip *chip)
अणु
	काष्ठा brcmf_pciedev_info *devinfo = (काष्ठा brcmf_pciedev_info *)ctx;
	u32 val;

	devinfo->ci = chip;
	brcmf_pcie_reset_device(devinfo);

	val = brcmf_pcie_पढ़ो_reg32(devinfo, BRCMF_PCIE_PCIE2REG_MAILBOXINT);
	अगर (val != 0xffffffff)
		brcmf_pcie_ग_लिखो_reg32(devinfo, BRCMF_PCIE_PCIE2REG_MAILBOXINT,
				       val);

	वापस 0;
पूर्ण


अटल व्योम brcmf_pcie_buscore_activate(व्योम *ctx, काष्ठा brcmf_chip *chip,
					u32 rstvec)
अणु
	काष्ठा brcmf_pciedev_info *devinfo = (काष्ठा brcmf_pciedev_info *)ctx;

	brcmf_pcie_ग_लिखो_tcm32(devinfo, 0, rstvec);
पूर्ण


अटल स्थिर काष्ठा brcmf_buscore_ops brcmf_pcie_buscore_ops = अणु
	.prepare = brcmf_pcie_buscoreprep,
	.reset = brcmf_pcie_buscore_reset,
	.activate = brcmf_pcie_buscore_activate,
	.पढ़ो32 = brcmf_pcie_buscore_पढ़ो32,
	.ग_लिखो32 = brcmf_pcie_buscore_ग_लिखो32,
पूर्ण;

#घोषणा BRCMF_PCIE_FW_CODE	0
#घोषणा BRCMF_PCIE_FW_NVRAM	1

अटल व्योम brcmf_pcie_setup(काष्ठा device *dev, पूर्णांक ret,
			     काष्ठा brcmf_fw_request *fwreq)
अणु
	स्थिर काष्ठा firmware *fw;
	व्योम *nvram;
	काष्ठा brcmf_bus *bus;
	काष्ठा brcmf_pciedev *pcie_bus_dev;
	काष्ठा brcmf_pciedev_info *devinfo;
	काष्ठा brcmf_commonring **flowrings;
	u32 i, nvram_len;

	/* check firmware loading result */
	अगर (ret)
		जाओ fail;

	bus = dev_get_drvdata(dev);
	pcie_bus_dev = bus->bus_priv.pcie;
	devinfo = pcie_bus_dev->devinfo;
	brcmf_pcie_attach(devinfo);

	fw = fwreq->items[BRCMF_PCIE_FW_CODE].binary;
	nvram = fwreq->items[BRCMF_PCIE_FW_NVRAM].nv_data.data;
	nvram_len = fwreq->items[BRCMF_PCIE_FW_NVRAM].nv_data.len;
	kमुक्त(fwreq);

	ret = brcmf_chip_get_raminfo(devinfo->ci);
	अगर (ret) अणु
		brcmf_err(bus, "Failed to get RAM info\n");
		जाओ fail;
	पूर्ण

	/* Some of the firmwares have the size of the memory of the device
	 * defined inside the firmware. This is because part of the memory in
	 * the device is shared and the devision is determined by FW. Parse
	 * the firmware and adjust the chip memory size now.
	 */
	brcmf_pcie_adjust_ramsize(devinfo, (u8 *)fw->data, fw->size);

	ret = brcmf_pcie_करोwnload_fw_nvram(devinfo, fw, nvram, nvram_len);
	अगर (ret)
		जाओ fail;

	devinfo->state = BRCMFMAC_PCIE_STATE_UP;

	ret = brcmf_pcie_init_ringbuffers(devinfo);
	अगर (ret)
		जाओ fail;

	ret = brcmf_pcie_init_scratchbuffers(devinfo);
	अगर (ret)
		जाओ fail;

	brcmf_pcie_select_core(devinfo, BCMA_CORE_PCIE2);
	ret = brcmf_pcie_request_irq(devinfo);
	अगर (ret)
		जाओ fail;

	/* hook the commonrings in the bus काष्ठाure. */
	क्रम (i = 0; i < BRCMF_NROF_COMMON_MSGRINGS; i++)
		bus->msgbuf->commonrings[i] =
				&devinfo->shared.commonrings[i]->commonring;

	flowrings = kसुस्मृति(devinfo->shared.max_flowrings, माप(*flowrings),
			    GFP_KERNEL);
	अगर (!flowrings)
		जाओ fail;

	क्रम (i = 0; i < devinfo->shared.max_flowrings; i++)
		flowrings[i] = &devinfo->shared.flowrings[i].commonring;
	bus->msgbuf->flowrings = flowrings;

	bus->msgbuf->rx_dataoffset = devinfo->shared.rx_dataoffset;
	bus->msgbuf->max_rxbufpost = devinfo->shared.max_rxbufpost;
	bus->msgbuf->max_flowrings = devinfo->shared.max_flowrings;

	init_रुकोqueue_head(&devinfo->mbdata_resp_रुको);

	brcmf_pcie_पूर्णांकr_enable(devinfo);
	brcmf_pcie_hostपढ़ोy(devinfo);

	ret = brcmf_attach(&devinfo->pdev->dev);
	अगर (ret)
		जाओ fail;

	brcmf_pcie_bus_console_पढ़ो(devinfo, false);

	वापस;

fail:
	device_release_driver(dev);
पूर्ण

अटल काष्ठा brcmf_fw_request *
brcmf_pcie_prepare_fw_request(काष्ठा brcmf_pciedev_info *devinfo)
अणु
	काष्ठा brcmf_fw_request *fwreq;
	काष्ठा brcmf_fw_name fwnames[] = अणु
		अणु ".bin", devinfo->fw_name पूर्ण,
		अणु ".txt", devinfo->nvram_name पूर्ण,
	पूर्ण;

	fwreq = brcmf_fw_alloc_request(devinfo->ci->chip, devinfo->ci->chiprev,
				       brcmf_pcie_fwnames,
				       ARRAY_SIZE(brcmf_pcie_fwnames),
				       fwnames, ARRAY_SIZE(fwnames));
	अगर (!fwreq)
		वापस शून्य;

	fwreq->items[BRCMF_PCIE_FW_CODE].type = BRCMF_FW_TYPE_BINARY;
	fwreq->items[BRCMF_PCIE_FW_NVRAM].type = BRCMF_FW_TYPE_NVRAM;
	fwreq->items[BRCMF_PCIE_FW_NVRAM].flags = BRCMF_FW_REQF_OPTIONAL;
	fwreq->board_type = devinfo->settings->board_type;
	/* NVRAM reserves PCI करोमुख्य 0 क्रम Broadcom's SDK faked bus */
	fwreq->करोमुख्य_nr = pci_करोमुख्य_nr(devinfo->pdev->bus) + 1;
	fwreq->bus_nr = devinfo->pdev->bus->number;

	वापस fwreq;
पूर्ण

अटल पूर्णांक
brcmf_pcie_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा brcmf_fw_request *fwreq;
	काष्ठा brcmf_pciedev_info *devinfo;
	काष्ठा brcmf_pciedev *pcie_bus_dev;
	काष्ठा brcmf_bus *bus;

	brcmf_dbg(PCIE, "Enter %x:%x\n", pdev->venकरोr, pdev->device);

	ret = -ENOMEM;
	devinfo = kzalloc(माप(*devinfo), GFP_KERNEL);
	अगर (devinfo == शून्य)
		वापस ret;

	devinfo->pdev = pdev;
	pcie_bus_dev = शून्य;
	devinfo->ci = brcmf_chip_attach(devinfo, &brcmf_pcie_buscore_ops);
	अगर (IS_ERR(devinfo->ci)) अणु
		ret = PTR_ERR(devinfo->ci);
		devinfo->ci = शून्य;
		जाओ fail;
	पूर्ण

	pcie_bus_dev = kzalloc(माप(*pcie_bus_dev), GFP_KERNEL);
	अगर (pcie_bus_dev == शून्य) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	devinfo->settings = brcmf_get_module_param(&devinfo->pdev->dev,
						   BRCMF_BUSTYPE_PCIE,
						   devinfo->ci->chip,
						   devinfo->ci->chiprev);
	अगर (!devinfo->settings) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	bus = kzalloc(माप(*bus), GFP_KERNEL);
	अगर (!bus) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण
	bus->msgbuf = kzalloc(माप(*bus->msgbuf), GFP_KERNEL);
	अगर (!bus->msgbuf) अणु
		ret = -ENOMEM;
		kमुक्त(bus);
		जाओ fail;
	पूर्ण

	/* hook it all together. */
	pcie_bus_dev->devinfo = devinfo;
	pcie_bus_dev->bus = bus;
	bus->dev = &pdev->dev;
	bus->bus_priv.pcie = pcie_bus_dev;
	bus->ops = &brcmf_pcie_bus_ops;
	bus->proto_type = BRCMF_PROTO_MSGBUF;
	bus->chip = devinfo->coreid;
	bus->wowl_supported = pci_pme_capable(pdev, PCI_D3hot);
	dev_set_drvdata(&pdev->dev, bus);

	ret = brcmf_alloc(&devinfo->pdev->dev, devinfo->settings);
	अगर (ret)
		जाओ fail_bus;

	fwreq = brcmf_pcie_prepare_fw_request(devinfo);
	अगर (!fwreq) अणु
		ret = -ENOMEM;
		जाओ fail_brcmf;
	पूर्ण

	ret = brcmf_fw_get_firmwares(bus->dev, fwreq, brcmf_pcie_setup);
	अगर (ret < 0) अणु
		kमुक्त(fwreq);
		जाओ fail_brcmf;
	पूर्ण
	वापस 0;

fail_brcmf:
	brcmf_मुक्त(&devinfo->pdev->dev);
fail_bus:
	kमुक्त(bus->msgbuf);
	kमुक्त(bus);
fail:
	brcmf_err(शून्य, "failed %x:%x\n", pdev->venकरोr, pdev->device);
	brcmf_pcie_release_resource(devinfo);
	अगर (devinfo->ci)
		brcmf_chip_detach(devinfo->ci);
	अगर (devinfo->settings)
		brcmf_release_module_param(devinfo->settings);
	kमुक्त(pcie_bus_dev);
	kमुक्त(devinfo);
	वापस ret;
पूर्ण


अटल व्योम
brcmf_pcie_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा brcmf_pciedev_info *devinfo;
	काष्ठा brcmf_bus *bus;

	brcmf_dbg(PCIE, "Enter\n");

	bus = dev_get_drvdata(&pdev->dev);
	अगर (bus == शून्य)
		वापस;

	devinfo = bus->bus_priv.pcie->devinfo;

	devinfo->state = BRCMFMAC_PCIE_STATE_DOWN;
	अगर (devinfo->ci)
		brcmf_pcie_पूर्णांकr_disable(devinfo);

	brcmf_detach(&pdev->dev);
	brcmf_मुक्त(&pdev->dev);

	kमुक्त(bus->bus_priv.pcie);
	kमुक्त(bus->msgbuf->flowrings);
	kमुक्त(bus->msgbuf);
	kमुक्त(bus);

	brcmf_pcie_release_irq(devinfo);
	brcmf_pcie_release_scratchbuffers(devinfo);
	brcmf_pcie_release_ringbuffers(devinfo);
	brcmf_pcie_reset_device(devinfo);
	brcmf_pcie_release_resource(devinfo);

	अगर (devinfo->ci)
		brcmf_chip_detach(devinfo->ci);
	अगर (devinfo->settings)
		brcmf_release_module_param(devinfo->settings);

	kमुक्त(devinfo);
	dev_set_drvdata(&pdev->dev, शून्य);
पूर्ण


#अगर_घोषित CONFIG_PM


अटल पूर्णांक brcmf_pcie_pm_enter_D3(काष्ठा device *dev)
अणु
	काष्ठा brcmf_pciedev_info *devinfo;
	काष्ठा brcmf_bus *bus;

	brcmf_dbg(PCIE, "Enter\n");

	bus = dev_get_drvdata(dev);
	devinfo = bus->bus_priv.pcie->devinfo;

	brcmf_bus_change_state(bus, BRCMF_BUS_DOWN);

	devinfo->mbdata_completed = false;
	brcmf_pcie_send_mb_data(devinfo, BRCMF_H2D_HOST_D3_INFORM);

	रुको_event_समयout(devinfo->mbdata_resp_रुको, devinfo->mbdata_completed,
			   BRCMF_PCIE_MBDATA_TIMEOUT);
	अगर (!devinfo->mbdata_completed) अणु
		brcmf_err(bus, "Timeout on response for entering D3 substate\n");
		brcmf_bus_change_state(bus, BRCMF_BUS_UP);
		वापस -EIO;
	पूर्ण

	devinfo->state = BRCMFMAC_PCIE_STATE_DOWN;

	वापस 0;
पूर्ण


अटल पूर्णांक brcmf_pcie_pm_leave_D3(काष्ठा device *dev)
अणु
	काष्ठा brcmf_pciedev_info *devinfo;
	काष्ठा brcmf_bus *bus;
	काष्ठा pci_dev *pdev;
	पूर्णांक err;

	brcmf_dbg(PCIE, "Enter\n");

	bus = dev_get_drvdata(dev);
	devinfo = bus->bus_priv.pcie->devinfo;
	brcmf_dbg(PCIE, "Enter, dev=%p, bus=%p\n", dev, bus);

	/* Check अगर device is still up and running, अगर so we are पढ़ोy */
	अगर (brcmf_pcie_पढ़ो_reg32(devinfo, BRCMF_PCIE_PCIE2REG_INTMASK) != 0) अणु
		brcmf_dbg(PCIE, "Try to wakeup device....\n");
		अगर (brcmf_pcie_send_mb_data(devinfo, BRCMF_H2D_HOST_D0_INFORM))
			जाओ cleanup;
		brcmf_dbg(PCIE, "Hot resume, continue....\n");
		devinfo->state = BRCMFMAC_PCIE_STATE_UP;
		brcmf_pcie_select_core(devinfo, BCMA_CORE_PCIE2);
		brcmf_bus_change_state(bus, BRCMF_BUS_UP);
		brcmf_pcie_पूर्णांकr_enable(devinfo);
		brcmf_pcie_hostपढ़ोy(devinfo);
		वापस 0;
	पूर्ण

cleanup:
	brcmf_chip_detach(devinfo->ci);
	devinfo->ci = शून्य;
	pdev = devinfo->pdev;
	brcmf_pcie_हटाओ(pdev);

	err = brcmf_pcie_probe(pdev, शून्य);
	अगर (err)
		brcmf_err(bus, "probe after resume failed, err=%d\n", err);

	वापस err;
पूर्ण


अटल स्थिर काष्ठा dev_pm_ops brcmf_pciedrvr_pm = अणु
	.suspend = brcmf_pcie_pm_enter_D3,
	.resume = brcmf_pcie_pm_leave_D3,
	.मुक्तze = brcmf_pcie_pm_enter_D3,
	.restore = brcmf_pcie_pm_leave_D3,
पूर्ण;


#पूर्ण_अगर /* CONFIG_PM */


#घोषणा BRCMF_PCIE_DEVICE(dev_id)	अणु BRCM_PCIE_VENDOR_ID_BROADCOM, dev_id,\
	PCI_ANY_ID, PCI_ANY_ID, PCI_CLASS_NETWORK_OTHER << 8, 0xffff00, 0 पूर्ण
#घोषणा BRCMF_PCIE_DEVICE_SUB(dev_id, subvend, subdev)	अणु \
	BRCM_PCIE_VENDOR_ID_BROADCOM, dev_id,\
	subvend, subdev, PCI_CLASS_NETWORK_OTHER << 8, 0xffff00, 0 पूर्ण

अटल स्थिर काष्ठा pci_device_id brcmf_pcie_devid_table[] = अणु
	BRCMF_PCIE_DEVICE(BRCM_PCIE_4350_DEVICE_ID),
	BRCMF_PCIE_DEVICE_SUB(0x4355, BRCM_PCIE_VENDOR_ID_BROADCOM, 0x4355),
	BRCMF_PCIE_DEVICE(BRCM_PCIE_4354_RAW_DEVICE_ID),
	BRCMF_PCIE_DEVICE(BRCM_PCIE_4356_DEVICE_ID),
	BRCMF_PCIE_DEVICE(BRCM_PCIE_43567_DEVICE_ID),
	BRCMF_PCIE_DEVICE(BRCM_PCIE_43570_DEVICE_ID),
	BRCMF_PCIE_DEVICE(BRCM_PCIE_4358_DEVICE_ID),
	BRCMF_PCIE_DEVICE(BRCM_PCIE_4359_DEVICE_ID),
	BRCMF_PCIE_DEVICE(BRCM_PCIE_43602_DEVICE_ID),
	BRCMF_PCIE_DEVICE(BRCM_PCIE_43602_2G_DEVICE_ID),
	BRCMF_PCIE_DEVICE(BRCM_PCIE_43602_5G_DEVICE_ID),
	BRCMF_PCIE_DEVICE(BRCM_PCIE_43602_RAW_DEVICE_ID),
	BRCMF_PCIE_DEVICE(BRCM_PCIE_4364_DEVICE_ID),
	BRCMF_PCIE_DEVICE(BRCM_PCIE_4365_DEVICE_ID),
	BRCMF_PCIE_DEVICE(BRCM_PCIE_4365_2G_DEVICE_ID),
	BRCMF_PCIE_DEVICE(BRCM_PCIE_4365_5G_DEVICE_ID),
	BRCMF_PCIE_DEVICE_SUB(0x4365, BRCM_PCIE_VENDOR_ID_BROADCOM, 0x4365),
	BRCMF_PCIE_DEVICE(BRCM_PCIE_4366_DEVICE_ID),
	BRCMF_PCIE_DEVICE(BRCM_PCIE_4366_2G_DEVICE_ID),
	BRCMF_PCIE_DEVICE(BRCM_PCIE_4366_5G_DEVICE_ID),
	BRCMF_PCIE_DEVICE(BRCM_PCIE_4371_DEVICE_ID),
	अणु /* end: all zeroes */ पूर्ण
पूर्ण;


MODULE_DEVICE_TABLE(pci, brcmf_pcie_devid_table);


अटल काष्ठा pci_driver brcmf_pciedrvr = अणु
	.node = अणुपूर्ण,
	.name = KBUILD_MODNAME,
	.id_table = brcmf_pcie_devid_table,
	.probe = brcmf_pcie_probe,
	.हटाओ = brcmf_pcie_हटाओ,
#अगर_घोषित CONFIG_PM
	.driver.pm = &brcmf_pciedrvr_pm,
#पूर्ण_अगर
	.driver.coredump = brcmf_dev_coredump,
पूर्ण;


पूर्णांक brcmf_pcie_रेजिस्टर(व्योम)
अणु
	brcmf_dbg(PCIE, "Enter\n");
	वापस pci_रेजिस्टर_driver(&brcmf_pciedrvr);
पूर्ण


व्योम brcmf_pcie_निकास(व्योम)
अणु
	brcmf_dbg(PCIE, "Enter\n");
	pci_unरेजिस्टर_driver(&brcmf_pciedrvr);
पूर्ण
