<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * me4000.c
 * Source code क्रम the Meilhaus ME-4000 board family.
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: me4000
 * Description: Meilhaus ME-4000 series boards
 * Devices: [Meilhaus] ME-4650 (me4000), ME-4670i, ME-4680, ME-4680i,
 *	    ME-4680is
 * Author: gg (Guenter Gebhardt <g.gebhardt@meilhaus.com>)
 * Updated: Mon, 18 Mar 2002 15:34:01 -0800
 * Status: untested
 *
 * Supports:
 *	- Analog Input
 *	- Analog Output
 *	- Digital I/O
 *	- Counter
 *
 * Configuration Options: not applicable, uses PCI स्वतः config
 *
 * The firmware required by these boards is available in the
 * comedi_nonमुक्त_firmware tarball available from
 * https://www.comedi.org.
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "../comedi_pci.h"

#समावेश "comedi_8254.h"
#समावेश "plx9052.h"

#घोषणा ME4000_FIRMWARE		"me4000_firmware.bin"

/*
 * ME4000 Register map and bit defines
 */
#घोषणा ME4000_AO_CHAN(x)			((x) * 0x18)

#घोषणा ME4000_AO_CTRL_REG(x)			(0x00 + ME4000_AO_CHAN(x))
#घोषणा ME4000_AO_CTRL_MODE_0			BIT(0)
#घोषणा ME4000_AO_CTRL_MODE_1			BIT(1)
#घोषणा ME4000_AO_CTRL_STOP			BIT(2)
#घोषणा ME4000_AO_CTRL_ENABLE_FIFO		BIT(3)
#घोषणा ME4000_AO_CTRL_ENABLE_EX_TRIG		BIT(4)
#घोषणा ME4000_AO_CTRL_EX_TRIG_EDGE		BIT(5)
#घोषणा ME4000_AO_CTRL_IMMEDIATE_STOP		BIT(7)
#घोषणा ME4000_AO_CTRL_ENABLE_DO		BIT(8)
#घोषणा ME4000_AO_CTRL_ENABLE_IRQ		BIT(9)
#घोषणा ME4000_AO_CTRL_RESET_IRQ		BIT(10)
#घोषणा ME4000_AO_STATUS_REG(x)			(0x04 + ME4000_AO_CHAN(x))
#घोषणा ME4000_AO_STATUS_FSM			BIT(0)
#घोषणा ME4000_AO_STATUS_FF			BIT(1)
#घोषणा ME4000_AO_STATUS_HF			BIT(2)
#घोषणा ME4000_AO_STATUS_EF			BIT(3)
#घोषणा ME4000_AO_FIFO_REG(x)			(0x08 + ME4000_AO_CHAN(x))
#घोषणा ME4000_AO_SINGLE_REG(x)			(0x0c + ME4000_AO_CHAN(x))
#घोषणा ME4000_AO_TIMER_REG(x)			(0x10 + ME4000_AO_CHAN(x))
#घोषणा ME4000_AI_CTRL_REG			0x74
#घोषणा ME4000_AI_STATUS_REG			0x74
#घोषणा ME4000_AI_CTRL_MODE_0			BIT(0)
#घोषणा ME4000_AI_CTRL_MODE_1			BIT(1)
#घोषणा ME4000_AI_CTRL_MODE_2			BIT(2)
#घोषणा ME4000_AI_CTRL_SAMPLE_HOLD		BIT(3)
#घोषणा ME4000_AI_CTRL_IMMEDIATE_STOP		BIT(4)
#घोषणा ME4000_AI_CTRL_STOP			BIT(5)
#घोषणा ME4000_AI_CTRL_CHANNEL_FIFO		BIT(6)
#घोषणा ME4000_AI_CTRL_DATA_FIFO		BIT(7)
#घोषणा ME4000_AI_CTRL_FULLSCALE		BIT(8)
#घोषणा ME4000_AI_CTRL_OFFSET			BIT(9)
#घोषणा ME4000_AI_CTRL_EX_TRIG_ANALOG		BIT(10)
#घोषणा ME4000_AI_CTRL_EX_TRIG			BIT(11)
#घोषणा ME4000_AI_CTRL_EX_TRIG_FALLING		BIT(12)
#घोषणा ME4000_AI_CTRL_EX_IRQ			BIT(13)
#घोषणा ME4000_AI_CTRL_EX_IRQ_RESET		BIT(14)
#घोषणा ME4000_AI_CTRL_LE_IRQ			BIT(15)
#घोषणा ME4000_AI_CTRL_LE_IRQ_RESET		BIT(16)
#घोषणा ME4000_AI_CTRL_HF_IRQ			BIT(17)
#घोषणा ME4000_AI_CTRL_HF_IRQ_RESET		BIT(18)
#घोषणा ME4000_AI_CTRL_SC_IRQ			BIT(19)
#घोषणा ME4000_AI_CTRL_SC_IRQ_RESET		BIT(20)
#घोषणा ME4000_AI_CTRL_SC_RELOAD		BIT(21)
#घोषणा ME4000_AI_STATUS_EF_CHANNEL		BIT(22)
#घोषणा ME4000_AI_STATUS_HF_CHANNEL		BIT(23)
#घोषणा ME4000_AI_STATUS_FF_CHANNEL		BIT(24)
#घोषणा ME4000_AI_STATUS_EF_DATA		BIT(25)
#घोषणा ME4000_AI_STATUS_HF_DATA		BIT(26)
#घोषणा ME4000_AI_STATUS_FF_DATA		BIT(27)
#घोषणा ME4000_AI_STATUS_LE			BIT(28)
#घोषणा ME4000_AI_STATUS_FSM			BIT(29)
#घोषणा ME4000_AI_CTRL_EX_TRIG_BOTH		BIT(31)
#घोषणा ME4000_AI_CHANNEL_LIST_REG		0x78
#घोषणा ME4000_AI_LIST_INPUT_DIFFERENTIAL	BIT(5)
#घोषणा ME4000_AI_LIST_RANGE(x)			((3 - ((x) & 3)) << 6)
#घोषणा ME4000_AI_LIST_LAST_ENTRY		BIT(8)
#घोषणा ME4000_AI_DATA_REG			0x7c
#घोषणा ME4000_AI_CHAN_TIMER_REG		0x80
#घोषणा ME4000_AI_CHAN_PRE_TIMER_REG		0x84
#घोषणा ME4000_AI_SCAN_TIMER_LOW_REG		0x88
#घोषणा ME4000_AI_SCAN_TIMER_HIGH_REG		0x8c
#घोषणा ME4000_AI_SCAN_PRE_TIMER_LOW_REG	0x90
#घोषणा ME4000_AI_SCAN_PRE_TIMER_HIGH_REG	0x94
#घोषणा ME4000_AI_START_REG			0x98
#घोषणा ME4000_IRQ_STATUS_REG			0x9c
#घोषणा ME4000_IRQ_STATUS_EX			BIT(0)
#घोषणा ME4000_IRQ_STATUS_LE			BIT(1)
#घोषणा ME4000_IRQ_STATUS_AI_HF			BIT(2)
#घोषणा ME4000_IRQ_STATUS_AO_0_HF		BIT(3)
#घोषणा ME4000_IRQ_STATUS_AO_1_HF		BIT(4)
#घोषणा ME4000_IRQ_STATUS_AO_2_HF		BIT(5)
#घोषणा ME4000_IRQ_STATUS_AO_3_HF		BIT(6)
#घोषणा ME4000_IRQ_STATUS_SC			BIT(7)
#घोषणा ME4000_DIO_PORT_0_REG			0xa0
#घोषणा ME4000_DIO_PORT_1_REG			0xa4
#घोषणा ME4000_DIO_PORT_2_REG			0xa8
#घोषणा ME4000_DIO_PORT_3_REG			0xac
#घोषणा ME4000_DIO_सूची_REG			0xb0
#घोषणा ME4000_AO_LOADSETREG_XX			0xb4
#घोषणा ME4000_DIO_CTRL_REG			0xb8
#घोषणा ME4000_DIO_CTRL_MODE_0			BIT(0)
#घोषणा ME4000_DIO_CTRL_MODE_1			BIT(1)
#घोषणा ME4000_DIO_CTRL_MODE_2			BIT(2)
#घोषणा ME4000_DIO_CTRL_MODE_3			BIT(3)
#घोषणा ME4000_DIO_CTRL_MODE_4			BIT(4)
#घोषणा ME4000_DIO_CTRL_MODE_5			BIT(5)
#घोषणा ME4000_DIO_CTRL_MODE_6			BIT(6)
#घोषणा ME4000_DIO_CTRL_MODE_7			BIT(7)
#घोषणा ME4000_DIO_CTRL_FUNCTION_0		BIT(8)
#घोषणा ME4000_DIO_CTRL_FUNCTION_1		BIT(9)
#घोषणा ME4000_DIO_CTRL_FIFO_HIGH_0		BIT(10)
#घोषणा ME4000_DIO_CTRL_FIFO_HIGH_1		BIT(11)
#घोषणा ME4000_DIO_CTRL_FIFO_HIGH_2		BIT(12)
#घोषणा ME4000_DIO_CTRL_FIFO_HIGH_3		BIT(13)
#घोषणा ME4000_AO_DEMUX_ADJUST_REG		0xbc
#घोषणा ME4000_AO_DEMUX_ADJUST_VALUE		0x4c
#घोषणा ME4000_AI_SAMPLE_COUNTER_REG		0xc0

#घोषणा ME4000_AI_FIFO_COUNT			2048

#घोषणा ME4000_AI_MIN_TICKS			66
#घोषणा ME4000_AI_MIN_SAMPLE_TIME		2000

#घोषणा ME4000_AI_CHANNEL_LIST_COUNT		1024

काष्ठा me4000_निजी अणु
	अचिन्हित दीर्घ plx_regbase;
	अचिन्हित पूर्णांक ai_ctrl_mode;
	अचिन्हित पूर्णांक ai_init_ticks;
	अचिन्हित पूर्णांक ai_scan_ticks;
	अचिन्हित पूर्णांक ai_chan_ticks;
पूर्ण;

क्रमागत me4000_boardid अणु
	BOARD_ME4650,
	BOARD_ME4660,
	BOARD_ME4660I,
	BOARD_ME4660S,
	BOARD_ME4660IS,
	BOARD_ME4670,
	BOARD_ME4670I,
	BOARD_ME4670S,
	BOARD_ME4670IS,
	BOARD_ME4680,
	BOARD_ME4680I,
	BOARD_ME4680S,
	BOARD_ME4680IS,
पूर्ण;

काष्ठा me4000_board अणु
	स्थिर अक्षर *name;
	पूर्णांक ai_nchan;
	अचिन्हित पूर्णांक can_करो_dअगरf_ai:1;
	अचिन्हित पूर्णांक can_करो_sh_ai:1;	/* sample & hold (8 channels) */
	अचिन्हित पूर्णांक ex_trig_analog:1;
	अचिन्हित पूर्णांक has_ao:1;
	अचिन्हित पूर्णांक has_ao_fअगरo:1;
	अचिन्हित पूर्णांक has_counter:1;
पूर्ण;

अटल स्थिर काष्ठा me4000_board me4000_boards[] = अणु
	[BOARD_ME4650] = अणु
		.name		= "ME-4650",
		.ai_nchan	= 16,
	पूर्ण,
	[BOARD_ME4660] = अणु
		.name		= "ME-4660",
		.ai_nchan	= 32,
		.can_करो_dअगरf_ai	= 1,
		.has_counter	= 1,
	पूर्ण,
	[BOARD_ME4660I] = अणु
		.name		= "ME-4660i",
		.ai_nchan	= 32,
		.can_करो_dअगरf_ai	= 1,
		.has_counter	= 1,
	पूर्ण,
	[BOARD_ME4660S] = अणु
		.name		= "ME-4660s",
		.ai_nchan	= 32,
		.can_करो_dअगरf_ai	= 1,
		.can_करो_sh_ai	= 1,
		.has_counter	= 1,
	पूर्ण,
	[BOARD_ME4660IS] = अणु
		.name		= "ME-4660is",
		.ai_nchan	= 32,
		.can_करो_dअगरf_ai	= 1,
		.can_करो_sh_ai	= 1,
		.has_counter	= 1,
	पूर्ण,
	[BOARD_ME4670] = अणु
		.name		= "ME-4670",
		.ai_nchan	= 32,
		.can_करो_dअगरf_ai	= 1,
		.ex_trig_analog	= 1,
		.has_ao		= 1,
		.has_counter	= 1,
	पूर्ण,
	[BOARD_ME4670I] = अणु
		.name		= "ME-4670i",
		.ai_nchan	= 32,
		.can_करो_dअगरf_ai	= 1,
		.ex_trig_analog	= 1,
		.has_ao		= 1,
		.has_counter	= 1,
	पूर्ण,
	[BOARD_ME4670S] = अणु
		.name		= "ME-4670s",
		.ai_nchan	= 32,
		.can_करो_dअगरf_ai	= 1,
		.can_करो_sh_ai	= 1,
		.ex_trig_analog	= 1,
		.has_ao		= 1,
		.has_counter	= 1,
	पूर्ण,
	[BOARD_ME4670IS] = अणु
		.name		= "ME-4670is",
		.ai_nchan	= 32,
		.can_करो_dअगरf_ai	= 1,
		.can_करो_sh_ai	= 1,
		.ex_trig_analog	= 1,
		.has_ao		= 1,
		.has_counter	= 1,
	पूर्ण,
	[BOARD_ME4680] = अणु
		.name		= "ME-4680",
		.ai_nchan	= 32,
		.can_करो_dअगरf_ai	= 1,
		.ex_trig_analog	= 1,
		.has_ao		= 1,
		.has_ao_fअगरo	= 1,
		.has_counter	= 1,
	पूर्ण,
	[BOARD_ME4680I] = अणु
		.name		= "ME-4680i",
		.ai_nchan	= 32,
		.can_करो_dअगरf_ai	= 1,
		.ex_trig_analog	= 1,
		.has_ao		= 1,
		.has_ao_fअगरo	= 1,
		.has_counter	= 1,
	पूर्ण,
	[BOARD_ME4680S] = अणु
		.name		= "ME-4680s",
		.ai_nchan	= 32,
		.can_करो_dअगरf_ai	= 1,
		.can_करो_sh_ai	= 1,
		.ex_trig_analog	= 1,
		.has_ao		= 1,
		.has_ao_fअगरo	= 1,
		.has_counter	= 1,
	पूर्ण,
	[BOARD_ME4680IS] = अणु
		.name		= "ME-4680is",
		.ai_nchan	= 32,
		.can_करो_dअगरf_ai	= 1,
		.can_करो_sh_ai	= 1,
		.ex_trig_analog	= 1,
		.has_ao		= 1,
		.has_ao_fअगरo	= 1,
		.has_counter	= 1,
	पूर्ण,
पूर्ण;

/*
 * NOTE: the ranges here are inverted compared to the values
 * written to the ME4000_AI_CHANNEL_LIST_REG,
 *
 * The ME4000_AI_LIST_RANGE() macro handles the inversion.
 */
अटल स्थिर काष्ठा comedi_lrange me4000_ai_range = अणु
	4, अणु
		UNI_RANGE(2.5),
		UNI_RANGE(10),
		BIP_RANGE(2.5),
		BIP_RANGE(10)
	पूर्ण
पूर्ण;

अटल पूर्णांक me4000_xilinx_करोwnload(काष्ठा comedi_device *dev,
				  स्थिर u8 *data, माप_प्रकार size,
				  अचिन्हित दीर्घ context)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	काष्ठा me4000_निजी *devpriv = dev->निजी;
	अचिन्हित दीर्घ xilinx_iobase = pci_resource_start(pcidev, 5);
	अचिन्हित पूर्णांक file_length;
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक i;

	अगर (!xilinx_iobase)
		वापस -ENODEV;

	/*
	 * Set PLX local पूर्णांकerrupt 2 polarity to high.
	 * Interrupt is thrown by init pin of xilinx.
	 */
	outl(PLX9052_INTCSR_LI2POL, devpriv->plx_regbase + PLX9052_INTCSR);

	/* Set /CS and /WRITE of the Xilinx */
	val = inl(devpriv->plx_regbase + PLX9052_CNTRL);
	val |= PLX9052_CNTRL_UIO2_DATA;
	outl(val, devpriv->plx_regbase + PLX9052_CNTRL);

	/* Init Xilinx with CS1 */
	inb(xilinx_iobase + 0xC8);

	/* Wait until /INIT pin is set */
	usleep_range(20, 1000);
	val = inl(devpriv->plx_regbase + PLX9052_INTCSR);
	अगर (!(val & PLX9052_INTCSR_LI2STAT)) अणु
		dev_err(dev->class_dev, "Can't init Xilinx\n");
		वापस -EIO;
	पूर्ण

	/* Reset /CS and /WRITE of the Xilinx */
	val = inl(devpriv->plx_regbase + PLX9052_CNTRL);
	val &= ~PLX9052_CNTRL_UIO2_DATA;
	outl(val, devpriv->plx_regbase + PLX9052_CNTRL);

	/* Download Xilinx firmware */
	file_length = (((अचिन्हित पूर्णांक)data[0] & 0xff) << 24) +
		      (((अचिन्हित पूर्णांक)data[1] & 0xff) << 16) +
		      (((अचिन्हित पूर्णांक)data[2] & 0xff) << 8) +
		      ((अचिन्हित पूर्णांक)data[3] & 0xff);
	usleep_range(10, 1000);

	क्रम (i = 0; i < file_length; i++) अणु
		outb(data[16 + i], xilinx_iobase);
		usleep_range(10, 1000);

		/* Check अगर BUSY flag is low */
		val = inl(devpriv->plx_regbase + PLX9052_CNTRL);
		अगर (val & PLX9052_CNTRL_UIO1_DATA) अणु
			dev_err(dev->class_dev,
				"Xilinx is still busy (i = %d)\n", i);
			वापस -EIO;
		पूर्ण
	पूर्ण

	/* If करोne flag is high करोwnload was successful */
	val = inl(devpriv->plx_regbase + PLX9052_CNTRL);
	अगर (!(val & PLX9052_CNTRL_UIO0_DATA)) अणु
		dev_err(dev->class_dev, "DONE flag is not set\n");
		dev_err(dev->class_dev, "Download not successful\n");
		वापस -EIO;
	पूर्ण

	/* Set /CS and /WRITE */
	val = inl(devpriv->plx_regbase + PLX9052_CNTRL);
	val |= PLX9052_CNTRL_UIO2_DATA;
	outl(val, devpriv->plx_regbase + PLX9052_CNTRL);

	वापस 0;
पूर्ण

अटल व्योम me4000_ai_reset(काष्ठा comedi_device *dev)
अणु
	अचिन्हित पूर्णांक ctrl;

	/* Stop any running conversion */
	ctrl = inl(dev->iobase + ME4000_AI_CTRL_REG);
	ctrl |= ME4000_AI_CTRL_STOP | ME4000_AI_CTRL_IMMEDIATE_STOP;
	outl(ctrl, dev->iobase + ME4000_AI_CTRL_REG);

	/* Clear the control रेजिस्टर */
	outl(0x0, dev->iobase + ME4000_AI_CTRL_REG);
पूर्ण

अटल व्योम me4000_reset(काष्ठा comedi_device *dev)
अणु
	काष्ठा me4000_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक val;
	पूर्णांक chan;

	/* Disable पूर्णांकerrupts on the PLX */
	outl(0, devpriv->plx_regbase + PLX9052_INTCSR);

	/* Software reset the PLX */
	val = inl(devpriv->plx_regbase + PLX9052_CNTRL);
	val |= PLX9052_CNTRL_PCI_RESET;
	outl(val, devpriv->plx_regbase + PLX9052_CNTRL);
	val &= ~PLX9052_CNTRL_PCI_RESET;
	outl(val, devpriv->plx_regbase + PLX9052_CNTRL);

	/* 0x8000 to the DACs means an output voltage of 0V */
	क्रम (chan = 0; chan < 4; chan++)
		outl(0x8000, dev->iobase + ME4000_AO_SINGLE_REG(chan));

	me4000_ai_reset(dev);

	/* Set both stop bits in the analog output control रेजिस्टर */
	val = ME4000_AO_CTRL_IMMEDIATE_STOP | ME4000_AO_CTRL_STOP;
	क्रम (chan = 0; chan < 4; chan++)
		outl(val, dev->iobase + ME4000_AO_CTRL_REG(chan));

	/* Set the adusपंचांगent रेजिस्टर क्रम AO demux */
	outl(ME4000_AO_DEMUX_ADJUST_VALUE,
	     dev->iobase + ME4000_AO_DEMUX_ADJUST_REG);

	/*
	 * Set digital I/O direction क्रम port 0
	 * to output on isolated versions
	 */
	अगर (!(inl(dev->iobase + ME4000_DIO_सूची_REG) & 0x1))
		outl(0x1, dev->iobase + ME4000_DIO_CTRL_REG);
पूर्ण

अटल अचिन्हित पूर्णांक me4000_ai_get_sample(काष्ठा comedi_device *dev,
					 काष्ठा comedi_subdevice *s)
अणु
	अचिन्हित पूर्णांक val;

	/* पढ़ो two's complement value and munge to offset binary */
	val = inl(dev->iobase + ME4000_AI_DATA_REG);
	वापस comedi_offset_munge(s, val);
पूर्ण

अटल पूर्णांक me4000_ai_eoc(काष्ठा comedi_device *dev,
			 काष्ठा comedi_subdevice *s,
			 काष्ठा comedi_insn *insn,
			 अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = inl(dev->iobase + ME4000_AI_STATUS_REG);
	अगर (status & ME4000_AI_STATUS_EF_DATA)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक me4000_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक range = CR_RANGE(insn->chanspec);
	अचिन्हित पूर्णांक aref = CR_AREF(insn->chanspec);
	अचिन्हित पूर्णांक entry;
	पूर्णांक ret = 0;
	पूर्णांक i;

	entry = chan | ME4000_AI_LIST_RANGE(range);
	अगर (aref == AREF_DIFF) अणु
		अगर (!(s->subdev_flags & SDF_DIFF)) अणु
			dev_err(dev->class_dev,
				"Differential inputs are not available\n");
			वापस -EINVAL;
		पूर्ण

		अगर (!comedi_range_is_bipolar(s, range)) अणु
			dev_err(dev->class_dev,
				"Range must be bipolar when aref = diff\n");
			वापस -EINVAL;
		पूर्ण

		अगर (chan >= (s->n_chan / 2)) अणु
			dev_err(dev->class_dev,
				"Analog input is not available\n");
			वापस -EINVAL;
		पूर्ण
		entry |= ME4000_AI_LIST_INPUT_DIFFERENTIAL;
	पूर्ण

	entry |= ME4000_AI_LIST_LAST_ENTRY;

	/* Enable channel list and data fअगरo क्रम single acquisition mode */
	outl(ME4000_AI_CTRL_CHANNEL_FIFO | ME4000_AI_CTRL_DATA_FIFO,
	     dev->iobase + ME4000_AI_CTRL_REG);

	/* Generate channel list entry */
	outl(entry, dev->iobase + ME4000_AI_CHANNEL_LIST_REG);

	/* Set the समयr to maximum sample rate */
	outl(ME4000_AI_MIN_TICKS, dev->iobase + ME4000_AI_CHAN_TIMER_REG);
	outl(ME4000_AI_MIN_TICKS, dev->iobase + ME4000_AI_CHAN_PRE_TIMER_REG);

	क्रम (i = 0; i < insn->n; i++) अणु
		अचिन्हित पूर्णांक val;

		/* start conversion by dummy पढ़ो */
		inl(dev->iobase + ME4000_AI_START_REG);

		ret = comedi_समयout(dev, s, insn, me4000_ai_eoc, 0);
		अगर (ret)
			अवरोध;

		val = me4000_ai_get_sample(dev, s);
		data[i] = comedi_offset_munge(s, val);
	पूर्ण

	me4000_ai_reset(dev);

	वापस ret ? ret : insn->n;
पूर्ण

अटल पूर्णांक me4000_ai_cancel(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s)
अणु
	me4000_ai_reset(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक me4000_ai_check_chanlist(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s,
				    काष्ठा comedi_cmd *cmd)
अणु
	अचिन्हित पूर्णांक aref0 = CR_AREF(cmd->chanlist[0]);
	पूर्णांक i;

	क्रम (i = 0; i < cmd->chanlist_len; i++) अणु
		अचिन्हित पूर्णांक chan = CR_CHAN(cmd->chanlist[i]);
		अचिन्हित पूर्णांक range = CR_RANGE(cmd->chanlist[i]);
		अचिन्हित पूर्णांक aref = CR_AREF(cmd->chanlist[i]);

		अगर (aref != aref0) अणु
			dev_dbg(dev->class_dev,
				"Mode is not equal for all entries\n");
			वापस -EINVAL;
		पूर्ण

		अगर (aref == AREF_DIFF) अणु
			अगर (!(s->subdev_flags & SDF_DIFF)) अणु
				dev_err(dev->class_dev,
					"Differential inputs are not available\n");
				वापस -EINVAL;
			पूर्ण

			अगर (chan >= (s->n_chan / 2)) अणु
				dev_dbg(dev->class_dev,
					"Channel number to high\n");
				वापस -EINVAL;
			पूर्ण

			अगर (!comedi_range_is_bipolar(s, range)) अणु
				dev_dbg(dev->class_dev,
					"Bipolar is not selected in differential mode\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम me4000_ai_round_cmd_args(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s,
				     काष्ठा comedi_cmd *cmd)
अणु
	काष्ठा me4000_निजी *devpriv = dev->निजी;
	पूर्णांक rest;

	devpriv->ai_init_ticks = 0;
	devpriv->ai_scan_ticks = 0;
	devpriv->ai_chan_ticks = 0;

	अगर (cmd->start_arg) अणु
		devpriv->ai_init_ticks = (cmd->start_arg * 33) / 1000;
		rest = (cmd->start_arg * 33) % 1000;

		अगर ((cmd->flags & CMDF_ROUND_MASK) == CMDF_ROUND_NEAREST) अणु
			अगर (rest > 33)
				devpriv->ai_init_ticks++;
		पूर्ण अन्यथा अगर ((cmd->flags & CMDF_ROUND_MASK) == CMDF_ROUND_UP) अणु
			अगर (rest)
				devpriv->ai_init_ticks++;
		पूर्ण
	पूर्ण

	अगर (cmd->scan_begin_arg) अणु
		devpriv->ai_scan_ticks = (cmd->scan_begin_arg * 33) / 1000;
		rest = (cmd->scan_begin_arg * 33) % 1000;

		अगर ((cmd->flags & CMDF_ROUND_MASK) == CMDF_ROUND_NEAREST) अणु
			अगर (rest > 33)
				devpriv->ai_scan_ticks++;
		पूर्ण अन्यथा अगर ((cmd->flags & CMDF_ROUND_MASK) == CMDF_ROUND_UP) अणु
			अगर (rest)
				devpriv->ai_scan_ticks++;
		पूर्ण
	पूर्ण

	अगर (cmd->convert_arg) अणु
		devpriv->ai_chan_ticks = (cmd->convert_arg * 33) / 1000;
		rest = (cmd->convert_arg * 33) % 1000;

		अगर ((cmd->flags & CMDF_ROUND_MASK) == CMDF_ROUND_NEAREST) अणु
			अगर (rest > 33)
				devpriv->ai_chan_ticks++;
		पूर्ण अन्यथा अगर ((cmd->flags & CMDF_ROUND_MASK) == CMDF_ROUND_UP) अणु
			अगर (rest)
				devpriv->ai_chan_ticks++;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम me4000_ai_ग_लिखो_chanlist(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s,
				     काष्ठा comedi_cmd *cmd)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < cmd->chanlist_len; i++) अणु
		अचिन्हित पूर्णांक chan = CR_CHAN(cmd->chanlist[i]);
		अचिन्हित पूर्णांक range = CR_RANGE(cmd->chanlist[i]);
		अचिन्हित पूर्णांक aref = CR_AREF(cmd->chanlist[i]);
		अचिन्हित पूर्णांक entry;

		entry = chan | ME4000_AI_LIST_RANGE(range);

		अगर (aref == AREF_DIFF)
			entry |= ME4000_AI_LIST_INPUT_DIFFERENTIAL;

		अगर (i == (cmd->chanlist_len - 1))
			entry |= ME4000_AI_LIST_LAST_ENTRY;

		outl(entry, dev->iobase + ME4000_AI_CHANNEL_LIST_REG);
	पूर्ण
पूर्ण

अटल पूर्णांक me4000_ai_करो_cmd(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s)
अणु
	काष्ठा me4000_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित पूर्णांक ctrl;

	/* Write समयr arguments */
	outl(devpriv->ai_init_ticks - 1,
	     dev->iobase + ME4000_AI_SCAN_PRE_TIMER_LOW_REG);
	outl(0x0, dev->iobase + ME4000_AI_SCAN_PRE_TIMER_HIGH_REG);

	अगर (devpriv->ai_scan_ticks) अणु
		outl(devpriv->ai_scan_ticks - 1,
		     dev->iobase + ME4000_AI_SCAN_TIMER_LOW_REG);
		outl(0x0, dev->iobase + ME4000_AI_SCAN_TIMER_HIGH_REG);
	पूर्ण

	outl(devpriv->ai_chan_ticks - 1,
	     dev->iobase + ME4000_AI_CHAN_PRE_TIMER_REG);
	outl(devpriv->ai_chan_ticks - 1,
	     dev->iobase + ME4000_AI_CHAN_TIMER_REG);

	/* Start sources */
	ctrl = devpriv->ai_ctrl_mode |
	       ME4000_AI_CTRL_CHANNEL_FIFO |
	       ME4000_AI_CTRL_DATA_FIFO;

	/* Stop triggers */
	अगर (cmd->stop_src == TRIG_COUNT) अणु
		outl(cmd->chanlist_len * cmd->stop_arg,
		     dev->iobase + ME4000_AI_SAMPLE_COUNTER_REG);
		ctrl |= ME4000_AI_CTRL_SC_IRQ;
	पूर्ण अन्यथा अगर (cmd->stop_src == TRIG_NONE &&
		   cmd->scan_end_src == TRIG_COUNT) अणु
		outl(cmd->scan_end_arg,
		     dev->iobase + ME4000_AI_SAMPLE_COUNTER_REG);
		ctrl |= ME4000_AI_CTRL_SC_IRQ;
	पूर्ण
	ctrl |= ME4000_AI_CTRL_HF_IRQ;

	/* Write the setup to the control रेजिस्टर */
	outl(ctrl, dev->iobase + ME4000_AI_CTRL_REG);

	/* Write the channel list */
	me4000_ai_ग_लिखो_chanlist(dev, s, cmd);

	/* Start acquistion by dummy पढ़ो */
	inl(dev->iobase + ME4000_AI_START_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक me4000_ai_करो_cmd_test(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_cmd *cmd)
अणु
	काष्ठा me4000_निजी *devpriv = dev->निजी;
	पूर्णांक err = 0;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src,
					TRIG_FOLLOW | TRIG_TIMER | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->convert_src,
					TRIG_TIMER | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->scan_end_src,
					TRIG_NONE | TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_NONE | TRIG_COUNT);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->start_src);
	err |= comedi_check_trigger_is_unique(cmd->scan_begin_src);
	err |= comedi_check_trigger_is_unique(cmd->convert_src);
	err |= comedi_check_trigger_is_unique(cmd->scan_end_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	अगर (cmd->start_src == TRIG_NOW &&
	    cmd->scan_begin_src == TRIG_TIMER &&
	    cmd->convert_src == TRIG_TIMER) अणु
		devpriv->ai_ctrl_mode = ME4000_AI_CTRL_MODE_0;
	पूर्ण अन्यथा अगर (cmd->start_src == TRIG_NOW &&
		   cmd->scan_begin_src == TRIG_FOLLOW &&
		   cmd->convert_src == TRIG_TIMER) अणु
		devpriv->ai_ctrl_mode = ME4000_AI_CTRL_MODE_0;
	पूर्ण अन्यथा अगर (cmd->start_src == TRIG_EXT &&
		   cmd->scan_begin_src == TRIG_TIMER &&
		   cmd->convert_src == TRIG_TIMER) अणु
		devpriv->ai_ctrl_mode = ME4000_AI_CTRL_MODE_1;
	पूर्ण अन्यथा अगर (cmd->start_src == TRIG_EXT &&
		   cmd->scan_begin_src == TRIG_FOLLOW &&
		   cmd->convert_src == TRIG_TIMER) अणु
		devpriv->ai_ctrl_mode = ME4000_AI_CTRL_MODE_1;
	पूर्ण अन्यथा अगर (cmd->start_src == TRIG_EXT &&
		   cmd->scan_begin_src == TRIG_EXT &&
		   cmd->convert_src == TRIG_TIMER) अणु
		devpriv->ai_ctrl_mode = ME4000_AI_CTRL_MODE_2;
	पूर्ण अन्यथा अगर (cmd->start_src == TRIG_EXT &&
		   cmd->scan_begin_src == TRIG_EXT &&
		   cmd->convert_src == TRIG_EXT) अणु
		devpriv->ai_ctrl_mode = ME4000_AI_CTRL_MODE_0 |
					ME4000_AI_CTRL_MODE_1;
	पूर्ण अन्यथा अणु
		err |= -EINVAL;
	पूर्ण

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);

	अगर (cmd->chanlist_len < 1) अणु
		cmd->chanlist_len = 1;
		err |= -EINVAL;
	पूर्ण

	/* Round the समयr arguments */
	me4000_ai_round_cmd_args(dev, s, cmd);

	अगर (devpriv->ai_init_ticks < 66) अणु
		cmd->start_arg = 2000;
		err |= -EINVAL;
	पूर्ण
	अगर (devpriv->ai_scan_ticks && devpriv->ai_scan_ticks < 67) अणु
		cmd->scan_begin_arg = 2031;
		err |= -EINVAL;
	पूर्ण
	अगर (devpriv->ai_chan_ticks < 66) अणु
		cmd->convert_arg = 2000;
		err |= -EINVAL;
	पूर्ण

	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	अन्यथा	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/*
	 * Stage 4. Check क्रम argument conflicts.
	 */
	अगर (cmd->start_src == TRIG_NOW &&
	    cmd->scan_begin_src == TRIG_TIMER &&
	    cmd->convert_src == TRIG_TIMER) अणु
		/* Check समयr arguments */
		अगर (devpriv->ai_init_ticks < ME4000_AI_MIN_TICKS) अणु
			dev_err(dev->class_dev, "Invalid start arg\n");
			cmd->start_arg = 2000;	/*  66 ticks at least */
			err++;
		पूर्ण
		अगर (devpriv->ai_chan_ticks < ME4000_AI_MIN_TICKS) अणु
			dev_err(dev->class_dev, "Invalid convert arg\n");
			cmd->convert_arg = 2000;	/*  66 ticks at least */
			err++;
		पूर्ण
		अगर (devpriv->ai_scan_ticks <=
		    cmd->chanlist_len * devpriv->ai_chan_ticks) अणु
			dev_err(dev->class_dev, "Invalid scan end arg\n");

			/*  At least one tick more */
			cmd->scan_end_arg = 2000 * cmd->chanlist_len + 31;
			err++;
		पूर्ण
	पूर्ण अन्यथा अगर (cmd->start_src == TRIG_NOW &&
		   cmd->scan_begin_src == TRIG_FOLLOW &&
		   cmd->convert_src == TRIG_TIMER) अणु
		/* Check समयr arguments */
		अगर (devpriv->ai_init_ticks < ME4000_AI_MIN_TICKS) अणु
			dev_err(dev->class_dev, "Invalid start arg\n");
			cmd->start_arg = 2000;	/*  66 ticks at least */
			err++;
		पूर्ण
		अगर (devpriv->ai_chan_ticks < ME4000_AI_MIN_TICKS) अणु
			dev_err(dev->class_dev, "Invalid convert arg\n");
			cmd->convert_arg = 2000;	/*  66 ticks at least */
			err++;
		पूर्ण
	पूर्ण अन्यथा अगर (cmd->start_src == TRIG_EXT &&
		   cmd->scan_begin_src == TRIG_TIMER &&
		   cmd->convert_src == TRIG_TIMER) अणु
		/* Check समयr arguments */
		अगर (devpriv->ai_init_ticks < ME4000_AI_MIN_TICKS) अणु
			dev_err(dev->class_dev, "Invalid start arg\n");
			cmd->start_arg = 2000;	/*  66 ticks at least */
			err++;
		पूर्ण
		अगर (devpriv->ai_chan_ticks < ME4000_AI_MIN_TICKS) अणु
			dev_err(dev->class_dev, "Invalid convert arg\n");
			cmd->convert_arg = 2000;	/*  66 ticks at least */
			err++;
		पूर्ण
		अगर (devpriv->ai_scan_ticks <=
		    cmd->chanlist_len * devpriv->ai_chan_ticks) अणु
			dev_err(dev->class_dev, "Invalid scan end arg\n");

			/*  At least one tick more */
			cmd->scan_end_arg = 2000 * cmd->chanlist_len + 31;
			err++;
		पूर्ण
	पूर्ण अन्यथा अगर (cmd->start_src == TRIG_EXT &&
		   cmd->scan_begin_src == TRIG_FOLLOW &&
		   cmd->convert_src == TRIG_TIMER) अणु
		/* Check समयr arguments */
		अगर (devpriv->ai_init_ticks < ME4000_AI_MIN_TICKS) अणु
			dev_err(dev->class_dev, "Invalid start arg\n");
			cmd->start_arg = 2000;	/*  66 ticks at least */
			err++;
		पूर्ण
		अगर (devpriv->ai_chan_ticks < ME4000_AI_MIN_TICKS) अणु
			dev_err(dev->class_dev, "Invalid convert arg\n");
			cmd->convert_arg = 2000;	/*  66 ticks at least */
			err++;
		पूर्ण
	पूर्ण अन्यथा अगर (cmd->start_src == TRIG_EXT &&
		   cmd->scan_begin_src == TRIG_EXT &&
		   cmd->convert_src == TRIG_TIMER) अणु
		/* Check समयr arguments */
		अगर (devpriv->ai_init_ticks < ME4000_AI_MIN_TICKS) अणु
			dev_err(dev->class_dev, "Invalid start arg\n");
			cmd->start_arg = 2000;	/*  66 ticks at least */
			err++;
		पूर्ण
		अगर (devpriv->ai_chan_ticks < ME4000_AI_MIN_TICKS) अणु
			dev_err(dev->class_dev, "Invalid convert arg\n");
			cmd->convert_arg = 2000;	/*  66 ticks at least */
			err++;
		पूर्ण
	पूर्ण अन्यथा अगर (cmd->start_src == TRIG_EXT &&
		   cmd->scan_begin_src == TRIG_EXT &&
		   cmd->convert_src == TRIG_EXT) अणु
		/* Check समयr arguments */
		अगर (devpriv->ai_init_ticks < ME4000_AI_MIN_TICKS) अणु
			dev_err(dev->class_dev, "Invalid start arg\n");
			cmd->start_arg = 2000;	/*  66 ticks at least */
			err++;
		पूर्ण
	पूर्ण
	अगर (cmd->scan_end_src == TRIG_COUNT) अणु
		अगर (cmd->scan_end_arg == 0) अणु
			dev_err(dev->class_dev, "Invalid scan end arg\n");
			cmd->scan_end_arg = 1;
			err++;
		पूर्ण
	पूर्ण

	अगर (err)
		वापस 4;

	/* Step 5: check channel list अगर it exists */
	अगर (cmd->chanlist && cmd->chanlist_len > 0)
		err |= me4000_ai_check_chanlist(dev, s, cmd);

	अगर (err)
		वापस 5;

	वापस 0;
पूर्ण

अटल irqवापस_t me4000_ai_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	काष्ठा comedi_device *dev = dev_id;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	पूर्णांक i;
	पूर्णांक c = 0;
	अचिन्हित लघु lval;

	अगर (!dev->attached)
		वापस IRQ_NONE;

	अगर (inl(dev->iobase + ME4000_IRQ_STATUS_REG) &
	    ME4000_IRQ_STATUS_AI_HF) अणु
		/* Read status रेजिस्टर to find out what happened */
		पंचांगp = inl(dev->iobase + ME4000_AI_STATUS_REG);

		अगर (!(पंचांगp & ME4000_AI_STATUS_FF_DATA) &&
		    !(पंचांगp & ME4000_AI_STATUS_HF_DATA) &&
		    (पंचांगp & ME4000_AI_STATUS_EF_DATA)) अणु
			dev_err(dev->class_dev, "FIFO overflow\n");
			s->async->events |= COMEDI_CB_ERROR;
			c = ME4000_AI_FIFO_COUNT;
		पूर्ण अन्यथा अगर ((पंचांगp & ME4000_AI_STATUS_FF_DATA) &&
			   !(पंचांगp & ME4000_AI_STATUS_HF_DATA) &&
			   (पंचांगp & ME4000_AI_STATUS_EF_DATA)) अणु
			c = ME4000_AI_FIFO_COUNT / 2;
		पूर्ण अन्यथा अणु
			dev_err(dev->class_dev, "Undefined FIFO state\n");
			s->async->events |= COMEDI_CB_ERROR;
			c = 0;
		पूर्ण

		क्रम (i = 0; i < c; i++) अणु
			lval = me4000_ai_get_sample(dev, s);
			अगर (!comedi_buf_ग_लिखो_samples(s, &lval, 1))
				अवरोध;
		पूर्ण

		/* Work is करोne, so reset the पूर्णांकerrupt */
		पंचांगp |= ME4000_AI_CTRL_HF_IRQ_RESET;
		outl(पंचांगp, dev->iobase + ME4000_AI_CTRL_REG);
		पंचांगp &= ~ME4000_AI_CTRL_HF_IRQ_RESET;
		outl(पंचांगp, dev->iobase + ME4000_AI_CTRL_REG);
	पूर्ण

	अगर (inl(dev->iobase + ME4000_IRQ_STATUS_REG) &
	    ME4000_IRQ_STATUS_SC) अणु
		/* Acquisition is complete */
		s->async->events |= COMEDI_CB_EOA;

		/* Poll data until fअगरo empty */
		जबतक (inl(dev->iobase + ME4000_AI_STATUS_REG) &
		       ME4000_AI_STATUS_EF_DATA) अणु
			lval = me4000_ai_get_sample(dev, s);
			अगर (!comedi_buf_ग_लिखो_samples(s, &lval, 1))
				अवरोध;
		पूर्ण

		/* Work is करोne, so reset the पूर्णांकerrupt */
		पंचांगp = inl(dev->iobase + ME4000_AI_CTRL_REG);
		पंचांगp |= ME4000_AI_CTRL_SC_IRQ_RESET;
		outl(पंचांगp, dev->iobase + ME4000_AI_CTRL_REG);
		पंचांगp &= ~ME4000_AI_CTRL_SC_IRQ_RESET;
		outl(पंचांगp, dev->iobase + ME4000_AI_CTRL_REG);
	पूर्ण

	comedi_handle_events(dev, s);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक me4000_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक पंचांगp;

	/* Stop any running conversion */
	पंचांगp = inl(dev->iobase + ME4000_AO_CTRL_REG(chan));
	पंचांगp |= ME4000_AO_CTRL_IMMEDIATE_STOP;
	outl(पंचांगp, dev->iobase + ME4000_AO_CTRL_REG(chan));

	/* Clear control रेजिस्टर and set to single mode */
	outl(0x0, dev->iobase + ME4000_AO_CTRL_REG(chan));

	/* Write data value */
	outl(data[0], dev->iobase + ME4000_AO_SINGLE_REG(chan));

	/* Store in the mirror */
	s->पढ़ोback[chan] = data[0];

	वापस 1;
पूर्ण

अटल पूर्णांक me4000_dio_insn_bits(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data)) अणु
		outl((s->state >> 0) & 0xFF,
		     dev->iobase + ME4000_DIO_PORT_0_REG);
		outl((s->state >> 8) & 0xFF,
		     dev->iobase + ME4000_DIO_PORT_1_REG);
		outl((s->state >> 16) & 0xFF,
		     dev->iobase + ME4000_DIO_PORT_2_REG);
		outl((s->state >> 24) & 0xFF,
		     dev->iobase + ME4000_DIO_PORT_3_REG);
	पूर्ण

	data[1] = ((inl(dev->iobase + ME4000_DIO_PORT_0_REG) & 0xFF) << 0) |
		  ((inl(dev->iobase + ME4000_DIO_PORT_1_REG) & 0xFF) << 8) |
		  ((inl(dev->iobase + ME4000_DIO_PORT_2_REG) & 0xFF) << 16) |
		  ((inl(dev->iobase + ME4000_DIO_PORT_3_REG) & 0xFF) << 24);

	वापस insn->n;
पूर्ण

अटल पूर्णांक me4000_dio_insn_config(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक ret;

	अगर (chan < 8)
		mask = 0x000000ff;
	अन्यथा अगर (chan < 16)
		mask = 0x0000ff00;
	अन्यथा अगर (chan < 24)
		mask = 0x00ff0000;
	अन्यथा
		mask = 0xff000000;

	ret = comedi_dio_insn_config(dev, s, insn, data, mask);
	अगर (ret)
		वापस ret;

	पंचांगp = inl(dev->iobase + ME4000_DIO_CTRL_REG);
	पंचांगp &= ~(ME4000_DIO_CTRL_MODE_0 | ME4000_DIO_CTRL_MODE_1 |
		 ME4000_DIO_CTRL_MODE_2 | ME4000_DIO_CTRL_MODE_3 |
		 ME4000_DIO_CTRL_MODE_4 | ME4000_DIO_CTRL_MODE_5 |
		 ME4000_DIO_CTRL_MODE_6 | ME4000_DIO_CTRL_MODE_7);
	अगर (s->io_bits & 0x000000ff)
		पंचांगp |= ME4000_DIO_CTRL_MODE_0;
	अगर (s->io_bits & 0x0000ff00)
		पंचांगp |= ME4000_DIO_CTRL_MODE_2;
	अगर (s->io_bits & 0x00ff0000)
		पंचांगp |= ME4000_DIO_CTRL_MODE_4;
	अगर (s->io_bits & 0xff000000)
		पंचांगp |= ME4000_DIO_CTRL_MODE_6;

	/*
	 * Check क्रम optoisolated ME-4000 version.
	 * If one the first port is a fixed output
	 * port and the second is a fixed input port.
	 */
	अगर (inl(dev->iobase + ME4000_DIO_सूची_REG)) अणु
		s->io_bits |= 0x000000ff;
		s->io_bits &= ~0x0000ff00;
		पंचांगp |= ME4000_DIO_CTRL_MODE_0;
		पंचांगp &= ~(ME4000_DIO_CTRL_MODE_2 | ME4000_DIO_CTRL_MODE_3);
	पूर्ण

	outl(पंचांगp, dev->iobase + ME4000_DIO_CTRL_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक me4000_स्वतः_attach(काष्ठा comedi_device *dev,
			      अचिन्हित दीर्घ context)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	स्थिर काष्ठा me4000_board *board = शून्य;
	काष्ठा me4000_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक result;

	अगर (context < ARRAY_SIZE(me4000_boards))
		board = &me4000_boards[context];
	अगर (!board)
		वापस -ENODEV;
	dev->board_ptr = board;
	dev->board_name = board->name;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	result = comedi_pci_enable(dev);
	अगर (result)
		वापस result;

	devpriv->plx_regbase = pci_resource_start(pcidev, 1);
	dev->iobase = pci_resource_start(pcidev, 2);
	अगर (!devpriv->plx_regbase || !dev->iobase)
		वापस -ENODEV;

	result = comedi_load_firmware(dev, &pcidev->dev, ME4000_FIRMWARE,
				      me4000_xilinx_करोwnload, 0);
	अगर (result < 0)
		वापस result;

	me4000_reset(dev);

	अगर (pcidev->irq > 0) अणु
		result = request_irq(pcidev->irq, me4000_ai_isr, IRQF_SHARED,
				     dev->board_name, dev);
		अगर (result == 0) अणु
			dev->irq = pcidev->irq;

			/* Enable पूर्णांकerrupts on the PLX */
			outl(PLX9052_INTCSR_LI1ENAB | PLX9052_INTCSR_LI1POL |
			     PLX9052_INTCSR_PCIENAB,
			     devpriv->plx_regbase + PLX9052_INTCSR);
		पूर्ण
	पूर्ण

	result = comedi_alloc_subdevices(dev, 4);
	अगर (result)
		वापस result;

	/* Analog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE | SDF_COMMON | SDF_GROUND;
	अगर (board->can_करो_dअगरf_ai)
		s->subdev_flags	|= SDF_DIFF;
	s->n_chan	= board->ai_nchan;
	s->maxdata	= 0xffff;
	s->len_chanlist	= ME4000_AI_CHANNEL_LIST_COUNT;
	s->range_table	= &me4000_ai_range;
	s->insn_पढ़ो	= me4000_ai_insn_पढ़ो;

	अगर (dev->irq) अणु
		dev->पढ़ो_subdev = s;
		s->subdev_flags	|= SDF_CMD_READ;
		s->cancel	= me4000_ai_cancel;
		s->करो_cmdtest	= me4000_ai_करो_cmd_test;
		s->करो_cmd	= me4000_ai_करो_cmd;
	पूर्ण

	/* Analog Output subdevice */
	s = &dev->subdevices[1];
	अगर (board->has_ao) अणु
		s->type		= COMEDI_SUBD_AO;
		s->subdev_flags	= SDF_WRITABLE | SDF_COMMON | SDF_GROUND;
		s->n_chan	= 4;
		s->maxdata	= 0xffff;
		s->range_table	= &range_bipolar10;
		s->insn_ग_लिखो	= me4000_ao_insn_ग_लिखो;

		result = comedi_alloc_subdev_पढ़ोback(s);
		अगर (result)
			वापस result;
	पूर्ण अन्यथा अणु
		s->type		= COMEDI_SUBD_UNUSED;
	पूर्ण

	/* Digital I/O subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_flags	= SDF_READABLE | SDF_WRITABLE;
	s->n_chan	= 32;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= me4000_dio_insn_bits;
	s->insn_config	= me4000_dio_insn_config;

	/*
	 * Check क्रम optoisolated ME-4000 version. If one the first
	 * port is a fixed output port and the second is a fixed input port.
	 */
	अगर (!inl(dev->iobase + ME4000_DIO_सूची_REG)) अणु
		s->io_bits |= 0xFF;
		outl(ME4000_DIO_CTRL_MODE_0,
		     dev->iobase + ME4000_DIO_सूची_REG);
	पूर्ण

	/* Counter subdevice (8254) */
	s = &dev->subdevices[3];
	अगर (board->has_counter) अणु
		अचिन्हित दीर्घ समयr_base = pci_resource_start(pcidev, 3);

		अगर (!समयr_base)
			वापस -ENODEV;

		dev->pacer = comedi_8254_init(समयr_base, 0, I8254_IO8, 0);
		अगर (!dev->pacer)
			वापस -ENOMEM;

		comedi_8254_subdevice_init(s, dev->pacer);
	पूर्ण अन्यथा अणु
		s->type = COMEDI_SUBD_UNUSED;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम me4000_detach(काष्ठा comedi_device *dev)
अणु
	अगर (dev->irq) अणु
		काष्ठा me4000_निजी *devpriv = dev->निजी;

		/* Disable पूर्णांकerrupts on the PLX */
		outl(0, devpriv->plx_regbase + PLX9052_INTCSR);
	पूर्ण
	comedi_pci_detach(dev);
पूर्ण

अटल काष्ठा comedi_driver me4000_driver = अणु
	.driver_name	= "me4000",
	.module		= THIS_MODULE,
	.स्वतः_attach	= me4000_स्वतः_attach,
	.detach		= me4000_detach,
पूर्ण;

अटल पूर्णांक me4000_pci_probe(काष्ठा pci_dev *dev,
			    स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &me4000_driver, id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id me4000_pci_table[] = अणु
	अणु PCI_VDEVICE(MEILHAUS, 0x4650), BOARD_ME4650 पूर्ण,
	अणु PCI_VDEVICE(MEILHAUS, 0x4660), BOARD_ME4660 पूर्ण,
	अणु PCI_VDEVICE(MEILHAUS, 0x4661), BOARD_ME4660I पूर्ण,
	अणु PCI_VDEVICE(MEILHAUS, 0x4662), BOARD_ME4660S पूर्ण,
	अणु PCI_VDEVICE(MEILHAUS, 0x4663), BOARD_ME4660IS पूर्ण,
	अणु PCI_VDEVICE(MEILHAUS, 0x4670), BOARD_ME4670 पूर्ण,
	अणु PCI_VDEVICE(MEILHAUS, 0x4671), BOARD_ME4670I पूर्ण,
	अणु PCI_VDEVICE(MEILHAUS, 0x4672), BOARD_ME4670S पूर्ण,
	अणु PCI_VDEVICE(MEILHAUS, 0x4673), BOARD_ME4670IS पूर्ण,
	अणु PCI_VDEVICE(MEILHAUS, 0x4680), BOARD_ME4680 पूर्ण,
	अणु PCI_VDEVICE(MEILHAUS, 0x4681), BOARD_ME4680I पूर्ण,
	अणु PCI_VDEVICE(MEILHAUS, 0x4682), BOARD_ME4680S पूर्ण,
	अणु PCI_VDEVICE(MEILHAUS, 0x4683), BOARD_ME4680IS पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, me4000_pci_table);

अटल काष्ठा pci_driver me4000_pci_driver = अणु
	.name		= "me4000",
	.id_table	= me4000_pci_table,
	.probe		= me4000_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(me4000_driver, me4000_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for Meilhaus ME-4000 series boards");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(ME4000_FIRMWARE);
