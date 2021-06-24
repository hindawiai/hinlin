<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2012 - 2018 Microchip Technology Inc., and its subsidiaries.
 * All rights reserved.
 */

#अगर_अघोषित WILC_WLAN_H
#घोषणा WILC_WLAN_H

#समावेश <linux/types.h>
#समावेश <linux/bitfield.h>

/********************************************
 *
 *      Mac eth header length
 *
 ********************************************/
#घोषणा MAX_MAC_HDR_LEN			26 /* QOS_MAC_HDR_LEN */
#घोषणा SUB_MSDU_HEADER_LENGTH		14
#घोषणा SNAP_HDR_LEN			8
#घोषणा ETHERNET_HDR_LEN		14
#घोषणा WORD_ALIGNMENT_PAD		0

#घोषणा ETH_ETHERNET_HDR_OFFSET		(MAX_MAC_HDR_LEN + \
					 SUB_MSDU_HEADER_LENGTH + \
					 SNAP_HDR_LEN - \
					 ETHERNET_HDR_LEN + \
					 WORD_ALIGNMENT_PAD)

#घोषणा HOST_HDR_OFFSET			4
#घोषणा ETHERNET_HDR_LEN		14
#घोषणा IP_HDR_LEN			20
#घोषणा IP_HDR_OFFSET			ETHERNET_HDR_LEN
#घोषणा UDP_HDR_OFFSET			(IP_HDR_LEN + IP_HDR_OFFSET)
#घोषणा UDP_HDR_LEN			8
#घोषणा UDP_DATA_OFFSET			(UDP_HDR_OFFSET + UDP_HDR_LEN)
#घोषणा ETH_CONFIG_PKT_HDR_LEN		UDP_DATA_OFFSET

#घोषणा ETH_CONFIG_PKT_HDR_OFFSET	(ETH_ETHERNET_HDR_OFFSET + \
					 ETH_CONFIG_PKT_HDR_LEN)

/********************************************
 *
 *      Register Defines
 *
 ********************************************/
#घोषणा WILC_PERIPH_REG_BASE		0x1000
#घोषणा WILC_CHANGING_VIR_IF		0x108c
#घोषणा WILC_CHIPID			WILC_PERIPH_REG_BASE
#घोषणा WILC_GLB_RESET_0		(WILC_PERIPH_REG_BASE + 0x400)
#घोषणा WILC_PIN_MUX_0			(WILC_PERIPH_REG_BASE + 0x408)
#घोषणा WILC_HOST_TX_CTRL		(WILC_PERIPH_REG_BASE + 0x6c)
#घोषणा WILC_HOST_RX_CTRL_0		(WILC_PERIPH_REG_BASE + 0x70)
#घोषणा WILC_HOST_RX_CTRL_1		(WILC_PERIPH_REG_BASE + 0x74)
#घोषणा WILC_HOST_VMM_CTL		(WILC_PERIPH_REG_BASE + 0x78)
#घोषणा WILC_HOST_RX_CTRL		(WILC_PERIPH_REG_BASE + 0x80)
#घोषणा WILC_HOST_RX_EXTRA_SIZE		(WILC_PERIPH_REG_BASE + 0x84)
#घोषणा WILC_HOST_TX_CTRL_1		(WILC_PERIPH_REG_BASE + 0x88)
#घोषणा WILC_MISC			(WILC_PERIPH_REG_BASE + 0x428)
#घोषणा WILC_INTR_REG_BASE		(WILC_PERIPH_REG_BASE + 0xa00)
#घोषणा WILC_INTR_ENABLE		WILC_INTR_REG_BASE
#घोषणा WILC_INTR2_ENABLE		(WILC_INTR_REG_BASE + 4)

#घोषणा WILC_INTR_POLARITY		(WILC_INTR_REG_BASE + 0x10)
#घोषणा WILC_INTR_TYPE			(WILC_INTR_REG_BASE + 0x20)
#घोषणा WILC_INTR_CLEAR			(WILC_INTR_REG_BASE + 0x30)
#घोषणा WILC_INTR_STATUS		(WILC_INTR_REG_BASE + 0x40)

#घोषणा WILC_RF_REVISION_ID		0x13f4

#घोषणा WILC_VMM_TBL_SIZE		64
#घोषणा WILC_VMM_TX_TBL_BASE		0x150400
#घोषणा WILC_VMM_RX_TBL_BASE		0x150500

#घोषणा WILC_VMM_BASE			0x150000
#घोषणा WILC_VMM_CORE_CTL		WILC_VMM_BASE
#घोषणा WILC_VMM_TBL_CTL		(WILC_VMM_BASE + 0x4)
#घोषणा WILC_VMM_TBL_ENTRY		(WILC_VMM_BASE + 0x8)
#घोषणा WILC_VMM_TBL0_SIZE		(WILC_VMM_BASE + 0xc)
#घोषणा WILC_VMM_TO_HOST_SIZE		(WILC_VMM_BASE + 0x10)
#घोषणा WILC_VMM_CORE_CFG		(WILC_VMM_BASE + 0x14)
#घोषणा WILC_VMM_TBL_ACTIVE		(WILC_VMM_BASE + 040)
#घोषणा WILC_VMM_TBL_STATUS		(WILC_VMM_BASE + 0x44)

#घोषणा WILC_SPI_REG_BASE		0xe800
#घोषणा WILC_SPI_CTL			WILC_SPI_REG_BASE
#घोषणा WILC_SPI_MASTER_DMA_ADDR	(WILC_SPI_REG_BASE + 0x4)
#घोषणा WILC_SPI_MASTER_DMA_COUNT	(WILC_SPI_REG_BASE + 0x8)
#घोषणा WILC_SPI_SLAVE_DMA_ADDR		(WILC_SPI_REG_BASE + 0xc)
#घोषणा WILC_SPI_SLAVE_DMA_COUNT	(WILC_SPI_REG_BASE + 0x10)
#घोषणा WILC_SPI_TX_MODE		(WILC_SPI_REG_BASE + 0x20)
#घोषणा WILC_SPI_PROTOCOL_CONFIG	(WILC_SPI_REG_BASE + 0x24)
#घोषणा WILC_SPI_INTR_CTL		(WILC_SPI_REG_BASE + 0x2c)
#घोषणा WILC_SPI_INT_STATUS		(WILC_SPI_REG_BASE + 0x40)
#घोषणा WILC_SPI_INT_CLEAR		(WILC_SPI_REG_BASE + 0x44)

#घोषणा WILC_SPI_WAKEUP_REG		0x1
#घोषणा WILC_SPI_WAKEUP_BIT		BIT(1)

#घोषणा WILC_SPI_HOST_TO_FW_REG		0x0b
#घोषणा WILC_SPI_HOST_TO_FW_BIT		BIT(0)

#घोषणा WILC_SPI_FW_TO_HOST_REG		0x10
#घोषणा WILC_SPI_FW_TO_HOST_BIT		BIT(0)

#घोषणा WILC_SPI_PROTOCOL_OFFSET	(WILC_SPI_PROTOCOL_CONFIG - \
					 WILC_SPI_REG_BASE)

#घोषणा WILC_SPI_CLOCKLESS_ADDR_LIMIT	0x30

/* Functions IO enables bits */
#घोषणा WILC_SDIO_CCCR_IO_EN_FUNC1	BIT(1)

/* Function/Interrupt enables bits */
#घोषणा WILC_SDIO_CCCR_IEN_MASTER	BIT(0)
#घोषणा WILC_SDIO_CCCR_IEN_FUNC1	BIT(1)

/* Abort CCCR रेजिस्टर bits */
#घोषणा WILC_SDIO_CCCR_ABORT_RESET	BIT(3)

/* Venकरोr specअगरic CCCR रेजिस्टरs */
#घोषणा WILC_SDIO_WAKEUP_REG		0xf0
#घोषणा WILC_SDIO_WAKEUP_BIT		BIT(0)

#घोषणा WILC_SDIO_CLK_STATUS_REG	0xf1
#घोषणा WILC_SDIO_CLK_STATUS_BIT	BIT(0)

#घोषणा WILC_SDIO_INTERRUPT_DATA_SZ_REG	0xf2 /* Read size (2 bytes) */

#घोषणा WILC_SDIO_VMM_TBL_CTRL_REG	0xf6
#घोषणा WILC_SDIO_IRQ_FLAG_REG		0xf7
#घोषणा WILC_SDIO_IRQ_CLEAR_FLAG_REG	0xf8

#घोषणा WILC_SDIO_HOST_TO_FW_REG	0xfa
#घोषणा WILC_SDIO_HOST_TO_FW_BIT	BIT(0)

#घोषणा WILC_SDIO_FW_TO_HOST_REG	0xfc
#घोषणा WILC_SDIO_FW_TO_HOST_BIT	BIT(0)

/* Function 1 specअगरic FBR रेजिस्टर */
#घोषणा WILC_SDIO_FBR_CSA_REG		0x10C /* CSA poपूर्णांकer (3 bytes) */
#घोषणा WILC_SDIO_FBR_DATA_REG		0x10F

#घोषणा WILC_SDIO_F1_DATA_REG		0x0
#घोषणा WILC_SDIO_EXT_IRQ_FLAG_REG	0x4

#घोषणा WILC_AHB_DATA_MEM_BASE		0x30000
#घोषणा WILC_AHB_SHARE_MEM_BASE		0xd0000

#घोषणा WILC_VMM_TBL_RX_SHADOW_BASE	WILC_AHB_SHARE_MEM_BASE
#घोषणा WILC_VMM_TBL_RX_SHADOW_SIZE	256

#घोषणा WILC_FW_HOST_COMM		0x13c0
#घोषणा WILC_GP_REG_0			0x149c
#घोषणा WILC_GP_REG_1			0x14a0

#घोषणा WILC_HAVE_SDIO_IRQ_GPIO		BIT(0)
#घोषणा WILC_HAVE_USE_PMU		BIT(1)
#घोषणा WILC_HAVE_SLEEP_CLK_SRC_RTC	BIT(2)
#घोषणा WILC_HAVE_SLEEP_CLK_SRC_XO	BIT(3)
#घोषणा WILC_HAVE_EXT_PA_INV_TX_RX	BIT(4)
#घोषणा WILC_HAVE_LEGACY_RF_SETTINGS	BIT(5)
#घोषणा WILC_HAVE_XTAL_24		BIT(6)
#घोषणा WILC_HAVE_DISABLE_WILC_UART	BIT(7)
#घोषणा WILC_HAVE_USE_IRQ_AS_HOST_WAKE	BIT(8)

#घोषणा WILC_CORTUS_INTERRUPT_BASE	0x10A8
#घोषणा WILC_CORTUS_INTERRUPT_1		(WILC_CORTUS_INTERRUPT_BASE + 0x4)
#घोषणा WILC_CORTUS_INTERRUPT_2		(WILC_CORTUS_INTERRUPT_BASE + 0x8)

/* tx control रेजिस्टर 1 to 4 क्रम RX */
#घोषणा WILC_REG_4_TO_1_RX		0x1e1c

/* tx control रेजिस्टर 1 to 4 क्रम TX Bank_0 */
#घोषणा WILC_REG_4_TO_1_TX_BANK0	0x1e9c

#घोषणा WILC_CORTUS_RESET_MUX_SEL	0x1118
#घोषणा WILC_CORTUS_BOOT_REGISTER	0xc0000

#घोषणा WILC_CORTUS_BOOT_FROM_IRAM	0x71

#घोषणा WILC_1000_BASE_ID		0x100000

#घोषणा WILC_1000_BASE_ID_2A		0x1002A0
#घोषणा WILC_1000_BASE_ID_2A_REV1	(WILC_1000_BASE_ID_2A + 1)

#घोषणा WILC_1000_BASE_ID_2B		0x1002B0
#घोषणा WILC_1000_BASE_ID_2B_REV1	(WILC_1000_BASE_ID_2B + 1)
#घोषणा WILC_1000_BASE_ID_2B_REV2	(WILC_1000_BASE_ID_2B + 2)

#घोषणा WILC_CHIP_REV_FIELD		GENMASK(11, 0)

/********************************************
 *
 *      Wlan Defines
 *
 ********************************************/
#घोषणा WILC_CFG_PKT		1
#घोषणा WILC_NET_PKT		0
#घोषणा WILC_MGMT_PKT		2

#घोषणा WILC_CFG_SET		1
#घोषणा WILC_CFG_QUERY		0

#घोषणा WILC_CFG_RSP		1
#घोषणा WILC_CFG_RSP_STATUS	2
#घोषणा WILC_CFG_RSP_SCAN	3

#घोषणा WILC_ABORT_REQ_BIT		BIT(31)

#घोषणा WILC_RX_BUFF_SIZE	(96 * 1024)
#घोषणा WILC_TX_BUFF_SIZE	(64 * 1024)

#घोषणा MODALIAS		"WILC_SPI"

#घोषणा NQUEUES			4
#घोषणा AC_BUFFER_SIZE		1000

#घोषणा VO_AC_COUNT_FIELD		GENMASK(31, 25)
#घोषणा VO_AC_ACM_STAT_FIELD		BIT(24)
#घोषणा VI_AC_COUNT_FIELD		GENMASK(23, 17)
#घोषणा VI_AC_ACM_STAT_FIELD		BIT(16)
#घोषणा BE_AC_COUNT_FIELD		GENMASK(15, 9)
#घोषणा BE_AC_ACM_STAT_FIELD		BIT(8)
#घोषणा BK_AC_COUNT_FIELD		GENMASK(7, 3)
#घोषणा BK_AC_ACM_STAT_FIELD		BIT(1)

#घोषणा WILC_PKT_HDR_CONFIG_FIELD	BIT(31)
#घोषणा WILC_PKT_HDR_OFFSET_FIELD	GENMASK(30, 22)
#घोषणा WILC_PKT_HDR_TOTAL_LEN_FIELD	GENMASK(21, 11)
#घोषणा WILC_PKT_HDR_LEN_FIELD		GENMASK(10, 0)

#घोषणा WILC_INTERRUPT_DATA_SIZE	GENMASK(14, 0)

#घोषणा WILC_VMM_BUFFER_SIZE		GENMASK(9, 0)

#घोषणा WILC_VMM_HDR_TYPE		BIT(31)
#घोषणा WILC_VMM_HDR_MGMT_FIELD		BIT(30)
#घोषणा WILC_VMM_HDR_PKT_SIZE		GENMASK(29, 15)
#घोषणा WILC_VMM_HDR_BUFF_SIZE		GENMASK(14, 0)

#घोषणा WILC_VMM_ENTRY_COUNT		GENMASK(8, 3)
#घोषणा WILC_VMM_ENTRY_AVAILABLE	BIT(2)
/*******************************************/
/*        E0 and later Interrupt flags.    */
/*******************************************/
/*******************************************/
/*        E0 and later Interrupt flags.    */
/*           IRQ Status word               */
/* 15:0 = DMA count in words.              */
/* 16: INT0 flag                           */
/* 17: INT1 flag                           */
/* 18: INT2 flag                           */
/* 19: INT3 flag                           */
/* 20: INT4 flag                           */
/* 21: INT5 flag                           */
/*******************************************/
#घोषणा IRG_FLAGS_OFFSET	16
#घोषणा IRQ_DMA_WD_CNT_MASK	GENMASK(IRG_FLAGS_OFFSET - 1, 0)
#घोषणा INT_0			BIT(IRG_FLAGS_OFFSET)
#घोषणा INT_1			BIT(IRG_FLAGS_OFFSET + 1)
#घोषणा INT_2			BIT(IRG_FLAGS_OFFSET + 2)
#घोषणा INT_3			BIT(IRG_FLAGS_OFFSET + 3)
#घोषणा INT_4			BIT(IRG_FLAGS_OFFSET + 4)
#घोषणा INT_5			BIT(IRG_FLAGS_OFFSET + 5)
#घोषणा MAX_NUM_INT		5
#घोषणा IRG_FLAGS_MASK		GENMASK(IRG_FLAGS_OFFSET + MAX_NUM_INT, \
					IRG_FLAGS_OFFSET)

/*******************************************/
/*        E0 and later Interrupt flags.    */
/*           IRQ Clear word                */
/* 0: Clear INT0                           */
/* 1: Clear INT1                           */
/* 2: Clear INT2                           */
/* 3: Clear INT3                           */
/* 4: Clear INT4                           */
/* 5: Clear INT5                           */
/* 6: Select VMM table 1                   */
/* 7: Select VMM table 2                   */
/* 8: Enable VMM                           */
/*******************************************/
#घोषणा CLR_INT0		BIT(0)
#घोषणा CLR_INT1		BIT(1)
#घोषणा CLR_INT2		BIT(2)
#घोषणा CLR_INT3		BIT(3)
#घोषणा CLR_INT4		BIT(4)
#घोषणा CLR_INT5		BIT(5)
#घोषणा SEL_VMM_TBL0		BIT(6)
#घोषणा SEL_VMM_TBL1		BIT(7)
#घोषणा EN_VMM			BIT(8)

#घोषणा DATA_INT_EXT		INT_0
#घोषणा ALL_INT_EXT		DATA_INT_EXT
#घोषणा NUM_INT_EXT		1
#घोषणा UNHANDLED_IRQ_MASK	GENMASK(MAX_NUM_INT - 1, NUM_INT_EXT)

#घोषणा DATA_INT_CLR		CLR_INT0

#घोषणा ENABLE_RX_VMM		(SEL_VMM_TBL1 | EN_VMM)
#घोषणा ENABLE_TX_VMM		(SEL_VMM_TBL0 | EN_VMM)
/* समय क्रम expiring the completion of cfg packets */
#घोषणा WILC_CFG_PKTS_TIMEOUT	msecs_to_jअगरfies(2000)

#घोषणा IS_MANAGMEMENT		0x100
#घोषणा IS_MANAGMEMENT_CALLBACK	0x080
#घोषणा IS_MGMT_STATUS_SUCCES	0x040

#घोषणा WILC_WID_TYPE		GENMASK(15, 12)
#घोषणा WILC_VMM_ENTRY_FULL_RETRY	1
/********************************************
 *
 *      Tx/Rx Queue Structure
 *
 ********************************************/
क्रमागत ip_pkt_priority अणु
	AC_VO_Q = 0,
	AC_VI_Q = 1,
	AC_BE_Q = 2,
	AC_BK_Q = 3
पूर्ण;

काष्ठा txq_entry_t अणु
	काष्ठा list_head list;
	पूर्णांक type;
	u8 q_num;
	पूर्णांक ack_idx;
	u8 *buffer;
	पूर्णांक buffer_size;
	व्योम *priv;
	पूर्णांक status;
	काष्ठा wilc_vअगर *vअगर;
	व्योम (*tx_complete_func)(व्योम *priv, पूर्णांक status);
पूर्ण;

काष्ठा txq_fw_recv_queue_stat अणु
	u8 acm;
	u8 count;
पूर्ण;

काष्ठा txq_handle अणु
	काष्ठा txq_entry_t txq_head;
	u16 count;
	काष्ठा txq_fw_recv_queue_stat fw;
पूर्ण;

काष्ठा rxq_entry_t अणु
	काष्ठा list_head list;
	u8 *buffer;
	पूर्णांक buffer_size;
पूर्ण;

/********************************************
 *
 *      Host IF Structure
 *
 ********************************************/
काष्ठा wilc;
काष्ठा wilc_hअगर_func अणु
	पूर्णांक (*hअगर_init)(काष्ठा wilc *wilc, bool resume);
	पूर्णांक (*hअगर_deinit)(काष्ठा wilc *wilc);
	पूर्णांक (*hअगर_पढ़ो_reg)(काष्ठा wilc *wilc, u32 addr, u32 *data);
	पूर्णांक (*hअगर_ग_लिखो_reg)(काष्ठा wilc *wilc, u32 addr, u32 data);
	पूर्णांक (*hअगर_block_rx)(काष्ठा wilc *wilc, u32 addr, u8 *buf, u32 size);
	पूर्णांक (*hअगर_block_tx)(काष्ठा wilc *wilc, u32 addr, u8 *buf, u32 size);
	पूर्णांक (*hअगर_पढ़ो_पूर्णांक)(काष्ठा wilc *wilc, u32 *पूर्णांक_status);
	पूर्णांक (*hअगर_clear_पूर्णांक_ext)(काष्ठा wilc *wilc, u32 val);
	पूर्णांक (*hअगर_पढ़ो_size)(काष्ठा wilc *wilc, u32 *size);
	पूर्णांक (*hअगर_block_tx_ext)(काष्ठा wilc *wilc, u32 addr, u8 *buf, u32 size);
	पूर्णांक (*hअगर_block_rx_ext)(काष्ठा wilc *wilc, u32 addr, u8 *buf, u32 size);
	पूर्णांक (*hअगर_sync_ext)(काष्ठा wilc *wilc, पूर्णांक nपूर्णांक);
	पूर्णांक (*enable_पूर्णांकerrupt)(काष्ठा wilc *nic);
	व्योम (*disable_पूर्णांकerrupt)(काष्ठा wilc *nic);
पूर्ण;

#घोषणा WILC_MAX_CFG_FRAME_SIZE		1468

काष्ठा tx_complete_data अणु
	पूर्णांक size;
	व्योम *buff;
	काष्ठा sk_buff *skb;
पूर्ण;

काष्ठा wilc_cfg_cmd_hdr अणु
	u8 cmd_type;
	u8 seq_no;
	__le16 total_len;
	__le32 driver_handler;
पूर्ण;

काष्ठा wilc_cfg_frame अणु
	काष्ठा wilc_cfg_cmd_hdr hdr;
	u8 frame[WILC_MAX_CFG_FRAME_SIZE];
पूर्ण;

काष्ठा wilc_cfg_rsp अणु
	u8 type;
	u8 seq_no;
पूर्ण;

काष्ठा wilc_vअगर;

पूर्णांक wilc_wlan_firmware_करोwnload(काष्ठा wilc *wilc, स्थिर u8 *buffer,
				u32 buffer_size);
पूर्णांक wilc_wlan_start(काष्ठा wilc *wilc);
पूर्णांक wilc_wlan_stop(काष्ठा wilc *wilc, काष्ठा wilc_vअगर *vअगर);
पूर्णांक wilc_wlan_txq_add_net_pkt(काष्ठा net_device *dev,
			      काष्ठा tx_complete_data *tx_data, u8 *buffer,
			      u32 buffer_size,
			      व्योम (*tx_complete_fn)(व्योम *, पूर्णांक));
पूर्णांक wilc_wlan_handle_txq(काष्ठा wilc *wl, u32 *txq_count);
व्योम wilc_handle_isr(काष्ठा wilc *wilc);
व्योम wilc_wlan_cleanup(काष्ठा net_device *dev);
पूर्णांक wilc_wlan_cfg_set(काष्ठा wilc_vअगर *vअगर, पूर्णांक start, u16 wid, u8 *buffer,
		      u32 buffer_size, पूर्णांक commit, u32 drv_handler);
पूर्णांक wilc_wlan_cfg_get(काष्ठा wilc_vअगर *vअगर, पूर्णांक start, u16 wid, पूर्णांक commit,
		      u32 drv_handler);
पूर्णांक wilc_wlan_txq_add_mgmt_pkt(काष्ठा net_device *dev, व्योम *priv, u8 *buffer,
			       u32 buffer_size, व्योम (*func)(व्योम *, पूर्णांक));
व्योम wilc_enable_tcp_ack_filter(काष्ठा wilc_vअगर *vअगर, bool value);
पूर्णांक wilc_wlan_get_num_conn_अगरcs(काष्ठा wilc *wilc);
netdev_tx_t wilc_mac_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev);

व्योम wilc_wfi_p2p_rx(काष्ठा wilc_vअगर *vअगर, u8 *buff, u32 size);
व्योम host_wakeup_notअगरy(काष्ठा wilc *wilc);
व्योम host_sleep_notअगरy(काष्ठा wilc *wilc);
व्योम chip_allow_sleep(काष्ठा wilc *wilc);
व्योम chip_wakeup(काष्ठा wilc *wilc);
पूर्णांक wilc_send_config_pkt(काष्ठा wilc_vअगर *vअगर, u8 mode, काष्ठा wid *wids,
			 u32 count);
पूर्णांक wilc_wlan_init(काष्ठा net_device *dev);
u32 wilc_get_chipid(काष्ठा wilc *wilc, bool update);
#पूर्ण_अगर
