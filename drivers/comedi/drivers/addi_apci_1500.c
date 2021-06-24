<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * addi_apci_1500.c
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

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "../comedi_pci.h"
#समावेश "amcc_s5933.h"
#समावेश "z8536.h"

/*
 * PCI Bar 0 Register map (devpriv->amcc)
 * see amcc_s5933.h क्रम रेजिस्टर and bit defines
 */

/*
 * PCI Bar 1 Register map (dev->iobase)
 * see z8536.h क्रम Z8536 पूर्णांकernal रेजिस्टरs and bit defines
 */
#घोषणा APCI1500_Z8536_PORTC_REG	0x00
#घोषणा APCI1500_Z8536_PORTB_REG	0x01
#घोषणा APCI1500_Z8536_PORTA_REG	0x02
#घोषणा APCI1500_Z8536_CTRL_REG		0x03

/*
 * PCI Bar 2 Register map (devpriv->adकरोn)
 */
#घोषणा APCI1500_CLK_SEL_REG		0x00
#घोषणा APCI1500_DI_REG			0x00
#घोषणा APCI1500_DO_REG			0x02

काष्ठा apci1500_निजी अणु
	अचिन्हित दीर्घ amcc;
	अचिन्हित दीर्घ adकरोn;

	अचिन्हित पूर्णांक clk_src;

	/* Digital trigger configuration [0]=AND [1]=OR */
	अचिन्हित पूर्णांक pm[2];	/* Pattern Mask */
	अचिन्हित पूर्णांक pt[2];	/* Pattern Transition */
	अचिन्हित पूर्णांक pp[2];	/* Pattern Polarity */
पूर्ण;

अटल अचिन्हित पूर्णांक z8536_पढ़ो(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक val;

	spin_lock_irqsave(&dev->spinlock, flags);
	outb(reg, dev->iobase + APCI1500_Z8536_CTRL_REG);
	val = inb(dev->iobase + APCI1500_Z8536_CTRL_REG);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	वापस val;
पूर्ण

अटल व्योम z8536_ग_लिखो(काष्ठा comedi_device *dev,
			अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->spinlock, flags);
	outb(reg, dev->iobase + APCI1500_Z8536_CTRL_REG);
	outb(val, dev->iobase + APCI1500_Z8536_CTRL_REG);
	spin_unlock_irqrestore(&dev->spinlock, flags);
पूर्ण

अटल व्योम z8536_reset(काष्ठा comedi_device *dev)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * Even अगर the state of the Z8536 is not known, the following
	 * sequence will reset it and put it in State 0.
	 */
	spin_lock_irqsave(&dev->spinlock, flags);
	inb(dev->iobase + APCI1500_Z8536_CTRL_REG);
	outb(0, dev->iobase + APCI1500_Z8536_CTRL_REG);
	inb(dev->iobase + APCI1500_Z8536_CTRL_REG);
	outb(0, dev->iobase + APCI1500_Z8536_CTRL_REG);
	outb(1, dev->iobase + APCI1500_Z8536_CTRL_REG);
	outb(0, dev->iobase + APCI1500_Z8536_CTRL_REG);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	/* Disable all Ports and Counter/Timers */
	z8536_ग_लिखो(dev, 0x00, Z8536_CFG_CTRL_REG);

	/*
	 * Port A is connected to Ditial Input channels 0-7.
	 * Configure the port to allow पूर्णांकerrupt detection.
	 */
	z8536_ग_लिखो(dev, Z8536_PAB_MODE_PTS_BIT |
			 Z8536_PAB_MODE_SB |
			 Z8536_PAB_MODE_PMS_DISABLE,
		    Z8536_PA_MODE_REG);
	z8536_ग_लिखो(dev, 0xff, Z8536_PB_DPP_REG);
	z8536_ग_लिखो(dev, 0xff, Z8536_PA_DD_REG);

	/*
	 * Port B is connected to Ditial Input channels 8-13.
	 * Configure the port to allow पूर्णांकerrupt detection.
	 *
	 * NOTE: Bits 7 and 6 of Port B are connected to पूर्णांकernal
	 * diagnostic संकेतs and bit 7 is inverted.
	 */
	z8536_ग_लिखो(dev, Z8536_PAB_MODE_PTS_BIT |
			 Z8536_PAB_MODE_SB |
			 Z8536_PAB_MODE_PMS_DISABLE,
		    Z8536_PB_MODE_REG);
	z8536_ग_लिखो(dev, 0x7f, Z8536_PB_DPP_REG);
	z8536_ग_लिखो(dev, 0xff, Z8536_PB_DD_REG);

	/*
	 * Not sure what Port C is connected to...
	 */
	z8536_ग_लिखो(dev, 0x09, Z8536_PC_DPP_REG);
	z8536_ग_लिखो(dev, 0x0e, Z8536_PC_DD_REG);

	/*
	 * Clear and disable all पूर्णांकerrupt sources.
	 *
	 * Just in हाल, the reset of the Z8536 should have alपढ़ोy
	 * करोne this.
	 */
	z8536_ग_लिखो(dev, Z8536_CMD_CLR_IP_IUS, Z8536_PA_CMDSTAT_REG);
	z8536_ग_लिखो(dev, Z8536_CMD_CLR_IE, Z8536_PA_CMDSTAT_REG);

	z8536_ग_लिखो(dev, Z8536_CMD_CLR_IP_IUS, Z8536_PB_CMDSTAT_REG);
	z8536_ग_लिखो(dev, Z8536_CMD_CLR_IE, Z8536_PB_CMDSTAT_REG);

	z8536_ग_लिखो(dev, Z8536_CMD_CLR_IP_IUS, Z8536_CT_CMDSTAT_REG(0));
	z8536_ग_लिखो(dev, Z8536_CMD_CLR_IE, Z8536_CT_CMDSTAT_REG(0));

	z8536_ग_लिखो(dev, Z8536_CMD_CLR_IP_IUS, Z8536_CT_CMDSTAT_REG(1));
	z8536_ग_लिखो(dev, Z8536_CMD_CLR_IE, Z8536_CT_CMDSTAT_REG(1));

	z8536_ग_लिखो(dev, Z8536_CMD_CLR_IP_IUS, Z8536_CT_CMDSTAT_REG(2));
	z8536_ग_लिखो(dev, Z8536_CMD_CLR_IE, Z8536_CT_CMDSTAT_REG(2));

	/* Disable all पूर्णांकerrupts */
	z8536_ग_लिखो(dev, 0x00, Z8536_INT_CTRL_REG);
पूर्ण

अटल व्योम apci1500_port_enable(काष्ठा comedi_device *dev, bool enable)
अणु
	अचिन्हित पूर्णांक cfg;

	cfg = z8536_पढ़ो(dev, Z8536_CFG_CTRL_REG);
	अगर (enable)
		cfg |= (Z8536_CFG_CTRL_PAE | Z8536_CFG_CTRL_PBE);
	अन्यथा
		cfg &= ~(Z8536_CFG_CTRL_PAE | Z8536_CFG_CTRL_PBE);
	z8536_ग_लिखो(dev, cfg, Z8536_CFG_CTRL_REG);
पूर्ण

अटल व्योम apci1500_समयr_enable(काष्ठा comedi_device *dev,
				  अचिन्हित पूर्णांक chan, bool enable)
अणु
	अचिन्हित पूर्णांक bit;
	अचिन्हित पूर्णांक cfg;

	अगर (chan == 0)
		bit = Z8536_CFG_CTRL_CT1E;
	अन्यथा अगर (chan == 1)
		bit = Z8536_CFG_CTRL_CT2E;
	अन्यथा
		bit = Z8536_CFG_CTRL_PCE_CT3E;

	cfg = z8536_पढ़ो(dev, Z8536_CFG_CTRL_REG);
	अगर (enable) अणु
		cfg |= bit;
	पूर्ण अन्यथा अणु
		cfg &= ~bit;
		z8536_ग_लिखो(dev, 0x00, Z8536_CT_CMDSTAT_REG(chan));
	पूर्ण
	z8536_ग_लिखो(dev, cfg, Z8536_CFG_CTRL_REG);
पूर्ण

अटल bool apci1500_ack_irq(काष्ठा comedi_device *dev,
			     अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित पूर्णांक val;

	val = z8536_पढ़ो(dev, reg);
	अगर ((val & Z8536_STAT_IE_IP) == Z8536_STAT_IE_IP) अणु
		val &= 0x0f;			/* preserve any ग_लिखो bits */
		val |= Z8536_CMD_CLR_IP_IUS;
		z8536_ग_लिखो(dev, val, reg);

		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल irqवापस_t apci1500_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा apci1500_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	अचिन्हित लघु status = 0;
	अचिन्हित पूर्णांक val;

	val = inl(devpriv->amcc + AMCC_OP_REG_INTCSR);
	अगर (!(val & INTCSR_INTR_ASSERTED))
		वापस IRQ_NONE;

	अगर (apci1500_ack_irq(dev, Z8536_PA_CMDSTAT_REG))
		status |= 0x01;	/* port a event (inमाला_दो 0-7) */

	अगर (apci1500_ack_irq(dev, Z8536_PB_CMDSTAT_REG)) अणु
		/* Tests अगर this is an बाह्यal error */
		val = inb(dev->iobase + APCI1500_Z8536_PORTB_REG);
		val &= 0xc0;
		अगर (val) अणु
			अगर (val & 0x80)	/* voltage error */
				status |= 0x40;
			अगर (val & 0x40)	/* लघु circuit error */
				status |= 0x80;
		पूर्ण अन्यथा अणु
			status |= 0x02;	/* port b event (inमाला_दो 8-13) */
		पूर्ण
	पूर्ण

	/*
	 * NOTE: The 'status' वापसed by the sample matches the
	 * पूर्णांकerrupt mask inक्रमmation from the APCI-1500 Users Manual.
	 *
	 *    Mask     Meaning
	 * ----------  ------------------------------------------
	 * 0b00000001  Event 1 has occurred
	 * 0b00000010  Event 2 has occurred
	 * 0b00000100  Counter/समयr 1 has run करोwn (not implemented)
	 * 0b00001000  Counter/समयr 2 has run करोwn (not implemented)
	 * 0b00010000  Counter 3 has run करोwn (not implemented)
	 * 0b00100000  Watchकरोg has run करोwn (not implemented)
	 * 0b01000000  Voltage error
	 * 0b10000000  Short-circuit error
	 */
	comedi_buf_ग_लिखो_samples(s, &status, 1);
	comedi_handle_events(dev, s);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक apci1500_di_cancel(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s)
अणु
	/* Disables the मुख्य पूर्णांकerrupt on the board */
	z8536_ग_लिखो(dev, 0x00, Z8536_INT_CTRL_REG);

	/* Disable Ports A & B */
	apci1500_port_enable(dev, false);

	/* Ack any pending पूर्णांकerrupts */
	apci1500_ack_irq(dev, Z8536_PA_CMDSTAT_REG);
	apci1500_ack_irq(dev, Z8536_PB_CMDSTAT_REG);

	/* Disable pattern पूर्णांकerrupts */
	z8536_ग_लिखो(dev, Z8536_CMD_CLR_IE, Z8536_PA_CMDSTAT_REG);
	z8536_ग_लिखो(dev, Z8536_CMD_CLR_IE, Z8536_PB_CMDSTAT_REG);

	/* Enable Ports A & B */
	apci1500_port_enable(dev, true);

	वापस 0;
पूर्ण

अटल पूर्णांक apci1500_di_पूर्णांकtrig_start(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s,
				     अचिन्हित पूर्णांक trig_num)
अणु
	काष्ठा apci1500_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित पूर्णांक pa_mode = Z8536_PAB_MODE_PMS_DISABLE;
	अचिन्हित पूर्णांक pb_mode = Z8536_PAB_MODE_PMS_DISABLE;
	अचिन्हित पूर्णांक pa_trig = trig_num & 0x01;
	अचिन्हित पूर्णांक pb_trig = (trig_num >> 1) & 0x01;
	bool valid_trig = false;
	अचिन्हित पूर्णांक val;

	अगर (trig_num != cmd->start_arg)
		वापस -EINVAL;

	/* Disable Ports A & B */
	apci1500_port_enable(dev, false);

	/* Set Port A क्रम selected trigger pattern */
	z8536_ग_लिखो(dev, devpriv->pm[pa_trig] & 0xff, Z8536_PA_PM_REG);
	z8536_ग_लिखो(dev, devpriv->pt[pa_trig] & 0xff, Z8536_PA_PT_REG);
	z8536_ग_लिखो(dev, devpriv->pp[pa_trig] & 0xff, Z8536_PA_PP_REG);

	/* Set Port B क्रम selected trigger pattern */
	z8536_ग_लिखो(dev, (devpriv->pm[pb_trig] >> 8) & 0xff, Z8536_PB_PM_REG);
	z8536_ग_लिखो(dev, (devpriv->pt[pb_trig] >> 8) & 0xff, Z8536_PB_PT_REG);
	z8536_ग_लिखो(dev, (devpriv->pp[pb_trig] >> 8) & 0xff, Z8536_PB_PP_REG);

	/* Set Port A trigger mode (अगर enabled) and enable पूर्णांकerrupt */
	अगर (devpriv->pm[pa_trig] & 0xff) अणु
		pa_mode = pa_trig ? Z8536_PAB_MODE_PMS_AND
				  : Z8536_PAB_MODE_PMS_OR;

		val = z8536_पढ़ो(dev, Z8536_PA_MODE_REG);
		val &= ~Z8536_PAB_MODE_PMS_MASK;
		val |= (pa_mode | Z8536_PAB_MODE_IMO);
		z8536_ग_लिखो(dev, val, Z8536_PA_MODE_REG);

		z8536_ग_लिखो(dev, Z8536_CMD_SET_IE, Z8536_PA_CMDSTAT_REG);

		valid_trig = true;

		dev_dbg(dev->class_dev,
			"Port A configured for %s mode pattern detection\n",
			pa_trig ? "AND" : "OR");
	पूर्ण

	/* Set Port B trigger mode (अगर enabled) and enable पूर्णांकerrupt */
	अगर (devpriv->pm[pb_trig] & 0xff00) अणु
		pb_mode = pb_trig ? Z8536_PAB_MODE_PMS_AND
				  : Z8536_PAB_MODE_PMS_OR;

		val = z8536_पढ़ो(dev, Z8536_PB_MODE_REG);
		val &= ~Z8536_PAB_MODE_PMS_MASK;
		val |= (pb_mode | Z8536_PAB_MODE_IMO);
		z8536_ग_लिखो(dev, val, Z8536_PB_MODE_REG);

		z8536_ग_लिखो(dev, Z8536_CMD_SET_IE, Z8536_PB_CMDSTAT_REG);

		valid_trig = true;

		dev_dbg(dev->class_dev,
			"Port B configured for %s mode pattern detection\n",
			pb_trig ? "AND" : "OR");
	पूर्ण

	/* Enable Ports A & B */
	apci1500_port_enable(dev, true);

	अगर (!valid_trig) अणु
		dev_dbg(dev->class_dev,
			"digital trigger %d is not configured\n", trig_num);
		वापस -EINVAL;
	पूर्ण

	/* Authorizes the मुख्य पूर्णांकerrupt on the board */
	z8536_ग_लिखो(dev, Z8536_INT_CTRL_MIE | Z8536_INT_CTRL_DLC,
		    Z8536_INT_CTRL_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक apci1500_di_cmd(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s)
अणु
	s->async->पूर्णांकtrig = apci1500_di_पूर्णांकtrig_start;

	वापस 0;
पूर्ण

अटल पूर्णांक apci1500_di_cmdtest(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_cmd *cmd)
अणु
	पूर्णांक err = 0;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_INT);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_FOLLOW);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */
	/* Step 2b : and mutually compatible */

	/* Step 3: check अगर arguments are trivially valid */

	/*
	 * Internal start source triggers:
	 *
	 *   0	AND mode क्रम Port A (digital inमाला_दो 0-7)
	 *	AND mode क्रम Port B (digital inमाला_दो 8-13 and पूर्णांकernal संकेतs)
	 *
	 *   1	OR mode क्रम Port A (digital inमाला_दो 0-7)
	 *	AND mode क्रम Port B (digital inमाला_दो 8-13 and पूर्णांकernal संकेतs)
	 *
	 *   2	AND mode क्रम Port A (digital inमाला_दो 0-7)
	 *	OR mode क्रम Port B (digital inमाला_दो 8-13 and पूर्णांकernal संकेतs)
	 *
	 *   3	OR mode क्रम Port A (digital inमाला_दो 0-7)
	 *	OR mode क्रम Port B (digital inमाला_दो 8-13 and पूर्णांकernal संकेतs)
	 */
	err |= comedi_check_trigger_arg_max(&cmd->start_arg, 3);

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
 * The pattern-recognition logic must be configured beक्रमe the digital
 * input async command is started.
 *
 * Digital input channels 0 to 13 can generate पूर्णांकerrupts. Channels 14
 * and 15 are connected to पूर्णांकernal board status/diagnostic संकेतs.
 *
 * Channel 14 - Voltage error (the बाह्यal supply is < 5V)
 * Channel 15 - Short-circuit/overtemperature error
 *
 *	data[0] : INSN_CONFIG_DIGITAL_TRIG
 *	data[1] : trigger number
 *		  0 = AND mode
 *		  1 = OR mode
 *	data[2] : configuration operation:
 *	          COMEDI_DIGITAL_TRIG_DISABLE = no पूर्णांकerrupts
 *	          COMEDI_DIGITAL_TRIG_ENABLE_EDGES = edge पूर्णांकerrupts
 *	          COMEDI_DIGITAL_TRIG_ENABLE_LEVELS = level पूर्णांकerrupts
 *	data[3] : left-shअगरt क्रम data[4] and data[5]
 *	data[4] : rising-edge/high level channels
 *	data[5] : falling-edge/low level channels
 */
अटल पूर्णांक apci1500_di_cfg_trig(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	काष्ठा apci1500_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक trig = data[1];
	अचिन्हित पूर्णांक shअगरt = data[3];
	अचिन्हित पूर्णांक hi_mask;
	अचिन्हित पूर्णांक lo_mask;
	अचिन्हित पूर्णांक chan_mask;
	अचिन्हित पूर्णांक old_mask;
	अचिन्हित पूर्णांक pm;
	अचिन्हित पूर्णांक pt;
	अचिन्हित पूर्णांक pp;
	अचिन्हित पूर्णांक invalid_chan;

	अगर (trig > 1) अणु
		dev_dbg(dev->class_dev,
			"invalid digital trigger number (0=AND, 1=OR)\n");
		वापस -EINVAL;
	पूर्ण

	अगर (shअगरt <= 16) अणु
		hi_mask = data[4] << shअगरt;
		lo_mask = data[5] << shअगरt;
		old_mask = (1U << shअगरt) - 1;
		invalid_chan = (data[4] | data[5]) >> (16 - shअगरt);
	पूर्ण अन्यथा अणु
		hi_mask = 0;
		lo_mask = 0;
		old_mask = 0xffff;
		invalid_chan = data[4] | data[5];
	पूर्ण
	chan_mask = hi_mask | lo_mask;

	अगर (invalid_chan) अणु
		dev_dbg(dev->class_dev, "invalid digital trigger channel\n");
		वापस -EINVAL;
	पूर्ण

	pm = devpriv->pm[trig] & old_mask;
	pt = devpriv->pt[trig] & old_mask;
	pp = devpriv->pp[trig] & old_mask;

	चयन (data[2]) अणु
	हाल COMEDI_DIGITAL_TRIG_DISABLE:
		/* clear trigger configuration */
		pm = 0;
		pt = 0;
		pp = 0;
		अवरोध;
	हाल COMEDI_DIGITAL_TRIG_ENABLE_EDGES:
		pm |= chan_mask;	/* enable channels */
		pt |= chan_mask;	/* enable edge detection */
		pp |= hi_mask;		/* rising-edge channels */
		pp &= ~lo_mask;		/* falling-edge channels */
		अवरोध;
	हाल COMEDI_DIGITAL_TRIG_ENABLE_LEVELS:
		pm |= chan_mask;	/* enable channels */
		pt &= ~chan_mask;	/* enable level detection */
		pp |= hi_mask;		/* high level channels */
		pp &= ~lo_mask;		/* low level channels */
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	 * The AND mode trigger can only have one channel (max) enabled
	 * क्रम edge detection.
	 */
	अगर (trig == 0) अणु
		पूर्णांक ret = 0;
		अचिन्हित पूर्णांक src;

		src = pt & 0xff;
		अगर (src)
			ret |= comedi_check_trigger_is_unique(src);

		src = (pt >> 8) & 0xff;
		अगर (src)
			ret |= comedi_check_trigger_is_unique(src);

		अगर (ret) अणु
			dev_dbg(dev->class_dev,
				"invalid AND trigger configuration\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/* save the trigger configuration */
	devpriv->pm[trig] = pm;
	devpriv->pt[trig] = pt;
	devpriv->pp[trig] = pp;

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci1500_di_insn_config(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_insn *insn,
				   अचिन्हित पूर्णांक *data)
अणु
	चयन (data[0]) अणु
	हाल INSN_CONFIG_DIGITAL_TRIG:
		वापस apci1500_di_cfg_trig(dev, s, insn, data);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक apci1500_di_insn_bits(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	काष्ठा apci1500_निजी *devpriv = dev->निजी;

	data[1] = inw(devpriv->adकरोn + APCI1500_DI_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci1500_करो_insn_bits(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	काष्ठा apci1500_निजी *devpriv = dev->निजी;

	अगर (comedi_dio_update_state(s, data))
		outw(s->state, devpriv->adकरोn + APCI1500_DO_REG);

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci1500_समयr_insn_config(काष्ठा comedi_device *dev,
				      काष्ठा comedi_subdevice *s,
				      काष्ठा comedi_insn *insn,
				      अचिन्हित पूर्णांक *data)
अणु
	काष्ठा apci1500_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक val;

	चयन (data[0]) अणु
	हाल INSN_CONFIG_ARM:
		val = data[1] & s->maxdata;
		z8536_ग_लिखो(dev, val & 0xff, Z8536_CT_RELOAD_LSB_REG(chan));
		z8536_ग_लिखो(dev, (val >> 8) & 0xff,
			    Z8536_CT_RELOAD_MSB_REG(chan));

		apci1500_समयr_enable(dev, chan, true);
		z8536_ग_लिखो(dev, Z8536_CT_CMDSTAT_GCB,
			    Z8536_CT_CMDSTAT_REG(chan));
		अवरोध;
	हाल INSN_CONFIG_DISARM:
		apci1500_समयr_enable(dev, chan, false);
		अवरोध;

	हाल INSN_CONFIG_GET_COUNTER_STATUS:
		data[1] = 0;
		val = z8536_पढ़ो(dev, Z8536_CT_CMDSTAT_REG(chan));
		अगर (val & Z8536_CT_STAT_CIP)
			data[1] |= COMEDI_COUNTER_COUNTING;
		अगर (val & Z8536_CT_CMDSTAT_GCB)
			data[1] |= COMEDI_COUNTER_ARMED;
		अगर (val & Z8536_STAT_IP) अणु
			data[1] |= COMEDI_COUNTER_TERMINAL_COUNT;
			apci1500_ack_irq(dev, Z8536_CT_CMDSTAT_REG(chan));
		पूर्ण
		data[2] = COMEDI_COUNTER_ARMED | COMEDI_COUNTER_COUNTING |
			  COMEDI_COUNTER_TERMINAL_COUNT;
		अवरोध;

	हाल INSN_CONFIG_SET_COUNTER_MODE:
		/* Simulate the 8254 समयr modes */
		चयन (data[1]) अणु
		हाल I8254_MODE0:
			/* Interrupt on Terminal Count */
			val = Z8536_CT_MODE_ECE |
			      Z8536_CT_MODE_DCS_ONESHOT;
			अवरोध;
		हाल I8254_MODE1:
			/* Hardware Retriggerable One-Shot */
			val = Z8536_CT_MODE_ETE |
			      Z8536_CT_MODE_DCS_ONESHOT;
			अवरोध;
		हाल I8254_MODE2:
			/* Rate Generator */
			val = Z8536_CT_MODE_CSC |
			      Z8536_CT_MODE_DCS_PULSE;
			अवरोध;
		हाल I8254_MODE3:
			/* Square Wave Mode */
			val = Z8536_CT_MODE_CSC |
			      Z8536_CT_MODE_DCS_SQRWAVE;
			अवरोध;
		हाल I8254_MODE4:
			/* Software Triggered Strobe */
			val = Z8536_CT_MODE_REB |
			      Z8536_CT_MODE_DCS_PULSE;
			अवरोध;
		हाल I8254_MODE5:
			/* Hardware Triggered Strobe (watchकरोg) */
			val = Z8536_CT_MODE_EOE |
			      Z8536_CT_MODE_ETE |
			      Z8536_CT_MODE_REB |
			      Z8536_CT_MODE_DCS_PULSE;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		apci1500_समयr_enable(dev, chan, false);
		z8536_ग_लिखो(dev, val, Z8536_CT_MODE_REG(chan));
		अवरोध;

	हाल INSN_CONFIG_SET_CLOCK_SRC:
		अगर (data[1] > 2)
			वापस -EINVAL;
		devpriv->clk_src = data[1];
		अगर (devpriv->clk_src == 2)
			devpriv->clk_src = 3;
		outw(devpriv->clk_src, devpriv->adकरोn + APCI1500_CLK_SEL_REG);
		अवरोध;
	हाल INSN_CONFIG_GET_CLOCK_SRC:
		चयन (devpriv->clk_src) अणु
		हाल 0:
			data[1] = 0;		/* 111.86 kHz / 2 */
			data[2] = 17879;	/* 17879 ns (approx) */
			अवरोध;
		हाल 1:
			data[1] = 1;		/* 3.49 kHz / 2 */
			data[2] = 573066;	/* 573066 ns (approx) */
			अवरोध;
		हाल 3:
			data[1] = 2;		/* 1.747 kHz / 2 */
			data[2] = 1164822;	/* 1164822 ns (approx) */
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;

	हाल INSN_CONFIG_SET_GATE_SRC:
		अगर (chan == 0)
			वापस -EINVAL;

		val = z8536_पढ़ो(dev, Z8536_CT_MODE_REG(chan));
		val &= Z8536_CT_MODE_EGE;
		अगर (data[1] == 1)
			val |= Z8536_CT_MODE_EGE;
		अन्यथा अगर (data[1] > 1)
			वापस -EINVAL;
		z8536_ग_लिखो(dev, val, Z8536_CT_MODE_REG(chan));
		अवरोध;
	हाल INSN_CONFIG_GET_GATE_SRC:
		अगर (chan == 0)
			वापस -EINVAL;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस insn->n;
पूर्ण

अटल पूर्णांक apci1500_समयr_insn_ग_लिखो(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s,
				     काष्ठा comedi_insn *insn,
				     अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक cmd;

	cmd = z8536_पढ़ो(dev, Z8536_CT_CMDSTAT_REG(chan));
	cmd &= Z8536_CT_CMDSTAT_GCB;	/* preserve gate */
	cmd |= Z8536_CT_CMD_TCB;	/* set trigger */

	/* software trigger a समयr, it only makes sense to करो one ग_लिखो */
	अगर (insn->n)
		z8536_ग_लिखो(dev, cmd, Z8536_CT_CMDSTAT_REG(chan));

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci1500_समयr_insn_पढ़ो(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s,
				    काष्ठा comedi_insn *insn,
				    अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक cmd;
	अचिन्हित पूर्णांक val;
	पूर्णांक i;

	cmd = z8536_पढ़ो(dev, Z8536_CT_CMDSTAT_REG(chan));
	cmd &= Z8536_CT_CMDSTAT_GCB;	/* preserve gate */
	cmd |= Z8536_CT_CMD_RCC;	/* set RCC */

	क्रम (i = 0; i < insn->n; i++) अणु
		z8536_ग_लिखो(dev, cmd, Z8536_CT_CMDSTAT_REG(chan));

		val = z8536_पढ़ो(dev, Z8536_CT_VAL_MSB_REG(chan)) << 8;
		val |= z8536_पढ़ो(dev, Z8536_CT_VAL_LSB_REG(chan));

		data[i] = val;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक apci1500_स्वतः_attach(काष्ठा comedi_device *dev,
				अचिन्हित दीर्घ context)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	काष्ठा apci1500_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;

	dev->iobase = pci_resource_start(pcidev, 1);
	devpriv->amcc = pci_resource_start(pcidev, 0);
	devpriv->adकरोn = pci_resource_start(pcidev, 2);

	z8536_reset(dev);

	अगर (pcidev->irq > 0) अणु
		ret = request_irq(pcidev->irq, apci1500_पूर्णांकerrupt, IRQF_SHARED,
				  dev->board_name, dev);
		अगर (ret == 0)
			dev->irq = pcidev->irq;
	पूर्ण

	ret = comedi_alloc_subdevices(dev, 3);
	अगर (ret)
		वापस ret;

	/* Digital Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= apci1500_di_insn_bits;
	अगर (dev->irq) अणु
		dev->पढ़ो_subdev = s;
		s->subdev_flags |= SDF_CMD_READ;
		s->len_chanlist	= 1;
		s->insn_config	= apci1500_di_insn_config;
		s->करो_cmdtest	= apci1500_di_cmdtest;
		s->करो_cmd	= apci1500_di_cmd;
		s->cancel	= apci1500_di_cancel;
	पूर्ण

	/* Digital Output subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= apci1500_करो_insn_bits;

	/* reset all the digital outमाला_दो */
	outw(0x0, devpriv->adकरोn + APCI1500_DO_REG);

	/* Counter/Timer(Watchकरोg) subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_TIMER;
	s->subdev_flags	= SDF_WRITABLE | SDF_READABLE;
	s->n_chan	= 3;
	s->maxdata	= 0xffff;
	s->range_table	= &range_unknown;
	s->insn_config	= apci1500_समयr_insn_config;
	s->insn_ग_लिखो	= apci1500_समयr_insn_ग_लिखो;
	s->insn_पढ़ो	= apci1500_समयr_insn_पढ़ो;

	/* Enable the PCI पूर्णांकerrupt */
	अगर (dev->irq) अणु
		outl(0x2000 | INTCSR_INBOX_FULL_INT,
		     devpriv->amcc + AMCC_OP_REG_INTCSR);
		inl(devpriv->amcc + AMCC_OP_REG_IMB1);
		inl(devpriv->amcc + AMCC_OP_REG_INTCSR);
		outl(INTCSR_INBOX_INTR_STATUS | 0x2000 | INTCSR_INBOX_FULL_INT,
		     devpriv->amcc + AMCC_OP_REG_INTCSR);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम apci1500_detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा apci1500_निजी *devpriv = dev->निजी;

	अगर (devpriv->amcc)
		outl(0x0, devpriv->amcc + AMCC_OP_REG_INTCSR);
	comedi_pci_detach(dev);
पूर्ण

अटल काष्ठा comedi_driver apci1500_driver = अणु
	.driver_name	= "addi_apci_1500",
	.module		= THIS_MODULE,
	.स्वतः_attach	= apci1500_स्वतः_attach,
	.detach		= apci1500_detach,
पूर्ण;

अटल पूर्णांक apci1500_pci_probe(काष्ठा pci_dev *dev,
			      स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &apci1500_driver, id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id apci1500_pci_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMCC, 0x80fc) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, apci1500_pci_table);

अटल काष्ठा pci_driver apci1500_pci_driver = अणु
	.name		= "addi_apci_1500",
	.id_table	= apci1500_pci_table,
	.probe		= apci1500_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(apci1500_driver, apci1500_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("ADDI-DATA APCI-1500, 16 channel DI / 16 channel DO boards");
MODULE_LICENSE("GPL");
