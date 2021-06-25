<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-2-Clause
/* Copyright (C) 2018 KVASER AB, Sweden. All rights reserved.
 * Parts of this driver are based on the following:
 *  - Kvaser linux pciefd driver (version 5.25)
 *  - PEAK linux canfd driver
 *  - Altera Avalon EPCS flash controller driver
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/pci.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/समयr.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/crc32.h>
#समावेश <linux/iopoll.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Kvaser AB <support@kvaser.com>");
MODULE_DESCRIPTION("CAN driver for Kvaser CAN/PCIe devices");

#घोषणा KVASER_PCIEFD_DRV_NAME "kvaser_pciefd"

#घोषणा KVASER_PCIEFD_WAIT_TIMEOUT msecs_to_jअगरfies(1000)
#घोषणा KVASER_PCIEFD_BEC_POLL_FREQ (jअगरfies + msecs_to_jअगरfies(200))
#घोषणा KVASER_PCIEFD_MAX_ERR_REP 256
#घोषणा KVASER_PCIEFD_CAN_TX_MAX_COUNT 17
#घोषणा KVASER_PCIEFD_MAX_CAN_CHANNELS 4
#घोषणा KVASER_PCIEFD_DMA_COUNT 2

#घोषणा KVASER_PCIEFD_DMA_SIZE (4 * 1024)
#घोषणा KVASER_PCIEFD_64BIT_DMA_BIT BIT(0)

#घोषणा KVASER_PCIEFD_VENDOR 0x1a07
#घोषणा KVASER_PCIEFD_4HS_ID 0x0d
#घोषणा KVASER_PCIEFD_2HS_ID 0x0e
#घोषणा KVASER_PCIEFD_HS_ID 0x0f
#घोषणा KVASER_PCIEFD_MINIPCIE_HS_ID 0x10
#घोषणा KVASER_PCIEFD_MINIPCIE_2HS_ID 0x11

/* PCIe IRQ रेजिस्टरs */
#घोषणा KVASER_PCIEFD_IRQ_REG 0x40
#घोषणा KVASER_PCIEFD_IEN_REG 0x50
/* DMA map */
#घोषणा KVASER_PCIEFD_DMA_MAP_BASE 0x1000
/* Kvaser KCAN CAN controller रेजिस्टरs */
#घोषणा KVASER_PCIEFD_KCAN0_BASE 0x10000
#घोषणा KVASER_PCIEFD_KCAN_BASE_OFFSET 0x1000
#घोषणा KVASER_PCIEFD_KCAN_FIFO_REG 0x100
#घोषणा KVASER_PCIEFD_KCAN_FIFO_LAST_REG 0x180
#घोषणा KVASER_PCIEFD_KCAN_CTRL_REG 0x2c0
#घोषणा KVASER_PCIEFD_KCAN_CMD_REG 0x400
#घोषणा KVASER_PCIEFD_KCAN_IEN_REG 0x408
#घोषणा KVASER_PCIEFD_KCAN_IRQ_REG 0x410
#घोषणा KVASER_PCIEFD_KCAN_TX_NPACKETS_REG 0x414
#घोषणा KVASER_PCIEFD_KCAN_STAT_REG 0x418
#घोषणा KVASER_PCIEFD_KCAN_MODE_REG 0x41c
#घोषणा KVASER_PCIEFD_KCAN_BTRN_REG 0x420
#घोषणा KVASER_PCIEFD_KCAN_BUS_LOAD_REG 0x424
#घोषणा KVASER_PCIEFD_KCAN_BTRD_REG 0x428
#घोषणा KVASER_PCIEFD_KCAN_PWM_REG 0x430
/* Loopback control रेजिस्टर */
#घोषणा KVASER_PCIEFD_LOOP_REG 0x1f000
/* System identअगरication and inक्रमmation रेजिस्टरs */
#घोषणा KVASER_PCIEFD_SYSID_BASE 0x1f020
#घोषणा KVASER_PCIEFD_SYSID_VERSION_REG (KVASER_PCIEFD_SYSID_BASE + 0x8)
#घोषणा KVASER_PCIEFD_SYSID_CANFREQ_REG (KVASER_PCIEFD_SYSID_BASE + 0xc)
#घोषणा KVASER_PCIEFD_SYSID_BUSFREQ_REG (KVASER_PCIEFD_SYSID_BASE + 0x10)
#घोषणा KVASER_PCIEFD_SYSID_BUILD_REG (KVASER_PCIEFD_SYSID_BASE + 0x14)
/* Shared receive buffer रेजिस्टरs */
#घोषणा KVASER_PCIEFD_SRB_BASE 0x1f200
#घोषणा KVASER_PCIEFD_SRB_CMD_REG (KVASER_PCIEFD_SRB_BASE + 0x200)
#घोषणा KVASER_PCIEFD_SRB_IEN_REG (KVASER_PCIEFD_SRB_BASE + 0x204)
#घोषणा KVASER_PCIEFD_SRB_IRQ_REG (KVASER_PCIEFD_SRB_BASE + 0x20c)
#घोषणा KVASER_PCIEFD_SRB_STAT_REG (KVASER_PCIEFD_SRB_BASE + 0x210)
#घोषणा KVASER_PCIEFD_SRB_CTRL_REG (KVASER_PCIEFD_SRB_BASE + 0x218)
/* EPCS flash controller रेजिस्टरs */
#घोषणा KVASER_PCIEFD_SPI_BASE 0x1fc00
#घोषणा KVASER_PCIEFD_SPI_RX_REG KVASER_PCIEFD_SPI_BASE
#घोषणा KVASER_PCIEFD_SPI_TX_REG (KVASER_PCIEFD_SPI_BASE + 0x4)
#घोषणा KVASER_PCIEFD_SPI_STATUS_REG (KVASER_PCIEFD_SPI_BASE + 0x8)
#घोषणा KVASER_PCIEFD_SPI_CTRL_REG (KVASER_PCIEFD_SPI_BASE + 0xc)
#घोषणा KVASER_PCIEFD_SPI_SSEL_REG (KVASER_PCIEFD_SPI_BASE + 0x14)

#घोषणा KVASER_PCIEFD_IRQ_ALL_MSK 0x1f
#घोषणा KVASER_PCIEFD_IRQ_SRB BIT(4)

#घोषणा KVASER_PCIEFD_SYSID_NRCHAN_SHIFT 24
#घोषणा KVASER_PCIEFD_SYSID_MAJOR_VER_SHIFT 16
#घोषणा KVASER_PCIEFD_SYSID_BUILD_VER_SHIFT 1

/* Reset DMA buffer 0, 1 and FIFO offset */
#घोषणा KVASER_PCIEFD_SRB_CMD_RDB0 BIT(4)
#घोषणा KVASER_PCIEFD_SRB_CMD_RDB1 BIT(5)
#घोषणा KVASER_PCIEFD_SRB_CMD_FOR BIT(0)

/* DMA packet करोne, buffer 0 and 1 */
#घोषणा KVASER_PCIEFD_SRB_IRQ_DPD0 BIT(8)
#घोषणा KVASER_PCIEFD_SRB_IRQ_DPD1 BIT(9)
/* DMA overflow, buffer 0 and 1 */
#घोषणा KVASER_PCIEFD_SRB_IRQ_DOF0 BIT(10)
#घोषणा KVASER_PCIEFD_SRB_IRQ_DOF1 BIT(11)
/* DMA underflow, buffer 0 and 1 */
#घोषणा KVASER_PCIEFD_SRB_IRQ_DUF0 BIT(12)
#घोषणा KVASER_PCIEFD_SRB_IRQ_DUF1 BIT(13)

/* DMA idle */
#घोषणा KVASER_PCIEFD_SRB_STAT_DI BIT(15)
/* DMA support */
#घोषणा KVASER_PCIEFD_SRB_STAT_DMA BIT(24)

/* DMA Enable */
#घोषणा KVASER_PCIEFD_SRB_CTRL_DMA_ENABLE BIT(0)

/* EPCS flash controller definitions */
#घोषणा KVASER_PCIEFD_CFG_IMG_SZ (64 * 1024)
#घोषणा KVASER_PCIEFD_CFG_IMG_OFFSET (31 * 65536L)
#घोषणा KVASER_PCIEFD_CFG_MAX_PARAMS 256
#घोषणा KVASER_PCIEFD_CFG_MAGIC 0xcafef00d
#घोषणा KVASER_PCIEFD_CFG_PARAM_MAX_SZ 24
#घोषणा KVASER_PCIEFD_CFG_SYS_VER 1
#घोषणा KVASER_PCIEFD_CFG_PARAM_NR_CHAN 130
#घोषणा KVASER_PCIEFD_SPI_TMT BIT(5)
#घोषणा KVASER_PCIEFD_SPI_TRDY BIT(6)
#घोषणा KVASER_PCIEFD_SPI_RRDY BIT(7)
#घोषणा KVASER_PCIEFD_FLASH_ID_EPCS16 0x14
/* Commands क्रम controlling the onboard flash */
#घोषणा KVASER_PCIEFD_FLASH_RES_CMD 0xab
#घोषणा KVASER_PCIEFD_FLASH_READ_CMD 0x3
#घोषणा KVASER_PCIEFD_FLASH_STATUS_CMD 0x5

/* Kvaser KCAN definitions */
#घोषणा KVASER_PCIEFD_KCAN_CTRL_EFLUSH (4 << 29)
#घोषणा KVASER_PCIEFD_KCAN_CTRL_EFRAME (5 << 29)

#घोषणा KVASER_PCIEFD_KCAN_CMD_SEQ_SHIFT 16
/* Request status packet */
#घोषणा KVASER_PCIEFD_KCAN_CMD_SRQ BIT(0)
/* Abort, flush and reset */
#घोषणा KVASER_PCIEFD_KCAN_CMD_AT BIT(1)

/* Tx FIFO unaligned पढ़ो */
#घोषणा KVASER_PCIEFD_KCAN_IRQ_TAR BIT(0)
/* Tx FIFO unaligned end */
#घोषणा KVASER_PCIEFD_KCAN_IRQ_TAE BIT(1)
/* Bus parameter protection error */
#घोषणा KVASER_PCIEFD_KCAN_IRQ_BPP BIT(2)
/* FDF bit when controller is in classic mode */
#घोषणा KVASER_PCIEFD_KCAN_IRQ_FDIC BIT(3)
/* Rx FIFO overflow */
#घोषणा KVASER_PCIEFD_KCAN_IRQ_ROF BIT(5)
/* Abort करोne */
#घोषणा KVASER_PCIEFD_KCAN_IRQ_ABD BIT(13)
/* Tx buffer flush करोne */
#घोषणा KVASER_PCIEFD_KCAN_IRQ_TFD BIT(14)
/* Tx FIFO overflow */
#घोषणा KVASER_PCIEFD_KCAN_IRQ_TOF BIT(15)
/* Tx FIFO empty */
#घोषणा KVASER_PCIEFD_KCAN_IRQ_TE BIT(16)
/* Transmitter unaligned */
#घोषणा KVASER_PCIEFD_KCAN_IRQ_TAL BIT(17)

#घोषणा KVASER_PCIEFD_KCAN_TX_NPACKETS_MAX_SHIFT 16

#घोषणा KVASER_PCIEFD_KCAN_STAT_SEQNO_SHIFT 24
/* Abort request */
#घोषणा KVASER_PCIEFD_KCAN_STAT_AR BIT(7)
/* Idle state. Controller in reset mode and no पात or flush pending */
#घोषणा KVASER_PCIEFD_KCAN_STAT_IDLE BIT(10)
/* Bus off */
#घोषणा KVASER_PCIEFD_KCAN_STAT_BOFF BIT(11)
/* Reset mode request */
#घोषणा KVASER_PCIEFD_KCAN_STAT_RMR BIT(14)
/* Controller in reset mode */
#घोषणा KVASER_PCIEFD_KCAN_STAT_IRM BIT(15)
/* Controller got one-shot capability */
#घोषणा KVASER_PCIEFD_KCAN_STAT_CAP BIT(16)
/* Controller got CAN FD capability */
#घोषणा KVASER_PCIEFD_KCAN_STAT_FD BIT(19)
#घोषणा KVASER_PCIEFD_KCAN_STAT_BUS_OFF_MSK (KVASER_PCIEFD_KCAN_STAT_AR | \
	KVASER_PCIEFD_KCAN_STAT_BOFF | KVASER_PCIEFD_KCAN_STAT_RMR | \
	KVASER_PCIEFD_KCAN_STAT_IRM)

/* Reset mode */
#घोषणा KVASER_PCIEFD_KCAN_MODE_RM BIT(8)
/* Listen only mode */
#घोषणा KVASER_PCIEFD_KCAN_MODE_LOM BIT(9)
/* Error packet enable */
#घोषणा KVASER_PCIEFD_KCAN_MODE_EPEN BIT(12)
/* CAN FD non-ISO */
#घोषणा KVASER_PCIEFD_KCAN_MODE_NIFDEN BIT(15)
/* Acknowledgment packet type */
#घोषणा KVASER_PCIEFD_KCAN_MODE_APT BIT(20)
/* Active error flag enable. Clear to क्रमce error passive */
#घोषणा KVASER_PCIEFD_KCAN_MODE_EEN BIT(23)
/* Classic CAN mode */
#घोषणा KVASER_PCIEFD_KCAN_MODE_CCM BIT(31)

#घोषणा KVASER_PCIEFD_KCAN_BTRN_SJW_SHIFT 13
#घोषणा KVASER_PCIEFD_KCAN_BTRN_TSEG1_SHIFT 17
#घोषणा KVASER_PCIEFD_KCAN_BTRN_TSEG2_SHIFT 26

#घोषणा KVASER_PCIEFD_KCAN_PWM_TOP_SHIFT 16

/* Kvaser KCAN packet types */
#घोषणा KVASER_PCIEFD_PACK_TYPE_DATA 0
#घोषणा KVASER_PCIEFD_PACK_TYPE_ACK 1
#घोषणा KVASER_PCIEFD_PACK_TYPE_TXRQ 2
#घोषणा KVASER_PCIEFD_PACK_TYPE_ERROR 3
#घोषणा KVASER_PCIEFD_PACK_TYPE_EFLUSH_ACK 4
#घोषणा KVASER_PCIEFD_PACK_TYPE_EFRAME_ACK 5
#घोषणा KVASER_PCIEFD_PACK_TYPE_ACK_DATA 6
#घोषणा KVASER_PCIEFD_PACK_TYPE_STATUS 8
#घोषणा KVASER_PCIEFD_PACK_TYPE_BUS_LOAD 9

/* Kvaser KCAN packet common definitions */
#घोषणा KVASER_PCIEFD_PACKET_SEQ_MSK 0xff
#घोषणा KVASER_PCIEFD_PACKET_CHID_SHIFT 25
#घोषणा KVASER_PCIEFD_PACKET_TYPE_SHIFT 28

/* Kvaser KCAN TDATA and RDATA first word */
#घोषणा KVASER_PCIEFD_RPACKET_IDE BIT(30)
#घोषणा KVASER_PCIEFD_RPACKET_RTR BIT(29)
/* Kvaser KCAN TDATA and RDATA second word */
#घोषणा KVASER_PCIEFD_RPACKET_ESI BIT(13)
#घोषणा KVASER_PCIEFD_RPACKET_BRS BIT(14)
#घोषणा KVASER_PCIEFD_RPACKET_FDF BIT(15)
#घोषणा KVASER_PCIEFD_RPACKET_DLC_SHIFT 8
/* Kvaser KCAN TDATA second word */
#घोषणा KVASER_PCIEFD_TPACKET_SMS BIT(16)
#घोषणा KVASER_PCIEFD_TPACKET_AREQ BIT(31)

/* Kvaser KCAN APACKET */
#घोषणा KVASER_PCIEFD_APACKET_FLU BIT(8)
#घोषणा KVASER_PCIEFD_APACKET_CT BIT(9)
#घोषणा KVASER_PCIEFD_APACKET_ABL BIT(10)
#घोषणा KVASER_PCIEFD_APACKET_NACK BIT(11)

/* Kvaser KCAN SPACK first word */
#घोषणा KVASER_PCIEFD_SPACK_RXERR_SHIFT 8
#घोषणा KVASER_PCIEFD_SPACK_BOFF BIT(16)
#घोषणा KVASER_PCIEFD_SPACK_IDET BIT(20)
#घोषणा KVASER_PCIEFD_SPACK_IRM BIT(21)
#घोषणा KVASER_PCIEFD_SPACK_RMCD BIT(22)
/* Kvaser KCAN SPACK second word */
#घोषणा KVASER_PCIEFD_SPACK_AUTO BIT(21)
#घोषणा KVASER_PCIEFD_SPACK_EWLR BIT(23)
#घोषणा KVASER_PCIEFD_SPACK_EPLR BIT(24)

काष्ठा kvaser_pciefd;

काष्ठा kvaser_pciefd_can अणु
	काष्ठा can_priv can;
	काष्ठा kvaser_pciefd *kv_pcie;
	व्योम __iomem *reg_base;
	काष्ठा can_berr_counter bec;
	u8 cmd_seq;
	पूर्णांक err_rep_cnt;
	पूर्णांक echo_idx;
	spinlock_t lock; /* Locks sensitive रेजिस्टरs (e.g. MODE) */
	spinlock_t echo_lock; /* Locks the message echo buffer */
	काष्ठा समयr_list bec_poll_समयr;
	काष्ठा completion start_comp, flush_comp;
पूर्ण;

काष्ठा kvaser_pciefd अणु
	काष्ठा pci_dev *pci;
	व्योम __iomem *reg_base;
	काष्ठा kvaser_pciefd_can *can[KVASER_PCIEFD_MAX_CAN_CHANNELS];
	व्योम *dma_data[KVASER_PCIEFD_DMA_COUNT];
	u8 nr_channels;
	u32 bus_freq;
	u32 freq;
	u32 freq_to_ticks_भाग;
पूर्ण;

काष्ठा kvaser_pciefd_rx_packet अणु
	u32 header[2];
	u64 बारtamp;
पूर्ण;

काष्ठा kvaser_pciefd_tx_packet अणु
	u32 header[2];
	u8 data[64];
पूर्ण;

अटल स्थिर काष्ठा can_bittiming_स्थिर kvaser_pciefd_bittiming_स्थिर = अणु
	.name = KVASER_PCIEFD_DRV_NAME,
	.tseg1_min = 1,
	.tseg1_max = 512,
	.tseg2_min = 1,
	.tseg2_max = 32,
	.sjw_max = 16,
	.brp_min = 1,
	.brp_max = 8192,
	.brp_inc = 1,
पूर्ण;

काष्ठा kvaser_pciefd_cfg_param अणु
	__le32 magic;
	__le32 nr;
	__le32 len;
	u8 data[KVASER_PCIEFD_CFG_PARAM_MAX_SZ];
पूर्ण;

काष्ठा kvaser_pciefd_cfg_img अणु
	__le32 version;
	__le32 magic;
	__le32 crc;
	काष्ठा kvaser_pciefd_cfg_param params[KVASER_PCIEFD_CFG_MAX_PARAMS];
पूर्ण;

अटल काष्ठा pci_device_id kvaser_pciefd_id_table[] = अणु
	अणु PCI_DEVICE(KVASER_PCIEFD_VENDOR, KVASER_PCIEFD_4HS_ID), पूर्ण,
	अणु PCI_DEVICE(KVASER_PCIEFD_VENDOR, KVASER_PCIEFD_2HS_ID), पूर्ण,
	अणु PCI_DEVICE(KVASER_PCIEFD_VENDOR, KVASER_PCIEFD_HS_ID), पूर्ण,
	अणु PCI_DEVICE(KVASER_PCIEFD_VENDOR, KVASER_PCIEFD_MINIPCIE_HS_ID), पूर्ण,
	अणु PCI_DEVICE(KVASER_PCIEFD_VENDOR, KVASER_PCIEFD_MINIPCIE_2HS_ID), पूर्ण,
	अणु 0,पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, kvaser_pciefd_id_table);

/* Onboard flash memory functions */
अटल पूर्णांक kvaser_pciefd_spi_रुको_loop(काष्ठा kvaser_pciefd *pcie, पूर्णांक msk)
अणु
	u32 res;
	पूर्णांक ret;

	ret = पढ़ोl_poll_समयout(pcie->reg_base + KVASER_PCIEFD_SPI_STATUS_REG,
				 res, res & msk, 0, 10);

	वापस ret;
पूर्ण

अटल पूर्णांक kvaser_pciefd_spi_cmd(काष्ठा kvaser_pciefd *pcie, स्थिर u8 *tx,
				 u32 tx_len, u8 *rx, u32 rx_len)
अणु
	पूर्णांक c;

	ioग_लिखो32(BIT(0), pcie->reg_base + KVASER_PCIEFD_SPI_SSEL_REG);
	ioग_लिखो32(BIT(10), pcie->reg_base + KVASER_PCIEFD_SPI_CTRL_REG);
	ioपढ़ो32(pcie->reg_base + KVASER_PCIEFD_SPI_RX_REG);

	c = tx_len;
	जबतक (c--) अणु
		अगर (kvaser_pciefd_spi_रुको_loop(pcie, KVASER_PCIEFD_SPI_TRDY))
			वापस -EIO;

		ioग_लिखो32(*tx++, pcie->reg_base + KVASER_PCIEFD_SPI_TX_REG);

		अगर (kvaser_pciefd_spi_रुको_loop(pcie, KVASER_PCIEFD_SPI_RRDY))
			वापस -EIO;

		ioपढ़ो32(pcie->reg_base + KVASER_PCIEFD_SPI_RX_REG);
	पूर्ण

	c = rx_len;
	जबतक (c-- > 0) अणु
		अगर (kvaser_pciefd_spi_रुको_loop(pcie, KVASER_PCIEFD_SPI_TRDY))
			वापस -EIO;

		ioग_लिखो32(0, pcie->reg_base + KVASER_PCIEFD_SPI_TX_REG);

		अगर (kvaser_pciefd_spi_रुको_loop(pcie, KVASER_PCIEFD_SPI_RRDY))
			वापस -EIO;

		*rx++ = ioपढ़ो32(pcie->reg_base + KVASER_PCIEFD_SPI_RX_REG);
	पूर्ण

	अगर (kvaser_pciefd_spi_रुको_loop(pcie, KVASER_PCIEFD_SPI_TMT))
		वापस -EIO;

	ioग_लिखो32(0, pcie->reg_base + KVASER_PCIEFD_SPI_CTRL_REG);

	अगर (c != -1) अणु
		dev_err(&pcie->pci->dev, "Flash SPI transfer failed\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kvaser_pciefd_cfg_पढ़ो_and_verअगरy(काष्ठा kvaser_pciefd *pcie,
					     काष्ठा kvaser_pciefd_cfg_img *img)
अणु
	पूर्णांक offset = KVASER_PCIEFD_CFG_IMG_OFFSET;
	पूर्णांक res, crc;
	u8 *crc_buff;

	u8 cmd[] = अणु
		KVASER_PCIEFD_FLASH_READ_CMD,
		(u8)((offset >> 16) & 0xff),
		(u8)((offset >> 8) & 0xff),
		(u8)(offset & 0xff)
	पूर्ण;

	res = kvaser_pciefd_spi_cmd(pcie, cmd, ARRAY_SIZE(cmd), (u8 *)img,
				    KVASER_PCIEFD_CFG_IMG_SZ);
	अगर (res)
		वापस res;

	crc_buff = (u8 *)img->params;

	अगर (le32_to_cpu(img->version) != KVASER_PCIEFD_CFG_SYS_VER) अणु
		dev_err(&pcie->pci->dev,
			"Config flash corrupted, version number is wrong\n");
		वापस -ENODEV;
	पूर्ण

	अगर (le32_to_cpu(img->magic) != KVASER_PCIEFD_CFG_MAGIC) अणु
		dev_err(&pcie->pci->dev,
			"Config flash corrupted, magic number is wrong\n");
		वापस -ENODEV;
	पूर्ण

	crc = ~crc32_be(0xffffffff, crc_buff, माप(img->params));
	अगर (le32_to_cpu(img->crc) != crc) अणु
		dev_err(&pcie->pci->dev,
			"Stored CRC does not match flash image contents\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम kvaser_pciefd_cfg_पढ़ो_params(काष्ठा kvaser_pciefd *pcie,
					  काष्ठा kvaser_pciefd_cfg_img *img)
अणु
	काष्ठा kvaser_pciefd_cfg_param *param;

	param = &img->params[KVASER_PCIEFD_CFG_PARAM_NR_CHAN];
	स_नकल(&pcie->nr_channels, param->data, le32_to_cpu(param->len));
पूर्ण

अटल पूर्णांक kvaser_pciefd_पढ़ो_cfg(काष्ठा kvaser_pciefd *pcie)
अणु
	पूर्णांक res;
	काष्ठा kvaser_pciefd_cfg_img *img;

	/* Read electronic signature */
	u8 cmd[] = अणुKVASER_PCIEFD_FLASH_RES_CMD, 0, 0, 0पूर्ण;

	res = kvaser_pciefd_spi_cmd(pcie, cmd, ARRAY_SIZE(cmd), cmd, 1);
	अगर (res)
		वापस -EIO;

	img = kदो_स्मृति(KVASER_PCIEFD_CFG_IMG_SZ, GFP_KERNEL);
	अगर (!img)
		वापस -ENOMEM;

	अगर (cmd[0] != KVASER_PCIEFD_FLASH_ID_EPCS16) अणु
		dev_err(&pcie->pci->dev,
			"Flash id is 0x%x instead of expected EPCS16 (0x%x)\n",
			cmd[0], KVASER_PCIEFD_FLASH_ID_EPCS16);

		res = -ENODEV;
		जाओ image_मुक्त;
	पूर्ण

	cmd[0] = KVASER_PCIEFD_FLASH_STATUS_CMD;
	res = kvaser_pciefd_spi_cmd(pcie, cmd, 1, cmd, 1);
	अगर (res) अणु
		जाओ image_मुक्त;
	पूर्ण अन्यथा अगर (cmd[0] & 1) अणु
		res = -EIO;
		/* No ग_लिखो is ever करोne, the WIP should never be set */
		dev_err(&pcie->pci->dev, "Unexpected WIP bit set in flash\n");
		जाओ image_मुक्त;
	पूर्ण

	res = kvaser_pciefd_cfg_पढ़ो_and_verअगरy(pcie, img);
	अगर (res) अणु
		res = -EIO;
		जाओ image_मुक्त;
	पूर्ण

	kvaser_pciefd_cfg_पढ़ो_params(pcie, img);

image_मुक्त:
	kमुक्त(img);
	वापस res;
पूर्ण

अटल व्योम kvaser_pciefd_request_status(काष्ठा kvaser_pciefd_can *can)
अणु
	u32 cmd;

	cmd = KVASER_PCIEFD_KCAN_CMD_SRQ;
	cmd |= ++can->cmd_seq << KVASER_PCIEFD_KCAN_CMD_SEQ_SHIFT;
	ioग_लिखो32(cmd, can->reg_base + KVASER_PCIEFD_KCAN_CMD_REG);
पूर्ण

अटल व्योम kvaser_pciefd_enable_err_gen(काष्ठा kvaser_pciefd_can *can)
अणु
	u32 mode;
	अचिन्हित दीर्घ irq;

	spin_lock_irqsave(&can->lock, irq);
	mode = ioपढ़ो32(can->reg_base + KVASER_PCIEFD_KCAN_MODE_REG);
	अगर (!(mode & KVASER_PCIEFD_KCAN_MODE_EPEN)) अणु
		mode |= KVASER_PCIEFD_KCAN_MODE_EPEN;
		ioग_लिखो32(mode, can->reg_base + KVASER_PCIEFD_KCAN_MODE_REG);
	पूर्ण
	spin_unlock_irqrestore(&can->lock, irq);
पूर्ण

अटल व्योम kvaser_pciefd_disable_err_gen(काष्ठा kvaser_pciefd_can *can)
अणु
	u32 mode;
	अचिन्हित दीर्घ irq;

	spin_lock_irqsave(&can->lock, irq);
	mode = ioपढ़ो32(can->reg_base + KVASER_PCIEFD_KCAN_MODE_REG);
	mode &= ~KVASER_PCIEFD_KCAN_MODE_EPEN;
	ioग_लिखो32(mode, can->reg_base + KVASER_PCIEFD_KCAN_MODE_REG);
	spin_unlock_irqrestore(&can->lock, irq);
पूर्ण

अटल पूर्णांक kvaser_pciefd_set_tx_irq(काष्ठा kvaser_pciefd_can *can)
अणु
	u32 msk;

	msk = KVASER_PCIEFD_KCAN_IRQ_TE | KVASER_PCIEFD_KCAN_IRQ_ROF |
	      KVASER_PCIEFD_KCAN_IRQ_TOF | KVASER_PCIEFD_KCAN_IRQ_ABD |
	      KVASER_PCIEFD_KCAN_IRQ_TAE | KVASER_PCIEFD_KCAN_IRQ_TAL |
	      KVASER_PCIEFD_KCAN_IRQ_FDIC | KVASER_PCIEFD_KCAN_IRQ_BPP |
	      KVASER_PCIEFD_KCAN_IRQ_TAR | KVASER_PCIEFD_KCAN_IRQ_TFD;

	ioग_लिखो32(msk, can->reg_base + KVASER_PCIEFD_KCAN_IEN_REG);

	वापस 0;
पूर्ण

अटल व्योम kvaser_pciefd_setup_controller(काष्ठा kvaser_pciefd_can *can)
अणु
	u32 mode;
	अचिन्हित दीर्घ irq;

	spin_lock_irqsave(&can->lock, irq);

	mode = ioपढ़ो32(can->reg_base + KVASER_PCIEFD_KCAN_MODE_REG);
	अगर (can->can.ctrlmode & CAN_CTRLMODE_FD) अणु
		mode &= ~KVASER_PCIEFD_KCAN_MODE_CCM;
		अगर (can->can.ctrlmode & CAN_CTRLMODE_FD_NON_ISO)
			mode |= KVASER_PCIEFD_KCAN_MODE_NIFDEN;
		अन्यथा
			mode &= ~KVASER_PCIEFD_KCAN_MODE_NIFDEN;
	पूर्ण अन्यथा अणु
		mode |= KVASER_PCIEFD_KCAN_MODE_CCM;
		mode &= ~KVASER_PCIEFD_KCAN_MODE_NIFDEN;
	पूर्ण

	अगर (can->can.ctrlmode & CAN_CTRLMODE_LISTENONLY)
		mode |= KVASER_PCIEFD_KCAN_MODE_LOM;

	mode |= KVASER_PCIEFD_KCAN_MODE_EEN;
	mode |= KVASER_PCIEFD_KCAN_MODE_EPEN;
	/* Use ACK packet type */
	mode &= ~KVASER_PCIEFD_KCAN_MODE_APT;
	mode &= ~KVASER_PCIEFD_KCAN_MODE_RM;
	ioग_लिखो32(mode, can->reg_base + KVASER_PCIEFD_KCAN_MODE_REG);

	spin_unlock_irqrestore(&can->lock, irq);
पूर्ण

अटल व्योम kvaser_pciefd_start_controller_flush(काष्ठा kvaser_pciefd_can *can)
अणु
	u32 status;
	अचिन्हित दीर्घ irq;

	spin_lock_irqsave(&can->lock, irq);
	ioग_लिखो32(-1, can->reg_base + KVASER_PCIEFD_KCAN_IRQ_REG);
	ioग_लिखो32(KVASER_PCIEFD_KCAN_IRQ_ABD | KVASER_PCIEFD_KCAN_IRQ_TFD,
		  can->reg_base + KVASER_PCIEFD_KCAN_IEN_REG);

	status = ioपढ़ो32(can->reg_base + KVASER_PCIEFD_KCAN_STAT_REG);
	अगर (status & KVASER_PCIEFD_KCAN_STAT_IDLE) अणु
		u32 cmd;

		/* If controller is alपढ़ोy idle, run पात, flush and reset */
		cmd = KVASER_PCIEFD_KCAN_CMD_AT;
		cmd |= ++can->cmd_seq << KVASER_PCIEFD_KCAN_CMD_SEQ_SHIFT;
		ioग_लिखो32(cmd, can->reg_base + KVASER_PCIEFD_KCAN_CMD_REG);
	पूर्ण अन्यथा अगर (!(status & KVASER_PCIEFD_KCAN_STAT_RMR)) अणु
		u32 mode;

		/* Put controller in reset mode */
		mode = ioपढ़ो32(can->reg_base + KVASER_PCIEFD_KCAN_MODE_REG);
		mode |= KVASER_PCIEFD_KCAN_MODE_RM;
		ioग_लिखो32(mode, can->reg_base + KVASER_PCIEFD_KCAN_MODE_REG);
	पूर्ण

	spin_unlock_irqrestore(&can->lock, irq);
पूर्ण

अटल पूर्णांक kvaser_pciefd_bus_on(काष्ठा kvaser_pciefd_can *can)
अणु
	u32 mode;
	अचिन्हित दीर्घ irq;

	del_समयr(&can->bec_poll_समयr);

	अगर (!completion_करोne(&can->flush_comp))
		kvaser_pciefd_start_controller_flush(can);

	अगर (!रुको_क्रम_completion_समयout(&can->flush_comp,
					 KVASER_PCIEFD_WAIT_TIMEOUT)) अणु
		netdev_err(can->can.dev, "Timeout during bus on flush\n");
		वापस -ETIMEDOUT;
	पूर्ण

	spin_lock_irqsave(&can->lock, irq);
	ioग_लिखो32(0, can->reg_base + KVASER_PCIEFD_KCAN_IEN_REG);
	ioग_लिखो32(-1, can->reg_base + KVASER_PCIEFD_KCAN_IRQ_REG);

	ioग_लिखो32(KVASER_PCIEFD_KCAN_IRQ_ABD | KVASER_PCIEFD_KCAN_IRQ_TFD,
		  can->reg_base + KVASER_PCIEFD_KCAN_IEN_REG);

	mode = ioपढ़ो32(can->reg_base + KVASER_PCIEFD_KCAN_MODE_REG);
	mode &= ~KVASER_PCIEFD_KCAN_MODE_RM;
	ioग_लिखो32(mode, can->reg_base + KVASER_PCIEFD_KCAN_MODE_REG);
	spin_unlock_irqrestore(&can->lock, irq);

	अगर (!रुको_क्रम_completion_समयout(&can->start_comp,
					 KVASER_PCIEFD_WAIT_TIMEOUT)) अणु
		netdev_err(can->can.dev, "Timeout during bus on reset\n");
		वापस -ETIMEDOUT;
	पूर्ण
	/* Reset पूर्णांकerrupt handling */
	ioग_लिखो32(0, can->reg_base + KVASER_PCIEFD_KCAN_IEN_REG);
	ioग_लिखो32(-1, can->reg_base + KVASER_PCIEFD_KCAN_IRQ_REG);

	kvaser_pciefd_set_tx_irq(can);
	kvaser_pciefd_setup_controller(can);

	can->can.state = CAN_STATE_ERROR_ACTIVE;
	netअगर_wake_queue(can->can.dev);
	can->bec.txerr = 0;
	can->bec.rxerr = 0;
	can->err_rep_cnt = 0;

	वापस 0;
पूर्ण

अटल व्योम kvaser_pciefd_pwm_stop(काष्ठा kvaser_pciefd_can *can)
अणु
	u8 top;
	u32 pwm_ctrl;
	अचिन्हित दीर्घ irq;

	spin_lock_irqsave(&can->lock, irq);
	pwm_ctrl = ioपढ़ो32(can->reg_base + KVASER_PCIEFD_KCAN_PWM_REG);
	top = (pwm_ctrl >> KVASER_PCIEFD_KCAN_PWM_TOP_SHIFT) & 0xff;

	/* Set duty cycle to zero */
	pwm_ctrl |= top;
	ioग_लिखो32(pwm_ctrl, can->reg_base + KVASER_PCIEFD_KCAN_PWM_REG);
	spin_unlock_irqrestore(&can->lock, irq);
पूर्ण

अटल व्योम kvaser_pciefd_pwm_start(काष्ठा kvaser_pciefd_can *can)
अणु
	पूर्णांक top, trigger;
	u32 pwm_ctrl;
	अचिन्हित दीर्घ irq;

	kvaser_pciefd_pwm_stop(can);
	spin_lock_irqsave(&can->lock, irq);

	/* Set frequency to 500 KHz*/
	top = can->kv_pcie->bus_freq / (2 * 500000) - 1;

	pwm_ctrl = top & 0xff;
	pwm_ctrl |= (top & 0xff) << KVASER_PCIEFD_KCAN_PWM_TOP_SHIFT;
	ioग_लिखो32(pwm_ctrl, can->reg_base + KVASER_PCIEFD_KCAN_PWM_REG);

	/* Set duty cycle to 95 */
	trigger = (100 * top - 95 * (top + 1) + 50) / 100;
	pwm_ctrl = trigger & 0xff;
	pwm_ctrl |= (top & 0xff) << KVASER_PCIEFD_KCAN_PWM_TOP_SHIFT;
	ioग_लिखो32(pwm_ctrl, can->reg_base + KVASER_PCIEFD_KCAN_PWM_REG);
	spin_unlock_irqrestore(&can->lock, irq);
पूर्ण

अटल पूर्णांक kvaser_pciefd_खोलो(काष्ठा net_device *netdev)
अणु
	पूर्णांक err;
	काष्ठा kvaser_pciefd_can *can = netdev_priv(netdev);

	err = खोलो_candev(netdev);
	अगर (err)
		वापस err;

	err = kvaser_pciefd_bus_on(can);
	अगर (err) अणु
		बंद_candev(netdev);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kvaser_pciefd_stop(काष्ठा net_device *netdev)
अणु
	काष्ठा kvaser_pciefd_can *can = netdev_priv(netdev);
	पूर्णांक ret = 0;

	/* Don't पूर्णांकerrupt ongoing flush */
	अगर (!completion_करोne(&can->flush_comp))
		kvaser_pciefd_start_controller_flush(can);

	अगर (!रुको_क्रम_completion_समयout(&can->flush_comp,
					 KVASER_PCIEFD_WAIT_TIMEOUT)) अणु
		netdev_err(can->can.dev, "Timeout during stop\n");
		ret = -ETIMEDOUT;
	पूर्ण अन्यथा अणु
		ioग_लिखो32(0, can->reg_base + KVASER_PCIEFD_KCAN_IEN_REG);
		del_समयr(&can->bec_poll_समयr);
	पूर्ण
	बंद_candev(netdev);

	वापस ret;
पूर्ण

अटल पूर्णांक kvaser_pciefd_prepare_tx_packet(काष्ठा kvaser_pciefd_tx_packet *p,
					   काष्ठा kvaser_pciefd_can *can,
					   काष्ठा sk_buff *skb)
अणु
	काष्ठा canfd_frame *cf = (काष्ठा canfd_frame *)skb->data;
	पूर्णांक packet_size;
	पूर्णांक seq = can->echo_idx;

	स_रखो(p, 0, माप(*p));

	अगर (can->can.ctrlmode & CAN_CTRLMODE_ONE_SHOT)
		p->header[1] |= KVASER_PCIEFD_TPACKET_SMS;

	अगर (cf->can_id & CAN_RTR_FLAG)
		p->header[0] |= KVASER_PCIEFD_RPACKET_RTR;

	अगर (cf->can_id & CAN_EFF_FLAG)
		p->header[0] |= KVASER_PCIEFD_RPACKET_IDE;

	p->header[0] |= cf->can_id & CAN_EFF_MASK;
	p->header[1] |= can_fd_len2dlc(cf->len) << KVASER_PCIEFD_RPACKET_DLC_SHIFT;
	p->header[1] |= KVASER_PCIEFD_TPACKET_AREQ;

	अगर (can_is_canfd_skb(skb)) अणु
		p->header[1] |= KVASER_PCIEFD_RPACKET_FDF;
		अगर (cf->flags & CANFD_BRS)
			p->header[1] |= KVASER_PCIEFD_RPACKET_BRS;
		अगर (cf->flags & CANFD_ESI)
			p->header[1] |= KVASER_PCIEFD_RPACKET_ESI;
	पूर्ण

	p->header[1] |= seq & KVASER_PCIEFD_PACKET_SEQ_MSK;

	packet_size = cf->len;
	स_नकल(p->data, cf->data, packet_size);

	वापस DIV_ROUND_UP(packet_size, 4);
पूर्ण

अटल netdev_tx_t kvaser_pciefd_start_xmit(काष्ठा sk_buff *skb,
					    काष्ठा net_device *netdev)
अणु
	काष्ठा kvaser_pciefd_can *can = netdev_priv(netdev);
	अचिन्हित दीर्घ irq_flags;
	काष्ठा kvaser_pciefd_tx_packet packet;
	पूर्णांक nwords;
	u8 count;

	अगर (can_dropped_invalid_skb(netdev, skb))
		वापस NETDEV_TX_OK;

	nwords = kvaser_pciefd_prepare_tx_packet(&packet, can, skb);

	spin_lock_irqsave(&can->echo_lock, irq_flags);

	/* Prepare and save echo skb in पूर्णांकernal slot */
	can_put_echo_skb(skb, netdev, can->echo_idx, 0);

	/* Move echo index to the next slot */
	can->echo_idx = (can->echo_idx + 1) % can->can.echo_skb_max;

	/* Write header to fअगरo */
	ioग_लिखो32(packet.header[0],
		  can->reg_base + KVASER_PCIEFD_KCAN_FIFO_REG);
	ioग_लिखो32(packet.header[1],
		  can->reg_base + KVASER_PCIEFD_KCAN_FIFO_REG);

	अगर (nwords) अणु
		u32 data_last = ((u32 *)packet.data)[nwords - 1];

		/* Write data to fअगरo, except last word */
		ioग_लिखो32_rep(can->reg_base +
			      KVASER_PCIEFD_KCAN_FIFO_REG, packet.data,
			      nwords - 1);
		/* Write last word to end of fअगरo */
		__raw_ग_लिखोl(data_last, can->reg_base +
			     KVASER_PCIEFD_KCAN_FIFO_LAST_REG);
	पूर्ण अन्यथा अणु
		/* Complete ग_लिखो to fअगरo */
		__raw_ग_लिखोl(0, can->reg_base +
			     KVASER_PCIEFD_KCAN_FIFO_LAST_REG);
	पूर्ण

	count = ioपढ़ो32(can->reg_base + KVASER_PCIEFD_KCAN_TX_NPACKETS_REG);
	/* No room क्रम a new message, stop the queue until at least one
	 * successful transmit
	 */
	अगर (count >= KVASER_PCIEFD_CAN_TX_MAX_COUNT ||
	    can->can.echo_skb[can->echo_idx])
		netअगर_stop_queue(netdev);

	spin_unlock_irqrestore(&can->echo_lock, irq_flags);

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक kvaser_pciefd_set_bittiming(काष्ठा kvaser_pciefd_can *can, bool data)
अणु
	u32 mode, test, btrn;
	अचिन्हित दीर्घ irq_flags;
	पूर्णांक ret;
	काष्ठा can_bittiming *bt;

	अगर (data)
		bt = &can->can.data_bittiming;
	अन्यथा
		bt = &can->can.bittiming;

	btrn = ((bt->phase_seg2 - 1) & 0x1f) <<
	       KVASER_PCIEFD_KCAN_BTRN_TSEG2_SHIFT |
	       (((bt->prop_seg + bt->phase_seg1) - 1) & 0x1ff) <<
	       KVASER_PCIEFD_KCAN_BTRN_TSEG1_SHIFT |
	       ((bt->sjw - 1) & 0xf) << KVASER_PCIEFD_KCAN_BTRN_SJW_SHIFT |
	       ((bt->brp - 1) & 0x1fff);

	spin_lock_irqsave(&can->lock, irq_flags);
	mode = ioपढ़ो32(can->reg_base + KVASER_PCIEFD_KCAN_MODE_REG);

	/* Put the circuit in reset mode */
	ioग_लिखो32(mode | KVASER_PCIEFD_KCAN_MODE_RM,
		  can->reg_base + KVASER_PCIEFD_KCAN_MODE_REG);

	/* Can only set bittiming अगर in reset mode */
	ret = पढ़ोl_poll_समयout(can->reg_base + KVASER_PCIEFD_KCAN_MODE_REG,
				 test, test & KVASER_PCIEFD_KCAN_MODE_RM,
				 0, 10);

	अगर (ret) अणु
		spin_unlock_irqrestore(&can->lock, irq_flags);
		वापस -EBUSY;
	पूर्ण

	अगर (data)
		ioग_लिखो32(btrn, can->reg_base + KVASER_PCIEFD_KCAN_BTRD_REG);
	अन्यथा
		ioग_लिखो32(btrn, can->reg_base + KVASER_PCIEFD_KCAN_BTRN_REG);

	/* Restore previous reset mode status */
	ioग_लिखो32(mode, can->reg_base + KVASER_PCIEFD_KCAN_MODE_REG);

	spin_unlock_irqrestore(&can->lock, irq_flags);
	वापस 0;
पूर्ण

अटल पूर्णांक kvaser_pciefd_set_nominal_bittiming(काष्ठा net_device *ndev)
अणु
	वापस kvaser_pciefd_set_bittiming(netdev_priv(ndev), false);
पूर्ण

अटल पूर्णांक kvaser_pciefd_set_data_bittiming(काष्ठा net_device *ndev)
अणु
	वापस kvaser_pciefd_set_bittiming(netdev_priv(ndev), true);
पूर्ण

अटल पूर्णांक kvaser_pciefd_set_mode(काष्ठा net_device *ndev, क्रमागत can_mode mode)
अणु
	काष्ठा kvaser_pciefd_can *can = netdev_priv(ndev);
	पूर्णांक ret = 0;

	चयन (mode) अणु
	हाल CAN_MODE_START:
		अगर (!can->can.restart_ms)
			ret = kvaser_pciefd_bus_on(can);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक kvaser_pciefd_get_berr_counter(स्थिर काष्ठा net_device *ndev,
					  काष्ठा can_berr_counter *bec)
अणु
	काष्ठा kvaser_pciefd_can *can = netdev_priv(ndev);

	bec->rxerr = can->bec.rxerr;
	bec->txerr = can->bec.txerr;
	वापस 0;
पूर्ण

अटल व्योम kvaser_pciefd_bec_poll_समयr(काष्ठा समयr_list *data)
अणु
	काष्ठा kvaser_pciefd_can *can = from_समयr(can, data, bec_poll_समयr);

	kvaser_pciefd_enable_err_gen(can);
	kvaser_pciefd_request_status(can);
	can->err_rep_cnt = 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops kvaser_pciefd_netdev_ops = अणु
	.nकरो_खोलो = kvaser_pciefd_खोलो,
	.nकरो_stop = kvaser_pciefd_stop,
	.nकरो_start_xmit = kvaser_pciefd_start_xmit,
	.nकरो_change_mtu = can_change_mtu,
पूर्ण;

अटल पूर्णांक kvaser_pciefd_setup_can_ctrls(काष्ठा kvaser_pciefd *pcie)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pcie->nr_channels; i++) अणु
		काष्ठा net_device *netdev;
		काष्ठा kvaser_pciefd_can *can;
		u32 status, tx_npackets;

		netdev = alloc_candev(माप(काष्ठा kvaser_pciefd_can),
				      KVASER_PCIEFD_CAN_TX_MAX_COUNT);
		अगर (!netdev)
			वापस -ENOMEM;

		can = netdev_priv(netdev);
		netdev->netdev_ops = &kvaser_pciefd_netdev_ops;
		can->reg_base = pcie->reg_base + KVASER_PCIEFD_KCAN0_BASE +
				i * KVASER_PCIEFD_KCAN_BASE_OFFSET;

		can->kv_pcie = pcie;
		can->cmd_seq = 0;
		can->err_rep_cnt = 0;
		can->bec.txerr = 0;
		can->bec.rxerr = 0;

		init_completion(&can->start_comp);
		init_completion(&can->flush_comp);
		समयr_setup(&can->bec_poll_समयr, kvaser_pciefd_bec_poll_समयr,
			    0);

		/* Disable Bus load reporting */
		ioग_लिखो32(0, can->reg_base + KVASER_PCIEFD_KCAN_BUS_LOAD_REG);

		tx_npackets = ioपढ़ो32(can->reg_base +
				       KVASER_PCIEFD_KCAN_TX_NPACKETS_REG);
		अगर (((tx_npackets >> KVASER_PCIEFD_KCAN_TX_NPACKETS_MAX_SHIFT) &
		      0xff) < KVASER_PCIEFD_CAN_TX_MAX_COUNT) अणु
			dev_err(&pcie->pci->dev,
				"Max Tx count is smaller than expected\n");

			मुक्त_candev(netdev);
			वापस -ENODEV;
		पूर्ण

		can->can.घड़ी.freq = pcie->freq;
		can->can.echo_skb_max = KVASER_PCIEFD_CAN_TX_MAX_COUNT;
		can->echo_idx = 0;
		spin_lock_init(&can->echo_lock);
		spin_lock_init(&can->lock);
		can->can.bittiming_स्थिर = &kvaser_pciefd_bittiming_स्थिर;
		can->can.data_bittiming_स्थिर = &kvaser_pciefd_bittiming_स्थिर;

		can->can.करो_set_bittiming = kvaser_pciefd_set_nominal_bittiming;
		can->can.करो_set_data_bittiming =
			kvaser_pciefd_set_data_bittiming;

		can->can.करो_set_mode = kvaser_pciefd_set_mode;
		can->can.करो_get_berr_counter = kvaser_pciefd_get_berr_counter;

		can->can.ctrlmode_supported = CAN_CTRLMODE_LISTENONLY |
					      CAN_CTRLMODE_FD |
					      CAN_CTRLMODE_FD_NON_ISO;

		status = ioपढ़ो32(can->reg_base + KVASER_PCIEFD_KCAN_STAT_REG);
		अगर (!(status & KVASER_PCIEFD_KCAN_STAT_FD)) अणु
			dev_err(&pcie->pci->dev,
				"CAN FD not supported as expected %d\n", i);

			मुक्त_candev(netdev);
			वापस -ENODEV;
		पूर्ण

		अगर (status & KVASER_PCIEFD_KCAN_STAT_CAP)
			can->can.ctrlmode_supported |= CAN_CTRLMODE_ONE_SHOT;

		netdev->flags |= IFF_ECHO;

		SET_NETDEV_DEV(netdev, &pcie->pci->dev);

		ioग_लिखो32(-1, can->reg_base + KVASER_PCIEFD_KCAN_IRQ_REG);
		ioग_लिखो32(KVASER_PCIEFD_KCAN_IRQ_ABD |
			  KVASER_PCIEFD_KCAN_IRQ_TFD,
			  can->reg_base + KVASER_PCIEFD_KCAN_IEN_REG);

		pcie->can[i] = can;
		kvaser_pciefd_pwm_start(can);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kvaser_pciefd_reg_candev(काष्ठा kvaser_pciefd *pcie)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pcie->nr_channels; i++) अणु
		पूर्णांक err = रेजिस्टर_candev(pcie->can[i]->can.dev);

		अगर (err) अणु
			पूर्णांक j;

			/* Unरेजिस्टर all successfully रेजिस्टरed devices. */
			क्रम (j = 0; j < i; j++)
				unरेजिस्टर_candev(pcie->can[j]->can.dev);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम kvaser_pciefd_ग_लिखो_dma_map(काष्ठा kvaser_pciefd *pcie,
					dma_addr_t addr, पूर्णांक offset)
अणु
	u32 word1, word2;

#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
	word1 = addr | KVASER_PCIEFD_64BIT_DMA_BIT;
	word2 = addr >> 32;
#अन्यथा
	word1 = addr;
	word2 = 0;
#पूर्ण_अगर
	ioग_लिखो32(word1, pcie->reg_base + offset);
	ioग_लिखो32(word2, pcie->reg_base + offset + 4);
पूर्ण

अटल पूर्णांक kvaser_pciefd_setup_dma(काष्ठा kvaser_pciefd *pcie)
अणु
	पूर्णांक i;
	u32 srb_status;
	dma_addr_t dma_addr[KVASER_PCIEFD_DMA_COUNT];

	/* Disable the DMA */
	ioग_लिखो32(0, pcie->reg_base + KVASER_PCIEFD_SRB_CTRL_REG);
	क्रम (i = 0; i < KVASER_PCIEFD_DMA_COUNT; i++) अणु
		अचिन्हित पूर्णांक offset = KVASER_PCIEFD_DMA_MAP_BASE + 8 * i;

		pcie->dma_data[i] =
			dmam_alloc_coherent(&pcie->pci->dev,
					    KVASER_PCIEFD_DMA_SIZE,
					    &dma_addr[i],
					    GFP_KERNEL);

		अगर (!pcie->dma_data[i] || !dma_addr[i]) अणु
			dev_err(&pcie->pci->dev, "Rx dma_alloc(%u) failure\n",
				KVASER_PCIEFD_DMA_SIZE);
			वापस -ENOMEM;
		पूर्ण

		kvaser_pciefd_ग_लिखो_dma_map(pcie, dma_addr[i], offset);
	पूर्ण

	/* Reset Rx FIFO, and both DMA buffers */
	ioग_लिखो32(KVASER_PCIEFD_SRB_CMD_FOR | KVASER_PCIEFD_SRB_CMD_RDB0 |
		  KVASER_PCIEFD_SRB_CMD_RDB1,
		  pcie->reg_base + KVASER_PCIEFD_SRB_CMD_REG);

	srb_status = ioपढ़ो32(pcie->reg_base + KVASER_PCIEFD_SRB_STAT_REG);
	अगर (!(srb_status & KVASER_PCIEFD_SRB_STAT_DI)) अणु
		dev_err(&pcie->pci->dev, "DMA not idle before enabling\n");
		वापस -EIO;
	पूर्ण

	/* Enable the DMA */
	ioग_लिखो32(KVASER_PCIEFD_SRB_CTRL_DMA_ENABLE,
		  pcie->reg_base + KVASER_PCIEFD_SRB_CTRL_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक kvaser_pciefd_setup_board(काष्ठा kvaser_pciefd *pcie)
अणु
	u32 sysid, srb_status, build;
	u8 sysid_nr_chan;
	पूर्णांक ret;

	ret = kvaser_pciefd_पढ़ो_cfg(pcie);
	अगर (ret)
		वापस ret;

	sysid = ioपढ़ो32(pcie->reg_base + KVASER_PCIEFD_SYSID_VERSION_REG);
	sysid_nr_chan = (sysid >> KVASER_PCIEFD_SYSID_NRCHAN_SHIFT) & 0xff;
	अगर (pcie->nr_channels != sysid_nr_chan) अणु
		dev_err(&pcie->pci->dev,
			"Number of channels does not match: %u vs %u\n",
			pcie->nr_channels,
			sysid_nr_chan);
		वापस -ENODEV;
	पूर्ण

	अगर (pcie->nr_channels > KVASER_PCIEFD_MAX_CAN_CHANNELS)
		pcie->nr_channels = KVASER_PCIEFD_MAX_CAN_CHANNELS;

	build = ioपढ़ो32(pcie->reg_base + KVASER_PCIEFD_SYSID_BUILD_REG);
	dev_dbg(&pcie->pci->dev, "Version %u.%u.%u\n",
		(sysid >> KVASER_PCIEFD_SYSID_MAJOR_VER_SHIFT) & 0xff,
		sysid & 0xff,
		(build >> KVASER_PCIEFD_SYSID_BUILD_VER_SHIFT) & 0x7fff);

	srb_status = ioपढ़ो32(pcie->reg_base + KVASER_PCIEFD_SRB_STAT_REG);
	अगर (!(srb_status & KVASER_PCIEFD_SRB_STAT_DMA)) अणु
		dev_err(&pcie->pci->dev,
			"Hardware without DMA is not supported\n");
		वापस -ENODEV;
	पूर्ण

	pcie->bus_freq = ioपढ़ो32(pcie->reg_base +
				  KVASER_PCIEFD_SYSID_BUSFREQ_REG);
	pcie->freq = ioपढ़ो32(pcie->reg_base + KVASER_PCIEFD_SYSID_CANFREQ_REG);
	pcie->freq_to_ticks_भाग = pcie->freq / 1000000;
	अगर (pcie->freq_to_ticks_भाग == 0)
		pcie->freq_to_ticks_भाग = 1;

	/* Turn off all loopback functionality */
	ioग_लिखो32(0, pcie->reg_base + KVASER_PCIEFD_LOOP_REG);
	वापस ret;
पूर्ण

अटल पूर्णांक kvaser_pciefd_handle_data_packet(काष्ठा kvaser_pciefd *pcie,
					    काष्ठा kvaser_pciefd_rx_packet *p,
					    __le32 *data)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा canfd_frame *cf;
	काष्ठा can_priv *priv;
	काष्ठा net_device_stats *stats;
	काष्ठा skb_shared_hwtstamps *shhwtstamps;
	u8 ch_id = (p->header[1] >> KVASER_PCIEFD_PACKET_CHID_SHIFT) & 0x7;

	अगर (ch_id >= pcie->nr_channels)
		वापस -EIO;

	priv = &pcie->can[ch_id]->can;
	stats = &priv->dev->stats;

	अगर (p->header[1] & KVASER_PCIEFD_RPACKET_FDF) अणु
		skb = alloc_canfd_skb(priv->dev, &cf);
		अगर (!skb) अणु
			stats->rx_dropped++;
			वापस -ENOMEM;
		पूर्ण

		अगर (p->header[1] & KVASER_PCIEFD_RPACKET_BRS)
			cf->flags |= CANFD_BRS;

		अगर (p->header[1] & KVASER_PCIEFD_RPACKET_ESI)
			cf->flags |= CANFD_ESI;
	पूर्ण अन्यथा अणु
		skb = alloc_can_skb(priv->dev, (काष्ठा can_frame **)&cf);
		अगर (!skb) अणु
			stats->rx_dropped++;
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	cf->can_id = p->header[0] & CAN_EFF_MASK;
	अगर (p->header[0] & KVASER_PCIEFD_RPACKET_IDE)
		cf->can_id |= CAN_EFF_FLAG;

	cf->len = can_fd_dlc2len(p->header[1] >> KVASER_PCIEFD_RPACKET_DLC_SHIFT);

	अगर (p->header[0] & KVASER_PCIEFD_RPACKET_RTR)
		cf->can_id |= CAN_RTR_FLAG;
	अन्यथा
		स_नकल(cf->data, data, cf->len);

	shhwtstamps = skb_hwtstamps(skb);

	shhwtstamps->hwtstamp =
		ns_to_kसमय(भाग_u64(p->बारtamp * 1000,
				    pcie->freq_to_ticks_भाग));

	stats->rx_bytes += cf->len;
	stats->rx_packets++;

	वापस netअगर_rx(skb);
पूर्ण

अटल व्योम kvaser_pciefd_change_state(काष्ठा kvaser_pciefd_can *can,
				       काष्ठा can_frame *cf,
				       क्रमागत can_state new_state,
				       क्रमागत can_state tx_state,
				       क्रमागत can_state rx_state)
अणु
	can_change_state(can->can.dev, cf, tx_state, rx_state);

	अगर (new_state == CAN_STATE_BUS_OFF) अणु
		काष्ठा net_device *ndev = can->can.dev;
		अचिन्हित दीर्घ irq_flags;

		spin_lock_irqsave(&can->lock, irq_flags);
		netअगर_stop_queue(can->can.dev);
		spin_unlock_irqrestore(&can->lock, irq_flags);

		/* Prevent CAN controller from स्वतः recover from bus off */
		अगर (!can->can.restart_ms) अणु
			kvaser_pciefd_start_controller_flush(can);
			can_bus_off(ndev);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम kvaser_pciefd_packet_to_state(काष्ठा kvaser_pciefd_rx_packet *p,
					  काष्ठा can_berr_counter *bec,
					  क्रमागत can_state *new_state,
					  क्रमागत can_state *tx_state,
					  क्रमागत can_state *rx_state)
अणु
	अगर (p->header[0] & KVASER_PCIEFD_SPACK_BOFF ||
	    p->header[0] & KVASER_PCIEFD_SPACK_IRM)
		*new_state = CAN_STATE_BUS_OFF;
	अन्यथा अगर (bec->txerr >= 255 ||  bec->rxerr >= 255)
		*new_state = CAN_STATE_BUS_OFF;
	अन्यथा अगर (p->header[1] & KVASER_PCIEFD_SPACK_EPLR)
		*new_state = CAN_STATE_ERROR_PASSIVE;
	अन्यथा अगर (bec->txerr >= 128 || bec->rxerr >= 128)
		*new_state = CAN_STATE_ERROR_PASSIVE;
	अन्यथा अगर (p->header[1] & KVASER_PCIEFD_SPACK_EWLR)
		*new_state = CAN_STATE_ERROR_WARNING;
	अन्यथा अगर (bec->txerr >= 96 || bec->rxerr >= 96)
		*new_state = CAN_STATE_ERROR_WARNING;
	अन्यथा
		*new_state = CAN_STATE_ERROR_ACTIVE;

	*tx_state = bec->txerr >= bec->rxerr ? *new_state : 0;
	*rx_state = bec->txerr <= bec->rxerr ? *new_state : 0;
पूर्ण

अटल पूर्णांक kvaser_pciefd_rx_error_frame(काष्ठा kvaser_pciefd_can *can,
					काष्ठा kvaser_pciefd_rx_packet *p)
अणु
	काष्ठा can_berr_counter bec;
	क्रमागत can_state old_state, new_state, tx_state, rx_state;
	काष्ठा net_device *ndev = can->can.dev;
	काष्ठा sk_buff *skb;
	काष्ठा can_frame *cf = शून्य;
	काष्ठा skb_shared_hwtstamps *shhwtstamps;
	काष्ठा net_device_stats *stats = &ndev->stats;

	old_state = can->can.state;

	bec.txerr = p->header[0] & 0xff;
	bec.rxerr = (p->header[0] >> KVASER_PCIEFD_SPACK_RXERR_SHIFT) & 0xff;

	kvaser_pciefd_packet_to_state(p, &bec, &new_state, &tx_state,
				      &rx_state);

	skb = alloc_can_err_skb(ndev, &cf);

	अगर (new_state != old_state) अणु
		kvaser_pciefd_change_state(can, cf, new_state, tx_state,
					   rx_state);

		अगर (old_state == CAN_STATE_BUS_OFF &&
		    new_state == CAN_STATE_ERROR_ACTIVE &&
		    can->can.restart_ms) अणु
			can->can.can_stats.restarts++;
			अगर (skb)
				cf->can_id |= CAN_ERR_RESTARTED;
		पूर्ण
	पूर्ण

	can->err_rep_cnt++;
	can->can.can_stats.bus_error++;
	stats->rx_errors++;

	can->bec.txerr = bec.txerr;
	can->bec.rxerr = bec.rxerr;

	अगर (!skb) अणु
		stats->rx_dropped++;
		वापस -ENOMEM;
	पूर्ण

	shhwtstamps = skb_hwtstamps(skb);
	shhwtstamps->hwtstamp =
		ns_to_kसमय(भाग_u64(p->बारtamp * 1000,
				    can->kv_pcie->freq_to_ticks_भाग));
	cf->can_id |= CAN_ERR_BUSERROR;

	cf->data[6] = bec.txerr;
	cf->data[7] = bec.rxerr;

	stats->rx_packets++;
	stats->rx_bytes += cf->len;

	netअगर_rx(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक kvaser_pciefd_handle_error_packet(काष्ठा kvaser_pciefd *pcie,
					     काष्ठा kvaser_pciefd_rx_packet *p)
अणु
	काष्ठा kvaser_pciefd_can *can;
	u8 ch_id = (p->header[1] >> KVASER_PCIEFD_PACKET_CHID_SHIFT) & 0x7;

	अगर (ch_id >= pcie->nr_channels)
		वापस -EIO;

	can = pcie->can[ch_id];

	kvaser_pciefd_rx_error_frame(can, p);
	अगर (can->err_rep_cnt >= KVASER_PCIEFD_MAX_ERR_REP)
		/* Do not report more errors, until bec_poll_समयr expires */
		kvaser_pciefd_disable_err_gen(can);
	/* Start polling the error counters */
	mod_समयr(&can->bec_poll_समयr, KVASER_PCIEFD_BEC_POLL_FREQ);
	वापस 0;
पूर्ण

अटल पूर्णांक kvaser_pciefd_handle_status_resp(काष्ठा kvaser_pciefd_can *can,
					    काष्ठा kvaser_pciefd_rx_packet *p)
अणु
	काष्ठा can_berr_counter bec;
	क्रमागत can_state old_state, new_state, tx_state, rx_state;

	old_state = can->can.state;

	bec.txerr = p->header[0] & 0xff;
	bec.rxerr = (p->header[0] >> KVASER_PCIEFD_SPACK_RXERR_SHIFT) & 0xff;

	kvaser_pciefd_packet_to_state(p, &bec, &new_state, &tx_state,
				      &rx_state);

	अगर (new_state != old_state) अणु
		काष्ठा net_device *ndev = can->can.dev;
		काष्ठा sk_buff *skb;
		काष्ठा can_frame *cf;
		काष्ठा skb_shared_hwtstamps *shhwtstamps;

		skb = alloc_can_err_skb(ndev, &cf);
		अगर (!skb) अणु
			काष्ठा net_device_stats *stats = &ndev->stats;

			stats->rx_dropped++;
			वापस -ENOMEM;
		पूर्ण

		kvaser_pciefd_change_state(can, cf, new_state, tx_state,
					   rx_state);

		अगर (old_state == CAN_STATE_BUS_OFF &&
		    new_state == CAN_STATE_ERROR_ACTIVE &&
		    can->can.restart_ms) अणु
			can->can.can_stats.restarts++;
			cf->can_id |= CAN_ERR_RESTARTED;
		पूर्ण

		shhwtstamps = skb_hwtstamps(skb);
		shhwtstamps->hwtstamp =
			ns_to_kसमय(भाग_u64(p->बारtamp * 1000,
					    can->kv_pcie->freq_to_ticks_भाग));

		cf->data[6] = bec.txerr;
		cf->data[7] = bec.rxerr;

		netअगर_rx(skb);
	पूर्ण
	can->bec.txerr = bec.txerr;
	can->bec.rxerr = bec.rxerr;
	/* Check अगर we need to poll the error counters */
	अगर (bec.txerr || bec.rxerr)
		mod_समयr(&can->bec_poll_समयr, KVASER_PCIEFD_BEC_POLL_FREQ);

	वापस 0;
पूर्ण

अटल पूर्णांक kvaser_pciefd_handle_status_packet(काष्ठा kvaser_pciefd *pcie,
					      काष्ठा kvaser_pciefd_rx_packet *p)
अणु
	काष्ठा kvaser_pciefd_can *can;
	u8 cmdseq;
	u32 status;
	u8 ch_id = (p->header[1] >> KVASER_PCIEFD_PACKET_CHID_SHIFT) & 0x7;

	अगर (ch_id >= pcie->nr_channels)
		वापस -EIO;

	can = pcie->can[ch_id];

	status = ioपढ़ो32(can->reg_base + KVASER_PCIEFD_KCAN_STAT_REG);
	cmdseq = (status >> KVASER_PCIEFD_KCAN_STAT_SEQNO_SHIFT) & 0xff;

	/* Reset करोne, start पात and flush */
	अगर (p->header[0] & KVASER_PCIEFD_SPACK_IRM &&
	    p->header[0] & KVASER_PCIEFD_SPACK_RMCD &&
	    p->header[1] & KVASER_PCIEFD_SPACK_AUTO &&
	    cmdseq == (p->header[1] & KVASER_PCIEFD_PACKET_SEQ_MSK) &&
	    status & KVASER_PCIEFD_KCAN_STAT_IDLE) अणु
		u32 cmd;

		ioग_लिखो32(KVASER_PCIEFD_KCAN_IRQ_ABD,
			  can->reg_base + KVASER_PCIEFD_KCAN_IRQ_REG);
		cmd = KVASER_PCIEFD_KCAN_CMD_AT;
		cmd |= ++can->cmd_seq << KVASER_PCIEFD_KCAN_CMD_SEQ_SHIFT;
		ioग_लिखो32(cmd, can->reg_base + KVASER_PCIEFD_KCAN_CMD_REG);

		ioग_लिखो32(KVASER_PCIEFD_KCAN_IRQ_TFD,
			  can->reg_base + KVASER_PCIEFD_KCAN_IEN_REG);
	पूर्ण अन्यथा अगर (p->header[0] & KVASER_PCIEFD_SPACK_IDET &&
		   p->header[0] & KVASER_PCIEFD_SPACK_IRM &&
		   cmdseq == (p->header[1] & KVASER_PCIEFD_PACKET_SEQ_MSK) &&
		   status & KVASER_PCIEFD_KCAN_STAT_IDLE) अणु
		/* Reset detected, send end of flush अगर no packet are in FIFO */
		u8 count = ioपढ़ो32(can->reg_base +
				    KVASER_PCIEFD_KCAN_TX_NPACKETS_REG) & 0xff;

		अगर (!count)
			ioग_लिखो32(KVASER_PCIEFD_KCAN_CTRL_EFLUSH,
				  can->reg_base + KVASER_PCIEFD_KCAN_CTRL_REG);
	पूर्ण अन्यथा अगर (!(p->header[1] & KVASER_PCIEFD_SPACK_AUTO) &&
		   cmdseq == (p->header[1] & KVASER_PCIEFD_PACKET_SEQ_MSK)) अणु
		/* Response to status request received */
		kvaser_pciefd_handle_status_resp(can, p);
		अगर (can->can.state != CAN_STATE_BUS_OFF &&
		    can->can.state != CAN_STATE_ERROR_ACTIVE) अणु
			mod_समयr(&can->bec_poll_समयr,
				  KVASER_PCIEFD_BEC_POLL_FREQ);
		पूर्ण
	पूर्ण अन्यथा अगर (p->header[0] & KVASER_PCIEFD_SPACK_RMCD &&
		   !(status & KVASER_PCIEFD_KCAN_STAT_BUS_OFF_MSK)) अणु
		/* Reset to bus on detected */
		अगर (!completion_करोne(&can->start_comp))
			complete(&can->start_comp);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kvaser_pciefd_handle_eack_packet(काष्ठा kvaser_pciefd *pcie,
					    काष्ठा kvaser_pciefd_rx_packet *p)
अणु
	काष्ठा kvaser_pciefd_can *can;
	u8 ch_id = (p->header[1] >> KVASER_PCIEFD_PACKET_CHID_SHIFT) & 0x7;

	अगर (ch_id >= pcie->nr_channels)
		वापस -EIO;

	can = pcie->can[ch_id];

	/* If this is the last flushed packet, send end of flush */
	अगर (p->header[0] & KVASER_PCIEFD_APACKET_FLU) अणु
		u8 count = ioपढ़ो32(can->reg_base +
				    KVASER_PCIEFD_KCAN_TX_NPACKETS_REG) & 0xff;

		अगर (count == 0)
			ioग_लिखो32(KVASER_PCIEFD_KCAN_CTRL_EFLUSH,
				  can->reg_base + KVASER_PCIEFD_KCAN_CTRL_REG);
	पूर्ण अन्यथा अणु
		पूर्णांक echo_idx = p->header[0] & KVASER_PCIEFD_PACKET_SEQ_MSK;
		पूर्णांक dlc = can_get_echo_skb(can->can.dev, echo_idx, शून्य);
		काष्ठा net_device_stats *stats = &can->can.dev->stats;

		stats->tx_bytes += dlc;
		stats->tx_packets++;

		अगर (netअगर_queue_stopped(can->can.dev))
			netअगर_wake_queue(can->can.dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम kvaser_pciefd_handle_nack_packet(काष्ठा kvaser_pciefd_can *can,
					     काष्ठा kvaser_pciefd_rx_packet *p)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा net_device_stats *stats = &can->can.dev->stats;
	काष्ठा can_frame *cf;

	skb = alloc_can_err_skb(can->can.dev, &cf);

	stats->tx_errors++;
	अगर (p->header[0] & KVASER_PCIEFD_APACKET_ABL) अणु
		अगर (skb)
			cf->can_id |= CAN_ERR_LOSTARB;
		can->can.can_stats.arbitration_lost++;
	पूर्ण अन्यथा अगर (skb) अणु
		cf->can_id |= CAN_ERR_ACK;
	पूर्ण

	अगर (skb) अणु
		cf->can_id |= CAN_ERR_BUSERROR;
		stats->rx_bytes += cf->len;
		stats->rx_packets++;
		netअगर_rx(skb);
	पूर्ण अन्यथा अणु
		stats->rx_dropped++;
		netdev_warn(can->can.dev, "No memory left for err_skb\n");
	पूर्ण
पूर्ण

अटल पूर्णांक kvaser_pciefd_handle_ack_packet(काष्ठा kvaser_pciefd *pcie,
					   काष्ठा kvaser_pciefd_rx_packet *p)
अणु
	काष्ठा kvaser_pciefd_can *can;
	bool one_shot_fail = false;
	u8 ch_id = (p->header[1] >> KVASER_PCIEFD_PACKET_CHID_SHIFT) & 0x7;

	अगर (ch_id >= pcie->nr_channels)
		वापस -EIO;

	can = pcie->can[ch_id];
	/* Ignore control packet ACK */
	अगर (p->header[0] & KVASER_PCIEFD_APACKET_CT)
		वापस 0;

	अगर (p->header[0] & KVASER_PCIEFD_APACKET_NACK) अणु
		kvaser_pciefd_handle_nack_packet(can, p);
		one_shot_fail = true;
	पूर्ण

	अगर (p->header[0] & KVASER_PCIEFD_APACKET_FLU) अणु
		netdev_dbg(can->can.dev, "Packet was flushed\n");
	पूर्ण अन्यथा अणु
		पूर्णांक echo_idx = p->header[0] & KVASER_PCIEFD_PACKET_SEQ_MSK;
		पूर्णांक dlc = can_get_echo_skb(can->can.dev, echo_idx, शून्य);
		u8 count = ioपढ़ो32(can->reg_base +
				    KVASER_PCIEFD_KCAN_TX_NPACKETS_REG) & 0xff;

		अगर (count < KVASER_PCIEFD_CAN_TX_MAX_COUNT &&
		    netअगर_queue_stopped(can->can.dev))
			netअगर_wake_queue(can->can.dev);

		अगर (!one_shot_fail) अणु
			काष्ठा net_device_stats *stats = &can->can.dev->stats;

			stats->tx_bytes += dlc;
			stats->tx_packets++;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kvaser_pciefd_handle_eflush_packet(काष्ठा kvaser_pciefd *pcie,
					      काष्ठा kvaser_pciefd_rx_packet *p)
अणु
	काष्ठा kvaser_pciefd_can *can;
	u8 ch_id = (p->header[1] >> KVASER_PCIEFD_PACKET_CHID_SHIFT) & 0x7;

	अगर (ch_id >= pcie->nr_channels)
		वापस -EIO;

	can = pcie->can[ch_id];

	अगर (!completion_करोne(&can->flush_comp))
		complete(&can->flush_comp);

	वापस 0;
पूर्ण

अटल पूर्णांक kvaser_pciefd_पढ़ो_packet(काष्ठा kvaser_pciefd *pcie, पूर्णांक *start_pos,
				     पूर्णांक dma_buf)
अणु
	__le32 *buffer = pcie->dma_data[dma_buf];
	__le64 बारtamp;
	काष्ठा kvaser_pciefd_rx_packet packet;
	काष्ठा kvaser_pciefd_rx_packet *p = &packet;
	u8 type;
	पूर्णांक pos = *start_pos;
	पूर्णांक size;
	पूर्णांक ret = 0;

	size = le32_to_cpu(buffer[pos++]);
	अगर (!size) अणु
		*start_pos = 0;
		वापस 0;
	पूर्ण

	p->header[0] = le32_to_cpu(buffer[pos++]);
	p->header[1] = le32_to_cpu(buffer[pos++]);

	/* Read 64-bit बारtamp */
	स_नकल(&बारtamp, &buffer[pos], माप(__le64));
	pos += 2;
	p->बारtamp = le64_to_cpu(बारtamp);

	type = (p->header[1] >> KVASER_PCIEFD_PACKET_TYPE_SHIFT) & 0xf;
	चयन (type) अणु
	हाल KVASER_PCIEFD_PACK_TYPE_DATA:
		ret = kvaser_pciefd_handle_data_packet(pcie, p, &buffer[pos]);
		अगर (!(p->header[0] & KVASER_PCIEFD_RPACKET_RTR)) अणु
			u8 data_len;

			data_len = can_fd_dlc2len(p->header[1] >>
					       KVASER_PCIEFD_RPACKET_DLC_SHIFT);
			pos += DIV_ROUND_UP(data_len, 4);
		पूर्ण
		अवरोध;

	हाल KVASER_PCIEFD_PACK_TYPE_ACK:
		ret = kvaser_pciefd_handle_ack_packet(pcie, p);
		अवरोध;

	हाल KVASER_PCIEFD_PACK_TYPE_STATUS:
		ret = kvaser_pciefd_handle_status_packet(pcie, p);
		अवरोध;

	हाल KVASER_PCIEFD_PACK_TYPE_ERROR:
		ret = kvaser_pciefd_handle_error_packet(pcie, p);
		अवरोध;

	हाल KVASER_PCIEFD_PACK_TYPE_EFRAME_ACK:
		ret = kvaser_pciefd_handle_eack_packet(pcie, p);
		अवरोध;

	हाल KVASER_PCIEFD_PACK_TYPE_EFLUSH_ACK:
		ret = kvaser_pciefd_handle_eflush_packet(pcie, p);
		अवरोध;

	हाल KVASER_PCIEFD_PACK_TYPE_ACK_DATA:
	हाल KVASER_PCIEFD_PACK_TYPE_BUS_LOAD:
	हाल KVASER_PCIEFD_PACK_TYPE_TXRQ:
		dev_info(&pcie->pci->dev,
			 "Received unexpected packet type 0x%08X\n", type);
		अवरोध;

	शेष:
		dev_err(&pcie->pci->dev, "Unknown packet type 0x%08X\n", type);
		ret = -EIO;
		अवरोध;
	पूर्ण

	अगर (ret)
		वापस ret;

	/* Position करोes not poपूर्णांक to the end of the package,
	 * corrupted packet size?
	 */
	अगर ((*start_pos + size) != pos)
		वापस -EIO;

	/* Poपूर्णांक to the next packet header, अगर any */
	*start_pos = pos;

	वापस ret;
पूर्ण

अटल पूर्णांक kvaser_pciefd_पढ़ो_buffer(काष्ठा kvaser_pciefd *pcie, पूर्णांक dma_buf)
अणु
	पूर्णांक pos = 0;
	पूर्णांक res = 0;

	करो अणु
		res = kvaser_pciefd_पढ़ो_packet(pcie, &pos, dma_buf);
	पूर्ण जबतक (!res && pos > 0 && pos < KVASER_PCIEFD_DMA_SIZE);

	वापस res;
पूर्ण

अटल पूर्णांक kvaser_pciefd_receive_irq(काष्ठा kvaser_pciefd *pcie)
अणु
	u32 irq;

	irq = ioपढ़ो32(pcie->reg_base + KVASER_PCIEFD_SRB_IRQ_REG);
	अगर (irq & KVASER_PCIEFD_SRB_IRQ_DPD0) अणु
		kvaser_pciefd_पढ़ो_buffer(pcie, 0);
		/* Reset DMA buffer 0 */
		ioग_लिखो32(KVASER_PCIEFD_SRB_CMD_RDB0,
			  pcie->reg_base + KVASER_PCIEFD_SRB_CMD_REG);
	पूर्ण

	अगर (irq & KVASER_PCIEFD_SRB_IRQ_DPD1) अणु
		kvaser_pciefd_पढ़ो_buffer(pcie, 1);
		/* Reset DMA buffer 1 */
		ioग_लिखो32(KVASER_PCIEFD_SRB_CMD_RDB1,
			  pcie->reg_base + KVASER_PCIEFD_SRB_CMD_REG);
	पूर्ण

	अगर (irq & KVASER_PCIEFD_SRB_IRQ_DOF0 ||
	    irq & KVASER_PCIEFD_SRB_IRQ_DOF1 ||
	    irq & KVASER_PCIEFD_SRB_IRQ_DUF0 ||
	    irq & KVASER_PCIEFD_SRB_IRQ_DUF1)
		dev_err(&pcie->pci->dev, "DMA IRQ error 0x%08X\n", irq);

	ioग_लिखो32(irq, pcie->reg_base + KVASER_PCIEFD_SRB_IRQ_REG);
	वापस 0;
पूर्ण

अटल पूर्णांक kvaser_pciefd_transmit_irq(काष्ठा kvaser_pciefd_can *can)
अणु
	u32 irq = ioपढ़ो32(can->reg_base + KVASER_PCIEFD_KCAN_IRQ_REG);

	अगर (irq & KVASER_PCIEFD_KCAN_IRQ_TOF)
		netdev_err(can->can.dev, "Tx FIFO overflow\n");

	अगर (irq & KVASER_PCIEFD_KCAN_IRQ_TFD) अणु
		u8 count = ioपढ़ो32(can->reg_base +
				    KVASER_PCIEFD_KCAN_TX_NPACKETS_REG) & 0xff;

		अगर (count == 0)
			ioग_लिखो32(KVASER_PCIEFD_KCAN_CTRL_EFLUSH,
				  can->reg_base + KVASER_PCIEFD_KCAN_CTRL_REG);
	पूर्ण

	अगर (irq & KVASER_PCIEFD_KCAN_IRQ_BPP)
		netdev_err(can->can.dev,
			   "Fail to change bittiming, when not in reset mode\n");

	अगर (irq & KVASER_PCIEFD_KCAN_IRQ_FDIC)
		netdev_err(can->can.dev, "CAN FD frame in CAN mode\n");

	अगर (irq & KVASER_PCIEFD_KCAN_IRQ_ROF)
		netdev_err(can->can.dev, "Rx FIFO overflow\n");

	ioग_लिखो32(irq, can->reg_base + KVASER_PCIEFD_KCAN_IRQ_REG);
	वापस 0;
पूर्ण

अटल irqवापस_t kvaser_pciefd_irq_handler(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा kvaser_pciefd *pcie = (काष्ठा kvaser_pciefd *)dev;
	u32 board_irq;
	पूर्णांक i;

	board_irq = ioपढ़ो32(pcie->reg_base + KVASER_PCIEFD_IRQ_REG);

	अगर (!(board_irq & KVASER_PCIEFD_IRQ_ALL_MSK))
		वापस IRQ_NONE;

	अगर (board_irq & KVASER_PCIEFD_IRQ_SRB)
		kvaser_pciefd_receive_irq(pcie);

	क्रम (i = 0; i < pcie->nr_channels; i++) अणु
		अगर (!pcie->can[i]) अणु
			dev_err(&pcie->pci->dev,
				"IRQ mask points to unallocated controller\n");
			अवरोध;
		पूर्ण

		/* Check that mask matches channel (i) IRQ mask */
		अगर (board_irq & (1 << i))
			kvaser_pciefd_transmit_irq(pcie->can[i]);
	पूर्ण

	ioग_लिखो32(board_irq, pcie->reg_base + KVASER_PCIEFD_IRQ_REG);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम kvaser_pciefd_tearकरोwn_can_ctrls(काष्ठा kvaser_pciefd *pcie)
अणु
	पूर्णांक i;
	काष्ठा kvaser_pciefd_can *can;

	क्रम (i = 0; i < pcie->nr_channels; i++) अणु
		can = pcie->can[i];
		अगर (can) अणु
			ioग_लिखो32(0,
				  can->reg_base + KVASER_PCIEFD_KCAN_IEN_REG);
			kvaser_pciefd_pwm_stop(can);
			मुक्त_candev(can->can.dev);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक kvaser_pciefd_probe(काष्ठा pci_dev *pdev,
			       स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक err;
	काष्ठा kvaser_pciefd *pcie;

	pcie = devm_kzalloc(&pdev->dev, माप(*pcie), GFP_KERNEL);
	अगर (!pcie)
		वापस -ENOMEM;

	pci_set_drvdata(pdev, pcie);
	pcie->pci = pdev;

	err = pci_enable_device(pdev);
	अगर (err)
		वापस err;

	err = pci_request_regions(pdev, KVASER_PCIEFD_DRV_NAME);
	अगर (err)
		जाओ err_disable_pci;

	pcie->reg_base = pci_iomap(pdev, 0, 0);
	अगर (!pcie->reg_base) अणु
		err = -ENOMEM;
		जाओ err_release_regions;
	पूर्ण

	err = kvaser_pciefd_setup_board(pcie);
	अगर (err)
		जाओ err_pci_iounmap;

	err = kvaser_pciefd_setup_dma(pcie);
	अगर (err)
		जाओ err_pci_iounmap;

	pci_set_master(pdev);

	err = kvaser_pciefd_setup_can_ctrls(pcie);
	अगर (err)
		जाओ err_tearकरोwn_can_ctrls;

	ioग_लिखो32(KVASER_PCIEFD_SRB_IRQ_DPD0 | KVASER_PCIEFD_SRB_IRQ_DPD1,
		  pcie->reg_base + KVASER_PCIEFD_SRB_IRQ_REG);

	ioग_लिखो32(KVASER_PCIEFD_SRB_IRQ_DPD0 | KVASER_PCIEFD_SRB_IRQ_DPD1 |
		  KVASER_PCIEFD_SRB_IRQ_DOF0 | KVASER_PCIEFD_SRB_IRQ_DOF1 |
		  KVASER_PCIEFD_SRB_IRQ_DUF0 | KVASER_PCIEFD_SRB_IRQ_DUF1,
		  pcie->reg_base + KVASER_PCIEFD_SRB_IEN_REG);

	/* Reset IRQ handling, expected to be off beक्रमe */
	ioग_लिखो32(KVASER_PCIEFD_IRQ_ALL_MSK,
		  pcie->reg_base + KVASER_PCIEFD_IRQ_REG);
	ioग_लिखो32(KVASER_PCIEFD_IRQ_ALL_MSK,
		  pcie->reg_base + KVASER_PCIEFD_IEN_REG);

	/* Ready the DMA buffers */
	ioग_लिखो32(KVASER_PCIEFD_SRB_CMD_RDB0,
		  pcie->reg_base + KVASER_PCIEFD_SRB_CMD_REG);
	ioग_लिखो32(KVASER_PCIEFD_SRB_CMD_RDB1,
		  pcie->reg_base + KVASER_PCIEFD_SRB_CMD_REG);

	err = request_irq(pcie->pci->irq, kvaser_pciefd_irq_handler,
			  IRQF_SHARED, KVASER_PCIEFD_DRV_NAME, pcie);
	अगर (err)
		जाओ err_tearकरोwn_can_ctrls;

	err = kvaser_pciefd_reg_candev(pcie);
	अगर (err)
		जाओ err_मुक्त_irq;

	वापस 0;

err_मुक्त_irq:
	मुक्त_irq(pcie->pci->irq, pcie);

err_tearकरोwn_can_ctrls:
	kvaser_pciefd_tearकरोwn_can_ctrls(pcie);
	ioग_लिखो32(0, pcie->reg_base + KVASER_PCIEFD_SRB_CTRL_REG);
	pci_clear_master(pdev);

err_pci_iounmap:
	pci_iounmap(pdev, pcie->reg_base);

err_release_regions:
	pci_release_regions(pdev);

err_disable_pci:
	pci_disable_device(pdev);

	वापस err;
पूर्ण

अटल व्योम kvaser_pciefd_हटाओ_all_ctrls(काष्ठा kvaser_pciefd *pcie)
अणु
	काष्ठा kvaser_pciefd_can *can;
	पूर्णांक i;

	क्रम (i = 0; i < pcie->nr_channels; i++) अणु
		can = pcie->can[i];
		अगर (can) अणु
			ioग_लिखो32(0,
				  can->reg_base + KVASER_PCIEFD_KCAN_IEN_REG);
			unरेजिस्टर_candev(can->can.dev);
			del_समयr(&can->bec_poll_समयr);
			kvaser_pciefd_pwm_stop(can);
			मुक्त_candev(can->can.dev);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम kvaser_pciefd_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा kvaser_pciefd *pcie = pci_get_drvdata(pdev);

	kvaser_pciefd_हटाओ_all_ctrls(pcie);

	/* Turn off IRQ generation */
	ioग_लिखो32(0, pcie->reg_base + KVASER_PCIEFD_SRB_CTRL_REG);
	ioग_लिखो32(KVASER_PCIEFD_IRQ_ALL_MSK,
		  pcie->reg_base + KVASER_PCIEFD_IRQ_REG);
	ioग_लिखो32(0, pcie->reg_base + KVASER_PCIEFD_IEN_REG);

	मुक्त_irq(pcie->pci->irq, pcie);

	pci_clear_master(pdev);
	pci_iounmap(pdev, pcie->reg_base);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल काष्ठा pci_driver kvaser_pciefd = अणु
	.name = KVASER_PCIEFD_DRV_NAME,
	.id_table = kvaser_pciefd_id_table,
	.probe = kvaser_pciefd_probe,
	.हटाओ = kvaser_pciefd_हटाओ,
पूर्ण;

module_pci_driver(kvaser_pciefd)
