<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __DT_FSL_IMX_AUDMUX_H
#घोषणा __DT_FSL_IMX_AUDMUX_H

#घोषणा MX27_AUDMUX_HPCR1_SSI0		0
#घोषणा MX27_AUDMUX_HPCR2_SSI1		1
#घोषणा MX27_AUDMUX_HPCR3_SSI_PINS_4	2
#घोषणा MX27_AUDMUX_PPCR1_SSI_PINS_1	3
#घोषणा MX27_AUDMUX_PPCR2_SSI_PINS_2	4
#घोषणा MX27_AUDMUX_PPCR3_SSI_PINS_3	5

#घोषणा MX31_AUDMUX_PORT1_SSI0		0
#घोषणा MX31_AUDMUX_PORT2_SSI1		1
#घोषणा MX31_AUDMUX_PORT3_SSI_PINS_3	2
#घोषणा MX31_AUDMUX_PORT4_SSI_PINS_4	3
#घोषणा MX31_AUDMUX_PORT5_SSI_PINS_5	4
#घोषणा MX31_AUDMUX_PORT6_SSI_PINS_6	5
#घोषणा MX31_AUDMUX_PORT7_SSI_PINS_7	6

#घोषणा MX51_AUDMUX_PORT1_SSI0		0
#घोषणा MX51_AUDMUX_PORT2_SSI1		1
#घोषणा MX51_AUDMUX_PORT3		2
#घोषणा MX51_AUDMUX_PORT4		3
#घोषणा MX51_AUDMUX_PORT5		4
#घोषणा MX51_AUDMUX_PORT6		5
#घोषणा MX51_AUDMUX_PORT7		6

/*
 * TFCSEL/RFCSEL (i.MX27) or TFSEL/TCSEL/RFSEL/RCSEL (i.MX31/51/53/6Q)
 * can be sourced from Rx/Tx.
 */
#घोषणा IMX_AUDMUX_RXFS			0x8
#घोषणा IMX_AUDMUX_RXCLK		0x8

/* Register definitions क्रम the i.MX21/27 Digital Audio Multiplexer */
#घोषणा IMX_AUDMUX_V1_PCR_INMMASK(x)	((x) & 0xff)
#घोषणा IMX_AUDMUX_V1_PCR_INMEN		(1 << 8)
#घोषणा IMX_AUDMUX_V1_PCR_TXRXEN	(1 << 10)
#घोषणा IMX_AUDMUX_V1_PCR_SYN		(1 << 12)
#घोषणा IMX_AUDMUX_V1_PCR_RXDSEL(x)	(((x) & 0x7) << 13)
#घोषणा IMX_AUDMUX_V1_PCR_RFCSEL(x)	(((x) & 0xf) << 20)
#घोषणा IMX_AUDMUX_V1_PCR_RCLKसूची	(1 << 24)
#घोषणा IMX_AUDMUX_V1_PCR_RFSसूची	(1 << 25)
#घोषणा IMX_AUDMUX_V1_PCR_TFCSEL(x)	(((x) & 0xf) << 26)
#घोषणा IMX_AUDMUX_V1_PCR_TCLKसूची	(1 << 30)
#घोषणा IMX_AUDMUX_V1_PCR_TFSसूची	(1 << 31)

/* Register definitions क्रम the i.MX25/31/35/51 Digital Audio Multiplexer */
#घोषणा IMX_AUDMUX_V2_PTCR_TFSसूची	(1 << 31)
#घोषणा IMX_AUDMUX_V2_PTCR_TFSEL(x)	(((x) & 0xf) << 27)
#घोषणा IMX_AUDMUX_V2_PTCR_TCLKसूची	(1 << 26)
#घोषणा IMX_AUDMUX_V2_PTCR_TCSEL(x)	(((x) & 0xf) << 22)
#घोषणा IMX_AUDMUX_V2_PTCR_RFSसूची	(1 << 21)
#घोषणा IMX_AUDMUX_V2_PTCR_RFSEL(x)	(((x) & 0xf) << 17)
#घोषणा IMX_AUDMUX_V2_PTCR_RCLKसूची	(1 << 16)
#घोषणा IMX_AUDMUX_V2_PTCR_RCSEL(x)	(((x) & 0xf) << 12)
#घोषणा IMX_AUDMUX_V2_PTCR_SYN		(1 << 11)

#घोषणा IMX_AUDMUX_V2_PDCR_RXDSEL(x)	(((x) & 0x7) << 13)
#घोषणा IMX_AUDMUX_V2_PDCR_TXRXEN	(1 << 12)
#घोषणा IMX_AUDMUX_V2_PDCR_MODE(x)	(((x) & 0x3) << 8)
#घोषणा IMX_AUDMUX_V2_PDCR_INMMASK(x)	((x) & 0xff)

#पूर्ण_अगर /* __DT_FSL_IMX_AUDMUX_H */
