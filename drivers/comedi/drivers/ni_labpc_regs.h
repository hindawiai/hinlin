<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ni_labpc रेजिस्टर definitions.
 */

#अगर_अघोषित _NI_LABPC_REGS_H
#घोषणा _NI_LABPC_REGS_H

/*
 * Register map (all रेजिस्टरs are 8-bit)
 */
#घोषणा STAT1_REG		0x00	/* R: Status 1 reg */
#घोषणा STAT1_DAVAIL		BIT(0)
#घोषणा STAT1_OVERRUN		BIT(1)
#घोषणा STAT1_OVERFLOW		BIT(2)
#घोषणा STAT1_CNTINT		BIT(3)
#घोषणा STAT1_GATA0		BIT(5)
#घोषणा STAT1_EXTGATA0		BIT(6)
#घोषणा CMD1_REG		0x00	/* W: Command 1 reg */
#घोषणा CMD1_MA(x)		(((x) & 0x7) << 0)
#घोषणा CMD1_TWOSCMP		BIT(3)
#घोषणा CMD1_GAIN(x)		(((x) & 0x7) << 4)
#घोषणा CMD1_SCANEN		BIT(7)
#घोषणा CMD2_REG		0x01	/* W: Command 2 reg */
#घोषणा CMD2_PRETRIG		BIT(0)
#घोषणा CMD2_HWTRIG		BIT(1)
#घोषणा CMD2_SWTRIG		BIT(2)
#घोषणा CMD2_TBSEL		BIT(3)
#घोषणा CMD2_2SDAC0		BIT(4)
#घोषणा CMD2_2SDAC1		BIT(5)
#घोषणा CMD2_LDAC(x)		BIT(6 + ((x) & 0x1))
#घोषणा CMD3_REG		0x02	/* W: Command 3 reg */
#घोषणा CMD3_DMAEN		BIT(0)
#घोषणा CMD3_DIOINTEN		BIT(1)
#घोषणा CMD3_DMATCINTEN		BIT(2)
#घोषणा CMD3_CNTINTEN		BIT(3)
#घोषणा CMD3_ERRINTEN		BIT(4)
#घोषणा CMD3_FIFOINTEN		BIT(5)
#घोषणा ADC_START_CONVERT_REG	0x03	/* W: Start Convert reg */
#घोषणा DAC_LSB_REG(x)		(0x04 + 2 * (x)) /* W: DAC0/1 LSB reg */
#घोषणा DAC_MSB_REG(x)		(0x05 + 2 * (x)) /* W: DAC0/1 MSB reg */
#घोषणा ADC_FIFO_CLEAR_REG	0x08	/* W: A/D FIFO Clear reg */
#घोषणा ADC_FIFO_REG		0x0a	/* R: A/D FIFO reg */
#घोषणा DMATC_CLEAR_REG		0x0a	/* W: DMA Interrupt Clear reg */
#घोषणा TIMER_CLEAR_REG		0x0c	/* W: Timer Interrupt Clear reg */
#घोषणा CMD6_REG		0x0e	/* W: Command 6 reg */
#घोषणा CMD6_NRSE		BIT(0)
#घोषणा CMD6_ADCUNI		BIT(1)
#घोषणा CMD6_DACUNI(x)		BIT(2 + ((x) & 0x1))
#घोषणा CMD6_HFINTEN		BIT(5)
#घोषणा CMD6_DQINTEN		BIT(6)
#घोषणा CMD6_SCANUP		BIT(7)
#घोषणा CMD4_REG		0x0f	/* W: Command 3 reg */
#घोषणा CMD4_INTSCAN		BIT(0)
#घोषणा CMD4_EOIRCV		BIT(1)
#घोषणा CMD4_ECLKDRV		BIT(2)
#घोषणा CMD4_SEDIFF		BIT(3)
#घोषणा CMD4_ECLKRCV		BIT(4)
#घोषणा DIO_BASE_REG		0x10	/* R/W: 8255 DIO base reg */
#घोषणा COUNTER_A_BASE_REG	0x14	/* R/W: 8253 Counter A base reg */
#घोषणा COUNTER_B_BASE_REG	0x18	/* R/W: 8253 Counter B base reg */
#घोषणा CMD5_REG		0x1c	/* W: Command 5 reg */
#घोषणा CMD5_WRTPRT		BIT(2)
#घोषणा CMD5_DITHEREN		BIT(3)
#घोषणा CMD5_CALDACLD		BIT(4)
#घोषणा CMD5_SCLK		BIT(5)
#घोषणा CMD5_SDATA		BIT(6)
#घोषणा CMD5_EEPROMCS		BIT(7)
#घोषणा STAT2_REG		0x1d	/* R: Status 2 reg */
#घोषणा STAT2_PROMOUT		BIT(0)
#घोषणा STAT2_OUTA1		BIT(1)
#घोषणा STAT2_FIFONHF		BIT(2)
#घोषणा INTERVAL_COUNT_REG	0x1e	/* W: Interval Counter Data reg */
#घोषणा INTERVAL_STROBE_REG	0x1f	/* W: Interval Counter Strobe reg */

#पूर्ण_अगर /* _NI_LABPC_REGS_H */
