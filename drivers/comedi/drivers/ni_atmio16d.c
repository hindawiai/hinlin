<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Comedi driver क्रम National Instruments AT-MIO16D board
 * Copyright (C) 2000 Chris R. Baugher <baugher@enteract.com>
 */

/*
 * Driver: ni_aपंचांगio16d
 * Description: National Instruments AT-MIO-16D
 * Author: Chris R. Baugher <baugher@enteract.com>
 * Status: unknown
 * Devices: [National Instruments] AT-MIO-16 (aपंचांगio16), AT-MIO-16D (aपंचांगio16d)
 *
 * Configuration options:
 *   [0] - I/O port
 *   [1] - MIO irq (0 == no irq; or 3,4,5,6,7,9,10,11,12,14,15)
 *   [2] - DIO irq (0 == no irq; or 3,4,5,6,7,9)
 *   [3] - DMA1 channel (0 == no DMA; or 5,6,7)
 *   [4] - DMA2 channel (0 == no DMA; or 5,6,7)
 *   [5] - a/d mux (0=dअगरferential; 1=single)
 *   [6] - a/d range (0=bipolar10; 1=bipolar5; 2=unipolar10)
 *   [7] - dac0 range (0=bipolar; 1=unipolar)
 *   [8] - dac0 reference (0=पूर्णांकernal; 1=बाह्यal)
 *   [9] - dac0 coding (0=2's comp; 1=straight binary)
 *   [10] - dac1 range (same as dac0 options)
 *   [11] - dac1 reference (same as dac0 options)
 *   [12] - dac1 coding (same as dac0 options)
 */

/*
 * I must give credit here to Michal Dobes <करोbes@tesnet.cz> who
 * wrote the driver क्रम Advantec's pcl812 boards. I used the पूर्णांकerrupt
 * handling code from his driver as an example क्रम this one.
 *
 * Chris Baugher
 * 5/1/2000
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश "../comedidev.h"

#समावेश "8255.h"

/* Configuration and Status Registers */
#घोषणा COM_REG_1	0x00	/* wo 16 */
#घोषणा STAT_REG	0x00	/* ro 16 */
#घोषणा COM_REG_2	0x02	/* wo 16 */
/* Event Strobe Registers */
#घोषणा START_CONVERT_REG	0x08	/* wo 16 */
#घोषणा START_DAQ_REG		0x0A	/* wo 16 */
#घोषणा AD_CLEAR_REG		0x0C	/* wo 16 */
#घोषणा EXT_STROBE_REG		0x0E	/* wo 16 */
/* Analog Output Registers */
#घोषणा DAC0_REG		0x10	/* wo 16 */
#घोषणा DAC1_REG		0x12	/* wo 16 */
#घोषणा INT2CLR_REG		0x14	/* wo 16 */
/* Analog Input Registers */
#घोषणा MUX_CNTR_REG		0x04	/* wo 16 */
#घोषणा MUX_GAIN_REG		0x06	/* wo 16 */
#घोषणा AD_FIFO_REG		0x16	/* ro 16 */
#घोषणा DMA_TC_INT_CLR_REG	0x16	/* wo 16 */
/* AM9513A Counter/Timer Registers */
#घोषणा AM9513A_DATA_REG	0x18	/* rw 16 */
#घोषणा AM9513A_COM_REG		0x1A	/* wo 16 */
#घोषणा AM9513A_STAT_REG	0x1A	/* ro 16 */
/* MIO-16 Digital I/O Registers */
#घोषणा MIO_16_DIG_IN_REG	0x1C	/* ro 16 */
#घोषणा MIO_16_DIG_OUT_REG	0x1C	/* wo 16 */
/* RTSI Switch Registers */
#घोषणा RTSI_SW_SHIFT_REG	0x1E	/* wo 8 */
#घोषणा RTSI_SW_STROBE_REG	0x1F	/* wo 8 */
/* DIO-24 Registers */
#घोषणा DIO_24_PORTA_REG	0x00	/* rw 8 */
#घोषणा DIO_24_PORTB_REG	0x01	/* rw 8 */
#घोषणा DIO_24_PORTC_REG	0x02	/* rw 8 */
#घोषणा DIO_24_CNFG_REG		0x03	/* wo 8 */

/* Command Register bits */
#घोषणा COMREG1_2SCADC		0x0001
#घोषणा COMREG1_1632CNT		0x0002
#घोषणा COMREG1_SCANEN		0x0008
#घोषणा COMREG1_DAQEN		0x0010
#घोषणा COMREG1_DMAEN		0x0020
#घोषणा COMREG1_CONVINTEN	0x0080
#घोषणा COMREG2_SCN2		0x0010
#घोषणा COMREG2_INTEN		0x0080
#घोषणा COMREG2_DOUTEN0		0x0100
#घोषणा COMREG2_DOUTEN1		0x0200
/* Status Register bits */
#घोषणा STAT_AD_OVERRUN		0x0100
#घोषणा STAT_AD_OVERFLOW	0x0200
#घोषणा STAT_AD_DAQPROG		0x0800
#घोषणा STAT_AD_CONVAVAIL	0x2000
#घोषणा STAT_AD_DAQSTOPINT	0x4000
/* AM9513A Counter/Timer defines */
#घोषणा CLOCK_1_MHZ		0x8B25
#घोषणा CLOCK_100_KHZ	0x8C25
#घोषणा CLOCK_10_KHZ	0x8D25
#घोषणा CLOCK_1_KHZ		0x8E25
#घोषणा CLOCK_100_HZ	0x8F25

काष्ठा aपंचांगio16_board_t अणु
	स्थिर अक्षर *name;
	पूर्णांक has_8255;
पूर्ण;

/* range काष्ठाs */
अटल स्थिर काष्ठा comedi_lrange range_aपंचांगio16d_ai_10_bipolar = अणु
	4, अणु
		BIP_RANGE(10),
		BIP_RANGE(1),
		BIP_RANGE(0.1),
		BIP_RANGE(0.02)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_aपंचांगio16d_ai_5_bipolar = अणु
	4, अणु
		BIP_RANGE(5),
		BIP_RANGE(0.5),
		BIP_RANGE(0.05),
		BIP_RANGE(0.01)
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange range_aपंचांगio16d_ai_unipolar = अणु
	4, अणु
		UNI_RANGE(10),
		UNI_RANGE(1),
		UNI_RANGE(0.1),
		UNI_RANGE(0.02)
	पूर्ण
पूर्ण;

/* निजी data काष्ठा */
काष्ठा aपंचांगio16d_निजी अणु
	क्रमागत अणु adc_dअगरf, adc_singleended पूर्ण adc_mux;
	क्रमागत अणु adc_bipolar10, adc_bipolar5, adc_unipolar10 पूर्ण adc_range;
	क्रमागत अणु adc_2comp, adc_straight पूर्ण adc_coding;
	क्रमागत अणु dac_bipolar, dac_unipolar पूर्ण dac0_range, dac1_range;
	क्रमागत अणु dac_पूर्णांकernal, dac_बाह्यal पूर्ण dac0_reference, dac1_reference;
	क्रमागत अणु dac_2comp, dac_straight पूर्ण dac0_coding, dac1_coding;
	स्थिर काष्ठा comedi_lrange *ao_range_type_list[2];
	अचिन्हित पूर्णांक com_reg_1_state; /* current state of command रेजिस्टर 1 */
	अचिन्हित पूर्णांक com_reg_2_state; /* current state of command रेजिस्टर 2 */
पूर्ण;

अटल व्योम reset_counters(काष्ठा comedi_device *dev)
अणु
	/* Counter 2 */
	outw(0xFFC2, dev->iobase + AM9513A_COM_REG);
	outw(0xFF02, dev->iobase + AM9513A_COM_REG);
	outw(0x4, dev->iobase + AM9513A_DATA_REG);
	outw(0xFF0A, dev->iobase + AM9513A_COM_REG);
	outw(0x3, dev->iobase + AM9513A_DATA_REG);
	outw(0xFF42, dev->iobase + AM9513A_COM_REG);
	outw(0xFF42, dev->iobase + AM9513A_COM_REG);
	/* Counter 3 */
	outw(0xFFC4, dev->iobase + AM9513A_COM_REG);
	outw(0xFF03, dev->iobase + AM9513A_COM_REG);
	outw(0x4, dev->iobase + AM9513A_DATA_REG);
	outw(0xFF0B, dev->iobase + AM9513A_COM_REG);
	outw(0x3, dev->iobase + AM9513A_DATA_REG);
	outw(0xFF44, dev->iobase + AM9513A_COM_REG);
	outw(0xFF44, dev->iobase + AM9513A_COM_REG);
	/* Counter 4 */
	outw(0xFFC8, dev->iobase + AM9513A_COM_REG);
	outw(0xFF04, dev->iobase + AM9513A_COM_REG);
	outw(0x4, dev->iobase + AM9513A_DATA_REG);
	outw(0xFF0C, dev->iobase + AM9513A_COM_REG);
	outw(0x3, dev->iobase + AM9513A_DATA_REG);
	outw(0xFF48, dev->iobase + AM9513A_COM_REG);
	outw(0xFF48, dev->iobase + AM9513A_COM_REG);
	/* Counter 5 */
	outw(0xFFD0, dev->iobase + AM9513A_COM_REG);
	outw(0xFF05, dev->iobase + AM9513A_COM_REG);
	outw(0x4, dev->iobase + AM9513A_DATA_REG);
	outw(0xFF0D, dev->iobase + AM9513A_COM_REG);
	outw(0x3, dev->iobase + AM9513A_DATA_REG);
	outw(0xFF50, dev->iobase + AM9513A_COM_REG);
	outw(0xFF50, dev->iobase + AM9513A_COM_REG);

	outw(0, dev->iobase + AD_CLEAR_REG);
पूर्ण

अटल व्योम reset_aपंचांगio16d(काष्ठा comedi_device *dev)
अणु
	काष्ठा aपंचांगio16d_निजी *devpriv = dev->निजी;
	पूर्णांक i;

	/* now we need to initialize the board */
	outw(0, dev->iobase + COM_REG_1);
	outw(0, dev->iobase + COM_REG_2);
	outw(0, dev->iobase + MUX_GAIN_REG);
	/* init AM9513A समयr */
	outw(0xFFFF, dev->iobase + AM9513A_COM_REG);
	outw(0xFFEF, dev->iobase + AM9513A_COM_REG);
	outw(0xFF17, dev->iobase + AM9513A_COM_REG);
	outw(0xF000, dev->iobase + AM9513A_DATA_REG);
	क्रम (i = 1; i <= 5; ++i) अणु
		outw(0xFF00 + i, dev->iobase + AM9513A_COM_REG);
		outw(0x0004, dev->iobase + AM9513A_DATA_REG);
		outw(0xFF08 + i, dev->iobase + AM9513A_COM_REG);
		outw(0x3, dev->iobase + AM9513A_DATA_REG);
	पूर्ण
	outw(0xFF5F, dev->iobase + AM9513A_COM_REG);
	/* समयr init करोne */
	outw(0, dev->iobase + AD_CLEAR_REG);
	outw(0, dev->iobase + INT2CLR_REG);
	/* select straight binary mode क्रम Analog Input */
	devpriv->com_reg_1_state |= 1;
	outw(devpriv->com_reg_1_state, dev->iobase + COM_REG_1);
	devpriv->adc_coding = adc_straight;
	/* zero the analog outमाला_दो */
	outw(2048, dev->iobase + DAC0_REG);
	outw(2048, dev->iobase + DAC1_REG);
पूर्ण

अटल irqवापस_t aपंचांगio16d_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	अचिन्हित लघु val;

	val = inw(dev->iobase + AD_FIFO_REG);
	comedi_buf_ग_लिखो_samples(s, &val, 1);
	comedi_handle_events(dev, s);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक aपंचांगio16d_ai_cmdtest(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_cmd *cmd)
अणु
	पूर्णांक err = 0;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src,
					TRIG_FOLLOW | TRIG_TIMER);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_TIMER);
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

	अगर (cmd->scan_begin_src == TRIG_FOLLOW) अणु
		/* पूर्णांकernal trigger */
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);
	पूर्ण

	err |= comedi_check_trigger_arg_min(&cmd->convert_arg, 10000);
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	अन्यथा	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगio16d_ai_cmd(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s)
अणु
	काष्ठा aपंचांगio16d_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित पूर्णांक समयr, base_घड़ी;
	अचिन्हित पूर्णांक sample_count, पंचांगp, chan, gain;
	पूर्णांक i;

	/*
	 * This is slowly becoming a working command पूर्णांकerface.
	 * It is still uber-experimental
	 */

	reset_counters(dev);

	/* check अगर scanning multiple channels */
	अगर (cmd->chanlist_len < 2) अणु
		devpriv->com_reg_1_state &= ~COMREG1_SCANEN;
		outw(devpriv->com_reg_1_state, dev->iobase + COM_REG_1);
	पूर्ण अन्यथा अणु
		devpriv->com_reg_1_state |= COMREG1_SCANEN;
		devpriv->com_reg_2_state |= COMREG2_SCN2;
		outw(devpriv->com_reg_1_state, dev->iobase + COM_REG_1);
		outw(devpriv->com_reg_2_state, dev->iobase + COM_REG_2);
	पूर्ण

	/* Setup the Mux-Gain Counter */
	क्रम (i = 0; i < cmd->chanlist_len; ++i) अणु
		chan = CR_CHAN(cmd->chanlist[i]);
		gain = CR_RANGE(cmd->chanlist[i]);
		outw(i, dev->iobase + MUX_CNTR_REG);
		पंचांगp = chan | (gain << 6);
		अगर (i == cmd->scan_end_arg - 1)
			पंचांगp |= 0x0010;	/* set LASTONE bit */
		outw(पंचांगp, dev->iobase + MUX_GAIN_REG);
	पूर्ण

	/*
	 * Now program the sample पूर्णांकerval समयr.
	 * Figure out which घड़ी to use then get an appropriate समयr value.
	 */
	अगर (cmd->convert_arg < 65536000) अणु
		base_घड़ी = CLOCK_1_MHZ;
		समयr = cmd->convert_arg / 1000;
	पूर्ण अन्यथा अगर (cmd->convert_arg < 655360000) अणु
		base_घड़ी = CLOCK_100_KHZ;
		समयr = cmd->convert_arg / 10000;
	पूर्ण अन्यथा /* cmd->convert_arg < 6553600000 */ अणु
		base_घड़ी = CLOCK_10_KHZ;
		समयr = cmd->convert_arg / 100000;
	पूर्ण
	outw(0xFF03, dev->iobase + AM9513A_COM_REG);
	outw(base_घड़ी, dev->iobase + AM9513A_DATA_REG);
	outw(0xFF0B, dev->iobase + AM9513A_COM_REG);
	outw(0x2, dev->iobase + AM9513A_DATA_REG);
	outw(0xFF44, dev->iobase + AM9513A_COM_REG);
	outw(0xFFF3, dev->iobase + AM9513A_COM_REG);
	outw(समयr, dev->iobase + AM9513A_DATA_REG);
	outw(0xFF24, dev->iobase + AM9513A_COM_REG);

	/* Now figure out how many samples to get */
	/* and program the sample counter */
	sample_count = cmd->stop_arg * cmd->scan_end_arg;
	outw(0xFF04, dev->iobase + AM9513A_COM_REG);
	outw(0x1025, dev->iobase + AM9513A_DATA_REG);
	outw(0xFF0C, dev->iobase + AM9513A_COM_REG);
	अगर (sample_count < 65536) अणु
		/* use only Counter 4 */
		outw(sample_count, dev->iobase + AM9513A_DATA_REG);
		outw(0xFF48, dev->iobase + AM9513A_COM_REG);
		outw(0xFFF4, dev->iobase + AM9513A_COM_REG);
		outw(0xFF28, dev->iobase + AM9513A_COM_REG);
		devpriv->com_reg_1_state &= ~COMREG1_1632CNT;
		outw(devpriv->com_reg_1_state, dev->iobase + COM_REG_1);
	पूर्ण अन्यथा अणु
		/* Counter 4 and 5 are needed */

		पंचांगp = sample_count & 0xFFFF;
		अगर (पंचांगp)
			outw(पंचांगp - 1, dev->iobase + AM9513A_DATA_REG);
		अन्यथा
			outw(0xFFFF, dev->iobase + AM9513A_DATA_REG);

		outw(0xFF48, dev->iobase + AM9513A_COM_REG);
		outw(0, dev->iobase + AM9513A_DATA_REG);
		outw(0xFF28, dev->iobase + AM9513A_COM_REG);
		outw(0xFF05, dev->iobase + AM9513A_COM_REG);
		outw(0x25, dev->iobase + AM9513A_DATA_REG);
		outw(0xFF0D, dev->iobase + AM9513A_COM_REG);
		पंचांगp = sample_count & 0xFFFF;
		अगर ((पंचांगp == 0) || (पंचांगp == 1)) अणु
			outw((sample_count >> 16) & 0xFFFF,
			     dev->iobase + AM9513A_DATA_REG);
		पूर्ण अन्यथा अणु
			outw(((sample_count >> 16) & 0xFFFF) + 1,
			     dev->iobase + AM9513A_DATA_REG);
		पूर्ण
		outw(0xFF70, dev->iobase + AM9513A_COM_REG);
		devpriv->com_reg_1_state |= COMREG1_1632CNT;
		outw(devpriv->com_reg_1_state, dev->iobase + COM_REG_1);
	पूर्ण

	/*
	 * Program the scan पूर्णांकerval समयr ONLY IF SCANNING IS ENABLED.
	 * Figure out which घड़ी to use then get an appropriate समयr value.
	 */
	अगर (cmd->chanlist_len > 1) अणु
		अगर (cmd->scan_begin_arg < 65536000) अणु
			base_घड़ी = CLOCK_1_MHZ;
			समयr = cmd->scan_begin_arg / 1000;
		पूर्ण अन्यथा अगर (cmd->scan_begin_arg < 655360000) अणु
			base_घड़ी = CLOCK_100_KHZ;
			समयr = cmd->scan_begin_arg / 10000;
		पूर्ण अन्यथा /* cmd->scan_begin_arg < 6553600000 */ अणु
			base_घड़ी = CLOCK_10_KHZ;
			समयr = cmd->scan_begin_arg / 100000;
		पूर्ण
		outw(0xFF02, dev->iobase + AM9513A_COM_REG);
		outw(base_घड़ी, dev->iobase + AM9513A_DATA_REG);
		outw(0xFF0A, dev->iobase + AM9513A_COM_REG);
		outw(0x2, dev->iobase + AM9513A_DATA_REG);
		outw(0xFF42, dev->iobase + AM9513A_COM_REG);
		outw(0xFFF2, dev->iobase + AM9513A_COM_REG);
		outw(समयr, dev->iobase + AM9513A_DATA_REG);
		outw(0xFF22, dev->iobase + AM9513A_COM_REG);
	पूर्ण

	/* Clear the A/D FIFO and reset the MUX counter */
	outw(0, dev->iobase + AD_CLEAR_REG);
	outw(0, dev->iobase + MUX_CNTR_REG);
	outw(0, dev->iobase + INT2CLR_REG);
	/* enable this acquisition operation */
	devpriv->com_reg_1_state |= COMREG1_DAQEN;
	outw(devpriv->com_reg_1_state, dev->iobase + COM_REG_1);
	/* enable पूर्णांकerrupts क्रम conversion completion */
	devpriv->com_reg_1_state |= COMREG1_CONVINTEN;
	devpriv->com_reg_2_state |= COMREG2_INTEN;
	outw(devpriv->com_reg_1_state, dev->iobase + COM_REG_1);
	outw(devpriv->com_reg_2_state, dev->iobase + COM_REG_2);
	/* apply a trigger. this starts the counters! */
	outw(0, dev->iobase + START_DAQ_REG);

	वापस 0;
पूर्ण

/* This will cancel a running acquisition operation */
अटल पूर्णांक aपंचांगio16d_ai_cancel(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s)
अणु
	reset_aपंचांगio16d(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगio16d_ai_eoc(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s,
			   काष्ठा comedi_insn *insn,
			   अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = inw(dev->iobase + STAT_REG);
	अगर (status & STAT_AD_CONVAVAIL)
		वापस 0;
	अगर (status & STAT_AD_OVERFLOW) अणु
		outw(0, dev->iobase + AD_CLEAR_REG);
		वापस -EOVERFLOW;
	पूर्ण
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक aपंचांगio16d_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	काष्ठा aपंचांगio16d_निजी *devpriv = dev->निजी;
	पूर्णांक i;
	पूर्णांक chan;
	पूर्णांक gain;
	पूर्णांक ret;

	chan = CR_CHAN(insn->chanspec);
	gain = CR_RANGE(insn->chanspec);

	/* reset the Analog input circuitry */
	/* outw( 0, dev->iobase+AD_CLEAR_REG ); */
	/* reset the Analog Input MUX Counter to 0 */
	/* outw( 0, dev->iobase+MUX_CNTR_REG ); */

	/* set the Input MUX gain */
	outw(chan | (gain << 6), dev->iobase + MUX_GAIN_REG);

	क्रम (i = 0; i < insn->n; i++) अणु
		/* start the conversion */
		outw(0, dev->iobase + START_CONVERT_REG);

		/* रुको क्रम it to finish */
		ret = comedi_समयout(dev, s, insn, aपंचांगio16d_ai_eoc, 0);
		अगर (ret)
			वापस ret;

		/* पढ़ो the data now */
		data[i] = inw(dev->iobase + AD_FIFO_REG);
		/* change to two's complement अगर need be */
		अगर (devpriv->adc_coding == adc_2comp)
			data[i] ^= 0x800;
	पूर्ण

	वापस i;
पूर्ण

अटल पूर्णांक aपंचांगio16d_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	काष्ठा aपंचांगio16d_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक reg = (chan) ? DAC1_REG : DAC0_REG;
	bool munge = false;
	पूर्णांक i;

	अगर (chan == 0 && devpriv->dac0_coding == dac_2comp)
		munge = true;
	अगर (chan == 1 && devpriv->dac1_coding == dac_2comp)
		munge = true;

	क्रम (i = 0; i < insn->n; i++) अणु
		अचिन्हित पूर्णांक val = data[i];

		s->पढ़ोback[chan] = val;

		अगर (munge)
			val ^= 0x800;

		outw(val, dev->iobase + reg);
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक aपंचांगio16d_dio_insn_bits(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data))
		outw(s->state, dev->iobase + MIO_16_DIG_OUT_REG);

	data[1] = inw(dev->iobase + MIO_16_DIG_IN_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक aपंचांगio16d_dio_insn_config(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s,
				    काष्ठा comedi_insn *insn,
				    अचिन्हित पूर्णांक *data)
अणु
	काष्ठा aपंचांगio16d_निजी *devpriv = dev->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक mask;
	पूर्णांक ret;

	अगर (chan < 4)
		mask = 0x0f;
	अन्यथा
		mask = 0xf0;

	ret = comedi_dio_insn_config(dev, s, insn, data, mask);
	अगर (ret)
		वापस ret;

	devpriv->com_reg_2_state &= ~(COMREG2_DOUTEN0 | COMREG2_DOUTEN1);
	अगर (s->io_bits & 0x0f)
		devpriv->com_reg_2_state |= COMREG2_DOUTEN0;
	अगर (s->io_bits & 0xf0)
		devpriv->com_reg_2_state |= COMREG2_DOUTEN1;
	outw(devpriv->com_reg_2_state, dev->iobase + COM_REG_2);

	वापस insn->n;
पूर्ण

अटल पूर्णांक aपंचांगio16d_attach(काष्ठा comedi_device *dev,
			   काष्ठा comedi_devconfig *it)
अणु
	स्थिर काष्ठा aपंचांगio16_board_t *board = dev->board_ptr;
	काष्ठा aपंचांगio16d_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	ret = comedi_request_region(dev, it->options[0], 0x20);
	अगर (ret)
		वापस ret;

	ret = comedi_alloc_subdevices(dev, 4);
	अगर (ret)
		वापस ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	/* reset the aपंचांगio16d hardware */
	reset_aपंचांगio16d(dev);

	अगर (it->options[1]) अणु
		ret = request_irq(it->options[1], aपंचांगio16d_पूर्णांकerrupt, 0,
				  dev->board_name, dev);
		अगर (ret == 0)
			dev->irq = it->options[1];
	पूर्ण

	/* set device options */
	devpriv->adc_mux = it->options[5];
	devpriv->adc_range = it->options[6];

	devpriv->dac0_range = it->options[7];
	devpriv->dac0_reference = it->options[8];
	devpriv->dac0_coding = it->options[9];
	devpriv->dac1_range = it->options[10];
	devpriv->dac1_reference = it->options[11];
	devpriv->dac1_coding = it->options[12];

	/* setup sub-devices */
	s = &dev->subdevices[0];
	/* ai subdevice */
	s->type = COMEDI_SUBD_AI;
	s->subdev_flags = SDF_READABLE | SDF_GROUND;
	s->n_chan = (devpriv->adc_mux ? 16 : 8);
	s->insn_पढ़ो = aपंचांगio16d_ai_insn_पढ़ो;
	s->maxdata = 0xfff;	/* 4095 decimal */
	चयन (devpriv->adc_range) अणु
	हाल adc_bipolar10:
		s->range_table = &range_aपंचांगio16d_ai_10_bipolar;
		अवरोध;
	हाल adc_bipolar5:
		s->range_table = &range_aपंचांगio16d_ai_5_bipolar;
		अवरोध;
	हाल adc_unipolar10:
		s->range_table = &range_aपंचांगio16d_ai_unipolar;
		अवरोध;
	पूर्ण
	अगर (dev->irq) अणु
		dev->पढ़ो_subdev = s;
		s->subdev_flags |= SDF_CMD_READ;
		s->len_chanlist = 16;
		s->करो_cmdtest = aपंचांगio16d_ai_cmdtest;
		s->करो_cmd = aपंचांगio16d_ai_cmd;
		s->cancel = aपंचांगio16d_ai_cancel;
	पूर्ण

	/* ao subdevice */
	s = &dev->subdevices[1];
	s->type = COMEDI_SUBD_AO;
	s->subdev_flags = SDF_WRITABLE;
	s->n_chan = 2;
	s->maxdata = 0xfff;	/* 4095 decimal */
	s->range_table_list = devpriv->ao_range_type_list;
	चयन (devpriv->dac0_range) अणु
	हाल dac_bipolar:
		devpriv->ao_range_type_list[0] = &range_bipolar10;
		अवरोध;
	हाल dac_unipolar:
		devpriv->ao_range_type_list[0] = &range_unipolar10;
		अवरोध;
	पूर्ण
	चयन (devpriv->dac1_range) अणु
	हाल dac_bipolar:
		devpriv->ao_range_type_list[1] = &range_bipolar10;
		अवरोध;
	हाल dac_unipolar:
		devpriv->ao_range_type_list[1] = &range_unipolar10;
		अवरोध;
	पूर्ण
	s->insn_ग_लिखो = aपंचांगio16d_ao_insn_ग_लिखो;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	/* Digital I/O */
	s = &dev->subdevices[2];
	s->type = COMEDI_SUBD_DIO;
	s->subdev_flags = SDF_WRITABLE | SDF_READABLE;
	s->n_chan = 8;
	s->insn_bits = aपंचांगio16d_dio_insn_bits;
	s->insn_config = aपंचांगio16d_dio_insn_config;
	s->maxdata = 1;
	s->range_table = &range_digital;

	/* 8255 subdevice */
	s = &dev->subdevices[3];
	अगर (board->has_8255) अणु
		ret = subdev_8255_init(dev, s, शून्य, 0x00);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		s->type = COMEDI_SUBD_UNUSED;
	पूर्ण

/* करोn't yet know how to deal with counter/समयrs */
#अगर 0
	s = &dev->subdevices[4];
	/* करो */
	s->type = COMEDI_SUBD_TIMER;
	s->n_chan = 0;
	s->maxdata = 0
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम aपंचांगio16d_detach(काष्ठा comedi_device *dev)
अणु
	reset_aपंचांगio16d(dev);
	comedi_legacy_detach(dev);
पूर्ण

अटल स्थिर काष्ठा aपंचांगio16_board_t aपंचांगio16_boards[] = अणु
	अणु
		.name		= "atmio16",
		.has_8255	= 0,
	पूर्ण, अणु
		.name		= "atmio16d",
		.has_8255	= 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा comedi_driver aपंचांगio16d_driver = अणु
	.driver_name	= "atmio16",
	.module		= THIS_MODULE,
	.attach		= aपंचांगio16d_attach,
	.detach		= aपंचांगio16d_detach,
	.board_name	= &aपंचांगio16_boards[0].name,
	.num_names	= ARRAY_SIZE(aपंचांगio16_boards),
	.offset		= माप(काष्ठा aपंचांगio16_board_t),
पूर्ण;
module_comedi_driver(aपंचांगio16d_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
