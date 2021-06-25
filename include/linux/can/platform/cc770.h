<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _CAN_PLATFORM_CC770_H
#घोषणा _CAN_PLATFORM_CC770_H

/* CPU Interface Register (0x02) */
#घोषणा CPUIF_CEN	0x01	/* Clock Out Enable */
#घोषणा CPUIF_MUX	0x04	/* Multiplex */
#घोषणा CPUIF_SLP	0x08	/* Sleep */
#घोषणा CPUIF_PWD	0x10	/* Power Down Mode */
#घोषणा CPUIF_DMC	0x20	/* Divide Memory Clock */
#घोषणा CPUIF_DSC	0x40	/* Divide System Clock */
#घोषणा CPUIF_RST	0x80	/* Hardware Reset Status */

/* Clock Out Register (0x1f) */
#घोषणा CLKOUT_CD_MASK  0x0f	/* Clock Divider mask */
#घोषणा CLKOUT_SL_MASK	0x30	/* Slew Rate mask */
#घोषणा CLKOUT_SL_SHIFT	4

/* Bus Configuration Register (0x2f) */
#घोषणा BUSCFG_DR0	0x01	/* Disconnect RX0 Input / Select RX input */
#घोषणा BUSCFG_DR1	0x02	/* Disconnect RX1 Input / Silent mode */
#घोषणा BUSCFG_DT1	0x08	/* Disconnect TX1 Output */
#घोषणा BUSCFG_POL	0x20	/* Polarity करोminant or recessive */
#घोषणा BUSCFG_CBY	0x40	/* Input Comparator Bypass */

काष्ठा cc770_platक्रमm_data अणु
	u32 osc_freq;	/* CAN bus oscillator frequency in Hz */

	u8 cir;		/* CPU Interface Register */
	u8 cor;		/* Clock Out Register */
	u8 bcr;		/* Bus Configuration Register */
पूर्ण;

#पूर्ण_अगर	/* !_CAN_PLATFORM_CC770_H */
