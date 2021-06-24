<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * COMEDI driver क्रम the Advantech PCI-1760
 * Copyright (C) 2015 H Hartley Sweeten <hsweeten@visionengravers.com>
 *
 * Based on the pci1760 support in the adv_pci_dio driver written by:
 *	Michal Dobes <करोbes@tesnet.cz>
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: adv_pci1760
 * Description: Advantech PCI-1760 Relay & Isolated Digital Input Card
 * Devices: [Advantech] PCI-1760 (adv_pci1760)
 * Author: H Hartley Sweeten <hsweeten@visionengravers.com>
 * Updated: Fri, 13 Nov 2015 12:34:00 -0700
 * Status: untested
 *
 * Configuration Options: not applicable, uses PCI स्वतः config
 */

#समावेश <linux/module.h>

#समावेश "../comedi_pci.h"

/*
 * PCI-1760 Register Map
 *
 * Outgoing Mailbox Bytes
 * OMB3: Not used (must be 0)
 * OMB2: The command code to the PCI-1760
 * OMB1: The hi byte of the parameter क्रम the command in OMB2
 * OMB0: The lo byte of the parameter क्रम the command in OMB2
 *
 * Incoming Mailbox Bytes
 * IMB3: The Isolated Digital Input status (updated every 100us)
 * IMB2: The current command (matches OMB2 when command is successful)
 * IMB1: The hi byte of the feedback data क्रम the command in OMB2
 * IMB0: The lo byte of the feedback data क्रम the command in OMB2
 *
 * Interrupt Control/Status
 * INTCSR3: Not used (must be 0)
 * INTCSR2: The पूर्णांकerrupt status (पढ़ो only)
 * INTCSR1: Interrupt enable/disable
 * INTCSR0: Not used (must be 0)
 */
#घोषणा PCI1760_OMB_REG(x)		(0x0c + (x))
#घोषणा PCI1760_IMB_REG(x)		(0x1c + (x))
#घोषणा PCI1760_INTCSR_REG(x)		(0x38 + (x))
#घोषणा PCI1760_INTCSR1_IRQ_ENA		BIT(5)
#घोषणा PCI1760_INTCSR2_OMB_IRQ		BIT(0)
#घोषणा PCI1760_INTCSR2_IMB_IRQ		BIT(1)
#घोषणा PCI1760_INTCSR2_IRQ_STATUS	BIT(6)
#घोषणा PCI1760_INTCSR2_IRQ_ASSERTED	BIT(7)

/* PCI-1760 command codes */
#घोषणा PCI1760_CMD_CLR_IMB2		0x00	/* Clears IMB2 */
#घोषणा PCI1760_CMD_SET_DO		0x01	/* Set output state */
#घोषणा PCI1760_CMD_GET_DO		0x02	/* Read output status */
#घोषणा PCI1760_CMD_GET_STATUS		0x03	/* Read current status */
#घोषणा PCI1760_CMD_GET_FW_VER		0x0e	/* Read firmware version */
#घोषणा PCI1760_CMD_GET_HW_VER		0x0f	/* Read hardware version */
#घोषणा PCI1760_CMD_SET_PWM_HI(x)	(0x10 + (x) * 2) /* Set "hi" period */
#घोषणा PCI1760_CMD_SET_PWM_LO(x)	(0x11 + (x) * 2) /* Set "lo" period */
#घोषणा PCI1760_CMD_SET_PWM_CNT(x)	(0x14 + (x)) /* Set burst count */
#घोषणा PCI1760_CMD_ENA_PWM		0x1f	/* Enable PWM outमाला_दो */
#घोषणा PCI1760_CMD_ENA_FILT		0x20	/* Enable input filter */
#घोषणा PCI1760_CMD_ENA_PAT_MATCH	0x21	/* Enable input pattern match */
#घोषणा PCI1760_CMD_SET_PAT_MATCH	0x22	/* Set input pattern match */
#घोषणा PCI1760_CMD_ENA_RISE_EDGE	0x23	/* Enable input rising edge */
#घोषणा PCI1760_CMD_ENA_FALL_EDGE	0x24	/* Enable input falling edge */
#घोषणा PCI1760_CMD_ENA_CNT		0x28	/* Enable counter */
#घोषणा PCI1760_CMD_RST_CNT		0x29	/* Reset counter */
#घोषणा PCI1760_CMD_ENA_CNT_OFLOW	0x2a	/* Enable counter overflow */
#घोषणा PCI1760_CMD_ENA_CNT_MATCH	0x2b	/* Enable counter match */
#घोषणा PCI1760_CMD_SET_CNT_EDGE	0x2c	/* Set counter edge */
#घोषणा PCI1760_CMD_GET_CNT		0x2f	/* Reads counter value */
#घोषणा PCI1760_CMD_SET_HI_SAMP(x)	(0x30 + (x)) /* Set "hi" sample समय */
#घोषणा PCI1760_CMD_SET_LO_SAMP(x)	(0x38 + (x)) /* Set "lo" sample समय */
#घोषणा PCI1760_CMD_SET_CNT(x)		(0x40 + (x)) /* Set counter reset val */
#घोषणा PCI1760_CMD_SET_CNT_MATCH(x)	(0x48 + (x)) /* Set counter match val */
#घोषणा PCI1760_CMD_GET_INT_FLAGS	0x60	/* Read पूर्णांकerrupt flags */
#घोषणा PCI1760_CMD_GET_INT_FLAGS_MATCH	BIT(0)
#घोषणा PCI1760_CMD_GET_INT_FLAGS_COS	BIT(1)
#घोषणा PCI1760_CMD_GET_INT_FLAGS_OFLOW	BIT(2)
#घोषणा PCI1760_CMD_GET_OS		0x61	/* Read edge change flags */
#घोषणा PCI1760_CMD_GET_CNT_STATUS	0x62	/* Read counter oflow/match */

#घोषणा PCI1760_CMD_TIMEOUT		250	/* 250 usec समयout */
#घोषणा PCI1760_CMD_RETRIES		3	/* limit number of retries */

#घोषणा PCI1760_PWM_TIMEBASE		100000	/* 1 unit = 100 usec */

अटल पूर्णांक pci1760_send_cmd(काष्ठा comedi_device *dev,
			    अचिन्हित अक्षर cmd, अचिन्हित लघु val)
अणु
	अचिन्हित दीर्घ समयout;

	/* send the command and parameter */
	outb(val & 0xff, dev->iobase + PCI1760_OMB_REG(0));
	outb((val >> 8) & 0xff, dev->iobase + PCI1760_OMB_REG(1));
	outb(cmd, dev->iobase + PCI1760_OMB_REG(2));
	outb(0, dev->iobase + PCI1760_OMB_REG(3));

	/* datasheet says to allow up to 250 usec क्रम the command to complete */
	समयout = jअगरfies + usecs_to_jअगरfies(PCI1760_CMD_TIMEOUT);
	करो अणु
		अगर (inb(dev->iobase + PCI1760_IMB_REG(2)) == cmd) अणु
			/* command success; वापस the feedback data */
			वापस inb(dev->iobase + PCI1760_IMB_REG(0)) |
			       (inb(dev->iobase + PCI1760_IMB_REG(1)) << 8);
		पूर्ण
		cpu_relax();
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक pci1760_cmd(काष्ठा comedi_device *dev,
		       अचिन्हित अक्षर cmd, अचिन्हित लघु val)
अणु
	पूर्णांक repeats;
	पूर्णांक ret;

	/* send PCI1760_CMD_CLR_IMB2 between identical commands */
	अगर (inb(dev->iobase + PCI1760_IMB_REG(2)) == cmd) अणु
		ret = pci1760_send_cmd(dev, PCI1760_CMD_CLR_IMB2, 0);
		अगर (ret < 0) अणु
			/* समयout? try it once more */
			ret = pci1760_send_cmd(dev, PCI1760_CMD_CLR_IMB2, 0);
			अगर (ret < 0)
				वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	/* datasheet says to keep retrying the command */
	क्रम (repeats = 0; repeats < PCI1760_CMD_RETRIES; repeats++) अणु
		ret = pci1760_send_cmd(dev, cmd, val);
		अगर (ret >= 0)
			वापस ret;
	पूर्ण

	/* command failed! */
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक pci1760_di_insn_bits(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	data[1] = inb(dev->iobase + PCI1760_IMB_REG(3));

	वापस insn->n;
पूर्ण

अटल पूर्णांक pci1760_करो_insn_bits(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक ret;

	अगर (comedi_dio_update_state(s, data)) अणु
		ret = pci1760_cmd(dev, PCI1760_CMD_SET_DO, s->state);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल पूर्णांक pci1760_pwm_ns_to_भाग(अचिन्हित पूर्णांक flags, अचिन्हित पूर्णांक ns)
अणु
	अचिन्हित पूर्णांक भागisor;

	चयन (flags) अणु
	हाल CMDF_ROUND_NEAREST:
		भागisor = DIV_ROUND_CLOSEST(ns, PCI1760_PWM_TIMEBASE);
		अवरोध;
	हाल CMDF_ROUND_UP:
		भागisor = DIV_ROUND_UP(ns, PCI1760_PWM_TIMEBASE);
		अवरोध;
	हाल CMDF_ROUND_DOWN:
		भागisor = ns / PCI1760_PWM_TIMEBASE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (भागisor < 1)
		भागisor = 1;
	अगर (भागisor > 0xffff)
		भागisor = 0xffff;

	वापस भागisor;
पूर्ण

अटल पूर्णांक pci1760_pwm_enable(काष्ठा comedi_device *dev,
			      अचिन्हित पूर्णांक chan, bool enable)
अणु
	पूर्णांक ret;

	ret = pci1760_cmd(dev, PCI1760_CMD_GET_STATUS, PCI1760_CMD_ENA_PWM);
	अगर (ret < 0)
		वापस ret;

	अगर (enable)
		ret |= BIT(chan);
	अन्यथा
		ret &= ~BIT(chan);

	वापस pci1760_cmd(dev, PCI1760_CMD_ENA_PWM, ret);
पूर्ण

अटल पूर्णांक pci1760_pwm_insn_config(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_insn *insn,
				   अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	पूर्णांक hi_भाग;
	पूर्णांक lo_भाग;
	पूर्णांक ret;

	चयन (data[0]) अणु
	हाल INSN_CONFIG_ARM:
		ret = pci1760_pwm_enable(dev, chan, false);
		अगर (ret < 0)
			वापस ret;

		अगर (data[1] > 0xffff)
			वापस -EINVAL;
		ret = pci1760_cmd(dev, PCI1760_CMD_SET_PWM_CNT(chan), data[1]);
		अगर (ret < 0)
			वापस ret;

		ret = pci1760_pwm_enable(dev, chan, true);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	हाल INSN_CONFIG_DISARM:
		ret = pci1760_pwm_enable(dev, chan, false);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	हाल INSN_CONFIG_PWM_OUTPUT:
		ret = pci1760_pwm_enable(dev, chan, false);
		अगर (ret < 0)
			वापस ret;

		hi_भाग = pci1760_pwm_ns_to_भाग(data[1], data[2]);
		lo_भाग = pci1760_pwm_ns_to_भाग(data[3], data[4]);
		अगर (hi_भाग < 0 || lo_भाग < 0)
			वापस -EINVAL;
		अगर ((hi_भाग * PCI1760_PWM_TIMEBASE) != data[2] ||
		    (lo_भाग * PCI1760_PWM_TIMEBASE) != data[4]) अणु
			data[2] = hi_भाग * PCI1760_PWM_TIMEBASE;
			data[4] = lo_भाग * PCI1760_PWM_TIMEBASE;
			वापस -EAGAIN;
		पूर्ण
		ret = pci1760_cmd(dev, PCI1760_CMD_SET_PWM_HI(chan), hi_भाग);
		अगर (ret < 0)
			वापस ret;
		ret = pci1760_cmd(dev, PCI1760_CMD_SET_PWM_LO(chan), lo_भाग);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	हाल INSN_CONFIG_GET_PWM_OUTPUT:
		hi_भाग = pci1760_cmd(dev, PCI1760_CMD_GET_STATUS,
				     PCI1760_CMD_SET_PWM_HI(chan));
		lo_भाग = pci1760_cmd(dev, PCI1760_CMD_GET_STATUS,
				     PCI1760_CMD_SET_PWM_LO(chan));
		अगर (hi_भाग < 0 || lo_भाग < 0)
			वापस -ETIMEDOUT;

		data[1] = hi_भाग * PCI1760_PWM_TIMEBASE;
		data[2] = lo_भाग * PCI1760_PWM_TIMEBASE;
		अवरोध;
	हाल INSN_CONFIG_GET_PWM_STATUS:
		ret = pci1760_cmd(dev, PCI1760_CMD_GET_STATUS,
				  PCI1760_CMD_ENA_PWM);
		अगर (ret < 0)
			वापस ret;

		data[1] = (ret & BIT(chan)) ? 1 : 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल व्योम pci1760_reset(काष्ठा comedi_device *dev)
अणु
	पूर्णांक i;

	/* disable पूर्णांकerrupts (पूर्णांकcsr2 is पढ़ो-only) */
	outb(0, dev->iobase + PCI1760_INTCSR_REG(0));
	outb(0, dev->iobase + PCI1760_INTCSR_REG(1));
	outb(0, dev->iobase + PCI1760_INTCSR_REG(3));

	/* disable counters */
	pci1760_cmd(dev, PCI1760_CMD_ENA_CNT, 0);

	/* disable overflow पूर्णांकerrupts */
	pci1760_cmd(dev, PCI1760_CMD_ENA_CNT_OFLOW, 0);

	/* disable match */
	pci1760_cmd(dev, PCI1760_CMD_ENA_CNT_MATCH, 0);

	/* set match and counter reset values */
	क्रम (i = 0; i < 8; i++) अणु
		pci1760_cmd(dev, PCI1760_CMD_SET_CNT_MATCH(i), 0x8000);
		pci1760_cmd(dev, PCI1760_CMD_SET_CNT(i), 0x0000);
	पूर्ण

	/* reset counters to reset values */
	pci1760_cmd(dev, PCI1760_CMD_RST_CNT, 0xff);

	/* set counter count edges */
	pci1760_cmd(dev, PCI1760_CMD_SET_CNT_EDGE, 0);

	/* disable input filters */
	pci1760_cmd(dev, PCI1760_CMD_ENA_FILT, 0);

	/* disable pattern matching */
	pci1760_cmd(dev, PCI1760_CMD_ENA_PAT_MATCH, 0);

	/* set pattern match value */
	pci1760_cmd(dev, PCI1760_CMD_SET_PAT_MATCH, 0);
पूर्ण

अटल पूर्णांक pci1760_स्वतः_attach(काष्ठा comedi_device *dev,
			       अचिन्हित दीर्घ context)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;
	dev->iobase = pci_resource_start(pcidev, 0);

	pci1760_reset(dev);

	ret = comedi_alloc_subdevices(dev, 4);
	अगर (ret)
		वापस ret;

	/* Digital Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= pci1760_di_insn_bits;

	/* Digital Output subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= pci1760_करो_insn_bits;

	/* get the current state of the outमाला_दो */
	ret = pci1760_cmd(dev, PCI1760_CMD_GET_DO, 0);
	अगर (ret < 0)
		वापस ret;
	s->state	= ret;

	/* PWM subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_PWM;
	s->subdev_flags	= SDF_PWM_COUNTER;
	s->n_chan	= 2;
	s->insn_config	= pci1760_pwm_insn_config;

	/* Counter subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_UNUSED;

	वापस 0;
पूर्ण

अटल काष्ठा comedi_driver pci1760_driver = अणु
	.driver_name	= "adv_pci1760",
	.module		= THIS_MODULE,
	.स्वतः_attach	= pci1760_स्वतः_attach,
	.detach		= comedi_pci_detach,
पूर्ण;

अटल पूर्णांक pci1760_pci_probe(काष्ठा pci_dev *dev,
			     स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &pci1760_driver, id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id pci1760_pci_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_ADVANTECH, 0x1760) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, pci1760_pci_table);

अटल काष्ठा pci_driver pci1760_pci_driver = अणु
	.name		= "adv_pci1760",
	.id_table	= pci1760_pci_table,
	.probe		= pci1760_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(pci1760_driver, pci1760_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for Advantech PCI-1760");
MODULE_LICENSE("GPL");
