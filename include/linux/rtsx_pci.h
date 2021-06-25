<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Driver क्रम Realtek PCI-Express card पढ़ोer
 *
 * Copyright(c) 2009-2013 Realtek Semiconductor Corp. All rights reserved.
 *
 * Author:
 *   Wei WANG <wei_wang@realsil.com.cn>
 */

#अगर_अघोषित __RTSX_PCI_H
#घोषणा __RTSX_PCI_H

#समावेश <linux/sched.h>
#समावेश <linux/pci.h>
#समावेश <linux/rtsx_common.h>

#घोषणा MAX_RW_REG_CNT			1024

#घोषणा RTSX_HCBAR			0x00
#घोषणा RTSX_HCBCTLR			0x04
#घोषणा   STOP_CMD			(0x01 << 28)
#घोषणा   READ_REG_CMD			0
#घोषणा   WRITE_REG_CMD			1
#घोषणा   CHECK_REG_CMD			2

#घोषणा RTSX_HDBAR			0x08
#घोषणा   RTSX_SG_INT			0x04
#घोषणा   RTSX_SG_END			0x02
#घोषणा   RTSX_SG_VALID			0x01
#घोषणा   RTSX_SG_NO_OP			0x00
#घोषणा   RTSX_SG_TRANS_DATA		(0x02 << 4)
#घोषणा   RTSX_SG_LINK_DESC		(0x03 << 4)
#घोषणा RTSX_HDBCTLR			0x0C
#घोषणा   SDMA_MODE			0x00
#घोषणा   ADMA_MODE			(0x02 << 26)
#घोषणा   STOP_DMA			(0x01 << 28)
#घोषणा   TRIG_DMA			(0x01 << 31)

#घोषणा RTSX_HAIMR			0x10
#घोषणा   HAIMR_TRANS_START		(0x01 << 31)
#घोषणा   HAIMR_READ			0x00
#घोषणा   HAIMR_WRITE			(0x01 << 30)
#घोषणा   HAIMR_READ_START		(HAIMR_TRANS_START | HAIMR_READ)
#घोषणा   HAIMR_WRITE_START		(HAIMR_TRANS_START | HAIMR_WRITE)
#घोषणा   HAIMR_TRANS_END			(HAIMR_TRANS_START)

#घोषणा RTSX_BIPR			0x14
#घोषणा   CMD_DONE_INT			(1 << 31)
#घोषणा   DATA_DONE_INT			(1 << 30)
#घोषणा   TRANS_OK_INT			(1 << 29)
#घोषणा   TRANS_FAIL_INT		(1 << 28)
#घोषणा   XD_INT			(1 << 27)
#घोषणा   MS_INT			(1 << 26)
#घोषणा   SD_INT			(1 << 25)
#घोषणा   GPIO0_INT			(1 << 24)
#घोषणा   OC_INT			(1 << 23)
#घोषणा   SD_WRITE_PROTECT		(1 << 19)
#घोषणा   XD_EXIST			(1 << 18)
#घोषणा   MS_EXIST			(1 << 17)
#घोषणा   SD_EXIST			(1 << 16)
#घोषणा   DELINK_INT			GPIO0_INT
#घोषणा   MS_OC_INT			(1 << 23)
#घोषणा   SD_OC_INT			(1 << 22)

#घोषणा CARD_INT		(XD_INT | MS_INT | SD_INT)
#घोषणा NEED_COMPLETE_INT	(DATA_DONE_INT | TRANS_OK_INT | TRANS_FAIL_INT)
#घोषणा RTSX_INT		(CMD_DONE_INT | NEED_COMPLETE_INT | \
					CARD_INT | GPIO0_INT | OC_INT)
#घोषणा CARD_EXIST		(XD_EXIST | MS_EXIST | SD_EXIST)

#घोषणा RTSX_BIER			0x18
#घोषणा   CMD_DONE_INT_EN		(1 << 31)
#घोषणा   DATA_DONE_INT_EN		(1 << 30)
#घोषणा   TRANS_OK_INT_EN		(1 << 29)
#घोषणा   TRANS_FAIL_INT_EN		(1 << 28)
#घोषणा   XD_INT_EN			(1 << 27)
#घोषणा   MS_INT_EN			(1 << 26)
#घोषणा   SD_INT_EN			(1 << 25)
#घोषणा   GPIO0_INT_EN			(1 << 24)
#घोषणा   OC_INT_EN			(1 << 23)
#घोषणा   DELINK_INT_EN			GPIO0_INT_EN
#घोषणा   MS_OC_INT_EN			(1 << 23)
#घोषणा   SD_OC_INT_EN			(1 << 22)

#घोषणा RTSX_DUM_REG			0x1C

/*
 * macros क्रम easy use
 */
#घोषणा rtsx_pci_ग_लिखोl(pcr, reg, value) \
	ioग_लिखो32(value, (pcr)->remap_addr + reg)
#घोषणा rtsx_pci_पढ़ोl(pcr, reg) \
	ioपढ़ो32((pcr)->remap_addr + reg)
#घोषणा rtsx_pci_ग_लिखोw(pcr, reg, value) \
	ioग_लिखो16(value, (pcr)->remap_addr + reg)
#घोषणा rtsx_pci_पढ़ोw(pcr, reg) \
	ioपढ़ो16((pcr)->remap_addr + reg)
#घोषणा rtsx_pci_ग_लिखोb(pcr, reg, value) \
	ioग_लिखो8(value, (pcr)->remap_addr + reg)
#घोषणा rtsx_pci_पढ़ोb(pcr, reg) \
	ioपढ़ो8((pcr)->remap_addr + reg)

#घोषणा STATE_TRANS_NONE		0
#घोषणा STATE_TRANS_CMD			1
#घोषणा STATE_TRANS_BUF			2
#घोषणा STATE_TRANS_SG			3

#घोषणा TRANS_NOT_READY			0
#घोषणा TRANS_RESULT_OK			1
#घोषणा TRANS_RESULT_FAIL		2
#घोषणा TRANS_NO_DEVICE			3

#घोषणा RTSX_RESV_BUF_LEN		4096
#घोषणा HOST_CMDS_BUF_LEN		1024
#घोषणा HOST_SG_TBL_BUF_LEN		(RTSX_RESV_BUF_LEN - HOST_CMDS_BUF_LEN)
#घोषणा HOST_SG_TBL_ITEMS		(HOST_SG_TBL_BUF_LEN / 8)
#घोषणा MAX_SG_ITEM_LEN			0x80000
#घोषणा HOST_TO_DEVICE			0
#घोषणा DEVICE_TO_HOST			1

#घोषणा OUTPUT_3V3			0
#घोषणा OUTPUT_1V8			1

#घोषणा RTSX_PHASE_MAX			32
#घोषणा RX_TUNING_CNT			3

#घोषणा MS_CFG				0xFD40
#घोषणा   SAMPLE_TIME_RISING		0x00
#घोषणा   SAMPLE_TIME_FALLING		0x80
#घोषणा   PUSH_TIME_DEFAULT		0x00
#घोषणा   PUSH_TIME_ODD			0x40
#घोषणा   NO_EXTEND_TOGGLE		0x00
#घोषणा   EXTEND_TOGGLE_CHK		0x20
#घोषणा   MS_BUS_WIDTH_1		0x00
#घोषणा   MS_BUS_WIDTH_4		0x10
#घोषणा   MS_BUS_WIDTH_8		0x18
#घोषणा   MS_2K_SECTOR_MODE		0x04
#घोषणा   MS_512_SECTOR_MODE		0x00
#घोषणा   MS_TOGGLE_TIMEOUT_EN		0x00
#घोषणा   MS_TOGGLE_TIMEOUT_DISEN	0x01
#घोषणा MS_NO_CHECK_INT			0x02
#घोषणा MS_TPC				0xFD41
#घोषणा MS_TRANS_CFG			0xFD42
#घोषणा   WAIT_INT			0x80
#घोषणा   NO_WAIT_INT			0x00
#घोषणा   NO_AUTO_READ_INT_REG		0x00
#घोषणा   AUTO_READ_INT_REG		0x40
#घोषणा   MS_CRC16_ERR			0x20
#घोषणा   MS_RDY_TIMEOUT		0x10
#घोषणा   MS_INT_CMDNK			0x08
#घोषणा   MS_INT_BREQ			0x04
#घोषणा   MS_INT_ERR			0x02
#घोषणा   MS_INT_CED			0x01
#घोषणा MS_TRANSFER			0xFD43
#घोषणा   MS_TRANSFER_START		0x80
#घोषणा   MS_TRANSFER_END		0x40
#घोषणा   MS_TRANSFER_ERR		0x20
#घोषणा   MS_BS_STATE			0x10
#घोषणा   MS_TM_READ_BYTES		0x00
#घोषणा   MS_TM_NORMAL_READ		0x01
#घोषणा   MS_TM_WRITE_BYTES		0x04
#घोषणा   MS_TM_NORMAL_WRITE		0x05
#घोषणा   MS_TM_AUTO_READ		0x08
#घोषणा   MS_TM_AUTO_WRITE		0x0C
#घोषणा MS_INT_REG			0xFD44
#घोषणा MS_BYTE_CNT			0xFD45
#घोषणा MS_SECTOR_CNT_L			0xFD46
#घोषणा MS_SECTOR_CNT_H			0xFD47
#घोषणा MS_DBUS_H			0xFD48

#घोषणा SD_CFG1				0xFDA0
#घोषणा   SD_CLK_DIVIDE_0		0x00
#घोषणा   SD_CLK_DIVIDE_256		0xC0
#घोषणा   SD_CLK_DIVIDE_128		0x80
#घोषणा   SD_BUS_WIDTH_1BIT		0x00
#घोषणा   SD_BUS_WIDTH_4BIT		0x01
#घोषणा   SD_BUS_WIDTH_8BIT		0x02
#घोषणा   SD_ASYNC_FIFO_NOT_RST		0x10
#घोषणा   SD_20_MODE			0x00
#घोषणा   SD_DDR_MODE			0x04
#घोषणा   SD_30_MODE			0x08
#घोषणा   SD_CLK_DIVIDE_MASK		0xC0
#घोषणा   SD_MODE_SELECT_MASK		0x0C
#घोषणा SD_CFG2				0xFDA1
#घोषणा   SD_CALCULATE_CRC7		0x00
#घोषणा   SD_NO_CALCULATE_CRC7		0x80
#घोषणा   SD_CHECK_CRC16		0x00
#घोषणा   SD_NO_CHECK_CRC16		0x40
#घोषणा   SD_NO_CHECK_WAIT_CRC_TO	0x20
#घोषणा   SD_WAIT_BUSY_END		0x08
#घोषणा   SD_NO_WAIT_BUSY_END		0x00
#घोषणा   SD_CHECK_CRC7			0x00
#घोषणा   SD_NO_CHECK_CRC7		0x04
#घोषणा   SD_RSP_LEN_0			0x00
#घोषणा   SD_RSP_LEN_6			0x01
#घोषणा   SD_RSP_LEN_17			0x02
#घोषणा   SD_RSP_TYPE_R0		0x04
#घोषणा   SD_RSP_TYPE_R1		0x01
#घोषणा   SD_RSP_TYPE_R1b		0x09
#घोषणा   SD_RSP_TYPE_R2		0x02
#घोषणा   SD_RSP_TYPE_R3		0x05
#घोषणा   SD_RSP_TYPE_R4		0x05
#घोषणा   SD_RSP_TYPE_R5		0x01
#घोषणा   SD_RSP_TYPE_R6		0x01
#घोषणा   SD_RSP_TYPE_R7		0x01
#घोषणा SD_CFG3				0xFDA2
#घोषणा   SD30_CLK_END_EN		0x10
#घोषणा   SD_RSP_80CLK_TIMEOUT_EN	0x01

#घोषणा SD_STAT1			0xFDA3
#घोषणा   SD_CRC7_ERR			0x80
#घोषणा   SD_CRC16_ERR			0x40
#घोषणा   SD_CRC_WRITE_ERR		0x20
#घोषणा   SD_CRC_WRITE_ERR_MASK		0x1C
#घोषणा   GET_CRC_TIME_OUT		0x02
#घोषणा   SD_TUNING_COMPARE_ERR		0x01
#घोषणा SD_STAT2			0xFDA4
#घोषणा   SD_RSP_80CLK_TIMEOUT		0x01

#घोषणा SD_BUS_STAT			0xFDA5
#घोषणा   SD_CLK_TOGGLE_EN		0x80
#घोषणा   SD_CLK_FORCE_STOP		0x40
#घोषणा   SD_DAT3_STATUS		0x10
#घोषणा   SD_DAT2_STATUS		0x08
#घोषणा   SD_DAT1_STATUS		0x04
#घोषणा   SD_DAT0_STATUS		0x02
#घोषणा   SD_CMD_STATUS			0x01
#घोषणा SD_PAD_CTL			0xFDA6
#घोषणा   SD_IO_USING_1V8		0x80
#घोषणा   SD_IO_USING_3V3		0x7F
#घोषणा   TYPE_A_DRIVING		0x00
#घोषणा   TYPE_B_DRIVING		0x01
#घोषणा   TYPE_C_DRIVING		0x02
#घोषणा   TYPE_D_DRIVING		0x03
#घोषणा SD_SAMPLE_POINT_CTL		0xFDA7
#घोषणा   DDR_FIX_RX_DAT		0x00
#घोषणा   DDR_VAR_RX_DAT		0x80
#घोषणा   DDR_FIX_RX_DAT_EDGE		0x00
#घोषणा   DDR_FIX_RX_DAT_14_DELAY	0x40
#घोषणा   DDR_FIX_RX_CMD		0x00
#घोषणा   DDR_VAR_RX_CMD		0x20
#घोषणा   DDR_FIX_RX_CMD_POS_EDGE	0x00
#घोषणा   DDR_FIX_RX_CMD_14_DELAY	0x10
#घोषणा   SD20_RX_POS_EDGE		0x00
#घोषणा   SD20_RX_14_DELAY		0x08
#घोषणा SD20_RX_SEL_MASK		0x08
#घोषणा SD_PUSH_POINT_CTL		0xFDA8
#घोषणा   DDR_FIX_TX_CMD_DAT		0x00
#घोषणा   DDR_VAR_TX_CMD_DAT		0x80
#घोषणा   DDR_FIX_TX_DAT_14_TSU		0x00
#घोषणा   DDR_FIX_TX_DAT_12_TSU		0x40
#घोषणा   DDR_FIX_TX_CMD_NEG_EDGE	0x00
#घोषणा   DDR_FIX_TX_CMD_14_AHEAD	0x20
#घोषणा   SD20_TX_NEG_EDGE		0x00
#घोषणा   SD20_TX_14_AHEAD		0x10
#घोषणा   SD20_TX_SEL_MASK		0x10
#घोषणा   DDR_VAR_SDCLK_POL_SWAP	0x01
#घोषणा SD_CMD0				0xFDA9
#घोषणा   SD_CMD_START			0x40
#घोषणा SD_CMD1				0xFDAA
#घोषणा SD_CMD2				0xFDAB
#घोषणा SD_CMD3				0xFDAC
#घोषणा SD_CMD4				0xFDAD
#घोषणा SD_CMD5				0xFDAE
#घोषणा SD_BYTE_CNT_L			0xFDAF
#घोषणा SD_BYTE_CNT_H			0xFDB0
#घोषणा SD_BLOCK_CNT_L			0xFDB1
#घोषणा SD_BLOCK_CNT_H			0xFDB2
#घोषणा SD_TRANSFER			0xFDB3
#घोषणा   SD_TRANSFER_START		0x80
#घोषणा   SD_TRANSFER_END		0x40
#घोषणा   SD_STAT_IDLE			0x20
#घोषणा   SD_TRANSFER_ERR		0x10
#घोषणा   SD_TM_NORMAL_WRITE		0x00
#घोषणा   SD_TM_AUTO_WRITE_3		0x01
#घोषणा   SD_TM_AUTO_WRITE_4		0x02
#घोषणा   SD_TM_AUTO_READ_3		0x05
#घोषणा   SD_TM_AUTO_READ_4		0x06
#घोषणा   SD_TM_CMD_RSP			0x08
#घोषणा   SD_TM_AUTO_WRITE_1		0x09
#घोषणा   SD_TM_AUTO_WRITE_2		0x0A
#घोषणा   SD_TM_NORMAL_READ		0x0C
#घोषणा   SD_TM_AUTO_READ_1		0x0D
#घोषणा   SD_TM_AUTO_READ_2		0x0E
#घोषणा   SD_TM_AUTO_TUNING		0x0F
#घोषणा SD_CMD_STATE			0xFDB5
#घोषणा   SD_CMD_IDLE			0x80

#घोषणा SD_DATA_STATE			0xFDB6
#घोषणा   SD_DATA_IDLE			0x80
#घोषणा REG_SD_STOP_SDCLK_CFG		0xFDB8
#घोषणा   SD30_CLK_STOP_CFG_EN		0x04
#घोषणा   SD30_CLK_STOP_CFG1		0x02
#घोषणा   SD30_CLK_STOP_CFG0		0x01
#घोषणा REG_PRE_RW_MODE			0xFD70
#घोषणा EN_INFINITE_MODE		0x01
#घोषणा REG_CRC_DUMMY_0		0xFD71
#घोषणा CFG_SD_POW_AUTO_PD		(1<<0)

#घोषणा SRCTL				0xFC13

#घोषणा DCM_DRP_CTL			0xFC23
#घोषणा   DCM_RESET			0x08
#घोषणा   DCM_LOCKED			0x04
#घोषणा   DCM_208M			0x00
#घोषणा   DCM_TX			0x01
#घोषणा   DCM_RX			0x02
#घोषणा DCM_DRP_TRIG			0xFC24
#घोषणा   DRP_START			0x80
#घोषणा   DRP_DONE			0x40
#घोषणा DCM_DRP_CFG			0xFC25
#घोषणा   DRP_WRITE			0x80
#घोषणा   DRP_READ			0x00
#घोषणा   DCM_WRITE_ADDRESS_50		0x50
#घोषणा   DCM_WRITE_ADDRESS_51		0x51
#घोषणा   DCM_READ_ADDRESS_00		0x00
#घोषणा   DCM_READ_ADDRESS_51		0x51
#घोषणा DCM_DRP_WR_DATA_L		0xFC26
#घोषणा DCM_DRP_WR_DATA_H		0xFC27
#घोषणा DCM_DRP_RD_DATA_L		0xFC28
#घोषणा DCM_DRP_RD_DATA_H		0xFC29
#घोषणा SD_VPCLK0_CTL			0xFC2A
#घोषणा SD_VPCLK1_CTL			0xFC2B
#घोषणा   PHASE_SELECT_MASK		0x1F
#घोषणा SD_DCMPS0_CTL			0xFC2C
#घोषणा SD_DCMPS1_CTL			0xFC2D
#घोषणा SD_VPTX_CTL			SD_VPCLK0_CTL
#घोषणा SD_VPRX_CTL			SD_VPCLK1_CTL
#घोषणा   PHASE_CHANGE			0x80
#घोषणा   PHASE_NOT_RESET		0x40
#घोषणा SD_DCMPS_TX_CTL			SD_DCMPS0_CTL
#घोषणा SD_DCMPS_RX_CTL			SD_DCMPS1_CTL
#घोषणा   DCMPS_CHANGE			0x80
#घोषणा   DCMPS_CHANGE_DONE		0x40
#घोषणा   DCMPS_ERROR			0x20
#घोषणा   DCMPS_CURRENT_PHASE		0x1F
#घोषणा CARD_CLK_SOURCE			0xFC2E
#घोषणा   CRC_FIX_CLK			(0x00 << 0)
#घोषणा   CRC_VAR_CLK0			(0x01 << 0)
#घोषणा   CRC_VAR_CLK1			(0x02 << 0)
#घोषणा   SD30_FIX_CLK			(0x00 << 2)
#घोषणा   SD30_VAR_CLK0			(0x01 << 2)
#घोषणा   SD30_VAR_CLK1			(0x02 << 2)
#घोषणा   SAMPLE_FIX_CLK		(0x00 << 4)
#घोषणा   SAMPLE_VAR_CLK0		(0x01 << 4)
#घोषणा   SAMPLE_VAR_CLK1		(0x02 << 4)
#घोषणा CARD_PWR_CTL			0xFD50
#घोषणा   PMOS_STRG_MASK		0x10
#घोषणा   PMOS_STRG_800mA		0x10
#घोषणा   PMOS_STRG_400mA		0x00
#घोषणा   SD_POWER_OFF			0x03
#घोषणा   SD_PARTIAL_POWER_ON		0x01
#घोषणा   SD_POWER_ON			0x00
#घोषणा   SD_POWER_MASK			0x03
#घोषणा   MS_POWER_OFF			0x0C
#घोषणा   MS_PARTIAL_POWER_ON		0x04
#घोषणा   MS_POWER_ON			0x00
#घोषणा   MS_POWER_MASK			0x0C
#घोषणा   BPP_POWER_OFF			0x0F
#घोषणा   BPP_POWER_5_PERCENT_ON	0x0E
#घोषणा   BPP_POWER_10_PERCENT_ON	0x0C
#घोषणा   BPP_POWER_15_PERCENT_ON	0x08
#घोषणा   BPP_POWER_ON			0x00
#घोषणा   BPP_POWER_MASK		0x0F
#घोषणा   SD_VCC_PARTIAL_POWER_ON	0x02
#घोषणा   SD_VCC_POWER_ON		0x00
#घोषणा CARD_CLK_SWITCH			0xFD51
#घोषणा RTL8411B_PACKAGE_MODE		0xFD51
#घोषणा CARD_SHARE_MODE			0xFD52
#घोषणा   CARD_SHARE_MASK		0x0F
#घोषणा   CARD_SHARE_MULTI_LUN		0x00
#घोषणा   CARD_SHARE_NORMAL		0x00
#घोषणा   CARD_SHARE_48_SD		0x04
#घोषणा   CARD_SHARE_48_MS		0x08
#घोषणा   CARD_SHARE_BAROSSA_SD		0x01
#घोषणा   CARD_SHARE_BAROSSA_MS		0x02
#घोषणा CARD_DRIVE_SEL			0xFD53
#घोषणा   MS_DRIVE_8mA			(0x01 << 6)
#घोषणा   MMC_DRIVE_8mA			(0x01 << 4)
#घोषणा   XD_DRIVE_8mA			(0x01 << 2)
#घोषणा   GPIO_DRIVE_8mA		0x01
#घोषणा RTS5209_CARD_DRIVE_DEFAULT	(MS_DRIVE_8mA | MMC_DRIVE_8mA |\
					XD_DRIVE_8mA | GPIO_DRIVE_8mA)
#घोषणा RTL8411_CARD_DRIVE_DEFAULT	(MS_DRIVE_8mA | MMC_DRIVE_8mA |\
					XD_DRIVE_8mA)
#घोषणा RTSX_CARD_DRIVE_DEFAULT		(MS_DRIVE_8mA | GPIO_DRIVE_8mA)

#घोषणा CARD_STOP			0xFD54
#घोषणा   SPI_STOP			0x01
#घोषणा   XD_STOP			0x02
#घोषणा   SD_STOP			0x04
#घोषणा   MS_STOP			0x08
#घोषणा   SPI_CLR_ERR			0x10
#घोषणा   XD_CLR_ERR			0x20
#घोषणा   SD_CLR_ERR			0x40
#घोषणा   MS_CLR_ERR			0x80
#घोषणा CARD_OE				0xFD55
#घोषणा   SD_OUTPUT_EN			0x04
#घोषणा   MS_OUTPUT_EN			0x08
#घोषणा CARD_AUTO_BLINK			0xFD56
#घोषणा CARD_GPIO_सूची			0xFD57
#घोषणा CARD_GPIO			0xFD58
#घोषणा CARD_DATA_SOURCE		0xFD5B
#घोषणा   PINGPONG_BUFFER		0x01
#घोषणा   RING_BUFFER			0x00
#घोषणा SD30_CLK_DRIVE_SEL		0xFD5A
#घोषणा   DRIVER_TYPE_A			0x05
#घोषणा   DRIVER_TYPE_B			0x03
#घोषणा   DRIVER_TYPE_C			0x02
#घोषणा   DRIVER_TYPE_D			0x01
#घोषणा CARD_SELECT			0xFD5C
#घोषणा   SD_MOD_SEL			2
#घोषणा   MS_MOD_SEL			3
#घोषणा SD30_DRIVE_SEL			0xFD5E
#घोषणा   CFG_DRIVER_TYPE_A		0x02
#घोषणा   CFG_DRIVER_TYPE_B		0x03
#घोषणा   CFG_DRIVER_TYPE_C		0x01
#घोषणा   CFG_DRIVER_TYPE_D		0x00
#घोषणा SD30_CMD_DRIVE_SEL		0xFD5E
#घोषणा SD30_DAT_DRIVE_SEL		0xFD5F
#घोषणा CARD_CLK_EN			0xFD69
#घोषणा   SD_CLK_EN			0x04
#घोषणा   MS_CLK_EN			0x08
#घोषणा   SD40_CLK_EN		0x10
#घोषणा SDIO_CTRL			0xFD6B
#घोषणा CD_PAD_CTL			0xFD73
#घोषणा   CD_DISABLE_MASK		0x07
#घोषणा   MS_CD_DISABLE			0x04
#घोषणा   SD_CD_DISABLE			0x02
#घोषणा   XD_CD_DISABLE			0x01
#घोषणा   CD_DISABLE			0x07
#घोषणा   CD_ENABLE			0x00
#घोषणा   MS_CD_EN_ONLY			0x03
#घोषणा   SD_CD_EN_ONLY			0x05
#घोषणा   XD_CD_EN_ONLY			0x06
#घोषणा   FORCE_CD_LOW_MASK		0x38
#घोषणा   FORCE_CD_XD_LOW		0x08
#घोषणा   FORCE_CD_SD_LOW		0x10
#घोषणा   FORCE_CD_MS_LOW		0x20
#घोषणा   CD_AUTO_DISABLE		0x40
#घोषणा FPDCTL				0xFC00
#घोषणा   SSC_POWER_DOWN		0x01
#घोषणा   SD_OC_POWER_DOWN		0x02
#घोषणा   ALL_POWER_DOWN		0x03
#घोषणा   OC_POWER_DOWN			0x02
#घोषणा PDINFO				0xFC01

#घोषणा CLK_CTL				0xFC02
#घोषणा   CHANGE_CLK			0x01
#घोषणा   CLK_LOW_FREQ			0x01

#घोषणा CLK_DIV				0xFC03
#घोषणा   CLK_DIV_1			0x01
#घोषणा   CLK_DIV_2			0x02
#घोषणा   CLK_DIV_4			0x03
#घोषणा   CLK_DIV_8			0x04
#घोषणा CLK_SEL				0xFC04

#घोषणा SSC_DIV_N_0			0xFC0F
#घोषणा SSC_DIV_N_1			0xFC10
#घोषणा SSC_CTL1			0xFC11
#घोषणा    SSC_RSTB			0x80
#घोषणा    SSC_8X_EN			0x40
#घोषणा    SSC_FIX_FRAC			0x20
#घोषणा    SSC_SEL_1M			0x00
#घोषणा    SSC_SEL_2M			0x08
#घोषणा    SSC_SEL_4M			0x10
#घोषणा    SSC_SEL_8M			0x18
#घोषणा SSC_CTL2			0xFC12
#घोषणा    SSC_DEPTH_MASK		0x07
#घोषणा    SSC_DEPTH_DISALBE		0x00
#घोषणा    SSC_DEPTH_4M			0x01
#घोषणा    SSC_DEPTH_2M			0x02
#घोषणा    SSC_DEPTH_1M			0x03
#घोषणा    SSC_DEPTH_500K		0x04
#घोषणा    SSC_DEPTH_250K		0x05
#घोषणा RCCTL				0xFC14

#घोषणा FPGA_PULL_CTL			0xFC1D
#घोषणा OLT_LED_CTL			0xFC1E
#घोषणा   LED_SHINE_MASK		0x08
#घोषणा   LED_SHINE_EN			0x08
#घोषणा   LED_SHINE_DISABLE		0x00
#घोषणा GPIO_CTL			0xFC1F

#घोषणा LDO_CTL				0xFC1E
#घोषणा   BPP_ASIC_1V7			0x00
#घोषणा   BPP_ASIC_1V8			0x01
#घोषणा   BPP_ASIC_1V9			0x02
#घोषणा   BPP_ASIC_2V0			0x03
#घोषणा   BPP_ASIC_2V7			0x04
#घोषणा   BPP_ASIC_2V8			0x05
#घोषणा   BPP_ASIC_3V2			0x06
#घोषणा   BPP_ASIC_3V3			0x07
#घोषणा   BPP_REG_TUNED18		0x07
#घोषणा   BPP_TUNED18_SHIFT_8402	5
#घोषणा   BPP_TUNED18_SHIFT_8411	4
#घोषणा   BPP_PAD_MASK			0x04
#घोषणा   BPP_PAD_3V3			0x04
#घोषणा   BPP_PAD_1V8			0x00
#घोषणा   BPP_LDO_POWB			0x03
#घोषणा   BPP_LDO_ON			0x00
#घोषणा   BPP_LDO_SUSPEND		0x02
#घोषणा   BPP_LDO_OFF			0x03
#घोषणा EFUSE_CTL			0xFC30
#घोषणा EFUSE_ADD			0xFC31
#घोषणा SYS_VER				0xFC32
#घोषणा EFUSE_DATAL			0xFC34
#घोषणा EFUSE_DATAH			0xFC35

#घोषणा CARD_PULL_CTL1			0xFD60
#घोषणा CARD_PULL_CTL2			0xFD61
#घोषणा CARD_PULL_CTL3			0xFD62
#घोषणा CARD_PULL_CTL4			0xFD63
#घोषणा CARD_PULL_CTL5			0xFD64
#घोषणा CARD_PULL_CTL6			0xFD65

/* PCI Express Related Registers */
#घोषणा IRQEN0				0xFE20
#घोषणा IRQSTAT0			0xFE21
#घोषणा    DMA_DONE_INT			0x80
#घोषणा    SUSPEND_INT			0x40
#घोषणा    LINK_RDY_INT			0x20
#घोषणा    LINK_DOWN_INT		0x10
#घोषणा IRQEN1				0xFE22
#घोषणा IRQSTAT1			0xFE23
#घोषणा TLPRIEN				0xFE24
#घोषणा TLPRISTAT			0xFE25
#घोषणा TLPTIEN				0xFE26
#घोषणा TLPTISTAT			0xFE27
#घोषणा DMATC0				0xFE28
#घोषणा DMATC1				0xFE29
#घोषणा DMATC2				0xFE2A
#घोषणा DMATC3				0xFE2B
#घोषणा DMACTL				0xFE2C
#घोषणा   DMA_RST			0x80
#घोषणा   DMA_BUSY			0x04
#घोषणा   DMA_सूची_TO_CARD		0x00
#घोषणा   DMA_सूची_FROM_CARD		0x02
#घोषणा   DMA_EN			0x01
#घोषणा   DMA_128			(0 << 4)
#घोषणा   DMA_256			(1 << 4)
#घोषणा   DMA_512			(2 << 4)
#घोषणा   DMA_1024			(3 << 4)
#घोषणा   DMA_PACK_SIZE_MASK		0x30
#घोषणा BCTL				0xFE2D
#घोषणा RBBC0				0xFE2E
#घोषणा RBBC1				0xFE2F
#घोषणा RBDAT				0xFE30
#घोषणा RBCTL				0xFE34
#घोषणा   U_AUTO_DMA_EN_MASK		0x20
#घोषणा   U_AUTO_DMA_DISABLE		0x00
#घोषणा   RB_FLUSH			0x80
#घोषणा CFGADDR0			0xFE35
#घोषणा CFGADDR1			0xFE36
#घोषणा CFGDATA0			0xFE37
#घोषणा CFGDATA1			0xFE38
#घोषणा CFGDATA2			0xFE39
#घोषणा CFGDATA3			0xFE3A
#घोषणा CFGRWCTL			0xFE3B
#घोषणा PHYRWCTL			0xFE3C
#घोषणा PHYDATA0			0xFE3D
#घोषणा PHYDATA1			0xFE3E
#घोषणा PHYADDR				0xFE3F
#घोषणा MSGRXDATA0			0xFE40
#घोषणा MSGRXDATA1			0xFE41
#घोषणा MSGRXDATA2			0xFE42
#घोषणा MSGRXDATA3			0xFE43
#घोषणा MSGTXDATA0			0xFE44
#घोषणा MSGTXDATA1			0xFE45
#घोषणा MSGTXDATA2			0xFE46
#घोषणा MSGTXDATA3			0xFE47
#घोषणा MSGTXCTL			0xFE48
#घोषणा LTR_CTL				0xFE4A
#घोषणा LTR_TX_EN_MASK		BIT(7)
#घोषणा LTR_TX_EN_1			BIT(7)
#घोषणा LTR_TX_EN_0			0
#घोषणा LTR_LATENCY_MODE_MASK		BIT(6)
#घोषणा LTR_LATENCY_MODE_HW		0
#घोषणा LTR_LATENCY_MODE_SW		BIT(6)
#घोषणा OBFF_CFG			0xFE4C
#घोषणा   OBFF_EN_MASK			0x03
#घोषणा   OBFF_DISABLE			0x00

#घोषणा CDRESUMECTL			0xFE52
#घोषणा WAKE_SEL_CTL			0xFE54
#घोषणा PCLK_CTL			0xFE55
#घोषणा   PCLK_MODE_SEL			0x20
#घोषणा PME_FORCE_CTL			0xFE56

#घोषणा ASPM_FORCE_CTL			0xFE57
#घोषणा   FORCE_ASPM_CTL0		0x10
#घोषणा   FORCE_ASPM_CTL1		0x20
#घोषणा   FORCE_ASPM_VAL_MASK		0x03
#घोषणा   FORCE_ASPM_L1_EN		0x02
#घोषणा   FORCE_ASPM_L0_EN		0x01
#घोषणा   FORCE_ASPM_NO_ASPM		0x00
#घोषणा PM_CLK_FORCE_CTL		0xFE58
#घोषणा   CLK_PM_EN			0x01
#घोषणा FUNC_FORCE_CTL			0xFE59
#घोषणा   FUNC_FORCE_UPME_XMT_DBG	0x02
#घोषणा PERST_GLITCH_WIDTH		0xFE5C
#घोषणा CHANGE_LINK_STATE		0xFE5B
#घोषणा RESET_LOAD_REG			0xFE5E
#घोषणा EFUSE_CONTENT			0xFE5F
#घोषणा HOST_SLEEP_STATE		0xFE60
#घोषणा   HOST_ENTER_S1			1
#घोषणा   HOST_ENTER_S3			2

#घोषणा SDIO_CFG			0xFE70
#घोषणा PM_EVENT_DEBUG			0xFE71
#घोषणा   PME_DEBUG_0			0x08
#घोषणा NFTS_TX_CTRL			0xFE72

#घोषणा PWR_GATE_CTRL			0xFE75
#घोषणा   PWR_GATE_EN			0x01
#घोषणा   LDO3318_PWR_MASK		0x06
#घोषणा   LDO_ON			0x00
#घोषणा   LDO_SUSPEND			0x04
#घोषणा   LDO_OFF			0x06
#घोषणा PWD_SUSPEND_EN			0xFE76
#घोषणा LDO_PWR_SEL			0xFE78

#घोषणा L1SUB_CONFIG1			0xFE8D
#घोषणा   AUX_CLK_ACTIVE_SEL_MASK	0x01
#घोषणा   MAC_CKSW_DONE			0x00
#घोषणा L1SUB_CONFIG2			0xFE8E
#घोषणा   L1SUB_AUTO_CFG		0x02
#घोषणा L1SUB_CONFIG3			0xFE8F
#घोषणा   L1OFF_MBIAS2_EN_5250		BIT(7)

#घोषणा DUMMY_REG_RESET_0		0xFE90
#घोषणा   IC_VERSION_MASK		0x0F

#घोषणा REG_VREF			0xFE97
#घोषणा   PWD_SUSPND_EN			0x10
#घोषणा RTS5260_DMA_RST_CTL_0		0xFEBF
#घोषणा   RTS5260_DMA_RST		0x80
#घोषणा   RTS5260_ADMA3_RST		0x40
#घोषणा AUTOLOAD_CFG_BASE		0xFF00
#घोषणा RELINK_TIME_MASK		0x01
#घोषणा PETXCFG				0xFF03
#घोषणा FORCE_CLKREQ_DELINK_MASK	BIT(7)
#घोषणा FORCE_CLKREQ_LOW	0x80
#घोषणा FORCE_CLKREQ_HIGH	0x00

#घोषणा PM_CTRL1			0xFF44
#घोषणा   CD_RESUME_EN_MASK		0xF0

#घोषणा PM_CTRL2			0xFF45
#घोषणा PM_CTRL3			0xFF46
#घोषणा   SDIO_SEND_PME_EN		0x80
#घोषणा   FORCE_RC_MODE_ON		0x40
#घोषणा   FORCE_RX50_LINK_ON		0x20
#घोषणा   D3_DELINK_MODE_EN		0x10
#घोषणा   USE_PESRTB_CTL_DELINK		0x08
#घोषणा   DELAY_PIN_WAKE		0x04
#घोषणा   RESET_PIN_WAKE		0x02
#घोषणा   PM_WAKE_EN			0x01
#घोषणा PM_CTRL4			0xFF47

/* FW config info रेजिस्टर */
#घोषणा RTS5261_FW_CFG_INFO0		0xFF50
#घोषणा   RTS5261_FW_EXPRESS_TEST_MASK	(0x01 << 0)
#घोषणा   RTS5261_FW_EA_MODE_MASK	(0x01 << 5)
#घोषणा RTS5261_FW_CFG0			0xFF54
#घोषणा   RTS5261_FW_ENTER_EXPRESS	(0x01 << 0)

#घोषणा RTS5261_FW_CFG1			0xFF55
#घोषणा   RTS5261_SYS_CLK_SEL_MCU_CLK	(0x01 << 7)
#घोषणा   RTS5261_CRC_CLK_SEL_MCU_CLK	(0x01 << 6)
#घोषणा   RTS5261_FAKE_MCU_CLOCK_GATING	(0x01 << 5)
#घोषणा   RTS5261_MCU_BUS_SEL_MASK	(0x01 << 4)
#घोषणा   RTS5261_MCU_CLOCK_SEL_MASK	(0x03 << 2)
#घोषणा   RTS5261_MCU_CLOCK_SEL_16M	(0x01 << 2)
#घोषणा   RTS5261_MCU_CLOCK_GATING	(0x01 << 1)
#घोषणा   RTS5261_DRIVER_ENABLE_FW	(0x01 << 0)

#घोषणा REG_CFG_OOBS_OFF_TIMER 0xFEA6
#घोषणा REG_CFG_OOBS_ON_TIMER 0xFEA7
#घोषणा REG_CFG_VCM_ON_TIMER 0xFEA8
#घोषणा REG_CFG_OOBS_POLLING 0xFEA9

/* Memory mapping */
#घोषणा SRAM_BASE			0xE600
#घोषणा RBUF_BASE			0xF400
#घोषणा PPBUF_BASE1			0xF800
#घोषणा PPBUF_BASE2			0xFA00
#घोषणा IMAGE_FLAG_ADDR0		0xCE80
#घोषणा IMAGE_FLAG_ADDR1		0xCE81

#घोषणा RREF_CFG			0xFF6C
#घोषणा   RREF_VBGSEL_MASK		0x38
#घोषणा   RREF_VBGSEL_1V25		0x28

#घोषणा OOBS_CONFIG			0xFF6E
#घोषणा   OOBS_AUTOK_DIS		0x80
#घोषणा   OOBS_VAL_MASK			0x1F

#घोषणा LDO_DV18_CFG			0xFF70
#घोषणा   LDO_DV18_SR_MASK		0xC0
#घोषणा   LDO_DV18_SR_DF		0x40
#घोषणा   DV331812_MASK			0x70
#घोषणा   DV331812_33			0x70
#घोषणा   DV331812_17			0x30

#घोषणा LDO_CONFIG2			0xFF71
#घोषणा   LDO_D3318_MASK		0x07
#घोषणा   LDO_D3318_33V			0x07
#घोषणा   LDO_D3318_18V			0x02
#घोषणा   DV331812_VDD1			0x04
#घोषणा   DV331812_POWERON		0x08
#घोषणा   DV331812_POWEROFF		0x00

#घोषणा LDO_VCC_CFG0			0xFF72
#घोषणा   LDO_VCC_LMTVTH_MASK		0x30
#घोषणा   LDO_VCC_LMTVTH_2A		0x10
/*RTS5260*/
#घोषणा   RTS5260_DVCC_TUNE_MASK	0x70
#घोषणा   RTS5260_DVCC_33		0x70

/*RTS5261*/
#घोषणा RTS5261_LDO1_CFG0		0xFF72
#घोषणा   RTS5261_LDO1_OCP_THD_MASK	(0x07 << 5)
#घोषणा   RTS5261_LDO1_OCP_EN		(0x01 << 4)
#घोषणा   RTS5261_LDO1_OCP_LMT_THD_MASK	(0x03 << 2)
#घोषणा   RTS5261_LDO1_OCP_LMT_EN	(0x01 << 1)

#घोषणा LDO_VCC_CFG1			0xFF73
#घोषणा   LDO_VCC_REF_TUNE_MASK		0x30
#घोषणा   LDO_VCC_REF_1V2		0x20
#घोषणा   LDO_VCC_TUNE_MASK		0x07
#घोषणा   LDO_VCC_1V8			0x04
#घोषणा   LDO_VCC_3V3			0x07
#घोषणा   LDO_VCC_LMT_EN		0x08
/*RTS5260*/
#घोषणा	  LDO_POW_SDVDD1_MASK		0x08
#घोषणा	  LDO_POW_SDVDD1_ON		0x08
#घोषणा	  LDO_POW_SDVDD1_OFF		0x00

#घोषणा LDO_VIO_CFG			0xFF75
#घोषणा   LDO_VIO_SR_MASK		0xC0
#घोषणा   LDO_VIO_SR_DF			0x40
#घोषणा   LDO_VIO_REF_TUNE_MASK		0x30
#घोषणा   LDO_VIO_REF_1V2		0x20
#घोषणा   LDO_VIO_TUNE_MASK		0x07
#घोषणा   LDO_VIO_1V7			0x03
#घोषणा   LDO_VIO_1V8			0x04
#घोषणा   LDO_VIO_3V3			0x07

#घोषणा LDO_DV12S_CFG			0xFF76
#घोषणा   LDO_REF12_TUNE_MASK		0x18
#घोषणा   LDO_REF12_TUNE_DF		0x10
#घोषणा   LDO_D12_TUNE_MASK		0x07
#घोषणा   LDO_D12_TUNE_DF		0x04

#घोषणा LDO_AV12S_CFG			0xFF77
#घोषणा   LDO_AV12S_TUNE_MASK		0x07
#घोषणा   LDO_AV12S_TUNE_DF		0x04

#घोषणा SD40_LDO_CTL1			0xFE7D
#घोषणा   SD40_VIO_TUNE_MASK		0x70
#घोषणा   SD40_VIO_TUNE_1V7		0x30
#घोषणा   SD_VIO_LDO_1V8		0x40
#घोषणा   SD_VIO_LDO_3V3		0x70

#घोषणा RTS5260_AUTOLOAD_CFG4		0xFF7F
#घोषणा   RTS5260_MIMO_DISABLE		0x8A
/*RTS5261*/
#घोषणा   RTS5261_AUX_CLK_16M_EN		(1 << 5)

#घोषणा RTS5260_REG_GPIO_CTL0		0xFC1A
#घोषणा   RTS5260_REG_GPIO_MASK		0x01
#घोषणा   RTS5260_REG_GPIO_ON		0x01
#घोषणा   RTS5260_REG_GPIO_OFF		0x00

#घोषणा PWR_GLOBAL_CTRL			0xF200
#घोषणा PCIE_L1_2_EN			0x0C
#घोषणा PCIE_L1_1_EN			0x0A
#घोषणा PCIE_L1_0_EN			0x09
#घोषणा PWR_FE_CTL			0xF201
#घोषणा PCIE_L1_2_PD_FE_EN		0x0C
#घोषणा PCIE_L1_1_PD_FE_EN		0x0A
#घोषणा PCIE_L1_0_PD_FE_EN		0x09
#घोषणा CFG_PCIE_APHY_OFF_0		0xF204
#घोषणा CFG_PCIE_APHY_OFF_0_DEFAULT	0xBF
#घोषणा CFG_PCIE_APHY_OFF_1		0xF205
#घोषणा CFG_PCIE_APHY_OFF_1_DEFAULT	0xFF
#घोषणा CFG_PCIE_APHY_OFF_2		0xF206
#घोषणा CFG_PCIE_APHY_OFF_2_DEFAULT	0x01
#घोषणा CFG_PCIE_APHY_OFF_3		0xF207
#घोषणा CFG_PCIE_APHY_OFF_3_DEFAULT	0x00
#घोषणा CFG_L1_0_PCIE_MAC_RET_VALUE	0xF20C
#घोषणा CFG_L1_0_PCIE_DPHY_RET_VALUE	0xF20E
#घोषणा CFG_L1_0_SYS_RET_VALUE		0xF210
#घोषणा CFG_L1_0_CRC_MISC_RET_VALUE	0xF212
#घोषणा CFG_L1_0_CRC_SD30_RET_VALUE	0xF214
#घोषणा CFG_L1_0_CRC_SD40_RET_VALUE	0xF216
#घोषणा CFG_LP_FPWM_VALUE		0xF219
#घोषणा CFG_LP_FPWM_VALUE_DEFAULT	0x18
#घोषणा PWC_CDR				0xF253
#घोषणा PWC_CDR_DEFAULT			0x03
#घोषणा CFG_L1_0_RET_VALUE_DEFAULT	0x1B
#घोषणा CFG_L1_0_CRC_MISC_RET_VALUE_DEFAULT	0x0C

/* OCPCTL */
#घोषणा SD_DETECT_EN			0x08
#घोषणा SD_OCP_INT_EN			0x04
#घोषणा SD_OCP_INT_CLR			0x02
#घोषणा SD_OC_CLR			0x01

#घोषणा SDVIO_DETECT_EN			(1 << 7)
#घोषणा SDVIO_OCP_INT_EN		(1 << 6)
#घोषणा SDVIO_OCP_INT_CLR		(1 << 5)
#घोषणा SDVIO_OC_CLR			(1 << 4)

/* OCPSTAT */
#घोषणा SD_OCP_DETECT			0x08
#घोषणा SD_OC_NOW			0x04
#घोषणा SD_OC_EVER			0x02

#घोषणा SDVIO_OC_NOW			(1 << 6)
#घोषणा SDVIO_OC_EVER			(1 << 5)

#घोषणा REG_OCPCTL			0xFD6A
#घोषणा REG_OCPSTAT			0xFD6E
#घोषणा REG_OCPGLITCH			0xFD6C
#घोषणा REG_OCPPARA1			0xFD6B
#घोषणा REG_OCPPARA2			0xFD6D

/* rts5260 DV3318 OCP-related रेजिस्टरs */
#घोषणा REG_DV3318_OCPCTL		0xFD89
#घोषणा DV3318_OCP_TIME_MASK	0xF0
#घोषणा DV3318_DETECT_EN		0x08
#घोषणा DV3318_OCP_INT_EN		0x04
#घोषणा DV3318_OCP_INT_CLR		0x02
#घोषणा DV3318_OCP_CLR			0x01

#घोषणा REG_DV3318_OCPSTAT		0xFD8A
#घोषणा DV3318_OCP_GlITCH_TIME_MASK	0xF0
#घोषणा DV3318_OCP_DETECT		0x08
#घोषणा DV3318_OCP_NOW			0x04
#घोषणा DV3318_OCP_EVER			0x02

#घोषणा SD_OCP_GLITCH_MASK		0x0F

/* OCPPARA1 */
#घोषणा SDVIO_OCP_TIME_60		0x00
#घोषणा SDVIO_OCP_TIME_100		0x10
#घोषणा SDVIO_OCP_TIME_200		0x20
#घोषणा SDVIO_OCP_TIME_400		0x30
#घोषणा SDVIO_OCP_TIME_600		0x40
#घोषणा SDVIO_OCP_TIME_800		0x50
#घोषणा SDVIO_OCP_TIME_1100		0x60
#घोषणा SDVIO_OCP_TIME_MASK		0x70

#घोषणा SD_OCP_TIME_60			0x00
#घोषणा SD_OCP_TIME_100			0x01
#घोषणा SD_OCP_TIME_200			0x02
#घोषणा SD_OCP_TIME_400			0x03
#घोषणा SD_OCP_TIME_600			0x04
#घोषणा SD_OCP_TIME_800			0x05
#घोषणा SD_OCP_TIME_1100		0x06
#घोषणा SD_OCP_TIME_MASK		0x07

/* OCPPARA2 */
#घोषणा SDVIO_OCP_THD_190		0x00
#घोषणा SDVIO_OCP_THD_250		0x10
#घोषणा SDVIO_OCP_THD_320		0x20
#घोषणा SDVIO_OCP_THD_380		0x30
#घोषणा SDVIO_OCP_THD_440		0x40
#घोषणा SDVIO_OCP_THD_500		0x50
#घोषणा SDVIO_OCP_THD_570		0x60
#घोषणा SDVIO_OCP_THD_630		0x70
#घोषणा SDVIO_OCP_THD_MASK		0x70

#घोषणा SD_OCP_THD_450			0x00
#घोषणा SD_OCP_THD_550			0x01
#घोषणा SD_OCP_THD_650			0x02
#घोषणा SD_OCP_THD_750			0x03
#घोषणा SD_OCP_THD_850			0x04
#घोषणा SD_OCP_THD_950			0x05
#घोषणा SD_OCP_THD_1050			0x06
#घोषणा SD_OCP_THD_1150			0x07
#घोषणा SD_OCP_THD_MASK			0x07

#घोषणा SDVIO_OCP_GLITCH_MASK		0xF0
#घोषणा SDVIO_OCP_GLITCH_NONE		0x00
#घोषणा SDVIO_OCP_GLITCH_50U		0x10
#घोषणा SDVIO_OCP_GLITCH_100U		0x20
#घोषणा SDVIO_OCP_GLITCH_200U		0x30
#घोषणा SDVIO_OCP_GLITCH_600U		0x40
#घोषणा SDVIO_OCP_GLITCH_800U		0x50
#घोषणा SDVIO_OCP_GLITCH_1M		0x60
#घोषणा SDVIO_OCP_GLITCH_2M		0x70
#घोषणा SDVIO_OCP_GLITCH_3M		0x80
#घोषणा SDVIO_OCP_GLITCH_4M		0x90
#घोषणा SDVIO_OCP_GLIVCH_5M		0xA0
#घोषणा SDVIO_OCP_GLITCH_6M		0xB0
#घोषणा SDVIO_OCP_GLITCH_7M		0xC0
#घोषणा SDVIO_OCP_GLITCH_8M		0xD0
#घोषणा SDVIO_OCP_GLITCH_9M		0xE0
#घोषणा SDVIO_OCP_GLITCH_10M		0xF0

#घोषणा SD_OCP_GLITCH_MASK		0x0F
#घोषणा SD_OCP_GLITCH_NONE		0x00
#घोषणा SD_OCP_GLITCH_50U		0x01
#घोषणा SD_OCP_GLITCH_100U		0x02
#घोषणा SD_OCP_GLITCH_200U		0x03
#घोषणा SD_OCP_GLITCH_600U		0x04
#घोषणा SD_OCP_GLITCH_800U		0x05
#घोषणा SD_OCP_GLITCH_1M		0x06
#घोषणा SD_OCP_GLITCH_2M		0x07
#घोषणा SD_OCP_GLITCH_3M		0x08
#घोषणा SD_OCP_GLITCH_4M		0x09
#घोषणा SD_OCP_GLIVCH_5M		0x0A
#घोषणा SD_OCP_GLITCH_6M		0x0B
#घोषणा SD_OCP_GLITCH_7M		0x0C
#घोषणा SD_OCP_GLITCH_8M		0x0D
#घोषणा SD_OCP_GLITCH_9M		0x0E
#घोषणा SD_OCP_GLITCH_10M		0x0F

/* Phy रेजिस्टर */
#घोषणा PHY_PCR				0x00
#घोषणा   PHY_PCR_FORCE_CODE		0xB000
#घोषणा   PHY_PCR_OOBS_CALI_50		0x0800
#घोषणा   PHY_PCR_OOBS_VCM_08		0x0200
#घोषणा   PHY_PCR_OOBS_SEN_90		0x0040
#घोषणा   PHY_PCR_RSSI_EN		0x0002
#घोषणा   PHY_PCR_RX10K			0x0001

#घोषणा PHY_RCR0			0x01
#घोषणा PHY_RCR1			0x02
#घोषणा   PHY_RCR1_ADP_TIME_4		0x0400
#घोषणा   PHY_RCR1_VCO_COARSE		0x001F
#घोषणा   PHY_RCR1_INIT_27S		0x0A1F
#घोषणा PHY_SSCCR2			0x02
#घोषणा   PHY_SSCCR2_PLL_NCODE		0x0A00
#घोषणा   PHY_SSCCR2_TIME0		0x001C
#घोषणा   PHY_SSCCR2_TIME2_WIDTH	0x0003

#घोषणा PHY_RCR2			0x03
#घोषणा   PHY_RCR2_EMPHASE_EN		0x8000
#घोषणा   PHY_RCR2_NADJR		0x4000
#घोषणा   PHY_RCR2_CDR_SR_2		0x0100
#घोषणा   PHY_RCR2_FREQSEL_12		0x0040
#घोषणा   PHY_RCR2_CDR_SC_12P		0x0010
#घोषणा   PHY_RCR2_CALIB_LATE		0x0002
#घोषणा   PHY_RCR2_INIT_27S		0xC152
#घोषणा PHY_SSCCR3			0x03
#घोषणा   PHY_SSCCR3_STEP_IN		0x2740
#घोषणा   PHY_SSCCR3_CHECK_DELAY	0x0008
#घोषणा _PHY_ANA03			0x03
#घोषणा   _PHY_ANA03_TIMER_MAX		0x2700
#घोषणा   _PHY_ANA03_OOBS_DEB_EN	0x0040
#घोषणा   _PHY_CMU_DEBUG_EN		0x0008

#घोषणा PHY_RTCR			0x04
#घोषणा PHY_RDR				0x05
#घोषणा   PHY_RDR_RXDSEL_1_9		0x4000
#घोषणा   PHY_SSC_AUTO_PWD		0x0600
#घोषणा PHY_TCR0			0x06
#घोषणा PHY_TCR1			0x07
#घोषणा PHY_TUNE			0x08
#घोषणा   PHY_TUNE_TUNEREF_1_0		0x4000
#घोषणा   PHY_TUNE_VBGSEL_1252		0x0C00
#घोषणा   PHY_TUNE_SDBUS_33		0x0200
#घोषणा   PHY_TUNE_TUNED18		0x01C0
#घोषणा   PHY_TUNE_TUNED12		0X0020
#घोषणा   PHY_TUNE_TUNEA12		0x0004
#घोषणा   PHY_TUNE_VOLTAGE_MASK		0xFC3F
#घोषणा   PHY_TUNE_VOLTAGE_3V3		0x03C0
#घोषणा   PHY_TUNE_D18_1V8		0x0100
#घोषणा   PHY_TUNE_D18_1V7		0x0080
#घोषणा PHY_ANA08			0x08
#घोषणा   PHY_ANA08_RX_EQ_DCGAIN	0x5000
#घोषणा   PHY_ANA08_SEL_RX_EN		0x0400
#घोषणा   PHY_ANA08_RX_EQ_VAL		0x03C0
#घोषणा   PHY_ANA08_SCP			0x0020
#घोषणा   PHY_ANA08_SEL_IPI		0x0004

#घोषणा PHY_IMR				0x09
#घोषणा PHY_BPCR			0x0A
#घोषणा   PHY_BPCR_IBRXSEL		0x0400
#घोषणा   PHY_BPCR_IBTXSEL		0x0100
#घोषणा   PHY_BPCR_IB_FILTER		0x0080
#घोषणा   PHY_BPCR_CMIRROR_EN		0x0040

#घोषणा PHY_BIST			0x0B
#घोषणा PHY_RAW_L			0x0C
#घोषणा PHY_RAW_H			0x0D
#घोषणा PHY_RAW_DATA			0x0E
#घोषणा PHY_HOST_CLK_CTRL		0x0F
#घोषणा PHY_DMR				0x10
#घोषणा PHY_BACR			0x11
#घोषणा   PHY_BACR_BASIC_MASK		0xFFF3
#घोषणा PHY_IER				0x12
#घोषणा PHY_BCSR			0x13
#घोषणा PHY_BPR				0x14
#घोषणा PHY_BPNR2			0x15
#घोषणा PHY_BPNR			0x16
#घोषणा PHY_BRNR2			0x17
#घोषणा PHY_BENR			0x18
#घोषणा PHY_REV				0x19
#घोषणा   PHY_REV_RESV			0xE000
#घोषणा   PHY_REV_RXIDLE_LATCHED	0x1000
#घोषणा   PHY_REV_P1_EN			0x0800
#घोषणा   PHY_REV_RXIDLE_EN		0x0400
#घोषणा   PHY_REV_CLKREQ_TX_EN		0x0200
#घोषणा   PHY_REV_CLKREQ_RX_EN		0x0100
#घोषणा   PHY_REV_CLKREQ_DT_1_0		0x0040
#घोषणा   PHY_REV_STOP_CLKRD		0x0020
#घोषणा   PHY_REV_RX_PWST		0x0008
#घोषणा   PHY_REV_STOP_CLKWR		0x0004
#घोषणा _PHY_REV0			0x19
#घोषणा   _PHY_REV0_FILTER_OUT		0x3800
#घोषणा   _PHY_REV0_CDR_BYPASS_PFD	0x0100
#घोषणा   _PHY_REV0_CDR_RX_IDLE_BYPASS	0x0002

#घोषणा PHY_FLD0			0x1A
#घोषणा PHY_ANA1A			0x1A
#घोषणा   PHY_ANA1A_TXR_LOOPBACK	0x2000
#घोषणा   PHY_ANA1A_RXT_BIST		0x0500
#घोषणा   PHY_ANA1A_TXR_BIST		0x0040
#घोषणा   PHY_ANA1A_REV			0x0006
#घोषणा   PHY_FLD0_INIT_27S		0x2546
#घोषणा PHY_FLD1			0x1B
#घोषणा PHY_FLD2			0x1C
#घोषणा PHY_FLD3			0x1D
#घोषणा   PHY_FLD3_TIMER_4		0x0800
#घोषणा   PHY_FLD3_TIMER_6		0x0020
#घोषणा   PHY_FLD3_RXDELINK		0x0004
#घोषणा   PHY_FLD3_INIT_27S		0x0004
#घोषणा PHY_ANA1D			0x1D
#घोषणा   PHY_ANA1D_DEBUG_ADDR		0x0004
#घोषणा _PHY_FLD0			0x1D
#घोषणा   _PHY_FLD0_CLK_REQ_20C		0x8000
#घोषणा   _PHY_FLD0_RX_IDLE_EN		0x1000
#घोषणा   _PHY_FLD0_BIT_ERR_RSTN	0x0800
#घोषणा   _PHY_FLD0_BER_COUNT		0x01E0
#घोषणा   _PHY_FLD0_BER_TIMER		0x001E
#घोषणा   _PHY_FLD0_CHECK_EN		0x0001

#घोषणा PHY_FLD4			0x1E
#घोषणा   PHY_FLD4_FLDEN_SEL		0x4000
#घोषणा   PHY_FLD4_REQ_REF		0x2000
#घोषणा   PHY_FLD4_RXAMP_OFF		0x1000
#घोषणा   PHY_FLD4_REQ_ADDA		0x0800
#घोषणा   PHY_FLD4_BER_COUNT		0x00E0
#घोषणा   PHY_FLD4_BER_TIMER		0x000A
#घोषणा   PHY_FLD4_BER_CHK_EN		0x0001
#घोषणा   PHY_FLD4_INIT_27S		0x5C7F
#घोषणा PHY_DIG1E			0x1E
#घोषणा   PHY_DIG1E_REV			0x4000
#घोषणा   PHY_DIG1E_D0_X_D1		0x1000
#घोषणा   PHY_DIG1E_RX_ON_HOST		0x0800
#घोषणा   PHY_DIG1E_RCLK_REF_HOST	0x0400
#घोषणा   PHY_DIG1E_RCLK_TX_EN_KEEP	0x0040
#घोषणा   PHY_DIG1E_RCLK_TX_TERM_KEEP	0x0020
#घोषणा   PHY_DIG1E_RCLK_RX_EIDLE_ON	0x0010
#घोषणा   PHY_DIG1E_TX_TERM_KEEP	0x0008
#घोषणा   PHY_DIG1E_RX_TERM_KEEP	0x0004
#घोषणा   PHY_DIG1E_TX_EN_KEEP		0x0002
#घोषणा   PHY_DIG1E_RX_EN_KEEP		0x0001
#घोषणा PHY_DUM_REG			0x1F

#घोषणा PCR_SETTING_REG1		0x724
#घोषणा PCR_SETTING_REG2		0x814
#घोषणा PCR_SETTING_REG3		0x747

#घोषणा rtsx_pci_init_cmd(pcr)		((pcr)->ci = 0)

#घोषणा RTS5227_DEVICE_ID		0x5227
#घोषणा RTS_MAX_TIMES_FREQ_REDUCTION	8

काष्ठा rtsx_pcr;

काष्ठा pcr_handle अणु
	काष्ठा rtsx_pcr			*pcr;
पूर्ण;

काष्ठा pcr_ops अणु
	पूर्णांक (*ग_लिखो_phy)(काष्ठा rtsx_pcr *pcr, u8 addr, u16 val);
	पूर्णांक (*पढ़ो_phy)(काष्ठा rtsx_pcr *pcr, u8 addr, u16 *val);
	पूर्णांक		(*extra_init_hw)(काष्ठा rtsx_pcr *pcr);
	पूर्णांक		(*optimize_phy)(काष्ठा rtsx_pcr *pcr);
	पूर्णांक		(*turn_on_led)(काष्ठा rtsx_pcr *pcr);
	पूर्णांक		(*turn_off_led)(काष्ठा rtsx_pcr *pcr);
	पूर्णांक		(*enable_स्वतः_blink)(काष्ठा rtsx_pcr *pcr);
	पूर्णांक		(*disable_स्वतः_blink)(काष्ठा rtsx_pcr *pcr);
	पूर्णांक		(*card_घातer_on)(काष्ठा rtsx_pcr *pcr, पूर्णांक card);
	पूर्णांक		(*card_घातer_off)(काष्ठा rtsx_pcr *pcr, पूर्णांक card);
	पूर्णांक		(*चयन_output_voltage)(काष्ठा rtsx_pcr *pcr,
						u8 voltage);
	अचिन्हित पूर्णांक	(*cd_deglitch)(काष्ठा rtsx_pcr *pcr);
	पूर्णांक		(*conv_clk_and_भाग_n)(पूर्णांक clk, पूर्णांक dir);
	व्योम		(*fetch_venकरोr_settings)(काष्ठा rtsx_pcr *pcr);
	व्योम		(*क्रमce_घातer_करोwn)(काष्ठा rtsx_pcr *pcr, u8 pm_state);
	व्योम		(*stop_cmd)(काष्ठा rtsx_pcr *pcr);

	व्योम (*set_aspm)(काष्ठा rtsx_pcr *pcr, bool enable);
	व्योम (*set_l1off_cfg_sub_d0)(काष्ठा rtsx_pcr *pcr, पूर्णांक active);
	व्योम (*enable_ocp)(काष्ठा rtsx_pcr *pcr);
	व्योम (*disable_ocp)(काष्ठा rtsx_pcr *pcr);
	व्योम (*init_ocp)(काष्ठा rtsx_pcr *pcr);
	व्योम (*process_ocp)(काष्ठा rtsx_pcr *pcr);
	पूर्णांक (*get_ocpstat)(काष्ठा rtsx_pcr *pcr, u8 *val);
	व्योम (*clear_ocpstat)(काष्ठा rtsx_pcr *pcr);
पूर्ण;

क्रमागत PDEV_STAT  अणुPDEV_STAT_IDLE, PDEV_STAT_RUNपूर्ण;
क्रमागत ASPM_MODE  अणुASPM_MODE_CFG, ASPM_MODE_REGपूर्ण;

#घोषणा ASPM_L1_1_EN			BIT(0)
#घोषणा ASPM_L1_2_EN			BIT(1)
#घोषणा PM_L1_1_EN				BIT(2)
#घोषणा PM_L1_2_EN				BIT(3)
#घोषणा LTR_L1SS_PWR_GATE_EN	BIT(4)
#घोषणा L1_SNOOZE_TEST_EN		BIT(5)
#घोषणा LTR_L1SS_PWR_GATE_CHECK_CARD_EN	BIT(6)

/*
 * काष्ठा rtsx_cr_option  - card पढ़ोer option
 * @dev_flags: device flags
 * @क्रमce_clkreq_0: क्रमce घड़ी request
 * @ltr_en: enable ltr mode flag
 * @ltr_enabled: ltr mode in configure space flag
 * @ltr_active: ltr mode status
 * @ltr_active_latency: ltr mode active latency
 * @ltr_idle_latency: ltr mode idle latency
 * @ltr_l1off_latency: ltr mode l1off latency
 * @l1_snooze_delay: l1 snooze delay
 * @ltr_l1off_sspwrgate: ltr l1off sspwrgate
 * @ltr_l1off_snooze_sspwrgate: ltr l1off snooze sspwrgate
 * @ocp_en: enable ocp flag
 * @sd_400mA_ocp_thd: 400mA ocp thd
 * @sd_800mA_ocp_thd: 800mA ocp thd
 */
काष्ठा rtsx_cr_option अणु
	u32 dev_flags;
	bool क्रमce_clkreq_0;
	bool ltr_en;
	bool ltr_enabled;
	bool ltr_active;
	u32 ltr_active_latency;
	u32 ltr_idle_latency;
	u32 ltr_l1off_latency;
	u32 l1_snooze_delay;
	u8 ltr_l1off_sspwrgate;
	u8 ltr_l1off_snooze_sspwrgate;
	bool ocp_en;
	u8 sd_400mA_ocp_thd;
	u8 sd_800mA_ocp_thd;
पूर्ण;

/*
 * काष्ठा rtsx_hw_param  - card पढ़ोer hardware param
 * @पूर्णांकerrupt_en: indicate which पूर्णांकerrutp enable
 * @ocp_glitch: ocp glitch समय
 */
काष्ठा rtsx_hw_param अणु
	u32 पूर्णांकerrupt_en;
	u8 ocp_glitch;
पूर्ण;

#घोषणा rtsx_set_dev_flag(cr, flag) \
	((cr)->option.dev_flags |= (flag))
#घोषणा rtsx_clear_dev_flag(cr, flag) \
	((cr)->option.dev_flags &= ~(flag))
#घोषणा rtsx_check_dev_flag(cr, flag) \
	((cr)->option.dev_flags & (flag))

काष्ठा rtsx_pcr अणु
	काष्ठा pci_dev			*pci;
	अचिन्हित पूर्णांक			id;
	काष्ठा rtsx_cr_option	option;
	काष्ठा rtsx_hw_param hw_param;

	/* pci resources */
	अचिन्हित दीर्घ			addr;
	व्योम __iomem			*remap_addr;
	पूर्णांक				irq;

	/* host reserved buffer */
	व्योम				*rtsx_resv_buf;
	dma_addr_t			rtsx_resv_buf_addr;

	व्योम				*host_cmds_ptr;
	dma_addr_t			host_cmds_addr;
	पूर्णांक				ci;

	व्योम				*host_sg_tbl_ptr;
	dma_addr_t			host_sg_tbl_addr;
	पूर्णांक				sgi;

	u32				bier;
	अक्षर				trans_result;

	अचिन्हित पूर्णांक			card_inserted;
	अचिन्हित पूर्णांक			card_हटाओd;
	अचिन्हित पूर्णांक			card_exist;

	काष्ठा delayed_work		carddet_work;
	काष्ठा delayed_work		idle_work;
	काष्ठा delayed_work		rtd3_work;

	spinlock_t			lock;
	काष्ठा mutex			pcr_mutex;
	काष्ठा completion		*करोne;
	काष्ठा completion		*finish_me;

	अचिन्हित पूर्णांक			cur_घड़ी;
	bool				हटाओ_pci;
	bool				msi_en;
	bool				is_runसमय_suspended;

#घोषणा EXTRA_CAPS_SD_SDR50		(1 << 0)
#घोषणा EXTRA_CAPS_SD_SDR104		(1 << 1)
#घोषणा EXTRA_CAPS_SD_DDR50		(1 << 2)
#घोषणा EXTRA_CAPS_MMC_HSDDR		(1 << 3)
#घोषणा EXTRA_CAPS_MMC_HS200		(1 << 4)
#घोषणा EXTRA_CAPS_MMC_8BIT		(1 << 5)
#घोषणा EXTRA_CAPS_NO_MMC		(1 << 7)
#घोषणा EXTRA_CAPS_SD_EXPRESS		(1 << 8)
	u32				extra_caps;

#घोषणा IC_VER_A			0
#घोषणा IC_VER_B			1
#घोषणा IC_VER_C			2
#घोषणा IC_VER_D			3
	u8				ic_version;

	u8				sd30_drive_sel_1v8;
	u8				sd30_drive_sel_3v3;
	u8				card_drive_sel;
#घोषणा ASPM_L1_EN			0x02
	u8				aspm_en;
	क्रमागत ASPM_MODE			aspm_mode;
	bool				aspm_enabled;

#घोषणा PCR_MS_PMOS			(1 << 0)
#घोषणा PCR_REVERSE_SOCKET		(1 << 1)
	u32				flags;

	u32				tx_initial_phase;
	u32				rx_initial_phase;

	स्थिर u32			*sd_pull_ctl_enable_tbl;
	स्थिर u32			*sd_pull_ctl_disable_tbl;
	स्थिर u32			*ms_pull_ctl_enable_tbl;
	स्थिर u32			*ms_pull_ctl_disable_tbl;

	स्थिर काष्ठा pcr_ops		*ops;
	क्रमागत PDEV_STAT			state;

	u16				reg_pm_ctrl3;

	पूर्णांक				num_slots;
	काष्ठा rtsx_slot		*slots;

	u8				dma_error_count;
	u8			ocp_stat;
	u8			ocp_stat2;
	u8			rtd3_en;
पूर्ण;

#घोषणा PID_524A	0x524A
#घोषणा PID_5249	0x5249
#घोषणा PID_5250	0x5250
#घोषणा PID_525A	0x525A
#घोषणा PID_5260	0x5260
#घोषणा PID_5261	0x5261
#घोषणा PID_5228	0x5228

#घोषणा CHK_PCI_PID(pcr, pid)		((pcr)->pci->device == (pid))
#घोषणा PCI_VID(pcr)			((pcr)->pci->venकरोr)
#घोषणा PCI_PID(pcr)			((pcr)->pci->device)
#घोषणा is_version(pcr, pid, ver)				\
	(CHK_PCI_PID(pcr, pid) && (pcr)->ic_version == (ver))
#घोषणा is_version_higher_than(pcr, pid, ver)			\
	(CHK_PCI_PID(pcr, pid) && (pcr)->ic_version > (ver))
#घोषणा pcr_dbg(pcr, fmt, arg...)				\
	dev_dbg(&(pcr)->pci->dev, fmt, ##arg)

#घोषणा SDR104_PHASE(val)		((val) & 0xFF)
#घोषणा SDR50_PHASE(val)		(((val) >> 8) & 0xFF)
#घोषणा DDR50_PHASE(val)		(((val) >> 16) & 0xFF)
#घोषणा SDR104_TX_PHASE(pcr)		SDR104_PHASE((pcr)->tx_initial_phase)
#घोषणा SDR50_TX_PHASE(pcr)		SDR50_PHASE((pcr)->tx_initial_phase)
#घोषणा DDR50_TX_PHASE(pcr)		DDR50_PHASE((pcr)->tx_initial_phase)
#घोषणा SDR104_RX_PHASE(pcr)		SDR104_PHASE((pcr)->rx_initial_phase)
#घोषणा SDR50_RX_PHASE(pcr)		SDR50_PHASE((pcr)->rx_initial_phase)
#घोषणा DDR50_RX_PHASE(pcr)		DDR50_PHASE((pcr)->rx_initial_phase)
#घोषणा SET_CLOCK_PHASE(sdr104, sdr50, ddr50)	\
				(((ddr50) << 16) | ((sdr50) << 8) | (sdr104))

व्योम rtsx_pci_start_run(काष्ठा rtsx_pcr *pcr);
पूर्णांक rtsx_pci_ग_लिखो_रेजिस्टर(काष्ठा rtsx_pcr *pcr, u16 addr, u8 mask, u8 data);
पूर्णांक rtsx_pci_पढ़ो_रेजिस्टर(काष्ठा rtsx_pcr *pcr, u16 addr, u8 *data);
पूर्णांक rtsx_pci_ग_लिखो_phy_रेजिस्टर(काष्ठा rtsx_pcr *pcr, u8 addr, u16 val);
पूर्णांक rtsx_pci_पढ़ो_phy_रेजिस्टर(काष्ठा rtsx_pcr *pcr, u8 addr, u16 *val);
व्योम rtsx_pci_stop_cmd(काष्ठा rtsx_pcr *pcr);
व्योम rtsx_pci_add_cmd(काष्ठा rtsx_pcr *pcr,
		u8 cmd_type, u16 reg_addr, u8 mask, u8 data);
व्योम rtsx_pci_send_cmd_no_रुको(काष्ठा rtsx_pcr *pcr);
पूर्णांक rtsx_pci_send_cmd(काष्ठा rtsx_pcr *pcr, पूर्णांक समयout);
पूर्णांक rtsx_pci_transfer_data(काष्ठा rtsx_pcr *pcr, काष्ठा scatterlist *sglist,
		पूर्णांक num_sg, bool पढ़ो, पूर्णांक समयout);
पूर्णांक rtsx_pci_dma_map_sg(काष्ठा rtsx_pcr *pcr, काष्ठा scatterlist *sglist,
		पूर्णांक num_sg, bool पढ़ो);
व्योम rtsx_pci_dma_unmap_sg(काष्ठा rtsx_pcr *pcr, काष्ठा scatterlist *sglist,
		पूर्णांक num_sg, bool पढ़ो);
पूर्णांक rtsx_pci_dma_transfer(काष्ठा rtsx_pcr *pcr, काष्ठा scatterlist *sglist,
		पूर्णांक count, bool पढ़ो, पूर्णांक समयout);
पूर्णांक rtsx_pci_पढ़ो_ppbuf(काष्ठा rtsx_pcr *pcr, u8 *buf, पूर्णांक buf_len);
पूर्णांक rtsx_pci_ग_लिखो_ppbuf(काष्ठा rtsx_pcr *pcr, u8 *buf, पूर्णांक buf_len);
पूर्णांक rtsx_pci_card_pull_ctl_enable(काष्ठा rtsx_pcr *pcr, पूर्णांक card);
पूर्णांक rtsx_pci_card_pull_ctl_disable(काष्ठा rtsx_pcr *pcr, पूर्णांक card);
पूर्णांक rtsx_pci_चयन_घड़ी(काष्ठा rtsx_pcr *pcr, अचिन्हित पूर्णांक card_घड़ी,
		u8 ssc_depth, bool initial_mode, bool द्विगुन_clk, bool vpclk);
पूर्णांक rtsx_pci_card_घातer_on(काष्ठा rtsx_pcr *pcr, पूर्णांक card);
पूर्णांक rtsx_pci_card_घातer_off(काष्ठा rtsx_pcr *pcr, पूर्णांक card);
पूर्णांक rtsx_pci_card_exclusive_check(काष्ठा rtsx_pcr *pcr, पूर्णांक card);
पूर्णांक rtsx_pci_चयन_output_voltage(काष्ठा rtsx_pcr *pcr, u8 voltage);
अचिन्हित पूर्णांक rtsx_pci_card_exist(काष्ठा rtsx_pcr *pcr);
व्योम rtsx_pci_complete_unfinished_transfer(काष्ठा rtsx_pcr *pcr);

अटल अंतरभूत u8 *rtsx_pci_get_cmd_data(काष्ठा rtsx_pcr *pcr)
अणु
	वापस (u8 *)(pcr->host_cmds_ptr);
पूर्ण

अटल अंतरभूत व्योम rtsx_pci_ग_लिखो_be32(काष्ठा rtsx_pcr *pcr, u16 reg, u32 val)
अणु
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, reg,     0xFF, val >> 24);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, reg + 1, 0xFF, val >> 16);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, reg + 2, 0xFF, val >> 8);
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, reg + 3, 0xFF, val);
पूर्ण

अटल अंतरभूत पूर्णांक rtsx_pci_update_phy(काष्ठा rtsx_pcr *pcr, u8 addr,
	u16 mask, u16 append)
अणु
	पूर्णांक err;
	u16 val;

	err = rtsx_pci_पढ़ो_phy_रेजिस्टर(pcr, addr, &val);
	अगर (err < 0)
		वापस err;

	वापस rtsx_pci_ग_लिखो_phy_रेजिस्टर(pcr, addr, (val & mask) | append);
पूर्ण

#पूर्ण_अगर
