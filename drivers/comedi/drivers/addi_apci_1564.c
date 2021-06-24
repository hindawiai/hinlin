<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * addi_apci_1564.c
 * Copyright (C) 2004,2005  ADDI-DATA GmbH क्रम the source code of this module.
 *
 *	ADDI-DATA GmbH
 *	Dieselstrasse 3
 *	D-77833 Ottersweier
 *	Tel: +19(0)7223/9493-0
 *	Fax: +49(0)7223/9493-92
 *	http://www.addi-data.com
 *	info@addi-data.com
 */

/*
 * Driver: addi_apci_1564
 * Description: ADDI-DATA APCI-1564 Digital I/O board
 * Devices: [ADDI-DATA] APCI-1564 (addi_apci_1564)
 * Author: H Hartley Sweeten <hsweeten@visionengravers.com>
 * Updated: Thu, 02 Jun 2016 13:12:46 -0700
 * Status: untested
 *
 * Configuration Options: not applicable, uses comedi PCI स्वतः config
 *
 * This board has the following features:
 *   - 32 optically isolated digital inमाला_दो (24V), 16 of which can
 *     generate change-of-state (COS) पूर्णांकerrupts (channels 4 to 19)
 *   - 32 optically isolated digital outमाला_दो (10V to 36V)
 *   - 1 8-bit watchकरोg क्रम resetting the outमाला_दो
 *   - 1 12-bit समयr
 *   - 3 32-bit counters
 *   - 2 diagnostic inमाला_दो
 *
 * The COS, समयr, and counter subdevices all use the dev->पढ़ो_subdev to
 * वापस the पूर्णांकerrupt status. The sample data is updated and वापसed when
 * any of these subdevices generate an पूर्णांकerrupt. The sample data क्रमmat is:
 *
 *    Bit   Description
 *   -----  ------------------------------------------
 *    31    COS पूर्णांकerrupt
 *    30    समयr पूर्णांकerrupt
 *    29    counter 2 पूर्णांकerrupt
 *    28    counter 1 पूर्णांकerrupt
 *    27    counter 0 पूर्णांकerrupt
 *   26:20  not used
 *   19:4   COS digital input state (channels 19 to 4)
 *    3:0   not used
 *
 * The COS पूर्णांकerrupts must be configured using an INSN_CONFIG_DIGITAL_TRIG
 * inकाष्ठाion beक्रमe they can be enabled by an async command. The COS
 * पूर्णांकerrupts will stay active until canceled.
 *
 * The समयr subdevice करोes not use an async command. All control is handled
 * by the (*insn_config).
 *
 * FIXME: The क्रमmat of the ADDI_TCW_TIMEBASE_REG is not descibed in the
 * datasheet I have. The INSN_CONFIG_SET_CLOCK_SRC currently just ग_लिखोs
 * the raw data[1] to this रेजिस्टर aदीर्घ with the raw data[2] value to the
 * ADDI_TCW_RELOAD_REG. If anyone tests this and can determine the actual
 * समयbase/reload operation please let me know.
 *
 * The counter subdevice also करोes not use an async command. All control is
 * handled by the (*insn_config).
 *
 * FIXME: The operation of the counters is not really described in the
 * datasheet I have. The (*insn_config) needs more work.
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "../comedi_pci.h"
#समावेश "addi_tcw.h"
#समावेश "addi_watchdog.h"

/*
 * PCI BAR 0
 *
 * PLD Revision 1.0 I/O Mapping
 *   0x00         93C76 EEPROM
 *   0x04 - 0x18  Timer 12-Bit
 *
 * PLD Revision 2.x I/O Mapping
 *   0x00         93C76 EEPROM
 *   0x04 - 0x14  Digital Input
 *   0x18 - 0x25  Digital Output
 *   0x28 - 0x44  Watchकरोg 8-Bit
 *   0x48 - 0x64  Timer 12-Bit
 */
#घोषणा APCI1564_EEPROM_REG			0x00
#घोषणा APCI1564_EEPROM_VCC_STATUS		BIT(8)
#घोषणा APCI1564_EEPROM_TO_REV(x)		(((x) >> 4) & 0xf)
#घोषणा APCI1564_EEPROM_DI			BIT(3)
#घोषणा APCI1564_EEPROM_DO			BIT(2)
#घोषणा APCI1564_EEPROM_CS			BIT(1)
#घोषणा APCI1564_EEPROM_CLK			BIT(0)
#घोषणा APCI1564_REV1_TIMER_IOBASE		0x04
#घोषणा APCI1564_REV2_MAIN_IOBASE		0x04
#घोषणा APCI1564_REV2_TIMER_IOBASE		0x48

/*
 * PCI BAR 1
 *
 * PLD Revision 1.0 I/O Mapping
 *   0x00 - 0x10  Digital Input
 *   0x14 - 0x20  Digital Output
 *   0x24 - 0x3c  Watchकरोg 8-Bit
 *
 * PLD Revision 2.x I/O Mapping
 *   0x00         Counter_0
 *   0x20         Counter_1
 *   0x30         Counter_3
 */
#घोषणा APCI1564_REV1_MAIN_IOBASE		0x00

/*
 * dev->iobase Register Map
 *   PLD Revision 1.0 - PCI BAR 1 + 0x00
 *   PLD Revision 2.x - PCI BAR 0 + 0x04
 */
#घोषणा APCI1564_DI_REG				0x00
#घोषणा APCI1564_DI_INT_MODE1_REG		0x04
#घोषणा APCI1564_DI_INT_MODE2_REG		0x08
#घोषणा APCI1564_DI_INT_MODE_MASK		0x000ffff0 /* chans [19:4] */
#घोषणा APCI1564_DI_INT_STATUS_REG		0x0c
#घोषणा APCI1564_DI_IRQ_REG			0x10
#घोषणा APCI1564_DI_IRQ_ENA			BIT(2)
#घोषणा APCI1564_DI_IRQ_MODE			BIT(1)	/* 1=AND, 0=OR */
#घोषणा APCI1564_DO_REG				0x14
#घोषणा APCI1564_DO_INT_CTRL_REG		0x18
#घोषणा APCI1564_DO_INT_CTRL_CC_INT_ENA		BIT(1)
#घोषणा APCI1564_DO_INT_CTRL_VCC_INT_ENA	BIT(0)
#घोषणा APCI1564_DO_INT_STATUS_REG		0x1c
#घोषणा APCI1564_DO_INT_STATUS_CC		BIT(1)
#घोषणा APCI1564_DO_INT_STATUS_VCC		BIT(0)
#घोषणा APCI1564_DO_IRQ_REG			0x20
#घोषणा APCI1564_DO_IRQ_INTR			BIT(0)
#घोषणा APCI1564_WDOG_IOBASE			0x24

/*
 * devpriv->समयr Register Map (see addi_tcw.h क्रम रेजिस्टर/bit defines)
 *   PLD Revision 1.0 - PCI BAR 0 + 0x04
 *   PLD Revision 2.x - PCI BAR 0 + 0x48
 */

/*
 * devpriv->counters Register Map (see addi_tcw.h क्रम रेजिस्टर/bit defines)
 *   PLD Revision 2.x - PCI BAR 1 + 0x00
 */
#घोषणा APCI1564_COUNTER(x)			((x) * 0x20)

/*
 * The dev->पढ़ो_subdev is used to वापस the पूर्णांकerrupt events aदीर्घ with
 * the state of the पूर्णांकerrupt capable inमाला_दो.
 */
#घोषणा APCI1564_EVENT_COS			BIT(31)
#घोषणा APCI1564_EVENT_TIMER			BIT(30)
#घोषणा APCI1564_EVENT_COUNTER(x)		BIT(27 + (x)) /* counter 0-2 */
#घोषणा APCI1564_EVENT_MASK			0xfff0000f /* all but [19:4] */

काष्ठा apci1564_निजी अणु
	अचिन्हित दीर्घ eeprom;	/* base address of EEPROM रेजिस्टर */
	अचिन्हित दीर्घ समयr;	/* base address of 12-bit समयr */
	अचिन्हित दीर्घ counters;	/* base address of 32-bit counters */
	अचिन्हित पूर्णांक mode1;	/* rising-edge/high level channels */
	अचिन्हित पूर्णांक mode2;	/* falling-edge/low level channels */
	अचिन्हित पूर्णांक ctrl;	/* पूर्णांकerrupt mode OR (edge) . AND (level) */
पूर्ण;

अटल पूर्णांक apci1564_reset(काष्ठा comedi_device *dev)
अणु
	काष्ठा apci1564_निजी *devpriv = dev->निजी;

	/* Disable the input पूर्णांकerrupts and reset status रेजिस्टर */
	outl(0x0, dev->iobase + APCI1564_DI_IRQ_REG);
	inl(dev->iobase + APCI1564_DI_INT_STATUS_REG);
	outl(0x0, dev->iobase + APCI1564_DI_INT_MODE1_REG);
	outl(0x0, dev->iobase + APCI1564_DI_INT_MODE2_REG);

	/* Reset the output channels and disable पूर्णांकerrupts */
	outl(0x0, dev->iobase + APCI1564_DO_REG);
	outl(0x0, dev->iobase + APCI1564_DO_INT_CTRL_REG);

	/* Reset the watchकरोg रेजिस्टरs */
	addi_watchकरोg_reset(dev->iobase + APCI1564_WDOG_IOBASE);

	/* Reset the समयr रेजिस्टरs */
	outl(0x0, devpriv->समयr + ADDI_TCW_CTRL_REG);
	outl(0x0, devpriv->समयr + ADDI_TCW_RELOAD_REG);

	अगर (devpriv->counters) अणु
		अचिन्हित दीर्घ iobase = devpriv->counters + ADDI_TCW_CTRL_REG;

		/* Reset the counter रेजिस्टरs */
		outl(0x0, iobase + APCI1564_COUNTER(0));
		outl(0x0, iobase + APCI1564_COUNTER(1));
		outl(0x0, iobase + APCI1564_COUNTER(2));
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t apci1564_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा apci1564_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	अचिन्हित पूर्णांक status;
	अचिन्हित पूर्णांक ctrl;
	अचिन्हित पूर्णांक chan;

	s->state &= ~APCI1564_EVENT_MASK;

	status = inl(dev->iobase + APCI1564_DI_IRQ_REG);
	अगर (status & APCI1564_DI_IRQ_ENA) अणु
		/* get the COS पूर्णांकerrupt state and set the event flag */
		s->state = inl(dev->iobase + APCI1564_DI_INT_STATUS_REG);
		s->state &= APCI1564_DI_INT_MODE_MASK;
		s->state |= APCI1564_EVENT_COS;

		/* clear the पूर्णांकerrupt */
		outl(status & ~APCI1564_DI_IRQ_ENA,
		     dev->iobase + APCI1564_DI_IRQ_REG);
		outl(status, dev->iobase + APCI1564_DI_IRQ_REG);
	पूर्ण

	status = inl(devpriv->समयr + ADDI_TCW_IRQ_REG);
	अगर (status & ADDI_TCW_IRQ) अणु
		s->state |= APCI1564_EVENT_TIMER;

		/* clear the पूर्णांकerrupt */
		ctrl = inl(devpriv->समयr + ADDI_TCW_CTRL_REG);
		outl(0x0, devpriv->समयr + ADDI_TCW_CTRL_REG);
		outl(ctrl, devpriv->समयr + ADDI_TCW_CTRL_REG);
	पूर्ण

	अगर (devpriv->counters) अणु
		क्रम (chan = 0; chan < 3; chan++) अणु
			अचिन्हित दीर्घ iobase;

			iobase = devpriv->counters + APCI1564_COUNTER(chan);

			status = inl(iobase + ADDI_TCW_IRQ_REG);
			अगर (status & ADDI_TCW_IRQ) अणु
				s->state |= APCI1564_EVENT_COUNTER(chan);

				/* clear the पूर्णांकerrupt */
				ctrl = inl(iobase + ADDI_TCW_CTRL_REG);
				outl(0x0, iobase + ADDI_TCW_CTRL_REG);
				outl(ctrl, iobase + ADDI_TCW_CTRL_REG);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (s->state & APCI1564_EVENT_MASK) अणु
		comedi_buf_ग_लिखो_samples(s, &s->state, 1);
		comedi_handle_events(dev, s);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक apci1564_di_insn_bits(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	data[1] = inl(dev->iobase + APCI1564_DI_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci1564_करो_insn_bits(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	s->state = inl(dev->iobase + APCI1564_DO_REG);

	अगर (comedi_dio_update_state(s, data))
		outl(s->state, dev->iobase + APCI1564_DO_REG);

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci1564_diag_insn_bits(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_insn *insn,
				   अचिन्हित पूर्णांक *data)
अणु
	data[1] = inl(dev->iobase + APCI1564_DO_INT_STATUS_REG) & 3;

	वापस insn->n;
पूर्ण

/*
 * Change-Of-State (COS) पूर्णांकerrupt configuration
 *
 * Channels 4 to 19 are पूर्णांकerruptible. These channels can be configured
 * to generate पूर्णांकerrupts based on AND/OR logic क्रम the desired channels.
 *
 *	OR logic
 *		- reacts to rising or falling edges
 *		- पूर्णांकerrupt is generated when any enabled channel
 *		  meet the desired पूर्णांकerrupt condition
 *
 *	AND logic
 *		- reacts to changes in level of the selected inमाला_दो
 *		- पूर्णांकerrupt is generated when all enabled channels
 *		  meet the desired पूर्णांकerrupt condition
 *		- after an पूर्णांकerrupt, a change in level must occur on
 *		  the selected inमाला_दो to release the IRQ logic
 *
 * The COS पूर्णांकerrupt must be configured beक्रमe it can be enabled.
 *
 *	data[0] : INSN_CONFIG_DIGITAL_TRIG
 *	data[1] : trigger number (= 0)
 *	data[2] : configuration operation:
 *	          COMEDI_DIGITAL_TRIG_DISABLE = no पूर्णांकerrupts
 *	          COMEDI_DIGITAL_TRIG_ENABLE_EDGES = OR (edge) पूर्णांकerrupts
 *	          COMEDI_DIGITAL_TRIG_ENABLE_LEVELS = AND (level) पूर्णांकerrupts
 *	data[3] : left-shअगरt क्रम data[4] and data[5]
 *	data[4] : rising-edge/high level channels
 *	data[5] : falling-edge/low level channels
 */
अटल पूर्णांक apci1564_cos_insn_config(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s,
				    काष्ठा comedi_insn *insn,
				    अचिन्हित पूर्णांक *data)
अणु
	काष्ठा apci1564_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक shअगरt, oldmask, himask, lomask;

	चयन (data[0]) अणु
	हाल INSN_CONFIG_DIGITAL_TRIG:
		अगर (data[1] != 0)
			वापस -EINVAL;
		shअगरt = data[3];
		अगर (shअगरt < 32) अणु
			oldmask = (1U << shअगरt) - 1;
			himask = data[4] << shअगरt;
			lomask = data[5] << shअगरt;
		पूर्ण अन्यथा अणु
			oldmask = 0xffffffffu;
			himask = 0;
			lomask = 0;
		पूर्ण
		चयन (data[2]) अणु
		हाल COMEDI_DIGITAL_TRIG_DISABLE:
			devpriv->ctrl = 0;
			devpriv->mode1 = 0;
			devpriv->mode2 = 0;
			outl(0x0, dev->iobase + APCI1564_DI_IRQ_REG);
			inl(dev->iobase + APCI1564_DI_INT_STATUS_REG);
			outl(0x0, dev->iobase + APCI1564_DI_INT_MODE1_REG);
			outl(0x0, dev->iobase + APCI1564_DI_INT_MODE2_REG);
			अवरोध;
		हाल COMEDI_DIGITAL_TRIG_ENABLE_EDGES:
			अगर (devpriv->ctrl != APCI1564_DI_IRQ_ENA) अणु
				/* चयनing to 'OR' mode */
				devpriv->ctrl = APCI1564_DI_IRQ_ENA;
				/* wipe old channels */
				devpriv->mode1 = 0;
				devpriv->mode2 = 0;
			पूर्ण अन्यथा अणु
				/* preserve unspecअगरied channels */
				devpriv->mode1 &= oldmask;
				devpriv->mode2 &= oldmask;
			पूर्ण
			/* configure specअगरied channels */
			devpriv->mode1 |= himask;
			devpriv->mode2 |= lomask;
			अवरोध;
		हाल COMEDI_DIGITAL_TRIG_ENABLE_LEVELS:
			अगर (devpriv->ctrl != (APCI1564_DI_IRQ_ENA |
					      APCI1564_DI_IRQ_MODE)) अणु
				/* चयनing to 'AND' mode */
				devpriv->ctrl = APCI1564_DI_IRQ_ENA |
						APCI1564_DI_IRQ_MODE;
				/* wipe old channels */
				devpriv->mode1 = 0;
				devpriv->mode2 = 0;
			पूर्ण अन्यथा अणु
				/* preserve unspecअगरied channels */
				devpriv->mode1 &= oldmask;
				devpriv->mode2 &= oldmask;
			पूर्ण
			/* configure specअगरied channels */
			devpriv->mode1 |= himask;
			devpriv->mode2 |= lomask;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		/* ensure the mode bits are in-range क्रम channels [19:4] */
		devpriv->mode1 &= APCI1564_DI_INT_MODE_MASK;
		devpriv->mode2 &= APCI1564_DI_INT_MODE_MASK;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस insn->n;
पूर्ण

अटल पूर्णांक apci1564_cos_insn_bits(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	data[1] = s->state;

	वापस 0;
पूर्ण

अटल पूर्णांक apci1564_cos_cmdtest(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_cmd *cmd)
अणु
	पूर्णांक err = 0;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_FOLLOW);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */
	/* Step 2b : and mutually compatible */

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->convert_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);
	err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* Step 4: fix up any arguments */

	/* Step 5: check channel list अगर it exists */

	वापस 0;
पूर्ण

/*
 * Change-Of-State (COS) 'do_cmd' operation
 *
 * Enable the COS पूर्णांकerrupt as configured by apci1564_cos_insn_config().
 */
अटल पूर्णांक apci1564_cos_cmd(काष्ठा comedi_device *dev,
			    काष्ठा comedi_subdevice *s)
अणु
	काष्ठा apci1564_निजी *devpriv = dev->निजी;

	अगर (!devpriv->ctrl && !(devpriv->mode1 || devpriv->mode2)) अणु
		dev_warn(dev->class_dev,
			 "Interrupts disabled due to mode configuration!\n");
		वापस -EINVAL;
	पूर्ण

	outl(devpriv->mode1, dev->iobase + APCI1564_DI_INT_MODE1_REG);
	outl(devpriv->mode2, dev->iobase + APCI1564_DI_INT_MODE2_REG);
	outl(devpriv->ctrl, dev->iobase + APCI1564_DI_IRQ_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक apci1564_cos_cancel(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s)
अणु
	outl(0x0, dev->iobase + APCI1564_DI_IRQ_REG);
	inl(dev->iobase + APCI1564_DI_INT_STATUS_REG);
	outl(0x0, dev->iobase + APCI1564_DI_INT_MODE1_REG);
	outl(0x0, dev->iobase + APCI1564_DI_INT_MODE2_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक apci1564_समयr_insn_config(काष्ठा comedi_device *dev,
				      काष्ठा comedi_subdevice *s,
				      काष्ठा comedi_insn *insn,
				      अचिन्हित पूर्णांक *data)
अणु
	काष्ठा apci1564_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक val;

	चयन (data[0]) अणु
	हाल INSN_CONFIG_ARM:
		अगर (data[1] > s->maxdata)
			वापस -EINVAL;
		outl(data[1], devpriv->समयr + ADDI_TCW_RELOAD_REG);
		outl(ADDI_TCW_CTRL_IRQ_ENA | ADDI_TCW_CTRL_TIMER_ENA,
		     devpriv->समयr + ADDI_TCW_CTRL_REG);
		अवरोध;
	हाल INSN_CONFIG_DISARM:
		outl(0x0, devpriv->समयr + ADDI_TCW_CTRL_REG);
		अवरोध;
	हाल INSN_CONFIG_GET_COUNTER_STATUS:
		data[1] = 0;
		val = inl(devpriv->समयr + ADDI_TCW_CTRL_REG);
		अगर (val & ADDI_TCW_CTRL_IRQ_ENA)
			data[1] |= COMEDI_COUNTER_ARMED;
		अगर (val & ADDI_TCW_CTRL_TIMER_ENA)
			data[1] |= COMEDI_COUNTER_COUNTING;
		val = inl(devpriv->समयr + ADDI_TCW_STATUS_REG);
		अगर (val & ADDI_TCW_STATUS_OVERFLOW)
			data[1] |= COMEDI_COUNTER_TERMINAL_COUNT;
		data[2] = COMEDI_COUNTER_ARMED | COMEDI_COUNTER_COUNTING |
			  COMEDI_COUNTER_TERMINAL_COUNT;
		अवरोध;
	हाल INSN_CONFIG_SET_CLOCK_SRC:
		अगर (data[2] > s->maxdata)
			वापस -EINVAL;
		outl(data[1], devpriv->समयr + ADDI_TCW_TIMEBASE_REG);
		outl(data[2], devpriv->समयr + ADDI_TCW_RELOAD_REG);
		अवरोध;
	हाल INSN_CONFIG_GET_CLOCK_SRC:
		data[1] = inl(devpriv->समयr + ADDI_TCW_TIMEBASE_REG);
		data[2] = inl(devpriv->समयr + ADDI_TCW_RELOAD_REG);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci1564_समयr_insn_ग_लिखो(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s,
				     काष्ठा comedi_insn *insn,
				     अचिन्हित पूर्णांक *data)
अणु
	काष्ठा apci1564_निजी *devpriv = dev->निजी;

	/* just ग_लिखो the last to the reload रेजिस्टर */
	अगर (insn->n) अणु
		अचिन्हित पूर्णांक val = data[insn->n - 1];

		outl(val, devpriv->समयr + ADDI_TCW_RELOAD_REG);
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci1564_समयr_insn_पढ़ो(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s,
				    काष्ठा comedi_insn *insn,
				    अचिन्हित पूर्णांक *data)
अणु
	काष्ठा apci1564_निजी *devpriv = dev->निजी;
	पूर्णांक i;

	/* वापस the actual value of the समयr */
	क्रम (i = 0; i < insn->n; i++)
		data[i] = inl(devpriv->समयr + ADDI_TCW_VAL_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci1564_counter_insn_config(काष्ठा comedi_device *dev,
					काष्ठा comedi_subdevice *s,
					काष्ठा comedi_insn *insn,
					अचिन्हित पूर्णांक *data)
अणु
	काष्ठा apci1564_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित दीर्घ iobase = devpriv->counters + APCI1564_COUNTER(chan);
	अचिन्हित पूर्णांक val;

	चयन (data[0]) अणु
	हाल INSN_CONFIG_ARM:
		val = inl(iobase + ADDI_TCW_CTRL_REG);
		val |= ADDI_TCW_CTRL_IRQ_ENA | ADDI_TCW_CTRL_CNTR_ENA;
		outl(data[1], iobase + ADDI_TCW_RELOAD_REG);
		outl(val, iobase + ADDI_TCW_CTRL_REG);
		अवरोध;
	हाल INSN_CONFIG_DISARM:
		val = inl(iobase + ADDI_TCW_CTRL_REG);
		val &= ~(ADDI_TCW_CTRL_IRQ_ENA | ADDI_TCW_CTRL_CNTR_ENA);
		outl(val, iobase + ADDI_TCW_CTRL_REG);
		अवरोध;
	हाल INSN_CONFIG_SET_COUNTER_MODE:
		/*
		 * FIXME: The counter operation is not described in the
		 * datasheet. For now just ग_लिखो the raw data[1] value to
		 * the control रेजिस्टर.
		 */
		outl(data[1], iobase + ADDI_TCW_CTRL_REG);
		अवरोध;
	हाल INSN_CONFIG_GET_COUNTER_STATUS:
		data[1] = 0;
		val = inl(iobase + ADDI_TCW_CTRL_REG);
		अगर (val & ADDI_TCW_CTRL_IRQ_ENA)
			data[1] |= COMEDI_COUNTER_ARMED;
		अगर (val & ADDI_TCW_CTRL_CNTR_ENA)
			data[1] |= COMEDI_COUNTER_COUNTING;
		val = inl(iobase + ADDI_TCW_STATUS_REG);
		अगर (val & ADDI_TCW_STATUS_OVERFLOW)
			data[1] |= COMEDI_COUNTER_TERMINAL_COUNT;
		data[2] = COMEDI_COUNTER_ARMED | COMEDI_COUNTER_COUNTING |
			  COMEDI_COUNTER_TERMINAL_COUNT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci1564_counter_insn_ग_लिखो(काष्ठा comedi_device *dev,
				       काष्ठा comedi_subdevice *s,
				       काष्ठा comedi_insn *insn,
				       अचिन्हित पूर्णांक *data)
अणु
	काष्ठा apci1564_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित दीर्घ iobase = devpriv->counters + APCI1564_COUNTER(chan);

	/* just ग_लिखो the last to the reload रेजिस्टर */
	अगर (insn->n) अणु
		अचिन्हित पूर्णांक val = data[insn->n - 1];

		outl(val, iobase + ADDI_TCW_RELOAD_REG);
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci1564_counter_insn_पढ़ो(काष्ठा comedi_device *dev,
				      काष्ठा comedi_subdevice *s,
				      काष्ठा comedi_insn *insn,
				      अचिन्हित पूर्णांक *data)
अणु
	काष्ठा apci1564_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित दीर्घ iobase = devpriv->counters + APCI1564_COUNTER(chan);
	पूर्णांक i;

	/* वापस the actual value of the counter */
	क्रम (i = 0; i < insn->n; i++)
		data[i] = inl(iobase + ADDI_TCW_VAL_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci1564_स्वतः_attach(काष्ठा comedi_device *dev,
				अचिन्हित दीर्घ context_unused)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	काष्ठा apci1564_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;

	/* पढ़ो the EEPROM रेजिस्टर and check the I/O map revision */
	devpriv->eeprom = pci_resource_start(pcidev, 0);
	val = inl(devpriv->eeprom + APCI1564_EEPROM_REG);
	अगर (APCI1564_EEPROM_TO_REV(val) == 0) अणु
		/* PLD Revision 1.0 I/O Mapping */
		dev->iobase = pci_resource_start(pcidev, 1) +
			      APCI1564_REV1_MAIN_IOBASE;
		devpriv->समयr = devpriv->eeprom + APCI1564_REV1_TIMER_IOBASE;
	पूर्ण अन्यथा अणु
		/* PLD Revision 2.x I/O Mapping */
		dev->iobase = devpriv->eeprom + APCI1564_REV2_MAIN_IOBASE;
		devpriv->समयr = devpriv->eeprom + APCI1564_REV2_TIMER_IOBASE;
		devpriv->counters = pci_resource_start(pcidev, 1);
	पूर्ण

	apci1564_reset(dev);

	अगर (pcidev->irq > 0) अणु
		ret = request_irq(pcidev->irq, apci1564_पूर्णांकerrupt, IRQF_SHARED,
				  dev->board_name, dev);
		अगर (ret == 0)
			dev->irq = pcidev->irq;
	पूर्ण

	ret = comedi_alloc_subdevices(dev, 7);
	अगर (ret)
		वापस ret;

	/*  Allocate and Initialise DI Subdevice Structures */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 32;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= apci1564_di_insn_bits;

	/*  Allocate and Initialise DO Subdevice Structures */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 32;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= apci1564_करो_insn_bits;

	/* Change-Of-State (COS) पूर्णांकerrupt subdevice */
	s = &dev->subdevices[2];
	अगर (dev->irq) अणु
		dev->पढ़ो_subdev = s;
		s->type		= COMEDI_SUBD_DI;
		s->subdev_flags	= SDF_READABLE | SDF_CMD_READ | SDF_LSAMPL;
		s->n_chan	= 1;
		s->maxdata	= 1;
		s->range_table	= &range_digital;
		s->len_chanlist	= 1;
		s->insn_config	= apci1564_cos_insn_config;
		s->insn_bits	= apci1564_cos_insn_bits;
		s->करो_cmdtest	= apci1564_cos_cmdtest;
		s->करो_cmd	= apci1564_cos_cmd;
		s->cancel	= apci1564_cos_cancel;
	पूर्ण अन्यथा अणु
		s->type		= COMEDI_SUBD_UNUSED;
	पूर्ण

	/* Timer subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_TIMER;
	s->subdev_flags	= SDF_WRITABLE | SDF_READABLE;
	s->n_chan	= 1;
	s->maxdata	= 0x0fff;
	s->range_table	= &range_digital;
	s->insn_config	= apci1564_समयr_insn_config;
	s->insn_ग_लिखो	= apci1564_समयr_insn_ग_लिखो;
	s->insn_पढ़ो	= apci1564_समयr_insn_पढ़ो;

	/* Counter subdevice */
	s = &dev->subdevices[4];
	अगर (devpriv->counters) अणु
		s->type		= COMEDI_SUBD_COUNTER;
		s->subdev_flags	= SDF_WRITABLE | SDF_READABLE | SDF_LSAMPL;
		s->n_chan	= 3;
		s->maxdata	= 0xffffffff;
		s->range_table	= &range_digital;
		s->insn_config	= apci1564_counter_insn_config;
		s->insn_ग_लिखो	= apci1564_counter_insn_ग_लिखो;
		s->insn_पढ़ो	= apci1564_counter_insn_पढ़ो;
	पूर्ण अन्यथा अणु
		s->type		= COMEDI_SUBD_UNUSED;
	पूर्ण

	/* Initialize the watchकरोg subdevice */
	s = &dev->subdevices[5];
	ret = addi_watchकरोg_init(s, dev->iobase + APCI1564_WDOG_IOBASE);
	अगर (ret)
		वापस ret;

	/* Initialize the diagnostic status subdevice */
	s = &dev->subdevices[6];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 2;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= apci1564_diag_insn_bits;

	वापस 0;
पूर्ण

अटल व्योम apci1564_detach(काष्ठा comedi_device *dev)
अणु
	अगर (dev->iobase)
		apci1564_reset(dev);
	comedi_pci_detach(dev);
पूर्ण

अटल काष्ठा comedi_driver apci1564_driver = अणु
	.driver_name	= "addi_apci_1564",
	.module		= THIS_MODULE,
	.स्वतः_attach	= apci1564_स्वतः_attach,
	.detach		= apci1564_detach,
पूर्ण;

अटल पूर्णांक apci1564_pci_probe(काष्ठा pci_dev *dev,
			      स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &apci1564_driver, id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id apci1564_pci_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_ADDIDATA, 0x1006) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, apci1564_pci_table);

अटल काष्ठा pci_driver apci1564_pci_driver = अणु
	.name		= "addi_apci_1564",
	.id_table	= apci1564_pci_table,
	.probe		= apci1564_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(apci1564_driver, apci1564_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("ADDI-DATA APCI-1564, 32 channel DI / 32 channel DO boards");
MODULE_LICENSE("GPL");
