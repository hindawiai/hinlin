<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित __UNIMAC_H
#घोषणा __UNIMAC_H

#घोषणा UMAC_HD_BKP_CTRL		0x004
#घोषणा  HD_FC_EN			(1 << 0)
#घोषणा  HD_FC_BKOFF_OK			(1 << 1)
#घोषणा  IPG_CONFIG_RX_SHIFT		2
#घोषणा  IPG_CONFIG_RX_MASK		0x1F
#घोषणा UMAC_CMD			0x008
#घोषणा  CMD_TX_EN			(1 << 0)
#घोषणा  CMD_RX_EN			(1 << 1)
#घोषणा  CMD_SPEED_10			0
#घोषणा  CMD_SPEED_100			1
#घोषणा  CMD_SPEED_1000			2
#घोषणा  CMD_SPEED_2500			3
#घोषणा  CMD_SPEED_SHIFT		2
#घोषणा  CMD_SPEED_MASK			3
#घोषणा  CMD_PROMISC			(1 << 4)
#घोषणा  CMD_PAD_EN			(1 << 5)
#घोषणा  CMD_CRC_FWD			(1 << 6)
#घोषणा  CMD_PAUSE_FWD			(1 << 7)
#घोषणा  CMD_RX_PAUSE_IGNORE		(1 << 8)
#घोषणा  CMD_TX_ADDR_INS		(1 << 9)
#घोषणा  CMD_HD_EN			(1 << 10)
#घोषणा  CMD_SW_RESET_OLD		(1 << 11)
#घोषणा  CMD_SW_RESET			(1 << 13)
#घोषणा  CMD_LCL_LOOP_EN		(1 << 15)
#घोषणा  CMD_AUTO_CONFIG		(1 << 22)
#घोषणा  CMD_CNTL_FRM_EN		(1 << 23)
#घोषणा  CMD_NO_LEN_CHK			(1 << 24)
#घोषणा  CMD_RMT_LOOP_EN		(1 << 25)
#घोषणा  CMD_RX_ERR_DISC		(1 << 26)
#घोषणा  CMD_PRBL_EN			(1 << 27)
#घोषणा  CMD_TX_PAUSE_IGNORE		(1 << 28)
#घोषणा  CMD_TX_RX_EN			(1 << 29)
#घोषणा  CMD_RUNT_FILTER_DIS		(1 << 30)
#घोषणा UMAC_MAC0			0x00c
#घोषणा UMAC_MAC1			0x010
#घोषणा UMAC_MAX_FRAME_LEN		0x014
#घोषणा UMAC_PAUSE_QUANTA		0x018
#घोषणा UMAC_MODE			0x044
#घोषणा  MODE_LINK_STATUS		(1 << 5)
#घोषणा UMAC_FRM_TAG0			0x048		/* outer tag */
#घोषणा UMAC_FRM_TAG1			0x04c		/* inner tag */
#घोषणा UMAC_TX_IPG_LEN			0x05c
#घोषणा UMAC_EEE_CTRL			0x064
#घोषणा  EN_LPI_RX_PAUSE		(1 << 0)
#घोषणा  EN_LPI_TX_PFC			(1 << 1)
#घोषणा  EN_LPI_TX_PAUSE		(1 << 2)
#घोषणा  EEE_EN				(1 << 3)
#घोषणा  RX_FIFO_CHECK			(1 << 4)
#घोषणा  EEE_TX_CLK_DIS			(1 << 5)
#घोषणा  DIS_EEE_10M			(1 << 6)
#घोषणा  LP_IDLE_PREDICTION_MODE	(1 << 7)
#घोषणा UMAC_EEE_LPI_TIMER		0x068
#घोषणा UMAC_EEE_WAKE_TIMER		0x06C
#घोषणा UMAC_EEE_REF_COUNT		0x070
#घोषणा  EEE_REFERENCE_COUNT_MASK	0xffff
#घोषणा UMAC_RX_IPG_INV			0x078
#घोषणा UMAC_MACSEC_PROG_TX_CRC		0x310
#घोषणा UMAC_MACSEC_CTRL		0x314
#घोषणा UMAC_PAUSE_CTRL			0x330
#घोषणा UMAC_TX_FLUSH			0x334
#घोषणा UMAC_RX_FIFO_STATUS		0x338
#घोषणा UMAC_TX_FIFO_STATUS		0x33c

#पूर्ण_अगर
