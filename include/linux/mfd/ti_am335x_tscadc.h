<शैली गुरु>
#अगर_अघोषित __LINUX_TI_AM335X_TSCADC_MFD_H
#घोषणा __LINUX_TI_AM335X_TSCADC_MFD_H

/*
 * TI Touch Screen / ADC MFD driver
 *
 * Copyright (C) 2012 Texas Instruments Incorporated - https://www.ti.com/
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/mfd/core.h>

#घोषणा REG_RAWIRQSTATUS	0x024
#घोषणा REG_IRQSTATUS		0x028
#घोषणा REG_IRQENABLE		0x02C
#घोषणा REG_IRQCLR		0x030
#घोषणा REG_IRQWAKEUP		0x034
#घोषणा REG_DMAENABLE_SET	0x038
#घोषणा REG_DMAENABLE_CLEAR	0x03c
#घोषणा REG_CTRL		0x040
#घोषणा REG_ADCFSM		0x044
#घोषणा REG_CLKDIV		0x04C
#घोषणा REG_SE			0x054
#घोषणा REG_IDLECONFIG		0x058
#घोषणा REG_CHARGECONFIG	0x05C
#घोषणा REG_CHARGEDELAY		0x060
#घोषणा REG_STEPCONFIG(n)	(0x64 + ((n) * 8))
#घोषणा REG_STEPDELAY(n)	(0x68 + ((n) * 8))
#घोषणा REG_FIFO0CNT		0xE4
#घोषणा REG_FIFO0THR		0xE8
#घोषणा REG_FIFO1CNT		0xF0
#घोषणा REG_FIFO1THR		0xF4
#घोषणा REG_DMA1REQ		0xF8
#घोषणा REG_FIFO0		0x100
#घोषणा REG_FIFO1		0x200

/*	Register Bitfields	*/
/* IRQ wakeup enable */
#घोषणा IRQWKUP_ENB		BIT(0)

/* Step Enable */
#घोषणा STEPENB_MASK		(0x1FFFF << 0)
#घोषणा STEPENB(val)		((val) << 0)
#घोषणा ENB(val)			(1 << (val))
#घोषणा STPENB_STEPENB		STEPENB(0x1FFFF)
#घोषणा STPENB_STEPENB_TC	STEPENB(0x1FFF)

/* IRQ enable */
#घोषणा IRQENB_HW_PEN		BIT(0)
#घोषणा IRQENB_EOS		BIT(1)
#घोषणा IRQENB_FIFO0THRES	BIT(2)
#घोषणा IRQENB_FIFO0OVRRUN	BIT(3)
#घोषणा IRQENB_FIFO0UNDRFLW	BIT(4)
#घोषणा IRQENB_FIFO1THRES	BIT(5)
#घोषणा IRQENB_FIFO1OVRRUN	BIT(6)
#घोषणा IRQENB_FIFO1UNDRFLW	BIT(7)
#घोषणा IRQENB_PENUP		BIT(9)

/* Step Configuration */
#घोषणा STEPCONFIG_MODE_MASK	(3 << 0)
#घोषणा STEPCONFIG_MODE(val)	((val) << 0)
#घोषणा STEPCONFIG_MODE_SWCNT	STEPCONFIG_MODE(1)
#घोषणा STEPCONFIG_MODE_HWSYNC	STEPCONFIG_MODE(2)
#घोषणा STEPCONFIG_AVG_MASK	(7 << 2)
#घोषणा STEPCONFIG_AVG(val)	((val) << 2)
#घोषणा STEPCONFIG_AVG_16	STEPCONFIG_AVG(4)
#घोषणा STEPCONFIG_XPP		BIT(5)
#घोषणा STEPCONFIG_XNN		BIT(6)
#घोषणा STEPCONFIG_YPP		BIT(7)
#घोषणा STEPCONFIG_YNN		BIT(8)
#घोषणा STEPCONFIG_XNP		BIT(9)
#घोषणा STEPCONFIG_YPN		BIT(10)
#घोषणा STEPCONFIG_RFP(val)	((val) << 12)
#घोषणा STEPCONFIG_RFP_VREFP	(0x3 << 12)
#घोषणा STEPCONFIG_INM_MASK	(0xF << 15)
#घोषणा STEPCONFIG_INM(val)	((val) << 15)
#घोषणा STEPCONFIG_INM_ADCREFM	STEPCONFIG_INM(8)
#घोषणा STEPCONFIG_INP_MASK	(0xF << 19)
#घोषणा STEPCONFIG_INP(val)	((val) << 19)
#घोषणा STEPCONFIG_INP_AN4	STEPCONFIG_INP(4)
#घोषणा STEPCONFIG_INP_ADCREFM	STEPCONFIG_INP(8)
#घोषणा STEPCONFIG_FIFO1	BIT(26)
#घोषणा STEPCONFIG_RFM(val)	((val) << 23)
#घोषणा STEPCONFIG_RFM_VREFN	(0x3 << 23)

/* Delay रेजिस्टर */
#घोषणा STEPDELAY_OPEN_MASK	(0x3FFFF << 0)
#घोषणा STEPDELAY_OPEN(val)	((val) << 0)
#घोषणा STEPCONFIG_OPENDLY	STEPDELAY_OPEN(0x098)
#घोषणा STEPDELAY_SAMPLE_MASK	(0xFF << 24)
#घोषणा STEPDELAY_SAMPLE(val)	((val) << 24)
#घोषणा STEPCONFIG_SAMPLEDLY	STEPDELAY_SAMPLE(0)

/* Charge Config */
#घोषणा STEPCHARGE_RFP_MASK	(7 << 12)
#घोषणा STEPCHARGE_RFP(val)	((val) << 12)
#घोषणा STEPCHARGE_RFP_XPUL	STEPCHARGE_RFP(1)
#घोषणा STEPCHARGE_INM_MASK	(0xF << 15)
#घोषणा STEPCHARGE_INM(val)	((val) << 15)
#घोषणा STEPCHARGE_INM_AN1	STEPCHARGE_INM(1)
#घोषणा STEPCHARGE_INP_MASK	(0xF << 19)
#घोषणा STEPCHARGE_INP(val)	((val) << 19)
#घोषणा STEPCHARGE_RFM_MASK	(3 << 23)
#घोषणा STEPCHARGE_RFM(val)	((val) << 23)
#घोषणा STEPCHARGE_RFM_XNUR	STEPCHARGE_RFM(1)

/* Charge delay */
#घोषणा CHARGEDLY_OPEN_MASK	(0x3FFFF << 0)
#घोषणा CHARGEDLY_OPEN(val)	((val) << 0)
#घोषणा CHARGEDLY_OPENDLY	CHARGEDLY_OPEN(0x400)

/* Control रेजिस्टर */
#घोषणा CNTRLREG_TSCSSENB	BIT(0)
#घोषणा CNTRLREG_STEPID		BIT(1)
#घोषणा CNTRLREG_STEPCONFIGWRT	BIT(2)
#घोषणा CNTRLREG_POWERDOWN	BIT(4)
#घोषणा CNTRLREG_AFE_CTRL_MASK	(3 << 5)
#घोषणा CNTRLREG_AFE_CTRL(val)	((val) << 5)
#घोषणा CNTRLREG_4WIRE		CNTRLREG_AFE_CTRL(1)
#घोषणा CNTRLREG_5WIRE		CNTRLREG_AFE_CTRL(2)
#घोषणा CNTRLREG_8WIRE		CNTRLREG_AFE_CTRL(3)
#घोषणा CNTRLREG_TSCENB		BIT(7)

/* FIFO READ Register */
#घोषणा FIFOREAD_DATA_MASK (0xfff << 0)
#घोषणा FIFOREAD_CHNLID_MASK (0xf << 16)

/* DMA ENABLE/CLEAR Register */
#घोषणा DMA_FIFO0		BIT(0)
#घोषणा DMA_FIFO1		BIT(1)

/* Sequencer Status */
#घोषणा SEQ_STATUS BIT(5)
#घोषणा CHARGE_STEP		0x11

#घोषणा ADC_CLK			3000000
#घोषणा TOTAL_STEPS		16
#घोषणा TOTAL_CHANNELS		8
#घोषणा FIFO1_THRESHOLD		19

/*
 * समय in us क्रम processing a single channel, calculated as follows:
 *
 * max num cycles = खोलो delay + (sample delay + conv समय) * averaging
 *
 * max num cycles: 262143 + (255 + 13) * 16 = 266431
 *
 * घड़ी frequency: 26MHz / 8 = 3.25MHz
 * घड़ी period: 1 / 3.25MHz = 308ns
 *
 * max processing समय: 266431 * 308ns = 83ms(approx)
 */
#घोषणा IDLE_TIMEOUT 83 /* milliseconds */

#घोषणा TSCADC_CELLS		2

काष्ठा ti_tscadc_dev अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	व्योम __iomem *tscadc_base;
	phys_addr_t tscadc_phys_base;
	पूर्णांक irq;
	पूर्णांक used_cells;	/* 1-2 */
	पूर्णांक tsc_wires;
	पूर्णांक tsc_cell;	/* -1 अगर not used */
	पूर्णांक adc_cell;	/* -1 अगर not used */
	काष्ठा mfd_cell cells[TSCADC_CELLS];
	u32 reg_se_cache;
	bool adc_रुकोing;
	bool adc_in_use;
	रुको_queue_head_t reg_se_रुको;
	spinlock_t reg_lock;
	अचिन्हित पूर्णांक clk_भाग;

	/* tsc device */
	काष्ठा titsc *tsc;

	/* adc device */
	काष्ठा adc_device *adc;
पूर्ण;

अटल अंतरभूत काष्ठा ti_tscadc_dev *ti_tscadc_dev_get(काष्ठा platक्रमm_device *p)
अणु
	काष्ठा ti_tscadc_dev **tscadc_dev = p->dev.platक्रमm_data;

	वापस *tscadc_dev;
पूर्ण

व्योम am335x_tsc_se_set_cache(काष्ठा ti_tscadc_dev *tsadc, u32 val);
व्योम am335x_tsc_se_set_once(काष्ठा ti_tscadc_dev *tsadc, u32 val);
व्योम am335x_tsc_se_clr(काष्ठा ti_tscadc_dev *tsadc, u32 val);
व्योम am335x_tsc_se_adc_करोne(काष्ठा ti_tscadc_dev *tsadc);

#पूर्ण_अगर
