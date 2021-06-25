<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Driver क्रम Realtek PCI-Express card पढ़ोer
 *
 * Copyright(c) 2009-2013 Realtek Semiconductor Corp. All rights reserved.
 *
 * Author:
 *   Wei WANG (wei_wang@realsil.com.cn)
 *   Micky Ching (micky_ching@realsil.com.cn)
 */

#अगर_अघोषित __REALTEK_RTSX_CARD_H
#घोषणा __REALTEK_RTSX_CARD_H

#समावेश "rtsx.h"
#समावेश "rtsx_chip.h"
#समावेश "rtsx_transport.h"
#समावेश "sd.h"

#घोषणा SSC_POWER_DOWN		0x01
#घोषणा SD_OC_POWER_DOWN	0x02
#घोषणा MS_OC_POWER_DOWN	0x04
#घोषणा ALL_POWER_DOWN		0x07
#घोषणा OC_POWER_DOWN		0x06

#घोषणा PMOS_STRG_MASK		0x10
#घोषणा PMOS_STRG_800mA		0x10
#घोषणा PMOS_STRG_400mA		0x00

#घोषणा POWER_OFF		0x03
#घोषणा PARTIAL_POWER_ON	0x01
#घोषणा POWER_ON		0x00

#घोषणा MS_POWER_OFF		0x0C
#घोषणा MS_PARTIAL_POWER_ON	0x04
#घोषणा MS_POWER_ON		0x00
#घोषणा MS_POWER_MASK		0x0C

#घोषणा SD_POWER_OFF		0x03
#घोषणा SD_PARTIAL_POWER_ON	0x01
#घोषणा SD_POWER_ON		0x00
#घोषणा SD_POWER_MASK		0x03

#घोषणा XD_OUTPUT_EN		0x02
#घोषणा SD_OUTPUT_EN		0x04
#घोषणा MS_OUTPUT_EN		0x08
#घोषणा SPI_OUTPUT_EN		0x10

#घोषणा CLK_LOW_FREQ		0x01

#घोषणा CLK_DIV_1		0x01
#घोषणा CLK_DIV_2		0x02
#घोषणा CLK_DIV_4		0x03
#घोषणा CLK_DIV_8		0x04

#घोषणा SSC_80			0
#घोषणा SSC_100			1
#घोषणा SSC_120			2
#घोषणा SSC_150			3
#घोषणा SSC_200			4

#घोषणा XD_CLK_EN		0x02
#घोषणा SD_CLK_EN		0x04
#घोषणा MS_CLK_EN		0x08
#घोषणा SPI_CLK_EN		0x10

#घोषणा XD_MOD_SEL		1
#घोषणा SD_MOD_SEL		2
#घोषणा MS_MOD_SEL		3
#घोषणा SPI_MOD_SEL		4

#घोषणा CHANGE_CLK		0x01

#घोषणा	SD_CRC7_ERR			0x80
#घोषणा	SD_CRC16_ERR			0x40
#घोषणा	SD_CRC_WRITE_ERR		0x20
#घोषणा	SD_CRC_WRITE_ERR_MASK		0x1C
#घोषणा	GET_CRC_TIME_OUT		0x02
#घोषणा	SD_TUNING_COMPARE_ERR		0x01

#घोषणा	SD_RSP_80CLK_TIMEOUT		0x01

#घोषणा	SD_CLK_TOGGLE_EN		0x80
#घोषणा	SD_CLK_FORCE_STOP		0x40
#घोषणा	SD_DAT3_STATUS			0x10
#घोषणा	SD_DAT2_STATUS			0x08
#घोषणा	SD_DAT1_STATUS			0x04
#घोषणा	SD_DAT0_STATUS			0x02
#घोषणा	SD_CMD_STATUS			0x01

#घोषणा	SD_IO_USING_1V8			0x80
#घोषणा	SD_IO_USING_3V3			0x7F
#घोषणा	TYPE_A_DRIVING			0x00
#घोषणा	TYPE_B_DRIVING			0x01
#घोषणा	TYPE_C_DRIVING			0x02
#घोषणा	TYPE_D_DRIVING			0x03

#घोषणा	DDR_FIX_RX_DAT			0x00
#घोषणा	DDR_VAR_RX_DAT			0x80
#घोषणा	DDR_FIX_RX_DAT_EDGE		0x00
#घोषणा	DDR_FIX_RX_DAT_14_DELAY		0x40
#घोषणा	DDR_FIX_RX_CMD			0x00
#घोषणा	DDR_VAR_RX_CMD			0x20
#घोषणा	DDR_FIX_RX_CMD_POS_EDGE		0x00
#घोषणा	DDR_FIX_RX_CMD_14_DELAY		0x10
#घोषणा	SD20_RX_POS_EDGE		0x00
#घोषणा	SD20_RX_14_DELAY		0x08
#घोषणा SD20_RX_SEL_MASK		0x08

#घोषणा	DDR_FIX_TX_CMD_DAT		0x00
#घोषणा	DDR_VAR_TX_CMD_DAT		0x80
#घोषणा	DDR_FIX_TX_DAT_14_TSU		0x00
#घोषणा	DDR_FIX_TX_DAT_12_TSU		0x40
#घोषणा	DDR_FIX_TX_CMD_NEG_EDGE		0x00
#घोषणा	DDR_FIX_TX_CMD_14_AHEAD		0x20
#घोषणा	SD20_TX_NEG_EDGE		0x00
#घोषणा	SD20_TX_14_AHEAD		0x10
#घोषणा SD20_TX_SEL_MASK		0x10
#घोषणा	DDR_VAR_SDCLK_POL_SWAP		0x01

#घोषणा	SD_TRANSFER_START		0x80
#घोषणा	SD_TRANSFER_END			0x40
#घोषणा SD_STAT_IDLE			0x20
#घोषणा	SD_TRANSFER_ERR			0x10
#घोषणा	SD_TM_NORMAL_WRITE		0x00
#घोषणा	SD_TM_AUTO_WRITE_3		0x01
#घोषणा	SD_TM_AUTO_WRITE_4		0x02
#घोषणा	SD_TM_AUTO_READ_3		0x05
#घोषणा	SD_TM_AUTO_READ_4		0x06
#घोषणा	SD_TM_CMD_RSP			0x08
#घोषणा	SD_TM_AUTO_WRITE_1		0x09
#घोषणा	SD_TM_AUTO_WRITE_2		0x0A
#घोषणा	SD_TM_NORMAL_READ		0x0C
#घोषणा	SD_TM_AUTO_READ_1		0x0D
#घोषणा	SD_TM_AUTO_READ_2		0x0E
#घोषणा	SD_TM_AUTO_TUNING		0x0F

#घोषणा PHASE_CHANGE			0x80
#घोषणा PHASE_NOT_RESET			0x40

#घोषणा DCMPS_CHANGE			0x80
#घोषणा DCMPS_CHANGE_DONE		0x40
#घोषणा DCMPS_ERROR			0x20
#घोषणा DCMPS_CURRENT_PHASE		0x1F

#घोषणा SD_CLK_DIVIDE_0			0x00
#घोषणा	SD_CLK_DIVIDE_256		0xC0
#घोषणा	SD_CLK_DIVIDE_128		0x80
#घोषणा	SD_BUS_WIDTH_1			0x00
#घोषणा	SD_BUS_WIDTH_4			0x01
#घोषणा	SD_BUS_WIDTH_8			0x02
#घोषणा	SD_ASYNC_FIFO_NOT_RST		0x10
#घोषणा	SD_20_MODE			0x00
#घोषणा	SD_DDR_MODE			0x04
#घोषणा	SD_30_MODE			0x08

#घोषणा SD_CLK_DIVIDE_MASK		0xC0

#घोषणा SD_CMD_IDLE			0x80

#घोषणा SD_DATA_IDLE			0x80

#घोषणा DCM_RESET			0x08
#घोषणा DCM_LOCKED			0x04
#घोषणा DCM_208M			0x00
#घोषणा DCM_TX				0x01
#घोषणा DCM_RX				0x02

#घोषणा DRP_START			0x80
#घोषणा DRP_DONE			0x40

#घोषणा DRP_WRITE			0x80
#घोषणा DRP_READ			0x00
#घोषणा DCM_WRITE_ADDRESS_50		0x50
#घोषणा DCM_WRITE_ADDRESS_51		0x51
#घोषणा DCM_READ_ADDRESS_00		0x00
#घोषणा DCM_READ_ADDRESS_51		0x51

#घोषणा	SD_CALCULATE_CRC7		0x00
#घोषणा	SD_NO_CALCULATE_CRC7		0x80
#घोषणा	SD_CHECK_CRC16			0x00
#घोषणा	SD_NO_CHECK_CRC16		0x40
#घोषणा SD_NO_CHECK_WAIT_CRC_TO		0x20
#घोषणा	SD_WAIT_BUSY_END		0x08
#घोषणा	SD_NO_WAIT_BUSY_END		0x00
#घोषणा	SD_CHECK_CRC7			0x00
#घोषणा	SD_NO_CHECK_CRC7		0x04
#घोषणा	SD_RSP_LEN_0			0x00
#घोषणा	SD_RSP_LEN_6			0x01
#घोषणा	SD_RSP_LEN_17			0x02
#घोषणा	SD_RSP_TYPE_R0			0x04
#घोषणा	SD_RSP_TYPE_R1			0x01
#घोषणा	SD_RSP_TYPE_R1b			0x09
#घोषणा	SD_RSP_TYPE_R2			0x02
#घोषणा	SD_RSP_TYPE_R3			0x05
#घोषणा	SD_RSP_TYPE_R4			0x05
#घोषणा	SD_RSP_TYPE_R5			0x01
#घोषणा	SD_RSP_TYPE_R6			0x01
#घोषणा	SD_RSP_TYPE_R7			0x01

#घोषणा	SD_RSP_80CLK_TIMEOUT_EN		0x01

#घोषणा	SAMPLE_TIME_RISING		0x00
#घोषणा	SAMPLE_TIME_FALLING		0x80
#घोषणा	PUSH_TIME_DEFAULT		0x00
#घोषणा	PUSH_TIME_ODD			0x40
#घोषणा	NO_EXTEND_TOGGLE		0x00
#घोषणा	EXTEND_TOGGLE_CHK		0x20
#घोषणा	MS_BUS_WIDTH_1			0x00
#घोषणा	MS_BUS_WIDTH_4			0x10
#घोषणा	MS_BUS_WIDTH_8			0x18
#घोषणा	MS_2K_SECTOR_MODE		0x04
#घोषणा	MS_512_SECTOR_MODE		0x00
#घोषणा	MS_TOGGLE_TIMEOUT_EN		0x00
#घोषणा	MS_TOGGLE_TIMEOUT_DISEN		0x01
#घोषणा MS_NO_CHECK_INT			0x02

#घोषणा	WAIT_INT			0x80
#घोषणा	NO_WAIT_INT			0x00
#घोषणा	NO_AUTO_READ_INT_REG		0x00
#घोषणा	AUTO_READ_INT_REG		0x40
#घोषणा	MS_CRC16_ERR			0x20
#घोषणा	MS_RDY_TIMEOUT			0x10
#घोषणा	MS_INT_CMDNK			0x08
#घोषणा	MS_INT_BREQ			0x04
#घोषणा	MS_INT_ERR			0x02
#घोषणा	MS_INT_CED			0x01

#घोषणा	MS_TRANSFER_START		0x80
#घोषणा	MS_TRANSFER_END			0x40
#घोषणा	MS_TRANSFER_ERR			0x20
#घोषणा	MS_BS_STATE			0x10
#घोषणा	MS_TM_READ_BYTES		0x00
#घोषणा	MS_TM_NORMAL_READ		0x01
#घोषणा	MS_TM_WRITE_BYTES		0x04
#घोषणा	MS_TM_NORMAL_WRITE		0x05
#घोषणा	MS_TM_AUTO_READ			0x08
#घोषणा	MS_TM_AUTO_WRITE		0x0C

#घोषणा CARD_SHARE_MASK			0x0F
#घोषणा CARD_SHARE_MULTI_LUN		0x00
#घोषणा	CARD_SHARE_NORMAL		0x00
#घोषणा	CARD_SHARE_48_XD		0x02
#घोषणा	CARD_SHARE_48_SD		0x04
#घोषणा	CARD_SHARE_48_MS		0x08
#घोषणा CARD_SHARE_BAROSSA_XD		0x00
#घोषणा CARD_SHARE_BAROSSA_SD		0x01
#घोषणा CARD_SHARE_BAROSSA_MS		0x02

#घोषणा	MS_DRIVE_8			0x00
#घोषणा	MS_DRIVE_4			0x40
#घोषणा	MS_DRIVE_12			0x80
#घोषणा	SD_DRIVE_8			0x00
#घोषणा	SD_DRIVE_4			0x10
#घोषणा	SD_DRIVE_12			0x20
#घोषणा	XD_DRIVE_8			0x00
#घोषणा	XD_DRIVE_4			0x04
#घोषणा	XD_DRIVE_12			0x08

#घोषणा SPI_STOP		0x01
#घोषणा XD_STOP			0x02
#घोषणा SD_STOP			0x04
#घोषणा MS_STOP			0x08
#घोषणा SPI_CLR_ERR		0x10
#घोषणा XD_CLR_ERR		0x20
#घोषणा SD_CLR_ERR		0x40
#घोषणा MS_CLR_ERR		0x80

#घोषणा CRC_FIX_CLK		(0x00 << 0)
#घोषणा CRC_VAR_CLK0		(0x01 << 0)
#घोषणा CRC_VAR_CLK1		(0x02 << 0)
#घोषणा SD30_FIX_CLK		(0x00 << 2)
#घोषणा SD30_VAR_CLK0		(0x01 << 2)
#घोषणा SD30_VAR_CLK1		(0x02 << 2)
#घोषणा SAMPLE_FIX_CLK		(0x00 << 4)
#घोषणा SAMPLE_VAR_CLK0		(0x01 << 4)
#घोषणा SAMPLE_VAR_CLK1		(0x02 << 4)

#घोषणा SDIO_VER_20		0x80
#घोषणा SDIO_VER_10		0x00
#घोषणा SDIO_VER_CHG		0x40
#घोषणा SDIO_BUS_AUTO_SWITCH	0x10

#घोषणा PINGPONG_BUFFER		0x01
#घोषणा RING_BUFFER		0x00

#घोषणा RB_FLUSH		0x80

#घोषणा DMA_DONE_INT_EN			0x80
#घोषणा SUSPEND_INT_EN			0x40
#घोषणा LINK_RDY_INT_EN			0x20
#घोषणा LINK_DOWN_INT_EN		0x10

#घोषणा DMA_DONE_INT			0x80
#घोषणा SUSPEND_INT			0x40
#घोषणा LINK_RDY_INT			0x20
#घोषणा LINK_DOWN_INT			0x10

#घोषणा MRD_ERR_INT_EN			0x40
#घोषणा MWR_ERR_INT_EN			0x20
#घोषणा SCSI_CMD_INT_EN			0x10
#घोषणा TLP_RCV_INT_EN			0x08
#घोषणा TLP_TRSMT_INT_EN		0x04
#घोषणा MRD_COMPLETE_INT_EN		0x02
#घोषणा MWR_COMPLETE_INT_EN		0x01

#घोषणा MRD_ERR_INT			0x40
#घोषणा MWR_ERR_INT			0x20
#घोषणा SCSI_CMD_INT			0x10
#घोषणा TLP_RX_INT			0x08
#घोषणा TLP_TX_INT			0x04
#घोषणा MRD_COMPLETE_INT		0x02
#घोषणा MWR_COMPLETE_INT		0x01

#घोषणा MSG_RX_INT_EN			0x08
#घोषणा MRD_RX_INT_EN			0x04
#घोषणा MWR_RX_INT_EN			0x02
#घोषणा CPLD_RX_INT_EN			0x01

#घोषणा MSG_RX_INT			0x08
#घोषणा MRD_RX_INT			0x04
#घोषणा MWR_RX_INT			0x02
#घोषणा CPLD_RX_INT			0x01

#घोषणा MSG_TX_INT_EN			0x08
#घोषणा MRD_TX_INT_EN			0x04
#घोषणा MWR_TX_INT_EN			0x02
#घोषणा CPLD_TX_INT_EN			0x01

#घोषणा MSG_TX_INT			0x08
#घोषणा MRD_TX_INT			0x04
#घोषणा MWR_TX_INT			0x02
#घोषणा CPLD_TX_INT			0x01

#घोषणा DMA_RST				0x80
#घोषणा DMA_BUSY			0x04
#घोषणा DMA_सूची_TO_CARD			0x00
#घोषणा DMA_सूची_FROM_CARD		0x02
#घोषणा DMA_EN				0x01
#घोषणा DMA_128				(0 << 4)
#घोषणा DMA_256				(1 << 4)
#घोषणा DMA_512				(2 << 4)
#घोषणा DMA_1024			(3 << 4)
#घोषणा DMA_PACK_SIZE_MASK		0x30

#घोषणा	XD_PWR_OFF_DELAY0		0x00
#घोषणा	XD_PWR_OFF_DELAY1		0x02
#घोषणा	XD_PWR_OFF_DELAY2		0x04
#घोषणा	XD_PWR_OFF_DELAY3		0x06
#घोषणा	XD_AUTO_PWR_OFF_EN		0xF7
#घोषणा	XD_NO_AUTO_PWR_OFF		0x08

#घोषणा	XD_TIME_RWN_1			0x00
#घोषणा	XD_TIME_RWN_STEP		0x20
#घोषणा	XD_TIME_RW_1			0x00
#घोषणा	XD_TIME_RW_STEP			0x04
#घोषणा	XD_TIME_SETUP_1			0x00
#घोषणा	XD_TIME_SETUP_STEP		0x01

#घोषणा	XD_ECC2_UNCORRECTABLE		0x80
#घोषणा	XD_ECC2_ERROR			0x40
#घोषणा	XD_ECC1_UNCORRECTABLE		0x20
#घोषणा	XD_ECC1_ERROR			0x10
#घोषणा	XD_RDY				0x04
#घोषणा	XD_CE_EN			0xFD
#घोषणा	XD_CE_DISEN			0x02
#घोषणा	XD_WP_EN			0xFE
#घोषणा	XD_WP_DISEN			0x01

#घोषणा	XD_TRANSFER_START		0x80
#घोषणा	XD_TRANSFER_END			0x40
#घोषणा	XD_PPB_EMPTY			0x20
#घोषणा	XD_RESET			0x00
#घोषणा	XD_ERASE			0x01
#घोषणा	XD_READ_STATUS			0x02
#घोषणा	XD_READ_ID			0x03
#घोषणा	XD_READ_REDUNDANT		0x04
#घोषणा	XD_READ_PAGES			0x05
#घोषणा	XD_SET_CMD			0x06
#घोषणा	XD_NORMAL_READ			0x07
#घोषणा	XD_WRITE_PAGES			0x08
#घोषणा	XD_NORMAL_WRITE			0x09
#घोषणा	XD_WRITE_REDUNDANT		0x0A
#घोषणा	XD_SET_ADDR			0x0B

#घोषणा	XD_PPB_TO_SIE			0x80
#घोषणा	XD_TO_PPB_ONLY			0x00
#घोषणा	XD_BA_TRANSFORM			0x40
#घोषणा	XD_BA_NO_TRANSFORM		0x00
#घोषणा	XD_NO_CALC_ECC			0x20
#घोषणा	XD_CALC_ECC			0x00
#घोषणा	XD_IGNORE_ECC			0x10
#घोषणा	XD_CHECK_ECC			0x00
#घोषणा	XD_सूचीECT_TO_RB			0x08
#घोषणा	XD_ADDR_LENGTH_0		0x00
#घोषणा	XD_ADDR_LENGTH_1		0x01
#घोषणा	XD_ADDR_LENGTH_2		0x02
#घोषणा	XD_ADDR_LENGTH_3		0x03
#घोषणा	XD_ADDR_LENGTH_4		0x04

#घोषणा	XD_GPG				0xFF
#घोषणा	XD_BPG				0x00

#घोषणा	XD_GBLK				0xFF
#घोषणा	XD_LATER_BBLK			0xF0

#घोषणा	XD_ECC2_ALL1			0x80
#घोषणा	XD_ECC1_ALL1			0x40
#घोषणा	XD_BA2_ALL0			0x20
#घोषणा	XD_BA1_ALL0			0x10
#घोषणा	XD_BA1_BA2_EQL			0x04
#घोषणा	XD_BA2_VALID			0x02
#घोषणा	XD_BA1_VALID			0x01

#घोषणा	XD_PGSTS_ZEROBIT_OVER4		0x00
#घोषणा	XD_PGSTS_NOT_FF			0x02
#घोषणा	XD_AUTO_CHK_DATA_STATUS		0x01

#घोषणा	RSTB_MODE_DETECT		0x80
#घोषणा	MODE_OUT_VLD			0x40
#घोषणा	MODE_OUT_0_NONE			0x00
#घोषणा	MODE_OUT_10_NONE		0x04
#घोषणा	MODE_OUT_10_47			0x05
#घोषणा	MODE_OUT_10_180			0x06
#घोषणा	MODE_OUT_10_680			0x07
#घोषणा	MODE_OUT_16_NONE		0x08
#घोषणा	MODE_OUT_16_47			0x09
#घोषणा	MODE_OUT_16_180			0x0A
#घोषणा	MODE_OUT_16_680			0x0B
#घोषणा	MODE_OUT_NONE_NONE		0x0C
#घोषणा	MODE_OUT_NONE_47		0x0D
#घोषणा	MODE_OUT_NONE_180		0x0E
#घोषणा	MODE_OUT_NONE_680		0x0F

#घोषणा	CARD_OC_INT_EN			0x20
#घोषणा	CARD_DETECT_EN			0x08

#घोषणा MS_DETECT_EN			0x80
#घोषणा MS_OCP_INT_EN			0x40
#घोषणा MS_OCP_INT_CLR			0x20
#घोषणा MS_OC_CLR			0x10
#घोषणा SD_DETECT_EN			0x08
#घोषणा SD_OCP_INT_EN			0x04
#घोषणा SD_OCP_INT_CLR			0x02
#घोषणा SD_OC_CLR			0x01

#घोषणा	CARD_OCP_DETECT			0x80
#घोषणा	CARD_OC_NOW			0x08
#घोषणा	CARD_OC_EVER			0x04

#घोषणा MS_OCP_DETECT			0x80
#घोषणा MS_OC_NOW			0x40
#घोषणा MS_OC_EVER			0x20
#घोषणा SD_OCP_DETECT			0x08
#घोषणा SD_OC_NOW			0x04
#घोषणा SD_OC_EVER			0x02

#घोषणा	CARD_OC_INT_CLR			0x08
#घोषणा	CARD_OC_CLR			0x02

#घोषणा SD_OCP_GLITCH_MASK		0x07
#घोषणा SD_OCP_GLITCH_6_4		0x00
#घोषणा SD_OCP_GLITCH_64		0x01
#घोषणा SD_OCP_GLITCH_640		0x02
#घोषणा SD_OCP_GLITCH_1000		0x03
#घोषणा SD_OCP_GLITCH_2000		0x04
#घोषणा SD_OCP_GLITCH_4000		0x05
#घोषणा SD_OCP_GLITCH_8000		0x06
#घोषणा SD_OCP_GLITCH_10000		0x07

#घोषणा MS_OCP_GLITCH_MASK		0x70
#घोषणा MS_OCP_GLITCH_6_4		(0x00 << 4)
#घोषणा MS_OCP_GLITCH_64		(0x01 << 4)
#घोषणा MS_OCP_GLITCH_640		(0x02 << 4)
#घोषणा MS_OCP_GLITCH_1000		(0x03 << 4)
#घोषणा MS_OCP_GLITCH_2000		(0x04 << 4)
#घोषणा MS_OCP_GLITCH_4000		(0x05 << 4)
#घोषणा MS_OCP_GLITCH_8000		(0x06 << 4)
#घोषणा MS_OCP_GLITCH_10000		(0x07 << 4)

#घोषणा OCP_TIME_60			0x00
#घोषणा OCP_TIME_100			(0x01 << 3)
#घोषणा OCP_TIME_200			(0x02 << 3)
#घोषणा OCP_TIME_400			(0x03 << 3)
#घोषणा OCP_TIME_600			(0x04 << 3)
#घोषणा OCP_TIME_800			(0x05 << 3)
#घोषणा OCP_TIME_1100			(0x06 << 3)
#घोषणा OCP_TIME_MASK			0x38

#घोषणा MS_OCP_TIME_60			0x00
#घोषणा MS_OCP_TIME_100			(0x01 << 4)
#घोषणा MS_OCP_TIME_200			(0x02 << 4)
#घोषणा MS_OCP_TIME_400			(0x03 << 4)
#घोषणा MS_OCP_TIME_600			(0x04 << 4)
#घोषणा MS_OCP_TIME_800			(0x05 << 4)
#घोषणा MS_OCP_TIME_1100		(0x06 << 4)
#घोषणा MS_OCP_TIME_MASK		0x70

#घोषणा SD_OCP_TIME_60			0x00
#घोषणा SD_OCP_TIME_100			0x01
#घोषणा SD_OCP_TIME_200			0x02
#घोषणा SD_OCP_TIME_400			0x03
#घोषणा SD_OCP_TIME_600			0x04
#घोषणा SD_OCP_TIME_800			0x05
#घोषणा SD_OCP_TIME_1100		0x06
#घोषणा SD_OCP_TIME_MASK		0x07

#घोषणा OCP_THD_315_417			0x00
#घोषणा OCP_THD_283_783			(0x01 << 6)
#घोषणा OCP_THD_244_946			(0x02 << 6)
#घोषणा OCP_THD_191_1080		(0x03 << 6)
#घोषणा OCP_THD_MASK			0xC0

#घोषणा MS_OCP_THD_450			0x00
#घोषणा MS_OCP_THD_550			(0x01 << 4)
#घोषणा MS_OCP_THD_650			(0x02 << 4)
#घोषणा MS_OCP_THD_750			(0x03 << 4)
#घोषणा MS_OCP_THD_850			(0x04 << 4)
#घोषणा MS_OCP_THD_950			(0x05 << 4)
#घोषणा MS_OCP_THD_1050			(0x06 << 4)
#घोषणा MS_OCP_THD_1150			(0x07 << 4)
#घोषणा MS_OCP_THD_MASK			0x70

#घोषणा SD_OCP_THD_450			0x00
#घोषणा SD_OCP_THD_550			0x01
#घोषणा SD_OCP_THD_650			0x02
#घोषणा SD_OCP_THD_750			0x03
#घोषणा SD_OCP_THD_850			0x04
#घोषणा SD_OCP_THD_950			0x05
#घोषणा SD_OCP_THD_1050			0x06
#घोषणा SD_OCP_THD_1150			0x07
#घोषणा SD_OCP_THD_MASK			0x07

#घोषणा FPGA_MS_PULL_CTL_EN		0xEF
#घोषणा FPGA_SD_PULL_CTL_EN		0xF7
#घोषणा FPGA_XD_PULL_CTL_EN1		0xFE
#घोषणा FPGA_XD_PULL_CTL_EN2		0xFD
#घोषणा FPGA_XD_PULL_CTL_EN3		0xFB

#घोषणा FPGA_MS_PULL_CTL_BIT		0x10
#घोषणा FPGA_SD_PULL_CTL_BIT		0x08

#घोषणा BLINK_EN			0x08
#घोषणा LED_GPIO0			(0 << 4)
#घोषणा LED_GPIO1			(1 << 4)
#घोषणा LED_GPIO2			(2 << 4)

#घोषणा SDIO_BUS_CTRL		0x01
#घोषणा SDIO_CD_CTRL		0x02

#घोषणा SSC_RSTB		0x80
#घोषणा SSC_8X_EN		0x40
#घोषणा SSC_FIX_FRAC		0x20
#घोषणा SSC_SEL_1M		0x00
#घोषणा SSC_SEL_2M		0x08
#घोषणा SSC_SEL_4M		0x10
#घोषणा SSC_SEL_8M		0x18

#घोषणा SSC_DEPTH_MASK		0x07
#घोषणा SSC_DEPTH_DISALBE	0x00
#घोषणा SSC_DEPTH_4M		0x01
#घोषणा SSC_DEPTH_2M		0x02
#घोषणा SSC_DEPTH_1M		0x03
#घोषणा SSC_DEPTH_512K		0x04
#घोषणा SSC_DEPTH_256K		0x05
#घोषणा SSC_DEPTH_128K		0x06
#घोषणा SSC_DEPTH_64K		0x07

#घोषणा XD_D3_NP		0x00
#घोषणा XD_D3_PD		(0x01 << 6)
#घोषणा XD_D3_PU		(0x02 << 6)
#घोषणा XD_D2_NP		0x00
#घोषणा XD_D2_PD		(0x01 << 4)
#घोषणा XD_D2_PU		(0x02 << 4)
#घोषणा XD_D1_NP		0x00
#घोषणा XD_D1_PD		(0x01 << 2)
#घोषणा XD_D1_PU		(0x02 << 2)
#घोषणा XD_D0_NP		0x00
#घोषणा XD_D0_PD		0x01
#घोषणा XD_D0_PU		0x02

#घोषणा SD_D7_NP		0x00
#घोषणा SD_D7_PD		(0x01 << 4)
#घोषणा SD_DAT7_PU		(0x02 << 4)
#घोषणा SD_CLK_NP		0x00
#घोषणा SD_CLK_PD		(0x01 << 2)
#घोषणा SD_CLK_PU		(0x02 << 2)
#घोषणा SD_D5_NP		0x00
#घोषणा SD_D5_PD		0x01
#घोषणा SD_D5_PU		0x02

#घोषणा MS_D1_NP		0x00
#घोषणा MS_D1_PD		(0x01 << 6)
#घोषणा MS_D1_PU		(0x02 << 6)
#घोषणा MS_D2_NP		0x00
#घोषणा MS_D2_PD		(0x01 << 4)
#घोषणा MS_D2_PU		(0x02 << 4)
#घोषणा MS_CLK_NP		0x00
#घोषणा MS_CLK_PD		(0x01 << 2)
#घोषणा MS_CLK_PU		(0x02 << 2)
#घोषणा MS_D6_NP		0x00
#घोषणा MS_D6_PD		0x01
#घोषणा MS_D6_PU		0x02

#घोषणा XD_D7_NP		0x00
#घोषणा XD_D7_PD		(0x01 << 6)
#घोषणा XD_D7_PU		(0x02 << 6)
#घोषणा XD_D6_NP		0x00
#घोषणा XD_D6_PD		(0x01 << 4)
#घोषणा XD_D6_PU		(0x02 << 4)
#घोषणा XD_D5_NP		0x00
#घोषणा XD_D5_PD		(0x01 << 2)
#घोषणा XD_D5_PU		(0x02 << 2)
#घोषणा XD_D4_NP		0x00
#घोषणा XD_D4_PD		0x01
#घोषणा XD_D4_PU		0x02

#घोषणा SD_D6_NP		0x00
#घोषणा SD_D6_PD		(0x01 << 6)
#घोषणा SD_D6_PU		(0x02 << 6)
#घोषणा SD_D0_NP		0x00
#घोषणा SD_D0_PD		(0x01 << 4)
#घोषणा SD_D0_PU		(0x02 << 4)
#घोषणा SD_D1_NP		0x00
#घोषणा SD_D1_PD		0x01
#घोषणा SD_D1_PU		0x02

#घोषणा MS_D3_NP		0x00
#घोषणा MS_D3_PD		(0x01 << 6)
#घोषणा MS_D3_PU		(0x02 << 6)
#घोषणा MS_D0_NP		0x00
#घोषणा MS_D0_PD		(0x01 << 4)
#घोषणा MS_D0_PU		(0x02 << 4)
#घोषणा MS_BS_NP		0x00
#घोषणा MS_BS_PD		(0x01 << 2)
#घोषणा MS_BS_PU		(0x02 << 2)

#घोषणा XD_WP_NP		0x00
#घोषणा XD_WP_PD		(0x01 << 6)
#घोषणा XD_WP_PU		(0x02 << 6)
#घोषणा XD_CE_NP		0x00
#घोषणा XD_CE_PD		(0x01 << 3)
#घोषणा XD_CE_PU		(0x02 << 3)
#घोषणा XD_CLE_NP		0x00
#घोषणा XD_CLE_PD		(0x01 << 1)
#घोषणा XD_CLE_PU		(0x02 << 1)
#घोषणा XD_CD_PD		0x00
#घोषणा XD_CD_PU		0x01

#घोषणा SD_D4_NP		0x00
#घोषणा SD_D4_PD		(0x01 << 6)
#घोषणा SD_D4_PU		(0x02 << 6)

#घोषणा MS_D7_NP		0x00
#घोषणा MS_D7_PD		(0x01 << 6)
#घोषणा MS_D7_PU		(0x02 << 6)

#घोषणा XD_RDY_NP		0x00
#घोषणा XD_RDY_PD		(0x01 << 6)
#घोषणा XD_RDY_PU		(0x02 << 6)
#घोषणा XD_WE_NP		0x00
#घोषणा XD_WE_PD		(0x01 << 4)
#घोषणा XD_WE_PU		(0x02 << 4)
#घोषणा XD_RE_NP		0x00
#घोषणा XD_RE_PD		(0x01 << 2)
#घोषणा XD_RE_PU		(0x02 << 2)
#घोषणा XD_ALE_NP		0x00
#घोषणा XD_ALE_PD		0x01
#घोषणा XD_ALE_PU		0x02

#घोषणा SD_D3_NP		0x00
#घोषणा SD_D3_PD		(0x01 << 4)
#घोषणा SD_D3_PU		(0x02 << 4)
#घोषणा SD_D2_NP		0x00
#घोषणा SD_D2_PD		(0x01 << 2)
#घोषणा SD_D2_PU		(0x02 << 2)

#घोषणा MS_INS_PD		0x00
#घोषणा MS_INS_PU		(0x01 << 7)
#घोषणा SD_WP_NP		0x00
#घोषणा SD_WP_PD		(0x01 << 5)
#घोषणा SD_WP_PU		(0x02 << 5)
#घोषणा SD_CD_PD		0x00
#घोषणा SD_CD_PU		(0x01 << 4)
#घोषणा SD_CMD_NP		0x00
#घोषणा SD_CMD_PD		(0x01 << 2)
#घोषणा SD_CMD_PU		(0x02 << 2)

#घोषणा MS_D5_NP		0x00
#घोषणा MS_D5_PD		(0x01 << 2)
#घोषणा MS_D5_PU		(0x02 << 2)
#घोषणा MS_D4_NP		0x00
#घोषणा MS_D4_PD		0x01
#घोषणा MS_D4_PU		0x02

#घोषणा FORCE_PM_CLOCK		0x10
#घोषणा EN_CLOCK_PM		0x01

#घोषणा HOST_ENTER_S3		0x02
#घोषणा HOST_ENTER_S1		0x01

#घोषणा AUX_PWR_DETECTED	0x01

#घोषणा PHY_DEBUG_MODE		0x01

#घोषणा SPI_COMMAND_BIT_8	0xE0
#घोषणा SPI_ADDRESS_BIT_24	0x17
#घोषणा SPI_ADDRESS_BIT_32	0x1F

#घोषणा SPI_TRANSFER0_START	0x80
#घोषणा SPI_TRANSFER0_END	0x40
#घोषणा SPI_C_MODE0		0x00
#घोषणा SPI_CA_MODE0		0x01
#घोषणा SPI_CDO_MODE0		0x02
#घोषणा SPI_CDI_MODE0		0x03
#घोषणा SPI_CADO_MODE0		0x04
#घोषणा SPI_CADI_MODE0		0x05
#घोषणा SPI_POLLING_MODE0	0x06

#घोषणा SPI_TRANSFER1_START	0x80
#घोषणा SPI_TRANSFER1_END	0x40
#घोषणा SPI_DO_MODE1		0x00
#घोषणा SPI_DI_MODE1		0x01

#घोषणा CS_POLARITY_HIGH	0x40
#घोषणा CS_POLARITY_LOW		0x00
#घोषणा DTO_MSB_FIRST		0x00
#घोषणा DTO_LSB_FIRST		0x20
#घोषणा SPI_MASTER		0x00
#घोषणा SPI_SLAVE		0x10
#घोषणा SPI_MODE0		0x00
#घोषणा SPI_MODE1		0x04
#घोषणा SPI_MODE2		0x08
#घोषणा SPI_MODE3		0x0C
#घोषणा SPI_MANUAL		0x00
#घोषणा SPI_HALF_AUTO		0x01
#घोषणा SPI_AUTO		0x02
#घोषणा SPI_EEPROM_AUTO		0x03

#घोषणा EDO_TIMING_MASK		0x03
#घोषणा SAMPLE_RISING		0x00
#घोषणा SAMPLE_DELAY_HALF	0x01
#घोषणा SAMPLE_DELAY_ONE	0x02
#घोषणा SAPMLE_DELAY_ONE_HALF	0x03
#घोषणा TCS_MASK		0x0C

#घोषणा NOT_BYPASS_SD		0x02
#घोषणा DISABLE_SDIO_FUNC	0x04
#घोषणा SELECT_1LUN		0x08

#घोषणा PWR_GATE_EN		0x01
#घोषणा LDO3318_PWR_MASK	0x06
#घोषणा LDO_ON			0x00
#घोषणा LDO_SUSPEND		0x04
#घोषणा LDO_OFF			0x06

#घोषणा SD_CFG1			0xFDA0
#घोषणा SD_CFG2			0xFDA1
#घोषणा SD_CFG3			0xFDA2
#घोषणा SD_STAT1		0xFDA3
#घोषणा SD_STAT2		0xFDA4
#घोषणा SD_BUS_STAT		0xFDA5
#घोषणा SD_PAD_CTL		0xFDA6
#घोषणा SD_SAMPLE_POINT_CTL	0xFDA7
#घोषणा SD_PUSH_POINT_CTL	0xFDA8
#घोषणा SD_CMD0			0xFDA9
#घोषणा SD_CMD1			0xFDAA
#घोषणा SD_CMD2			0xFDAB
#घोषणा SD_CMD3			0xFDAC
#घोषणा SD_CMD4			0xFDAD
#घोषणा SD_CMD5			0xFDAE
#घोषणा SD_BYTE_CNT_L		0xFDAF
#घोषणा SD_BYTE_CNT_H		0xFDB0
#घोषणा SD_BLOCK_CNT_L		0xFDB1
#घोषणा SD_BLOCK_CNT_H		0xFDB2
#घोषणा SD_TRANSFER		0xFDB3
#घोषणा SD_CMD_STATE		0xFDB5
#घोषणा SD_DATA_STATE		0xFDB6

#घोषणा	DCM_DRP_CTL		0xFC23
#घोषणा	DCM_DRP_TRIG		0xFC24
#घोषणा	DCM_DRP_CFG		0xFC25
#घोषणा	DCM_DRP_WR_DATA_L	0xFC26
#घोषणा	DCM_DRP_WR_DATA_H	0xFC27
#घोषणा	DCM_DRP_RD_DATA_L	0xFC28
#घोषणा	DCM_DRP_RD_DATA_H	0xFC29
#घोषणा SD_VPCLK0_CTL		0xFC2A
#घोषणा SD_VPCLK1_CTL		0xFC2B
#घोषणा SD_DCMPS0_CTL		0xFC2C
#घोषणा SD_DCMPS1_CTL		0xFC2D
#घोषणा SD_VPTX_CTL		SD_VPCLK0_CTL
#घोषणा SD_VPRX_CTL		SD_VPCLK1_CTL
#घोषणा SD_DCMPS_TX_CTL		SD_DCMPS0_CTL
#घोषणा SD_DCMPS_RX_CTL		SD_DCMPS1_CTL

#घोषणा CARD_CLK_SOURCE		0xFC2E

#घोषणा CARD_PWR_CTL		0xFD50
#घोषणा CARD_CLK_SWITCH		0xFD51
#घोषणा CARD_SHARE_MODE		0xFD52
#घोषणा CARD_DRIVE_SEL		0xFD53
#घोषणा CARD_STOP		0xFD54
#घोषणा CARD_OE			0xFD55
#घोषणा CARD_AUTO_BLINK		0xFD56
#घोषणा CARD_GPIO_सूची		0xFD57
#घोषणा CARD_GPIO		0xFD58

#घोषणा CARD_DATA_SOURCE	0xFD5B
#घोषणा CARD_SELECT		0xFD5C
#घोषणा SD30_DRIVE_SEL		0xFD5E

#घोषणा CARD_CLK_EN		0xFD69

#घोषणा SDIO_CTRL		0xFD6B

#घोषणा FPDCTL			0xFC00
#घोषणा PDINFO			0xFC01

#घोषणा CLK_CTL			0xFC02
#घोषणा CLK_DIV			0xFC03
#घोषणा CLK_SEL			0xFC04

#घोषणा SSC_DIV_N_0		0xFC0F
#घोषणा SSC_DIV_N_1		0xFC10

#घोषणा RCCTL			0xFC14

#घोषणा FPGA_PULL_CTL		0xFC1D

#घोषणा CARD_PULL_CTL1		0xFD60
#घोषणा CARD_PULL_CTL2		0xFD61
#घोषणा CARD_PULL_CTL3		0xFD62
#घोषणा CARD_PULL_CTL4		0xFD63
#घोषणा CARD_PULL_CTL5		0xFD64
#घोषणा CARD_PULL_CTL6		0xFD65

#घोषणा IRQEN0				0xFE20
#घोषणा IRQSTAT0			0xFE21
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
#घोषणा BCTL				0xFE2D
#घोषणा RBBC0				0xFE2E
#घोषणा RBBC1				0xFE2F
#घोषणा RBDAT				0xFE30
#घोषणा RBCTL				0xFE34
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
#घोषणा PETXCFG				0xFE49

#घोषणा CDRESUMECTL			0xFE52
#घोषणा WAKE_SEL_CTL			0xFE54
#घोषणा PME_FORCE_CTL			0xFE56
#घोषणा ASPM_FORCE_CTL			0xFE57
#घोषणा PM_CLK_FORCE_CTL		0xFE58
#घोषणा PERST_GLITCH_WIDTH		0xFE5C
#घोषणा CHANGE_LINK_STATE		0xFE5B
#घोषणा RESET_LOAD_REG			0xFE5E
#घोषणा HOST_SLEEP_STATE		0xFE60
#घोषणा MAIN_PWR_OFF_CTL		0xFE70	/* RTS5208 */

#घोषणा NFTS_TX_CTRL			0xFE72

#घोषणा PWR_GATE_CTRL			0xFE75
#घोषणा PWD_SUSPEND_EN			0xFE76

#घोषणा EFUSE_CONTENT			0xFE5F

#घोषणा XD_INIT				0xFD10
#घोषणा XD_DTCTL			0xFD11
#घोषणा XD_CTL				0xFD12
#घोषणा XD_TRANSFER			0xFD13
#घोषणा XD_CFG				0xFD14
#घोषणा XD_ADDRESS0			0xFD15
#घोषणा XD_ADDRESS1			0xFD16
#घोषणा XD_ADDRESS2			0xFD17
#घोषणा XD_ADDRESS3			0xFD18
#घोषणा XD_ADDRESS4			0xFD19
#घोषणा XD_DAT				0xFD1A
#घोषणा XD_PAGE_CNT			0xFD1B
#घोषणा XD_PAGE_STATUS			0xFD1C
#घोषणा XD_BLOCK_STATUS			0xFD1D
#घोषणा XD_BLOCK_ADDR1_L		0xFD1E
#घोषणा XD_BLOCK_ADDR1_H		0xFD1F
#घोषणा XD_BLOCK_ADDR2_L		0xFD20
#घोषणा XD_BLOCK_ADDR2_H		0xFD21
#घोषणा XD_BYTE_CNT_L			0xFD22
#घोषणा XD_BYTE_CNT_H			0xFD23
#घोषणा	XD_PARITY			0xFD24
#घोषणा XD_ECC_BIT1			0xFD25
#घोषणा XD_ECC_BYTE1			0xFD26
#घोषणा XD_ECC_BIT2			0xFD27
#घोषणा XD_ECC_BYTE2			0xFD28
#घोषणा XD_RESERVED0			0xFD29
#घोषणा XD_RESERVED1			0xFD2A
#घोषणा XD_RESERVED2			0xFD2B
#घोषणा XD_RESERVED3			0xFD2C
#घोषणा XD_CHK_DATA_STATUS		0xFD2D
#घोषणा XD_CATCTL			0xFD2E

#घोषणा MS_CFG				0xFD40
#घोषणा MS_TPC				0xFD41
#घोषणा MS_TRANS_CFG			0xFD42
#घोषणा MS_TRANSFER			0xFD43
#घोषणा MS_INT_REG			0xFD44
#घोषणा MS_BYTE_CNT			0xFD45
#घोषणा MS_SECTOR_CNT_L			0xFD46
#घोषणा MS_SECTOR_CNT_H			0xFD47
#घोषणा MS_DBUS_H			0xFD48

#घोषणा SSC_CTL1			0xFC11
#घोषणा SSC_CTL2			0xFC12

#घोषणा OCPCTL				0xFC15
#घोषणा OCPSTAT				0xFC16
#घोषणा OCPCLR				0xFC17	/* 5208 */
#घोषणा OCPPARA1			0xFC18
#घोषणा OCPPARA2			0xFC19

#घोषणा EFUSE_OP			0xFC20
#घोषणा EFUSE_CTRL			0xFC21
#घोषणा EFUSE_DATA			0xFC22

#घोषणा	SPI_COMMAND			0xFD80
#घोषणा	SPI_ADDR0			0xFD81
#घोषणा	SPI_ADDR1			0xFD82
#घोषणा	SPI_ADDR2			0xFD83
#घोषणा	SPI_ADDR3			0xFD84
#घोषणा	SPI_CA_NUMBER			0xFD85
#घोषणा	SPI_LENGTH0			0xFD86
#घोषणा	SPI_LENGTH1			0xFD87
#घोषणा	SPI_DATA			0xFD88
#घोषणा SPI_DATA_NUMBER			0xFD89
#घोषणा	SPI_TRANSFER0			0xFD90
#घोषणा	SPI_TRANSFER1			0xFD91
#घोषणा	SPI_CONTROL			0xFD92
#घोषणा	SPI_SIG				0xFD93
#घोषणा	SPI_TCTL			0xFD94
#घोषणा	SPI_SLAVE_NUM			0xFD95
#घोषणा	SPI_CLK_DIVIDER0		0xFD96
#घोषणा	SPI_CLK_DIVIDER1		0xFD97

#घोषणा SRAM_BASE			0xE600
#घोषणा RBUF_BASE			0xF400
#घोषणा PPBUF_BASE1			0xF800
#घोषणा PPBUF_BASE2			0xFA00
#घोषणा IMAGE_FLAG_ADDR0		0xCE80
#घोषणा IMAGE_FLAG_ADDR1		0xCE81

#घोषणा READ_OP			1
#घोषणा WRITE_OP		2

#घोषणा LCTLR		0x80

#घोषणा POLLING_WAIT_CNT	1
#घोषणा IDLE_MAX_COUNT		10
#घोषणा SDIO_IDLE_COUNT		10

#घोषणा DEBOUNCE_CNT			5

व्योम करो_reमुख्यing_work(काष्ठा rtsx_chip *chip);
व्योम try_to_चयन_sdio_ctrl(काष्ठा rtsx_chip *chip);
व्योम करो_reset_sd_card(काष्ठा rtsx_chip *chip);
व्योम करो_reset_xd_card(काष्ठा rtsx_chip *chip);
व्योम करो_reset_ms_card(काष्ठा rtsx_chip *chip);
व्योम rtsx_घातer_off_card(काष्ठा rtsx_chip *chip);
व्योम rtsx_release_cards(काष्ठा rtsx_chip *chip);
व्योम rtsx_reset_cards(काष्ठा rtsx_chip *chip);
व्योम rtsx_reinit_cards(काष्ठा rtsx_chip *chip, पूर्णांक reset_chip);
व्योम rtsx_init_cards(काष्ठा rtsx_chip *chip);
पूर्णांक चयन_ssc_घड़ी(काष्ठा rtsx_chip *chip, पूर्णांक clk);
पूर्णांक चयन_normal_घड़ी(काष्ठा rtsx_chip *chip, पूर्णांक clk);
पूर्णांक enable_card_घड़ी(काष्ठा rtsx_chip *chip, u8 card);
पूर्णांक disable_card_घड़ी(काष्ठा rtsx_chip *chip, u8 card);
पूर्णांक card_rw(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip,
	    u32 sec_addr, u16 sec_cnt);
व्योम trans_dma_enable(क्रमागत dma_data_direction dir,
		      काष्ठा rtsx_chip *chip, u32 byte_cnt, u8 pack_size);
व्योम toggle_gpio(काष्ठा rtsx_chip *chip, u8 gpio);
व्योम turn_on_led(काष्ठा rtsx_chip *chip, u8 gpio);
व्योम turn_off_led(काष्ठा rtsx_chip *chip, u8 gpio);

पूर्णांक card_share_mode(काष्ठा rtsx_chip *chip, पूर्णांक card);
पूर्णांक select_card(काष्ठा rtsx_chip *chip, पूर्णांक card);
पूर्णांक detect_card_cd(काष्ठा rtsx_chip *chip, पूर्णांक card);
पूर्णांक check_card_exist(काष्ठा rtsx_chip *chip, अचिन्हित पूर्णांक lun);
पूर्णांक check_card_पढ़ोy(काष्ठा rtsx_chip *chip, अचिन्हित पूर्णांक lun);
पूर्णांक check_card_wp(काष्ठा rtsx_chip *chip, अचिन्हित पूर्णांक lun);
व्योम eject_card(काष्ठा rtsx_chip *chip, अचिन्हित पूर्णांक lun);
u8 get_lun_card(काष्ठा rtsx_chip *chip, अचिन्हित पूर्णांक lun);

अटल अंतरभूत u32 get_card_size(काष्ठा rtsx_chip *chip, अचिन्हित पूर्णांक lun)
अणु
#अगर_घोषित SUPPORT_SD_LOCK
	काष्ठा sd_info *sd_card = &chip->sd_card;

	अगर ((get_lun_card(chip, lun) == SD_CARD) &&
	    (sd_card->sd_lock_status & SD_LOCKED))
		वापस 0;

	वापस chip->capacity[lun];
#अन्यथा
	वापस chip->capacity[lun];
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक चयन_घड़ी(काष्ठा rtsx_chip *chip, पूर्णांक clk)
अणु
	पूर्णांक retval = 0;

	अगर (chip->asic_code)
		retval = चयन_ssc_घड़ी(chip, clk);
	अन्यथा
		retval = चयन_normal_घड़ी(chip, clk);

	वापस retval;
पूर्ण

पूर्णांक card_घातer_on(काष्ठा rtsx_chip *chip, u8 card);
पूर्णांक card_घातer_off(काष्ठा rtsx_chip *chip, u8 card);

अटल अंतरभूत पूर्णांक card_घातer_off_all(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_PWR_CTL, 0x0F, 0x0F);
	अगर (retval)
		वापस retval;

	वापस STATUS_SUCCESS;
पूर्ण

अटल अंतरभूत व्योम rtsx_clear_xd_error(काष्ठा rtsx_chip *chip)
अणु
	rtsx_ग_लिखो_रेजिस्टर(chip, CARD_STOP, XD_STOP | XD_CLR_ERR,
			    XD_STOP | XD_CLR_ERR);
पूर्ण

अटल अंतरभूत व्योम rtsx_clear_sd_error(काष्ठा rtsx_chip *chip)
अणु
	rtsx_ग_लिखो_रेजिस्टर(chip, CARD_STOP, SD_STOP | SD_CLR_ERR,
			    SD_STOP | SD_CLR_ERR);
पूर्ण

अटल अंतरभूत व्योम rtsx_clear_ms_error(काष्ठा rtsx_chip *chip)
अणु
	rtsx_ग_लिखो_रेजिस्टर(chip, CARD_STOP, MS_STOP | MS_CLR_ERR,
			    MS_STOP | MS_CLR_ERR);
पूर्ण

अटल अंतरभूत व्योम rtsx_clear_spi_error(काष्ठा rtsx_chip *chip)
अणु
	rtsx_ग_लिखो_रेजिस्टर(chip, CARD_STOP, SPI_STOP | SPI_CLR_ERR,
			    SPI_STOP | SPI_CLR_ERR);
पूर्ण

#अगर_घोषित SUPPORT_SDIO_ASPM
व्योम dynamic_configure_sdio_aspm(काष्ठा rtsx_chip *chip);
#पूर्ण_अगर

#पूर्ण_अगर  /* __REALTEK_RTSX_CARD_H */
