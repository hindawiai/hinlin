<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 MediaTek Inc.
 * Author: Flora Fu, MediaTek
 */
#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>

#घोषणा PWRAP_MT8135_BRIDGE_IORD_ARB_EN		0x4
#घोषणा PWRAP_MT8135_BRIDGE_WACS3_EN		0x10
#घोषणा PWRAP_MT8135_BRIDGE_INIT_DONE3		0x14
#घोषणा PWRAP_MT8135_BRIDGE_WACS4_EN		0x24
#घोषणा PWRAP_MT8135_BRIDGE_INIT_DONE4		0x28
#घोषणा PWRAP_MT8135_BRIDGE_INT_EN		0x38
#घोषणा PWRAP_MT8135_BRIDGE_TIMER_EN		0x48
#घोषणा PWRAP_MT8135_BRIDGE_WDT_UNIT		0x50
#घोषणा PWRAP_MT8135_BRIDGE_WDT_SRC_EN		0x54

/* macro क्रम wrapper status */
#घोषणा PWRAP_GET_WACS_RDATA(x)		(((x) >> 0) & 0x0000ffff)
#घोषणा PWRAP_GET_WACS_ARB_FSM(x)	(((x) >> 1) & 0x00000007)
#घोषणा PWRAP_GET_WACS_FSM(x)		(((x) >> 16) & 0x00000007)
#घोषणा PWRAP_GET_WACS_REQ(x)		(((x) >> 19) & 0x00000001)
#घोषणा PWRAP_STATE_SYNC_IDLE0		BIT(20)
#घोषणा PWRAP_STATE_INIT_DONE0		BIT(21)
#घोषणा PWRAP_STATE_INIT_DONE1		BIT(15)

/* macro क्रम WACS FSM */
#घोषणा PWRAP_WACS_FSM_IDLE		0x00
#घोषणा PWRAP_WACS_FSM_REQ		0x02
#घोषणा PWRAP_WACS_FSM_WFDLE		0x04
#घोषणा PWRAP_WACS_FSM_WFVLDCLR		0x06
#घोषणा PWRAP_WACS_INIT_DONE		0x01
#घोषणा PWRAP_WACS_WACS_SYNC_IDLE	0x01
#घोषणा PWRAP_WACS_SYNC_BUSY		0x00

/* macro क्रम device wrapper शेष value */
#घोषणा PWRAP_DEW_READ_TEST_VAL		0x5aa5
#घोषणा PWRAP_DEW_WRITE_TEST_VAL	0xa55a

/* macro क्रम manual command */
#घोषणा PWRAP_MAN_CMD_SPI_WRITE_NEW	(1 << 14)
#घोषणा PWRAP_MAN_CMD_SPI_WRITE		(1 << 13)
#घोषणा PWRAP_MAN_CMD_OP_CSH		(0x0 << 8)
#घोषणा PWRAP_MAN_CMD_OP_CSL		(0x1 << 8)
#घोषणा PWRAP_MAN_CMD_OP_CK		(0x2 << 8)
#घोषणा PWRAP_MAN_CMD_OP_OUTS		(0x8 << 8)
#घोषणा PWRAP_MAN_CMD_OP_OUTD		(0x9 << 8)
#घोषणा PWRAP_MAN_CMD_OP_OUTQ		(0xa << 8)

/* macro क्रम Watch Dog Timer Source */
#घोषणा PWRAP_WDT_SRC_EN_STAUPD_TRIG		(1 << 25)
#घोषणा PWRAP_WDT_SRC_EN_HARB_STAUPD_DLE	(1 << 20)
#घोषणा PWRAP_WDT_SRC_EN_HARB_STAUPD_ALE	(1 << 6)
#घोषणा PWRAP_WDT_SRC_MASK_ALL			0xffffffff
#घोषणा PWRAP_WDT_SRC_MASK_NO_STAUPD	~(PWRAP_WDT_SRC_EN_STAUPD_TRIG | \
					  PWRAP_WDT_SRC_EN_HARB_STAUPD_DLE | \
					  PWRAP_WDT_SRC_EN_HARB_STAUPD_ALE)

/* Group of bits used क्रम shown slave capability */
#घोषणा PWRAP_SLV_CAP_SPI	BIT(0)
#घोषणा PWRAP_SLV_CAP_DUALIO	BIT(1)
#घोषणा PWRAP_SLV_CAP_SECURITY	BIT(2)
#घोषणा HAS_CAP(_c, _x)	(((_c) & (_x)) == (_x))

/* Group of bits used क्रम shown pwrap capability */
#घोषणा PWRAP_CAP_BRIDGE	BIT(0)
#घोषणा PWRAP_CAP_RESET		BIT(1)
#घोषणा PWRAP_CAP_DCM		BIT(2)
#घोषणा PWRAP_CAP_INT1_EN	BIT(3)
#घोषणा PWRAP_CAP_WDT_SRC1	BIT(4)
#घोषणा PWRAP_CAP_ARB		BIT(5)

/* defines क्रम slave device wrapper रेजिस्टरs */
क्रमागत dew_regs अणु
	PWRAP_DEW_BASE,
	PWRAP_DEW_DIO_EN,
	PWRAP_DEW_READ_TEST,
	PWRAP_DEW_WRITE_TEST,
	PWRAP_DEW_CRC_EN,
	PWRAP_DEW_CRC_VAL,
	PWRAP_DEW_MON_GRP_SEL,
	PWRAP_DEW_CIPHER_KEY_SEL,
	PWRAP_DEW_CIPHER_IV_SEL,
	PWRAP_DEW_CIPHER_RDY,
	PWRAP_DEW_CIPHER_MODE,
	PWRAP_DEW_CIPHER_SWRST,

	/* MT6323 only regs */
	PWRAP_DEW_CIPHER_EN,
	PWRAP_DEW_RDDMY_NO,

	/* MT6358 only regs */
	PWRAP_SMT_CON1,
	PWRAP_DRV_CON1,
	PWRAP_FILTER_CON0,
	PWRAP_GPIO_PULLEN0_CLR,
	PWRAP_RG_SPI_CON0,
	PWRAP_RG_SPI_RECORD0,
	PWRAP_RG_SPI_CON2,
	PWRAP_RG_SPI_CON3,
	PWRAP_RG_SPI_CON4,
	PWRAP_RG_SPI_CON5,
	PWRAP_RG_SPI_CON6,
	PWRAP_RG_SPI_CON7,
	PWRAP_RG_SPI_CON8,
	PWRAP_RG_SPI_CON13,
	PWRAP_SPISLV_KEY,

	/* MT6359 only regs */
	PWRAP_DEW_CRC_SWRST,
	PWRAP_DEW_RG_EN_RECORD,
	PWRAP_DEW_RECORD_CMD0,
	PWRAP_DEW_RECORD_CMD1,
	PWRAP_DEW_RECORD_CMD2,
	PWRAP_DEW_RECORD_CMD3,
	PWRAP_DEW_RECORD_CMD4,
	PWRAP_DEW_RECORD_CMD5,
	PWRAP_DEW_RECORD_WDATA0,
	PWRAP_DEW_RECORD_WDATA1,
	PWRAP_DEW_RECORD_WDATA2,
	PWRAP_DEW_RECORD_WDATA3,
	PWRAP_DEW_RECORD_WDATA4,
	PWRAP_DEW_RECORD_WDATA5,
	PWRAP_DEW_RG_ADDR_TARGET,
	PWRAP_DEW_RG_ADDR_MASK,
	PWRAP_DEW_RG_WDATA_TARGET,
	PWRAP_DEW_RG_WDATA_MASK,
	PWRAP_DEW_RG_SPI_RECORD_CLR,
	PWRAP_DEW_RG_CMD_ALERT_CLR,

	/* MT6397 only regs */
	PWRAP_DEW_EVENT_OUT_EN,
	PWRAP_DEW_EVENT_SRC_EN,
	PWRAP_DEW_EVENT_SRC,
	PWRAP_DEW_EVENT_FLAG,
	PWRAP_DEW_MON_FLAG_SEL,
	PWRAP_DEW_EVENT_TEST,
	PWRAP_DEW_CIPHER_LOAD,
	PWRAP_DEW_CIPHER_START,
पूर्ण;

अटल स्थिर u32 mt6323_regs[] = अणु
	[PWRAP_DEW_BASE] =		0x0000,
	[PWRAP_DEW_DIO_EN] =		0x018a,
	[PWRAP_DEW_READ_TEST] =		0x018c,
	[PWRAP_DEW_WRITE_TEST] =	0x018e,
	[PWRAP_DEW_CRC_EN] =		0x0192,
	[PWRAP_DEW_CRC_VAL] =		0x0194,
	[PWRAP_DEW_MON_GRP_SEL] =	0x0196,
	[PWRAP_DEW_CIPHER_KEY_SEL] =	0x0198,
	[PWRAP_DEW_CIPHER_IV_SEL] =	0x019a,
	[PWRAP_DEW_CIPHER_EN] =		0x019c,
	[PWRAP_DEW_CIPHER_RDY] =	0x019e,
	[PWRAP_DEW_CIPHER_MODE] =	0x01a0,
	[PWRAP_DEW_CIPHER_SWRST] =	0x01a2,
	[PWRAP_DEW_RDDMY_NO] =		0x01a4,
पूर्ण;

अटल स्थिर u32 mt6351_regs[] = अणु
	[PWRAP_DEW_DIO_EN] =		0x02F2,
	[PWRAP_DEW_READ_TEST] =		0x02F4,
	[PWRAP_DEW_WRITE_TEST] =	0x02F6,
	[PWRAP_DEW_CRC_EN] =		0x02FA,
	[PWRAP_DEW_CRC_VAL] =		0x02FC,
	[PWRAP_DEW_CIPHER_KEY_SEL] =	0x0300,
	[PWRAP_DEW_CIPHER_IV_SEL] =	0x0302,
	[PWRAP_DEW_CIPHER_EN] =		0x0304,
	[PWRAP_DEW_CIPHER_RDY] =	0x0306,
	[PWRAP_DEW_CIPHER_MODE] =	0x0308,
	[PWRAP_DEW_CIPHER_SWRST] =	0x030A,
	[PWRAP_DEW_RDDMY_NO] =		0x030C,
पूर्ण;

अटल स्थिर u32 mt6357_regs[] = अणु
	[PWRAP_DEW_DIO_EN] =            0x040A,
	[PWRAP_DEW_READ_TEST] =         0x040C,
	[PWRAP_DEW_WRITE_TEST] =        0x040E,
	[PWRAP_DEW_CRC_EN] =            0x0412,
	[PWRAP_DEW_CRC_VAL] =           0x0414,
	[PWRAP_DEW_CIPHER_KEY_SEL] =    0x0418,
	[PWRAP_DEW_CIPHER_IV_SEL] =     0x041A,
	[PWRAP_DEW_CIPHER_EN] =         0x041C,
	[PWRAP_DEW_CIPHER_RDY] =        0x041E,
	[PWRAP_DEW_CIPHER_MODE] =       0x0420,
	[PWRAP_DEW_CIPHER_SWRST] =      0x0422,
	[PWRAP_DEW_RDDMY_NO] =          0x0424,
पूर्ण;

अटल स्थिर u32 mt6358_regs[] = अणु
	[PWRAP_SMT_CON1] =		0x0030,
	[PWRAP_DRV_CON1] =		0x0038,
	[PWRAP_FILTER_CON0] =		0x0040,
	[PWRAP_GPIO_PULLEN0_CLR] =	0x0098,
	[PWRAP_RG_SPI_CON0] =		0x0408,
	[PWRAP_RG_SPI_RECORD0] =	0x040a,
	[PWRAP_DEW_DIO_EN] =		0x040c,
	[PWRAP_DEW_READ_TEST]	=	0x040e,
	[PWRAP_DEW_WRITE_TEST]	=	0x0410,
	[PWRAP_DEW_CRC_EN] =		0x0414,
	[PWRAP_DEW_CIPHER_KEY_SEL] =	0x041a,
	[PWRAP_DEW_CIPHER_IV_SEL] =	0x041c,
	[PWRAP_DEW_CIPHER_EN]	=	0x041e,
	[PWRAP_DEW_CIPHER_RDY] =	0x0420,
	[PWRAP_DEW_CIPHER_MODE] =	0x0422,
	[PWRAP_DEW_CIPHER_SWRST] =	0x0424,
	[PWRAP_RG_SPI_CON2] =		0x0432,
	[PWRAP_RG_SPI_CON3] =		0x0434,
	[PWRAP_RG_SPI_CON4] =		0x0436,
	[PWRAP_RG_SPI_CON5] =		0x0438,
	[PWRAP_RG_SPI_CON6] =		0x043a,
	[PWRAP_RG_SPI_CON7] =		0x043c,
	[PWRAP_RG_SPI_CON8] =		0x043e,
	[PWRAP_RG_SPI_CON13] =		0x0448,
	[PWRAP_SPISLV_KEY] =		0x044a,
पूर्ण;

अटल स्थिर u32 mt6359_regs[] = अणु
	[PWRAP_DEW_RG_EN_RECORD] =	0x040a,
	[PWRAP_DEW_DIO_EN] =		0x040c,
	[PWRAP_DEW_READ_TEST] =		0x040e,
	[PWRAP_DEW_WRITE_TEST] =	0x0410,
	[PWRAP_DEW_CRC_SWRST] =		0x0412,
	[PWRAP_DEW_CRC_EN] =		0x0414,
	[PWRAP_DEW_CRC_VAL] =		0x0416,
	[PWRAP_DEW_CIPHER_KEY_SEL] =	0x0418,
	[PWRAP_DEW_CIPHER_IV_SEL] =	0x041a,
	[PWRAP_DEW_CIPHER_EN] =		0x041c,
	[PWRAP_DEW_CIPHER_RDY] =	0x041e,
	[PWRAP_DEW_CIPHER_MODE] =	0x0420,
	[PWRAP_DEW_CIPHER_SWRST] =	0x0422,
	[PWRAP_DEW_RDDMY_NO] =		0x0424,
	[PWRAP_DEW_RECORD_CMD0] =	0x0428,
	[PWRAP_DEW_RECORD_CMD1] =	0x042a,
	[PWRAP_DEW_RECORD_CMD2] =	0x042c,
	[PWRAP_DEW_RECORD_CMD3] =	0x042e,
	[PWRAP_DEW_RECORD_CMD4] =	0x0430,
	[PWRAP_DEW_RECORD_CMD5] =	0x0432,
	[PWRAP_DEW_RECORD_WDATA0] =	0x0434,
	[PWRAP_DEW_RECORD_WDATA1] =	0x0436,
	[PWRAP_DEW_RECORD_WDATA2] =	0x0438,
	[PWRAP_DEW_RECORD_WDATA3] =	0x043a,
	[PWRAP_DEW_RECORD_WDATA4] =	0x043c,
	[PWRAP_DEW_RECORD_WDATA5] =	0x043e,
	[PWRAP_DEW_RG_ADDR_TARGET] =	0x0440,
	[PWRAP_DEW_RG_ADDR_MASK] =	0x0442,
	[PWRAP_DEW_RG_WDATA_TARGET] =	0x0444,
	[PWRAP_DEW_RG_WDATA_MASK] =	0x0446,
	[PWRAP_DEW_RG_SPI_RECORD_CLR] =	0x0448,
	[PWRAP_DEW_RG_CMD_ALERT_CLR] =	0x0448,
	[PWRAP_SPISLV_KEY] =		0x044a,
पूर्ण;

अटल स्थिर u32 mt6397_regs[] = अणु
	[PWRAP_DEW_BASE] =		0xbc00,
	[PWRAP_DEW_EVENT_OUT_EN] =	0xbc00,
	[PWRAP_DEW_DIO_EN] =		0xbc02,
	[PWRAP_DEW_EVENT_SRC_EN] =	0xbc04,
	[PWRAP_DEW_EVENT_SRC] =		0xbc06,
	[PWRAP_DEW_EVENT_FLAG] =	0xbc08,
	[PWRAP_DEW_READ_TEST] =		0xbc0a,
	[PWRAP_DEW_WRITE_TEST] =	0xbc0c,
	[PWRAP_DEW_CRC_EN] =		0xbc0e,
	[PWRAP_DEW_CRC_VAL] =		0xbc10,
	[PWRAP_DEW_MON_GRP_SEL] =	0xbc12,
	[PWRAP_DEW_MON_FLAG_SEL] =	0xbc14,
	[PWRAP_DEW_EVENT_TEST] =	0xbc16,
	[PWRAP_DEW_CIPHER_KEY_SEL] =	0xbc18,
	[PWRAP_DEW_CIPHER_IV_SEL] =	0xbc1a,
	[PWRAP_DEW_CIPHER_LOAD] =	0xbc1c,
	[PWRAP_DEW_CIPHER_START] =	0xbc1e,
	[PWRAP_DEW_CIPHER_RDY] =	0xbc20,
	[PWRAP_DEW_CIPHER_MODE] =	0xbc22,
	[PWRAP_DEW_CIPHER_SWRST] =	0xbc24,
पूर्ण;

क्रमागत pwrap_regs अणु
	PWRAP_MUX_SEL,
	PWRAP_WRAP_EN,
	PWRAP_DIO_EN,
	PWRAP_SIDLY,
	PWRAP_CSHEXT_WRITE,
	PWRAP_CSHEXT_READ,
	PWRAP_CSLEXT_START,
	PWRAP_CSLEXT_END,
	PWRAP_STAUPD_PRD,
	PWRAP_STAUPD_GRPEN,
	PWRAP_STAUPD_MAN_TRIG,
	PWRAP_STAUPD_STA,
	PWRAP_WRAP_STA,
	PWRAP_HARB_INIT,
	PWRAP_HARB_HPRIO,
	PWRAP_HIPRIO_ARB_EN,
	PWRAP_HARB_STA0,
	PWRAP_HARB_STA1,
	PWRAP_MAN_EN,
	PWRAP_MAN_CMD,
	PWRAP_MAN_RDATA,
	PWRAP_MAN_VLDCLR,
	PWRAP_WACS0_EN,
	PWRAP_INIT_DONE0,
	PWRAP_WACS0_CMD,
	PWRAP_WACS0_RDATA,
	PWRAP_WACS0_VLDCLR,
	PWRAP_WACS1_EN,
	PWRAP_INIT_DONE1,
	PWRAP_WACS1_CMD,
	PWRAP_WACS1_RDATA,
	PWRAP_WACS1_VLDCLR,
	PWRAP_WACS2_EN,
	PWRAP_INIT_DONE2,
	PWRAP_WACS2_CMD,
	PWRAP_WACS2_RDATA,
	PWRAP_WACS2_VLDCLR,
	PWRAP_INT_EN,
	PWRAP_INT_FLG_RAW,
	PWRAP_INT_FLG,
	PWRAP_INT_CLR,
	PWRAP_SIG_ADR,
	PWRAP_SIG_MODE,
	PWRAP_SIG_VALUE,
	PWRAP_संक_त्रुटिVAL,
	PWRAP_CRC_EN,
	PWRAP_TIMER_EN,
	PWRAP_TIMER_STA,
	PWRAP_WDT_UNIT,
	PWRAP_WDT_SRC_EN,
	PWRAP_WDT_FLG,
	PWRAP_DEBUG_INT_SEL,
	PWRAP_CIPHER_KEY_SEL,
	PWRAP_CIPHER_IV_SEL,
	PWRAP_CIPHER_RDY,
	PWRAP_CIPHER_MODE,
	PWRAP_CIPHER_SWRST,
	PWRAP_DCM_EN,
	PWRAP_DCM_DBC_PRD,
	PWRAP_EINT_STA0_ADR,
	PWRAP_EINT_STA1_ADR,
	PWRAP_SWINF_2_WDATA_31_0,
	PWRAP_SWINF_2_RDATA_31_0,

	/* MT2701 only regs */
	PWRAP_ADC_CMD_ADDR,
	PWRAP_PWRAP_ADC_CMD,
	PWRAP_ADC_RDY_ADDR,
	PWRAP_ADC_RDATA_ADDR1,
	PWRAP_ADC_RDATA_ADDR2,

	/* MT7622 only regs */
	PWRAP_STA,
	PWRAP_CLR,
	PWRAP_DVFS_ADR8,
	PWRAP_DVFS_WDATA8,
	PWRAP_DVFS_ADR9,
	PWRAP_DVFS_WDATA9,
	PWRAP_DVFS_ADR10,
	PWRAP_DVFS_WDATA10,
	PWRAP_DVFS_ADR11,
	PWRAP_DVFS_WDATA11,
	PWRAP_DVFS_ADR12,
	PWRAP_DVFS_WDATA12,
	PWRAP_DVFS_ADR13,
	PWRAP_DVFS_WDATA13,
	PWRAP_DVFS_ADR14,
	PWRAP_DVFS_WDATA14,
	PWRAP_DVFS_ADR15,
	PWRAP_DVFS_WDATA15,
	PWRAP_EXT_CK,
	PWRAP_ADC_RDATA_ADDR,
	PWRAP_GPS_STA,
	PWRAP_SW_RST,
	PWRAP_DVFS_STEP_CTRL0,
	PWRAP_DVFS_STEP_CTRL1,
	PWRAP_DVFS_STEP_CTRL2,
	PWRAP_SPI2_CTRL,

	/* MT8135 only regs */
	PWRAP_CSHEXT,
	PWRAP_EVENT_IN_EN,
	PWRAP_EVENT_DST_EN,
	PWRAP_RRARB_INIT,
	PWRAP_RRARB_EN,
	PWRAP_RRARB_STA0,
	PWRAP_RRARB_STA1,
	PWRAP_EVENT_STA,
	PWRAP_EVENT_STACLR,
	PWRAP_CIPHER_LOAD,
	PWRAP_CIPHER_START,

	/* MT8173 only regs */
	PWRAP_RDDMY,
	PWRAP_SI_CK_CON,
	PWRAP_DVFS_ADR0,
	PWRAP_DVFS_WDATA0,
	PWRAP_DVFS_ADR1,
	PWRAP_DVFS_WDATA1,
	PWRAP_DVFS_ADR2,
	PWRAP_DVFS_WDATA2,
	PWRAP_DVFS_ADR3,
	PWRAP_DVFS_WDATA3,
	PWRAP_DVFS_ADR4,
	PWRAP_DVFS_WDATA4,
	PWRAP_DVFS_ADR5,
	PWRAP_DVFS_WDATA5,
	PWRAP_DVFS_ADR6,
	PWRAP_DVFS_WDATA6,
	PWRAP_DVFS_ADR7,
	PWRAP_DVFS_WDATA7,
	PWRAP_SPMINF_STA,
	PWRAP_CIPHER_EN,

	/* MT8183 only regs */
	PWRAP_SI_SAMPLE_CTRL,
	PWRAP_CSLEXT_WRITE,
	PWRAP_CSLEXT_READ,
	PWRAP_EXT_CK_WRITE,
	PWRAP_STAUPD_CTRL,
	PWRAP_WACS_P2P_EN,
	PWRAP_INIT_DONE_P2P,
	PWRAP_WACS_MD32_EN,
	PWRAP_INIT_DONE_MD32,
	PWRAP_INT1_EN,
	PWRAP_INT1_FLG,
	PWRAP_INT1_CLR,
	PWRAP_WDT_SRC_EN_1,
	PWRAP_INT_GPS_AUXADC_CMD_ADDR,
	PWRAP_INT_GPS_AUXADC_CMD,
	PWRAP_INT_GPS_AUXADC_RDATA_ADDR,
	PWRAP_EXT_GPS_AUXADC_RDATA_ADDR,
	PWRAP_GPSINF_0_STA,
	PWRAP_GPSINF_1_STA,

	/* MT8516 only regs */
	PWRAP_OP_TYPE,
	PWRAP_MSB_FIRST,
पूर्ण;

अटल पूर्णांक mt2701_regs[] = अणु
	[PWRAP_MUX_SEL] =		0x0,
	[PWRAP_WRAP_EN] =		0x4,
	[PWRAP_DIO_EN] =		0x8,
	[PWRAP_SIDLY] =			0xc,
	[PWRAP_RDDMY] =			0x18,
	[PWRAP_SI_CK_CON] =		0x1c,
	[PWRAP_CSHEXT_WRITE] =		0x20,
	[PWRAP_CSHEXT_READ] =		0x24,
	[PWRAP_CSLEXT_START] =		0x28,
	[PWRAP_CSLEXT_END] =		0x2c,
	[PWRAP_STAUPD_PRD] =		0x30,
	[PWRAP_STAUPD_GRPEN] =		0x34,
	[PWRAP_STAUPD_MAN_TRIG] =	0x38,
	[PWRAP_STAUPD_STA] =		0x3c,
	[PWRAP_WRAP_STA] =		0x44,
	[PWRAP_HARB_INIT] =		0x48,
	[PWRAP_HARB_HPRIO] =		0x4c,
	[PWRAP_HIPRIO_ARB_EN] =		0x50,
	[PWRAP_HARB_STA0] =		0x54,
	[PWRAP_HARB_STA1] =		0x58,
	[PWRAP_MAN_EN] =		0x5c,
	[PWRAP_MAN_CMD] =		0x60,
	[PWRAP_MAN_RDATA] =		0x64,
	[PWRAP_MAN_VLDCLR] =		0x68,
	[PWRAP_WACS0_EN] =		0x6c,
	[PWRAP_INIT_DONE0] =		0x70,
	[PWRAP_WACS0_CMD] =		0x74,
	[PWRAP_WACS0_RDATA] =		0x78,
	[PWRAP_WACS0_VLDCLR] =		0x7c,
	[PWRAP_WACS1_EN] =		0x80,
	[PWRAP_INIT_DONE1] =		0x84,
	[PWRAP_WACS1_CMD] =		0x88,
	[PWRAP_WACS1_RDATA] =		0x8c,
	[PWRAP_WACS1_VLDCLR] =		0x90,
	[PWRAP_WACS2_EN] =		0x94,
	[PWRAP_INIT_DONE2] =		0x98,
	[PWRAP_WACS2_CMD] =		0x9c,
	[PWRAP_WACS2_RDATA] =		0xa0,
	[PWRAP_WACS2_VLDCLR] =		0xa4,
	[PWRAP_INT_EN] =		0xa8,
	[PWRAP_INT_FLG_RAW] =		0xac,
	[PWRAP_INT_FLG] =		0xb0,
	[PWRAP_INT_CLR] =		0xb4,
	[PWRAP_SIG_ADR] =		0xb8,
	[PWRAP_SIG_MODE] =		0xbc,
	[PWRAP_SIG_VALUE] =		0xc0,
	[PWRAP_संक_त्रुटिVAL] =		0xc4,
	[PWRAP_CRC_EN] =		0xc8,
	[PWRAP_TIMER_EN] =		0xcc,
	[PWRAP_TIMER_STA] =		0xd0,
	[PWRAP_WDT_UNIT] =		0xd4,
	[PWRAP_WDT_SRC_EN] =		0xd8,
	[PWRAP_WDT_FLG] =		0xdc,
	[PWRAP_DEBUG_INT_SEL] =		0xe0,
	[PWRAP_DVFS_ADR0] =		0xe4,
	[PWRAP_DVFS_WDATA0] =		0xe8,
	[PWRAP_DVFS_ADR1] =		0xec,
	[PWRAP_DVFS_WDATA1] =		0xf0,
	[PWRAP_DVFS_ADR2] =		0xf4,
	[PWRAP_DVFS_WDATA2] =		0xf8,
	[PWRAP_DVFS_ADR3] =		0xfc,
	[PWRAP_DVFS_WDATA3] =		0x100,
	[PWRAP_DVFS_ADR4] =		0x104,
	[PWRAP_DVFS_WDATA4] =		0x108,
	[PWRAP_DVFS_ADR5] =		0x10c,
	[PWRAP_DVFS_WDATA5] =		0x110,
	[PWRAP_DVFS_ADR6] =		0x114,
	[PWRAP_DVFS_WDATA6] =		0x118,
	[PWRAP_DVFS_ADR7] =		0x11c,
	[PWRAP_DVFS_WDATA7] =		0x120,
	[PWRAP_CIPHER_KEY_SEL] =	0x124,
	[PWRAP_CIPHER_IV_SEL] =		0x128,
	[PWRAP_CIPHER_EN] =		0x12c,
	[PWRAP_CIPHER_RDY] =		0x130,
	[PWRAP_CIPHER_MODE] =		0x134,
	[PWRAP_CIPHER_SWRST] =		0x138,
	[PWRAP_DCM_EN] =		0x13c,
	[PWRAP_DCM_DBC_PRD] =		0x140,
	[PWRAP_ADC_CMD_ADDR] =		0x144,
	[PWRAP_PWRAP_ADC_CMD] =		0x148,
	[PWRAP_ADC_RDY_ADDR] =		0x14c,
	[PWRAP_ADC_RDATA_ADDR1] =	0x150,
	[PWRAP_ADC_RDATA_ADDR2] =	0x154,
पूर्ण;

अटल पूर्णांक mt6765_regs[] = अणु
	[PWRAP_MUX_SEL] =		0x0,
	[PWRAP_WRAP_EN] =		0x4,
	[PWRAP_DIO_EN] =		0x8,
	[PWRAP_RDDMY] =			0x20,
	[PWRAP_CSHEXT_WRITE] =		0x24,
	[PWRAP_CSHEXT_READ] =		0x28,
	[PWRAP_CSLEXT_START] =		0x2C,
	[PWRAP_CSLEXT_END] =		0x30,
	[PWRAP_STAUPD_PRD] =		0x3C,
	[PWRAP_HARB_HPRIO] =		0x68,
	[PWRAP_HIPRIO_ARB_EN] =		0x6C,
	[PWRAP_MAN_EN] =		0x7C,
	[PWRAP_MAN_CMD] =		0x80,
	[PWRAP_WACS0_EN] =		0x8C,
	[PWRAP_WACS1_EN] =		0x94,
	[PWRAP_WACS2_EN] =		0x9C,
	[PWRAP_INIT_DONE2] =		0xA0,
	[PWRAP_WACS2_CMD] =		0xC20,
	[PWRAP_WACS2_RDATA] =		0xC24,
	[PWRAP_WACS2_VLDCLR] =		0xC28,
	[PWRAP_INT_EN] =		0xB4,
	[PWRAP_INT_FLG_RAW] =		0xB8,
	[PWRAP_INT_FLG] =		0xBC,
	[PWRAP_INT_CLR] =		0xC0,
	[PWRAP_TIMER_EN] =		0xE8,
	[PWRAP_WDT_UNIT] =		0xF0,
	[PWRAP_WDT_SRC_EN] =		0xF4,
	[PWRAP_DCM_EN] =		0x1DC,
	[PWRAP_DCM_DBC_PRD] =		0x1E0,
पूर्ण;

अटल पूर्णांक mt6779_regs[] = अणु
	[PWRAP_MUX_SEL] =		0x0,
	[PWRAP_WRAP_EN] =		0x4,
	[PWRAP_DIO_EN] =		0x8,
	[PWRAP_RDDMY] =			0x20,
	[PWRAP_CSHEXT_WRITE] =		0x24,
	[PWRAP_CSHEXT_READ] =		0x28,
	[PWRAP_CSLEXT_WRITE] =		0x2C,
	[PWRAP_CSLEXT_READ] =		0x30,
	[PWRAP_EXT_CK_WRITE] =		0x34,
	[PWRAP_STAUPD_CTRL] =		0x3C,
	[PWRAP_STAUPD_GRPEN] =		0x40,
	[PWRAP_EINT_STA0_ADR] =		0x44,
	[PWRAP_HARB_HPRIO] =		0x68,
	[PWRAP_HIPRIO_ARB_EN] =		0x6C,
	[PWRAP_MAN_EN] =		0x7C,
	[PWRAP_MAN_CMD] =		0x80,
	[PWRAP_WACS0_EN] =		0x8C,
	[PWRAP_INIT_DONE0] =		0x90,
	[PWRAP_WACS1_EN] =		0x94,
	[PWRAP_WACS2_EN] =		0x9C,
	[PWRAP_INIT_DONE1] =		0x98,
	[PWRAP_INIT_DONE2] =		0xA0,
	[PWRAP_INT_EN] =		0xBC,
	[PWRAP_INT_FLG_RAW] =		0xC0,
	[PWRAP_INT_FLG] =		0xC4,
	[PWRAP_INT_CLR] =		0xC8,
	[PWRAP_INT1_EN] =		0xCC,
	[PWRAP_INT1_FLG] =		0xD4,
	[PWRAP_INT1_CLR] =		0xD8,
	[PWRAP_TIMER_EN] =		0xF0,
	[PWRAP_WDT_UNIT] =		0xF8,
	[PWRAP_WDT_SRC_EN] =		0xFC,
	[PWRAP_WDT_SRC_EN_1] =		0x100,
	[PWRAP_WACS2_CMD] =		0xC20,
	[PWRAP_WACS2_RDATA] =		0xC24,
	[PWRAP_WACS2_VLDCLR] =		0xC28,
पूर्ण;

अटल पूर्णांक mt6797_regs[] = अणु
	[PWRAP_MUX_SEL] =		0x0,
	[PWRAP_WRAP_EN] =		0x4,
	[PWRAP_DIO_EN] =		0x8,
	[PWRAP_SIDLY] =			0xC,
	[PWRAP_RDDMY] =			0x10,
	[PWRAP_CSHEXT_WRITE] =		0x18,
	[PWRAP_CSHEXT_READ] =		0x1C,
	[PWRAP_CSLEXT_START] =		0x20,
	[PWRAP_CSLEXT_END] =		0x24,
	[PWRAP_STAUPD_PRD] =		0x28,
	[PWRAP_HARB_HPRIO] =		0x50,
	[PWRAP_HIPRIO_ARB_EN] =		0x54,
	[PWRAP_MAN_EN] =		0x60,
	[PWRAP_MAN_CMD] =		0x64,
	[PWRAP_WACS0_EN] =		0x70,
	[PWRAP_WACS1_EN] =		0x84,
	[PWRAP_WACS2_EN] =		0x98,
	[PWRAP_INIT_DONE2] =		0x9C,
	[PWRAP_WACS2_CMD] =		0xA0,
	[PWRAP_WACS2_RDATA] =		0xA4,
	[PWRAP_WACS2_VLDCLR] =		0xA8,
	[PWRAP_INT_EN] =		0xC0,
	[PWRAP_INT_FLG_RAW] =		0xC4,
	[PWRAP_INT_FLG] =		0xC8,
	[PWRAP_INT_CLR] =		0xCC,
	[PWRAP_TIMER_EN] =		0xF4,
	[PWRAP_WDT_UNIT] =		0xFC,
	[PWRAP_WDT_SRC_EN] =		0x100,
	[PWRAP_DCM_EN] =		0x1CC,
	[PWRAP_DCM_DBC_PRD] =		0x1D4,
पूर्ण;

अटल पूर्णांक mt6873_regs[] = अणु
	[PWRAP_INIT_DONE2] =		0x0,
	[PWRAP_TIMER_EN] =		0x3E0,
	[PWRAP_INT_EN] =		0x448,
	[PWRAP_WACS2_CMD] =		0xC80,
	[PWRAP_SWINF_2_WDATA_31_0] =	0xC84,
	[PWRAP_SWINF_2_RDATA_31_0] =	0xC94,
	[PWRAP_WACS2_VLDCLR] =		0xCA4,
	[PWRAP_WACS2_RDATA] =		0xCA8,
पूर्ण;

अटल पूर्णांक mt7622_regs[] = अणु
	[PWRAP_MUX_SEL] =		0x0,
	[PWRAP_WRAP_EN] =		0x4,
	[PWRAP_DIO_EN] =		0x8,
	[PWRAP_SIDLY] =			0xC,
	[PWRAP_RDDMY] =			0x10,
	[PWRAP_SI_CK_CON] =		0x14,
	[PWRAP_CSHEXT_WRITE] =		0x18,
	[PWRAP_CSHEXT_READ] =		0x1C,
	[PWRAP_CSLEXT_START] =		0x20,
	[PWRAP_CSLEXT_END] =		0x24,
	[PWRAP_STAUPD_PRD] =		0x28,
	[PWRAP_STAUPD_GRPEN] =		0x2C,
	[PWRAP_EINT_STA0_ADR] =		0x30,
	[PWRAP_EINT_STA1_ADR] =		0x34,
	[PWRAP_STA] =			0x38,
	[PWRAP_CLR] =			0x3C,
	[PWRAP_STAUPD_MAN_TRIG] =	0x40,
	[PWRAP_STAUPD_STA] =		0x44,
	[PWRAP_WRAP_STA] =		0x48,
	[PWRAP_HARB_INIT] =		0x4C,
	[PWRAP_HARB_HPRIO] =		0x50,
	[PWRAP_HIPRIO_ARB_EN] =		0x54,
	[PWRAP_HARB_STA0] =		0x58,
	[PWRAP_HARB_STA1] =		0x5C,
	[PWRAP_MAN_EN] =		0x60,
	[PWRAP_MAN_CMD] =		0x64,
	[PWRAP_MAN_RDATA] =		0x68,
	[PWRAP_MAN_VLDCLR] =		0x6C,
	[PWRAP_WACS0_EN] =		0x70,
	[PWRAP_INIT_DONE0] =		0x74,
	[PWRAP_WACS0_CMD] =		0x78,
	[PWRAP_WACS0_RDATA] =		0x7C,
	[PWRAP_WACS0_VLDCLR] =		0x80,
	[PWRAP_WACS1_EN] =		0x84,
	[PWRAP_INIT_DONE1] =		0x88,
	[PWRAP_WACS1_CMD] =		0x8C,
	[PWRAP_WACS1_RDATA] =		0x90,
	[PWRAP_WACS1_VLDCLR] =		0x94,
	[PWRAP_WACS2_EN] =		0x98,
	[PWRAP_INIT_DONE2] =		0x9C,
	[PWRAP_WACS2_CMD] =		0xA0,
	[PWRAP_WACS2_RDATA] =		0xA4,
	[PWRAP_WACS2_VLDCLR] =		0xA8,
	[PWRAP_INT_EN] =		0xAC,
	[PWRAP_INT_FLG_RAW] =		0xB0,
	[PWRAP_INT_FLG] =		0xB4,
	[PWRAP_INT_CLR] =		0xB8,
	[PWRAP_SIG_ADR] =		0xBC,
	[PWRAP_SIG_MODE] =		0xC0,
	[PWRAP_SIG_VALUE] =		0xC4,
	[PWRAP_संक_त्रुटिVAL] =		0xC8,
	[PWRAP_CRC_EN] =		0xCC,
	[PWRAP_TIMER_EN] =		0xD0,
	[PWRAP_TIMER_STA] =		0xD4,
	[PWRAP_WDT_UNIT] =		0xD8,
	[PWRAP_WDT_SRC_EN] =		0xDC,
	[PWRAP_WDT_FLG] =		0xE0,
	[PWRAP_DEBUG_INT_SEL] =		0xE4,
	[PWRAP_DVFS_ADR0] =		0xE8,
	[PWRAP_DVFS_WDATA0] =		0xEC,
	[PWRAP_DVFS_ADR1] =		0xF0,
	[PWRAP_DVFS_WDATA1] =		0xF4,
	[PWRAP_DVFS_ADR2] =		0xF8,
	[PWRAP_DVFS_WDATA2] =		0xFC,
	[PWRAP_DVFS_ADR3] =		0x100,
	[PWRAP_DVFS_WDATA3] =		0x104,
	[PWRAP_DVFS_ADR4] =		0x108,
	[PWRAP_DVFS_WDATA4] =		0x10C,
	[PWRAP_DVFS_ADR5] =		0x110,
	[PWRAP_DVFS_WDATA5] =		0x114,
	[PWRAP_DVFS_ADR6] =		0x118,
	[PWRAP_DVFS_WDATA6] =		0x11C,
	[PWRAP_DVFS_ADR7] =		0x120,
	[PWRAP_DVFS_WDATA7] =		0x124,
	[PWRAP_DVFS_ADR8] =		0x128,
	[PWRAP_DVFS_WDATA8] =		0x12C,
	[PWRAP_DVFS_ADR9] =		0x130,
	[PWRAP_DVFS_WDATA9] =		0x134,
	[PWRAP_DVFS_ADR10] =		0x138,
	[PWRAP_DVFS_WDATA10] =		0x13C,
	[PWRAP_DVFS_ADR11] =		0x140,
	[PWRAP_DVFS_WDATA11] =		0x144,
	[PWRAP_DVFS_ADR12] =		0x148,
	[PWRAP_DVFS_WDATA12] =		0x14C,
	[PWRAP_DVFS_ADR13] =		0x150,
	[PWRAP_DVFS_WDATA13] =		0x154,
	[PWRAP_DVFS_ADR14] =		0x158,
	[PWRAP_DVFS_WDATA14] =		0x15C,
	[PWRAP_DVFS_ADR15] =		0x160,
	[PWRAP_DVFS_WDATA15] =		0x164,
	[PWRAP_SPMINF_STA] =		0x168,
	[PWRAP_CIPHER_KEY_SEL] =	0x16C,
	[PWRAP_CIPHER_IV_SEL] =		0x170,
	[PWRAP_CIPHER_EN] =		0x174,
	[PWRAP_CIPHER_RDY] =		0x178,
	[PWRAP_CIPHER_MODE] =		0x17C,
	[PWRAP_CIPHER_SWRST] =		0x180,
	[PWRAP_DCM_EN] =		0x184,
	[PWRAP_DCM_DBC_PRD] =		0x188,
	[PWRAP_EXT_CK] =		0x18C,
	[PWRAP_ADC_CMD_ADDR] =		0x190,
	[PWRAP_PWRAP_ADC_CMD] =		0x194,
	[PWRAP_ADC_RDATA_ADDR] =	0x198,
	[PWRAP_GPS_STA] =		0x19C,
	[PWRAP_SW_RST] =		0x1A0,
	[PWRAP_DVFS_STEP_CTRL0] =	0x238,
	[PWRAP_DVFS_STEP_CTRL1] =	0x23C,
	[PWRAP_DVFS_STEP_CTRL2] =	0x240,
	[PWRAP_SPI2_CTRL] =		0x244,
पूर्ण;

अटल पूर्णांक mt8135_regs[] = अणु
	[PWRAP_MUX_SEL] =		0x0,
	[PWRAP_WRAP_EN] =		0x4,
	[PWRAP_DIO_EN] =		0x8,
	[PWRAP_SIDLY] =			0xc,
	[PWRAP_CSHEXT] =		0x10,
	[PWRAP_CSHEXT_WRITE] =		0x14,
	[PWRAP_CSHEXT_READ] =		0x18,
	[PWRAP_CSLEXT_START] =		0x1c,
	[PWRAP_CSLEXT_END] =		0x20,
	[PWRAP_STAUPD_PRD] =		0x24,
	[PWRAP_STAUPD_GRPEN] =		0x28,
	[PWRAP_STAUPD_MAN_TRIG] =	0x2c,
	[PWRAP_STAUPD_STA] =		0x30,
	[PWRAP_EVENT_IN_EN] =		0x34,
	[PWRAP_EVENT_DST_EN] =		0x38,
	[PWRAP_WRAP_STA] =		0x3c,
	[PWRAP_RRARB_INIT] =		0x40,
	[PWRAP_RRARB_EN] =		0x44,
	[PWRAP_RRARB_STA0] =		0x48,
	[PWRAP_RRARB_STA1] =		0x4c,
	[PWRAP_HARB_INIT] =		0x50,
	[PWRAP_HARB_HPRIO] =		0x54,
	[PWRAP_HIPRIO_ARB_EN] =		0x58,
	[PWRAP_HARB_STA0] =		0x5c,
	[PWRAP_HARB_STA1] =		0x60,
	[PWRAP_MAN_EN] =		0x64,
	[PWRAP_MAN_CMD] =		0x68,
	[PWRAP_MAN_RDATA] =		0x6c,
	[PWRAP_MAN_VLDCLR] =		0x70,
	[PWRAP_WACS0_EN] =		0x74,
	[PWRAP_INIT_DONE0] =		0x78,
	[PWRAP_WACS0_CMD] =		0x7c,
	[PWRAP_WACS0_RDATA] =		0x80,
	[PWRAP_WACS0_VLDCLR] =		0x84,
	[PWRAP_WACS1_EN] =		0x88,
	[PWRAP_INIT_DONE1] =		0x8c,
	[PWRAP_WACS1_CMD] =		0x90,
	[PWRAP_WACS1_RDATA] =		0x94,
	[PWRAP_WACS1_VLDCLR] =		0x98,
	[PWRAP_WACS2_EN] =		0x9c,
	[PWRAP_INIT_DONE2] =		0xa0,
	[PWRAP_WACS2_CMD] =		0xa4,
	[PWRAP_WACS2_RDATA] =		0xa8,
	[PWRAP_WACS2_VLDCLR] =		0xac,
	[PWRAP_INT_EN] =		0xb0,
	[PWRAP_INT_FLG_RAW] =		0xb4,
	[PWRAP_INT_FLG] =		0xb8,
	[PWRAP_INT_CLR] =		0xbc,
	[PWRAP_SIG_ADR] =		0xc0,
	[PWRAP_SIG_MODE] =		0xc4,
	[PWRAP_SIG_VALUE] =		0xc8,
	[PWRAP_संक_त्रुटिVAL] =		0xcc,
	[PWRAP_CRC_EN] =		0xd0,
	[PWRAP_EVENT_STA] =		0xd4,
	[PWRAP_EVENT_STACLR] =		0xd8,
	[PWRAP_TIMER_EN] =		0xdc,
	[PWRAP_TIMER_STA] =		0xe0,
	[PWRAP_WDT_UNIT] =		0xe4,
	[PWRAP_WDT_SRC_EN] =		0xe8,
	[PWRAP_WDT_FLG] =		0xec,
	[PWRAP_DEBUG_INT_SEL] =		0xf0,
	[PWRAP_CIPHER_KEY_SEL] =	0x134,
	[PWRAP_CIPHER_IV_SEL] =		0x138,
	[PWRAP_CIPHER_LOAD] =		0x13c,
	[PWRAP_CIPHER_START] =		0x140,
	[PWRAP_CIPHER_RDY] =		0x144,
	[PWRAP_CIPHER_MODE] =		0x148,
	[PWRAP_CIPHER_SWRST] =		0x14c,
	[PWRAP_DCM_EN] =		0x15c,
	[PWRAP_DCM_DBC_PRD] =		0x160,
पूर्ण;

अटल पूर्णांक mt8173_regs[] = अणु
	[PWRAP_MUX_SEL] =		0x0,
	[PWRAP_WRAP_EN] =		0x4,
	[PWRAP_DIO_EN] =		0x8,
	[PWRAP_SIDLY] =			0xc,
	[PWRAP_RDDMY] =			0x10,
	[PWRAP_SI_CK_CON] =		0x14,
	[PWRAP_CSHEXT_WRITE] =		0x18,
	[PWRAP_CSHEXT_READ] =		0x1c,
	[PWRAP_CSLEXT_START] =		0x20,
	[PWRAP_CSLEXT_END] =		0x24,
	[PWRAP_STAUPD_PRD] =		0x28,
	[PWRAP_STAUPD_GRPEN] =		0x2c,
	[PWRAP_STAUPD_MAN_TRIG] =	0x40,
	[PWRAP_STAUPD_STA] =		0x44,
	[PWRAP_WRAP_STA] =		0x48,
	[PWRAP_HARB_INIT] =		0x4c,
	[PWRAP_HARB_HPRIO] =		0x50,
	[PWRAP_HIPRIO_ARB_EN] =		0x54,
	[PWRAP_HARB_STA0] =		0x58,
	[PWRAP_HARB_STA1] =		0x5c,
	[PWRAP_MAN_EN] =		0x60,
	[PWRAP_MAN_CMD] =		0x64,
	[PWRAP_MAN_RDATA] =		0x68,
	[PWRAP_MAN_VLDCLR] =		0x6c,
	[PWRAP_WACS0_EN] =		0x70,
	[PWRAP_INIT_DONE0] =		0x74,
	[PWRAP_WACS0_CMD] =		0x78,
	[PWRAP_WACS0_RDATA] =		0x7c,
	[PWRAP_WACS0_VLDCLR] =		0x80,
	[PWRAP_WACS1_EN] =		0x84,
	[PWRAP_INIT_DONE1] =		0x88,
	[PWRAP_WACS1_CMD] =		0x8c,
	[PWRAP_WACS1_RDATA] =		0x90,
	[PWRAP_WACS1_VLDCLR] =		0x94,
	[PWRAP_WACS2_EN] =		0x98,
	[PWRAP_INIT_DONE2] =		0x9c,
	[PWRAP_WACS2_CMD] =		0xa0,
	[PWRAP_WACS2_RDATA] =		0xa4,
	[PWRAP_WACS2_VLDCLR] =		0xa8,
	[PWRAP_INT_EN] =		0xac,
	[PWRAP_INT_FLG_RAW] =		0xb0,
	[PWRAP_INT_FLG] =		0xb4,
	[PWRAP_INT_CLR] =		0xb8,
	[PWRAP_SIG_ADR] =		0xbc,
	[PWRAP_SIG_MODE] =		0xc0,
	[PWRAP_SIG_VALUE] =		0xc4,
	[PWRAP_संक_त्रुटिVAL] =		0xc8,
	[PWRAP_CRC_EN] =		0xcc,
	[PWRAP_TIMER_EN] =		0xd0,
	[PWRAP_TIMER_STA] =		0xd4,
	[PWRAP_WDT_UNIT] =		0xd8,
	[PWRAP_WDT_SRC_EN] =		0xdc,
	[PWRAP_WDT_FLG] =		0xe0,
	[PWRAP_DEBUG_INT_SEL] =		0xe4,
	[PWRAP_DVFS_ADR0] =		0xe8,
	[PWRAP_DVFS_WDATA0] =		0xec,
	[PWRAP_DVFS_ADR1] =		0xf0,
	[PWRAP_DVFS_WDATA1] =		0xf4,
	[PWRAP_DVFS_ADR2] =		0xf8,
	[PWRAP_DVFS_WDATA2] =		0xfc,
	[PWRAP_DVFS_ADR3] =		0x100,
	[PWRAP_DVFS_WDATA3] =		0x104,
	[PWRAP_DVFS_ADR4] =		0x108,
	[PWRAP_DVFS_WDATA4] =		0x10c,
	[PWRAP_DVFS_ADR5] =		0x110,
	[PWRAP_DVFS_WDATA5] =		0x114,
	[PWRAP_DVFS_ADR6] =		0x118,
	[PWRAP_DVFS_WDATA6] =		0x11c,
	[PWRAP_DVFS_ADR7] =		0x120,
	[PWRAP_DVFS_WDATA7] =		0x124,
	[PWRAP_SPMINF_STA] =		0x128,
	[PWRAP_CIPHER_KEY_SEL] =	0x12c,
	[PWRAP_CIPHER_IV_SEL] =		0x130,
	[PWRAP_CIPHER_EN] =		0x134,
	[PWRAP_CIPHER_RDY] =		0x138,
	[PWRAP_CIPHER_MODE] =		0x13c,
	[PWRAP_CIPHER_SWRST] =		0x140,
	[PWRAP_DCM_EN] =		0x144,
	[PWRAP_DCM_DBC_PRD] =		0x148,
पूर्ण;

अटल पूर्णांक mt8183_regs[] = अणु
	[PWRAP_MUX_SEL] =			0x0,
	[PWRAP_WRAP_EN] =			0x4,
	[PWRAP_DIO_EN] =			0x8,
	[PWRAP_SI_SAMPLE_CTRL] =		0xC,
	[PWRAP_RDDMY] =				0x14,
	[PWRAP_CSHEXT_WRITE] =			0x18,
	[PWRAP_CSHEXT_READ] =			0x1C,
	[PWRAP_CSLEXT_WRITE] =			0x20,
	[PWRAP_CSLEXT_READ] =			0x24,
	[PWRAP_EXT_CK_WRITE] =			0x28,
	[PWRAP_STAUPD_CTRL] =			0x30,
	[PWRAP_STAUPD_GRPEN] =			0x34,
	[PWRAP_EINT_STA0_ADR] =			0x38,
	[PWRAP_HARB_HPRIO] =			0x5C,
	[PWRAP_HIPRIO_ARB_EN] =			0x60,
	[PWRAP_MAN_EN] =			0x70,
	[PWRAP_MAN_CMD] =			0x74,
	[PWRAP_WACS0_EN] =			0x80,
	[PWRAP_INIT_DONE0] =			0x84,
	[PWRAP_WACS1_EN] =			0x88,
	[PWRAP_INIT_DONE1] =			0x8C,
	[PWRAP_WACS2_EN] =			0x90,
	[PWRAP_INIT_DONE2] =			0x94,
	[PWRAP_WACS_P2P_EN] =			0xA0,
	[PWRAP_INIT_DONE_P2P] =			0xA4,
	[PWRAP_WACS_MD32_EN] =			0xA8,
	[PWRAP_INIT_DONE_MD32] =		0xAC,
	[PWRAP_INT_EN] =			0xB0,
	[PWRAP_INT_FLG] =			0xB8,
	[PWRAP_INT_CLR] =			0xBC,
	[PWRAP_INT1_EN] =			0xC0,
	[PWRAP_INT1_FLG] =			0xC8,
	[PWRAP_INT1_CLR] =			0xCC,
	[PWRAP_SIG_ADR] =			0xD0,
	[PWRAP_CRC_EN] =			0xE0,
	[PWRAP_TIMER_EN] =			0xE4,
	[PWRAP_WDT_UNIT] =			0xEC,
	[PWRAP_WDT_SRC_EN] =			0xF0,
	[PWRAP_WDT_SRC_EN_1] =			0xF4,
	[PWRAP_INT_GPS_AUXADC_CMD_ADDR] =	0x1DC,
	[PWRAP_INT_GPS_AUXADC_CMD] =		0x1E0,
	[PWRAP_INT_GPS_AUXADC_RDATA_ADDR] =	0x1E4,
	[PWRAP_EXT_GPS_AUXADC_RDATA_ADDR] =	0x1E8,
	[PWRAP_GPSINF_0_STA] =			0x1EC,
	[PWRAP_GPSINF_1_STA] =			0x1F0,
	[PWRAP_WACS2_CMD] =			0xC20,
	[PWRAP_WACS2_RDATA] =			0xC24,
	[PWRAP_WACS2_VLDCLR] =			0xC28,
पूर्ण;

अटल पूर्णांक mt8516_regs[] = अणु
	[PWRAP_MUX_SEL] =		0x0,
	[PWRAP_WRAP_EN] =		0x4,
	[PWRAP_DIO_EN] =		0x8,
	[PWRAP_SIDLY] =			0xc,
	[PWRAP_RDDMY] =			0x10,
	[PWRAP_SI_CK_CON] =		0x14,
	[PWRAP_CSHEXT_WRITE] =		0x18,
	[PWRAP_CSHEXT_READ] =		0x1c,
	[PWRAP_CSLEXT_START] =		0x20,
	[PWRAP_CSLEXT_END] =		0x24,
	[PWRAP_STAUPD_PRD] =		0x28,
	[PWRAP_STAUPD_GRPEN] =		0x2c,
	[PWRAP_STAUPD_MAN_TRIG] =	0x40,
	[PWRAP_STAUPD_STA] =		0x44,
	[PWRAP_WRAP_STA] =		0x48,
	[PWRAP_HARB_INIT] =		0x4c,
	[PWRAP_HARB_HPRIO] =		0x50,
	[PWRAP_HIPRIO_ARB_EN] =		0x54,
	[PWRAP_HARB_STA0] =		0x58,
	[PWRAP_HARB_STA1] =		0x5c,
	[PWRAP_MAN_EN] =		0x60,
	[PWRAP_MAN_CMD] =		0x64,
	[PWRAP_MAN_RDATA] =		0x68,
	[PWRAP_MAN_VLDCLR] =		0x6c,
	[PWRAP_WACS0_EN] =		0x70,
	[PWRAP_INIT_DONE0] =		0x74,
	[PWRAP_WACS0_CMD] =		0x78,
	[PWRAP_WACS0_RDATA] =		0x7c,
	[PWRAP_WACS0_VLDCLR] =		0x80,
	[PWRAP_WACS1_EN] =		0x84,
	[PWRAP_INIT_DONE1] =		0x88,
	[PWRAP_WACS1_CMD] =		0x8c,
	[PWRAP_WACS1_RDATA] =		0x90,
	[PWRAP_WACS1_VLDCLR] =		0x94,
	[PWRAP_WACS2_EN] =		0x98,
	[PWRAP_INIT_DONE2] =		0x9c,
	[PWRAP_WACS2_CMD] =		0xa0,
	[PWRAP_WACS2_RDATA] =		0xa4,
	[PWRAP_WACS2_VLDCLR] =		0xa8,
	[PWRAP_INT_EN] =		0xac,
	[PWRAP_INT_FLG_RAW] =		0xb0,
	[PWRAP_INT_FLG] =		0xb4,
	[PWRAP_INT_CLR] =		0xb8,
	[PWRAP_SIG_ADR] =		0xbc,
	[PWRAP_SIG_MODE] =		0xc0,
	[PWRAP_SIG_VALUE] =		0xc4,
	[PWRAP_संक_त्रुटिVAL] =		0xc8,
	[PWRAP_CRC_EN] =		0xcc,
	[PWRAP_TIMER_EN] =		0xd0,
	[PWRAP_TIMER_STA] =		0xd4,
	[PWRAP_WDT_UNIT] =		0xd8,
	[PWRAP_WDT_SRC_EN] =		0xdc,
	[PWRAP_WDT_FLG] =		0xe0,
	[PWRAP_DEBUG_INT_SEL] =		0xe4,
	[PWRAP_DVFS_ADR0] =		0xe8,
	[PWRAP_DVFS_WDATA0] =		0xec,
	[PWRAP_DVFS_ADR1] =		0xf0,
	[PWRAP_DVFS_WDATA1] =		0xf4,
	[PWRAP_DVFS_ADR2] =		0xf8,
	[PWRAP_DVFS_WDATA2] =		0xfc,
	[PWRAP_DVFS_ADR3] =		0x100,
	[PWRAP_DVFS_WDATA3] =		0x104,
	[PWRAP_DVFS_ADR4] =		0x108,
	[PWRAP_DVFS_WDATA4] =		0x10c,
	[PWRAP_DVFS_ADR5] =		0x110,
	[PWRAP_DVFS_WDATA5] =		0x114,
	[PWRAP_DVFS_ADR6] =		0x118,
	[PWRAP_DVFS_WDATA6] =		0x11c,
	[PWRAP_DVFS_ADR7] =		0x120,
	[PWRAP_DVFS_WDATA7] =		0x124,
	[PWRAP_SPMINF_STA] =		0x128,
	[PWRAP_CIPHER_KEY_SEL] =	0x12c,
	[PWRAP_CIPHER_IV_SEL] =		0x130,
	[PWRAP_CIPHER_EN] =		0x134,
	[PWRAP_CIPHER_RDY] =		0x138,
	[PWRAP_CIPHER_MODE] =		0x13c,
	[PWRAP_CIPHER_SWRST] =		0x140,
	[PWRAP_DCM_EN] =		0x144,
	[PWRAP_DCM_DBC_PRD] =		0x148,
	[PWRAP_SW_RST] =		0x168,
	[PWRAP_OP_TYPE] =		0x16c,
	[PWRAP_MSB_FIRST] =		0x170,
पूर्ण;

क्रमागत pmic_type अणु
	PMIC_MT6323,
	PMIC_MT6351,
	PMIC_MT6357,
	PMIC_MT6358,
	PMIC_MT6359,
	PMIC_MT6380,
	PMIC_MT6397,
पूर्ण;

क्रमागत pwrap_type अणु
	PWRAP_MT2701,
	PWRAP_MT6765,
	PWRAP_MT6779,
	PWRAP_MT6797,
	PWRAP_MT6873,
	PWRAP_MT7622,
	PWRAP_MT8135,
	PWRAP_MT8173,
	PWRAP_MT8183,
	PWRAP_MT8516,
पूर्ण;

काष्ठा pmic_wrapper;
काष्ठा pwrap_slv_type अणु
	स्थिर u32 *dew_regs;
	क्रमागत pmic_type type;
	स्थिर काष्ठा regmap_config *regmap;
	/* Flags indicating the capability क्रम the target slave */
	u32 caps;
	/*
	 * pwrap operations are highly associated with the PMIC types,
	 * so the poपूर्णांकers added increases flexibility allowing determination
	 * which type is used by the detection through device tree.
	 */
	पूर्णांक (*pwrap_पढ़ो)(काष्ठा pmic_wrapper *wrp, u32 adr, u32 *rdata);
	पूर्णांक (*pwrap_ग_लिखो)(काष्ठा pmic_wrapper *wrp, u32 adr, u32 wdata);
पूर्ण;

काष्ठा pmic_wrapper अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा regmap *regmap;
	स्थिर काष्ठा pmic_wrapper_type *master;
	स्थिर काष्ठा pwrap_slv_type *slave;
	काष्ठा clk *clk_spi;
	काष्ठा clk *clk_wrap;
	काष्ठा reset_control *rstc;

	काष्ठा reset_control *rstc_bridge;
	व्योम __iomem *bridge_base;
पूर्ण;

काष्ठा pmic_wrapper_type अणु
	पूर्णांक *regs;
	क्रमागत pwrap_type type;
	u32 arb_en_all;
	u32 पूर्णांक_en_all;
	u32 पूर्णांक1_en_all;
	u32 spi_w;
	u32 wdt_src;
	/* Flags indicating the capability क्रम the target pwrap */
	u32 caps;
	पूर्णांक (*init_reg_घड़ी)(काष्ठा pmic_wrapper *wrp);
	पूर्णांक (*init_soc_specअगरic)(काष्ठा pmic_wrapper *wrp);
पूर्ण;

अटल u32 pwrap_पढ़ोl(काष्ठा pmic_wrapper *wrp, क्रमागत pwrap_regs reg)
अणु
	वापस पढ़ोl(wrp->base + wrp->master->regs[reg]);
पूर्ण

अटल व्योम pwrap_ग_लिखोl(काष्ठा pmic_wrapper *wrp, u32 val, क्रमागत pwrap_regs reg)
अणु
	ग_लिखोl(val, wrp->base + wrp->master->regs[reg]);
पूर्ण

अटल u32 pwrap_get_fsm_state(काष्ठा pmic_wrapper *wrp)
अणु
	u32 val;

	val = pwrap_पढ़ोl(wrp, PWRAP_WACS2_RDATA);
	अगर (HAS_CAP(wrp->master->caps, PWRAP_CAP_ARB))
		वापस PWRAP_GET_WACS_ARB_FSM(val);
	अन्यथा
		वापस PWRAP_GET_WACS_FSM(val);
पूर्ण

अटल bool pwrap_is_fsm_idle(काष्ठा pmic_wrapper *wrp)
अणु
	वापस pwrap_get_fsm_state(wrp) == PWRAP_WACS_FSM_IDLE;
पूर्ण

अटल bool pwrap_is_fsm_vldclr(काष्ठा pmic_wrapper *wrp)
अणु
	वापस pwrap_get_fsm_state(wrp) == PWRAP_WACS_FSM_WFVLDCLR;
पूर्ण

/*
 * Timeout issue someबार caused by the last पढ़ो command
 * failed because pmic wrap could not got the FSM_VLDCLR
 * in समय after finishing WACS2_CMD. It made state machine
 * still on FSM_VLDCLR and समयout next समय.
 * Check the status of FSM and clear the vldclr to recovery the
 * error.
 */
अटल अंतरभूत व्योम pwrap_leave_fsm_vldclr(काष्ठा pmic_wrapper *wrp)
अणु
	अगर (pwrap_is_fsm_vldclr(wrp))
		pwrap_ग_लिखोl(wrp, 1, PWRAP_WACS2_VLDCLR);
पूर्ण

अटल bool pwrap_is_sync_idle(काष्ठा pmic_wrapper *wrp)
अणु
	वापस pwrap_पढ़ोl(wrp, PWRAP_WACS2_RDATA) & PWRAP_STATE_SYNC_IDLE0;
पूर्ण

अटल bool pwrap_is_fsm_idle_and_sync_idle(काष्ठा pmic_wrapper *wrp)
अणु
	u32 val = pwrap_पढ़ोl(wrp, PWRAP_WACS2_RDATA);

	वापस (PWRAP_GET_WACS_FSM(val) == PWRAP_WACS_FSM_IDLE) &&
		(val & PWRAP_STATE_SYNC_IDLE0);
पूर्ण

अटल पूर्णांक pwrap_रुको_क्रम_state(काष्ठा pmic_wrapper *wrp,
		bool (*fp)(काष्ठा pmic_wrapper *))
अणु
	अचिन्हित दीर्घ समयout;

	समयout = jअगरfies + usecs_to_jअगरfies(10000);

	करो अणु
		अगर (समय_after(jअगरfies, समयout))
			वापस fp(wrp) ? 0 : -ETIMEDOUT;
		अगर (fp(wrp))
			वापस 0;
	पूर्ण जबतक (1);
पूर्ण

अटल पूर्णांक pwrap_पढ़ो16(काष्ठा pmic_wrapper *wrp, u32 adr, u32 *rdata)
अणु
	पूर्णांक ret;
	u32 val;

	ret = pwrap_रुको_क्रम_state(wrp, pwrap_is_fsm_idle);
	अगर (ret) अणु
		pwrap_leave_fsm_vldclr(wrp);
		वापस ret;
	पूर्ण

	अगर (HAS_CAP(wrp->master->caps, PWRAP_CAP_ARB))
		val = adr;
	अन्यथा
		val = (adr >> 1) << 16;
	pwrap_ग_लिखोl(wrp, val, PWRAP_WACS2_CMD);

	ret = pwrap_रुको_क्रम_state(wrp, pwrap_is_fsm_vldclr);
	अगर (ret)
		वापस ret;

	अगर (HAS_CAP(wrp->master->caps, PWRAP_CAP_ARB))
		val = pwrap_पढ़ोl(wrp, PWRAP_SWINF_2_RDATA_31_0);
	अन्यथा
		val = pwrap_पढ़ोl(wrp, PWRAP_WACS2_RDATA);
	*rdata = PWRAP_GET_WACS_RDATA(val);

	pwrap_ग_लिखोl(wrp, 1, PWRAP_WACS2_VLDCLR);

	वापस 0;
पूर्ण

अटल पूर्णांक pwrap_पढ़ो32(काष्ठा pmic_wrapper *wrp, u32 adr, u32 *rdata)
अणु
	पूर्णांक ret, msb;

	*rdata = 0;
	क्रम (msb = 0; msb < 2; msb++) अणु
		ret = pwrap_रुको_क्रम_state(wrp, pwrap_is_fsm_idle);
		अगर (ret) अणु
			pwrap_leave_fsm_vldclr(wrp);
			वापस ret;
		पूर्ण

		pwrap_ग_लिखोl(wrp, ((msb << 30) | (adr << 16)),
			     PWRAP_WACS2_CMD);

		ret = pwrap_रुको_क्रम_state(wrp, pwrap_is_fsm_vldclr);
		अगर (ret)
			वापस ret;

		*rdata += (PWRAP_GET_WACS_RDATA(pwrap_पढ़ोl(wrp,
			   PWRAP_WACS2_RDATA)) << (16 * msb));

		pwrap_ग_लिखोl(wrp, 1, PWRAP_WACS2_VLDCLR);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pwrap_पढ़ो(काष्ठा pmic_wrapper *wrp, u32 adr, u32 *rdata)
अणु
	वापस wrp->slave->pwrap_पढ़ो(wrp, adr, rdata);
पूर्ण

अटल पूर्णांक pwrap_ग_लिखो16(काष्ठा pmic_wrapper *wrp, u32 adr, u32 wdata)
अणु
	पूर्णांक ret;

	ret = pwrap_रुको_क्रम_state(wrp, pwrap_is_fsm_idle);
	अगर (ret) अणु
		pwrap_leave_fsm_vldclr(wrp);
		वापस ret;
	पूर्ण

	अगर (HAS_CAP(wrp->master->caps, PWRAP_CAP_ARB)) अणु
		pwrap_ग_लिखोl(wrp, wdata, PWRAP_SWINF_2_WDATA_31_0);
		pwrap_ग_लिखोl(wrp, BIT(29) | adr, PWRAP_WACS2_CMD);
	पूर्ण अन्यथा अणु
		pwrap_ग_लिखोl(wrp, BIT(31) | ((adr >> 1) << 16) | wdata,
			     PWRAP_WACS2_CMD);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pwrap_ग_लिखो32(काष्ठा pmic_wrapper *wrp, u32 adr, u32 wdata)
अणु
	पूर्णांक ret, msb, rdata;

	क्रम (msb = 0; msb < 2; msb++) अणु
		ret = pwrap_रुको_क्रम_state(wrp, pwrap_is_fsm_idle);
		अगर (ret) अणु
			pwrap_leave_fsm_vldclr(wrp);
			वापस ret;
		पूर्ण

		pwrap_ग_लिखोl(wrp, (1 << 31) | (msb << 30) | (adr << 16) |
			     ((wdata >> (msb * 16)) & 0xffff),
			     PWRAP_WACS2_CMD);

		/*
		 * The pwrap_पढ़ो operation is the requirement of hardware used
		 * क्रम the synchronization between two successive 16-bit
		 * pwrap_ग_लिखोl operations composing one 32-bit bus writing.
		 * Otherwise, we'll find the result fails on the lower 16-bit
		 * pwrap writing.
		 */
		अगर (!msb)
			pwrap_पढ़ो(wrp, adr, &rdata);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pwrap_ग_लिखो(काष्ठा pmic_wrapper *wrp, u32 adr, u32 wdata)
अणु
	वापस wrp->slave->pwrap_ग_लिखो(wrp, adr, wdata);
पूर्ण

अटल पूर्णांक pwrap_regmap_पढ़ो(व्योम *context, u32 adr, u32 *rdata)
अणु
	वापस pwrap_पढ़ो(context, adr, rdata);
पूर्ण

अटल पूर्णांक pwrap_regmap_ग_लिखो(व्योम *context, u32 adr, u32 wdata)
अणु
	वापस pwrap_ग_लिखो(context, adr, wdata);
पूर्ण

अटल पूर्णांक pwrap_reset_spislave(काष्ठा pmic_wrapper *wrp)
अणु
	पूर्णांक ret, i;

	pwrap_ग_लिखोl(wrp, 0, PWRAP_HIPRIO_ARB_EN);
	pwrap_ग_लिखोl(wrp, 0, PWRAP_WRAP_EN);
	pwrap_ग_लिखोl(wrp, 1, PWRAP_MUX_SEL);
	pwrap_ग_लिखोl(wrp, 1, PWRAP_MAN_EN);
	pwrap_ग_लिखोl(wrp, 0, PWRAP_DIO_EN);

	pwrap_ग_लिखोl(wrp, wrp->master->spi_w | PWRAP_MAN_CMD_OP_CSL,
			PWRAP_MAN_CMD);
	pwrap_ग_लिखोl(wrp, wrp->master->spi_w | PWRAP_MAN_CMD_OP_OUTS,
			PWRAP_MAN_CMD);
	pwrap_ग_लिखोl(wrp, wrp->master->spi_w | PWRAP_MAN_CMD_OP_CSH,
			PWRAP_MAN_CMD);

	क्रम (i = 0; i < 4; i++)
		pwrap_ग_लिखोl(wrp, wrp->master->spi_w | PWRAP_MAN_CMD_OP_OUTS,
				PWRAP_MAN_CMD);

	ret = pwrap_रुको_क्रम_state(wrp, pwrap_is_sync_idle);
	अगर (ret) अणु
		dev_err(wrp->dev, "%s fail, ret=%d\n", __func__, ret);
		वापस ret;
	पूर्ण

	pwrap_ग_लिखोl(wrp, 0, PWRAP_MAN_EN);
	pwrap_ग_लिखोl(wrp, 0, PWRAP_MUX_SEL);

	वापस 0;
पूर्ण

/*
 * pwrap_init_sidly - configure serial input delay
 *
 * This configures the serial input delay. We can configure 0, 2, 4 or 6ns
 * delay. Do a पढ़ो test with all possible values and chose the best delay.
 */
अटल पूर्णांक pwrap_init_sidly(काष्ठा pmic_wrapper *wrp)
अणु
	u32 rdata;
	u32 i;
	u32 pass = 0;
	चिन्हित अक्षर dly[16] = अणु
		-1, 0, 1, 0, 2, -1, 1, 1, 3, -1, -1, -1, 3, -1, 2, 1
	पूर्ण;

	क्रम (i = 0; i < 4; i++) अणु
		pwrap_ग_लिखोl(wrp, i, PWRAP_SIDLY);
		pwrap_पढ़ो(wrp, wrp->slave->dew_regs[PWRAP_DEW_READ_TEST],
			   &rdata);
		अगर (rdata == PWRAP_DEW_READ_TEST_VAL) अणु
			dev_dbg(wrp->dev, "[Read Test] pass, SIDLY=%x\n", i);
			pass |= 1 << i;
		पूर्ण
	पूर्ण

	अगर (dly[pass] < 0) अणु
		dev_err(wrp->dev, "sidly pass range 0x%x not continuous\n",
				pass);
		वापस -EIO;
	पूर्ण

	pwrap_ग_लिखोl(wrp, dly[pass], PWRAP_SIDLY);

	वापस 0;
पूर्ण

अटल पूर्णांक pwrap_init_dual_io(काष्ठा pmic_wrapper *wrp)
अणु
	पूर्णांक ret;
	u32 rdata;

	/* Enable dual IO mode */
	pwrap_ग_लिखो(wrp, wrp->slave->dew_regs[PWRAP_DEW_DIO_EN], 1);

	/* Check IDLE & INIT_DONE in advance */
	ret = pwrap_रुको_क्रम_state(wrp,
				   pwrap_is_fsm_idle_and_sync_idle);
	अगर (ret) अणु
		dev_err(wrp->dev, "%s fail, ret=%d\n", __func__, ret);
		वापस ret;
	पूर्ण

	pwrap_ग_लिखोl(wrp, 1, PWRAP_DIO_EN);

	/* Read Test */
	pwrap_पढ़ो(wrp,
		   wrp->slave->dew_regs[PWRAP_DEW_READ_TEST], &rdata);
	अगर (rdata != PWRAP_DEW_READ_TEST_VAL) अणु
		dev_err(wrp->dev,
			"Read failed on DIO mode: 0x%04x!=0x%04x\n",
			PWRAP_DEW_READ_TEST_VAL, rdata);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * pwrap_init_chip_select_ext is used to configure CS extension समय क्रम each
 * phase during data transactions on the pwrap bus.
 */
अटल व्योम pwrap_init_chip_select_ext(काष्ठा pmic_wrapper *wrp, u8 hext_ग_लिखो,
				       u8 hext_पढ़ो, u8 lext_start,
				       u8 lext_end)
अणु
	/*
	 * After finishing a ग_लिखो and पढ़ो transaction, extends CS high समय
	 * to be at least xT of BUS CLK as hext_ग_लिखो and hext_पढ़ो specअगरies
	 * respectively.
	 */
	pwrap_ग_लिखोl(wrp, hext_ग_लिखो, PWRAP_CSHEXT_WRITE);
	pwrap_ग_लिखोl(wrp, hext_पढ़ो, PWRAP_CSHEXT_READ);

	/*
	 * Extends CS low समय after CSL and beक्रमe CSH command to be at
	 * least xT of BUS CLK as lext_start and lext_end specअगरies
	 * respectively.
	 */
	pwrap_ग_लिखोl(wrp, lext_start, PWRAP_CSLEXT_START);
	pwrap_ग_लिखोl(wrp, lext_end, PWRAP_CSLEXT_END);
पूर्ण

अटल पूर्णांक pwrap_common_init_reg_घड़ी(काष्ठा pmic_wrapper *wrp)
अणु
	चयन (wrp->master->type) अणु
	हाल PWRAP_MT8173:
		pwrap_init_chip_select_ext(wrp, 0, 4, 2, 2);
		अवरोध;
	हाल PWRAP_MT8135:
		pwrap_ग_लिखोl(wrp, 0x4, PWRAP_CSHEXT);
		pwrap_init_chip_select_ext(wrp, 0, 4, 0, 0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pwrap_mt2701_init_reg_घड़ी(काष्ठा pmic_wrapper *wrp)
अणु
	चयन (wrp->slave->type) अणु
	हाल PMIC_MT6397:
		pwrap_ग_लिखोl(wrp, 0xc, PWRAP_RDDMY);
		pwrap_init_chip_select_ext(wrp, 4, 0, 2, 2);
		अवरोध;

	हाल PMIC_MT6323:
		pwrap_ग_लिखोl(wrp, 0x8, PWRAP_RDDMY);
		pwrap_ग_लिखो(wrp, wrp->slave->dew_regs[PWRAP_DEW_RDDMY_NO],
			    0x8);
		pwrap_init_chip_select_ext(wrp, 5, 0, 2, 2);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool pwrap_is_cipher_पढ़ोy(काष्ठा pmic_wrapper *wrp)
अणु
	वापस pwrap_पढ़ोl(wrp, PWRAP_CIPHER_RDY) & 1;
पूर्ण

अटल bool pwrap_is_pmic_cipher_पढ़ोy(काष्ठा pmic_wrapper *wrp)
अणु
	u32 rdata;
	पूर्णांक ret;

	ret = pwrap_पढ़ो(wrp, wrp->slave->dew_regs[PWRAP_DEW_CIPHER_RDY],
			 &rdata);
	अगर (ret)
		वापस false;

	वापस rdata == 1;
पूर्ण

अटल पूर्णांक pwrap_init_cipher(काष्ठा pmic_wrapper *wrp)
अणु
	पूर्णांक ret;
	u32 rdata = 0;

	pwrap_ग_लिखोl(wrp, 0x1, PWRAP_CIPHER_SWRST);
	pwrap_ग_लिखोl(wrp, 0x0, PWRAP_CIPHER_SWRST);
	pwrap_ग_लिखोl(wrp, 0x1, PWRAP_CIPHER_KEY_SEL);
	pwrap_ग_लिखोl(wrp, 0x2, PWRAP_CIPHER_IV_SEL);

	चयन (wrp->master->type) अणु
	हाल PWRAP_MT8135:
		pwrap_ग_लिखोl(wrp, 1, PWRAP_CIPHER_LOAD);
		pwrap_ग_लिखोl(wrp, 1, PWRAP_CIPHER_START);
		अवरोध;
	हाल PWRAP_MT2701:
	हाल PWRAP_MT6765:
	हाल PWRAP_MT6779:
	हाल PWRAP_MT6797:
	हाल PWRAP_MT8173:
	हाल PWRAP_MT8516:
		pwrap_ग_लिखोl(wrp, 1, PWRAP_CIPHER_EN);
		अवरोध;
	हाल PWRAP_MT7622:
		pwrap_ग_लिखोl(wrp, 0, PWRAP_CIPHER_EN);
		अवरोध;
	हाल PWRAP_MT6873:
	हाल PWRAP_MT8183:
		अवरोध;
	पूर्ण

	/* Config cipher mode @PMIC */
	pwrap_ग_लिखो(wrp, wrp->slave->dew_regs[PWRAP_DEW_CIPHER_SWRST], 0x1);
	pwrap_ग_लिखो(wrp, wrp->slave->dew_regs[PWRAP_DEW_CIPHER_SWRST], 0x0);
	pwrap_ग_लिखो(wrp, wrp->slave->dew_regs[PWRAP_DEW_CIPHER_KEY_SEL], 0x1);
	pwrap_ग_लिखो(wrp, wrp->slave->dew_regs[PWRAP_DEW_CIPHER_IV_SEL], 0x2);

	चयन (wrp->slave->type) अणु
	हाल PMIC_MT6397:
		pwrap_ग_लिखो(wrp, wrp->slave->dew_regs[PWRAP_DEW_CIPHER_LOAD],
			    0x1);
		pwrap_ग_लिखो(wrp, wrp->slave->dew_regs[PWRAP_DEW_CIPHER_START],
			    0x1);
		अवरोध;
	हाल PMIC_MT6323:
	हाल PMIC_MT6351:
	हाल PMIC_MT6357:
		pwrap_ग_लिखो(wrp, wrp->slave->dew_regs[PWRAP_DEW_CIPHER_EN],
			    0x1);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* रुको क्रम cipher data पढ़ोy@AP */
	ret = pwrap_रुको_क्रम_state(wrp, pwrap_is_cipher_पढ़ोy);
	अगर (ret) अणु
		dev_err(wrp->dev, "cipher data ready@AP fail, ret=%d\n", ret);
		वापस ret;
	पूर्ण

	/* रुको क्रम cipher data पढ़ोy@PMIC */
	ret = pwrap_रुको_क्रम_state(wrp, pwrap_is_pmic_cipher_पढ़ोy);
	अगर (ret) अणु
		dev_err(wrp->dev,
			"timeout waiting for cipher data ready@PMIC\n");
		वापस ret;
	पूर्ण

	/* रुको क्रम cipher mode idle */
	pwrap_ग_लिखो(wrp, wrp->slave->dew_regs[PWRAP_DEW_CIPHER_MODE], 0x1);
	ret = pwrap_रुको_क्रम_state(wrp, pwrap_is_fsm_idle_and_sync_idle);
	अगर (ret) अणु
		dev_err(wrp->dev, "cipher mode idle fail, ret=%d\n", ret);
		वापस ret;
	पूर्ण

	pwrap_ग_लिखोl(wrp, 1, PWRAP_CIPHER_MODE);

	/* Write Test */
	अगर (pwrap_ग_लिखो(wrp, wrp->slave->dew_regs[PWRAP_DEW_WRITE_TEST],
			PWRAP_DEW_WRITE_TEST_VAL) ||
	    pwrap_पढ़ो(wrp, wrp->slave->dew_regs[PWRAP_DEW_WRITE_TEST],
		       &rdata) ||
	    (rdata != PWRAP_DEW_WRITE_TEST_VAL)) अणु
		dev_err(wrp->dev, "rdata=0x%04X\n", rdata);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pwrap_init_security(काष्ठा pmic_wrapper *wrp)
अणु
	पूर्णांक ret;

	/* Enable encryption */
	ret = pwrap_init_cipher(wrp);
	अगर (ret)
		वापस ret;

	/* Signature checking - using CRC */
	अगर (pwrap_ग_लिखो(wrp,
			wrp->slave->dew_regs[PWRAP_DEW_CRC_EN], 0x1))
		वापस -EFAULT;

	pwrap_ग_लिखोl(wrp, 0x1, PWRAP_CRC_EN);
	pwrap_ग_लिखोl(wrp, 0x0, PWRAP_SIG_MODE);
	pwrap_ग_लिखोl(wrp, wrp->slave->dew_regs[PWRAP_DEW_CRC_VAL],
		     PWRAP_SIG_ADR);
	pwrap_ग_लिखोl(wrp,
		     wrp->master->arb_en_all, PWRAP_HIPRIO_ARB_EN);

	वापस 0;
पूर्ण

अटल पूर्णांक pwrap_mt8135_init_soc_specअगरic(काष्ठा pmic_wrapper *wrp)
अणु
	/* enable pwrap events and pwrap bridge in AP side */
	pwrap_ग_लिखोl(wrp, 0x1, PWRAP_EVENT_IN_EN);
	pwrap_ग_लिखोl(wrp, 0xffff, PWRAP_EVENT_DST_EN);
	ग_लिखोl(0x7f, wrp->bridge_base + PWRAP_MT8135_BRIDGE_IORD_ARB_EN);
	ग_लिखोl(0x1, wrp->bridge_base + PWRAP_MT8135_BRIDGE_WACS3_EN);
	ग_लिखोl(0x1, wrp->bridge_base + PWRAP_MT8135_BRIDGE_WACS4_EN);
	ग_लिखोl(0x1, wrp->bridge_base + PWRAP_MT8135_BRIDGE_WDT_UNIT);
	ग_लिखोl(0xffff, wrp->bridge_base + PWRAP_MT8135_BRIDGE_WDT_SRC_EN);
	ग_लिखोl(0x1, wrp->bridge_base + PWRAP_MT8135_BRIDGE_TIMER_EN);
	ग_लिखोl(0x7ff, wrp->bridge_base + PWRAP_MT8135_BRIDGE_INT_EN);

	/* enable PMIC event out and sources */
	अगर (pwrap_ग_लिखो(wrp, wrp->slave->dew_regs[PWRAP_DEW_EVENT_OUT_EN],
			0x1) ||
	    pwrap_ग_लिखो(wrp, wrp->slave->dew_regs[PWRAP_DEW_EVENT_SRC_EN],
			0xffff)) अणु
		dev_err(wrp->dev, "enable dewrap fail\n");
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pwrap_mt8173_init_soc_specअगरic(काष्ठा pmic_wrapper *wrp)
अणु
	/* PMIC_DEWRAP enables */
	अगर (pwrap_ग_लिखो(wrp, wrp->slave->dew_regs[PWRAP_DEW_EVENT_OUT_EN],
			0x1) ||
	    pwrap_ग_लिखो(wrp, wrp->slave->dew_regs[PWRAP_DEW_EVENT_SRC_EN],
			0xffff)) अणु
		dev_err(wrp->dev, "enable dewrap fail\n");
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pwrap_mt2701_init_soc_specअगरic(काष्ठा pmic_wrapper *wrp)
अणु
	/* GPS_INTF initialization */
	चयन (wrp->slave->type) अणु
	हाल PMIC_MT6323:
		pwrap_ग_लिखोl(wrp, 0x076c, PWRAP_ADC_CMD_ADDR);
		pwrap_ग_लिखोl(wrp, 0x8000, PWRAP_PWRAP_ADC_CMD);
		pwrap_ग_लिखोl(wrp, 0x072c, PWRAP_ADC_RDY_ADDR);
		pwrap_ग_लिखोl(wrp, 0x072e, PWRAP_ADC_RDATA_ADDR1);
		pwrap_ग_लिखोl(wrp, 0x0730, PWRAP_ADC_RDATA_ADDR2);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pwrap_mt7622_init_soc_specअगरic(काष्ठा pmic_wrapper *wrp)
अणु
	pwrap_ग_लिखोl(wrp, 0, PWRAP_STAUPD_PRD);
	/* enable 2wire SPI master */
	pwrap_ग_लिखोl(wrp, 0x8000000, PWRAP_SPI2_CTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक pwrap_mt8183_init_soc_specअगरic(काष्ठा pmic_wrapper *wrp)
अणु
	pwrap_ग_लिखोl(wrp, 0xf5, PWRAP_STAUPD_GRPEN);

	pwrap_ग_लिखो(wrp, wrp->slave->dew_regs[PWRAP_DEW_CRC_EN], 0x1);
	pwrap_ग_लिखोl(wrp, 1, PWRAP_CRC_EN);
	pwrap_ग_लिखोl(wrp, 0x416, PWRAP_SIG_ADR);
	pwrap_ग_लिखोl(wrp, 0x42e, PWRAP_EINT_STA0_ADR);

	pwrap_ग_लिखोl(wrp, 1, PWRAP_WACS_P2P_EN);
	pwrap_ग_लिखोl(wrp, 1, PWRAP_WACS_MD32_EN);
	pwrap_ग_लिखोl(wrp, 1, PWRAP_INIT_DONE_P2P);
	pwrap_ग_लिखोl(wrp, 1, PWRAP_INIT_DONE_MD32);

	वापस 0;
पूर्ण

अटल पूर्णांक pwrap_init(काष्ठा pmic_wrapper *wrp)
अणु
	पूर्णांक ret;

	अगर (wrp->rstc)
		reset_control_reset(wrp->rstc);
	अगर (wrp->rstc_bridge)
		reset_control_reset(wrp->rstc_bridge);

	अगर (wrp->master->type == PWRAP_MT8173) अणु
		/* Enable DCM */
		pwrap_ग_लिखोl(wrp, 3, PWRAP_DCM_EN);
		pwrap_ग_लिखोl(wrp, 0, PWRAP_DCM_DBC_PRD);
	पूर्ण

	अगर (HAS_CAP(wrp->slave->caps, PWRAP_SLV_CAP_SPI)) अणु
		/* Reset SPI slave */
		ret = pwrap_reset_spislave(wrp);
		अगर (ret)
			वापस ret;
	पूर्ण

	pwrap_ग_लिखोl(wrp, 1, PWRAP_WRAP_EN);

	pwrap_ग_लिखोl(wrp, wrp->master->arb_en_all, PWRAP_HIPRIO_ARB_EN);

	pwrap_ग_लिखोl(wrp, 1, PWRAP_WACS2_EN);

	ret = wrp->master->init_reg_घड़ी(wrp);
	अगर (ret)
		वापस ret;

	अगर (HAS_CAP(wrp->slave->caps, PWRAP_SLV_CAP_SPI)) अणु
		/* Setup serial input delay */
		ret = pwrap_init_sidly(wrp);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (HAS_CAP(wrp->slave->caps, PWRAP_SLV_CAP_DUALIO)) अणु
		/* Enable dual I/O mode */
		ret = pwrap_init_dual_io(wrp);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (HAS_CAP(wrp->slave->caps, PWRAP_SLV_CAP_SECURITY)) अणु
		/* Enable security on bus */
		ret = pwrap_init_security(wrp);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (wrp->master->type == PWRAP_MT8135)
		pwrap_ग_लिखोl(wrp, 0x7, PWRAP_RRARB_EN);

	pwrap_ग_लिखोl(wrp, 0x1, PWRAP_WACS0_EN);
	pwrap_ग_लिखोl(wrp, 0x1, PWRAP_WACS1_EN);
	pwrap_ग_लिखोl(wrp, 0x1, PWRAP_WACS2_EN);
	pwrap_ग_लिखोl(wrp, 0x5, PWRAP_STAUPD_PRD);
	pwrap_ग_लिखोl(wrp, 0xff, PWRAP_STAUPD_GRPEN);

	अगर (wrp->master->init_soc_specअगरic) अणु
		ret = wrp->master->init_soc_specअगरic(wrp);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Setup the init करोne रेजिस्टरs */
	pwrap_ग_लिखोl(wrp, 1, PWRAP_INIT_DONE2);
	pwrap_ग_लिखोl(wrp, 1, PWRAP_INIT_DONE0);
	pwrap_ग_लिखोl(wrp, 1, PWRAP_INIT_DONE1);

	अगर (HAS_CAP(wrp->master->caps, PWRAP_CAP_BRIDGE)) अणु
		ग_लिखोl(1, wrp->bridge_base + PWRAP_MT8135_BRIDGE_INIT_DONE3);
		ग_लिखोl(1, wrp->bridge_base + PWRAP_MT8135_BRIDGE_INIT_DONE4);
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t pwrap_पूर्णांकerrupt(पूर्णांक irqno, व्योम *dev_id)
अणु
	u32 rdata;
	काष्ठा pmic_wrapper *wrp = dev_id;

	rdata = pwrap_पढ़ोl(wrp, PWRAP_INT_FLG);
	dev_err(wrp->dev, "unexpected interrupt int=0x%x\n", rdata);
	pwrap_ग_लिखोl(wrp, 0xffffffff, PWRAP_INT_CLR);

	अगर (HAS_CAP(wrp->master->caps, PWRAP_CAP_INT1_EN)) अणु
		rdata = pwrap_पढ़ोl(wrp, PWRAP_INT1_FLG);
		dev_err(wrp->dev, "unexpected interrupt int1=0x%x\n", rdata);
		pwrap_ग_लिखोl(wrp, 0xffffffff, PWRAP_INT1_CLR);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा regmap_config pwrap_regmap_config16 = अणु
	.reg_bits = 16,
	.val_bits = 16,
	.reg_stride = 2,
	.reg_पढ़ो = pwrap_regmap_पढ़ो,
	.reg_ग_लिखो = pwrap_regmap_ग_लिखो,
	.max_रेजिस्टर = 0xffff,
पूर्ण;

अटल स्थिर काष्ठा regmap_config pwrap_regmap_config32 = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.reg_पढ़ो = pwrap_regmap_पढ़ो,
	.reg_ग_लिखो = pwrap_regmap_ग_लिखो,
	.max_रेजिस्टर = 0xffff,
पूर्ण;

अटल स्थिर काष्ठा pwrap_slv_type pmic_mt6323 = अणु
	.dew_regs = mt6323_regs,
	.type = PMIC_MT6323,
	.regmap = &pwrap_regmap_config16,
	.caps = PWRAP_SLV_CAP_SPI | PWRAP_SLV_CAP_DUALIO |
		PWRAP_SLV_CAP_SECURITY,
	.pwrap_पढ़ो = pwrap_पढ़ो16,
	.pwrap_ग_लिखो = pwrap_ग_लिखो16,
पूर्ण;

अटल स्थिर काष्ठा pwrap_slv_type pmic_mt6351 = अणु
	.dew_regs = mt6351_regs,
	.type = PMIC_MT6351,
	.regmap = &pwrap_regmap_config16,
	.caps = 0,
	.pwrap_पढ़ो = pwrap_पढ़ो16,
	.pwrap_ग_लिखो = pwrap_ग_लिखो16,
पूर्ण;

अटल स्थिर काष्ठा pwrap_slv_type pmic_mt6357 = अणु
	.dew_regs = mt6357_regs,
	.type = PMIC_MT6357,
	.regmap = &pwrap_regmap_config16,
	.caps = 0,
	.pwrap_पढ़ो = pwrap_पढ़ो16,
	.pwrap_ग_लिखो = pwrap_ग_लिखो16,
पूर्ण;

अटल स्थिर काष्ठा pwrap_slv_type pmic_mt6358 = अणु
	.dew_regs = mt6358_regs,
	.type = PMIC_MT6358,
	.regmap = &pwrap_regmap_config16,
	.caps = PWRAP_SLV_CAP_SPI | PWRAP_SLV_CAP_DUALIO,
	.pwrap_पढ़ो = pwrap_पढ़ो16,
	.pwrap_ग_लिखो = pwrap_ग_लिखो16,
पूर्ण;

अटल स्थिर काष्ठा pwrap_slv_type pmic_mt6359 = अणु
	.dew_regs = mt6359_regs,
	.type = PMIC_MT6359,
	.regmap = &pwrap_regmap_config16,
	.caps = PWRAP_SLV_CAP_DUALIO,
	.pwrap_पढ़ो = pwrap_पढ़ो16,
	.pwrap_ग_लिखो = pwrap_ग_लिखो16,
पूर्ण;

अटल स्थिर काष्ठा pwrap_slv_type pmic_mt6380 = अणु
	.dew_regs = शून्य,
	.type = PMIC_MT6380,
	.regmap = &pwrap_regmap_config32,
	.caps = 0,
	.pwrap_पढ़ो = pwrap_पढ़ो32,
	.pwrap_ग_लिखो = pwrap_ग_लिखो32,
पूर्ण;

अटल स्थिर काष्ठा pwrap_slv_type pmic_mt6397 = अणु
	.dew_regs = mt6397_regs,
	.type = PMIC_MT6397,
	.regmap = &pwrap_regmap_config16,
	.caps = PWRAP_SLV_CAP_SPI | PWRAP_SLV_CAP_DUALIO |
		PWRAP_SLV_CAP_SECURITY,
	.pwrap_पढ़ो = pwrap_पढ़ो16,
	.pwrap_ग_लिखो = pwrap_ग_लिखो16,
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_slave_match_tbl[] = अणु
	अणु
		.compatible = "mediatek,mt6323",
		.data = &pmic_mt6323,
	पूर्ण, अणु
		.compatible = "mediatek,mt6351",
		.data = &pmic_mt6351,
	पूर्ण, अणु
		.compatible = "mediatek,mt6357",
		.data = &pmic_mt6357,
	पूर्ण, अणु
		.compatible = "mediatek,mt6358",
		.data = &pmic_mt6358,
	पूर्ण, अणु
		.compatible = "mediatek,mt6359",
		.data = &pmic_mt6359,
	पूर्ण, अणु
		/* The MT6380 PMIC only implements a regulator, so we bind it
		 * directly instead of using a MFD.
		 */
		.compatible = "mediatek,mt6380-regulator",
		.data = &pmic_mt6380,
	पूर्ण, अणु
		.compatible = "mediatek,mt6397",
		.data = &pmic_mt6397,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_slave_match_tbl);

अटल स्थिर काष्ठा pmic_wrapper_type pwrap_mt2701 = अणु
	.regs = mt2701_regs,
	.type = PWRAP_MT2701,
	.arb_en_all = 0x3f,
	.पूर्णांक_en_all = ~(u32)(BIT(31) | BIT(2)),
	.पूर्णांक1_en_all = 0,
	.spi_w = PWRAP_MAN_CMD_SPI_WRITE_NEW,
	.wdt_src = PWRAP_WDT_SRC_MASK_ALL,
	.caps = PWRAP_CAP_RESET | PWRAP_CAP_DCM,
	.init_reg_घड़ी = pwrap_mt2701_init_reg_घड़ी,
	.init_soc_specअगरic = pwrap_mt2701_init_soc_specअगरic,
पूर्ण;

अटल स्थिर काष्ठा pmic_wrapper_type pwrap_mt6765 = अणु
	.regs = mt6765_regs,
	.type = PWRAP_MT6765,
	.arb_en_all = 0x3fd35,
	.पूर्णांक_en_all = 0xffffffff,
	.spi_w = PWRAP_MAN_CMD_SPI_WRITE,
	.wdt_src = PWRAP_WDT_SRC_MASK_ALL,
	.caps = PWRAP_CAP_RESET | PWRAP_CAP_DCM,
	.init_reg_घड़ी = pwrap_common_init_reg_घड़ी,
	.init_soc_specअगरic = शून्य,
पूर्ण;

अटल स्थिर काष्ठा pmic_wrapper_type pwrap_mt6779 = अणु
	.regs = mt6779_regs,
	.type = PWRAP_MT6779,
	.arb_en_all = 0xfbb7f,
	.पूर्णांक_en_all = 0xfffffffe,
	.पूर्णांक1_en_all = 0,
	.spi_w = PWRAP_MAN_CMD_SPI_WRITE,
	.wdt_src = PWRAP_WDT_SRC_MASK_ALL,
	.caps = 0,
	.init_reg_घड़ी = pwrap_common_init_reg_घड़ी,
	.init_soc_specअगरic = शून्य,
पूर्ण;

अटल स्थिर काष्ठा pmic_wrapper_type pwrap_mt6797 = अणु
	.regs = mt6797_regs,
	.type = PWRAP_MT6797,
	.arb_en_all = 0x01fff,
	.पूर्णांक_en_all = 0xffffffc6,
	.पूर्णांक1_en_all = 0,
	.spi_w = PWRAP_MAN_CMD_SPI_WRITE,
	.wdt_src = PWRAP_WDT_SRC_MASK_ALL,
	.caps = PWRAP_CAP_RESET | PWRAP_CAP_DCM,
	.init_reg_घड़ी = pwrap_common_init_reg_घड़ी,
	.init_soc_specअगरic = शून्य,
पूर्ण;

अटल स्थिर काष्ठा pmic_wrapper_type pwrap_mt6873 = अणु
	.regs = mt6873_regs,
	.type = PWRAP_MT6873,
	.arb_en_all = 0x777f,
	.पूर्णांक_en_all = BIT(4) | BIT(5),
	.पूर्णांक1_en_all = 0,
	.spi_w = PWRAP_MAN_CMD_SPI_WRITE,
	.wdt_src = PWRAP_WDT_SRC_MASK_ALL,
	.caps = PWRAP_CAP_ARB,
	.init_reg_घड़ी = pwrap_common_init_reg_घड़ी,
	.init_soc_specअगरic = शून्य,
पूर्ण;

अटल स्थिर काष्ठा pmic_wrapper_type pwrap_mt7622 = अणु
	.regs = mt7622_regs,
	.type = PWRAP_MT7622,
	.arb_en_all = 0xff,
	.पूर्णांक_en_all = ~(u32)BIT(31),
	.पूर्णांक1_en_all = 0,
	.spi_w = PWRAP_MAN_CMD_SPI_WRITE,
	.wdt_src = PWRAP_WDT_SRC_MASK_ALL,
	.caps = PWRAP_CAP_RESET | PWRAP_CAP_DCM,
	.init_reg_घड़ी = pwrap_common_init_reg_घड़ी,
	.init_soc_specअगरic = pwrap_mt7622_init_soc_specअगरic,
पूर्ण;

अटल स्थिर काष्ठा pmic_wrapper_type pwrap_mt8135 = अणु
	.regs = mt8135_regs,
	.type = PWRAP_MT8135,
	.arb_en_all = 0x1ff,
	.पूर्णांक_en_all = ~(u32)(BIT(31) | BIT(1)),
	.पूर्णांक1_en_all = 0,
	.spi_w = PWRAP_MAN_CMD_SPI_WRITE,
	.wdt_src = PWRAP_WDT_SRC_MASK_ALL,
	.caps = PWRAP_CAP_BRIDGE | PWRAP_CAP_RESET | PWRAP_CAP_DCM,
	.init_reg_घड़ी = pwrap_common_init_reg_घड़ी,
	.init_soc_specअगरic = pwrap_mt8135_init_soc_specअगरic,
पूर्ण;

अटल स्थिर काष्ठा pmic_wrapper_type pwrap_mt8173 = अणु
	.regs = mt8173_regs,
	.type = PWRAP_MT8173,
	.arb_en_all = 0x3f,
	.पूर्णांक_en_all = ~(u32)(BIT(31) | BIT(1)),
	.पूर्णांक1_en_all = 0,
	.spi_w = PWRAP_MAN_CMD_SPI_WRITE,
	.wdt_src = PWRAP_WDT_SRC_MASK_NO_STAUPD,
	.caps = PWRAP_CAP_RESET | PWRAP_CAP_DCM,
	.init_reg_घड़ी = pwrap_common_init_reg_घड़ी,
	.init_soc_specअगरic = pwrap_mt8173_init_soc_specअगरic,
पूर्ण;

अटल स्थिर काष्ठा pmic_wrapper_type pwrap_mt8183 = अणु
	.regs = mt8183_regs,
	.type = PWRAP_MT8183,
	.arb_en_all = 0x3fa75,
	.पूर्णांक_en_all = 0xffffffff,
	.पूर्णांक1_en_all = 0xeef7ffff,
	.spi_w = PWRAP_MAN_CMD_SPI_WRITE,
	.wdt_src = PWRAP_WDT_SRC_MASK_ALL,
	.caps = PWRAP_CAP_INT1_EN | PWRAP_CAP_WDT_SRC1,
	.init_reg_घड़ी = pwrap_common_init_reg_घड़ी,
	.init_soc_specअगरic = pwrap_mt8183_init_soc_specअगरic,
पूर्ण;

अटल काष्ठा pmic_wrapper_type pwrap_mt8516 = अणु
	.regs = mt8516_regs,
	.type = PWRAP_MT8516,
	.arb_en_all = 0xff,
	.पूर्णांक_en_all = ~(u32)(BIT(31) | BIT(2)),
	.spi_w = PWRAP_MAN_CMD_SPI_WRITE,
	.wdt_src = PWRAP_WDT_SRC_MASK_ALL,
	.caps = PWRAP_CAP_DCM,
	.init_reg_घड़ी = pwrap_mt2701_init_reg_घड़ी,
	.init_soc_specअगरic = शून्य,
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_pwrap_match_tbl[] = अणु
	अणु
		.compatible = "mediatek,mt2701-pwrap",
		.data = &pwrap_mt2701,
	पूर्ण, अणु
		.compatible = "mediatek,mt6765-pwrap",
		.data = &pwrap_mt6765,
	पूर्ण, अणु
		.compatible = "mediatek,mt6779-pwrap",
		.data = &pwrap_mt6779,
	पूर्ण, अणु
		.compatible = "mediatek,mt6797-pwrap",
		.data = &pwrap_mt6797,
	पूर्ण, अणु
		.compatible = "mediatek,mt6873-pwrap",
		.data = &pwrap_mt6873,
	पूर्ण, अणु
		.compatible = "mediatek,mt7622-pwrap",
		.data = &pwrap_mt7622,
	पूर्ण, अणु
		.compatible = "mediatek,mt8135-pwrap",
		.data = &pwrap_mt8135,
	पूर्ण, अणु
		.compatible = "mediatek,mt8173-pwrap",
		.data = &pwrap_mt8173,
	पूर्ण, अणु
		.compatible = "mediatek,mt8183-pwrap",
		.data = &pwrap_mt8183,
	पूर्ण, अणु
		.compatible = "mediatek,mt8516-pwrap",
		.data = &pwrap_mt8516,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_pwrap_match_tbl);

अटल पूर्णांक pwrap_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret, irq;
	u32 mask_करोne;
	काष्ठा pmic_wrapper *wrp;
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर काष्ठा of_device_id *of_slave_id = शून्य;
	काष्ठा resource *res;

	अगर (np->child)
		of_slave_id = of_match_node(of_slave_match_tbl, np->child);

	अगर (!of_slave_id) अणु
		dev_dbg(&pdev->dev, "slave pmic should be defined in dts\n");
		वापस -EINVAL;
	पूर्ण

	wrp = devm_kzalloc(&pdev->dev, माप(*wrp), GFP_KERNEL);
	अगर (!wrp)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, wrp);

	wrp->master = of_device_get_match_data(&pdev->dev);
	wrp->slave = of_slave_id->data;
	wrp->dev = &pdev->dev;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "pwrap");
	wrp->base = devm_ioremap_resource(wrp->dev, res);
	अगर (IS_ERR(wrp->base))
		वापस PTR_ERR(wrp->base);

	अगर (HAS_CAP(wrp->master->caps, PWRAP_CAP_RESET)) अणु
		wrp->rstc = devm_reset_control_get(wrp->dev, "pwrap");
		अगर (IS_ERR(wrp->rstc)) अणु
			ret = PTR_ERR(wrp->rstc);
			dev_dbg(wrp->dev, "cannot get pwrap reset: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (HAS_CAP(wrp->master->caps, PWRAP_CAP_BRIDGE)) अणु
		res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
				"pwrap-bridge");
		wrp->bridge_base = devm_ioremap_resource(wrp->dev, res);
		अगर (IS_ERR(wrp->bridge_base))
			वापस PTR_ERR(wrp->bridge_base);

		wrp->rstc_bridge = devm_reset_control_get(wrp->dev,
							  "pwrap-bridge");
		अगर (IS_ERR(wrp->rstc_bridge)) अणु
			ret = PTR_ERR(wrp->rstc_bridge);
			dev_dbg(wrp->dev,
				"cannot get pwrap-bridge reset: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	wrp->clk_spi = devm_clk_get(wrp->dev, "spi");
	अगर (IS_ERR(wrp->clk_spi)) अणु
		dev_dbg(wrp->dev, "failed to get clock: %ld\n",
			PTR_ERR(wrp->clk_spi));
		वापस PTR_ERR(wrp->clk_spi);
	पूर्ण

	wrp->clk_wrap = devm_clk_get(wrp->dev, "wrap");
	अगर (IS_ERR(wrp->clk_wrap)) अणु
		dev_dbg(wrp->dev, "failed to get clock: %ld\n",
			PTR_ERR(wrp->clk_wrap));
		वापस PTR_ERR(wrp->clk_wrap);
	पूर्ण

	ret = clk_prepare_enable(wrp->clk_spi);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(wrp->clk_wrap);
	अगर (ret)
		जाओ err_out1;

	/* Enable पूर्णांकernal dynamic घड़ी */
	अगर (HAS_CAP(wrp->master->caps, PWRAP_CAP_DCM)) अणु
		pwrap_ग_लिखोl(wrp, 1, PWRAP_DCM_EN);
		pwrap_ग_लिखोl(wrp, 0, PWRAP_DCM_DBC_PRD);
	पूर्ण

	/*
	 * The PMIC could alपढ़ोy be initialized by the bootloader.
	 * Skip initialization here in this हाल.
	 */
	अगर (!pwrap_पढ़ोl(wrp, PWRAP_INIT_DONE2)) अणु
		ret = pwrap_init(wrp);
		अगर (ret) अणु
			dev_dbg(wrp->dev, "init failed with %d\n", ret);
			जाओ err_out2;
		पूर्ण
	पूर्ण

	अगर (HAS_CAP(wrp->master->caps, PWRAP_CAP_ARB))
		mask_करोne = PWRAP_STATE_INIT_DONE1;
	अन्यथा
		mask_करोne = PWRAP_STATE_INIT_DONE0;

	अगर (!(pwrap_पढ़ोl(wrp, PWRAP_WACS2_RDATA) & mask_करोne)) अणु
		dev_dbg(wrp->dev, "initialization isn't finished\n");
		ret = -ENODEV;
		जाओ err_out2;
	पूर्ण

	/* Initialize watchकरोg, may not be करोne by the bootloader */
	अगर (!HAS_CAP(wrp->master->caps, PWRAP_CAP_ARB))
		pwrap_ग_लिखोl(wrp, 0xf, PWRAP_WDT_UNIT);

	/*
	 * Since STAUPD was not used on mt8173 platक्रमm,
	 * so STAUPD of WDT_SRC which should be turned off
	 */
	pwrap_ग_लिखोl(wrp, wrp->master->wdt_src, PWRAP_WDT_SRC_EN);
	अगर (HAS_CAP(wrp->master->caps, PWRAP_CAP_WDT_SRC1))
		pwrap_ग_लिखोl(wrp, wrp->master->wdt_src, PWRAP_WDT_SRC_EN_1);

	अगर (HAS_CAP(wrp->master->caps, PWRAP_CAP_ARB))
		pwrap_ग_लिखोl(wrp, 0x3, PWRAP_TIMER_EN);
	अन्यथा
		pwrap_ग_लिखोl(wrp, 0x1, PWRAP_TIMER_EN);

	pwrap_ग_लिखोl(wrp, wrp->master->पूर्णांक_en_all, PWRAP_INT_EN);
	/*
	 * We add INT1 पूर्णांकerrupt to handle starvation and request exception
	 * If we support it, we should enable it here.
	 */
	अगर (HAS_CAP(wrp->master->caps, PWRAP_CAP_INT1_EN))
		pwrap_ग_लिखोl(wrp, wrp->master->पूर्णांक1_en_all, PWRAP_INT1_EN);

	irq = platक्रमm_get_irq(pdev, 0);
	ret = devm_request_irq(wrp->dev, irq, pwrap_पूर्णांकerrupt,
			       IRQF_TRIGGER_HIGH,
			       "mt-pmic-pwrap", wrp);
	अगर (ret)
		जाओ err_out2;

	wrp->regmap = devm_regmap_init(wrp->dev, शून्य, wrp, wrp->slave->regmap);
	अगर (IS_ERR(wrp->regmap)) अणु
		ret = PTR_ERR(wrp->regmap);
		जाओ err_out2;
	पूर्ण

	ret = of_platक्रमm_populate(np, शून्य, शून्य, wrp->dev);
	अगर (ret) अणु
		dev_dbg(wrp->dev, "failed to create child devices at %pOF\n",
				np);
		जाओ err_out2;
	पूर्ण

	वापस 0;

err_out2:
	clk_disable_unprepare(wrp->clk_wrap);
err_out1:
	clk_disable_unprepare(wrp->clk_spi);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver pwrap_drv = अणु
	.driver = अणु
		.name = "mt-pmic-pwrap",
		.of_match_table = of_match_ptr(of_pwrap_match_tbl),
	पूर्ण,
	.probe = pwrap_probe,
पूर्ण;

module_platक्रमm_driver(pwrap_drv);

MODULE_AUTHOR("Flora Fu, MediaTek");
MODULE_DESCRIPTION("MediaTek MT8135 PMIC Wrapper Driver");
MODULE_LICENSE("GPL v2");
