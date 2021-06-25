<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/drivers/daqboard2000.c
 * hardware driver क्रम IOtech DAQboard/2000
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1999 Anders Blomdell <anders.blomdell@control.lth.se>
 */
/*
 * Driver: daqboard2000
 * Description: IOTech DAQBoard/2000
 * Author: Anders Blomdell <anders.blomdell@control.lth.se>
 * Status: works
 * Updated: Mon, 14 Apr 2008 15:28:52 +0100
 * Devices: [IOTech] DAQBoard/2000 (daqboard2000)
 *
 * Much of the functionality of this driver was determined from पढ़ोing
 * the source code क्रम the Winकरोws driver.
 *
 * The FPGA on the board requires firmware, which is available from
 * https://www.comedi.org in the comedi_nonमुक्त_firmware tarball.
 *
 * Configuration options: not applicable, uses PCI स्वतः config
 */
/*
 * This card was obviously never पूर्णांकended to leave the Winकरोws world,
 * since it lacked all kind of hardware करोcumentation (except क्रम cable
 * pinouts, plug and pray has something to catch up with yet).
 *
 * With some help from our swedish distributor, we got the Winकरोws sourcecode
 * क्रम the card, and here are the findings so far.
 *
 * 1. A good करोcument that describes the PCI पूर्णांकerface chip is 9080db-106.pdf
 *    available from http://www.plxtech.com/products/io/pci9080
 *
 * 2. The initialization करोne so far is:
 *      a. program the FPGA (winकरोws code sans a lot of error messages)
 *      b.
 *
 * 3. Analog out seems to work OK with DAC's disabled, if DAC's are enabled,
 *    you have to output values to all enabled DAC's until result appears, I
 *    guess that it has something to करो with pacer घड़ीs, but the source
 *    gives me no clues. I'll keep it simple so far.
 *
 * 4. Analog in.
 *    Each channel in the scanlist seems to be controlled by four
 *    control words:
 *
 *	Word0:
 *	  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	  ! | | | ! | | | ! | | | ! | | | !
 *	  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *	Word1:
 *	  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	  ! | | | ! | | | ! | | | ! | | | !
 *	  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	   |             |       | | | | |
 *	   +------+------+       | | | | +-- Digital input (??)
 *		  |		 | | | +---- 10 us settling समय
 *		  |		 | | +------ Suspend acquisition (last to scan)
 *		  |		 | +-------- Simultaneous sample and hold
 *		  |		 +---------- Signed data क्रमmat
 *		  +------------------------- Correction offset low
 *
 *	Word2:
 *	  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	  ! | | | ! | | | ! | | | ! | | | !
 *	  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	   |     | |     | | | | | |     |
 *	   +-----+ +--+--+ +++ +++ +--+--+
 *	      |       |     |   |     +----- Expansion channel
 *	      |       |     |   +----------- Expansion gain
 *	      |       |     +--------------- Channel (low)
 *	      |       +--------------------- Correction offset high
 *	      +----------------------------- Correction gain low
 *	Word3:
 *	  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	  ! | | | ! | | | ! | | | ! | | | !
 *	  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	   |             | | | |   | | | |
 *	   +------+------+ | | +-+-+ | | +-- Low bank enable
 *		  |	   | |   |   | +---- High bank enable
 *		  |	   | |   |   +------ Hi/low select
 *		  |	   | |   +---------- Gain (1,?,2,4,8,16,32,64)
 *		  |	   | +-------------- dअगरferential/single ended
 *		  |	   +---------------- Unipolar
 *		  +------------------------- Correction gain high
 *
 * 999. The card seems to have an incredible amount of capabilities, but
 *      trying to reverse engineer them from the Winकरोws source is beyond my
 *      patience.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "../comedi_pci.h"

#समावेश "8255.h"
#समावेश "plx9080.h"

#घोषणा DB2K_FIRMWARE		"daqboard2000_firmware.bin"

अटल स्थिर काष्ठा comedi_lrange db2k_ai_range = अणु
	13, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1.25),
		BIP_RANGE(0.625),
		BIP_RANGE(0.3125),
		BIP_RANGE(0.156),
		UNI_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(2.5),
		UNI_RANGE(1.25),
		UNI_RANGE(0.625),
		UNI_RANGE(0.3125)
	पूर्ण
पूर्ण;

/*
 * Register Memory Map
 */
#घोषणा DB2K_REG_ACQ_CONTROL			0x00		/* u16 (w) */
#घोषणा DB2K_REG_ACQ_STATUS			0x00		/* u16 (r) */
#घोषणा DB2K_REG_ACQ_SCAN_LIST_FIFO		0x02		/* u16 */
#घोषणा DB2K_REG_ACQ_PACER_CLOCK_DIV_LOW	0x04		/* u32 */
#घोषणा DB2K_REG_ACQ_SCAN_COUNTER		0x08		/* u16 */
#घोषणा DB2K_REG_ACQ_PACER_CLOCK_DIV_HIGH	0x0a		/* u16 */
#घोषणा DB2K_REG_ACQ_TRIGGER_COUNT		0x0c		/* u16 */
#घोषणा DB2K_REG_ACQ_RESULTS_FIFO		0x10		/* u16 */
#घोषणा DB2K_REG_ACQ_RESULTS_SHADOW		0x14		/* u16 */
#घोषणा DB2K_REG_ACQ_ADC_RESULT			0x18		/* u16 */
#घोषणा DB2K_REG_DAC_SCAN_COUNTER		0x1c		/* u16 */
#घोषणा DB2K_REG_DAC_CONTROL			0x20		/* u16 (w) */
#घोषणा DB2K_REG_DAC_STATUS			0x20		/* u16 (r) */
#घोषणा DB2K_REG_DAC_FIFO			0x24		/* s16 */
#घोषणा DB2K_REG_DAC_PACER_CLOCK_DIV		0x2a		/* u16 */
#घोषणा DB2K_REG_REF_DACS			0x2c		/* u16 */
#घोषणा DB2K_REG_DIO_CONTROL			0x30		/* u16 */
#घोषणा DB2K_REG_P3_HSIO_DATA			0x32		/* s16 */
#घोषणा DB2K_REG_P3_CONTROL			0x34		/* u16 */
#घोषणा DB2K_REG_CAL_EEPROM_CONTROL		0x36		/* u16 */
#घोषणा DB2K_REG_DAC_SETTING(x)			(0x38 + (x) * 2) /* s16 */
#घोषणा DB2K_REG_DIO_P2_EXP_IO_8_BIT		0x40		/* s16 */
#घोषणा DB2K_REG_COUNTER_TIMER_CONTROL		0x80		/* u16 */
#घोषणा DB2K_REG_COUNTER_INPUT(x)		(0x88 + (x) * 2) /* s16 */
#घोषणा DB2K_REG_TIMER_DIV(x)			(0xa0 + (x) * 2) /* u16 */
#घोषणा DB2K_REG_DMA_CONTROL			0xb0		/* u16 */
#घोषणा DB2K_REG_TRIG_CONTROL			0xb2		/* u16 */
#घोषणा DB2K_REG_CAL_EEPROM			0xb8		/* u16 */
#घोषणा DB2K_REG_ACQ_DIGITAL_MARK		0xba		/* u16 */
#घोषणा DB2K_REG_TRIG_DACS			0xbc		/* u16 */
#घोषणा DB2K_REG_DIO_P2_EXP_IO_16_BIT(x)	(0xc0 + (x) * 2) /* s16 */

/* CPLD रेजिस्टरs */
#घोषणा DB2K_REG_CPLD_STATUS			0x1000		/* u16 (r) */
#घोषणा DB2K_REG_CPLD_WDATA			0x1000		/* u16 (w) */

/* Scan Sequencer programming */
#घोषणा DB2K_ACQ_CONTROL_SEQ_START_SCAN_LIST		0x0011
#घोषणा DB2K_ACQ_CONTROL_SEQ_STOP_SCAN_LIST		0x0010

/* Prepare क्रम acquisition */
#घोषणा DB2K_ACQ_CONTROL_RESET_SCAN_LIST_FIFO		0x0004
#घोषणा DB2K_ACQ_CONTROL_RESET_RESULTS_FIFO		0x0002
#घोषणा DB2K_ACQ_CONTROL_RESET_CONFIG_PIPE		0x0001

/* Pacer Clock Control */
#घोषणा DB2K_ACQ_CONTROL_ADC_PACER_INTERNAL		0x0030
#घोषणा DB2K_ACQ_CONTROL_ADC_PACER_EXTERNAL		0x0032
#घोषणा DB2K_ACQ_CONTROL_ADC_PACER_ENABLE		0x0031
#घोषणा DB2K_ACQ_CONTROL_ADC_PACER_ENABLE_DAC_PACER	0x0034
#घोषणा DB2K_ACQ_CONTROL_ADC_PACER_DISABLE		0x0030
#घोषणा DB2K_ACQ_CONTROL_ADC_PACER_NORMAL_MODE		0x0060
#घोषणा DB2K_ACQ_CONTROL_ADC_PACER_COMPATIBILITY_MODE	0x0061
#घोषणा DB2K_ACQ_CONTROL_ADC_PACER_INTERNAL_OUT_ENABLE	0x0008
#घोषणा DB2K_ACQ_CONTROL_ADC_PACER_EXTERNAL_RISING	0x0100

/* Acquisition status bits */
#घोषणा DB2K_ACQ_STATUS_RESULTS_FIFO_MORE_1_SAMPLE	0x0001
#घोषणा DB2K_ACQ_STATUS_RESULTS_FIFO_HAS_DATA		0x0002
#घोषणा DB2K_ACQ_STATUS_RESULTS_FIFO_OVERRUN		0x0004
#घोषणा DB2K_ACQ_STATUS_LOGIC_SCANNING			0x0008
#घोषणा DB2K_ACQ_STATUS_CONFIG_PIPE_FULL		0x0010
#घोषणा DB2K_ACQ_STATUS_SCAN_LIST_FIFO_EMPTY		0x0020
#घोषणा DB2K_ACQ_STATUS_ADC_NOT_READY			0x0040
#घोषणा DB2K_ACQ_STATUS_ARBITRATION_FAILURE		0x0080
#घोषणा DB2K_ACQ_STATUS_ADC_PACER_OVERRUN		0x0100
#घोषणा DB2K_ACQ_STATUS_DAC_PACER_OVERRUN		0x0200

/* DAC status */
#घोषणा DB2K_DAC_STATUS_DAC_FULL			0x0001
#घोषणा DB2K_DAC_STATUS_REF_BUSY			0x0002
#घोषणा DB2K_DAC_STATUS_TRIG_BUSY			0x0004
#घोषणा DB2K_DAC_STATUS_CAL_BUSY			0x0008
#घोषणा DB2K_DAC_STATUS_DAC_BUSY(x)			(0x0010 << (x))

/* DAC control */
#घोषणा DB2K_DAC_CONTROL_ENABLE_BIT			0x0001
#घोषणा DB2K_DAC_CONTROL_DATA_IS_SIGNED			0x0002
#घोषणा DB2K_DAC_CONTROL_RESET_FIFO			0x0004
#घोषणा DB2K_DAC_CONTROL_DAC_DISABLE(x)			(0x0020 + ((x) << 4))
#घोषणा DB2K_DAC_CONTROL_DAC_ENABLE(x)			(0x0021 + ((x) << 4))
#घोषणा DB2K_DAC_CONTROL_PATTERN_DISABLE		0x0060
#घोषणा DB2K_DAC_CONTROL_PATTERN_ENABLE			0x0061

/* Trigger Control */
#घोषणा DB2K_TRIG_CONTROL_TYPE_ANALOG			0x0000
#घोषणा DB2K_TRIG_CONTROL_TYPE_TTL			0x0010
#घोषणा DB2K_TRIG_CONTROL_EDGE_HI_LO			0x0004
#घोषणा DB2K_TRIG_CONTROL_EDGE_LO_HI			0x0000
#घोषणा DB2K_TRIG_CONTROL_LEVEL_ABOVE			0x0000
#घोषणा DB2K_TRIG_CONTROL_LEVEL_BELOW			0x0004
#घोषणा DB2K_TRIG_CONTROL_SENSE_LEVEL			0x0002
#घोषणा DB2K_TRIG_CONTROL_SENSE_EDGE			0x0000
#घोषणा DB2K_TRIG_CONTROL_ENABLE			0x0001
#घोषणा DB2K_TRIG_CONTROL_DISABLE			0x0000

/* Reference Dac Selection */
#घोषणा DB2K_REF_DACS_SET				0x0080
#घोषणा DB2K_REF_DACS_SELECT_POS_REF			0x0100
#घोषणा DB2K_REF_DACS_SELECT_NEG_REF			0x0000

/* CPLD status bits */
#घोषणा DB2K_CPLD_STATUS_INIT				0x0002
#घोषणा DB2K_CPLD_STATUS_TXREADY			0x0004
#घोषणा DB2K_CPLD_VERSION_MASK				0xf000
/* "New CPLD" signature. */
#घोषणा DB2K_CPLD_VERSION_NEW				0x5000

क्रमागत db2k_boardid अणु
	BOARD_DAQBOARD2000,
	BOARD_DAQBOARD2001
पूर्ण;

काष्ठा db2k_boardtype अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक has_2_ao:1;/* false: 4 AO chans; true: 2 AO chans */
पूर्ण;

अटल स्थिर काष्ठा db2k_boardtype db2k_boardtypes[] = अणु
	[BOARD_DAQBOARD2000] = अणु
		.name		= "daqboard2000",
		.has_2_ao	= true,
	पूर्ण,
	[BOARD_DAQBOARD2001] = अणु
		.name		= "daqboard2001",
	पूर्ण,
पूर्ण;

काष्ठा db2k_निजी अणु
	व्योम __iomem *plx;
पूर्ण;

अटल व्योम db2k_ग_लिखो_acq_scan_list_entry(काष्ठा comedi_device *dev, u16 entry)
अणु
	ग_लिखोw(entry & 0x00ff, dev->mmio + DB2K_REG_ACQ_SCAN_LIST_FIFO);
	ग_लिखोw((entry >> 8) & 0x00ff,
	       dev->mmio + DB2K_REG_ACQ_SCAN_LIST_FIFO);
पूर्ण

अटल व्योम db2k_setup_sampling(काष्ठा comedi_device *dev, पूर्णांक chan, पूर्णांक gain)
अणु
	u16 word0, word1, word2, word3;

	/* Channel 0-7 dअगरf, channel 8-23 single ended */
	word0 = 0;
	word1 = 0x0004;		/* Last scan */
	word2 = (chan << 6) & 0x00c0;
	चयन (chan / 4) अणु
	हाल 0:
		word3 = 0x0001;
		अवरोध;
	हाल 1:
		word3 = 0x0002;
		अवरोध;
	हाल 2:
		word3 = 0x0005;
		अवरोध;
	हाल 3:
		word3 = 0x0006;
		अवरोध;
	हाल 4:
		word3 = 0x0041;
		अवरोध;
	हाल 5:
		word3 = 0x0042;
		अवरोध;
	शेष:
		word3 = 0;
		अवरोध;
	पूर्ण
	/* These should be पढ़ो from EEPROM */
	word2 |= 0x0800;	/* offset */
	word3 |= 0xc000;	/* gain */
	db2k_ग_लिखो_acq_scan_list_entry(dev, word0);
	db2k_ग_लिखो_acq_scan_list_entry(dev, word1);
	db2k_ग_लिखो_acq_scan_list_entry(dev, word2);
	db2k_ग_लिखो_acq_scan_list_entry(dev, word3);
पूर्ण

अटल पूर्णांक db2k_ai_status(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
			  काष्ठा comedi_insn *insn, अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = पढ़ोw(dev->mmio + DB2K_REG_ACQ_STATUS);
	अगर (status & context)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक db2k_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s,
			     काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक gain, chan;
	पूर्णांक ret;
	पूर्णांक i;

	ग_लिखोw(DB2K_ACQ_CONTROL_RESET_SCAN_LIST_FIFO |
	       DB2K_ACQ_CONTROL_RESET_RESULTS_FIFO |
	       DB2K_ACQ_CONTROL_RESET_CONFIG_PIPE,
	       dev->mmio + DB2K_REG_ACQ_CONTROL);

	/*
	 * If pacer घड़ी is not set to some high value (> 10 us), we
	 * risk multiple samples to be put पूर्णांकo the result FIFO.
	 */
	/* 1 second, should be दीर्घ enough */
	ग_लिखोl(1000000, dev->mmio + DB2K_REG_ACQ_PACER_CLOCK_DIV_LOW);
	ग_लिखोw(0, dev->mmio + DB2K_REG_ACQ_PACER_CLOCK_DIV_HIGH);

	gain = CR_RANGE(insn->chanspec);
	chan = CR_CHAN(insn->chanspec);

	/*
	 * This करोesn't look efficient.  I decided to take the conservative
	 * approach when I did the insn conversion.  Perhaps it would be
	 * better to have broken it completely, then someone would have been
	 * क्रमced to fix it.  --ds
	 */
	क्रम (i = 0; i < insn->n; i++) अणु
		db2k_setup_sampling(dev, chan, gain);
		/* Enable पढ़ोing from the scanlist FIFO */
		ग_लिखोw(DB2K_ACQ_CONTROL_SEQ_START_SCAN_LIST,
		       dev->mmio + DB2K_REG_ACQ_CONTROL);

		ret = comedi_समयout(dev, s, insn, db2k_ai_status,
				     DB2K_ACQ_STATUS_CONFIG_PIPE_FULL);
		अगर (ret)
			वापस ret;

		ग_लिखोw(DB2K_ACQ_CONTROL_ADC_PACER_ENABLE,
		       dev->mmio + DB2K_REG_ACQ_CONTROL);

		ret = comedi_समयout(dev, s, insn, db2k_ai_status,
				     DB2K_ACQ_STATUS_LOGIC_SCANNING);
		अगर (ret)
			वापस ret;

		ret =
		comedi_समयout(dev, s, insn, db2k_ai_status,
			       DB2K_ACQ_STATUS_RESULTS_FIFO_HAS_DATA);
		अगर (ret)
			वापस ret;

		data[i] = पढ़ोw(dev->mmio + DB2K_REG_ACQ_RESULTS_FIFO);
		ग_लिखोw(DB2K_ACQ_CONTROL_ADC_PACER_DISABLE,
		       dev->mmio + DB2K_REG_ACQ_CONTROL);
		ग_लिखोw(DB2K_ACQ_CONTROL_SEQ_STOP_SCAN_LIST,
		       dev->mmio + DB2K_REG_ACQ_CONTROL);
	पूर्ण

	वापस i;
पूर्ण

अटल पूर्णांक db2k_ao_eoc(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
		       काष्ठा comedi_insn *insn, अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक status;

	status = पढ़ोw(dev->mmio + DB2K_REG_DAC_STATUS);
	अगर ((status & DB2K_DAC_STATUS_DAC_BUSY(chan)) == 0)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक db2k_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		अचिन्हित पूर्णांक val = data[i];
		पूर्णांक ret;

		ग_लिखोw(val, dev->mmio + DB2K_REG_DAC_SETTING(chan));

		ret = comedi_समयout(dev, s, insn, db2k_ao_eoc, 0);
		अगर (ret)
			वापस ret;

		s->पढ़ोback[chan] = val;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल व्योम db2k_reset_local_bus(काष्ठा comedi_device *dev)
अणु
	काष्ठा db2k_निजी *devpriv = dev->निजी;
	u32 cntrl;

	cntrl = पढ़ोl(devpriv->plx + PLX_REG_CNTRL);
	cntrl |= PLX_CNTRL_RESET;
	ग_लिखोl(cntrl, devpriv->plx + PLX_REG_CNTRL);
	mdelay(10);
	cntrl &= ~PLX_CNTRL_RESET;
	ग_लिखोl(cntrl, devpriv->plx + PLX_REG_CNTRL);
	mdelay(10);
पूर्ण

अटल व्योम db2k_reload_plx(काष्ठा comedi_device *dev)
अणु
	काष्ठा db2k_निजी *devpriv = dev->निजी;
	u32 cntrl;

	cntrl = पढ़ोl(devpriv->plx + PLX_REG_CNTRL);
	cntrl &= ~PLX_CNTRL_EERELOAD;
	ग_लिखोl(cntrl, devpriv->plx + PLX_REG_CNTRL);
	mdelay(10);
	cntrl |= PLX_CNTRL_EERELOAD;
	ग_लिखोl(cntrl, devpriv->plx + PLX_REG_CNTRL);
	mdelay(10);
	cntrl &= ~PLX_CNTRL_EERELOAD;
	ग_लिखोl(cntrl, devpriv->plx + PLX_REG_CNTRL);
	mdelay(10);
पूर्ण

अटल व्योम db2k_pulse_prog_pin(काष्ठा comedi_device *dev)
अणु
	काष्ठा db2k_निजी *devpriv = dev->निजी;
	u32 cntrl;

	cntrl = पढ़ोl(devpriv->plx + PLX_REG_CNTRL);
	cntrl |= PLX_CNTRL_USERO;
	ग_लिखोl(cntrl, devpriv->plx + PLX_REG_CNTRL);
	mdelay(10);
	cntrl &= ~PLX_CNTRL_USERO;
	ग_लिखोl(cntrl, devpriv->plx + PLX_REG_CNTRL);
	mdelay(10);	/* Not in the original code, but I like symmetry... */
पूर्ण

अटल पूर्णांक db2k_रुको_cpld_init(काष्ठा comedi_device *dev)
अणु
	पूर्णांक result = -ETIMEDOUT;
	पूर्णांक i;
	u16 cpld;

	/* समयout after 50 tries -> 5ms */
	क्रम (i = 0; i < 50; i++) अणु
		cpld = पढ़ोw(dev->mmio + DB2K_REG_CPLD_STATUS);
		अगर (cpld & DB2K_CPLD_STATUS_INIT) अणु
			result = 0;
			अवरोध;
		पूर्ण
		usleep_range(100, 1000);
	पूर्ण
	udelay(5);
	वापस result;
पूर्ण

अटल पूर्णांक db2k_रुको_cpld_txपढ़ोy(काष्ठा comedi_device *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 100; i++) अणु
		अगर (पढ़ोw(dev->mmio + DB2K_REG_CPLD_STATUS) &
		    DB2K_CPLD_STATUS_TXREADY) अणु
			वापस 0;
		पूर्ण
		udelay(1);
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक db2k_ग_लिखो_cpld(काष्ठा comedi_device *dev, u16 data, bool new_cpld)
अणु
	पूर्णांक result = 0;

	अगर (new_cpld) अणु
		result = db2k_रुको_cpld_txपढ़ोy(dev);
		अगर (result)
			वापस result;
	पूर्ण अन्यथा अणु
		usleep_range(10, 20);
	पूर्ण
	ग_लिखोw(data, dev->mmio + DB2K_REG_CPLD_WDATA);
	अगर (!(पढ़ोw(dev->mmio + DB2K_REG_CPLD_STATUS) & DB2K_CPLD_STATUS_INIT))
		result = -EIO;

	वापस result;
पूर्ण

अटल पूर्णांक db2k_रुको_fpga_programmed(काष्ठा comedi_device *dev)
अणु
	काष्ठा db2k_निजी *devpriv = dev->निजी;
	पूर्णांक i;

	/* Time out after 200 tries -> 20ms */
	क्रम (i = 0; i < 200; i++) अणु
		u32 cntrl = पढ़ोl(devpriv->plx + PLX_REG_CNTRL);
		/* General Purpose Input (USERI) set on FPGA "DONE". */
		अगर (cntrl & PLX_CNTRL_USERI)
			वापस 0;

		usleep_range(100, 1000);
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक db2k_load_firmware(काष्ठा comedi_device *dev, स्थिर u8 *cpld_array,
			      माप_प्रकार len, अचिन्हित दीर्घ context)
अणु
	काष्ठा db2k_निजी *devpriv = dev->निजी;
	पूर्णांक result = -EIO;
	u32 cntrl;
	पूर्णांक retry;
	माप_प्रकार i;
	bool new_cpld;

	/* Look क्रम FPGA start sequence in firmware. */
	क्रम (i = 0; i + 1 < len; i++) अणु
		अगर (cpld_array[i] == 0xff && cpld_array[i + 1] == 0x20)
			अवरोध;
	पूर्ण
	अगर (i + 1 >= len) अणु
		dev_err(dev->class_dev, "bad firmware - no start sequence\n");
		वापस -EINVAL;
	पूर्ण
	/* Check length is even. */
	अगर ((len - i) & 1) अणु
		dev_err(dev->class_dev,
			"bad firmware - odd length (%zu = %zu - %zu)\n",
			len - i, len, i);
		वापस -EINVAL;
	पूर्ण
	/* Strip firmware header. */
	cpld_array += i;
	len -= i;

	/* Check to make sure the serial eeprom is present on the board */
	cntrl = पढ़ोl(devpriv->plx + PLX_REG_CNTRL);
	अगर (!(cntrl & PLX_CNTRL_EEPRESENT))
		वापस -EIO;

	क्रम (retry = 0; retry < 3; retry++) अणु
		db2k_reset_local_bus(dev);
		db2k_reload_plx(dev);
		db2k_pulse_prog_pin(dev);
		result = db2k_रुको_cpld_init(dev);
		अगर (result)
			जारी;

		new_cpld = (पढ़ोw(dev->mmio + DB2K_REG_CPLD_STATUS) &
			    DB2K_CPLD_VERSION_MASK) == DB2K_CPLD_VERSION_NEW;
		क्रम (; i < len; i += 2) अणु
			u16 data = (cpld_array[i] << 8) + cpld_array[i + 1];

			result = db2k_ग_लिखो_cpld(dev, data, new_cpld);
			अगर (result)
				अवरोध;
		पूर्ण
		अगर (result == 0)
			result = db2k_रुको_fpga_programmed(dev);
		अगर (result == 0) अणु
			db2k_reset_local_bus(dev);
			db2k_reload_plx(dev);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस result;
पूर्ण

अटल व्योम db2k_adc_stop_dma_transfer(काष्ठा comedi_device *dev)
अणु
पूर्ण

अटल व्योम db2k_adc_disarm(काष्ठा comedi_device *dev)
अणु
	/* Disable hardware triggers */
	udelay(2);
	ग_लिखोw(DB2K_TRIG_CONTROL_TYPE_ANALOG | DB2K_TRIG_CONTROL_DISABLE,
	       dev->mmio + DB2K_REG_TRIG_CONTROL);
	udelay(2);
	ग_लिखोw(DB2K_TRIG_CONTROL_TYPE_TTL | DB2K_TRIG_CONTROL_DISABLE,
	       dev->mmio + DB2K_REG_TRIG_CONTROL);

	/* Stop the scan list FIFO from loading the configuration pipe */
	udelay(2);
	ग_लिखोw(DB2K_ACQ_CONTROL_SEQ_STOP_SCAN_LIST,
	       dev->mmio + DB2K_REG_ACQ_CONTROL);

	/* Stop the pacer घड़ी */
	udelay(2);
	ग_लिखोw(DB2K_ACQ_CONTROL_ADC_PACER_DISABLE,
	       dev->mmio + DB2K_REG_ACQ_CONTROL);

	/* Stop the input dma (पात channel 1) */
	db2k_adc_stop_dma_transfer(dev);
पूर्ण

अटल व्योम db2k_activate_reference_dacs(काष्ठा comedi_device *dev)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक समयout;

	/*  Set the + reference dac value in the FPGA */
	ग_लिखोw(DB2K_REF_DACS_SET | DB2K_REF_DACS_SELECT_POS_REF,
	       dev->mmio + DB2K_REG_REF_DACS);
	क्रम (समयout = 0; समयout < 20; समयout++) अणु
		val = पढ़ोw(dev->mmio + DB2K_REG_DAC_STATUS);
		अगर ((val & DB2K_DAC_STATUS_REF_BUSY) == 0)
			अवरोध;
		udelay(2);
	पूर्ण

	/*  Set the - reference dac value in the FPGA */
	ग_लिखोw(DB2K_REF_DACS_SET | DB2K_REF_DACS_SELECT_NEG_REF,
	       dev->mmio + DB2K_REG_REF_DACS);
	क्रम (समयout = 0; समयout < 20; समयout++) अणु
		val = पढ़ोw(dev->mmio + DB2K_REG_DAC_STATUS);
		अगर ((val & DB2K_DAC_STATUS_REF_BUSY) == 0)
			अवरोध;
		udelay(2);
	पूर्ण
पूर्ण

अटल व्योम db2k_initialize_ctrs(काष्ठा comedi_device *dev)
अणु
पूर्ण

अटल व्योम db2k_initialize_पंचांगrs(काष्ठा comedi_device *dev)
अणु
पूर्ण

अटल व्योम db2k_dac_disarm(काष्ठा comedi_device *dev)
अणु
पूर्ण

अटल व्योम db2k_initialize_adc(काष्ठा comedi_device *dev)
अणु
	db2k_adc_disarm(dev);
	db2k_activate_reference_dacs(dev);
	db2k_initialize_ctrs(dev);
	db2k_initialize_पंचांगrs(dev);
पूर्ण

अटल पूर्णांक db2k_8255_cb(काष्ठा comedi_device *dev, पूर्णांक dir, पूर्णांक port, पूर्णांक data,
			अचिन्हित दीर्घ iobase)
अणु
	अगर (dir) अणु
		ग_लिखोw(data, dev->mmio + iobase + port * 2);
		वापस 0;
	पूर्ण
	वापस पढ़ोw(dev->mmio + iobase + port * 2);
पूर्ण

अटल पूर्णांक db2k_स्वतः_attach(काष्ठा comedi_device *dev, अचिन्हित दीर्घ context)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	स्थिर काष्ठा db2k_boardtype *board;
	काष्ठा db2k_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक result;

	अगर (context >= ARRAY_SIZE(db2k_boardtypes))
		वापस -ENODEV;
	board = &db2k_boardtypes[context];
	अगर (!board->name)
		वापस -ENODEV;
	dev->board_ptr = board;
	dev->board_name = board->name;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	result = comedi_pci_enable(dev);
	अगर (result)
		वापस result;

	devpriv->plx = pci_ioremap_bar(pcidev, 0);
	dev->mmio = pci_ioremap_bar(pcidev, 2);
	अगर (!devpriv->plx || !dev->mmio)
		वापस -ENOMEM;

	result = comedi_alloc_subdevices(dev, 3);
	अगर (result)
		वापस result;

	result = comedi_load_firmware(dev, &comedi_to_pci_dev(dev)->dev,
				      DB2K_FIRMWARE, db2k_load_firmware, 0);
	अगर (result < 0)
		वापस result;

	db2k_initialize_adc(dev);
	db2k_dac_disarm(dev);

	s = &dev->subdevices[0];
	/* ai subdevice */
	s->type = COMEDI_SUBD_AI;
	s->subdev_flags = SDF_READABLE | SDF_GROUND;
	s->n_chan = 24;
	s->maxdata = 0xffff;
	s->insn_पढ़ो = db2k_ai_insn_पढ़ो;
	s->range_table = &db2k_ai_range;

	s = &dev->subdevices[1];
	/* ao subdevice */
	s->type = COMEDI_SUBD_AO;
	s->subdev_flags = SDF_WRITABLE;
	s->n_chan = board->has_2_ao ? 2 : 4;
	s->maxdata = 0xffff;
	s->insn_ग_लिखो = db2k_ao_insn_ग_लिखो;
	s->range_table = &range_bipolar10;

	result = comedi_alloc_subdev_पढ़ोback(s);
	अगर (result)
		वापस result;

	s = &dev->subdevices[2];
	वापस subdev_8255_init(dev, s, db2k_8255_cb,
				DB2K_REG_DIO_P2_EXP_IO_8_BIT);
पूर्ण

अटल व्योम db2k_detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा db2k_निजी *devpriv = dev->निजी;

	अगर (devpriv && devpriv->plx)
		iounmap(devpriv->plx);
	comedi_pci_detach(dev);
पूर्ण

अटल काष्ठा comedi_driver db2k_driver = अणु
	.driver_name	= "daqboard2000",
	.module		= THIS_MODULE,
	.स्वतः_attach	= db2k_स्वतः_attach,
	.detach		= db2k_detach,
पूर्ण;

अटल पूर्णांक db2k_pci_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &db2k_driver, id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id db2k_pci_table[] = अणु
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_IOTECH, 0x0409, PCI_VENDOR_ID_IOTECH,
			 0x0002), .driver_data = BOARD_DAQBOARD2000, पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_IOTECH, 0x0409, PCI_VENDOR_ID_IOTECH,
			 0x0004), .driver_data = BOARD_DAQBOARD2001, पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, db2k_pci_table);

अटल काष्ठा pci_driver db2k_pci_driver = अणु
	.name		= "daqboard2000",
	.id_table	= db2k_pci_table,
	.probe		= db2k_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(db2k_driver, db2k_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(DB2K_FIRMWARE);
