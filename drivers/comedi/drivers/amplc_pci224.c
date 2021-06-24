<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/drivers/amplc_pci224.c
 * Driver क्रम Amplicon PCI224 and PCI234 AO boards.
 *
 * Copyright (C) 2005 MEV Ltd. <https://www.mev.co.uk/>
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1998,2000 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: amplc_pci224
 * Description: Amplicon PCI224, PCI234
 * Author: Ian Abbott <abbotti@mev.co.uk>
 * Devices: [Amplicon] PCI224 (amplc_pci224), PCI234
 * Updated: Thu, 31 Jul 2014 11:08:03 +0000
 * Status: works, but see caveats
 *
 * Supports:
 *
 *   - ao_insn पढ़ो/ग_लिखो
 *   - ao_करो_cmd mode with the following sources:
 *
 *     - start_src         TRIG_INT        TRIG_EXT
 *     - scan_begin_src    TRIG_TIMER      TRIG_EXT
 *     - convert_src       TRIG_NOW
 *     - scan_end_src      TRIG_COUNT
 *     - stop_src          TRIG_COUNT      TRIG_EXT        TRIG_NONE
 *
 *     The channel list must contain at least one channel with no repeated
 *     channels.  The scan end count must equal the number of channels in
 *     the channel list.
 *
 *     There is only one बाह्यal trigger source so only one of start_src,
 *     scan_begin_src or stop_src may use TRIG_EXT.
 *
 * Configuration options:
 *   none
 *
 * Manual configuration of PCI cards is not supported; they are configured
 * स्वतःmatically.
 *
 * Output range selection - PCI224:
 *
 *   Output ranges on PCI224 are partly software-selectable and partly
 *   hardware-selectable according to jumper LK1.  All channels are set
 *   to the same range:
 *
 *   - LK1 position 1-2 (factory शेष) corresponds to the following
 *     comedi ranges:
 *
 *       0: [-10V,+10V]; 1: [-5V,+5V]; 2: [-2.5V,+2.5V], 3: [-1.25V,+1.25V],
 *       4: [0,+10V],    5: [0,+5V],   6: [0,+2.5V],     7: [0,+1.25V]
 *
 *   - LK1 position 2-3 corresponds to the following Comedi ranges, using
 *     an बाह्यal voltage reference:
 *
 *       0: [-Vext,+Vext],
 *       1: [0,+Vext]
 *
 * Output range selection - PCI234:
 *
 *   Output ranges on PCI234 are hardware-selectable according to jumper
 *   LK1 which affects all channels, and jumpers LK2, LK3, LK4 and LK5
 *   which affect channels 0, 1, 2 and 3 inभागidually.  LK1 chooses between
 *   an पूर्णांकernal 5V reference and an बाह्यal voltage reference (Vext).
 *   LK2/3/4/5 choose (per channel) to द्विगुन the reference or not according
 *   to the following table:
 *
 *     LK1 position   LK2/3/4/5 pos  Comedi range
 *     -------------  -------------  --------------
 *     2-3 (factory)  1-2 (factory)  0: [-10V,+10V]
 *     2-3 (factory)  2-3            1: [-5V,+5V]
 *     1-2            1-2 (factory)  2: [-2*Vext,+2*Vext]
 *     1-2            2-3            3: [-Vext,+Vext]
 *
 * Caveats:
 *
 *   1) All channels on the PCI224 share the same range.  Any change to the
 *      range as a result of insn_ग_लिखो or a streaming command will affect
 *      the output voltages of all channels, including those not specअगरied
 *      by the inकाष्ठाion or command.
 *
 *   2) For the analog output command,  the first scan may be triggered
 *      falsely at the start of acquisition.  This occurs when the DAC scan
 *      trigger source is चयनed from 'none' to 'timer' (scan_begin_src =
 *      TRIG_TIMER) or 'external' (scan_begin_src == TRIG_EXT) at the start
 *      of acquisition and the trigger source is at logic level 1 at the
 *      समय of the चयन.  This is very likely क्रम TRIG_TIMER.  For
 *      TRIG_EXT, it depends on the state of the बाह्यal line and whether
 *      the CR_INVERT flag has been set.  The reमुख्यing scans are triggered
 *      correctly.
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>

#समावेश "../comedi_pci.h"

#समावेश "comedi_8254.h"

/*
 * PCI224/234 i/o space 1 (PCIBAR2) रेजिस्टरs.
 */
#घोषणा PCI224_Z2_BASE	0x14	/* 82C54 counter/समयr */
#घोषणा PCI224_ZCLK_SCE	0x1A	/* Group Z Clock Configuration Register */
#घोषणा PCI224_ZGAT_SCE	0x1D	/* Group Z Gate Configuration Register */
#घोषणा PCI224_INT_SCE	0x1E	/* ISR Interrupt source mask रेजिस्टर */
				/* /Interrupt status */

/*
 * PCI224/234 i/o space 2 (PCIBAR3) 16-bit रेजिस्टरs.
 */
#घोषणा PCI224_DACDATA	0x00	/* (w-o) DAC FIFO data. */
#घोषणा PCI224_SOFTTRIG	0x00	/* (r-o) DAC software scan trigger. */
#घोषणा PCI224_DACCON	0x02	/* (r/w) DAC status/configuration. */
#घोषणा PCI224_FIFOSIZ	0x04	/* (w-o) FIFO size क्रम wraparound mode. */
#घोषणा PCI224_DACCEN	0x06	/* (w-o) DAC channel enable रेजिस्टर. */

/*
 * DACCON values.
 */
/* (r/w) Scan trigger. */
#घोषणा PCI224_DACCON_TRIG(x)		(((x) & 0x7) << 0)
#घोषणा PCI224_DACCON_TRIG_MASK		PCI224_DACCON_TRIG(7)
#घोषणा PCI224_DACCON_TRIG_NONE		PCI224_DACCON_TRIG(0)	/* none */
#घोषणा PCI224_DACCON_TRIG_SW		PCI224_DACCON_TRIG(1)	/* soft trig */
#घोषणा PCI224_DACCON_TRIG_EXTP		PCI224_DACCON_TRIG(2)	/* ext + edge */
#घोषणा PCI224_DACCON_TRIG_EXTN		PCI224_DACCON_TRIG(3)	/* ext - edge */
#घोषणा PCI224_DACCON_TRIG_Z2CT0	PCI224_DACCON_TRIG(4)	/* Z2 CT0 out */
#घोषणा PCI224_DACCON_TRIG_Z2CT1	PCI224_DACCON_TRIG(5)	/* Z2 CT1 out */
#घोषणा PCI224_DACCON_TRIG_Z2CT2	PCI224_DACCON_TRIG(6)	/* Z2 CT2 out */
/* (r/w) Polarity (PCI224 only, PCI234 always bipolar!). */
#घोषणा PCI224_DACCON_POLAR(x)		(((x) & 0x1) << 3)
#घोषणा PCI224_DACCON_POLAR_MASK	PCI224_DACCON_POLAR(1)
#घोषणा PCI224_DACCON_POLAR_UNI		PCI224_DACCON_POLAR(0)	/* [0,+V] */
#घोषणा PCI224_DACCON_POLAR_BI		PCI224_DACCON_POLAR(1)	/* [-V,+V] */
/* (r/w) Internal Vref (PCI224 only, when LK1 in position 1-2). */
#घोषणा PCI224_DACCON_VREF(x)		(((x) & 0x3) << 4)
#घोषणा PCI224_DACCON_VREF_MASK		PCI224_DACCON_VREF(3)
#घोषणा PCI224_DACCON_VREF_1_25		PCI224_DACCON_VREF(0)	/* 1.25V */
#घोषणा PCI224_DACCON_VREF_2_5		PCI224_DACCON_VREF(1)	/* 2.5V */
#घोषणा PCI224_DACCON_VREF_5		PCI224_DACCON_VREF(2)	/* 5V */
#घोषणा PCI224_DACCON_VREF_10		PCI224_DACCON_VREF(3)	/* 10V */
/* (r/w) Wraparound mode enable (to play back stored waveक्रमm). */
#घोषणा PCI224_DACCON_FIFOWRAP		BIT(7)
/* (r/w) FIFO enable.  It MUST be set! */
#घोषणा PCI224_DACCON_FIFOENAB		BIT(8)
/* (r/w) FIFO पूर्णांकerrupt trigger level (most values are not very useful). */
#घोषणा PCI224_DACCON_FIFOINTR(x)	(((x) & 0x7) << 9)
#घोषणा PCI224_DACCON_FIFOINTR_MASK	PCI224_DACCON_FIFOINTR(7)
#घोषणा PCI224_DACCON_FIFOINTR_EMPTY	PCI224_DACCON_FIFOINTR(0) /* empty */
#घोषणा PCI224_DACCON_FIFOINTR_NEMPTY	PCI224_DACCON_FIFOINTR(1) /* !empty */
#घोषणा PCI224_DACCON_FIFOINTR_NHALF	PCI224_DACCON_FIFOINTR(2) /* !half */
#घोषणा PCI224_DACCON_FIFOINTR_HALF	PCI224_DACCON_FIFOINTR(3) /* half */
#घोषणा PCI224_DACCON_FIFOINTR_NFULL	PCI224_DACCON_FIFOINTR(4) /* !full */
#घोषणा PCI224_DACCON_FIFOINTR_FULL	PCI224_DACCON_FIFOINTR(5) /* full */
/* (r-o) FIFO fill level. */
#घोषणा PCI224_DACCON_FIFOFL(x)		(((x) & 0x7) << 12)
#घोषणा PCI224_DACCON_FIFOFL_MASK	PCI224_DACCON_FIFOFL(7)
#घोषणा PCI224_DACCON_FIFOFL_EMPTY	PCI224_DACCON_FIFOFL(1)	/* 0 */
#घोषणा PCI224_DACCON_FIFOFL_ONETOHALF	PCI224_DACCON_FIFOFL(0)	/* 1-2048 */
#घोषणा PCI224_DACCON_FIFOFL_HALFTOFULL	PCI224_DACCON_FIFOFL(4)	/* 2049-4095 */
#घोषणा PCI224_DACCON_FIFOFL_FULL	PCI224_DACCON_FIFOFL(6)	/* 4096 */
/* (r-o) DAC busy flag. */
#घोषणा PCI224_DACCON_BUSY		BIT(15)
/* (w-o) FIFO reset. */
#घोषणा PCI224_DACCON_FIFORESET		BIT(12)
/* (w-o) Global reset (not sure what it करोes). */
#घोषणा PCI224_DACCON_GLOBALRESET	BIT(13)

/*
 * DAC FIFO size.
 */
#घोषणा PCI224_FIFO_SIZE	4096

/*
 * DAC FIFO guaranteed minimum room available, depending on reported fill level.
 * The maximum room available depends on the reported fill level and how much
 * has been written!
 */
#घोषणा PCI224_FIFO_ROOM_EMPTY		PCI224_FIFO_SIZE
#घोषणा PCI224_FIFO_ROOM_ONETOHALF	(PCI224_FIFO_SIZE / 2)
#घोषणा PCI224_FIFO_ROOM_HALFTOFULL	1
#घोषणा PCI224_FIFO_ROOM_FULL		0

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

अटल अचिन्हित पूर्णांक pci224_clk_config(अचिन्हित पूर्णांक chan, अचिन्हित पूर्णांक src)
अणु
	वापस ((chan & 3) << 3) | (src & 7);
पूर्ण

/*
 * Counter/समयr gate input configuration sources.
 */
#घोषणा GAT_VCC		0	/* VCC (i.e. enabled) */
#घोषणा GAT_GND		1	/* GND (i.e. disabled) */
#घोषणा GAT_EXT		2	/* reserved (बाह्यal gate input) */
#घोषणा GAT_NOUTNM2	3	/* inverted output of channel-2 modulo total */

अटल अचिन्हित पूर्णांक pci224_gat_config(अचिन्हित पूर्णांक chan, अचिन्हित पूर्णांक src)
अणु
	वापस ((chan & 3) << 3) | (src & 7);
पूर्ण

/*
 * Summary of CLK_OUTNM1 and GAT_NOUTNM2 connections क्रम PCI224 and PCI234:
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
 * Interrupt enable/status bits
 */
#घोषणा PCI224_INTR_EXT		0x01	/* rising edge on बाह्यal input */
#घोषणा PCI224_INTR_DAC		0x04	/* DAC (FIFO) पूर्णांकerrupt */
#घोषणा PCI224_INTR_Z2CT1	0x20	/* rising edge on Z2-CT1 output */

#घोषणा PCI224_INTR_EDGE_BITS	(PCI224_INTR_EXT | PCI224_INTR_Z2CT1)
#घोषणा PCI224_INTR_LEVEL_BITS	PCI224_INTR_DACFIFO

/*
 * Handy macros.
 */

/* Combine old and new bits. */
#घोषणा COMBINE(old, new, mask)	(((old) & ~(mask)) | ((new) & (mask)))

/* Current CPU.  XXX should this be hard_smp_processor_id()? */
#घोषणा THISCPU		smp_processor_id()

/* State bits क्रम use with atomic bit operations. */
#घोषणा AO_CMD_STARTED	0

/*
 * Range tables.
 */

/*
 * The ranges क्रम PCI224.
 *
 * These are partly hardware-selectable by jumper LK1 and partly
 * software-selectable.
 *
 * All channels share the same hardware range.
 */
अटल स्थिर काष्ठा comedi_lrange range_pci224 = अणु
	10, अणु
		/* jumper LK1 in position 1-2 (factory शेष) */
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1.25),
		UNI_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(2.5),
		UNI_RANGE(1.25),
		/* jumper LK1 in position 2-3 */
		RANGE_ext(-1, 1),	/* bipolar [-Vext,+Vext] */
		RANGE_ext(0, 1),	/* unipolar [0,+Vext] */
	पूर्ण
पूर्ण;

अटल स्थिर अचिन्हित लघु hwrange_pci224[10] = अणु
	/* jumper LK1 in position 1-2 (factory शेष) */
	PCI224_DACCON_POLAR_BI | PCI224_DACCON_VREF_10,
	PCI224_DACCON_POLAR_BI | PCI224_DACCON_VREF_5,
	PCI224_DACCON_POLAR_BI | PCI224_DACCON_VREF_2_5,
	PCI224_DACCON_POLAR_BI | PCI224_DACCON_VREF_1_25,
	PCI224_DACCON_POLAR_UNI | PCI224_DACCON_VREF_10,
	PCI224_DACCON_POLAR_UNI | PCI224_DACCON_VREF_5,
	PCI224_DACCON_POLAR_UNI | PCI224_DACCON_VREF_2_5,
	PCI224_DACCON_POLAR_UNI | PCI224_DACCON_VREF_1_25,
	/* jumper LK1 in position 2-3 */
	PCI224_DACCON_POLAR_BI,
	PCI224_DACCON_POLAR_UNI,
पूर्ण;

/* Used to check all channels set to the same range on PCI224. */
अटल स्थिर अचिन्हित अक्षर range_check_pci224[10] = अणु
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
पूर्ण;

/*
 * The ranges क्रम PCI234.
 *
 * These are all hardware-selectable by jumper LK1 affecting all channels,
 * and jumpers LK2, LK3, LK4 and LK5 affecting channels 0, 1, 2 and 3
 * inभागidually.
 */
अटल स्थिर काष्ठा comedi_lrange range_pci234 = अणु
	4, अणु
		/* LK1: 1-2 (fact def), LK2/3/4/5: 2-3 (fac def) */
		BIP_RANGE(10),
		/* LK1: 1-2 (fact def), LK2/3/4/5: 1-2 */
		BIP_RANGE(5),
		/* LK1: 2-3, LK2/3/4/5: 2-3 (fac def) */
		RANGE_ext(-2, 2),	/* bipolar [-2*Vext,+2*Vext] */
		/* LK1: 2-3, LK2/3/4/5: 1-2 */
		RANGE_ext(-1, 1),	/* bipolar [-Vext,+Vext] */
	पूर्ण
पूर्ण;

/* N.B. PCI234 ignores the polarity bit, but software uses it. */
अटल स्थिर अचिन्हित लघु hwrange_pci234[4] = अणु
	PCI224_DACCON_POLAR_BI,
	PCI224_DACCON_POLAR_BI,
	PCI224_DACCON_POLAR_BI,
	PCI224_DACCON_POLAR_BI,
पूर्ण;

/* Used to check all channels use same LK1 setting on PCI234. */
अटल स्थिर अचिन्हित अक्षर range_check_pci234[4] = अणु
	0, 0, 1, 1,
पूर्ण;

/*
 * Board descriptions.
 */

क्रमागत pci224_model अणु pci224_model, pci234_model पूर्ण;

काष्ठा pci224_board अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक ao_chans;
	अचिन्हित पूर्णांक ao_bits;
	स्थिर काष्ठा comedi_lrange *ao_range;
	स्थिर अचिन्हित लघु *ao_hwrange;
	स्थिर अचिन्हित अक्षर *ao_range_check;
पूर्ण;

अटल स्थिर काष्ठा pci224_board pci224_boards[] = अणु
	[pci224_model] = अणु
		.name		= "pci224",
		.ao_chans	= 16,
		.ao_bits	= 12,
		.ao_range	= &range_pci224,
		.ao_hwrange	= &hwrange_pci224[0],
		.ao_range_check	= &range_check_pci224[0],
	पूर्ण,
	[pci234_model] = अणु
		.name		= "pci234",
		.ao_chans	= 4,
		.ao_bits	= 16,
		.ao_range	= &range_pci234,
		.ao_hwrange	= &hwrange_pci234[0],
		.ao_range_check	= &range_check_pci234[0],
	पूर्ण,
पूर्ण;

काष्ठा pci224_निजी अणु
	अचिन्हित दीर्घ iobase1;
	अचिन्हित दीर्घ state;
	spinlock_t ao_spinlock;	/* spinlock क्रम AO command handling */
	अचिन्हित लघु *ao_scan_vals;
	अचिन्हित अक्षर *ao_scan_order;
	पूर्णांक पूर्णांकr_cpuid;
	लघु पूर्णांकr_running;
	अचिन्हित लघु daccon;
	अचिन्हित लघु ao_enab;	/* max 16 channels so 'short' will करो */
	अचिन्हित अक्षर पूर्णांकsce;
पूर्ण;

/*
 * Called from the 'insn_write' function to perक्रमm a single ग_लिखो.
 */
अटल व्योम
pci224_ao_set_data(काष्ठा comedi_device *dev, पूर्णांक chan, पूर्णांक range,
		   अचिन्हित पूर्णांक data)
अणु
	स्थिर काष्ठा pci224_board *board = dev->board_ptr;
	काष्ठा pci224_निजी *devpriv = dev->निजी;
	अचिन्हित लघु mangled;

	/* Enable the channel. */
	outw(1 << chan, dev->iobase + PCI224_DACCEN);
	/* Set range and reset FIFO. */
	devpriv->daccon = COMBINE(devpriv->daccon, board->ao_hwrange[range],
				  PCI224_DACCON_POLAR_MASK |
				  PCI224_DACCON_VREF_MASK);
	outw(devpriv->daccon | PCI224_DACCON_FIFORESET,
	     dev->iobase + PCI224_DACCON);
	/*
	 * Mangle the data.  The hardware expects:
	 * - bipolar: 16-bit 2's complement
	 * - unipolar: 16-bit अचिन्हित
	 */
	mangled = (अचिन्हित लघु)data << (16 - board->ao_bits);
	अगर ((devpriv->daccon & PCI224_DACCON_POLAR_MASK) ==
	    PCI224_DACCON_POLAR_BI) अणु
		mangled ^= 0x8000;
	पूर्ण
	/* Write mangled data to the FIFO. */
	outw(mangled, dev->iobase + PCI224_DACDATA);
	/* Trigger the conversion. */
	inw(dev->iobase + PCI224_SOFTTRIG);
पूर्ण

अटल पूर्णांक pci224_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	अचिन्हित पूर्णांक val = s->पढ़ोback[chan];
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		val = data[i];
		pci224_ao_set_data(dev, chan, range, val);
	पूर्ण
	s->पढ़ोback[chan] = val;

	वापस insn->n;
पूर्ण

/*
 * Kills a command running on the AO subdevice.
 */
अटल व्योम pci224_ao_stop(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pci224_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ flags;

	अगर (!test_and_clear_bit(AO_CMD_STARTED, &devpriv->state))
		वापस;

	spin_lock_irqsave(&devpriv->ao_spinlock, flags);
	/* Kill the पूर्णांकerrupts. */
	devpriv->पूर्णांकsce = 0;
	outb(0, devpriv->iobase1 + PCI224_INT_SCE);
	/*
	 * Interrupt routine may or may not be running.  We may or may not
	 * have been called from the पूर्णांकerrupt routine (directly or
	 * indirectly via a comedi_events() callback routine).  It's highly
	 * unlikely that we've been called from some other पूर्णांकerrupt routine
	 * but who knows what strange things coders get up to!
	 *
	 * If the पूर्णांकerrupt routine is currently running, रुको क्रम it to
	 * finish, unless we appear to have been called via the पूर्णांकerrupt
	 * routine.
	 */
	जबतक (devpriv->पूर्णांकr_running && devpriv->पूर्णांकr_cpuid != THISCPU) अणु
		spin_unlock_irqrestore(&devpriv->ao_spinlock, flags);
		spin_lock_irqsave(&devpriv->ao_spinlock, flags);
	पूर्ण
	spin_unlock_irqrestore(&devpriv->ao_spinlock, flags);
	/* Reconfigure DAC क्रम insn_ग_लिखो usage. */
	outw(0, dev->iobase + PCI224_DACCEN);	/* Disable channels. */
	devpriv->daccon =
	     COMBINE(devpriv->daccon,
		     PCI224_DACCON_TRIG_SW | PCI224_DACCON_FIFOINTR_EMPTY,
		     PCI224_DACCON_TRIG_MASK | PCI224_DACCON_FIFOINTR_MASK);
	outw(devpriv->daccon | PCI224_DACCON_FIFORESET,
	     dev->iobase + PCI224_DACCON);
पूर्ण

/*
 * Handles start of acquisition क्रम the AO subdevice.
 */
अटल व्योम pci224_ao_start(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pci224_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित दीर्घ flags;

	set_bit(AO_CMD_STARTED, &devpriv->state);

	/* Enable पूर्णांकerrupts. */
	spin_lock_irqsave(&devpriv->ao_spinlock, flags);
	अगर (cmd->stop_src == TRIG_EXT)
		devpriv->पूर्णांकsce = PCI224_INTR_EXT | PCI224_INTR_DAC;
	अन्यथा
		devpriv->पूर्णांकsce = PCI224_INTR_DAC;

	outb(devpriv->पूर्णांकsce, devpriv->iobase1 + PCI224_INT_SCE);
	spin_unlock_irqrestore(&devpriv->ao_spinlock, flags);
पूर्ण

/*
 * Handles पूर्णांकerrupts from the DAC FIFO.
 */
अटल व्योम pci224_ao_handle_fअगरo(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pci224_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित पूर्णांक num_scans = comedi_nscans_left(s, 0);
	अचिन्हित पूर्णांक room;
	अचिन्हित लघु dacstat;
	अचिन्हित पूर्णांक i, n;

	/* Determine how much room is in the FIFO (in samples). */
	dacstat = inw(dev->iobase + PCI224_DACCON);
	चयन (dacstat & PCI224_DACCON_FIFOFL_MASK) अणु
	हाल PCI224_DACCON_FIFOFL_EMPTY:
		room = PCI224_FIFO_ROOM_EMPTY;
		अगर (cmd->stop_src == TRIG_COUNT &&
		    s->async->scans_करोne >= cmd->stop_arg) अणु
			/* FIFO empty at end of counted acquisition. */
			s->async->events |= COMEDI_CB_EOA;
			comedi_handle_events(dev, s);
			वापस;
		पूर्ण
		अवरोध;
	हाल PCI224_DACCON_FIFOFL_ONETOHALF:
		room = PCI224_FIFO_ROOM_ONETOHALF;
		अवरोध;
	हाल PCI224_DACCON_FIFOFL_HALFTOFULL:
		room = PCI224_FIFO_ROOM_HALFTOFULL;
		अवरोध;
	शेष:
		room = PCI224_FIFO_ROOM_FULL;
		अवरोध;
	पूर्ण
	अगर (room >= PCI224_FIFO_ROOM_ONETOHALF) अणु
		/* FIFO is less than half-full. */
		अगर (num_scans == 0) अणु
			/* Nothing left to put in the FIFO. */
			dev_err(dev->class_dev, "AO buffer underrun\n");
			s->async->events |= COMEDI_CB_OVERFLOW;
		पूर्ण
	पूर्ण
	/* Determine how many new scans can be put in the FIFO. */
	room /= cmd->chanlist_len;

	/* Determine how many scans to process. */
	अगर (num_scans > room)
		num_scans = room;

	/* Process scans. */
	क्रम (n = 0; n < num_scans; n++) अणु
		comedi_buf_पढ़ो_samples(s, &devpriv->ao_scan_vals[0],
					cmd->chanlist_len);
		क्रम (i = 0; i < cmd->chanlist_len; i++) अणु
			outw(devpriv->ao_scan_vals[devpriv->ao_scan_order[i]],
			     dev->iobase + PCI224_DACDATA);
		पूर्ण
	पूर्ण
	अगर (cmd->stop_src == TRIG_COUNT &&
	    s->async->scans_करोne >= cmd->stop_arg) अणु
		/*
		 * Change FIFO पूर्णांकerrupt trigger level to रुको
		 * until FIFO is empty.
		 */
		devpriv->daccon = COMBINE(devpriv->daccon,
					  PCI224_DACCON_FIFOINTR_EMPTY,
					  PCI224_DACCON_FIFOINTR_MASK);
		outw(devpriv->daccon, dev->iobase + PCI224_DACCON);
	पूर्ण
	अगर ((devpriv->daccon & PCI224_DACCON_TRIG_MASK) ==
	    PCI224_DACCON_TRIG_NONE) अणु
		अचिन्हित लघु trig;

		/*
		 * This is the initial DAC FIFO पूर्णांकerrupt at the
		 * start of the acquisition.  The DAC's scan trigger
		 * has been set to 'none' up until now.
		 *
		 * Now that data has been written to the FIFO, the
		 * DAC's scan trigger source can be set to the
		 * correct value.
		 *
		 * BUG: The first scan will be triggered immediately
		 * अगर the scan trigger source is at logic level 1.
		 */
		अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
			trig = PCI224_DACCON_TRIG_Z2CT0;
		पूर्ण अन्यथा अणु
			/* cmd->scan_begin_src == TRIG_EXT */
			अगर (cmd->scan_begin_arg & CR_INVERT)
				trig = PCI224_DACCON_TRIG_EXTN;
			अन्यथा
				trig = PCI224_DACCON_TRIG_EXTP;
		पूर्ण
		devpriv->daccon =
		    COMBINE(devpriv->daccon, trig, PCI224_DACCON_TRIG_MASK);
		outw(devpriv->daccon, dev->iobase + PCI224_DACCON);
	पूर्ण

	comedi_handle_events(dev, s);
पूर्ण

अटल पूर्णांक pci224_ao_पूर्णांकtrig_start(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   अचिन्हित पूर्णांक trig_num)
अणु
	काष्ठा comedi_cmd *cmd = &s->async->cmd;

	अगर (trig_num != cmd->start_arg)
		वापस -EINVAL;

	s->async->पूर्णांकtrig = शून्य;
	pci224_ao_start(dev, s);

	वापस 1;
पूर्ण

अटल पूर्णांक pci224_ao_check_chanlist(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s,
				    काष्ठा comedi_cmd *cmd)
अणु
	स्थिर काष्ठा pci224_board *board = dev->board_ptr;
	अचिन्हित पूर्णांक range_check_0;
	अचिन्हित पूर्णांक chan_mask = 0;
	पूर्णांक i;

	range_check_0 = board->ao_range_check[CR_RANGE(cmd->chanlist[0])];
	क्रम (i = 0; i < cmd->chanlist_len; i++) अणु
		अचिन्हित पूर्णांक chan = CR_CHAN(cmd->chanlist[i]);

		अगर (chan_mask & (1 << chan)) अणु
			dev_dbg(dev->class_dev,
				"%s: entries in chanlist must contain no duplicate channels\n",
				__func__);
			वापस -EINVAL;
		पूर्ण
		chan_mask |= 1 << chan;

		अगर (board->ao_range_check[CR_RANGE(cmd->chanlist[i])] !=
		    range_check_0) अणु
			dev_dbg(dev->class_dev,
				"%s: entries in chanlist have incompatible ranges\n",
				__func__);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा MAX_SCAN_PERIOD		0xFFFFFFFFU
#घोषणा MIN_SCAN_PERIOD		2500
#घोषणा CONVERT_PERIOD		625

/*
 * 'do_cmdtest' function क्रम AO subdevice.
 */
अटल पूर्णांक
pci224_ao_cmdtest(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
		  काष्ठा comedi_cmd *cmd)
अणु
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक arg;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_INT | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src,
					TRIG_EXT | TRIG_TIMER);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src,
					TRIG_COUNT | TRIG_EXT | TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->start_src);
	err |= comedi_check_trigger_is_unique(cmd->scan_begin_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	/*
	 * There's only one बाह्यal trigger संकेत (which makes these
	 * tests easier).  Only one thing can use it.
	 */
	arg = 0;
	अगर (cmd->start_src & TRIG_EXT)
		arg++;
	अगर (cmd->scan_begin_src & TRIG_EXT)
		arg++;
	अगर (cmd->stop_src & TRIG_EXT)
		arg++;
	अगर (arg > 1)
		err |= -EINVAL;

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	चयन (cmd->start_src) अणु
	हाल TRIG_INT:
		err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);
		अवरोध;
	हाल TRIG_EXT:
		/* Force to बाह्यal trigger 0. */
		अगर (cmd->start_arg & ~CR_FLAGS_MASK) अणु
			cmd->start_arg =
			    COMBINE(cmd->start_arg, 0, ~CR_FLAGS_MASK);
			err |= -EINVAL;
		पूर्ण
		/* The only flag allowed is CR_EDGE, which is ignored. */
		अगर (cmd->start_arg & CR_FLAGS_MASK & ~CR_EDGE) अणु
			cmd->start_arg = COMBINE(cmd->start_arg, 0,
						 CR_FLAGS_MASK & ~CR_EDGE);
			err |= -EINVAL;
		पूर्ण
		अवरोध;
	पूर्ण

	चयन (cmd->scan_begin_src) अणु
	हाल TRIG_TIMER:
		err |= comedi_check_trigger_arg_max(&cmd->scan_begin_arg,
						    MAX_SCAN_PERIOD);

		arg = cmd->chanlist_len * CONVERT_PERIOD;
		अगर (arg < MIN_SCAN_PERIOD)
			arg = MIN_SCAN_PERIOD;
		err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg, arg);
		अवरोध;
	हाल TRIG_EXT:
		/* Force to बाह्यal trigger 0. */
		अगर (cmd->scan_begin_arg & ~CR_FLAGS_MASK) अणु
			cmd->scan_begin_arg =
			    COMBINE(cmd->scan_begin_arg, 0, ~CR_FLAGS_MASK);
			err |= -EINVAL;
		पूर्ण
		/* Only allow flags CR_EDGE and CR_INVERT.  Ignore CR_EDGE. */
		अगर (cmd->scan_begin_arg & CR_FLAGS_MASK &
		    ~(CR_EDGE | CR_INVERT)) अणु
			cmd->scan_begin_arg =
			    COMBINE(cmd->scan_begin_arg, 0,
				    CR_FLAGS_MASK & ~(CR_EDGE | CR_INVERT));
			err |= -EINVAL;
		पूर्ण
		अवरोध;
	पूर्ण

	err |= comedi_check_trigger_arg_is(&cmd->convert_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	चयन (cmd->stop_src) अणु
	हाल TRIG_COUNT:
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
		अवरोध;
	हाल TRIG_EXT:
		/* Force to बाह्यal trigger 0. */
		अगर (cmd->stop_arg & ~CR_FLAGS_MASK) अणु
			cmd->stop_arg =
			    COMBINE(cmd->stop_arg, 0, ~CR_FLAGS_MASK);
			err |= -EINVAL;
		पूर्ण
		/* The only flag allowed is CR_EDGE, which is ignored. */
		अगर (cmd->stop_arg & CR_FLAGS_MASK & ~CR_EDGE) अणु
			cmd->stop_arg =
			    COMBINE(cmd->stop_arg, 0, CR_FLAGS_MASK & ~CR_EDGE);
		पूर्ण
		अवरोध;
	हाल TRIG_NONE:
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);
		अवरोध;
	पूर्ण

	अगर (err)
		वापस 3;

	/* Step 4: fix up any arguments. */

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		arg = cmd->scan_begin_arg;
		/* Use two समयrs. */
		comedi_8254_cascade_ns_to_समयr(dev->pacer, &arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, arg);
	पूर्ण

	अगर (err)
		वापस 4;

	/* Step 5: check channel list अगर it exists */
	अगर (cmd->chanlist && cmd->chanlist_len > 0)
		err |= pci224_ao_check_chanlist(dev, s, cmd);

	अगर (err)
		वापस 5;

	वापस 0;
पूर्ण

अटल व्योम pci224_ao_start_pacer(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s)
अणु
	काष्ठा pci224_निजी *devpriv = dev->निजी;

	/*
	 * The output of समयr Z2-0 will be used as the scan trigger
	 * source.
	 */
	/* Make sure Z2-0 is gated on.  */
	outb(pci224_gat_config(0, GAT_VCC), devpriv->iobase1 + PCI224_ZGAT_SCE);
	/* Cascading with Z2-2. */
	/* Make sure Z2-2 is gated on.  */
	outb(pci224_gat_config(2, GAT_VCC), devpriv->iobase1 + PCI224_ZGAT_SCE);
	/* Z2-2 needs 10 MHz घड़ी. */
	outb(pci224_clk_config(2, CLK_10MHZ),
	     devpriv->iobase1 + PCI224_ZCLK_SCE);
	/* Z2-0 is घड़ीed from Z2-2's output. */
	outb(pci224_clk_config(0, CLK_OUTNM1),
	     devpriv->iobase1 + PCI224_ZCLK_SCE);

	comedi_8254_pacer_enable(dev->pacer, 2, 0, false);
पूर्ण

अटल पूर्णांक pci224_ao_cmd(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	स्थिर काष्ठा pci224_board *board = dev->board_ptr;
	काष्ठा pci224_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	पूर्णांक range;
	अचिन्हित पूर्णांक i, j;
	अचिन्हित पूर्णांक ch;
	अचिन्हित पूर्णांक rank;
	अचिन्हित दीर्घ flags;

	/* Cannot handle null/empty chanlist. */
	अगर (!cmd->chanlist || cmd->chanlist_len == 0)
		वापस -EINVAL;

	/* Determine which channels are enabled and their load order.  */
	devpriv->ao_enab = 0;

	क्रम (i = 0; i < cmd->chanlist_len; i++) अणु
		ch = CR_CHAN(cmd->chanlist[i]);
		devpriv->ao_enab |= 1U << ch;
		rank = 0;
		क्रम (j = 0; j < cmd->chanlist_len; j++) अणु
			अगर (CR_CHAN(cmd->chanlist[j]) < ch)
				rank++;
		पूर्ण
		devpriv->ao_scan_order[rank] = i;
	पूर्ण

	/* Set enabled channels. */
	outw(devpriv->ao_enab, dev->iobase + PCI224_DACCEN);

	/* Determine range and polarity.  All channels the same.  */
	range = CR_RANGE(cmd->chanlist[0]);

	/*
	 * Set DAC range and polarity.
	 * Set DAC scan trigger source to 'none'.
	 * Set DAC FIFO पूर्णांकerrupt trigger level to 'not half full'.
	 * Reset DAC FIFO.
	 *
	 * N.B. DAC FIFO पूर्णांकerrupts are currently disabled.
	 */
	devpriv->daccon =
	    COMBINE(devpriv->daccon,
		    board->ao_hwrange[range] | PCI224_DACCON_TRIG_NONE |
		    PCI224_DACCON_FIFOINTR_NHALF,
		    PCI224_DACCON_POLAR_MASK | PCI224_DACCON_VREF_MASK |
		    PCI224_DACCON_TRIG_MASK | PCI224_DACCON_FIFOINTR_MASK);
	outw(devpriv->daccon | PCI224_DACCON_FIFORESET,
	     dev->iobase + PCI224_DACCON);

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		comedi_8254_update_भागisors(dev->pacer);
		pci224_ao_start_pacer(dev, s);
	पूर्ण

	spin_lock_irqsave(&devpriv->ao_spinlock, flags);
	अगर (cmd->start_src == TRIG_INT) अणु
		s->async->पूर्णांकtrig = pci224_ao_पूर्णांकtrig_start;
	पूर्ण अन्यथा अणु	/* TRIG_EXT */
		/* Enable बाह्यal पूर्णांकerrupt trigger to start acquisition. */
		devpriv->पूर्णांकsce |= PCI224_INTR_EXT;
		outb(devpriv->पूर्णांकsce, devpriv->iobase1 + PCI224_INT_SCE);
	पूर्ण
	spin_unlock_irqrestore(&devpriv->ao_spinlock, flags);

	वापस 0;
पूर्ण

/*
 * 'cancel' function क्रम AO subdevice.
 */
अटल पूर्णांक pci224_ao_cancel(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s)
अणु
	pci224_ao_stop(dev, s);
	वापस 0;
पूर्ण

/*
 * 'munge' data क्रम AO command.
 */
अटल व्योम
pci224_ao_munge(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
		व्योम *data, अचिन्हित पूर्णांक num_bytes, अचिन्हित पूर्णांक chan_index)
अणु
	स्थिर काष्ठा pci224_board *board = dev->board_ptr;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित लघु *array = data;
	अचिन्हित पूर्णांक length = num_bytes / माप(*array);
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक shअगरt;
	अचिन्हित पूर्णांक i;

	/* The hardware expects 16-bit numbers. */
	shअगरt = 16 - board->ao_bits;
	/* Channels will be all bipolar or all unipolar. */
	अगर ((board->ao_hwrange[CR_RANGE(cmd->chanlist[0])] &
	     PCI224_DACCON_POLAR_MASK) == PCI224_DACCON_POLAR_UNI) अणु
		/* Unipolar */
		offset = 0;
	पूर्ण अन्यथा अणु
		/* Bipolar */
		offset = 32768;
	पूर्ण
	/* Munge the data. */
	क्रम (i = 0; i < length; i++)
		array[i] = (array[i] << shअगरt) - offset;
पूर्ण

/*
 * Interrupt handler.
 */
अटल irqवापस_t pci224_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा pci224_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->ग_लिखो_subdev;
	काष्ठा comedi_cmd *cmd;
	अचिन्हित अक्षर पूर्णांकstat, valid_पूर्णांकstat;
	अचिन्हित अक्षर curenab;
	पूर्णांक retval = 0;
	अचिन्हित दीर्घ flags;

	पूर्णांकstat = inb(devpriv->iobase1 + PCI224_INT_SCE) & 0x3F;
	अगर (पूर्णांकstat) अणु
		retval = 1;
		spin_lock_irqsave(&devpriv->ao_spinlock, flags);
		valid_पूर्णांकstat = devpriv->पूर्णांकsce & पूर्णांकstat;
		/* Temporarily disable पूर्णांकerrupt sources. */
		curenab = devpriv->पूर्णांकsce & ~पूर्णांकstat;
		outb(curenab, devpriv->iobase1 + PCI224_INT_SCE);
		devpriv->पूर्णांकr_running = 1;
		devpriv->पूर्णांकr_cpuid = THISCPU;
		spin_unlock_irqrestore(&devpriv->ao_spinlock, flags);
		अगर (valid_पूर्णांकstat) अणु
			cmd = &s->async->cmd;
			अगर (valid_पूर्णांकstat & PCI224_INTR_EXT) अणु
				devpriv->पूर्णांकsce &= ~PCI224_INTR_EXT;
				अगर (cmd->start_src == TRIG_EXT)
					pci224_ao_start(dev, s);
				अन्यथा अगर (cmd->stop_src == TRIG_EXT)
					pci224_ao_stop(dev, s);
			पूर्ण
			अगर (valid_पूर्णांकstat & PCI224_INTR_DAC)
				pci224_ao_handle_fअगरo(dev, s);
		पूर्ण
		/* Reenable पूर्णांकerrupt sources. */
		spin_lock_irqsave(&devpriv->ao_spinlock, flags);
		अगर (curenab != devpriv->पूर्णांकsce) अणु
			outb(devpriv->पूर्णांकsce,
			     devpriv->iobase1 + PCI224_INT_SCE);
		पूर्ण
		devpriv->पूर्णांकr_running = 0;
		spin_unlock_irqrestore(&devpriv->ao_spinlock, flags);
	पूर्ण
	वापस IRQ_RETVAL(retval);
पूर्ण

अटल पूर्णांक
pci224_स्वतः_attach(काष्ठा comedi_device *dev, अचिन्हित दीर्घ context_model)
अणु
	काष्ठा pci_dev *pci_dev = comedi_to_pci_dev(dev);
	स्थिर काष्ठा pci224_board *board = शून्य;
	काष्ठा pci224_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	अचिन्हित पूर्णांक irq;
	पूर्णांक ret;

	अगर (context_model < ARRAY_SIZE(pci224_boards))
		board = &pci224_boards[context_model];
	अगर (!board || !board->name) अणु
		dev_err(dev->class_dev,
			"amplc_pci224: BUG! cannot determine board type!\n");
		वापस -EINVAL;
	पूर्ण
	dev->board_ptr = board;
	dev->board_name = board->name;

	dev_info(dev->class_dev, "amplc_pci224: attach pci %s - %s\n",
		 pci_name(pci_dev), dev->board_name);

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;

	spin_lock_init(&devpriv->ao_spinlock);

	devpriv->iobase1 = pci_resource_start(pci_dev, 2);
	dev->iobase = pci_resource_start(pci_dev, 3);
	irq = pci_dev->irq;

	/* Allocate buffer to hold values क्रम AO channel scan. */
	devpriv->ao_scan_vals = kदो_स्मृति_array(board->ao_chans,
					      माप(devpriv->ao_scan_vals[0]),
					      GFP_KERNEL);
	अगर (!devpriv->ao_scan_vals)
		वापस -ENOMEM;

	/* Allocate buffer to hold AO channel scan order. */
	devpriv->ao_scan_order =
				kदो_स्मृति_array(board->ao_chans,
					      माप(devpriv->ao_scan_order[0]),
					      GFP_KERNEL);
	अगर (!devpriv->ao_scan_order)
		वापस -ENOMEM;

	/* Disable पूर्णांकerrupt sources. */
	devpriv->पूर्णांकsce = 0;
	outb(0, devpriv->iobase1 + PCI224_INT_SCE);

	/* Initialize the DAC hardware. */
	outw(PCI224_DACCON_GLOBALRESET, dev->iobase + PCI224_DACCON);
	outw(0, dev->iobase + PCI224_DACCEN);
	outw(0, dev->iobase + PCI224_FIFOSIZ);
	devpriv->daccon = PCI224_DACCON_TRIG_SW | PCI224_DACCON_POLAR_BI |
			  PCI224_DACCON_FIFOENAB | PCI224_DACCON_FIFOINTR_EMPTY;
	outw(devpriv->daccon | PCI224_DACCON_FIFORESET,
	     dev->iobase + PCI224_DACCON);

	dev->pacer = comedi_8254_init(devpriv->iobase1 + PCI224_Z2_BASE,
				      I8254_OSC_BASE_10MHZ, I8254_IO8, 0);
	अगर (!dev->pacer)
		वापस -ENOMEM;

	ret = comedi_alloc_subdevices(dev, 1);
	अगर (ret)
		वापस ret;

	s = &dev->subdevices[0];
	/* Analog output subdevice. */
	s->type = COMEDI_SUBD_AO;
	s->subdev_flags = SDF_WRITABLE | SDF_GROUND | SDF_CMD_WRITE;
	s->n_chan = board->ao_chans;
	s->maxdata = (1 << board->ao_bits) - 1;
	s->range_table = board->ao_range;
	s->insn_ग_लिखो = pci224_ao_insn_ग_लिखो;
	s->len_chanlist = s->n_chan;
	dev->ग_लिखो_subdev = s;
	s->करो_cmd = pci224_ao_cmd;
	s->करो_cmdtest = pci224_ao_cmdtest;
	s->cancel = pci224_ao_cancel;
	s->munge = pci224_ao_munge;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	अगर (irq) अणु
		ret = request_irq(irq, pci224_पूर्णांकerrupt, IRQF_SHARED,
				  dev->board_name, dev);
		अगर (ret < 0) अणु
			dev_err(dev->class_dev,
				"error! unable to allocate irq %u\n", irq);
			वापस ret;
		पूर्ण
		dev->irq = irq;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pci224_detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा pci224_निजी *devpriv = dev->निजी;

	comedi_pci_detach(dev);
	अगर (devpriv) अणु
		kमुक्त(devpriv->ao_scan_vals);
		kमुक्त(devpriv->ao_scan_order);
	पूर्ण
पूर्ण

अटल काष्ठा comedi_driver amplc_pci224_driver = अणु
	.driver_name	= "amplc_pci224",
	.module		= THIS_MODULE,
	.detach		= pci224_detach,
	.स्वतः_attach	= pci224_स्वतः_attach,
	.board_name	= &pci224_boards[0].name,
	.offset		= माप(काष्ठा pci224_board),
	.num_names	= ARRAY_SIZE(pci224_boards),
पूर्ण;

अटल पूर्णांक amplc_pci224_pci_probe(काष्ठा pci_dev *dev,
				  स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &amplc_pci224_driver,
				      id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id amplc_pci224_pci_table[] = अणु
	अणु PCI_VDEVICE(AMPLICON, 0x0007), pci224_model पूर्ण,
	अणु PCI_VDEVICE(AMPLICON, 0x0008), pci234_model पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, amplc_pci224_pci_table);

अटल काष्ठा pci_driver amplc_pci224_pci_driver = अणु
	.name		= "amplc_pci224",
	.id_table	= amplc_pci224_pci_table,
	.probe		= amplc_pci224_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(amplc_pci224_driver, amplc_pci224_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for Amplicon PCI224 and PCI234 AO boards");
MODULE_LICENSE("GPL");
