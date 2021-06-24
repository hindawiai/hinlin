<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (C) 2018 Oleksij Rempel <linux@rempel-privat.de>
 *
 * Driver क्रम Alcor Micro AU6601 and AU6621 controllers
 */

#अगर_अघोषित __ALCOR_PCI_H
#घोषणा __ALCOR_PCI_H

#घोषणा ALCOR_SD_CARD 0
#घोषणा ALCOR_MS_CARD 1

#घोषणा DRV_NAME_ALCOR_PCI_SDMMC		"alcor_sdmmc"
#घोषणा DRV_NAME_ALCOR_PCI_MS			"alcor_ms"

#घोषणा PCI_ID_ALCOR_MICRO			0x1AEA
#घोषणा PCI_ID_AU6601				0x6601
#घोषणा PCI_ID_AU6621				0x6621
#घोषणा PCI_ID_AU6625				0x6625

#घोषणा MHZ_TO_HZ(freq)				((freq) * 1000 * 1000)

#घोषणा AU6601_BASE_CLOCK			31000000
#घोषणा AU6601_MIN_CLOCK			150000
#घोषणा AU6601_MAX_CLOCK			208000000
#घोषणा AU6601_MAX_DMA_SEGMENTS			64
#घोषणा AU6601_MAX_PIO_SEGMENTS			1
#घोषणा AU6601_MAX_DMA_BLOCK_SIZE		0x1000
#घोषणा AU6601_MAX_PIO_BLOCK_SIZE		0x200
#घोषणा AU6601_MAX_DMA_BLOCKS			1
#घोषणा AU6601_DMA_LOCAL_SEGMENTS		1

/* रेजिस्टरs spotter by reverse engineering but still
 * with unknown functionality:
 * 0x10 - ADMA phy address. AU6621 only?
 * 0x51 - LED ctrl?
 * 0x52 - unknown
 * 0x61 - LED related? Always toggled BIT0
 * 0x63 - Same as 0x61?
 * 0x77 - unknown
 */

/* SDMA phy address. Higher then 0x0800.0000?
 * The au6601 and au6621 have dअगरferent DMA engines with dअगरferent issues. One
 * For example au6621 engine is triggered by addr change. No other पूर्णांकeraction
 * is needed. This means, अगर we get two buffers with same address, then engine
 * will stall.
 */
#घोषणा AU6601_REG_SDMA_ADDR			0x00
#घोषणा AU6601_SDMA_MASK			0xffffffff

#घोषणा AU6601_DMA_BOUNDARY			0x05
#घोषणा AU6621_DMA_PAGE_CNT			0x05
/* PIO */
#घोषणा AU6601_REG_BUFFER			0x08
/* ADMA ctrl? AU6621 only. */
#घोषणा AU6621_DMA_CTRL				0x0c
#घोषणा AU6621_DMA_ENABLE			BIT(0)
/* CMD index */
#घोषणा AU6601_REG_CMD_OPCODE			0x23
/* CMD parametr */
#घोषणा AU6601_REG_CMD_ARG			0x24
/* CMD response 4x4 Bytes */
#घोषणा AU6601_REG_CMD_RSP0			0x30
#घोषणा AU6601_REG_CMD_RSP1			0x34
#घोषणा AU6601_REG_CMD_RSP2			0x38
#घोषणा AU6601_REG_CMD_RSP3			0x3C
/* शेष समयout set to 125: 125 * 40ms = 5 sec
 * how exactly it is calculated?
 */
#घोषणा AU6601_TIME_OUT_CTRL			0x69
/* Block size क्रम SDMA or PIO */
#घोषणा AU6601_REG_BLOCK_SIZE			0x6c
/* Some घातer related reg, used together with AU6601_OUTPUT_ENABLE */
#घोषणा AU6601_POWER_CONTROL			0x70

/* PLL ctrl */
#घोषणा AU6601_CLK_SELECT			0x72
#घोषणा	AU6601_CLK_OVER_CLK			0x80
#घोषणा	AU6601_CLK_384_MHZ			0x30
#घोषणा	AU6601_CLK_125_MHZ			0x20
#घोषणा	AU6601_CLK_48_MHZ			0x10
#घोषणा	AU6601_CLK_EXT_PLL			0x04
#घोषणा AU6601_CLK_X2_MODE			0x02
#घोषणा AU6601_CLK_ENABLE			0x01
#घोषणा AU6601_CLK_31_25_MHZ			0x00

#घोषणा AU6601_CLK_DIVIDER			0x73

#घोषणा AU6601_INTERFACE_MODE_CTRL		0x74
#घोषणा AU6601_DLINK_MODE			0x80
#घोषणा	AU6601_INTERRUPT_DELAY_TIME		0x40
#घोषणा	AU6601_SIGNAL_REQ_CTRL			0x30
#घोषणा AU6601_MS_CARD_WP			BIT(3)
#घोषणा AU6601_SD_CARD_WP			BIT(0)

/* same रेजिस्टर values are used क्रम:
 *  - AU6601_OUTPUT_ENABLE
 *  - AU6601_POWER_CONTROL
 */
#घोषणा AU6601_ACTIVE_CTRL			0x75
#घोषणा AU6601_XD_CARD				BIT(4)
/* AU6601_MS_CARD_ACTIVE - will cativate MS card section? */
#घोषणा AU6601_MS_CARD				BIT(3)
#घोषणा AU6601_SD_CARD				BIT(0)

/* card slot state. It should स्वतःmatically detect type of
 * the card
 */
#घोषणा AU6601_DETECT_STATUS			0x76
#घोषणा AU6601_DETECT_EN			BIT(7)
#घोषणा AU6601_MS_DETECTED			BIT(3)
#घोषणा AU6601_SD_DETECTED			BIT(0)
#घोषणा AU6601_DETECT_STATUS_M			0xf

#घोषणा AU6601_REG_SW_RESET			0x79
#घोषणा AU6601_BUF_CTRL_RESET			BIT(7)
#घोषणा AU6601_RESET_DATA			BIT(3)
#घोषणा AU6601_RESET_CMD			BIT(0)

#घोषणा AU6601_OUTPUT_ENABLE			0x7a

#घोषणा AU6601_PAD_DRIVE0			0x7b
#घोषणा AU6601_PAD_DRIVE1			0x7c
#घोषणा AU6601_PAD_DRIVE2			0x7d
/* पढ़ो EEPROM? */
#घोषणा AU6601_FUNCTION				0x7f

#घोषणा AU6601_CMD_XFER_CTRL			0x81
#घोषणा	AU6601_CMD_17_BYTE_CRC			0xc0
#घोषणा	AU6601_CMD_6_BYTE_WO_CRC		0x80
#घोषणा	AU6601_CMD_6_BYTE_CRC			0x40
#घोषणा	AU6601_CMD_START_XFER			0x20
#घोषणा	AU6601_CMD_STOP_WAIT_RDY		0x10
#घोषणा	AU6601_CMD_NO_RESP			0x00

#घोषणा AU6601_REG_BUS_CTRL			0x82
#घोषणा AU6601_BUS_WIDTH_4BIT			0x20
#घोषणा AU6601_BUS_WIDTH_8BIT			0x10
#घोषणा AU6601_BUS_WIDTH_1BIT			0x00

#घोषणा AU6601_DATA_XFER_CTRL			0x83
#घोषणा AU6601_DATA_WRITE			BIT(7)
#घोषणा AU6601_DATA_DMA_MODE			BIT(6)
#घोषणा AU6601_DATA_START_XFER			BIT(0)

#घोषणा AU6601_DATA_PIN_STATE			0x84
#घोषणा AU6601_BUS_STAT_CMD			BIT(15)
/* BIT(4) - BIT(7) are permanently 1.
 * May be reserved or not attached DAT4-DAT7
 */
#घोषणा AU6601_BUS_STAT_DAT3			BIT(3)
#घोषणा AU6601_BUS_STAT_DAT2			BIT(2)
#घोषणा AU6601_BUS_STAT_DAT1			BIT(1)
#घोषणा AU6601_BUS_STAT_DAT0			BIT(0)
#घोषणा AU6601_BUS_STAT_DAT_MASK		0xf

#घोषणा AU6601_OPT				0x85
#घोषणा	AU6601_OPT_CMD_LINE_LEVEL		0x80
#घोषणा	AU6601_OPT_NCRC_16_CLK			BIT(4)
#घोषणा	AU6601_OPT_CMD_NWT			BIT(3)
#घोषणा	AU6601_OPT_STOP_CLK			BIT(2)
#घोषणा	AU6601_OPT_DDR_MODE			BIT(1)
#घोषणा	AU6601_OPT_SD_18V			BIT(0)

#घोषणा AU6601_CLK_DELAY			0x86
#घोषणा	AU6601_CLK_DATA_POSITIVE_EDGE		0x80
#घोषणा	AU6601_CLK_CMD_POSITIVE_EDGE		0x40
#घोषणा	AU6601_CLK_POSITIVE_EDGE_ALL		(AU6601_CLK_CMD_POSITIVE_EDGE \
						| AU6601_CLK_DATA_POSITIVE_EDGE)


#घोषणा AU6601_REG_INT_STATUS			0x90
#घोषणा AU6601_REG_INT_ENABLE			0x94
#घोषणा AU6601_INT_DATA_END_BIT_ERR		BIT(22)
#घोषणा AU6601_INT_DATA_CRC_ERR			BIT(21)
#घोषणा AU6601_INT_DATA_TIMEOUT_ERR		BIT(20)
#घोषणा AU6601_INT_CMD_INDEX_ERR		BIT(19)
#घोषणा AU6601_INT_CMD_END_BIT_ERR		BIT(18)
#घोषणा AU6601_INT_CMD_CRC_ERR			BIT(17)
#घोषणा AU6601_INT_CMD_TIMEOUT_ERR		BIT(16)
#घोषणा AU6601_INT_ERROR			BIT(15)
#घोषणा AU6601_INT_OVER_CURRENT_ERR		BIT(8)
#घोषणा AU6601_INT_CARD_INSERT			BIT(7)
#घोषणा AU6601_INT_CARD_REMOVE			BIT(6)
#घोषणा AU6601_INT_READ_BUF_RDY			BIT(5)
#घोषणा AU6601_INT_WRITE_BUF_RDY		BIT(4)
#घोषणा AU6601_INT_DMA_END			BIT(3)
#घोषणा AU6601_INT_DATA_END			BIT(1)
#घोषणा AU6601_INT_CMD_END			BIT(0)

#घोषणा AU6601_INT_NORMAL_MASK			0x00007FFF
#घोषणा AU6601_INT_ERROR_MASK			0xFFFF8000

#घोषणा AU6601_INT_CMD_MASK	(AU6601_INT_CMD_END | \
		AU6601_INT_CMD_TIMEOUT_ERR | AU6601_INT_CMD_CRC_ERR | \
		AU6601_INT_CMD_END_BIT_ERR | AU6601_INT_CMD_INDEX_ERR)
#घोषणा AU6601_INT_DATA_MASK	(AU6601_INT_DATA_END | AU6601_INT_DMA_END | \
		AU6601_INT_READ_BUF_RDY | AU6601_INT_WRITE_BUF_RDY | \
		AU6601_INT_DATA_TIMEOUT_ERR | AU6601_INT_DATA_CRC_ERR | \
		AU6601_INT_DATA_END_BIT_ERR)
#घोषणा AU6601_INT_ALL_MASK			((u32)-1)

/* MS_CARD mode रेजिस्टरs */

#घोषणा AU6601_MS_STATUS			0xa0

#घोषणा AU6601_MS_BUS_MODE_CTRL			0xa1
#घोषणा AU6601_MS_BUS_8BIT_MODE			0x03
#घोषणा AU6601_MS_BUS_4BIT_MODE			0x01
#घोषणा AU6601_MS_BUS_1BIT_MODE			0x00

#घोषणा AU6601_MS_TPC_CMD			0xa2
#घोषणा AU6601_MS_TPC_READ_PAGE_DATA		0x02
#घोषणा AU6601_MS_TPC_READ_REG			0x04
#घोषणा AU6601_MS_TPC_GET_INT			0x07
#घोषणा AU6601_MS_TPC_WRITE_PAGE_DATA		0x0D
#घोषणा AU6601_MS_TPC_WRITE_REG			0x0B
#घोषणा AU6601_MS_TPC_SET_RW_REG_ADRS		0x08
#घोषणा AU6601_MS_TPC_SET_CMD			0x0E
#घोषणा AU6601_MS_TPC_EX_SET_CMD		0x09
#घोषणा AU6601_MS_TPC_READ_SHORT_DATA		0x03
#घोषणा AU6601_MS_TPC_WRITE_SHORT_DATA		0x0C

#घोषणा AU6601_MS_TRANSFER_MODE			0xa3
#घोषणा	AU6601_MS_XFER_INT_TIMEOUT_CHK		BIT(2)
#घोषणा	AU6601_MS_XFER_DMA_ENABLE		BIT(1)
#घोषणा	AU6601_MS_XFER_START			BIT(0)

#घोषणा AU6601_MS_DATA_PIN_STATE		0xa4

#घोषणा AU6601_MS_INT_STATUS			0xb0
#घोषणा AU6601_MS_INT_ENABLE			0xb4
#घोषणा AU6601_MS_INT_OVER_CURRENT_ERROR	BIT(23)
#घोषणा AU6601_MS_INT_DATA_CRC_ERROR		BIT(21)
#घोषणा AU6601_MS_INT_INT_TIMEOUT		BIT(20)
#घोषणा AU6601_MS_INT_INT_RESP_ERROR		BIT(19)
#घोषणा AU6601_MS_INT_CED_ERROR			BIT(18)
#घोषणा AU6601_MS_INT_TPC_TIMEOUT		BIT(16)
#घोषणा AU6601_MS_INT_ERROR			BIT(15)
#घोषणा AU6601_MS_INT_CARD_INSERT		BIT(7)
#घोषणा AU6601_MS_INT_CARD_REMOVE		BIT(6)
#घोषणा AU6601_MS_INT_BUF_READ_RDY		BIT(5)
#घोषणा AU6601_MS_INT_BUF_WRITE_RDY		BIT(4)
#घोषणा AU6601_MS_INT_DMA_END			BIT(3)
#घोषणा AU6601_MS_INT_TPC_END			BIT(1)

#घोषणा AU6601_MS_INT_DATA_MASK			0x00000038
#घोषणा AU6601_MS_INT_TPC_MASK			0x003d8002
#घोषणा AU6601_MS_INT_TPC_ERROR			0x003d0000

#घोषणा ALCOR_PCIE_LINK_CTRL_OFFSET		0x10
#घोषणा ALCOR_PCIE_LINK_CAP_OFFSET		0x0c
#घोषणा ALCOR_CAP_START_OFFSET			0x34

काष्ठा alcor_dev_cfg अणु
	u8	dma;
पूर्ण;

काष्ठा alcor_pci_priv अणु
	काष्ठा pci_dev *pdev;
	काष्ठा pci_dev *parent_pdev;
	काष्ठा  device *dev;
	व्योम __iomem *iobase;
	अचिन्हित पूर्णांक irq;

	अचिन्हित दीर्घ id; /* idr id */

	काष्ठा alcor_dev_cfg	*cfg;

	/* PCI ASPM related vars */
	पूर्णांक pdev_cap_off;
	u8  pdev_aspm_cap;
	पूर्णांक parent_cap_off;
	u8  parent_aspm_cap;
	u8 ext_config_dev_aspm;
पूर्ण;

व्योम alcor_ग_लिखो8(काष्ठा alcor_pci_priv *priv, u8 val, अचिन्हित पूर्णांक addr);
व्योम alcor_ग_लिखो16(काष्ठा alcor_pci_priv *priv, u16 val, अचिन्हित पूर्णांक addr);
व्योम alcor_ग_लिखो32(काष्ठा alcor_pci_priv *priv, u32 val, अचिन्हित पूर्णांक addr);
व्योम alcor_ग_लिखो32be(काष्ठा alcor_pci_priv *priv, u32 val, अचिन्हित पूर्णांक addr);
u8 alcor_पढ़ो8(काष्ठा alcor_pci_priv *priv, अचिन्हित पूर्णांक addr);
u32 alcor_पढ़ो32(काष्ठा alcor_pci_priv *priv, अचिन्हित पूर्णांक addr);
u32 alcor_पढ़ो32be(काष्ठा alcor_pci_priv *priv, अचिन्हित पूर्णांक addr);
#पूर्ण_अगर
