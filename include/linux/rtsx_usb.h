<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Driver क्रम Realtek RTS5139 USB card पढ़ोer
 *
 * Copyright(c) 2009-2013 Realtek Semiconductor Corp. All rights reserved.
 *
 * Author:
 *   Roger Tseng <rogerable@realtek.com>
 */

#अगर_अघोषित __RTSX_USB_H
#घोषणा __RTSX_USB_H

#समावेश <linux/usb.h>

/* related module names */
#घोषणा RTSX_USB_SD_CARD	0
#घोषणा RTSX_USB_MS_CARD	1

/* endpoपूर्णांक numbers */
#घोषणा EP_BULK_OUT		1
#घोषणा EP_BULK_IN		2
#घोषणा EP_INTR_IN		3

/* USB venकरोr requests */
#घोषणा RTSX_USB_REQ_REG_OP	0x00
#घोषणा RTSX_USB_REQ_POLL	0x02

/* miscellaneous parameters */
#घोषणा MIN_DIV_N		60
#घोषणा MAX_DIV_N		120

#घोषणा MAX_PHASE		15
#घोषणा RX_TUNING_CNT		3

#घोषणा QFN24			0
#घोषणा LQFP48			1
#घोषणा CHECK_PKG(ucr, pkg)	((ucr)->package == (pkg))

/* data काष्ठाures */
काष्ठा rtsx_ucr अणु
	u16			venकरोr_id;
	u16			product_id;

	पूर्णांक			package;
	u8			ic_version;
	bool			is_rts5179;

	अचिन्हित पूर्णांक		cur_clk;

	u8			*cmd_buf;
	अचिन्हित पूर्णांक		cmd_idx;
	u8			*rsp_buf;

	काष्ठा usb_device	*pusb_dev;
	काष्ठा usb_पूर्णांकerface	*pusb_पूर्णांकf;
	काष्ठा usb_sg_request	current_sg;
	अचिन्हित अक्षर		*iobuf;
	dma_addr_t		iobuf_dma;

	काष्ठा समयr_list	sg_समयr;
	काष्ठा mutex		dev_mutex;
पूर्ण;

/* buffer size */
#घोषणा IOBUF_SIZE		1024

/* prototypes of exported functions */
बाह्य पूर्णांक rtsx_usb_get_card_status(काष्ठा rtsx_ucr *ucr, u16 *status);

बाह्य पूर्णांक rtsx_usb_पढ़ो_रेजिस्टर(काष्ठा rtsx_ucr *ucr, u16 addr, u8 *data);
बाह्य पूर्णांक rtsx_usb_ग_लिखो_रेजिस्टर(काष्ठा rtsx_ucr *ucr, u16 addr, u8 mask,
		u8 data);

बाह्य पूर्णांक rtsx_usb_ep0_ग_लिखो_रेजिस्टर(काष्ठा rtsx_ucr *ucr, u16 addr, u8 mask,
		u8 data);
बाह्य पूर्णांक rtsx_usb_ep0_पढ़ो_रेजिस्टर(काष्ठा rtsx_ucr *ucr, u16 addr,
		u8 *data);

बाह्य व्योम rtsx_usb_add_cmd(काष्ठा rtsx_ucr *ucr, u8 cmd_type,
		u16 reg_addr, u8 mask, u8 data);
बाह्य पूर्णांक rtsx_usb_send_cmd(काष्ठा rtsx_ucr *ucr, u8 flag, पूर्णांक समयout);
बाह्य पूर्णांक rtsx_usb_get_rsp(काष्ठा rtsx_ucr *ucr, पूर्णांक rsp_len, पूर्णांक समयout);
बाह्य पूर्णांक rtsx_usb_transfer_data(काष्ठा rtsx_ucr *ucr, अचिन्हित पूर्णांक pipe,
			      व्योम *buf, अचिन्हित पूर्णांक len, पूर्णांक use_sg,
			      अचिन्हित पूर्णांक *act_len, पूर्णांक समयout);

बाह्य पूर्णांक rtsx_usb_पढ़ो_ppbuf(काष्ठा rtsx_ucr *ucr, u8 *buf, पूर्णांक buf_len);
बाह्य पूर्णांक rtsx_usb_ग_लिखो_ppbuf(काष्ठा rtsx_ucr *ucr, u8 *buf, पूर्णांक buf_len);
बाह्य पूर्णांक rtsx_usb_चयन_घड़ी(काष्ठा rtsx_ucr *ucr, अचिन्हित पूर्णांक card_घड़ी,
		u8 ssc_depth, bool initial_mode, bool द्विगुन_clk, bool vpclk);
बाह्य पूर्णांक rtsx_usb_card_exclusive_check(काष्ठा rtsx_ucr *ucr, पूर्णांक card);

/* card status */
#घोषणा SD_CD		0x01
#घोषणा MS_CD		0x02
#घोषणा XD_CD		0x04
#घोषणा CD_MASK		(SD_CD | MS_CD | XD_CD)
#घोषणा SD_WP		0x08

/* पढ़ोer command field offset & parameters */
#घोषणा READ_REG_CMD		0
#घोषणा WRITE_REG_CMD		1
#घोषणा CHECK_REG_CMD		2

#घोषणा PACKET_TYPE		4
#घोषणा CNT_H			5
#घोषणा CNT_L			6
#घोषणा STAGE_FLAG		7
#घोषणा CMD_OFFSET		8
#घोषणा SEQ_WRITE_DATA_OFFSET	12

#घोषणा BATCH_CMD		0
#घोषणा SEQ_READ		1
#घोषणा SEQ_WRITE		2

#घोषणा STAGE_R			0x01
#घोषणा STAGE_DI		0x02
#घोषणा STAGE_DO		0x04
#घोषणा STAGE_MS_STATUS		0x08
#घोषणा STAGE_XD_STATUS		0x10
#घोषणा MODE_C			0x00
#घोषणा MODE_CR			(STAGE_R)
#घोषणा MODE_Cसूची		(STAGE_R | STAGE_DI)
#घोषणा MODE_CDOR		(STAGE_R | STAGE_DO)

#घोषणा EP0_OP_SHIFT		14
#घोषणा EP0_READ_REG_CMD	2
#घोषणा EP0_WRITE_REG_CMD	3

#घोषणा rtsx_usb_cmd_hdr_tag(ucr)		\
	करो अणु					\
		ucr->cmd_buf[0] = 'R';		\
		ucr->cmd_buf[1] = 'T';		\
		ucr->cmd_buf[2] = 'C';		\
		ucr->cmd_buf[3] = 'R';		\
	पूर्ण जबतक (0)

अटल अंतरभूत व्योम rtsx_usb_init_cmd(काष्ठा rtsx_ucr *ucr)
अणु
	rtsx_usb_cmd_hdr_tag(ucr);
	ucr->cmd_idx = 0;
	ucr->cmd_buf[PACKET_TYPE] = BATCH_CMD;
पूर्ण

/* पूर्णांकernal रेजिस्टर address */
#घोषणा FPDCTL				0xFC00
#घोषणा SSC_DIV_N_0			0xFC07
#घोषणा SSC_CTL1			0xFC09
#घोषणा SSC_CTL2			0xFC0A
#घोषणा CFG_MODE			0xFC0E
#घोषणा CFG_MODE_1			0xFC0F
#घोषणा RCCTL				0xFC14
#घोषणा SOF_WDOG			0xFC28
#घोषणा SYS_DUMMY0			0xFC30

#घोषणा MS_BLKEND			0xFD30
#घोषणा MS_READ_START			0xFD31
#घोषणा MS_READ_COUNT			0xFD32
#घोषणा MS_WRITE_START			0xFD33
#घोषणा MS_WRITE_COUNT			0xFD34
#घोषणा MS_COMMAND			0xFD35
#घोषणा MS_OLD_BLOCK_0			0xFD36
#घोषणा MS_OLD_BLOCK_1			0xFD37
#घोषणा MS_NEW_BLOCK_0			0xFD38
#घोषणा MS_NEW_BLOCK_1			0xFD39
#घोषणा MS_LOG_BLOCK_0			0xFD3A
#घोषणा MS_LOG_BLOCK_1			0xFD3B
#घोषणा MS_BUS_WIDTH			0xFD3C
#घोषणा MS_PAGE_START			0xFD3D
#घोषणा MS_PAGE_LENGTH			0xFD3E
#घोषणा MS_CFG				0xFD40
#घोषणा MS_TPC				0xFD41
#घोषणा MS_TRANS_CFG			0xFD42
#घोषणा MS_TRANSFER			0xFD43
#घोषणा MS_INT_REG			0xFD44
#घोषणा MS_BYTE_CNT			0xFD45
#घोषणा MS_SECTOR_CNT_L			0xFD46
#घोषणा MS_SECTOR_CNT_H			0xFD47
#घोषणा MS_DBUS_H			0xFD48

#घोषणा CARD_DMA1_CTL			0xFD5C
#घोषणा CARD_PULL_CTL1			0xFD60
#घोषणा CARD_PULL_CTL2			0xFD61
#घोषणा CARD_PULL_CTL3			0xFD62
#घोषणा CARD_PULL_CTL4			0xFD63
#घोषणा CARD_PULL_CTL5			0xFD64
#घोषणा CARD_PULL_CTL6			0xFD65
#घोषणा CARD_EXIST			0xFD6F
#घोषणा CARD_INT_PEND			0xFD71

#घोषणा LDO_POWER_CFG			0xFD7B

#घोषणा SD_CFG1				0xFDA0
#घोषणा SD_CFG2				0xFDA1
#घोषणा SD_CFG3				0xFDA2
#घोषणा SD_STAT1			0xFDA3
#घोषणा SD_STAT2			0xFDA4
#घोषणा SD_BUS_STAT			0xFDA5
#घोषणा SD_PAD_CTL			0xFDA6
#घोषणा SD_SAMPLE_POINT_CTL		0xFDA7
#घोषणा SD_PUSH_POINT_CTL		0xFDA8
#घोषणा SD_CMD0				0xFDA9
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
#घोषणा SD_CMD_STATE			0xFDB5
#घोषणा SD_DATA_STATE			0xFDB6
#घोषणा SD_VPCLK0_CTL			0xFC2A
#घोषणा SD_VPCLK1_CTL			0xFC2B
#घोषणा SD_DCMPS0_CTL			0xFC2C
#घोषणा SD_DCMPS1_CTL			0xFC2D

#घोषणा CARD_DMA1_CTL			0xFD5C

#घोषणा HW_VERSION			0xFC01

#घोषणा SSC_CLK_FPGA_SEL		0xFC02
#घोषणा CLK_DIV				0xFC03
#घोषणा SFSM_ED				0xFC04

#घोषणा CD_DEGLITCH_WIDTH		0xFC20
#घोषणा CD_DEGLITCH_EN			0xFC21
#घोषणा AUTO_DELINK_EN			0xFC23

#घोषणा FPGA_PULL_CTL			0xFC1D
#घोषणा CARD_CLK_SOURCE			0xFC2E

#घोषणा CARD_SHARE_MODE			0xFD51
#घोषणा CARD_DRIVE_SEL			0xFD52
#घोषणा CARD_STOP			0xFD53
#घोषणा CARD_OE				0xFD54
#घोषणा CARD_AUTO_BLINK			0xFD55
#घोषणा CARD_GPIO			0xFD56
#घोषणा SD30_DRIVE_SEL			0xFD57

#घोषणा CARD_DATA_SOURCE		0xFD5D
#घोषणा CARD_SELECT			0xFD5E

#घोषणा CARD_CLK_EN			0xFD79
#घोषणा CARD_PWR_CTL			0xFD7A

#घोषणा OCPCTL				0xFD80
#घोषणा OCPPARA1			0xFD81
#घोषणा OCPPARA2			0xFD82
#घोषणा OCPSTAT				0xFD83

#घोषणा HS_USB_STAT			0xFE01
#घोषणा HS_VCONTROL			0xFE26
#घोषणा HS_VSTAIN			0xFE27
#घोषणा HS_VLOADM			0xFE28
#घोषणा HS_VSTAOUT			0xFE29

#घोषणा MC_IRQ				0xFF00
#घोषणा MC_IRQEN			0xFF01
#घोषणा MC_FIFO_CTL			0xFF02
#घोषणा MC_FIFO_BC0			0xFF03
#घोषणा MC_FIFO_BC1			0xFF04
#घोषणा MC_FIFO_STAT			0xFF05
#घोषणा MC_FIFO_MODE			0xFF06
#घोषणा MC_FIFO_RD_PTR0			0xFF07
#घोषणा MC_FIFO_RD_PTR1			0xFF08
#घोषणा MC_DMA_CTL			0xFF10
#घोषणा MC_DMA_TC0			0xFF11
#घोषणा MC_DMA_TC1			0xFF12
#घोषणा MC_DMA_TC2			0xFF13
#घोषणा MC_DMA_TC3			0xFF14
#घोषणा MC_DMA_RST			0xFF15

#घोषणा RBUF_SIZE_MASK			0xFBFF
#घोषणा RBUF_BASE			0xF000
#घोषणा PPBUF_BASE1			0xF800
#घोषणा PPBUF_BASE2			0xFA00

/* पूर्णांकernal रेजिस्टर value macros */
#घोषणा POWER_OFF			0x03
#घोषणा PARTIAL_POWER_ON		0x02
#घोषणा POWER_ON			0x00
#घोषणा POWER_MASK			0x03
#घोषणा LDO3318_PWR_MASK		0x0C
#घोषणा LDO_ON				0x00
#घोषणा LDO_SUSPEND			0x08
#घोषणा LDO_OFF				0x0C
#घोषणा DV3318_AUTO_PWR_OFF		0x10
#घोषणा FORCE_LDO_POWERB		0x60

/* LDO_POWER_CFG */
#घोषणा TUNE_SD18_MASK			0x1C
#घोषणा TUNE_SD18_1V7			0x00
#घोषणा TUNE_SD18_1V8			(0x01 << 2)
#घोषणा TUNE_SD18_1V9			(0x02 << 2)
#घोषणा TUNE_SD18_2V0			(0x03 << 2)
#घोषणा TUNE_SD18_2V7			(0x04 << 2)
#घोषणा TUNE_SD18_2V8			(0x05 << 2)
#घोषणा TUNE_SD18_2V9			(0x06 << 2)
#घोषणा TUNE_SD18_3V3			(0x07 << 2)

/* CLK_DIV */
#घोषणा CLK_CHANGE			0x80
#घोषणा CLK_DIV_1			0x00
#घोषणा CLK_DIV_2			0x01
#घोषणा CLK_DIV_4			0x02
#घोषणा CLK_DIV_8			0x03

#घोषणा SSC_POWER_MASK			0x01
#घोषणा SSC_POWER_DOWN			0x01
#घोषणा SSC_POWER_ON			0x00

#घोषणा FPGA_VER			0x80
#घोषणा HW_VER_MASK			0x0F

#घोषणा EXTEND_DMA1_ASYNC_SIGNAL	0x02

/* CFG_MODE*/
#घोषणा XTAL_FREE			0x80
#घोषणा CLK_MODE_MASK			0x03
#घोषणा CLK_MODE_12M_XTAL		0x00
#घोषणा CLK_MODE_NON_XTAL		0x01
#घोषणा CLK_MODE_24M_OSC		0x02
#घोषणा CLK_MODE_48M_OSC		0x03

/* CFG_MODE_1*/
#घोषणा RTS5179				0x02

#घोषणा NYET_EN				0x01
#घोषणा NYET_MSAK			0x01

#घोषणा SD30_DRIVE_MASK			0x07
#घोषणा SD20_DRIVE_MASK			0x03

#घोषणा DISABLE_SD_CD			0x08
#घोषणा DISABLE_MS_CD			0x10
#घोषणा DISABLE_XD_CD			0x20
#घोषणा SD_CD_DEGLITCH_EN		0x01
#घोषणा MS_CD_DEGLITCH_EN		0x02
#घोषणा XD_CD_DEGLITCH_EN		0x04

#घोषणा	CARD_SHARE_LQFP48		0x04
#घोषणा	CARD_SHARE_QFN24		0x00
#घोषणा CARD_SHARE_LQFP_SEL		0x04
#घोषणा	CARD_SHARE_XD			0x00
#घोषणा	CARD_SHARE_SD			0x01
#घोषणा	CARD_SHARE_MS			0x02
#घोषणा CARD_SHARE_MASK			0x03


/* SD30_DRIVE_SEL */
#घोषणा DRIVER_TYPE_A			0x05
#घोषणा DRIVER_TYPE_B			0x03
#घोषणा DRIVER_TYPE_C			0x02
#घोषणा DRIVER_TYPE_D			0x01

/* SD_BUS_STAT */
#घोषणा	SD_CLK_TOGGLE_EN		0x80
#घोषणा	SD_CLK_FORCE_STOP	        0x40
#घोषणा	SD_DAT3_STATUS		        0x10
#घोषणा	SD_DAT2_STATUS		        0x08
#घोषणा	SD_DAT1_STATUS		        0x04
#घोषणा	SD_DAT0_STATUS		        0x02
#घोषणा	SD_CMD_STATUS			0x01

/* SD_PAD_CTL */
#घोषणा	SD_IO_USING_1V8		        0x80
#घोषणा	SD_IO_USING_3V3		        0x7F
#घोषणा	TYPE_A_DRIVING		        0x00
#घोषणा	TYPE_B_DRIVING			0x01
#घोषणा	TYPE_C_DRIVING			0x02
#घोषणा	TYPE_D_DRIVING		        0x03

/* CARD_CLK_EN */
#घोषणा SD_CLK_EN			0x04
#घोषणा MS_CLK_EN			0x08

/* CARD_SELECT */
#घोषणा SD_MOD_SEL			2
#घोषणा MS_MOD_SEL			3

/* CARD_SHARE_MODE */
#घोषणा	CARD_SHARE_LQFP48		0x04
#घोषणा	CARD_SHARE_QFN24		0x00
#घोषणा CARD_SHARE_LQFP_SEL		0x04
#घोषणा	CARD_SHARE_XD			0x00
#घोषणा	CARD_SHARE_SD			0x01
#घोषणा	CARD_SHARE_MS			0x02
#घोषणा CARD_SHARE_MASK			0x03

/* SSC_CTL1 */
#घोषणा SSC_RSTB			0x80
#घोषणा SSC_8X_EN			0x40
#घोषणा SSC_FIX_FRAC			0x20
#घोषणा SSC_SEL_1M			0x00
#घोषणा SSC_SEL_2M			0x08
#घोषणा SSC_SEL_4M			0x10
#घोषणा SSC_SEL_8M			0x18

/* SSC_CTL2 */
#घोषणा SSC_DEPTH_MASK			0x03
#घोषणा SSC_DEPTH_DISALBE		0x00
#घोषणा SSC_DEPTH_2M			0x01
#घोषणा SSC_DEPTH_1M			0x02
#घोषणा SSC_DEPTH_512K			0x03

/* SD_VPCLK0_CTL */
#घोषणा PHASE_CHANGE			0x80
#घोषणा PHASE_NOT_RESET			0x40

/* SD_TRANSFER */
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

/* SD_CFG1 */
#घोषणा SD_CLK_DIVIDE_0			0x00
#घोषणा	SD_CLK_DIVIDE_256		0xC0
#घोषणा	SD_CLK_DIVIDE_128		0x80
#घोषणा SD_CLK_DIVIDE_MASK		0xC0
#घोषणा	SD_BUS_WIDTH_1BIT		0x00
#घोषणा	SD_BUS_WIDTH_4BIT		0x01
#घोषणा	SD_BUS_WIDTH_8BIT		0x02
#घोषणा	SD_ASYNC_FIFO_RST		0x10
#घोषणा	SD_20_MODE			0x00
#घोषणा	SD_DDR_MODE			0x04
#घोषणा	SD_30_MODE			0x08

/* SD_CFG2 */
#घोषणा	SD_CALCULATE_CRC7		0x00
#घोषणा	SD_NO_CALCULATE_CRC7		0x80
#घोषणा	SD_CHECK_CRC16			0x00
#घोषणा	SD_NO_CHECK_CRC16		0x40
#घोषणा SD_WAIT_CRC_TO_EN		0x20
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

/* SD_STAT1 */
#घोषणा	SD_CRC7_ERR			0x80
#घोषणा	SD_CRC16_ERR			0x40
#घोषणा	SD_CRC_WRITE_ERR		0x20
#घोषणा	SD_CRC_WRITE_ERR_MASK		0x1C
#घोषणा	GET_CRC_TIME_OUT		0x02
#घोषणा	SD_TUNING_COMPARE_ERR		0x01

/* SD_DATA_STATE */
#घोषणा SD_DATA_IDLE			0x80

/* CARD_DATA_SOURCE */
#घोषणा PINGPONG_BUFFER			0x01
#घोषणा RING_BUFFER			0x00

/* CARD_OE */
#घोषणा SD_OUTPUT_EN			0x04
#घोषणा MS_OUTPUT_EN			0x08

/* CARD_STOP */
#घोषणा SD_STOP				0x04
#घोषणा MS_STOP				0x08
#घोषणा SD_CLR_ERR			0x40
#घोषणा MS_CLR_ERR			0x80

/* CARD_CLK_SOURCE */
#घोषणा CRC_FIX_CLK			(0x00 << 0)
#घोषणा CRC_VAR_CLK0			(0x01 << 0)
#घोषणा CRC_VAR_CLK1			(0x02 << 0)
#घोषणा SD30_FIX_CLK			(0x00 << 2)
#घोषणा SD30_VAR_CLK0			(0x01 << 2)
#घोषणा SD30_VAR_CLK1			(0x02 << 2)
#घोषणा SAMPLE_FIX_CLK			(0x00 << 4)
#घोषणा SAMPLE_VAR_CLK0			(0x01 << 4)
#घोषणा SAMPLE_VAR_CLK1			(0x02 << 4)

/* SD_SAMPLE_POINT_CTL */
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

/* SD_PUSH_POINT_CTL */
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

/* MS_CFG */
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

/* MS_TRANS_CFG */
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

/* MS_TRANSFER */
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
#घोषणा MS_TM_SET_CMD			0x06
#घोषणा MS_TM_COPY_PAGE			0x07
#घोषणा MS_TM_MULTI_READ		0x02
#घोषणा MS_TM_MULTI_WRITE		0x03

/* MC_FIFO_CTL */
#घोषणा FIFO_FLUSH			0x01

/* MC_DMA_RST */
#घोषणा DMA_RESET  0x01

/* MC_DMA_CTL */
#घोषणा DMA_TC_EQ_0			0x80
#घोषणा DMA_सूची_TO_CARD			0x00
#घोषणा DMA_सूची_FROM_CARD		0x02
#घोषणा DMA_EN				0x01
#घोषणा DMA_128				(0 << 2)
#घोषणा DMA_256				(1 << 2)
#घोषणा DMA_512				(2 << 2)
#घोषणा DMA_1024			(3 << 2)
#घोषणा DMA_PACK_SIZE_MASK		0x0C

/* CARD_INT_PEND */
#घोषणा XD_INT				0x10
#घोषणा MS_INT				0x08
#घोषणा SD_INT				0x04

/* LED operations*/
अटल अंतरभूत पूर्णांक rtsx_usb_turn_on_led(काष्ठा rtsx_ucr *ucr)
अणु
	वापस  rtsx_usb_ep0_ग_लिखो_रेजिस्टर(ucr, CARD_GPIO, 0x03, 0x02);
पूर्ण

अटल अंतरभूत पूर्णांक rtsx_usb_turn_off_led(काष्ठा rtsx_ucr *ucr)
अणु
	वापस rtsx_usb_ep0_ग_लिखो_रेजिस्टर(ucr, CARD_GPIO, 0x03, 0x03);
पूर्ण

/* HW error clearing */
अटल अंतरभूत व्योम rtsx_usb_clear_fsm_err(काष्ठा rtsx_ucr *ucr)
अणु
	rtsx_usb_ep0_ग_लिखो_रेजिस्टर(ucr, SFSM_ED, 0xf8, 0xf8);
पूर्ण

अटल अंतरभूत व्योम rtsx_usb_clear_dma_err(काष्ठा rtsx_ucr *ucr)
अणु
	rtsx_usb_ep0_ग_लिखो_रेजिस्टर(ucr, MC_FIFO_CTL,
			FIFO_FLUSH, FIFO_FLUSH);
	rtsx_usb_ep0_ग_लिखो_रेजिस्टर(ucr, MC_DMA_RST, DMA_RESET, DMA_RESET);
पूर्ण
#पूर्ण_अगर /* __RTS51139_H */
