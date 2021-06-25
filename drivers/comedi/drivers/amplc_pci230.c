<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/drivers/amplc_pci230.c
 * Driver क्रम Amplicon PCI230 and PCI260 Multअगरunction I/O boards.
 *
 * Copyright (C) 2001 Allan Willcox <allanwillcox@ozemail.com.au>
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: amplc_pci230
 * Description: Amplicon PCI230, PCI260 Multअगरunction I/O boards
 * Author: Allan Willcox <allanwillcox@ozemail.com.au>,
 *   Steve D Sharples <steve.sharples@nottingham.ac.uk>,
 *   Ian Abbott <abbotti@mev.co.uk>
 * Updated: Mon, 01 Sep 2014 10:09:16 +0000
 * Devices: [Amplicon] PCI230 (amplc_pci230), PCI230+, PCI260, PCI260+
 * Status: works
 *
 * Configuration options:
 *   none
 *
 * Manual configuration of PCI cards is not supported; they are configured
 * स्वतःmatically.
 *
 * The PCI230+ and PCI260+ have the same PCI device IDs as the PCI230 and
 * PCI260, but can be distinguished by the size of the PCI regions.  A
 * card will be configured as a "+" model अगर detected as such.
 *
 * Subdevices:
 *
 *                 PCI230(+)    PCI260(+)
 *                 ---------    ---------
 *   Subdevices       3            1
 *         0          AI           AI
 *         1          AO
 *         2          DIO
 *
 * AI Subdevice:
 *
 *   The AI subdevice has 16 single-ended channels or 8 dअगरferential
 *   channels.
 *
 *   The PCI230 and PCI260 cards have 12-bit resolution.  The PCI230+ and
 *   PCI260+ cards have 16-bit resolution.
 *
 *   For dअगरferential mode, use inमाला_दो 2N and 2N+1 क्रम channel N (e.g. use
 *   inमाला_दो 14 and 15 क्रम channel 7).  If the card is physically a PCI230
 *   or PCI260 then it actually uses a "pseudo-differential" mode where the
 *   inमाला_दो are sampled a few microseconds apart.  The PCI230+ and PCI260+
 *   use true dअगरferential sampling.  Another dअगरference is that अगर the
 *   card is physically a PCI230 or PCI260, the inverting input is 2N,
 *   whereas क्रम a PCI230+ or PCI260+ the inverting input is 2N+1.  So अगर a
 *   PCI230 is physically replaced by a PCI230+ (or a PCI260 with a
 *   PCI260+) and dअगरferential mode is used, the dअगरferential inमाला_दो need
 *   to be physically swapped on the connector.
 *
 *   The following input ranges are supported:
 *
 *     0 => [-10, +10] V
 *     1 => [-5, +5] V
 *     2 => [-2.5, +2.5] V
 *     3 => [-1.25, +1.25] V
 *     4 => [0, 10] V
 *     5 => [0, 5] V
 *     6 => [0, 2.5] V
 *
 * AI Commands:
 *
 *   +=========+==============+===========+============+==========+
 *   |start_src|scan_begin_src|convert_src|scan_end_src| stop_src |
 *   +=========+==============+===========+============+==========+
 *   |TRIG_NOW | TRIG_FOLLOW  |TRIG_TIMER | TRIG_COUNT |TRIG_NONE |
 *   |TRIG_INT |              |TRIG_EXT(3)|            |TRIG_COUNT|
 *   |         |              |TRIG_INT   |            |          |
 *   |         |--------------|-----------|            |          |
 *   |         | TRIG_TIMER(1)|TRIG_TIMER |            |          |
 *   |         | TRIG_EXT(2)  |           |            |          |
 *   |         | TRIG_INT     |           |            |          |
 *   +---------+--------------+-----------+------------+----------+
 *
 *   Note 1: If AI command and AO command are used simultaneously, only
 *           one may have scan_begin_src == TRIG_TIMER.
 *
 *   Note 2: For PCI230 and PCI230+, scan_begin_src == TRIG_EXT uses
 *           DIO channel 16 (pin 49) which will need to be configured as
 *           a digital input.  For PCI260+, the EXTTRIG/EXTCONVCLK input
 *           (pin 17) is used instead.  For PCI230, scan_begin_src ==
 *           TRIG_EXT is not supported.  The trigger is a rising edge
 *           on the input.
 *
 *   Note 3: For convert_src == TRIG_EXT, the EXTTRIG/EXTCONVCLK input
 *           (pin 25 on PCI230(+), pin 17 on PCI260(+)) is used.  The
 *           convert_arg value is पूर्णांकerpreted as follows:
 *
 *             convert_arg == (CR_EDGE | 0) => rising edge
 *             convert_arg == (CR_EDGE | CR_INVERT | 0) => falling edge
 *             convert_arg == 0 => falling edge (backwards compatibility)
 *             convert_arg == 1 => rising edge (backwards compatibility)
 *
 *   All entries in the channel list must use the same analogue reference.
 *   If the analogue reference is not AREF_DIFF (not dअगरferential) each
 *   pair of channel numbers (0 and 1, 2 and 3, etc.) must use the same
 *   input range.  The input ranges used in the sequence must be all
 *   bipolar (ranges 0 to 3) or all unipolar (ranges 4 to 6).  The channel
 *   sequence must consist of 1 or more identical subsequences.  Within the
 *   subsequence, channels must be in ascending order with no repeated
 *   channels.  For example, the following sequences are valid: 0 1 2 3
 *   (single valid subsequence), 0 2 3 5 0 2 3 5 (repeated valid
 *   subsequence), 1 1 1 1 (repeated valid subsequence).  The following
 *   sequences are invalid: 0 3 2 1 (invalid subsequence), 0 2 3 5 0 2 3
 *   (incompletely repeated subsequence).  Some versions of the PCI230+ and
 *   PCI260+ have a bug that requires a subsequence दीर्घer than one entry
 *   दीर्घ to include channel 0.
 *
 * AO Subdevice:
 *
 *   The AO subdevice has 2 channels with 12-bit resolution.
 *   The following output ranges are supported:
 *     0 => [0, 10] V
 *     1 => [-10, +10] V
 *
 * AO Commands:
 *
 *   +=========+==============+===========+============+==========+
 *   |start_src|scan_begin_src|convert_src|scan_end_src| stop_src |
 *   +=========+==============+===========+============+==========+
 *   |TRIG_INT | TRIG_TIMER(1)| TRIG_NOW  | TRIG_COUNT |TRIG_NONE |
 *   |         | TRIG_EXT(2)  |           |            |TRIG_COUNT|
 *   |         | TRIG_INT     |           |            |          |
 *   +---------+--------------+-----------+------------+----------+
 *
 *   Note 1: If AI command and AO command are used simultaneously, only
 *           one may have scan_begin_src == TRIG_TIMER.
 *
 *   Note 2: scan_begin_src == TRIG_EXT is only supported अगर the card is
 *           configured as a PCI230+ and is only supported on later
 *           versions of the card.  As a card configured as a PCI230+ is
 *           not guaranteed to support बाह्यal triggering, please consider
 *           this support to be a bonus.  It uses the EXTTRIG/ EXTCONVCLK
 *           input (PCI230+ pin 25).  Triggering will be on the rising edge
 *           unless the CR_INVERT flag is set in scan_begin_arg.
 *
 *   The channels in the channel sequence must be in ascending order with
 *   no repeats.  All entries in the channel sequence must use the same
 *   output range.
 *
 * DIO Subdevice:
 *
 *   The DIO subdevice is a 8255 chip providing 24 DIO channels.  The DIO
 *   channels are configurable as inमाला_दो or outमाला_दो in four groups:
 *
 *     Port A  - channels  0 to  7
 *     Port B  - channels  8 to 15
 *     Port CL - channels 16 to 19
 *     Port CH - channels 20 to 23
 *
 *   Only mode 0 of the 8255 chip is supported.
 *
 *   Bit 0 of port C (DIO channel 16) is also used as an बाह्यal scan
 *   trigger input क्रम AI commands on PCI230 and PCI230+, so would need to
 *   be configured as an input to use it क्रम that purpose.
 */

/*
 * Extra triggered scan functionality, पूर्णांकerrupt bug-fix added by Steve
 * Sharples.  Support क्रम PCI230+/260+, more triggered scan functionality,
 * and workarounds क्रम (or detection of) various hardware problems added
 * by Ian Abbott.
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "../comedi_pci.h"

#समावेश "comedi_8254.h"
#समावेश "8255.h"

/*
 * PCI230 PCI configuration रेजिस्टर inक्रमmation
 */
#घोषणा PCI_DEVICE_ID_PCI230 0x0000
#घोषणा PCI_DEVICE_ID_PCI260 0x0006

/*
 * PCI230 i/o space 1 रेजिस्टरs.
 */
#घोषणा PCI230_PPI_X_BASE	0x00	/* User PPI (82C55) base */
#घोषणा PCI230_PPI_X_A		0x00	/* User PPI (82C55) port A */
#घोषणा PCI230_PPI_X_B		0x01	/* User PPI (82C55) port B */
#घोषणा PCI230_PPI_X_C		0x02	/* User PPI (82C55) port C */
#घोषणा PCI230_PPI_X_CMD	0x03	/* User PPI (82C55) control word */
#घोषणा PCI230_Z2_CT_BASE	0x14	/* 82C54 counter/समयr base */
#घोषणा PCI230_ZCLK_SCE		0x1A	/* Group Z Clock Configuration */
#घोषणा PCI230_ZGAT_SCE		0x1D	/* Group Z Gate Configuration */
#घोषणा PCI230_INT_SCE		0x1E	/* Interrupt source mask (w) */
#घोषणा PCI230_INT_STAT		0x1E	/* Interrupt status (r) */

/*
 * PCI230 i/o space 2 रेजिस्टरs.
 */
#घोषणा PCI230_DACCON		0x00	/* DAC control */
#घोषणा PCI230_DACOUT1		0x02	/* DAC channel 0 (w) */
#घोषणा PCI230_DACOUT2		0x04	/* DAC channel 1 (w) (not FIFO mode) */
#घोषणा PCI230_ADCDATA		0x08	/* ADC data (r) */
#घोषणा PCI230_ADCSWTRIG	0x08	/* ADC software trigger (w) */
#घोषणा PCI230_ADCCON		0x0A	/* ADC control */
#घोषणा PCI230_ADCEN		0x0C	/* ADC channel enable bits */
#घोषणा PCI230_ADCG		0x0E	/* ADC gain control bits */
/* PCI230+ i/o space 2 additional रेजिस्टरs. */
#घोषणा PCI230P_ADCTRIG		0x10	/* ADC start acquisition trigger */
#घोषणा PCI230P_ADCTH		0x12	/* ADC analog trigger threshold */
#घोषणा PCI230P_ADCFFTH		0x14	/* ADC FIFO पूर्णांकerrupt threshold */
#घोषणा PCI230P_ADCFFLEV	0x16	/* ADC FIFO level (r) */
#घोषणा PCI230P_ADCPTSC		0x18	/* ADC pre-trigger sample count (r) */
#घोषणा PCI230P_ADCHYST		0x1A	/* ADC analog trigger hysteresys */
#घोषणा PCI230P_EXTFUNC		0x1C	/* Extended functions */
#घोषणा PCI230P_HWVER		0x1E	/* Hardware version (r) */
/* PCI230+ hardware version 2 onwards. */
#घोषणा PCI230P2_DACDATA	0x02	/* DAC data (FIFO mode) (w) */
#घोषणा PCI230P2_DACSWTRIG	0x02	/* DAC soft trigger (FIFO mode) (r) */
#घोषणा PCI230P2_DACEN		0x06	/* DAC channel enable (FIFO mode) */

/*
 * DACCON पढ़ो-ग_लिखो values.
 */
#घोषणा PCI230_DAC_OR(x)		(((x) & 0x1) << 0)
#घोषणा PCI230_DAC_OR_UNI		PCI230_DAC_OR(0) /* Output unipolar */
#घोषणा PCI230_DAC_OR_BIP		PCI230_DAC_OR(1) /* Output bipolar */
#घोषणा PCI230_DAC_OR_MASK		PCI230_DAC_OR(1)
/*
 * The following applies only अगर DAC FIFO support is enabled in the EXTFUNC
 * रेजिस्टर (and only क्रम PCI230+ hardware version 2 onwards).
 */
#घोषणा PCI230P2_DAC_FIFO_EN		BIT(8) /* FIFO enable */
/*
 * The following apply only अगर the DAC FIFO is enabled (and only क्रम PCI230+
 * hardware version 2 onwards).
 */
#घोषणा PCI230P2_DAC_TRIG(x)		(((x) & 0x7) << 2)
#घोषणा PCI230P2_DAC_TRIG_NONE		PCI230P2_DAC_TRIG(0) /* none */
#घोषणा PCI230P2_DAC_TRIG_SW		PCI230P2_DAC_TRIG(1) /* soft trig */
#घोषणा PCI230P2_DAC_TRIG_EXTP		PCI230P2_DAC_TRIG(2) /* ext + edge */
#घोषणा PCI230P2_DAC_TRIG_EXTN		PCI230P2_DAC_TRIG(3) /* ext - edge */
#घोषणा PCI230P2_DAC_TRIG_Z2CT0		PCI230P2_DAC_TRIG(4) /* Z2 CT0 out */
#घोषणा PCI230P2_DAC_TRIG_Z2CT1		PCI230P2_DAC_TRIG(5) /* Z2 CT1 out */
#घोषणा PCI230P2_DAC_TRIG_Z2CT2		PCI230P2_DAC_TRIG(6) /* Z2 CT2 out */
#घोषणा PCI230P2_DAC_TRIG_MASK		PCI230P2_DAC_TRIG(7)
#घोषणा PCI230P2_DAC_FIFO_WRAP		BIT(7) /* FIFO wraparound mode */
#घोषणा PCI230P2_DAC_INT_FIFO(x)	(((x) & 7) << 9)
#घोषणा PCI230P2_DAC_INT_FIFO_EMPTY	PCI230P2_DAC_INT_FIFO(0) /* empty */
#घोषणा PCI230P2_DAC_INT_FIFO_NEMPTY	PCI230P2_DAC_INT_FIFO(1) /* !empty */
#घोषणा PCI230P2_DAC_INT_FIFO_NHALF	PCI230P2_DAC_INT_FIFO(2) /* !half */
#घोषणा PCI230P2_DAC_INT_FIFO_HALF	PCI230P2_DAC_INT_FIFO(3) /* half */
#घोषणा PCI230P2_DAC_INT_FIFO_NFULL	PCI230P2_DAC_INT_FIFO(4) /* !full */
#घोषणा PCI230P2_DAC_INT_FIFO_FULL	PCI230P2_DAC_INT_FIFO(5) /* full */
#घोषणा PCI230P2_DAC_INT_FIFO_MASK	PCI230P2_DAC_INT_FIFO(7)

/*
 * DACCON पढ़ो-only values.
 */
#घोषणा PCI230_DAC_BUSY			BIT(1) /* DAC busy. */
/*
 * The following apply only अगर the DAC FIFO is enabled (and only क्रम PCI230+
 * hardware version 2 onwards).
 */
#घोषणा PCI230P2_DAC_FIFO_UNDERRUN_LATCHED	BIT(5) /* Underrun error */
#घोषणा PCI230P2_DAC_FIFO_EMPTY		BIT(13) /* FIFO empty */
#घोषणा PCI230P2_DAC_FIFO_FULL		BIT(14) /* FIFO full */
#घोषणा PCI230P2_DAC_FIFO_HALF		BIT(15) /* FIFO half full */

/*
 * DACCON ग_लिखो-only, transient values.
 */
/*
 * The following apply only अगर the DAC FIFO is enabled (and only क्रम PCI230+
 * hardware version 2 onwards).
 */
#घोषणा PCI230P2_DAC_FIFO_UNDERRUN_CLEAR	BIT(5) /* Clear underrun */
#घोषणा PCI230P2_DAC_FIFO_RESET		BIT(12) /* FIFO reset */

/*
 * PCI230+ hardware version 2 DAC FIFO levels.
 */
#घोषणा PCI230P2_DAC_FIFOLEVEL_HALF	512
#घोषणा PCI230P2_DAC_FIFOLEVEL_FULL	1024
/* Free space in DAC FIFO. */
#घोषणा PCI230P2_DAC_FIFOROOM_EMPTY		PCI230P2_DAC_FIFOLEVEL_FULL
#घोषणा PCI230P2_DAC_FIFOROOM_ONETOHALF		\
	(PCI230P2_DAC_FIFOLEVEL_FULL - PCI230P2_DAC_FIFOLEVEL_HALF)
#घोषणा PCI230P2_DAC_FIFOROOM_HALFTOFULL	1
#घोषणा PCI230P2_DAC_FIFOROOM_FULL		0

/*
 * ADCCON पढ़ो/ग_लिखो values.
 */
#घोषणा PCI230_ADC_TRIG(x)		(((x) & 0x7) << 0)
#घोषणा PCI230_ADC_TRIG_NONE		PCI230_ADC_TRIG(0) /* none */
#घोषणा PCI230_ADC_TRIG_SW		PCI230_ADC_TRIG(1) /* soft trig */
#घोषणा PCI230_ADC_TRIG_EXTP		PCI230_ADC_TRIG(2) /* ext + edge */
#घोषणा PCI230_ADC_TRIG_EXTN		PCI230_ADC_TRIG(3) /* ext - edge */
#घोषणा PCI230_ADC_TRIG_Z2CT0		PCI230_ADC_TRIG(4) /* Z2 CT0 out*/
#घोषणा PCI230_ADC_TRIG_Z2CT1		PCI230_ADC_TRIG(5) /* Z2 CT1 out */
#घोषणा PCI230_ADC_TRIG_Z2CT2		PCI230_ADC_TRIG(6) /* Z2 CT2 out */
#घोषणा PCI230_ADC_TRIG_MASK		PCI230_ADC_TRIG(7)
#घोषणा PCI230_ADC_IR(x)		(((x) & 0x1) << 3)
#घोषणा PCI230_ADC_IR_UNI		PCI230_ADC_IR(0) /* Input unipolar */
#घोषणा PCI230_ADC_IR_BIP		PCI230_ADC_IR(1) /* Input bipolar */
#घोषणा PCI230_ADC_IR_MASK		PCI230_ADC_IR(1)
#घोषणा PCI230_ADC_IM(x)		(((x) & 0x1) << 4)
#घोषणा PCI230_ADC_IM_SE		PCI230_ADC_IM(0) /* single ended */
#घोषणा PCI230_ADC_IM_DIF		PCI230_ADC_IM(1) /* dअगरferential */
#घोषणा PCI230_ADC_IM_MASK		PCI230_ADC_IM(1)
#घोषणा PCI230_ADC_FIFO_EN		BIT(8) /* FIFO enable */
#घोषणा PCI230_ADC_INT_FIFO(x)		(((x) & 0x7) << 9)
#घोषणा PCI230_ADC_INT_FIFO_EMPTY	PCI230_ADC_INT_FIFO(0) /* empty */
#घोषणा PCI230_ADC_INT_FIFO_NEMPTY	PCI230_ADC_INT_FIFO(1) /* !empty */
#घोषणा PCI230_ADC_INT_FIFO_NHALF	PCI230_ADC_INT_FIFO(2) /* !half */
#घोषणा PCI230_ADC_INT_FIFO_HALF	PCI230_ADC_INT_FIFO(3) /* half */
#घोषणा PCI230_ADC_INT_FIFO_NFULL	PCI230_ADC_INT_FIFO(4) /* !full */
#घोषणा PCI230_ADC_INT_FIFO_FULL	PCI230_ADC_INT_FIFO(5) /* full */
#घोषणा PCI230P_ADC_INT_FIFO_THRESH	PCI230_ADC_INT_FIFO(7) /* threshold */
#घोषणा PCI230_ADC_INT_FIFO_MASK	PCI230_ADC_INT_FIFO(7)

/*
 * ADCCON ग_लिखो-only, transient values.
 */
#घोषणा PCI230_ADC_FIFO_RESET		BIT(12) /* FIFO reset */
#घोषणा PCI230_ADC_GLOB_RESET		BIT(13) /* Global reset */

/*
 * ADCCON पढ़ो-only values.
 */
#घोषणा PCI230_ADC_BUSY			BIT(15) /* ADC busy */
#घोषणा PCI230_ADC_FIFO_EMPTY		BIT(12) /* FIFO empty */
#घोषणा PCI230_ADC_FIFO_FULL		BIT(13) /* FIFO full */
#घोषणा PCI230_ADC_FIFO_HALF		BIT(14) /* FIFO half full */
#घोषणा PCI230_ADC_FIFO_FULL_LATCHED	BIT(5)  /* FIFO overrun occurred */

/*
 * PCI230 ADC FIFO levels.
 */
#घोषणा PCI230_ADC_FIFOLEVEL_HALFFULL	2049	/* Value क्रम FIFO half full */
#घोषणा PCI230_ADC_FIFOLEVEL_FULL	4096	/* FIFO size */

/*
 * PCI230+ EXTFUNC values.
 */
/* Route EXTTRIG pin to बाह्यal gate inमाला_दो. */
#घोषणा PCI230P_EXTFUNC_GAT_EXTTRIG	BIT(0)
/* PCI230+ hardware version 2 values. */
/* Allow DAC FIFO to be enabled. */
#घोषणा PCI230P2_EXTFUNC_DACFIFO	BIT(1)

/*
 * Counter/समयr घड़ी input configuration sources.
 */
#घोषणा CLK_CLK		0	/* reserved (channel-specअगरic घड़ी) */
#घोषणा CLK_10MHZ	1	/* पूर्णांकernal 10 MHz घड़ी */
#घोषणा CLK_1MHZ	2	/* पूर्णांकernal 1 MHz घड़ी */
#घोषणा CLK_100KHZ	3	/* पूर्णांकernal 100 kHz घड़ी */
#घोषणा CLK_10KHZ	4	/* पूर्णांकernal 10 kHz घड़ी */
#घोषणा CLK_1KHZ	5	/* पूर्णांकernal 1 kHz घड़ी */
#घोषणा CLK_OUTNM1	6	/* output of channel-1 modulo total */
#घोषणा CLK_EXT		7	/* बाह्यal घड़ी */

अटल अचिन्हित पूर्णांक pci230_clk_config(अचिन्हित पूर्णांक chan, अचिन्हित पूर्णांक src)
अणु
	वापस ((chan & 3) << 3) | (src & 7);
पूर्ण

/*
 * Counter/समयr gate input configuration sources.
 */
#घोषणा GAT_VCC		0	/* VCC (i.e. enabled) */
#घोषणा GAT_GND		1	/* GND (i.e. disabled) */
#घोषणा GAT_EXT		2	/* बाह्यal gate input (PPCn on PCI230) */
#घोषणा GAT_NOUTNM2	3	/* inverted output of channel-2 modulo total */

अटल अचिन्हित पूर्णांक pci230_gat_config(अचिन्हित पूर्णांक chan, अचिन्हित पूर्णांक src)
अणु
	वापस ((chan & 3) << 3) | (src & 7);
पूर्ण

/*
 * Summary of CLK_OUTNM1 and GAT_NOUTNM2 connections क्रम PCI230 and PCI260:
 *
 *              Channel's       Channel's
 *              घड़ी input     gate input
 * Channel      CLK_OUTNM1      GAT_NOUTNM2
 * -------      ----------      -----------
 * Z2-CT0       Z2-CT2-OUT      /Z2-CT1-OUT
 * Z2-CT1       Z2-CT0-OUT      /Z2-CT2-OUT
 * Z2-CT2       Z2-CT1-OUT      /Z2-CT0-OUT
 */

/*
 * Interrupt enables/status रेजिस्टर values.
 */
#घोषणा PCI230_INT_DISABLE		0
#घोषणा PCI230_INT_PPI_C0		BIT(0)
#घोषणा PCI230_INT_PPI_C3		BIT(1)
#घोषणा PCI230_INT_ADC			BIT(2)
#घोषणा PCI230_INT_ZCLK_CT1		BIT(5)
/* For PCI230+ hardware version 2 when DAC FIFO enabled. */
#घोषणा PCI230P2_INT_DAC		BIT(4)

/*
 * (Potentially) shared resources and their owners
 */
क्रमागत अणु
	RES_Z2CT0 = BIT(0),	/* Z2-CT0 */
	RES_Z2CT1 = BIT(1),	/* Z2-CT1 */
	RES_Z2CT2 = BIT(2)	/* Z2-CT2 */
पूर्ण;

क्रमागत अणु
	OWNER_AICMD,		/* Owned by AI command */
	OWNER_AOCMD,		/* Owned by AO command */
	NUM_OWNERS		/* Number of owners */
पूर्ण;

/*
 * Handy macros.
 */

/* Combine old and new bits. */
#घोषणा COMBINE(old, new, mask)	(((old) & ~(mask)) | ((new) & (mask)))

/* Current CPU.  XXX should this be hard_smp_processor_id()? */
#घोषणा THISCPU		smp_processor_id()

/*
 * Board descriptions क्रम the two boards supported.
 */

काष्ठा pci230_board अणु
	स्थिर अक्षर *name;
	अचिन्हित लघु id;
	अचिन्हित अक्षर ai_bits;
	अचिन्हित अक्षर ao_bits;
	अचिन्हित अक्षर min_hwver; /* Minimum hardware version supported. */
	अचिन्हित पूर्णांक have_dio:1;
पूर्ण;

अटल स्थिर काष्ठा pci230_board pci230_boards[] = अणु
	अणु
		.name		= "pci230+",
		.id		= PCI_DEVICE_ID_PCI230,
		.ai_bits	= 16,
		.ao_bits	= 12,
		.have_dio	= true,
		.min_hwver	= 1,
	पूर्ण,
	अणु
		.name		= "pci260+",
		.id		= PCI_DEVICE_ID_PCI260,
		.ai_bits	= 16,
		.min_hwver	= 1,
	पूर्ण,
	अणु
		.name		= "pci230",
		.id		= PCI_DEVICE_ID_PCI230,
		.ai_bits	= 12,
		.ao_bits	= 12,
		.have_dio	= true,
	पूर्ण,
	अणु
		.name		= "pci260",
		.id		= PCI_DEVICE_ID_PCI260,
		.ai_bits	= 12,
	पूर्ण,
पूर्ण;

काष्ठा pci230_निजी अणु
	spinlock_t isr_spinlock;	/* Interrupt spin lock */
	spinlock_t res_spinlock;	/* Shared resources spin lock */
	spinlock_t ai_stop_spinlock;	/* Spin lock क्रम stopping AI command */
	spinlock_t ao_stop_spinlock;	/* Spin lock क्रम stopping AO command */
	अचिन्हित दीर्घ daqio;		/* PCI230's DAQ I/O space */
	पूर्णांक पूर्णांकr_cpuid;			/* ID of CPU running ISR */
	अचिन्हित लघु hwver;		/* Hardware version (क्रम '+' models) */
	अचिन्हित लघु adccon;		/* ADCCON रेजिस्टर value */
	अचिन्हित लघु daccon;		/* DACCON रेजिस्टर value */
	अचिन्हित लघु adcfअगरothresh;	/* ADC FIFO threshold (PCI230+/260+) */
	अचिन्हित लघु adcg;		/* ADCG रेजिस्टर value */
	अचिन्हित अक्षर ier;		/* Interrupt enable bits */
	अचिन्हित अक्षर res_owned[NUM_OWNERS]; /* Owned resources */
	अचिन्हित पूर्णांक पूर्णांकr_running:1;	/* Flag set in पूर्णांकerrupt routine */
	अचिन्हित पूर्णांक ai_bipolar:1;	/* Flag AI range is bipolar */
	अचिन्हित पूर्णांक ao_bipolar:1;	/* Flag AO range is bipolar */
	अचिन्हित पूर्णांक ai_cmd_started:1;	/* Flag AI command started */
	अचिन्हित पूर्णांक ao_cmd_started:1;	/* Flag AO command started */
पूर्ण;

/* PCI230 घड़ी source periods in ns */
अटल स्थिर अचिन्हित पूर्णांक pci230_समयbase[8] = अणु
	[CLK_10MHZ]	= I8254_OSC_BASE_10MHZ,
	[CLK_1MHZ]	= I8254_OSC_BASE_1MHZ,
	[CLK_100KHZ]	= I8254_OSC_BASE_100KHZ,
	[CLK_10KHZ]	= I8254_OSC_BASE_10KHZ,
	[CLK_1KHZ]	= I8254_OSC_BASE_1KHZ,
पूर्ण;

/* PCI230 analogue input range table */
अटल स्थिर काष्ठा comedi_lrange pci230_ai_range = अणु
	7, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1.25),
		UNI_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(2.5)
	पूर्ण
पूर्ण;

/* PCI230 analogue gain bits क्रम each input range. */
अटल स्थिर अचिन्हित अक्षर pci230_ai_gain[7] = अणु 0, 1, 2, 3, 1, 2, 3 पूर्ण;

/* PCI230 analogue output range table */
अटल स्थिर काष्ठा comedi_lrange pci230_ao_range = अणु
	2, अणु
		UNI_RANGE(10),
		BIP_RANGE(10)
	पूर्ण
पूर्ण;

अटल अचिन्हित लघु pci230_ai_पढ़ो(काष्ठा comedi_device *dev)
अणु
	स्थिर काष्ठा pci230_board *board = dev->board_ptr;
	काष्ठा pci230_निजी *devpriv = dev->निजी;
	अचिन्हित लघु data;

	/* Read sample. */
	data = inw(devpriv->daqio + PCI230_ADCDATA);
	/*
	 * PCI230 is 12 bit - stored in upper bits of 16 bit रेजिस्टर
	 * (lower four bits reserved क्रम expansion).  PCI230+ is 16 bit AI.
	 *
	 * If a bipolar range was specअगरied, mangle it
	 * (twos complement->straight binary).
	 */
	अगर (devpriv->ai_bipolar)
		data ^= 0x8000;
	data >>= (16 - board->ai_bits);
	वापस data;
पूर्ण

अटल अचिन्हित लघु pci230_ao_mangle_datum(काष्ठा comedi_device *dev,
					     अचिन्हित लघु datum)
अणु
	स्थिर काष्ठा pci230_board *board = dev->board_ptr;
	काष्ठा pci230_निजी *devpriv = dev->निजी;

	/*
	 * PCI230 is 12 bit - stored in upper bits of 16 bit रेजिस्टर (lower
	 * four bits reserved क्रम expansion).  PCI230+ is also 12 bit AO.
	 */
	datum <<= (16 - board->ao_bits);
	/*
	 * If a bipolar range was specअगरied, mangle it
	 * (straight binary->twos complement).
	 */
	अगर (devpriv->ao_bipolar)
		datum ^= 0x8000;
	वापस datum;
पूर्ण

अटल व्योम pci230_ao_ग_लिखो_nofअगरo(काष्ठा comedi_device *dev,
				   अचिन्हित लघु datum, अचिन्हित पूर्णांक chan)
अणु
	काष्ठा pci230_निजी *devpriv = dev->निजी;

	/* Write mangled datum to appropriate DACOUT रेजिस्टर. */
	outw(pci230_ao_mangle_datum(dev, datum),
	     devpriv->daqio + ((chan == 0) ? PCI230_DACOUT1 : PCI230_DACOUT2));
पूर्ण

अटल व्योम pci230_ao_ग_लिखो_fअगरo(काष्ठा comedi_device *dev,
				 अचिन्हित लघु datum, अचिन्हित पूर्णांक chan)
अणु
	काष्ठा pci230_निजी *devpriv = dev->निजी;

	/* Write mangled datum to appropriate DACDATA रेजिस्टर. */
	outw(pci230_ao_mangle_datum(dev, datum),
	     devpriv->daqio + PCI230P2_DACDATA);
पूर्ण

अटल bool pci230_claim_shared(काष्ठा comedi_device *dev,
				अचिन्हित अक्षर res_mask, अचिन्हित पूर्णांक owner)
अणु
	काष्ठा pci230_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक o;
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&devpriv->res_spinlock, irqflags);
	क्रम (o = 0; o < NUM_OWNERS; o++) अणु
		अगर (o == owner)
			जारी;
		अगर (devpriv->res_owned[o] & res_mask) अणु
			spin_unlock_irqrestore(&devpriv->res_spinlock,
					       irqflags);
			वापस false;
		पूर्ण
	पूर्ण
	devpriv->res_owned[owner] |= res_mask;
	spin_unlock_irqrestore(&devpriv->res_spinlock, irqflags);
	वापस true;
पूर्ण

अटल व्योम pci230_release_shared(काष्ठा comedi_device *dev,
				  अचिन्हित अक्षर res_mask, अचिन्हित पूर्णांक owner)
अणु
	काष्ठा pci230_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&devpriv->res_spinlock, irqflags);
	devpriv->res_owned[owner] &= ~res_mask;
	spin_unlock_irqrestore(&devpriv->res_spinlock, irqflags);
पूर्ण

अटल व्योम pci230_release_all_resources(काष्ठा comedi_device *dev,
					 अचिन्हित पूर्णांक owner)
अणु
	pci230_release_shared(dev, (अचिन्हित अक्षर)~0, owner);
पूर्ण

अटल अचिन्हित पूर्णांक pci230_भागide_ns(u64 ns, अचिन्हित पूर्णांक समयbase,
				     अचिन्हित पूर्णांक flags)
अणु
	u64 भाग;
	अचिन्हित पूर्णांक rem;

	भाग = ns;
	rem = करो_भाग(भाग, समयbase);
	चयन (flags & CMDF_ROUND_MASK) अणु
	शेष:
	हाल CMDF_ROUND_NEAREST:
		भाग += DIV_ROUND_CLOSEST(rem, समयbase);
		अवरोध;
	हाल CMDF_ROUND_DOWN:
		अवरोध;
	हाल CMDF_ROUND_UP:
		भाग += DIV_ROUND_UP(rem, समयbase);
		अवरोध;
	पूर्ण
	वापस भाग > अच_पूर्णांक_उच्च ? अच_पूर्णांक_उच्च : (अचिन्हित पूर्णांक)भाग;
पूर्ण

/*
 * Given desired period in ns, वापसs the required पूर्णांकernal घड़ी source
 * and माला_लो the initial count.
 */
अटल अचिन्हित पूर्णांक pci230_choose_clk_count(u64 ns, अचिन्हित पूर्णांक *count,
					    अचिन्हित पूर्णांक flags)
अणु
	अचिन्हित पूर्णांक clk_src, cnt;

	क्रम (clk_src = CLK_10MHZ;; clk_src++) अणु
		cnt = pci230_भागide_ns(ns, pci230_समयbase[clk_src], flags);
		अगर (cnt <= 65536 || clk_src == CLK_1KHZ)
			अवरोध;
	पूर्ण
	*count = cnt;
	वापस clk_src;
पूर्ण

अटल व्योम pci230_ns_to_single_समयr(अचिन्हित पूर्णांक *ns, अचिन्हित पूर्णांक flags)
अणु
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक clk_src;

	clk_src = pci230_choose_clk_count(*ns, &count, flags);
	*ns = count * pci230_समयbase[clk_src];
पूर्ण

अटल व्योम pci230_ct_setup_ns_mode(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक ct,
				    अचिन्हित पूर्णांक mode, u64 ns,
				    अचिन्हित पूर्णांक flags)
अणु
	अचिन्हित पूर्णांक clk_src;
	अचिन्हित पूर्णांक count;

	/* Set mode. */
	comedi_8254_set_mode(dev->pacer, ct, mode);
	/* Determine घड़ी source and count. */
	clk_src = pci230_choose_clk_count(ns, &count, flags);
	/* Program घड़ी source. */
	outb(pci230_clk_config(ct, clk_src), dev->iobase + PCI230_ZCLK_SCE);
	/* Set initial count. */
	अगर (count >= 65536)
		count = 0;

	comedi_8254_ग_लिखो(dev->pacer, ct, count);
पूर्ण

अटल व्योम pci230_cancel_ct(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक ct)
अणु
	/* Counter ct, 8254 mode 1, initial count not written. */
	comedi_8254_set_mode(dev->pacer, ct, I8254_MODE1);
पूर्ण

अटल पूर्णांक pci230_ai_eoc(काष्ठा comedi_device *dev,
			 काष्ठा comedi_subdevice *s,
			 काष्ठा comedi_insn *insn,
			 अचिन्हित दीर्घ context)
अणु
	काष्ठा pci230_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक status;

	status = inw(devpriv->daqio + PCI230_ADCCON);
	अगर ((status & PCI230_ADC_FIFO_EMPTY) == 0)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक pci230_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	काष्ठा pci230_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक n;
	अचिन्हित पूर्णांक chan, range, aref;
	अचिन्हित पूर्णांक gainshअगरt;
	अचिन्हित लघु adccon, adcen;
	पूर्णांक ret;

	/* Unpack channel and range. */
	chan = CR_CHAN(insn->chanspec);
	range = CR_RANGE(insn->chanspec);
	aref = CR_AREF(insn->chanspec);
	अगर (aref == AREF_DIFF) अणु
		/* Dअगरferential. */
		अगर (chan >= s->n_chan / 2) अणु
			dev_dbg(dev->class_dev,
				"%s: differential channel number out of range 0 to %u\n",
				__func__, (s->n_chan / 2) - 1);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/*
	 * Use Z2-CT2 as a conversion trigger instead of the built-in
	 * software trigger, as otherwise triggering of dअगरferential channels
	 * करोesn't work properly क्रम some versions of PCI230/260.  Also set
	 * FIFO mode because the ADC busy bit only works क्रम software triggers.
	 */
	adccon = PCI230_ADC_TRIG_Z2CT2 | PCI230_ADC_FIFO_EN;
	/* Set Z2-CT2 output low to aव्योम any false triggers. */
	comedi_8254_set_mode(dev->pacer, 2, I8254_MODE0);
	devpriv->ai_bipolar = comedi_range_is_bipolar(s, range);
	अगर (aref == AREF_DIFF) अणु
		/* Dअगरferential. */
		gainshअगरt = chan * 2;
		अगर (devpriv->hwver == 0) अणु
			/*
			 * Original PCI230/260 expects both inमाला_दो of the
			 * dअगरferential channel to be enabled.
			 */
			adcen = 3 << gainshअगरt;
		पूर्ण अन्यथा अणु
			/*
			 * PCI230+/260+ expects only one input of the
			 * dअगरferential channel to be enabled.
			 */
			adcen = 1 << gainshअगरt;
		पूर्ण
		adccon |= PCI230_ADC_IM_DIF;
	पूर्ण अन्यथा अणु
		/* Single ended. */
		adcen = 1 << chan;
		gainshअगरt = chan & ~1;
		adccon |= PCI230_ADC_IM_SE;
	पूर्ण
	devpriv->adcg = (devpriv->adcg & ~(3 << gainshअगरt)) |
			(pci230_ai_gain[range] << gainshअगरt);
	अगर (devpriv->ai_bipolar)
		adccon |= PCI230_ADC_IR_BIP;
	अन्यथा
		adccon |= PCI230_ADC_IR_UNI;

	/*
	 * Enable only this channel in the scan list - otherwise by शेष
	 * we'll get one sample from each channel.
	 */
	outw(adcen, devpriv->daqio + PCI230_ADCEN);

	/* Set gain क्रम channel. */
	outw(devpriv->adcg, devpriv->daqio + PCI230_ADCG);

	/* Specअगरy uni/bip, se/dअगरf, conversion source, and reset FIFO. */
	devpriv->adccon = adccon;
	outw(adccon | PCI230_ADC_FIFO_RESET, devpriv->daqio + PCI230_ADCCON);

	/* Convert n samples */
	क्रम (n = 0; n < insn->n; n++) अणु
		/*
		 * Trigger conversion by toggling Z2-CT2 output
		 * (finish with output high).
		 */
		comedi_8254_set_mode(dev->pacer, 2, I8254_MODE0);
		comedi_8254_set_mode(dev->pacer, 2, I8254_MODE1);

		/* रुको क्रम conversion to end */
		ret = comedi_समयout(dev, s, insn, pci230_ai_eoc, 0);
		अगर (ret)
			वापस ret;

		/* पढ़ो data */
		data[n] = pci230_ai_पढ़ो(dev);
	पूर्ण

	/* वापस the number of samples पढ़ो/written */
	वापस n;
पूर्ण

अटल पूर्णांक pci230_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	काष्ठा pci230_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	अचिन्हित पूर्णांक val = s->पढ़ोback[chan];
	पूर्णांक i;

	/*
	 * Set range - see analogue output range table; 0 => unipolar 10V,
	 * 1 => bipolar +/-10V range scale
	 */
	devpriv->ao_bipolar = comedi_range_is_bipolar(s, range);
	outw(range, devpriv->daqio + PCI230_DACCON);

	क्रम (i = 0; i < insn->n; i++) अणु
		val = data[i];
		pci230_ao_ग_लिखो_nofअगरo(dev, val, chan);
	पूर्ण
	s->पढ़ोback[chan] = val;

	वापस insn->n;
पूर्ण

अटल पूर्णांक pci230_ao_check_chanlist(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s,
				    काष्ठा comedi_cmd *cmd)
अणु
	अचिन्हित पूर्णांक prev_chan = CR_CHAN(cmd->chanlist[0]);
	अचिन्हित पूर्णांक range0 = CR_RANGE(cmd->chanlist[0]);
	पूर्णांक i;

	क्रम (i = 1; i < cmd->chanlist_len; i++) अणु
		अचिन्हित पूर्णांक chan = CR_CHAN(cmd->chanlist[i]);
		अचिन्हित पूर्णांक range = CR_RANGE(cmd->chanlist[i]);

		अगर (chan < prev_chan) अणु
			dev_dbg(dev->class_dev,
				"%s: channel numbers must increase\n",
				__func__);
			वापस -EINVAL;
		पूर्ण

		अगर (range != range0) अणु
			dev_dbg(dev->class_dev,
				"%s: channels must have the same range\n",
				__func__);
			वापस -EINVAL;
		पूर्ण

		prev_chan = chan;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pci230_ao_cmdtest(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s, काष्ठा comedi_cmd *cmd)
अणु
	स्थिर काष्ठा pci230_board *board = dev->board_ptr;
	काष्ठा pci230_निजी *devpriv = dev->निजी;
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक पंचांगp;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_INT);

	पंचांगp = TRIG_TIMER | TRIG_INT;
	अगर (board->min_hwver > 0 && devpriv->hwver >= 2) अणु
		/*
		 * For PCI230+ hardware version 2 onwards, allow बाह्यal
		 * trigger from EXTTRIG/EXTCONVCLK input (PCI230+ pin 25).
		 *
		 * FIXME: The permitted scan_begin_src values shouldn't depend
		 * on devpriv->hwver (the detected card's actual hardware
		 * version).  They should only depend on board->min_hwver
		 * (the अटल capabilities of the configured card).  To fix
		 * it, a new card model, e.g. "pci230+2" would have to be
		 * defined with min_hwver set to 2.  It करोesn't seem worth it
		 * क्रम this alone.  At the moment, please consider
		 * scan_begin_src==TRIG_EXT support to be a bonus rather than a
		 * guarantee!
		 */
		पंचांगp |= TRIG_EXT;
	पूर्ण
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, पंचांगp);

	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->scan_begin_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);

#घोषणा MAX_SPEED_AO	8000	/* 8000 ns => 125 kHz */
/*
 * Comedi limit due to अचिन्हित पूर्णांक cmd.  Driver limit =
 * 2^16 (16bit * counter) * 1000000ns (1kHz onboard घड़ी) = 65.536s
 */
#घोषणा MIN_SPEED_AO	4294967295u	/* 4294967295ns = 4.29s */

	चयन (cmd->scan_begin_src) अणु
	हाल TRIG_TIMER:
		err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg,
						    MAX_SPEED_AO);
		err |= comedi_check_trigger_arg_max(&cmd->scan_begin_arg,
						    MIN_SPEED_AO);
		अवरोध;
	हाल TRIG_EXT:
		/*
		 * External trigger - क्रम PCI230+ hardware version 2 onwards.
		 */
		/* Trigger number must be 0. */
		अगर (cmd->scan_begin_arg & ~CR_FLAGS_MASK) अणु
			cmd->scan_begin_arg = COMBINE(cmd->scan_begin_arg, 0,
						      ~CR_FLAGS_MASK);
			err |= -EINVAL;
		पूर्ण
		/*
		 * The only flags allowed are CR_EDGE and CR_INVERT.
		 * The CR_EDGE flag is ignored.
		 */
		अगर (cmd->scan_begin_arg & CR_FLAGS_MASK &
		    ~(CR_EDGE | CR_INVERT)) अणु
			cmd->scan_begin_arg =
			    COMBINE(cmd->scan_begin_arg, 0,
				    CR_FLAGS_MASK & ~(CR_EDGE | CR_INVERT));
			err |= -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);
		अवरोध;
	पूर्ण

	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	अन्यथा	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* Step 4: fix up any arguments */

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		पंचांगp = cmd->scan_begin_arg;
		pci230_ns_to_single_समयr(&cmd->scan_begin_arg, cmd->flags);
		अगर (पंचांगp != cmd->scan_begin_arg)
			err++;
	पूर्ण

	अगर (err)
		वापस 4;

	/* Step 5: check channel list अगर it exists */
	अगर (cmd->chanlist && cmd->chanlist_len > 0)
		err |= pci230_ao_check_chanlist(dev, s, cmd);

	अगर (err)
		वापस 5;

	वापस 0;
पूर्ण

अटल व्योम pci230_ao_stop(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pci230_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ irqflags;
	अचिन्हित अक्षर पूर्णांकsrc;
	bool started;
	काष्ठा comedi_cmd *cmd;

	spin_lock_irqsave(&devpriv->ao_stop_spinlock, irqflags);
	started = devpriv->ao_cmd_started;
	devpriv->ao_cmd_started = false;
	spin_unlock_irqrestore(&devpriv->ao_stop_spinlock, irqflags);
	अगर (!started)
		वापस;
	cmd = &s->async->cmd;
	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		/* Stop scan rate generator. */
		pci230_cancel_ct(dev, 1);
	पूर्ण
	/* Determine पूर्णांकerrupt source. */
	अगर (devpriv->hwver < 2) अणु
		/* Not using DAC FIFO.  Using CT1 पूर्णांकerrupt. */
		पूर्णांकsrc = PCI230_INT_ZCLK_CT1;
	पूर्ण अन्यथा अणु
		/* Using DAC FIFO पूर्णांकerrupt. */
		पूर्णांकsrc = PCI230P2_INT_DAC;
	पूर्ण
	/*
	 * Disable पूर्णांकerrupt and रुको क्रम पूर्णांकerrupt routine to finish running
	 * unless we are called from the पूर्णांकerrupt routine.
	 */
	spin_lock_irqsave(&devpriv->isr_spinlock, irqflags);
	devpriv->ier &= ~पूर्णांकsrc;
	जबतक (devpriv->पूर्णांकr_running && devpriv->पूर्णांकr_cpuid != THISCPU) अणु
		spin_unlock_irqrestore(&devpriv->isr_spinlock, irqflags);
		spin_lock_irqsave(&devpriv->isr_spinlock, irqflags);
	पूर्ण
	outb(devpriv->ier, dev->iobase + PCI230_INT_SCE);
	spin_unlock_irqrestore(&devpriv->isr_spinlock, irqflags);
	अगर (devpriv->hwver >= 2) अणु
		/*
		 * Using DAC FIFO.  Reset FIFO, clear underrun error,
		 * disable FIFO.
		 */
		devpriv->daccon &= PCI230_DAC_OR_MASK;
		outw(devpriv->daccon | PCI230P2_DAC_FIFO_RESET |
		     PCI230P2_DAC_FIFO_UNDERRUN_CLEAR,
		     devpriv->daqio + PCI230_DACCON);
	पूर्ण
	/* Release resources. */
	pci230_release_all_resources(dev, OWNER_AOCMD);
पूर्ण

अटल व्योम pci230_handle_ao_nofअगरo(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s)
अणु
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	अचिन्हित लघु data;
	पूर्णांक i;

	अगर (cmd->stop_src == TRIG_COUNT && async->scans_करोne >= cmd->stop_arg)
		वापस;

	क्रम (i = 0; i < cmd->chanlist_len; i++) अणु
		अचिन्हित पूर्णांक chan = CR_CHAN(cmd->chanlist[i]);

		अगर (!comedi_buf_पढ़ो_samples(s, &data, 1)) अणु
			async->events |= COMEDI_CB_OVERFLOW;
			वापस;
		पूर्ण
		pci230_ao_ग_लिखो_nofअगरo(dev, data, chan);
		s->पढ़ोback[chan] = data;
	पूर्ण

	अगर (cmd->stop_src == TRIG_COUNT && async->scans_करोne >= cmd->stop_arg)
		async->events |= COMEDI_CB_EOA;
पूर्ण

/*
 * Loads DAC FIFO (अगर using it) from buffer.
 * Returns false अगर AO finished due to completion or error, true अगर still going.
 */
अटल bool pci230_handle_ao_fअगरo(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pci230_निजी *devpriv = dev->निजी;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	अचिन्हित पूर्णांक num_scans = comedi_nscans_left(s, 0);
	अचिन्हित पूर्णांक room;
	अचिन्हित लघु dacstat;
	अचिन्हित पूर्णांक i, n;
	अचिन्हित पूर्णांक events = 0;

	/* Get DAC FIFO status. */
	dacstat = inw(devpriv->daqio + PCI230_DACCON);

	अगर (cmd->stop_src == TRIG_COUNT && num_scans == 0)
		events |= COMEDI_CB_EOA;

	अगर (events == 0) अणु
		/* Check क्रम FIFO underrun. */
		अगर (dacstat & PCI230P2_DAC_FIFO_UNDERRUN_LATCHED) अणु
			dev_err(dev->class_dev, "AO FIFO underrun\n");
			events |= COMEDI_CB_OVERFLOW | COMEDI_CB_ERROR;
		पूर्ण
		/*
		 * Check क्रम buffer underrun अगर FIFO less than half full
		 * (otherwise there will be loads of "DAC FIFO not half full"
		 * पूर्णांकerrupts).
		 */
		अगर (num_scans == 0 &&
		    (dacstat & PCI230P2_DAC_FIFO_HALF) == 0) अणु
			dev_err(dev->class_dev, "AO buffer underrun\n");
			events |= COMEDI_CB_OVERFLOW | COMEDI_CB_ERROR;
		पूर्ण
	पूर्ण
	अगर (events == 0) अणु
		/* Determine how much room is in the FIFO (in samples). */
		अगर (dacstat & PCI230P2_DAC_FIFO_FULL)
			room = PCI230P2_DAC_FIFOROOM_FULL;
		अन्यथा अगर (dacstat & PCI230P2_DAC_FIFO_HALF)
			room = PCI230P2_DAC_FIFOROOM_HALFTOFULL;
		अन्यथा अगर (dacstat & PCI230P2_DAC_FIFO_EMPTY)
			room = PCI230P2_DAC_FIFOROOM_EMPTY;
		अन्यथा
			room = PCI230P2_DAC_FIFOROOM_ONETOHALF;
		/* Convert room to number of scans that can be added. */
		room /= cmd->chanlist_len;
		/* Determine number of scans to process. */
		अगर (num_scans > room)
			num_scans = room;
		/* Process scans. */
		क्रम (n = 0; n < num_scans; n++) अणु
			क्रम (i = 0; i < cmd->chanlist_len; i++) अणु
				अचिन्हित पूर्णांक chan = CR_CHAN(cmd->chanlist[i]);
				अचिन्हित लघु datum;

				comedi_buf_पढ़ो_samples(s, &datum, 1);
				pci230_ao_ग_लिखो_fअगरo(dev, datum, chan);
				s->पढ़ोback[chan] = datum;
			पूर्ण
		पूर्ण

		अगर (cmd->stop_src == TRIG_COUNT &&
		    async->scans_करोne >= cmd->stop_arg) अणु
			/*
			 * All data क्रम the command has been written
			 * to FIFO.  Set FIFO पूर्णांकerrupt trigger level
			 * to 'empty'.
			 */
			devpriv->daccon &= ~PCI230P2_DAC_INT_FIFO_MASK;
			devpriv->daccon |= PCI230P2_DAC_INT_FIFO_EMPTY;
			outw(devpriv->daccon, devpriv->daqio + PCI230_DACCON);
		पूर्ण
		/* Check अगर FIFO underrun occurred जबतक writing to FIFO. */
		dacstat = inw(devpriv->daqio + PCI230_DACCON);
		अगर (dacstat & PCI230P2_DAC_FIFO_UNDERRUN_LATCHED) अणु
			dev_err(dev->class_dev, "AO FIFO underrun\n");
			events |= COMEDI_CB_OVERFLOW | COMEDI_CB_ERROR;
		पूर्ण
	पूर्ण
	async->events |= events;
	वापस !(async->events & COMEDI_CB_CANCEL_MASK);
पूर्ण

अटल पूर्णांक pci230_ao_पूर्णांकtrig_scan_begin(काष्ठा comedi_device *dev,
					काष्ठा comedi_subdevice *s,
					अचिन्हित पूर्णांक trig_num)
अणु
	काष्ठा pci230_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ irqflags;

	अगर (trig_num)
		वापस -EINVAL;

	spin_lock_irqsave(&devpriv->ao_stop_spinlock, irqflags);
	अगर (!devpriv->ao_cmd_started) अणु
		spin_unlock_irqrestore(&devpriv->ao_stop_spinlock, irqflags);
		वापस 1;
	पूर्ण
	/* Perक्रमm scan. */
	अगर (devpriv->hwver < 2) अणु
		/* Not using DAC FIFO. */
		spin_unlock_irqrestore(&devpriv->ao_stop_spinlock, irqflags);
		pci230_handle_ao_nofअगरo(dev, s);
		comedi_handle_events(dev, s);
	पूर्ण अन्यथा अणु
		/* Using DAC FIFO. */
		/* Read DACSWTRIG रेजिस्टर to trigger conversion. */
		inw(devpriv->daqio + PCI230P2_DACSWTRIG);
		spin_unlock_irqrestore(&devpriv->ao_stop_spinlock, irqflags);
	पूर्ण
	/* Delay.  Should driver be responsible क्रम this? */
	/* XXX TODO: See अगर DAC busy bit can be used. */
	udelay(8);
	वापस 1;
पूर्ण

अटल व्योम pci230_ao_start(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pci230_निजी *devpriv = dev->निजी;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	अचिन्हित दीर्घ irqflags;

	devpriv->ao_cmd_started = true;

	अगर (devpriv->hwver >= 2) अणु
		/* Using DAC FIFO. */
		अचिन्हित लघु scantrig;
		bool run;

		/* Preload FIFO data. */
		run = pci230_handle_ao_fअगरo(dev, s);
		comedi_handle_events(dev, s);
		अगर (!run) अणु
			/* Stopped. */
			वापस;
		पूर्ण
		/* Set scan trigger source. */
		चयन (cmd->scan_begin_src) अणु
		हाल TRIG_TIMER:
			scantrig = PCI230P2_DAC_TRIG_Z2CT1;
			अवरोध;
		हाल TRIG_EXT:
			/* Trigger on EXTTRIG/EXTCONVCLK pin. */
			अगर ((cmd->scan_begin_arg & CR_INVERT) == 0) अणु
				/* +ve edge */
				scantrig = PCI230P2_DAC_TRIG_EXTP;
			पूर्ण अन्यथा अणु
				/* -ve edge */
				scantrig = PCI230P2_DAC_TRIG_EXTN;
			पूर्ण
			अवरोध;
		हाल TRIG_INT:
			scantrig = PCI230P2_DAC_TRIG_SW;
			अवरोध;
		शेष:
			/* Shouldn't get here. */
			scantrig = PCI230P2_DAC_TRIG_NONE;
			अवरोध;
		पूर्ण
		devpriv->daccon =
		    (devpriv->daccon & ~PCI230P2_DAC_TRIG_MASK) | scantrig;
		outw(devpriv->daccon, devpriv->daqio + PCI230_DACCON);
	पूर्ण
	चयन (cmd->scan_begin_src) अणु
	हाल TRIG_TIMER:
		अगर (devpriv->hwver < 2) अणु
			/* Not using DAC FIFO. */
			/* Enable CT1 समयr पूर्णांकerrupt. */
			spin_lock_irqsave(&devpriv->isr_spinlock, irqflags);
			devpriv->ier |= PCI230_INT_ZCLK_CT1;
			outb(devpriv->ier, dev->iobase + PCI230_INT_SCE);
			spin_unlock_irqrestore(&devpriv->isr_spinlock,
					       irqflags);
		पूर्ण
		/* Set CT1 gate high to start counting. */
		outb(pci230_gat_config(1, GAT_VCC),
		     dev->iobase + PCI230_ZGAT_SCE);
		अवरोध;
	हाल TRIG_INT:
		async->पूर्णांकtrig = pci230_ao_पूर्णांकtrig_scan_begin;
		अवरोध;
	पूर्ण
	अगर (devpriv->hwver >= 2) अणु
		/* Using DAC FIFO.  Enable DAC FIFO पूर्णांकerrupt. */
		spin_lock_irqsave(&devpriv->isr_spinlock, irqflags);
		devpriv->ier |= PCI230P2_INT_DAC;
		outb(devpriv->ier, dev->iobase + PCI230_INT_SCE);
		spin_unlock_irqrestore(&devpriv->isr_spinlock, irqflags);
	पूर्ण
पूर्ण

अटल पूर्णांक pci230_ao_पूर्णांकtrig_start(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   अचिन्हित पूर्णांक trig_num)
अणु
	काष्ठा comedi_cmd *cmd = &s->async->cmd;

	अगर (trig_num != cmd->start_src)
		वापस -EINVAL;

	s->async->पूर्णांकtrig = शून्य;
	pci230_ao_start(dev, s);

	वापस 1;
पूर्ण

अटल पूर्णांक pci230_ao_cmd(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pci230_निजी *devpriv = dev->निजी;
	अचिन्हित लघु daccon;
	अचिन्हित पूर्णांक range;

	/* Get the command. */
	काष्ठा comedi_cmd *cmd = &s->async->cmd;

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		/* Claim Z2-CT1. */
		अगर (!pci230_claim_shared(dev, RES_Z2CT1, OWNER_AOCMD))
			वापस -EBUSY;
	पूर्ण

	/*
	 * Set range - see analogue output range table; 0 => unipolar 10V,
	 * 1 => bipolar +/-10V range scale
	 */
	range = CR_RANGE(cmd->chanlist[0]);
	devpriv->ao_bipolar = comedi_range_is_bipolar(s, range);
	daccon = devpriv->ao_bipolar ? PCI230_DAC_OR_BIP : PCI230_DAC_OR_UNI;
	/* Use DAC FIFO क्रम hardware version 2 onwards. */
	अगर (devpriv->hwver >= 2) अणु
		अचिन्हित लघु dacen;
		अचिन्हित पूर्णांक i;

		dacen = 0;
		क्रम (i = 0; i < cmd->chanlist_len; i++)
			dacen |= 1 << CR_CHAN(cmd->chanlist[i]);

		/* Set channel scan list. */
		outw(dacen, devpriv->daqio + PCI230P2_DACEN);
		/*
		 * Enable DAC FIFO.
		 * Set DAC scan source to 'none'.
		 * Set DAC FIFO पूर्णांकerrupt trigger level to 'not half full'.
		 * Reset DAC FIFO and clear underrun.
		 *
		 * N.B. DAC FIFO पूर्णांकerrupts are currently disabled.
		 */
		daccon |= PCI230P2_DAC_FIFO_EN | PCI230P2_DAC_FIFO_RESET |
			  PCI230P2_DAC_FIFO_UNDERRUN_CLEAR |
			  PCI230P2_DAC_TRIG_NONE | PCI230P2_DAC_INT_FIFO_NHALF;
	पूर्ण

	/* Set DACCON. */
	outw(daccon, devpriv->daqio + PCI230_DACCON);
	/* Preserve most of DACCON apart from ग_लिखो-only, transient bits. */
	devpriv->daccon = daccon & ~(PCI230P2_DAC_FIFO_RESET |
				     PCI230P2_DAC_FIFO_UNDERRUN_CLEAR);

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		/*
		 * Set the counter समयr 1 to the specअगरied scan frequency.
		 * cmd->scan_begin_arg is sampling period in ns.
		 * Gate it off क्रम now.
		 */
		outb(pci230_gat_config(1, GAT_GND),
		     dev->iobase + PCI230_ZGAT_SCE);
		pci230_ct_setup_ns_mode(dev, 1, I8254_MODE3,
					cmd->scan_begin_arg,
					cmd->flags);
	पूर्ण

	/* N.B. cmd->start_src == TRIG_INT */
	s->async->पूर्णांकtrig = pci230_ao_पूर्णांकtrig_start;

	वापस 0;
पूर्ण

अटल पूर्णांक pci230_ao_cancel(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s)
अणु
	pci230_ao_stop(dev, s);
	वापस 0;
पूर्ण

अटल पूर्णांक pci230_ai_check_scan_period(काष्ठा comedi_cmd *cmd)
अणु
	अचिन्हित पूर्णांक min_scan_period, chanlist_len;
	पूर्णांक err = 0;

	chanlist_len = cmd->chanlist_len;
	अगर (cmd->chanlist_len == 0)
		chanlist_len = 1;

	min_scan_period = chanlist_len * cmd->convert_arg;
	अगर (min_scan_period < chanlist_len ||
	    min_scan_period < cmd->convert_arg) अणु
		/* Arithmetic overflow. */
		min_scan_period = अच_पूर्णांक_उच्च;
		err++;
	पूर्ण
	अगर (cmd->scan_begin_arg < min_scan_period) अणु
		cmd->scan_begin_arg = min_scan_period;
		err++;
	पूर्ण

	वापस !err;
पूर्ण

अटल पूर्णांक pci230_ai_check_chanlist(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s,
				    काष्ठा comedi_cmd *cmd)
अणु
	काष्ठा pci230_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक max_dअगरf_chan = (s->n_chan / 2) - 1;
	अचिन्हित पूर्णांक prev_chan = 0;
	अचिन्हित पूर्णांक prev_range = 0;
	अचिन्हित पूर्णांक prev_aref = 0;
	bool prev_bipolar = false;
	अचिन्हित पूर्णांक subseq_len = 0;
	पूर्णांक i;

	क्रम (i = 0; i < cmd->chanlist_len; i++) अणु
		अचिन्हित पूर्णांक chanspec = cmd->chanlist[i];
		अचिन्हित पूर्णांक chan = CR_CHAN(chanspec);
		अचिन्हित पूर्णांक range = CR_RANGE(chanspec);
		अचिन्हित पूर्णांक aref = CR_AREF(chanspec);
		bool bipolar = comedi_range_is_bipolar(s, range);

		अगर (aref == AREF_DIFF && chan >= max_dअगरf_chan) अणु
			dev_dbg(dev->class_dev,
				"%s: differential channel number out of range 0 to %u\n",
				__func__, max_dअगरf_chan);
			वापस -EINVAL;
		पूर्ण

		अगर (i > 0) अणु
			/*
			 * Channel numbers must strictly increase or
			 * subsequence must repeat exactly.
			 */
			अगर (chan <= prev_chan && subseq_len == 0)
				subseq_len = i;

			अगर (subseq_len > 0 &&
			    cmd->chanlist[i % subseq_len] != chanspec) अणु
				dev_dbg(dev->class_dev,
					"%s: channel numbers must increase or sequence must repeat exactly\n",
					__func__);
				वापस -EINVAL;
			पूर्ण

			अगर (aref != prev_aref) अणु
				dev_dbg(dev->class_dev,
					"%s: channel sequence analogue references must be all the same (single-ended or differential)\n",
					__func__);
				वापस -EINVAL;
			पूर्ण

			अगर (bipolar != prev_bipolar) अणु
				dev_dbg(dev->class_dev,
					"%s: channel sequence ranges must be all bipolar or all unipolar\n",
					__func__);
				वापस -EINVAL;
			पूर्ण

			अगर (aref != AREF_DIFF && range != prev_range &&
			    ((chan ^ prev_chan) & ~1) == 0) अणु
				dev_dbg(dev->class_dev,
					"%s: single-ended channel pairs must have the same range\n",
					__func__);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		prev_chan = chan;
		prev_range = range;
		prev_aref = aref;
		prev_bipolar = bipolar;
	पूर्ण

	अगर (subseq_len == 0)
		subseq_len = cmd->chanlist_len;

	अगर (cmd->chanlist_len % subseq_len) अणु
		dev_dbg(dev->class_dev,
			"%s: sequence must repeat exactly\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Buggy PCI230+ or PCI260+ requires channel 0 to be (first) in the
	 * sequence अगर the sequence contains more than one channel. Hardware
	 * versions 1 and 2 have the bug. There is no hardware version 3.
	 *
	 * Actually, there are two firmwares that report themselves as
	 * hardware version 1 (the boards have dअगरferent ADC chips with
	 * slightly dअगरferent timing requirements, which was supposed to
	 * be invisible to software). The first one करोesn't seem to have
	 * the bug, but the second one करोes, and we can't tell them apart!
	 */
	अगर (devpriv->hwver > 0 && devpriv->hwver < 4) अणु
		अगर (subseq_len > 1 && CR_CHAN(cmd->chanlist[0])) अणु
			dev_info(dev->class_dev,
				 "amplc_pci230: ai_cmdtest: Buggy PCI230+/260+ h/w version %u requires first channel of multi-channel sequence to be 0 (corrected in h/w version 4)\n",
				 devpriv->hwver);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pci230_ai_cmdtest(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s, काष्ठा comedi_cmd *cmd)
अणु
	स्थिर काष्ठा pci230_board *board = dev->board_ptr;
	काष्ठा pci230_निजी *devpriv = dev->निजी;
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक पंचांगp;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW | TRIG_INT);

	पंचांगp = TRIG_FOLLOW | TRIG_TIMER | TRIG_INT;
	अगर (board->have_dio || board->min_hwver > 0) अणु
		/*
		 * Unक्रमtunately, we cannot trigger a scan off an बाह्यal
		 * source on the PCI260 board, since it uses the PPIC0 (DIO)
		 * input, which isn't present on the PCI260.  For PCI260+
		 * we can use the EXTTRIG/EXTCONVCLK input on pin 17 instead.
		 */
		पंचांगp |= TRIG_EXT;
	पूर्ण
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, पंचांगp);
	err |= comedi_check_trigger_src(&cmd->convert_src,
					TRIG_TIMER | TRIG_INT | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->start_src);
	err |= comedi_check_trigger_is_unique(cmd->scan_begin_src);
	err |= comedi_check_trigger_is_unique(cmd->convert_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	/*
	 * If scan_begin_src is not TRIG_FOLLOW, then a monostable will be
	 * set up to generate a fixed number of समयd conversion pulses.
	 */
	अगर (cmd->scan_begin_src != TRIG_FOLLOW &&
	    cmd->convert_src != TRIG_TIMER)
		err |= -EINVAL;

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);

#घोषणा MAX_SPEED_AI_SE		3200	/* PCI230 SE:   3200 ns => 312.5 kHz */
#घोषणा MAX_SPEED_AI_DIFF	8000	/* PCI230 DIFF: 8000 ns => 125 kHz */
#घोषणा MAX_SPEED_AI_PLUS	4000	/* PCI230+:     4000 ns => 250 kHz */
/*
 * Comedi limit due to अचिन्हित पूर्णांक cmd.  Driver limit =
 * 2^16 (16bit * counter) * 1000000ns (1kHz onboard घड़ी) = 65.536s
 */
#घोषणा MIN_SPEED_AI	4294967295u	/* 4294967295ns = 4.29s */

	अगर (cmd->convert_src == TRIG_TIMER) अणु
		अचिन्हित पूर्णांक max_speed_ai;

		अगर (devpriv->hwver == 0) अणु
			/*
			 * PCI230 or PCI260.  Max speed depends whether
			 * single-ended or pseuकरो-dअगरferential.
			 */
			अगर (cmd->chanlist && cmd->chanlist_len > 0) अणु
				/* Peek analogue reference of first channel. */
				अगर (CR_AREF(cmd->chanlist[0]) == AREF_DIFF)
					max_speed_ai = MAX_SPEED_AI_DIFF;
				अन्यथा
					max_speed_ai = MAX_SPEED_AI_SE;

			पूर्ण अन्यथा अणु
				/* No channel list.  Assume single-ended. */
				max_speed_ai = MAX_SPEED_AI_SE;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* PCI230+ or PCI260+. */
			max_speed_ai = MAX_SPEED_AI_PLUS;
		पूर्ण

		err |= comedi_check_trigger_arg_min(&cmd->convert_arg,
						    max_speed_ai);
		err |= comedi_check_trigger_arg_max(&cmd->convert_arg,
						    MIN_SPEED_AI);
	पूर्ण अन्यथा अगर (cmd->convert_src == TRIG_EXT) अणु
		/*
		 * बाह्यal trigger
		 *
		 * convert_arg == (CR_EDGE | 0)
		 *                => trigger on +ve edge.
		 * convert_arg == (CR_EDGE | CR_INVERT | 0)
		 *                => trigger on -ve edge.
		 */
		अगर (cmd->convert_arg & CR_FLAGS_MASK) अणु
			/* Trigger number must be 0. */
			अगर (cmd->convert_arg & ~CR_FLAGS_MASK) अणु
				cmd->convert_arg = COMBINE(cmd->convert_arg, 0,
							   ~CR_FLAGS_MASK);
				err |= -EINVAL;
			पूर्ण
			/*
			 * The only flags allowed are CR_INVERT and CR_EDGE.
			 * CR_EDGE is required.
			 */
			अगर ((cmd->convert_arg & CR_FLAGS_MASK & ~CR_INVERT) !=
			    CR_EDGE) अणु
				/* Set CR_EDGE, preserve CR_INVERT. */
				cmd->convert_arg =
				    COMBINE(cmd->start_arg, CR_EDGE | 0,
					    CR_FLAGS_MASK & ~CR_INVERT);
				err |= -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * Backwards compatibility with previous versions:
			 * convert_arg == 0 => trigger on -ve edge.
			 * convert_arg == 1 => trigger on +ve edge.
			 */
			err |= comedi_check_trigger_arg_max(&cmd->convert_arg,
							    1);
		पूर्ण
	पूर्ण अन्यथा अणु
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, 0);
	पूर्ण

	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	अन्यथा	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (cmd->scan_begin_src == TRIG_EXT) अणु
		/*
		 * बाह्यal "trigger" to begin each scan:
		 * scan_begin_arg==0 => use PPC0 input -> gate of CT0 -> gate
		 * of CT2 (sample convert trigger is CT2)
		 */
		अगर (cmd->scan_begin_arg & ~CR_FLAGS_MASK) अणु
			cmd->scan_begin_arg = COMBINE(cmd->scan_begin_arg, 0,
						      ~CR_FLAGS_MASK);
			err |= -EINVAL;
		पूर्ण
		/* The only flag allowed is CR_EDGE, which is ignored. */
		अगर (cmd->scan_begin_arg & CR_FLAGS_MASK & ~CR_EDGE) अणु
			cmd->scan_begin_arg = COMBINE(cmd->scan_begin_arg, 0,
						      CR_FLAGS_MASK & ~CR_EDGE);
			err |= -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		/* N.B. cmd->convert_arg is also TRIG_TIMER */
		अगर (!pci230_ai_check_scan_period(cmd))
			err |= -EINVAL;

	पूर्ण अन्यथा अणु
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);
	पूर्ण

	अगर (err)
		वापस 3;

	/* Step 4: fix up any arguments */

	अगर (cmd->convert_src == TRIG_TIMER) अणु
		पंचांगp = cmd->convert_arg;
		pci230_ns_to_single_समयr(&cmd->convert_arg, cmd->flags);
		अगर (पंचांगp != cmd->convert_arg)
			err++;
	पूर्ण

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		/* N.B. cmd->convert_arg is also TRIG_TIMER */
		पंचांगp = cmd->scan_begin_arg;
		pci230_ns_to_single_समयr(&cmd->scan_begin_arg, cmd->flags);
		अगर (!pci230_ai_check_scan_period(cmd)) अणु
			/* Was below minimum required.  Round up. */
			pci230_ns_to_single_समयr(&cmd->scan_begin_arg,
						  CMDF_ROUND_UP);
			pci230_ai_check_scan_period(cmd);
		पूर्ण
		अगर (पंचांगp != cmd->scan_begin_arg)
			err++;
	पूर्ण

	अगर (err)
		वापस 4;

	/* Step 5: check channel list अगर it exists */
	अगर (cmd->chanlist && cmd->chanlist_len > 0)
		err |= pci230_ai_check_chanlist(dev, s, cmd);

	अगर (err)
		वापस 5;

	वापस 0;
पूर्ण

अटल व्योम pci230_ai_update_fअगरo_trigger_level(काष्ठा comedi_device *dev,
						काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pci230_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित पूर्णांक wake;
	अचिन्हित लघु triglev;
	अचिन्हित लघु adccon;

	अगर (cmd->flags & CMDF_WAKE_EOS)
		wake = cmd->scan_end_arg - s->async->cur_chan;
	अन्यथा
		wake = comedi_nsamples_left(s, PCI230_ADC_FIFOLEVEL_HALFFULL);

	अगर (wake >= PCI230_ADC_FIFOLEVEL_HALFFULL) अणु
		triglev = PCI230_ADC_INT_FIFO_HALF;
	पूर्ण अन्यथा अगर (wake > 1 && devpriv->hwver > 0) अणु
		/* PCI230+/260+ programmable FIFO पूर्णांकerrupt level. */
		अगर (devpriv->adcfअगरothresh != wake) अणु
			devpriv->adcfअगरothresh = wake;
			outw(wake, devpriv->daqio + PCI230P_ADCFFTH);
		पूर्ण
		triglev = PCI230P_ADC_INT_FIFO_THRESH;
	पूर्ण अन्यथा अणु
		triglev = PCI230_ADC_INT_FIFO_NEMPTY;
	पूर्ण
	adccon = (devpriv->adccon & ~PCI230_ADC_INT_FIFO_MASK) | triglev;
	अगर (adccon != devpriv->adccon) अणु
		devpriv->adccon = adccon;
		outw(adccon, devpriv->daqio + PCI230_ADCCON);
	पूर्ण
पूर्ण

अटल पूर्णांक pci230_ai_पूर्णांकtrig_convert(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s,
				     अचिन्हित पूर्णांक trig_num)
अणु
	काष्ठा pci230_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ irqflags;
	अचिन्हित पूर्णांक delayus;

	अगर (trig_num)
		वापस -EINVAL;

	spin_lock_irqsave(&devpriv->ai_stop_spinlock, irqflags);
	अगर (!devpriv->ai_cmd_started) अणु
		spin_unlock_irqrestore(&devpriv->ai_stop_spinlock, irqflags);
		वापस 1;
	पूर्ण
	/*
	 * Trigger conversion by toggling Z2-CT2 output.
	 * Finish with output high.
	 */
	comedi_8254_set_mode(dev->pacer, 2, I8254_MODE0);
	comedi_8254_set_mode(dev->pacer, 2, I8254_MODE1);
	/*
	 * Delay.  Should driver be responsible क्रम this?  An
	 * alternative would be to रुको until conversion is complete,
	 * but we can't tell when it's complete because the ADC busy
	 * bit has a dअगरferent meaning when FIFO enabled (and when
	 * FIFO not enabled, it only works क्रम software triggers).
	 */
	अगर ((devpriv->adccon & PCI230_ADC_IM_MASK) == PCI230_ADC_IM_DIF &&
	    devpriv->hwver == 0) अणु
		/* PCI230/260 in dअगरferential mode */
		delayus = 8;
	पूर्ण अन्यथा अणु
		/* single-ended or PCI230+/260+ */
		delayus = 4;
	पूर्ण
	spin_unlock_irqrestore(&devpriv->ai_stop_spinlock, irqflags);
	udelay(delayus);
	वापस 1;
पूर्ण

अटल पूर्णांक pci230_ai_पूर्णांकtrig_scan_begin(काष्ठा comedi_device *dev,
					काष्ठा comedi_subdevice *s,
					अचिन्हित पूर्णांक trig_num)
अणु
	काष्ठा pci230_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ irqflags;
	अचिन्हित अक्षर zgat;

	अगर (trig_num)
		वापस -EINVAL;

	spin_lock_irqsave(&devpriv->ai_stop_spinlock, irqflags);
	अगर (devpriv->ai_cmd_started) अणु
		/* Trigger scan by waggling CT0 gate source. */
		zgat = pci230_gat_config(0, GAT_GND);
		outb(zgat, dev->iobase + PCI230_ZGAT_SCE);
		zgat = pci230_gat_config(0, GAT_VCC);
		outb(zgat, dev->iobase + PCI230_ZGAT_SCE);
	पूर्ण
	spin_unlock_irqrestore(&devpriv->ai_stop_spinlock, irqflags);

	वापस 1;
पूर्ण

अटल व्योम pci230_ai_stop(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pci230_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ irqflags;
	काष्ठा comedi_cmd *cmd;
	bool started;

	spin_lock_irqsave(&devpriv->ai_stop_spinlock, irqflags);
	started = devpriv->ai_cmd_started;
	devpriv->ai_cmd_started = false;
	spin_unlock_irqrestore(&devpriv->ai_stop_spinlock, irqflags);
	अगर (!started)
		वापस;
	cmd = &s->async->cmd;
	अगर (cmd->convert_src == TRIG_TIMER) अणु
		/* Stop conversion rate generator. */
		pci230_cancel_ct(dev, 2);
	पूर्ण
	अगर (cmd->scan_begin_src != TRIG_FOLLOW) अणु
		/* Stop scan period monostable. */
		pci230_cancel_ct(dev, 0);
	पूर्ण
	spin_lock_irqsave(&devpriv->isr_spinlock, irqflags);
	/*
	 * Disable ADC पूर्णांकerrupt and रुको क्रम पूर्णांकerrupt routine to finish
	 * running unless we are called from the पूर्णांकerrupt routine.
	 */
	devpriv->ier &= ~PCI230_INT_ADC;
	जबतक (devpriv->पूर्णांकr_running && devpriv->पूर्णांकr_cpuid != THISCPU) अणु
		spin_unlock_irqrestore(&devpriv->isr_spinlock, irqflags);
		spin_lock_irqsave(&devpriv->isr_spinlock, irqflags);
	पूर्ण
	outb(devpriv->ier, dev->iobase + PCI230_INT_SCE);
	spin_unlock_irqrestore(&devpriv->isr_spinlock, irqflags);
	/*
	 * Reset FIFO, disable FIFO and set start conversion source to none.
	 * Keep se/dअगरf and bip/uni settings.
	 */
	devpriv->adccon =
	    (devpriv->adccon & (PCI230_ADC_IR_MASK | PCI230_ADC_IM_MASK)) |
	    PCI230_ADC_TRIG_NONE;
	outw(devpriv->adccon | PCI230_ADC_FIFO_RESET,
	     devpriv->daqio + PCI230_ADCCON);
	/* Release resources. */
	pci230_release_all_resources(dev, OWNER_AICMD);
पूर्ण

अटल व्योम pci230_ai_start(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pci230_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ irqflags;
	अचिन्हित लघु conv;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;

	devpriv->ai_cmd_started = true;

	/* Enable ADC FIFO trigger level पूर्णांकerrupt. */
	spin_lock_irqsave(&devpriv->isr_spinlock, irqflags);
	devpriv->ier |= PCI230_INT_ADC;
	outb(devpriv->ier, dev->iobase + PCI230_INT_SCE);
	spin_unlock_irqrestore(&devpriv->isr_spinlock, irqflags);

	/*
	 * Update conversion trigger source which is currently set
	 * to CT2 output, which is currently stuck high.
	 */
	चयन (cmd->convert_src) अणु
	शेष:
		conv = PCI230_ADC_TRIG_NONE;
		अवरोध;
	हाल TRIG_TIMER:
		/* Using CT2 output. */
		conv = PCI230_ADC_TRIG_Z2CT2;
		अवरोध;
	हाल TRIG_EXT:
		अगर (cmd->convert_arg & CR_EDGE) अणु
			अगर ((cmd->convert_arg & CR_INVERT) == 0) अणु
				/* Trigger on +ve edge. */
				conv = PCI230_ADC_TRIG_EXTP;
			पूर्ण अन्यथा अणु
				/* Trigger on -ve edge. */
				conv = PCI230_ADC_TRIG_EXTN;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Backwards compatibility. */
			अगर (cmd->convert_arg) अणु
				/* Trigger on +ve edge. */
				conv = PCI230_ADC_TRIG_EXTP;
			पूर्ण अन्यथा अणु
				/* Trigger on -ve edge. */
				conv = PCI230_ADC_TRIG_EXTN;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल TRIG_INT:
		/*
		 * Use CT2 output क्रम software trigger due to problems
		 * in dअगरferential mode on PCI230/260.
		 */
		conv = PCI230_ADC_TRIG_Z2CT2;
		अवरोध;
	पूर्ण
	devpriv->adccon = (devpriv->adccon & ~PCI230_ADC_TRIG_MASK) | conv;
	outw(devpriv->adccon, devpriv->daqio + PCI230_ADCCON);
	अगर (cmd->convert_src == TRIG_INT)
		async->पूर्णांकtrig = pci230_ai_पूर्णांकtrig_convert;

	/*
	 * Update FIFO पूर्णांकerrupt trigger level, which is currently
	 * set to "full".
	 */
	pci230_ai_update_fअगरo_trigger_level(dev, s);
	अगर (cmd->convert_src == TRIG_TIMER) अणु
		/* Update समयr gates. */
		अचिन्हित अक्षर zgat;

		अगर (cmd->scan_begin_src != TRIG_FOLLOW) अणु
			/*
			 * Conversion समयr CT2 needs to be gated by
			 * inverted output of monostable CT2.
			 */
			zgat = pci230_gat_config(2, GAT_NOUTNM2);
		पूर्ण अन्यथा अणु
			/*
			 * Conversion समयr CT2 needs to be gated on
			 * continuously.
			 */
			zgat = pci230_gat_config(2, GAT_VCC);
		पूर्ण
		outb(zgat, dev->iobase + PCI230_ZGAT_SCE);
		अगर (cmd->scan_begin_src != TRIG_FOLLOW) अणु
			/* Set monostable CT0 trigger source. */
			चयन (cmd->scan_begin_src) अणु
			शेष:
				zgat = pci230_gat_config(0, GAT_VCC);
				अवरोध;
			हाल TRIG_EXT:
				/*
				 * For CT0 on PCI230, the बाह्यal trigger
				 * (gate) संकेत comes from PPC0, which is
				 * channel 16 of the DIO subdevice.  The
				 * application needs to configure this as an
				 * input in order to use it as an बाह्यal scan
				 * trigger.
				 */
				zgat = pci230_gat_config(0, GAT_EXT);
				अवरोध;
			हाल TRIG_TIMER:
				/*
				 * Monostable CT0 triggered by rising edge on
				 * inverted output of CT1 (falling edge on CT1).
				 */
				zgat = pci230_gat_config(0, GAT_NOUTNM2);
				अवरोध;
			हाल TRIG_INT:
				/*
				 * Monostable CT0 is triggered by पूर्णांकtrig
				 * function waggling the CT0 gate source.
				 */
				zgat = pci230_gat_config(0, GAT_VCC);
				अवरोध;
			पूर्ण
			outb(zgat, dev->iobase + PCI230_ZGAT_SCE);
			चयन (cmd->scan_begin_src) अणु
			हाल TRIG_TIMER:
				/*
				 * Scan period समयr CT1 needs to be
				 * gated on to start counting.
				 */
				zgat = pci230_gat_config(1, GAT_VCC);
				outb(zgat, dev->iobase + PCI230_ZGAT_SCE);
				अवरोध;
			हाल TRIG_INT:
				async->पूर्णांकtrig = pci230_ai_पूर्णांकtrig_scan_begin;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (cmd->convert_src != TRIG_INT) अणु
		/* No दीर्घer need Z2-CT2. */
		pci230_release_shared(dev, RES_Z2CT2, OWNER_AICMD);
	पूर्ण
पूर्ण

अटल पूर्णांक pci230_ai_पूर्णांकtrig_start(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   अचिन्हित पूर्णांक trig_num)
अणु
	काष्ठा comedi_cmd *cmd = &s->async->cmd;

	अगर (trig_num != cmd->start_arg)
		वापस -EINVAL;

	s->async->पूर्णांकtrig = शून्य;
	pci230_ai_start(dev, s);

	वापस 1;
पूर्ण

अटल व्योम pci230_handle_ai(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pci230_निजी *devpriv = dev->निजी;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	अचिन्हित पूर्णांक status_fअगरo;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक nsamples;
	अचिन्हित पूर्णांक fअगरoamount;
	अचिन्हित लघु val;

	/* Determine number of samples to पढ़ो. */
	nsamples = comedi_nsamples_left(s, PCI230_ADC_FIFOLEVEL_HALFFULL);
	अगर (nsamples == 0)
		वापस;

	fअगरoamount = 0;
	क्रम (i = 0; i < nsamples; i++) अणु
		अगर (fअगरoamount == 0) अणु
			/* Read FIFO state. */
			status_fअगरo = inw(devpriv->daqio + PCI230_ADCCON);
			अगर (status_fअगरo & PCI230_ADC_FIFO_FULL_LATCHED) अणु
				/*
				 * Report error otherwise FIFO overruns will go
				 * unnoticed by the caller.
				 */
				dev_err(dev->class_dev, "AI FIFO overrun\n");
				async->events |= COMEDI_CB_ERROR;
				अवरोध;
			पूर्ण अन्यथा अगर (status_fअगरo & PCI230_ADC_FIFO_EMPTY) अणु
				/* FIFO empty. */
				अवरोध;
			पूर्ण अन्यथा अगर (status_fअगरo & PCI230_ADC_FIFO_HALF) अणु
				/* FIFO half full. */
				fअगरoamount = PCI230_ADC_FIFOLEVEL_HALFFULL;
			पूर्ण अन्यथा अगर (devpriv->hwver > 0) अणु
				/* Read PCI230+/260+ ADC FIFO level. */
				fअगरoamount = inw(devpriv->daqio +
						 PCI230P_ADCFFLEV);
				अगर (fअगरoamount == 0)
					अवरोध;	/* Shouldn't happen. */
			पूर्ण अन्यथा अणु
				/* FIFO not empty. */
				fअगरoamount = 1;
			पूर्ण
		पूर्ण

		val = pci230_ai_पढ़ो(dev);
		अगर (!comedi_buf_ग_लिखो_samples(s, &val, 1))
			अवरोध;

		fअगरoamount--;

		अगर (cmd->stop_src == TRIG_COUNT &&
		    async->scans_करोne >= cmd->stop_arg) अणु
			async->events |= COMEDI_CB_EOA;
			अवरोध;
		पूर्ण
	पूर्ण

	/* update FIFO पूर्णांकerrupt trigger level अगर still running */
	अगर (!(async->events & COMEDI_CB_CANCEL_MASK))
		pci230_ai_update_fअगरo_trigger_level(dev, s);
पूर्ण

अटल पूर्णांक pci230_ai_cmd(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pci230_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक i, chan, range, dअगरf;
	अचिन्हित पूर्णांक res_mask;
	अचिन्हित लघु adccon, adcen;
	अचिन्हित अक्षर zgat;

	/* Get the command. */
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;

	/*
	 * Determine which shared resources are needed.
	 */
	res_mask = 0;
	/*
	 * Need Z2-CT2 to supply a conversion trigger source at a high
	 * logic level, even अगर not करोing समयd conversions.
	 */
	res_mask |= RES_Z2CT2;
	अगर (cmd->scan_begin_src != TRIG_FOLLOW) अणु
		/* Using Z2-CT0 monostable to gate Z2-CT2 conversion समयr */
		res_mask |= RES_Z2CT0;
		अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
			/* Using Z2-CT1 क्रम scan frequency */
			res_mask |= RES_Z2CT1;
		पूर्ण
	पूर्ण
	/* Claim resources. */
	अगर (!pci230_claim_shared(dev, res_mask, OWNER_AICMD))
		वापस -EBUSY;

	/*
	 * Steps:
	 * - Set channel scan list.
	 * - Set channel gains.
	 * - Enable and reset FIFO, specअगरy uni/bip, se/dअगरf, and set
	 *   start conversion source to poपूर्णांक to something at a high logic
	 *   level (we use the output of counter/समयr 2 क्रम this purpose.
	 * - PAUSE to allow things to settle करोwn.
	 * - Reset the FIFO again because it needs resetting twice and there
	 *   may have been a false conversion trigger on some versions of
	 *   PCI230/260 due to the start conversion source being set to a
	 *   high logic level.
	 * - Enable ADC FIFO level पूर्णांकerrupt.
	 * - Set actual conversion trigger source and FIFO पूर्णांकerrupt trigger
	 *   level.
	 * - If convert_src is TRIG_TIMER, set up the समयrs.
	 */

	adccon = PCI230_ADC_FIFO_EN;
	adcen = 0;

	अगर (CR_AREF(cmd->chanlist[0]) == AREF_DIFF) अणु
		/* Dअगरferential - all channels must be dअगरferential. */
		dअगरf = 1;
		adccon |= PCI230_ADC_IM_DIF;
	पूर्ण अन्यथा अणु
		/* Single ended - all channels must be single-ended. */
		dअगरf = 0;
		adccon |= PCI230_ADC_IM_SE;
	पूर्ण

	range = CR_RANGE(cmd->chanlist[0]);
	devpriv->ai_bipolar = comedi_range_is_bipolar(s, range);
	अगर (devpriv->ai_bipolar)
		adccon |= PCI230_ADC_IR_BIP;
	अन्यथा
		adccon |= PCI230_ADC_IR_UNI;

	क्रम (i = 0; i < cmd->chanlist_len; i++) अणु
		अचिन्हित पूर्णांक gainshअगरt;

		chan = CR_CHAN(cmd->chanlist[i]);
		range = CR_RANGE(cmd->chanlist[i]);
		अगर (dअगरf) अणु
			gainshअगरt = 2 * chan;
			अगर (devpriv->hwver == 0) अणु
				/*
				 * Original PCI230/260 expects both inमाला_दो of
				 * the dअगरferential channel to be enabled.
				 */
				adcen |= 3 << gainshअगरt;
			पूर्ण अन्यथा अणु
				/*
				 * PCI230+/260+ expects only one input of the
				 * dअगरferential channel to be enabled.
				 */
				adcen |= 1 << gainshअगरt;
			पूर्ण
		पूर्ण अन्यथा अणु
			gainshअगरt = chan & ~1;
			adcen |= 1 << chan;
		पूर्ण
		devpriv->adcg = (devpriv->adcg & ~(3 << gainshअगरt)) |
				(pci230_ai_gain[range] << gainshअगरt);
	पूर्ण

	/* Set channel scan list. */
	outw(adcen, devpriv->daqio + PCI230_ADCEN);

	/* Set channel gains. */
	outw(devpriv->adcg, devpriv->daqio + PCI230_ADCG);

	/*
	 * Set counter/समयr 2 output high क्रम use as the initial start
	 * conversion source.
	 */
	comedi_8254_set_mode(dev->pacer, 2, I8254_MODE1);

	/*
	 * Temporarily use CT2 output as conversion trigger source and
	 * temporarily set FIFO पूर्णांकerrupt trigger level to 'full'.
	 */
	adccon |= PCI230_ADC_INT_FIFO_FULL | PCI230_ADC_TRIG_Z2CT2;

	/*
	 * Enable and reset FIFO, specअगरy FIFO trigger level full, specअगरy
	 * uni/bip, se/dअगरf, and temporarily set the start conversion source
	 * to CT2 output.  Note that CT2 output is currently high, and this
	 * will produce a false conversion trigger on some versions of the
	 * PCI230/260, but that will be dealt with later.
	 */
	devpriv->adccon = adccon;
	outw(adccon | PCI230_ADC_FIFO_RESET, devpriv->daqio + PCI230_ADCCON);

	/*
	 * Delay -
	 * Failure to include this will result in the first few channels'-worth
	 * of data being corrupt, normally manअगरesting itself by large negative
	 * voltages. It seems the board needs समय to settle between the first
	 * FIFO reset (above) and the second FIFO reset (below). Setting the
	 * channel gains and scan list _beक्रमe_ the first FIFO reset also
	 * helps, though only slightly.
	 */
	usleep_range(25, 100);

	/* Reset FIFO again. */
	outw(adccon | PCI230_ADC_FIFO_RESET, devpriv->daqio + PCI230_ADCCON);

	अगर (cmd->convert_src == TRIG_TIMER) अणु
		/*
		 * Set up CT2 as conversion समयr, but gate it off क्रम now.
		 * Note, counter/समयr output 2 can be monitored on the
		 * connector: PCI230 pin 21, PCI260 pin 18.
		 */
		zgat = pci230_gat_config(2, GAT_GND);
		outb(zgat, dev->iobase + PCI230_ZGAT_SCE);
		/* Set counter/समयr 2 to the specअगरied conversion period. */
		pci230_ct_setup_ns_mode(dev, 2, I8254_MODE3, cmd->convert_arg,
					cmd->flags);
		अगर (cmd->scan_begin_src != TRIG_FOLLOW) अणु
			/*
			 * Set up monostable on CT0 output क्रम scan timing.  A
			 * rising edge on the trigger (gate) input of CT0 will
			 * trigger the monostable, causing its output to go low
			 * क्रम the configured period.  The period depends on
			 * the conversion period and the number of conversions
			 * in the scan.
			 *
			 * Set the trigger high beक्रमe setting up the
			 * monostable to stop it triggering.  The trigger
			 * source will be changed later.
			 */
			zgat = pci230_gat_config(0, GAT_VCC);
			outb(zgat, dev->iobase + PCI230_ZGAT_SCE);
			pci230_ct_setup_ns_mode(dev, 0, I8254_MODE1,
						((u64)cmd->convert_arg *
						 cmd->scan_end_arg),
						CMDF_ROUND_UP);
			अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
				/*
				 * Monostable on CT0 will be triggered by
				 * output of CT1 at configured scan frequency.
				 *
				 * Set up CT1 but gate it off क्रम now.
				 */
				zgat = pci230_gat_config(1, GAT_GND);
				outb(zgat, dev->iobase + PCI230_ZGAT_SCE);
				pci230_ct_setup_ns_mode(dev, 1, I8254_MODE3,
							cmd->scan_begin_arg,
							cmd->flags);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (cmd->start_src == TRIG_INT)
		s->async->पूर्णांकtrig = pci230_ai_पूर्णांकtrig_start;
	अन्यथा	/* TRIG_NOW */
		pci230_ai_start(dev, s);

	वापस 0;
पूर्ण

अटल पूर्णांक pci230_ai_cancel(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s)
अणु
	pci230_ai_stop(dev, s);
	वापस 0;
पूर्ण

/* Interrupt handler */
अटल irqवापस_t pci230_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	अचिन्हित अक्षर status_पूर्णांक, valid_status_पूर्णांक, temp_ier;
	काष्ठा comedi_device *dev = d;
	काष्ठा pci230_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s_ao = dev->ग_लिखो_subdev;
	काष्ठा comedi_subdevice *s_ai = dev->पढ़ो_subdev;
	अचिन्हित दीर्घ irqflags;

	/* Read पूर्णांकerrupt status/enable रेजिस्टर. */
	status_पूर्णांक = inb(dev->iobase + PCI230_INT_STAT);

	अगर (status_पूर्णांक == PCI230_INT_DISABLE)
		वापस IRQ_NONE;

	spin_lock_irqsave(&devpriv->isr_spinlock, irqflags);
	valid_status_पूर्णांक = devpriv->ier & status_पूर्णांक;
	/*
	 * Disable triggered पूर्णांकerrupts.
	 * (Only those पूर्णांकerrupts that need re-enabling, are, later in the
	 * handler).
	 */
	temp_ier = devpriv->ier & ~status_पूर्णांक;
	outb(temp_ier, dev->iobase + PCI230_INT_SCE);
	devpriv->पूर्णांकr_running = true;
	devpriv->पूर्णांकr_cpuid = THISCPU;
	spin_unlock_irqrestore(&devpriv->isr_spinlock, irqflags);

	/*
	 * Check the source of पूर्णांकerrupt and handle it.
	 * The PCI230 can cope with concurrent ADC, DAC, PPI C0 and C3
	 * पूर्णांकerrupts.  However, at present (Comedi-0.7.60) करोes not allow
	 * concurrent execution of commands, inकाष्ठाions or a mixture of the
	 * two.
	 */

	अगर (valid_status_पूर्णांक & PCI230_INT_ZCLK_CT1)
		pci230_handle_ao_nofअगरo(dev, s_ao);

	अगर (valid_status_पूर्णांक & PCI230P2_INT_DAC)
		pci230_handle_ao_fअगरo(dev, s_ao);

	अगर (valid_status_पूर्णांक & PCI230_INT_ADC)
		pci230_handle_ai(dev, s_ai);

	/* Reenable पूर्णांकerrupts. */
	spin_lock_irqsave(&devpriv->isr_spinlock, irqflags);
	अगर (devpriv->ier != temp_ier)
		outb(devpriv->ier, dev->iobase + PCI230_INT_SCE);
	devpriv->पूर्णांकr_running = false;
	spin_unlock_irqrestore(&devpriv->isr_spinlock, irqflags);

	अगर (s_ao)
		comedi_handle_events(dev, s_ao);
	comedi_handle_events(dev, s_ai);

	वापस IRQ_HANDLED;
पूर्ण

/* Check अगर PCI device matches a specअगरic board. */
अटल bool pci230_match_pci_board(स्थिर काष्ठा pci230_board *board,
				   काष्ठा pci_dev *pci_dev)
अणु
	/* assume pci_dev->device != PCI_DEVICE_ID_INVALID */
	अगर (board->id != pci_dev->device)
		वापस false;
	अगर (board->min_hwver == 0)
		वापस true;
	/* Looking क्रम a '+' model.  First check length of रेजिस्टरs. */
	अगर (pci_resource_len(pci_dev, 3) < 32)
		वापस false;	/* Not a '+' model. */
	/*
	 * TODO: temporarily enable PCI device and पढ़ो the hardware version
	 * रेजिस्टर.  For now, assume it's okay.
	 */
	वापस true;
पूर्ण

/* Look क्रम board matching PCI device. */
अटल स्थिर काष्ठा pci230_board *pci230_find_pci_board(काष्ठा pci_dev *pci_dev)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pci230_boards); i++)
		अगर (pci230_match_pci_board(&pci230_boards[i], pci_dev))
			वापस &pci230_boards[i];
	वापस शून्य;
पूर्ण

अटल पूर्णांक pci230_स्वतः_attach(काष्ठा comedi_device *dev,
			      अचिन्हित दीर्घ context_unused)
अणु
	काष्ठा pci_dev *pci_dev = comedi_to_pci_dev(dev);
	स्थिर काष्ठा pci230_board *board;
	काष्ठा pci230_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक rc;

	dev_info(dev->class_dev, "amplc_pci230: attach pci %s\n",
		 pci_name(pci_dev));

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	spin_lock_init(&devpriv->isr_spinlock);
	spin_lock_init(&devpriv->res_spinlock);
	spin_lock_init(&devpriv->ai_stop_spinlock);
	spin_lock_init(&devpriv->ao_stop_spinlock);

	board = pci230_find_pci_board(pci_dev);
	अगर (!board) अणु
		dev_err(dev->class_dev,
			"amplc_pci230: BUG! cannot determine board type!\n");
		वापस -EINVAL;
	पूर्ण
	dev->board_ptr = board;
	dev->board_name = board->name;

	rc = comedi_pci_enable(dev);
	अगर (rc)
		वापस rc;

	/*
	 * Read base addresses of the PCI230's two I/O regions from PCI
	 * configuration रेजिस्टर.
	 */
	dev->iobase = pci_resource_start(pci_dev, 2);
	devpriv->daqio = pci_resource_start(pci_dev, 3);
	dev_dbg(dev->class_dev,
		"%s I/O region 1 0x%04lx I/O region 2 0x%04lx\n",
		dev->board_name, dev->iobase, devpriv->daqio);
	/* Read bits of DACCON रेजिस्टर - only the output range. */
	devpriv->daccon = inw(devpriv->daqio + PCI230_DACCON) &
			  PCI230_DAC_OR_MASK;
	/*
	 * Read hardware version रेजिस्टर and set extended function रेजिस्टर
	 * अगर they exist.
	 */
	अगर (pci_resource_len(pci_dev, 3) >= 32) अणु
		अचिन्हित लघु extfunc = 0;

		devpriv->hwver = inw(devpriv->daqio + PCI230P_HWVER);
		अगर (devpriv->hwver < board->min_hwver) अणु
			dev_err(dev->class_dev,
				"%s - bad hardware version - got %u, need %u\n",
				dev->board_name, devpriv->hwver,
				board->min_hwver);
			वापस -EIO;
		पूर्ण
		अगर (devpriv->hwver > 0) अणु
			अगर (!board->have_dio) अणु
				/*
				 * No DIO ports.  Route counters' बाह्यal gates
				 * to the EXTTRIG संकेत (PCI260+ pin 17).
				 * (Otherwise, they would be routed to DIO
				 * inमाला_दो PC0, PC1 and PC2 which करोn't exist
				 * on PCI260[+].)
				 */
				extfunc |= PCI230P_EXTFUNC_GAT_EXTTRIG;
			पूर्ण
			अगर (board->ao_bits && devpriv->hwver >= 2) अणु
				/* Enable DAC FIFO functionality. */
				extfunc |= PCI230P2_EXTFUNC_DACFIFO;
			पूर्ण
		पूर्ण
		outw(extfunc, devpriv->daqio + PCI230P_EXTFUNC);
		अगर (extfunc & PCI230P2_EXTFUNC_DACFIFO) अणु
			/*
			 * Temporarily enable DAC FIFO, reset it and disable
			 * FIFO wraparound.
			 */
			outw(devpriv->daccon | PCI230P2_DAC_FIFO_EN |
			     PCI230P2_DAC_FIFO_RESET,
			     devpriv->daqio + PCI230_DACCON);
			/* Clear DAC FIFO channel enable रेजिस्टर. */
			outw(0, devpriv->daqio + PCI230P2_DACEN);
			/* Disable DAC FIFO. */
			outw(devpriv->daccon, devpriv->daqio + PCI230_DACCON);
		पूर्ण
	पूर्ण
	/* Disable board's पूर्णांकerrupts. */
	outb(0, dev->iobase + PCI230_INT_SCE);
	/* Set ADC to a reasonable state. */
	devpriv->adcg = 0;
	devpriv->adccon = PCI230_ADC_TRIG_NONE | PCI230_ADC_IM_SE |
			  PCI230_ADC_IR_BIP;
	outw(BIT(0), devpriv->daqio + PCI230_ADCEN);
	outw(devpriv->adcg, devpriv->daqio + PCI230_ADCG);
	outw(devpriv->adccon | PCI230_ADC_FIFO_RESET,
	     devpriv->daqio + PCI230_ADCCON);

	अगर (pci_dev->irq) अणु
		rc = request_irq(pci_dev->irq, pci230_पूर्णांकerrupt, IRQF_SHARED,
				 dev->board_name, dev);
		अगर (rc == 0)
			dev->irq = pci_dev->irq;
	पूर्ण

	dev->pacer = comedi_8254_init(dev->iobase + PCI230_Z2_CT_BASE,
				      0, I8254_IO8, 0);
	अगर (!dev->pacer)
		वापस -ENOMEM;

	rc = comedi_alloc_subdevices(dev, 3);
	अगर (rc)
		वापस rc;

	s = &dev->subdevices[0];
	/* analog input subdevice */
	s->type = COMEDI_SUBD_AI;
	s->subdev_flags = SDF_READABLE | SDF_DIFF | SDF_GROUND;
	s->n_chan = 16;
	s->maxdata = (1 << board->ai_bits) - 1;
	s->range_table = &pci230_ai_range;
	s->insn_पढ़ो = pci230_ai_insn_पढ़ो;
	s->len_chanlist = 256;	/* but there are restrictions. */
	अगर (dev->irq) अणु
		dev->पढ़ो_subdev = s;
		s->subdev_flags |= SDF_CMD_READ;
		s->करो_cmd = pci230_ai_cmd;
		s->करो_cmdtest = pci230_ai_cmdtest;
		s->cancel = pci230_ai_cancel;
	पूर्ण

	s = &dev->subdevices[1];
	/* analog output subdevice */
	अगर (board->ao_bits) अणु
		s->type = COMEDI_SUBD_AO;
		s->subdev_flags = SDF_WRITABLE | SDF_GROUND;
		s->n_chan = 2;
		s->maxdata = (1 << board->ao_bits) - 1;
		s->range_table = &pci230_ao_range;
		s->insn_ग_लिखो = pci230_ao_insn_ग_लिखो;
		s->len_chanlist = 2;
		अगर (dev->irq) अणु
			dev->ग_लिखो_subdev = s;
			s->subdev_flags |= SDF_CMD_WRITE;
			s->करो_cmd = pci230_ao_cmd;
			s->करो_cmdtest = pci230_ao_cmdtest;
			s->cancel = pci230_ao_cancel;
		पूर्ण

		rc = comedi_alloc_subdev_पढ़ोback(s);
		अगर (rc)
			वापस rc;
	पूर्ण अन्यथा अणु
		s->type = COMEDI_SUBD_UNUSED;
	पूर्ण

	s = &dev->subdevices[2];
	/* digital i/o subdevice */
	अगर (board->have_dio) अणु
		rc = subdev_8255_init(dev, s, शून्य, PCI230_PPI_X_BASE);
		अगर (rc)
			वापस rc;
	पूर्ण अन्यथा अणु
		s->type = COMEDI_SUBD_UNUSED;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver amplc_pci230_driver = अणु
	.driver_name	= "amplc_pci230",
	.module		= THIS_MODULE,
	.स्वतः_attach	= pci230_स्वतः_attach,
	.detach		= comedi_pci_detach,
पूर्ण;

अटल पूर्णांक amplc_pci230_pci_probe(काष्ठा pci_dev *dev,
				  स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &amplc_pci230_driver,
				      id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id amplc_pci230_pci_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMPLICON, PCI_DEVICE_ID_PCI230) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMPLICON, PCI_DEVICE_ID_PCI260) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, amplc_pci230_pci_table);

अटल काष्ठा pci_driver amplc_pci230_pci_driver = अणु
	.name		= "amplc_pci230",
	.id_table	= amplc_pci230_pci_table,
	.probe		= amplc_pci230_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(amplc_pci230_driver, amplc_pci230_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for Amplicon PCI230(+) and PCI260(+)");
MODULE_LICENSE("GPL");
