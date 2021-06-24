<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/drivers/s626.c
 * Sensoray s626 Comedi driver
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 *
 * Based on Sensoray Model 626 Linux driver Version 0.2
 * Copyright (C) 2002-2004 Sensoray Co., Inc.
 */

/*
 * Driver: s626
 * Description: Sensoray 626 driver
 * Devices: [Sensoray] 626 (s626)
 * Authors: Gianluca Palli <gpalli@deis.unibo.it>,
 * Updated: Fri, 15 Feb 2008 10:28:42 +0000
 * Status: experimental

 * Configuration options: not applicable, uses PCI स्वतः config

 * INSN_CONFIG inकाष्ठाions:
 *   analog input:
 *    none
 *
 *   analog output:
 *    none
 *
 *   digital channel:
 *    s626 has 3 dio subdevices (2,3 and 4) each with 16 i/o channels
 *    supported configuration options:
 *    INSN_CONFIG_DIO_QUERY
 *    COMEDI_INPUT
 *    COMEDI_OUTPUT
 *
 *   encoder:
 *    Every channel must be configured beक्रमe पढ़ोing.
 *
 *   Example code
 *
 *    insn.insn=INSN_CONFIG;   //configuration inकाष्ठाion
 *    insn.n=1;                //number of operation (must be 1)
 *    insn.data=&initialvalue; //initial value loaded पूर्णांकo encoder
 *                             //during configuration
 *    insn.subdev=5;           //encoder subdevice
 *    insn.chanspec=CR_PACK(encoder_channel,0,AREF_OTHER); //encoder_channel
 *                                                         //to configure
 *
 *    comedi_करो_insn(cf,&insn); //executing configuration
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>

#समावेश "../comedi_pci.h"

#समावेश "s626.h"

काष्ठा s626_buffer_dma अणु
	dma_addr_t physical_base;
	व्योम *logical_base;
पूर्ण;

/**
 * काष्ठा s626_निजी - Working data क्रम s626 driver.
 * @ai_cmd_running: non-zero अगर ai_cmd is running.
 * @ai_sample_समयr: समय between samples in units of the समयr.
 * @ai_convert_count: conversion counter.
 * @ai_convert_समयr: समय between conversion in units of the समयr.
 * @counter_पूर्णांक_enअसल: counter पूर्णांकerrupt enable mask क्रम MISC2 रेजिस्टर.
 * @adc_items: number of items in ADC poll list.
 * @rps_buf: DMA buffer used to hold ADC (RPS1) program.
 * @ana_buf:  DMA buffer used to receive ADC data and hold DAC data.
 * @dac_wbuf: poपूर्णांकer to logical adrs of DMA buffer used to hold DAC data.
 * @dacpol: image of DAC polarity रेजिस्टर.
 * @trim_setpoपूर्णांक: images of TrimDAC setpoपूर्णांकs.
 * @i2c_adrs: I2C device address क्रम onboard EEPROM (board rev dependent)
 */
काष्ठा s626_निजी अणु
	u8 ai_cmd_running;
	अचिन्हित पूर्णांक ai_sample_समयr;
	पूर्णांक ai_convert_count;
	अचिन्हित पूर्णांक ai_convert_समयr;
	u16 counter_पूर्णांक_enअसल;
	u8 adc_items;
	काष्ठा s626_buffer_dma rps_buf;
	काष्ठा s626_buffer_dma ana_buf;
	u32 *dac_wbuf;
	u16 dacpol;
	u8 trim_setpoपूर्णांक[12];
	u32 i2c_adrs;
पूर्ण;

/* Counter overflow/index event flag masks क्रम RDMISC2. */
#घोषणा S626_INDXMASK(C) (1 << (((C) > 2) ? ((C) * 2 - 1) : ((C) * 2 +  4)))
#घोषणा S626_OVERMASK(C) (1 << (((C) > 2) ? ((C) * 2 + 5) : ((C) * 2 + 10)))

/*
 * Enable/disable a function or test status bit(s) that are accessed
 * through Main Control Registers 1 or 2.
 */
अटल व्योम s626_mc_enable(काष्ठा comedi_device *dev,
			   अचिन्हित पूर्णांक cmd, अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित पूर्णांक val = (cmd << 16) | cmd;

	ग_लिखोl(val, dev->mmio + reg);
पूर्ण

अटल व्योम s626_mc_disable(काष्ठा comedi_device *dev,
			    अचिन्हित पूर्णांक cmd, अचिन्हित पूर्णांक reg)
अणु
	ग_लिखोl(cmd << 16, dev->mmio + reg);
पूर्ण

अटल bool s626_mc_test(काष्ठा comedi_device *dev,
			 अचिन्हित पूर्णांक cmd, अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित पूर्णांक val;

	val = पढ़ोl(dev->mmio + reg);

	वापस (val & cmd) ? true : false;
पूर्ण

#घोषणा S626_BUGFIX_STREG(REGADRS)   ((REGADRS) - 4)

/* Write a समय slot control record to TSL2. */
#घोषणा S626_VECTPORT(VECTNUM)		(S626_P_TSL2 + ((VECTNUM) << 2))

अटल स्थिर काष्ठा comedi_lrange s626_range_table = अणु
	2, अणु
		BIP_RANGE(5),
		BIP_RANGE(10)
	पूर्ण
पूर्ण;

/*
 * Execute a DEBI transfer.  This must be called from within a critical section.
 */
अटल व्योम s626_debi_transfer(काष्ठा comedi_device *dev)
अणु
	अटल स्थिर पूर्णांक समयout = 10000;
	पूर्णांक i;

	/* Initiate upload of shaकरोw RAM to DEBI control रेजिस्टर */
	s626_mc_enable(dev, S626_MC2_UPLD_DEBI, S626_P_MC2);

	/*
	 * Wait क्रम completion of upload from shaकरोw RAM to
	 * DEBI control रेजिस्टर.
	 */
	क्रम (i = 0; i < समयout; i++) अणु
		अगर (s626_mc_test(dev, S626_MC2_UPLD_DEBI, S626_P_MC2))
			अवरोध;
		udelay(1);
	पूर्ण
	अगर (i == समयout)
		dev_err(dev->class_dev,
			"Timeout while uploading to DEBI control register\n");

	/* Wait until DEBI transfer is करोne */
	क्रम (i = 0; i < समयout; i++) अणु
		अगर (!(पढ़ोl(dev->mmio + S626_P_PSR) & S626_PSR_DEBI_S))
			अवरोध;
		udelay(1);
	पूर्ण
	अगर (i == समयout)
		dev_err(dev->class_dev, "DEBI transfer timeout\n");
पूर्ण

/*
 * Read a value from a gate array रेजिस्टर.
 */
अटल u16 s626_debi_पढ़ो(काष्ठा comedi_device *dev, u16 addr)
अणु
	/* Set up DEBI control रेजिस्टर value in shaकरोw RAM */
	ग_लिखोl(S626_DEBI_CMD_RDWORD | addr, dev->mmio + S626_P_DEBICMD);

	/*  Execute the DEBI transfer. */
	s626_debi_transfer(dev);

	वापस पढ़ोl(dev->mmio + S626_P_DEBIAD);
पूर्ण

/*
 * Write a value to a gate array रेजिस्टर.
 */
अटल व्योम s626_debi_ग_लिखो(काष्ठा comedi_device *dev, u16 addr,
			    u16 wdata)
अणु
	/* Set up DEBI control रेजिस्टर value in shaकरोw RAM */
	ग_लिखोl(S626_DEBI_CMD_WRWORD | addr, dev->mmio + S626_P_DEBICMD);
	ग_लिखोl(wdata, dev->mmio + S626_P_DEBIAD);

	/*  Execute the DEBI transfer. */
	s626_debi_transfer(dev);
पूर्ण

/*
 * Replace the specअगरied bits in a gate array रेजिस्टर.  Imports: mask
 * specअगरies bits that are to be preserved, wdata is new value to be
 * or'd with the masked original.
 */
अटल व्योम s626_debi_replace(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक addr,
			      अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक wdata)
अणु
	अचिन्हित पूर्णांक val;

	addr &= 0xffff;
	ग_लिखोl(S626_DEBI_CMD_RDWORD | addr, dev->mmio + S626_P_DEBICMD);
	s626_debi_transfer(dev);

	ग_लिखोl(S626_DEBI_CMD_WRWORD | addr, dev->mmio + S626_P_DEBICMD);
	val = पढ़ोl(dev->mmio + S626_P_DEBIAD);
	val &= mask;
	val |= wdata;
	ग_लिखोl(val & 0xffff, dev->mmio + S626_P_DEBIAD);
	s626_debi_transfer(dev);
पूर्ण

/* **************  EEPROM ACCESS FUNCTIONS  ************** */

अटल पूर्णांक s626_i2c_handshake_eoc(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित दीर्घ context)
अणु
	bool status;

	status = s626_mc_test(dev, S626_MC2_UPLD_IIC, S626_P_MC2);
	अगर (status)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक s626_i2c_handshake(काष्ठा comedi_device *dev, u32 val)
अणु
	अचिन्हित पूर्णांक ctrl;
	पूर्णांक ret;

	/* Write I2C command to I2C Transfer Control shaकरोw रेजिस्टर */
	ग_लिखोl(val, dev->mmio + S626_P_I2CCTRL);

	/*
	 * Upload I2C shaकरोw रेजिस्टरs पूर्णांकo working रेजिस्टरs and
	 * रुको क्रम upload confirmation.
	 */
	s626_mc_enable(dev, S626_MC2_UPLD_IIC, S626_P_MC2);
	ret = comedi_समयout(dev, शून्य, शून्य, s626_i2c_handshake_eoc, 0);
	अगर (ret)
		वापस ret;

	/* Wait until I2C bus transfer is finished or an error occurs */
	करो अणु
		ctrl = पढ़ोl(dev->mmio + S626_P_I2CCTRL);
	पूर्ण जबतक ((ctrl & (S626_I2C_BUSY | S626_I2C_ERR)) == S626_I2C_BUSY);

	/* Return non-zero अगर I2C error occurred */
	वापस ctrl & S626_I2C_ERR;
पूर्ण

/* Read u8 from EEPROM. */
अटल u8 s626_i2c_पढ़ो(काष्ठा comedi_device *dev, u8 addr)
अणु
	काष्ठा s626_निजी *devpriv = dev->निजी;

	/*
	 * Send EEPROM target address:
	 *  Byte2 = I2C command: ग_लिखो to I2C EEPROM device.
	 *  Byte1 = EEPROM पूर्णांकernal target address.
	 *  Byte0 = Not sent.
	 */
	अगर (s626_i2c_handshake(dev, S626_I2C_B2(S626_I2C_ATTRSTART,
						devpriv->i2c_adrs) |
				    S626_I2C_B1(S626_I2C_ATTRSTOP, addr) |
				    S626_I2C_B0(S626_I2C_ATTRNOP, 0)))
		/* Abort function and declare error अगर handshake failed. */
		वापस 0;

	/*
	 * Execute EEPROM पढ़ो:
	 *  Byte2 = I2C command: पढ़ो from I2C EEPROM device.
	 *  Byte1 receives uपूर्णांक8_t from EEPROM.
	 *  Byte0 = Not sent.
	 */
	अगर (s626_i2c_handshake(dev, S626_I2C_B2(S626_I2C_ATTRSTART,
						(devpriv->i2c_adrs | 1)) |
				    S626_I2C_B1(S626_I2C_ATTRSTOP, 0) |
				    S626_I2C_B0(S626_I2C_ATTRNOP, 0)))
		/* Abort function and declare error अगर handshake failed. */
		वापस 0;

	वापस (पढ़ोl(dev->mmio + S626_P_I2CCTRL) >> 16) & 0xff;
पूर्ण

/* ***********  DAC FUNCTIONS *********** */

/* TrimDac LogicalChan-to-PhysicalChan mapping table. */
अटल स्थिर u8 s626_trimchan[] = अणु 10, 9, 8, 3, 2, 7, 6, 1, 0, 5, 4 पूर्ण;

/* TrimDac LogicalChan-to-EepromAdrs mapping table. */
अटल स्थिर u8 s626_trimadrs[] = अणु
	0x40, 0x41, 0x42, 0x50, 0x51, 0x52, 0x53, 0x60, 0x61, 0x62, 0x63
पूर्ण;

क्रमागत अणु
	s626_send_dac_रुको_not_mc1_a2out,
	s626_send_dac_रुको_ssr_af2_out,
	s626_send_dac_रुको_fb_buffer2_msb_00,
	s626_send_dac_रुको_fb_buffer2_msb_ff
पूर्ण;

अटल पूर्णांक s626_send_dac_eoc(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s,
			     काष्ठा comedi_insn *insn,
			     अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	चयन (context) अणु
	हाल s626_send_dac_रुको_not_mc1_a2out:
		status = पढ़ोl(dev->mmio + S626_P_MC1);
		अगर (!(status & S626_MC1_A2OUT))
			वापस 0;
		अवरोध;
	हाल s626_send_dac_रुको_ssr_af2_out:
		status = पढ़ोl(dev->mmio + S626_P_SSR);
		अगर (status & S626_SSR_AF2_OUT)
			वापस 0;
		अवरोध;
	हाल s626_send_dac_रुको_fb_buffer2_msb_00:
		status = पढ़ोl(dev->mmio + S626_P_FB_BUFFER2);
		अगर (!(status & 0xff000000))
			वापस 0;
		अवरोध;
	हाल s626_send_dac_रुको_fb_buffer2_msb_ff:
		status = पढ़ोl(dev->mmio + S626_P_FB_BUFFER2);
		अगर (status & 0xff000000)
			वापस 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस -EBUSY;
पूर्ण

/*
 * Private helper function: Transmit serial data to DAC via Audio
 * channel 2.  Assumes: (1) TSL2 slot records initialized, and (2)
 * dacpol contains valid target image.
 */
अटल पूर्णांक s626_send_dac(काष्ठा comedi_device *dev, u32 val)
अणु
	काष्ठा s626_निजी *devpriv = dev->निजी;
	पूर्णांक ret;

	/* START THE SERIAL CLOCK RUNNING ------------- */

	/*
	 * Assert DAC polarity control and enable gating of DAC serial घड़ी
	 * and audio bit stream संकेतs.  At this poपूर्णांक in समय we must be
	 * assured of being in समय slot 0.  If we are not in slot 0, the
	 * serial घड़ी and audio stream संकेतs will be disabled; this is
	 * because the following s626_debi_ग_लिखो statement (which enables
	 * संकेतs to be passed through the gate array) would execute beक्रमe
	 * the trailing edge of WS1/WS3 (which turns off the संकेतs), thus
	 * causing the संकेतs to be inactive during the DAC ग_लिखो.
	 */
	s626_debi_ग_लिखो(dev, S626_LP_DACPOL, devpriv->dacpol);

	/* TRANSFER OUTPUT DWORD VALUE INTO A2'S OUTPUT FIFO ---------------- */

	/* Copy DAC setpoपूर्णांक value to DAC's output DMA buffer. */
	/* ग_लिखोl(val, dev->mmio + (uपूर्णांक32_t)devpriv->dac_wbuf); */
	*devpriv->dac_wbuf = val;

	/*
	 * Enable the output DMA transfer. This will cause the DMAC to copy
	 * the DAC's data value to A2's output FIFO. The DMA transfer will
	 * then immediately terminate because the protection address is
	 * reached upon transfer of the first DWORD value.
	 */
	s626_mc_enable(dev, S626_MC1_A2OUT, S626_P_MC1);

	/* While the DMA transfer is executing ... */

	/*
	 * Reset Audio2 output FIFO's underflow flag (aदीर्घ with any
	 * other FIFO underflow/overflow flags). When set, this flag
	 * will indicate that we have emerged from slot 0.
	 */
	ग_लिखोl(S626_ISR_AFOU, dev->mmio + S626_P_ISR);

	/*
	 * Wait क्रम the DMA transfer to finish so that there will be data
	 * available in the FIFO when समय slot 1 tries to transfer a DWORD
	 * from the FIFO to the output buffer रेजिस्टर.  We test क्रम DMA
	 * Done by polling the DMAC enable flag; this flag is स्वतःmatically
	 * cleared when the transfer has finished.
	 */
	ret = comedi_समयout(dev, शून्य, शून्य, s626_send_dac_eoc,
			     s626_send_dac_रुको_not_mc1_a2out);
	अगर (ret) अणु
		dev_err(dev->class_dev, "DMA transfer timeout\n");
		वापस ret;
	पूर्ण

	/* START THE OUTPUT STREAM TO THE TARGET DAC -------------------- */

	/*
	 * FIFO data is now available, so we enable execution of समय slots
	 * 1 and higher by clearing the EOS flag in slot 0.  Note that SD3
	 * will be shअगरted in and stored in FB_BUFFER2 क्रम end-of-slot-list
	 * detection.
	 */
	ग_लिखोl(S626_XSD2 | S626_RSD3 | S626_SIB_A2,
	       dev->mmio + S626_VECTPORT(0));

	/*
	 * Wait क्रम slot 1 to execute to ensure that the Packet will be
	 * transmitted.  This is detected by polling the Audio2 output FIFO
	 * underflow flag, which will be set when slot 1 execution has
	 * finished transferring the DAC's data DWORD from the output FIFO
	 * to the output buffer रेजिस्टर.
	 */
	ret = comedi_समयout(dev, शून्य, शून्य, s626_send_dac_eoc,
			     s626_send_dac_रुको_ssr_af2_out);
	अगर (ret) अणु
		dev_err(dev->class_dev,
			"TSL timeout waiting for slot 1 to execute\n");
		वापस ret;
	पूर्ण

	/*
	 * Set up to trap execution at slot 0 when the TSL sequencer cycles
	 * back to slot 0 after executing the EOS in slot 5.  Also,
	 * simultaneously shअगरt out and in the 0x00 that is ALWAYS the value
	 * stored in the last byte to be shअगरted out of the FIFO's DWORD
	 * buffer रेजिस्टर.
	 */
	ग_लिखोl(S626_XSD2 | S626_XFIFO_2 | S626_RSD2 | S626_SIB_A2 | S626_EOS,
	       dev->mmio + S626_VECTPORT(0));

	/* WAIT FOR THE TRANSACTION TO FINISH ----------------------- */

	/*
	 * Wait क्रम the TSL to finish executing all समय slots beक्रमe
	 * निकासing this function.  We must करो this so that the next DAC
	 * ग_लिखो करोesn't start, thereby enabling घड़ी/chip select संकेतs:
	 *
	 * 1. Beक्रमe the TSL sequence cycles back to slot 0, which disables
	 *    the घड़ी/cs संकेत gating and traps slot // list execution.
	 *    we have not yet finished slot 5 then the घड़ी/cs संकेतs are
	 *    still gated and we have not finished transmitting the stream.
	 *
	 * 2. While slots 2-5 are executing due to a late slot 0 trap.  In
	 *    this हाल, the slot sequence is currently repeating, but with
	 *    घड़ी/cs संकेतs disabled.  We must रुको क्रम slot 0 to trap
	 *    execution beक्रमe setting up the next DAC setpoपूर्णांक DMA transfer
	 *    and enabling the घड़ी/cs संकेतs.  To detect the end of slot 5,
	 *    we test क्रम the FB_BUFFER2 MSB contents to be equal to 0xFF.  If
	 *    the TSL has not yet finished executing slot 5 ...
	 */
	अगर (पढ़ोl(dev->mmio + S626_P_FB_BUFFER2) & 0xff000000) अणु
		/*
		 * The trap was set on समय and we are still executing somewhere
		 * in slots 2-5, so we now रुको क्रम slot 0 to execute and trap
		 * TSL execution.  This is detected when FB_BUFFER2 MSB changes
		 * from 0xFF to 0x00, which slot 0 causes to happen by shअगरting
		 * out/in on SD2 the 0x00 that is always referenced by slot 5.
		 */
		ret = comedi_समयout(dev, शून्य, शून्य, s626_send_dac_eoc,
				     s626_send_dac_रुको_fb_buffer2_msb_00);
		अगर (ret) अणु
			dev_err(dev->class_dev,
				"TSL timeout waiting for slot 0 to execute\n");
			वापस ret;
		पूर्ण
	पूर्ण
	/*
	 * Either (1) we were too late setting the slot 0 trap; the TSL
	 * sequencer restarted slot 0 beक्रमe we could set the EOS trap flag,
	 * or (2) we were not late and execution is now trapped at slot 0.
	 * In either हाल, we must now change slot 0 so that it will store
	 * value 0xFF (instead of 0x00) to FB_BUFFER2 next समय it executes.
	 * In order to करो this, we reprogram slot 0 so that it will shअगरt in
	 * SD3, which is driven only by a pull-up resistor.
	 */
	ग_लिखोl(S626_RSD3 | S626_SIB_A2 | S626_EOS,
	       dev->mmio + S626_VECTPORT(0));

	/*
	 * Wait क्रम slot 0 to execute, at which समय the TSL is setup क्रम
	 * the next DAC ग_लिखो.  This is detected when FB_BUFFER2 MSB changes
	 * from 0x00 to 0xFF.
	 */
	ret = comedi_समयout(dev, शून्य, शून्य, s626_send_dac_eoc,
			     s626_send_dac_रुको_fb_buffer2_msb_ff);
	अगर (ret) अणु
		dev_err(dev->class_dev,
			"TSL timeout waiting for slot 0 to execute\n");
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Private helper function: Write setpoपूर्णांक to an application DAC channel.
 */
अटल पूर्णांक s626_set_dac(काष्ठा comedi_device *dev,
			u16 chan, पूर्णांक16_t dacdata)
अणु
	काष्ठा s626_निजी *devpriv = dev->निजी;
	u16 signmask;
	u32 ws_image;
	u32 val;

	/*
	 * Adjust DAC data polarity and set up Polarity Control Register image.
	 */
	signmask = 1 << chan;
	अगर (dacdata < 0) अणु
		dacdata = -dacdata;
		devpriv->dacpol |= signmask;
	पूर्ण अन्यथा अणु
		devpriv->dacpol &= ~signmask;
	पूर्ण

	/* Limit DAC setpoपूर्णांक value to valid range. */
	अगर ((u16)dacdata > 0x1FFF)
		dacdata = 0x1FFF;

	/*
	 * Set up TSL2 records (aka "vectors") क्रम DAC update.  Vectors V2
	 * and V3 transmit the setpoपूर्णांक to the target DAC.  V4 and V5 send
	 * data to a non-existent TrimDac channel just to keep the घड़ी
	 * running after sending data to the target DAC.  This is necessary
	 * to eliminate the घड़ी glitch that would otherwise occur at the
	 * end of the target DAC's serial data stream.  When the sequence
	 * restarts at V0 (after executing V5), the gate array स्वतःmatically
	 * disables gating क्रम the DAC घड़ी and all DAC chip selects.
	 */

	/* Choose DAC chip select to be निश्चितed */
	ws_image = (chan & 2) ? S626_WS1 : S626_WS2;
	/* Slot 2: Transmit high data byte to target DAC */
	ग_लिखोl(S626_XSD2 | S626_XFIFO_1 | ws_image,
	       dev->mmio + S626_VECTPORT(2));
	/* Slot 3: Transmit low data byte to target DAC */
	ग_लिखोl(S626_XSD2 | S626_XFIFO_0 | ws_image,
	       dev->mmio + S626_VECTPORT(3));
	/* Slot 4: Transmit to non-existent TrimDac channel to keep घड़ी */
	ग_लिखोl(S626_XSD2 | S626_XFIFO_3 | S626_WS3,
	       dev->mmio + S626_VECTPORT(4));
	/* Slot 5: running after writing target DAC's low data byte */
	ग_लिखोl(S626_XSD2 | S626_XFIFO_2 | S626_WS3 | S626_EOS,
	       dev->mmio + S626_VECTPORT(5));

	/*
	 * Conकाष्ठा and transmit target DAC's serial packet:
	 * (A10D DDDD), (DDDD DDDD), (0x0F), (0x00) where A is chan<0>,
	 * and D<12:0> is the DAC setpoपूर्णांक.  Append a WORD value (that ग_लिखोs
	 * to a  non-existent TrimDac channel) that serves to keep the घड़ी
	 * running after the packet has been sent to the target DAC.
	 */
	val = 0x0F000000;	/* Continue घड़ी after target DAC data
				 * (ग_लिखो to non-existent trimdac).
				 */
	val |= 0x00004000;	/* Address the two मुख्य dual-DAC devices
				 * (TSL's chip select enables target device).
				 */
	val |= ((u32)(chan & 1) << 15);	/* Address the DAC channel
					 * within the device.
					 */
	val |= (u32)dacdata;	/* Include DAC setpoपूर्णांक data. */
	वापस s626_send_dac(dev, val);
पूर्ण

अटल पूर्णांक s626_ग_लिखो_trim_dac(काष्ठा comedi_device *dev,
			       u8 logical_chan, u8 dac_data)
अणु
	काष्ठा s626_निजी *devpriv = dev->निजी;
	u32 chan;

	/*
	 * Save the new setpoपूर्णांक in हाल the application needs to पढ़ो it back
	 * later.
	 */
	devpriv->trim_setpoपूर्णांक[logical_chan] = dac_data;

	/* Map logical channel number to physical channel number. */
	chan = s626_trimchan[logical_chan];

	/*
	 * Set up TSL2 records क्रम TrimDac ग_लिखो operation.  All slots shअगरt
	 * 0xFF in from pulled-up SD3 so that the end of the slot sequence
	 * can be detected.
	 */

	/* Slot 2: Send high uपूर्णांक8_t to target TrimDac */
	ग_लिखोl(S626_XSD2 | S626_XFIFO_1 | S626_WS3,
	       dev->mmio + S626_VECTPORT(2));
	/* Slot 3: Send low uपूर्णांक8_t to target TrimDac */
	ग_लिखोl(S626_XSD2 | S626_XFIFO_0 | S626_WS3,
	       dev->mmio + S626_VECTPORT(3));
	/* Slot 4: Send NOP high uपूर्णांक8_t to DAC0 to keep घड़ी running */
	ग_लिखोl(S626_XSD2 | S626_XFIFO_3 | S626_WS1,
	       dev->mmio + S626_VECTPORT(4));
	/* Slot 5: Send NOP low  uपूर्णांक8_t to DAC0 */
	ग_लिखोl(S626_XSD2 | S626_XFIFO_2 | S626_WS1 | S626_EOS,
	       dev->mmio + S626_VECTPORT(5));

	/*
	 * Conकाष्ठा and transmit target DAC's serial packet:
	 * (0000 AAAA), (DDDD DDDD), (0x00), (0x00) where A<3:0> is the
	 * DAC channel's address, and D<7:0> is the DAC setpoपूर्णांक.  Append a
	 * WORD value (that ग_लिखोs a channel 0 NOP command to a non-existent
	 * मुख्य DAC channel) that serves to keep the घड़ी running after the
	 * packet has been sent to the target DAC.
	 */

	/*
	 * Address the DAC channel within the trimdac device.
	 * Include DAC setpoपूर्णांक data.
	 */
	वापस s626_send_dac(dev, (chan << 8) | dac_data);
पूर्ण

अटल पूर्णांक s626_load_trim_dacs(काष्ठा comedi_device *dev)
अणु
	u8 i;
	पूर्णांक ret;

	/* Copy TrimDac setpoपूर्णांक values from EEPROM to TrimDacs. */
	क्रम (i = 0; i < ARRAY_SIZE(s626_trimchan); i++) अणु
		ret = s626_ग_लिखो_trim_dac(dev, i,
					  s626_i2c_पढ़ो(dev, s626_trimadrs[i]));
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/* ******  COUNTER FUNCTIONS  ******* */

/*
 * All counter functions address a specअगरic counter by means of the
 * "Counter" argument, which is a logical counter number.  The Counter
 * argument may have any of the following legal values: 0=0A, 1=1A,
 * 2=2A, 3=0B, 4=1B, 5=2B.
 */

/*
 * Return/set a counter pair's latch trigger source.  0: On पढ़ो
 * access, 1: A index latches A, 2: B index latches B, 3: A overflow
 * latches B.
 */
अटल व्योम s626_set_latch_source(काष्ठा comedi_device *dev,
				  अचिन्हित पूर्णांक chan, u16 value)
अणु
	s626_debi_replace(dev, S626_LP_CRB(chan),
			  ~(S626_CRBMSK_INTCTRL | S626_CRBMSK_LATCHSRC),
			  S626_SET_CRB_LATCHSRC(value));
पूर्ण

/*
 * Write value पूर्णांकo counter preload रेजिस्टर.
 */
अटल व्योम s626_preload(काष्ठा comedi_device *dev,
			 अचिन्हित पूर्णांक chan, u32 value)
अणु
	s626_debi_ग_लिखो(dev, S626_LP_CNTR(chan), value);
	s626_debi_ग_लिखो(dev, S626_LP_CNTR(chan) + 2, value >> 16);
पूर्ण

/* ******  PRIVATE COUNTER FUNCTIONS ****** */

/*
 * Reset a counter's index and overflow event capture flags.
 */
अटल व्योम s626_reset_cap_flags(काष्ठा comedi_device *dev,
				 अचिन्हित पूर्णांक chan)
अणु
	u16 set;

	set = S626_SET_CRB_INTRESETCMD(1);
	अगर (chan < 3)
		set |= S626_SET_CRB_INTRESET_A(1);
	अन्यथा
		set |= S626_SET_CRB_INTRESET_B(1);

	s626_debi_replace(dev, S626_LP_CRB(chan), ~S626_CRBMSK_INTCTRL, set);
पूर्ण

/*
 * Set the operating mode क्रम the specअगरied counter.  The setup
 * parameter is treated as a COUNTER_SETUP data type.  The following
 * parameters are programmable (all other parms are ignored): ClkMult,
 * ClkPol, ClkEnab, IndexSrc, IndexPol, LoadSrc.
 */
अटल व्योम s626_set_mode_a(काष्ठा comedi_device *dev,
			    अचिन्हित पूर्णांक chan, u16 setup,
			    u16 disable_पूर्णांक_src)
अणु
	काष्ठा s626_निजी *devpriv = dev->निजी;
	u16 cra;
	u16 crb;
	अचिन्हित पूर्णांक cntsrc, clkmult, clkpol;

	/* Initialize CRA and CRB images. */
	/* Preload trigger is passed through. */
	cra = S626_SET_CRA_LOADSRC_A(S626_GET_STD_LOADSRC(setup));
	/* IndexSrc is passed through. */
	cra |= S626_SET_CRA_INDXSRC_A(S626_GET_STD_INDXSRC(setup));

	/* Reset any pending CounterA event captures. */
	crb = S626_SET_CRB_INTRESETCMD(1) | S626_SET_CRB_INTRESET_A(1);
	/* Clock enable is passed through. */
	crb |= S626_SET_CRB_CLKENAB_A(S626_GET_STD_CLKENAB(setup));

	/* Force IntSrc to Disabled अगर disable_पूर्णांक_src is निश्चितed. */
	अगर (!disable_पूर्णांक_src)
		cra |= S626_SET_CRA_INTSRC_A(S626_GET_STD_INTSRC(setup));

	/* Populate all mode-dependent attributes of CRA & CRB images. */
	clkpol = S626_GET_STD_CLKPOL(setup);
	चयन (S626_GET_STD_ENCMODE(setup)) अणु
	हाल S626_ENCMODE_EXTENDER: /* Extender Mode: */
		/* Force to Timer mode (Extender valid only क्रम B counters). */
		/* Fall through to हाल S626_ENCMODE_TIMER: */
	हाल S626_ENCMODE_TIMER:	/* Timer Mode: */
		/* CntSrcA<1> selects प्रणाली घड़ी */
		cntsrc = S626_CNTSRC_SYSCLK;
		/* Count direction (CntSrcA<0>) obtained from ClkPol. */
		cntsrc |= clkpol;
		/* ClkPolA behaves as always-on घड़ी enable. */
		clkpol = 1;
		/* ClkMult must be 1x. */
		clkmult = S626_CLKMULT_1X;
		अवरोध;
	शेष:		/* Counter Mode: */
		/* Select ENC_C and ENC_D as घड़ी/direction inमाला_दो. */
		cntsrc = S626_CNTSRC_ENCODER;
		/* Clock polarity is passed through. */
		/* Force multiplier to x1 अगर not legal, अन्यथा pass through. */
		clkmult = S626_GET_STD_CLKMULT(setup);
		अगर (clkmult == S626_CLKMULT_SPECIAL)
			clkmult = S626_CLKMULT_1X;
		अवरोध;
	पूर्ण
	cra |= S626_SET_CRA_CNTSRC_A(cntsrc) | S626_SET_CRA_CLKPOL_A(clkpol) |
	       S626_SET_CRA_CLKMULT_A(clkmult);

	/*
	 * Force positive index polarity अगर IndxSrc is software-driven only,
	 * otherwise pass it through.
	 */
	अगर (S626_GET_STD_INDXSRC(setup) != S626_INDXSRC_SOFT)
		cra |= S626_SET_CRA_INDXPOL_A(S626_GET_STD_INDXPOL(setup));

	/*
	 * If IntSrc has been क्रमced to Disabled, update the MISC2 पूर्णांकerrupt
	 * enable mask to indicate the counter पूर्णांकerrupt is disabled.
	 */
	अगर (disable_पूर्णांक_src)
		devpriv->counter_पूर्णांक_enअसल &= ~(S626_OVERMASK(chan) |
						S626_INDXMASK(chan));

	/*
	 * While retaining CounterB and LatchSrc configurations, program the
	 * new counter operating mode.
	 */
	s626_debi_replace(dev, S626_LP_CRA(chan),
			  S626_CRAMSK_INDXSRC_B | S626_CRAMSK_CNTSRC_B, cra);
	s626_debi_replace(dev, S626_LP_CRB(chan),
			  ~(S626_CRBMSK_INTCTRL | S626_CRBMSK_CLKENAB_A), crb);
पूर्ण

अटल व्योम s626_set_mode_b(काष्ठा comedi_device *dev,
			    अचिन्हित पूर्णांक chan, u16 setup,
			    u16 disable_पूर्णांक_src)
अणु
	काष्ठा s626_निजी *devpriv = dev->निजी;
	u16 cra;
	u16 crb;
	अचिन्हित पूर्णांक cntsrc, clkmult, clkpol;

	/* Initialize CRA and CRB images. */
	/* IndexSrc is passed through. */
	cra = S626_SET_CRA_INDXSRC_B(S626_GET_STD_INDXSRC(setup));

	/* Reset event captures and disable पूर्णांकerrupts. */
	crb = S626_SET_CRB_INTRESETCMD(1) | S626_SET_CRB_INTRESET_B(1);
	/* Clock enable is passed through. */
	crb |= S626_SET_CRB_CLKENAB_B(S626_GET_STD_CLKENAB(setup));
	/* Preload trigger source is passed through. */
	crb |= S626_SET_CRB_LOADSRC_B(S626_GET_STD_LOADSRC(setup));

	/* Force IntSrc to Disabled अगर disable_पूर्णांक_src is निश्चितed. */
	अगर (!disable_पूर्णांक_src)
		crb |= S626_SET_CRB_INTSRC_B(S626_GET_STD_INTSRC(setup));

	/* Populate all mode-dependent attributes of CRA & CRB images. */
	clkpol = S626_GET_STD_CLKPOL(setup);
	चयन (S626_GET_STD_ENCMODE(setup)) अणु
	हाल S626_ENCMODE_TIMER:	/* Timer Mode: */
		/* CntSrcB<1> selects प्रणाली घड़ी */
		cntsrc = S626_CNTSRC_SYSCLK;
		/* with direction (CntSrcB<0>) obtained from ClkPol. */
		cntsrc |= clkpol;
		/* ClkPolB behaves as always-on घड़ी enable. */
		clkpol = 1;
		/* ClkMultB must be 1x. */
		clkmult = S626_CLKMULT_1X;
		अवरोध;
	हाल S626_ENCMODE_EXTENDER:	/* Extender Mode: */
		/* CntSrcB source is OverflowA (same as "timer") */
		cntsrc = S626_CNTSRC_SYSCLK;
		/* with direction obtained from ClkPol. */
		cntsrc |= clkpol;
		/* ClkPolB controls IndexB -- always set to active. */
		clkpol = 1;
		/* ClkMultB selects OverflowA as the घड़ी source. */
		clkmult = S626_CLKMULT_SPECIAL;
		अवरोध;
	शेष:		/* Counter Mode: */
		/* Select ENC_C and ENC_D as घड़ी/direction inमाला_दो. */
		cntsrc = S626_CNTSRC_ENCODER;
		/* ClkPol is passed through. */
		/* Force ClkMult to x1 अगर not legal, otherwise pass through. */
		clkmult = S626_GET_STD_CLKMULT(setup);
		अगर (clkmult == S626_CLKMULT_SPECIAL)
			clkmult = S626_CLKMULT_1X;
		अवरोध;
	पूर्ण
	cra |= S626_SET_CRA_CNTSRC_B(cntsrc);
	crb |= S626_SET_CRB_CLKPOL_B(clkpol) | S626_SET_CRB_CLKMULT_B(clkmult);

	/*
	 * Force positive index polarity अगर IndxSrc is software-driven only,
	 * otherwise pass it through.
	 */
	अगर (S626_GET_STD_INDXSRC(setup) != S626_INDXSRC_SOFT)
		crb |= S626_SET_CRB_INDXPOL_B(S626_GET_STD_INDXPOL(setup));

	/*
	 * If IntSrc has been क्रमced to Disabled, update the MISC2 पूर्णांकerrupt
	 * enable mask to indicate the counter पूर्णांकerrupt is disabled.
	 */
	अगर (disable_पूर्णांक_src)
		devpriv->counter_पूर्णांक_enअसल &= ~(S626_OVERMASK(chan) |
						S626_INDXMASK(chan));

	/*
	 * While retaining CounterA and LatchSrc configurations, program the
	 * new counter operating mode.
	 */
	s626_debi_replace(dev, S626_LP_CRA(chan),
			  ~(S626_CRAMSK_INDXSRC_B | S626_CRAMSK_CNTSRC_B), cra);
	s626_debi_replace(dev, S626_LP_CRB(chan),
			  S626_CRBMSK_CLKENAB_A | S626_CRBMSK_LATCHSRC, crb);
पूर्ण

अटल व्योम s626_set_mode(काष्ठा comedi_device *dev,
			  अचिन्हित पूर्णांक chan,
			  u16 setup, u16 disable_पूर्णांक_src)
अणु
	अगर (chan < 3)
		s626_set_mode_a(dev, chan, setup, disable_पूर्णांक_src);
	अन्यथा
		s626_set_mode_b(dev, chan, setup, disable_पूर्णांक_src);
पूर्ण

/*
 * Return/set a counter's enable.  enab: 0=always enabled, 1=enabled by index.
 */
अटल व्योम s626_set_enable(काष्ठा comedi_device *dev,
			    अचिन्हित पूर्णांक chan, u16 enab)
अणु
	अचिन्हित पूर्णांक mask = S626_CRBMSK_INTCTRL;
	अचिन्हित पूर्णांक set;

	अगर (chan < 3) अणु
		mask |= S626_CRBMSK_CLKENAB_A;
		set = S626_SET_CRB_CLKENAB_A(enab);
	पूर्ण अन्यथा अणु
		mask |= S626_CRBMSK_CLKENAB_B;
		set = S626_SET_CRB_CLKENAB_B(enab);
	पूर्ण
	s626_debi_replace(dev, S626_LP_CRB(chan), ~mask, set);
पूर्ण

/*
 * Return/set the event that will trigger transfer of the preload
 * रेजिस्टर पूर्णांकo the counter.  0=ThisCntr_Index, 1=ThisCntr_Overflow,
 * 2=OverflowA (B counters only), 3=disabled.
 */
अटल व्योम s626_set_load_trig(काष्ठा comedi_device *dev,
			       अचिन्हित पूर्णांक chan, u16 trig)
अणु
	u16 reg;
	u16 mask;
	u16 set;

	अगर (chan < 3) अणु
		reg = S626_LP_CRA(chan);
		mask = S626_CRAMSK_LOADSRC_A;
		set = S626_SET_CRA_LOADSRC_A(trig);
	पूर्ण अन्यथा अणु
		reg = S626_LP_CRB(chan);
		mask = S626_CRBMSK_LOADSRC_B | S626_CRBMSK_INTCTRL;
		set = S626_SET_CRB_LOADSRC_B(trig);
	पूर्ण
	s626_debi_replace(dev, reg, ~mask, set);
पूर्ण

/*
 * Return/set counter पूर्णांकerrupt source and clear any captured
 * index/overflow events.  पूर्णांक_source: 0=Disabled, 1=OverflowOnly,
 * 2=IndexOnly, 3=IndexAndOverflow.
 */
अटल व्योम s626_set_पूर्णांक_src(काष्ठा comedi_device *dev,
			     अचिन्हित पूर्णांक chan, u16 पूर्णांक_source)
अणु
	काष्ठा s626_निजी *devpriv = dev->निजी;
	u16 cra_reg = S626_LP_CRA(chan);
	u16 crb_reg = S626_LP_CRB(chan);

	अगर (chan < 3) अणु
		/* Reset any pending counter overflow or index captures */
		s626_debi_replace(dev, crb_reg, ~S626_CRBMSK_INTCTRL,
				  S626_SET_CRB_INTRESETCMD(1) |
				  S626_SET_CRB_INTRESET_A(1));

		/* Program counter पूर्णांकerrupt source */
		s626_debi_replace(dev, cra_reg, ~S626_CRAMSK_INTSRC_A,
				  S626_SET_CRA_INTSRC_A(पूर्णांक_source));
	पूर्ण अन्यथा अणु
		u16 crb;

		/* Cache ग_लिखोable CRB रेजिस्टर image */
		crb = s626_debi_पढ़ो(dev, crb_reg);
		crb &= ~S626_CRBMSK_INTCTRL;

		/* Reset any pending counter overflow or index captures */
		s626_debi_ग_लिखो(dev, crb_reg,
				crb | S626_SET_CRB_INTRESETCMD(1) |
				S626_SET_CRB_INTRESET_B(1));

		/* Program counter पूर्णांकerrupt source */
		s626_debi_ग_लिखो(dev, crb_reg,
				(crb & ~S626_CRBMSK_INTSRC_B) |
				S626_SET_CRB_INTSRC_B(पूर्णांक_source));
	पूर्ण

	/* Update MISC2 पूर्णांकerrupt enable mask. */
	devpriv->counter_पूर्णांक_enअसल &= ~(S626_OVERMASK(chan) |
					S626_INDXMASK(chan));
	चयन (पूर्णांक_source) अणु
	हाल 0:
	शेष:
		अवरोध;
	हाल 1:
		devpriv->counter_पूर्णांक_enअसल |= S626_OVERMASK(chan);
		अवरोध;
	हाल 2:
		devpriv->counter_पूर्णांक_enअसल |= S626_INDXMASK(chan);
		अवरोध;
	हाल 3:
		devpriv->counter_पूर्णांक_enअसल |= (S626_OVERMASK(chan) |
					       S626_INDXMASK(chan));
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Generate an index pulse.
 */
अटल व्योम s626_pulse_index(काष्ठा comedi_device *dev,
			     अचिन्हित पूर्णांक chan)
अणु
	अगर (chan < 3) अणु
		u16 cra;

		cra = s626_debi_पढ़ो(dev, S626_LP_CRA(chan));

		/* Pulse index */
		s626_debi_ग_लिखो(dev, S626_LP_CRA(chan),
				(cra ^ S626_CRAMSK_INDXPOL_A));
		s626_debi_ग_लिखो(dev, S626_LP_CRA(chan), cra);
	पूर्ण अन्यथा अणु
		u16 crb;

		crb = s626_debi_पढ़ो(dev, S626_LP_CRB(chan));
		crb &= ~S626_CRBMSK_INTCTRL;

		/* Pulse index */
		s626_debi_ग_लिखो(dev, S626_LP_CRB(chan),
				(crb ^ S626_CRBMSK_INDXPOL_B));
		s626_debi_ग_लिखो(dev, S626_LP_CRB(chan), crb);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक s626_ai_reg_to_uपूर्णांक(अचिन्हित पूर्णांक data)
अणु
	वापस ((data >> 18) & 0x3fff) ^ 0x2000;
पूर्ण

अटल पूर्णांक s626_dio_set_irq(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक chan)
अणु
	अचिन्हित पूर्णांक group = chan / 16;
	अचिन्हित पूर्णांक mask = 1 << (chan - (16 * group));
	अचिन्हित पूर्णांक status;

	/* set channel to capture positive edge */
	status = s626_debi_पढ़ो(dev, S626_LP_RDEDGSEL(group));
	s626_debi_ग_लिखो(dev, S626_LP_WREDGSEL(group), mask | status);

	/* enable पूर्णांकerrupt on selected channel */
	status = s626_debi_पढ़ो(dev, S626_LP_RDINTSEL(group));
	s626_debi_ग_लिखो(dev, S626_LP_WRINTSEL(group), mask | status);

	/* enable edge capture ग_लिखो command */
	s626_debi_ग_लिखो(dev, S626_LP_MISC1, S626_MISC1_EDCAP);

	/* enable edge capture on selected channel */
	status = s626_debi_पढ़ो(dev, S626_LP_RDCAPSEL(group));
	s626_debi_ग_लिखो(dev, S626_LP_WRCAPSEL(group), mask | status);

	वापस 0;
पूर्ण

अटल पूर्णांक s626_dio_reset_irq(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक group,
			      अचिन्हित पूर्णांक mask)
अणु
	/* disable edge capture ग_लिखो command */
	s626_debi_ग_लिखो(dev, S626_LP_MISC1, S626_MISC1_NOEDCAP);

	/* enable edge capture on selected channel */
	s626_debi_ग_लिखो(dev, S626_LP_WRCAPSEL(group), mask);

	वापस 0;
पूर्ण

अटल पूर्णांक s626_dio_clear_irq(काष्ठा comedi_device *dev)
अणु
	अचिन्हित पूर्णांक group;

	/* disable edge capture ग_लिखो command */
	s626_debi_ग_लिखो(dev, S626_LP_MISC1, S626_MISC1_NOEDCAP);

	/* clear all dio pending events and पूर्णांकerrupt */
	क्रम (group = 0; group < S626_DIO_BANKS; group++)
		s626_debi_ग_लिखो(dev, S626_LP_WRCAPSEL(group), 0xffff);

	वापस 0;
पूर्ण

अटल व्योम s626_handle_dio_पूर्णांकerrupt(काष्ठा comedi_device *dev,
				      u16 irqbit, u8 group)
अणु
	काष्ठा s626_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;

	s626_dio_reset_irq(dev, group, irqbit);

	अगर (devpriv->ai_cmd_running) अणु
		/* check अगर पूर्णांकerrupt is an ai acquisition start trigger */
		अगर ((irqbit >> (cmd->start_arg - (16 * group))) == 1 &&
		    cmd->start_src == TRIG_EXT) अणु
			/* Start executing the RPS program */
			s626_mc_enable(dev, S626_MC1_ERPS1, S626_P_MC1);

			अगर (cmd->scan_begin_src == TRIG_EXT)
				s626_dio_set_irq(dev, cmd->scan_begin_arg);
		पूर्ण
		अगर ((irqbit >> (cmd->scan_begin_arg - (16 * group))) == 1 &&
		    cmd->scan_begin_src == TRIG_EXT) अणु
			/* Trigger ADC scan loop start */
			s626_mc_enable(dev, S626_MC2_ADC_RPS, S626_P_MC2);

			अगर (cmd->convert_src == TRIG_EXT) अणु
				devpriv->ai_convert_count = cmd->chanlist_len;

				s626_dio_set_irq(dev, cmd->convert_arg);
			पूर्ण

			अगर (cmd->convert_src == TRIG_TIMER) अणु
				devpriv->ai_convert_count = cmd->chanlist_len;
				s626_set_enable(dev, 5, S626_CLKENAB_ALWAYS);
			पूर्ण
		पूर्ण
		अगर ((irqbit >> (cmd->convert_arg - (16 * group))) == 1 &&
		    cmd->convert_src == TRIG_EXT) अणु
			/* Trigger ADC scan loop start */
			s626_mc_enable(dev, S626_MC2_ADC_RPS, S626_P_MC2);

			devpriv->ai_convert_count--;
			अगर (devpriv->ai_convert_count > 0)
				s626_dio_set_irq(dev, cmd->convert_arg);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम s626_check_dio_पूर्णांकerrupts(काष्ठा comedi_device *dev)
अणु
	u16 irqbit;
	u8 group;

	क्रम (group = 0; group < S626_DIO_BANKS; group++) अणु
		/* पढ़ो पूर्णांकerrupt type */
		irqbit = s626_debi_पढ़ो(dev, S626_LP_RDCAPFLG(group));

		/* check अगर पूर्णांकerrupt is generated from dio channels */
		अगर (irqbit) अणु
			s626_handle_dio_पूर्णांकerrupt(dev, irqbit, group);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम s626_check_counter_पूर्णांकerrupts(काष्ठा comedi_device *dev)
अणु
	काष्ठा s626_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	u16 irqbit;

	/* पढ़ो पूर्णांकerrupt type */
	irqbit = s626_debi_पढ़ो(dev, S626_LP_RDMISC2);

	/* check पूर्णांकerrupt on counters */
	अगर (irqbit & S626_IRQ_COINT1A) अणु
		/* clear पूर्णांकerrupt capture flag */
		s626_reset_cap_flags(dev, 0);
	पूर्ण
	अगर (irqbit & S626_IRQ_COINT2A) अणु
		/* clear पूर्णांकerrupt capture flag */
		s626_reset_cap_flags(dev, 1);
	पूर्ण
	अगर (irqbit & S626_IRQ_COINT3A) अणु
		/* clear पूर्णांकerrupt capture flag */
		s626_reset_cap_flags(dev, 2);
	पूर्ण
	अगर (irqbit & S626_IRQ_COINT1B) अणु
		/* clear पूर्णांकerrupt capture flag */
		s626_reset_cap_flags(dev, 3);
	पूर्ण
	अगर (irqbit & S626_IRQ_COINT2B) अणु
		/* clear पूर्णांकerrupt capture flag */
		s626_reset_cap_flags(dev, 4);

		अगर (devpriv->ai_convert_count > 0) अणु
			devpriv->ai_convert_count--;
			अगर (devpriv->ai_convert_count == 0)
				s626_set_enable(dev, 4, S626_CLKENAB_INDEX);

			अगर (cmd->convert_src == TRIG_TIMER) अणु
				/* Trigger ADC scan loop start */
				s626_mc_enable(dev, S626_MC2_ADC_RPS,
					       S626_P_MC2);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (irqbit & S626_IRQ_COINT3B) अणु
		/* clear पूर्णांकerrupt capture flag */
		s626_reset_cap_flags(dev, 5);

		अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
			/* Trigger ADC scan loop start */
			s626_mc_enable(dev, S626_MC2_ADC_RPS, S626_P_MC2);
		पूर्ण

		अगर (cmd->convert_src == TRIG_TIMER) अणु
			devpriv->ai_convert_count = cmd->chanlist_len;
			s626_set_enable(dev, 4, S626_CLKENAB_ALWAYS);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool s626_handle_eos_पूर्णांकerrupt(काष्ठा comedi_device *dev)
अणु
	काष्ठा s626_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	/*
	 * Init ptr to DMA buffer that holds new ADC data.  We skip the
	 * first uपूर्णांक16_t in the buffer because it contains junk data
	 * from the final ADC of the previous poll list scan.
	 */
	u32 *पढ़ोaddr = (u32 *)devpriv->ana_buf.logical_base + 1;
	पूर्णांक i;

	/* get the data and hand it over to comedi */
	क्रम (i = 0; i < cmd->chanlist_len; i++) अणु
		अचिन्हित लघु tempdata;

		/*
		 * Convert ADC data to 16-bit पूर्णांकeger values and copy
		 * to application buffer.
		 */
		tempdata = s626_ai_reg_to_uपूर्णांक(*पढ़ोaddr);
		पढ़ोaddr++;

		comedi_buf_ग_लिखो_samples(s, &tempdata, 1);
	पूर्ण

	अगर (cmd->stop_src == TRIG_COUNT && async->scans_करोne >= cmd->stop_arg)
		async->events |= COMEDI_CB_EOA;

	अगर (async->events & COMEDI_CB_CANCEL_MASK)
		devpriv->ai_cmd_running = 0;

	अगर (devpriv->ai_cmd_running && cmd->scan_begin_src == TRIG_EXT)
		s626_dio_set_irq(dev, cmd->scan_begin_arg);

	comedi_handle_events(dev, s);

	वापस !devpriv->ai_cmd_running;
पूर्ण

अटल irqवापस_t s626_irq_handler(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा comedi_device *dev = d;
	अचिन्हित दीर्घ flags;
	u32 irqtype, irqstatus;

	अगर (!dev->attached)
		वापस IRQ_NONE;
	/* lock to aव्योम race with comedi_poll */
	spin_lock_irqsave(&dev->spinlock, flags);

	/* save पूर्णांकerrupt enable रेजिस्टर state */
	irqstatus = पढ़ोl(dev->mmio + S626_P_IER);

	/* पढ़ो पूर्णांकerrupt type */
	irqtype = पढ़ोl(dev->mmio + S626_P_ISR);

	/* disable master पूर्णांकerrupt */
	ग_लिखोl(0, dev->mmio + S626_P_IER);

	/* clear पूर्णांकerrupt */
	ग_लिखोl(irqtype, dev->mmio + S626_P_ISR);

	चयन (irqtype) अणु
	हाल S626_IRQ_RPS1:	/* end_of_scan occurs */
		अगर (s626_handle_eos_पूर्णांकerrupt(dev))
			irqstatus = 0;
		अवरोध;
	हाल S626_IRQ_GPIO3:	/* check dio and counter पूर्णांकerrupt */
		/* s626_dio_clear_irq(dev); */
		s626_check_dio_पूर्णांकerrupts(dev);
		s626_check_counter_पूर्णांकerrupts(dev);
		अवरोध;
	पूर्ण

	/* enable पूर्णांकerrupt */
	ग_लिखोl(irqstatus, dev->mmio + S626_P_IER);

	spin_unlock_irqrestore(&dev->spinlock, flags);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * This function builds the RPS program क्रम hardware driven acquisition.
 */
अटल व्योम s626_reset_adc(काष्ठा comedi_device *dev, u8 *ppl)
अणु
	काष्ठा s626_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	u32 *rps;
	u32 jmp_adrs;
	u16 i;
	u16 n;
	u32 local_ppl;

	/* Stop RPS program in हाल it is currently running */
	s626_mc_disable(dev, S626_MC1_ERPS1, S626_P_MC1);

	/* Set starting logical address to ग_लिखो RPS commands. */
	rps = (u32 *)devpriv->rps_buf.logical_base;

	/* Initialize RPS inकाष्ठाion poपूर्णांकer */
	ग_लिखोl((u32)devpriv->rps_buf.physical_base,
	       dev->mmio + S626_P_RPSADDR1);

	/* Conकाष्ठा RPS program in rps_buf DMA buffer */
	अगर (cmd->scan_begin_src != TRIG_FOLLOW) अणु
		/* Wait क्रम Start trigger. */
		*rps++ = S626_RPS_PAUSE | S626_RPS_SIGADC;
		*rps++ = S626_RPS_CLRSIGNAL | S626_RPS_SIGADC;
	पूर्ण

	/*
	 * SAA7146 BUG WORKAROUND Do a dummy DEBI Write.  This is necessary
	 * because the first RPS DEBI Write following a non-RPS DEBI ग_लिखो
	 * seems to always fail.  If we करोn't करो this dummy ग_लिखो, the ADC
	 * gain might not be set to the value required क्रम the first slot in
	 * the poll list; the ADC gain would instead reमुख्य unchanged from
	 * the previously programmed value.
	 */
	/* Write DEBI Write command and address to shaकरोw RAM. */
	*rps++ = S626_RPS_LDREG | (S626_P_DEBICMD >> 2);
	*rps++ = S626_DEBI_CMD_WRWORD | S626_LP_GSEL;
	*rps++ = S626_RPS_LDREG | (S626_P_DEBIAD >> 2);
	/* Write DEBI immediate data  to shaकरोw RAM: */
	*rps++ = S626_GSEL_BIPOLAR5V;	/* arbitrary immediate data  value. */
	*rps++ = S626_RPS_CLRSIGNAL | S626_RPS_DEBI;
	/* Reset "shadow RAM  uploaded" flag. */
	/* Invoke shaकरोw RAM upload. */
	*rps++ = S626_RPS_UPLOAD | S626_RPS_DEBI;
	/* Wait क्रम shaकरोw upload to finish. */
	*rps++ = S626_RPS_PAUSE | S626_RPS_DEBI;

	/*
	 * Digitize all slots in the poll list. This is implemented as a
	 * क्रम loop to limit the slot count to 16 in हाल the application
	 * क्रमgot to set the S626_EOPL flag in the final slot.
	 */
	क्रम (devpriv->adc_items = 0; devpriv->adc_items < 16;
	     devpriv->adc_items++) अणु
		/*
		 * Convert application's poll list item to निजी board class
		 * क्रमmat.  Each app poll list item is an uपूर्णांक8_t with क्रमm
		 * (EOPL,x,x,RANGE,CHAN<3:0>), where RANGE code indicates 0 =
		 * +-10V, 1 = +-5V, and EOPL = End of Poll List marker.
		 */
		local_ppl = (*ppl << 8) | (*ppl & 0x10 ? S626_GSEL_BIPOLAR5V :
					   S626_GSEL_BIPOLAR10V);

		/* Switch ADC analog gain. */
		/* Write DEBI command and address to shaकरोw RAM. */
		*rps++ = S626_RPS_LDREG | (S626_P_DEBICMD >> 2);
		*rps++ = S626_DEBI_CMD_WRWORD | S626_LP_GSEL;
		/* Write DEBI immediate data to shaकरोw RAM. */
		*rps++ = S626_RPS_LDREG | (S626_P_DEBIAD >> 2);
		*rps++ = local_ppl;
		/* Reset "shadow RAM uploaded" flag. */
		*rps++ = S626_RPS_CLRSIGNAL | S626_RPS_DEBI;
		/* Invoke shaकरोw RAM upload. */
		*rps++ = S626_RPS_UPLOAD | S626_RPS_DEBI;
		/* Wait क्रम shaकरोw upload to finish. */
		*rps++ = S626_RPS_PAUSE | S626_RPS_DEBI;
		/* Select ADC analog input channel. */
		*rps++ = S626_RPS_LDREG | (S626_P_DEBICMD >> 2);
		/* Write DEBI command and address to shaकरोw RAM. */
		*rps++ = S626_DEBI_CMD_WRWORD | S626_LP_ISEL;
		*rps++ = S626_RPS_LDREG | (S626_P_DEBIAD >> 2);
		/* Write DEBI immediate data to shaकरोw RAM. */
		*rps++ = local_ppl;
		/* Reset "shadow RAM uploaded" flag. */
		*rps++ = S626_RPS_CLRSIGNAL | S626_RPS_DEBI;
		/* Invoke shaकरोw RAM upload. */
		*rps++ = S626_RPS_UPLOAD | S626_RPS_DEBI;
		/* Wait क्रम shaकरोw upload to finish. */
		*rps++ = S626_RPS_PAUSE | S626_RPS_DEBI;

		/*
		 * Delay at least 10 microseconds क्रम analog input settling.
		 * Instead of padding with NOPs, we use S626_RPS_JUMP
		 * inकाष्ठाions here; this allows us to produce a दीर्घer delay
		 * than is possible with NOPs because each S626_RPS_JUMP
		 * flushes the RPS' inकाष्ठाion prefetch pipeline.
		 */
		jmp_adrs =
			(u32)devpriv->rps_buf.physical_base +
			(u32)((अचिन्हित दीर्घ)rps -
			      (अचिन्हित दीर्घ)devpriv->rps_buf.logical_base);
		क्रम (i = 0; i < (10 * S626_RPSCLK_PER_US / 2); i++) अणु
			jmp_adrs += 8;	/* Repeat to implement समय delay: */
			/* Jump to next RPS inकाष्ठाion. */
			*rps++ = S626_RPS_JUMP;
			*rps++ = jmp_adrs;
		पूर्ण

		अगर (cmd->convert_src != TRIG_NOW) अणु
			/* Wait क्रम Start trigger. */
			*rps++ = S626_RPS_PAUSE | S626_RPS_SIGADC;
			*rps++ = S626_RPS_CLRSIGNAL | S626_RPS_SIGADC;
		पूर्ण
		/* Start ADC by pulsing GPIO1. */
		/* Begin ADC Start pulse. */
		*rps++ = S626_RPS_LDREG | (S626_P_GPIO >> 2);
		*rps++ = S626_GPIO_BASE | S626_GPIO1_LO;
		*rps++ = S626_RPS_NOP;
		/* VERSION 2.03 CHANGE: STRETCH OUT ADC START PULSE. */
		/* End ADC Start pulse. */
		*rps++ = S626_RPS_LDREG | (S626_P_GPIO >> 2);
		*rps++ = S626_GPIO_BASE | S626_GPIO1_HI;
		/*
		 * Wait क्रम ADC to complete (GPIO2 is निश्चितed high when ADC not
		 * busy) and क्रम data from previous conversion to shअगरt पूर्णांकo FB
		 * BUFFER 1 रेजिस्टर.
		 */
		/* Wait क्रम ADC करोne. */
		*rps++ = S626_RPS_PAUSE | S626_RPS_GPIO2;

		/* Transfer ADC data from FB BUFFER 1 रेजिस्टर to DMA buffer. */
		*rps++ = S626_RPS_STREG |
			 (S626_BUGFIX_STREG(S626_P_FB_BUFFER1) >> 2);
		*rps++ = (u32)devpriv->ana_buf.physical_base +
			 (devpriv->adc_items << 2);

		/*
		 * If this slot's EndOfPollList flag is set, all channels have
		 * now been processed.
		 */
		अगर (*ppl++ & S626_EOPL) अणु
			devpriv->adc_items++; /* Adjust poll list item count. */
			अवरोध;	/* Exit poll list processing loop. */
		पूर्ण
	पूर्ण

	/*
	 * VERSION 2.01 CHANGE: DELAY CHANGED FROM 250NS to 2US.  Allow the
	 * ADC to stabilize क्रम 2 microseconds beक्रमe starting the final
	 * (dummy) conversion.  This delay is necessary to allow sufficient
	 * समय between last conversion finished and the start of the dummy
	 * conversion.  Without this delay, the last conversion's data value
	 * is someबार set to the previous conversion's data value.
	 */
	क्रम (n = 0; n < (2 * S626_RPSCLK_PER_US); n++)
		*rps++ = S626_RPS_NOP;

	/*
	 * Start a dummy conversion to cause the data from the last
	 * conversion of पूर्णांकerest to be shअगरted in.
	 */
	/* Begin ADC Start pulse. */
	*rps++ = S626_RPS_LDREG | (S626_P_GPIO >> 2);
	*rps++ = S626_GPIO_BASE | S626_GPIO1_LO;
	*rps++ = S626_RPS_NOP;
	/* VERSION 2.03 CHANGE: STRETCH OUT ADC START PULSE. */
	*rps++ = S626_RPS_LDREG | (S626_P_GPIO >> 2); /* End ADC Start pulse. */
	*rps++ = S626_GPIO_BASE | S626_GPIO1_HI;

	/*
	 * Wait क्रम the data from the last conversion of पूर्णांकerest to arrive
	 * in FB BUFFER 1 रेजिस्टर.
	 */
	*rps++ = S626_RPS_PAUSE | S626_RPS_GPIO2;	/* Wait क्रम ADC करोne. */

	/* Transfer final ADC data from FB BUFFER 1 रेजिस्टर to DMA buffer. */
	*rps++ = S626_RPS_STREG | (S626_BUGFIX_STREG(S626_P_FB_BUFFER1) >> 2);
	*rps++ = (u32)devpriv->ana_buf.physical_base +
		 (devpriv->adc_items << 2);

	/* Indicate ADC scan loop is finished. */
	/* Signal ReadADC() that scan is करोne. */
	/* *rps++= S626_RPS_CLRSIGNAL | S626_RPS_SIGADC; */

	/* invoke पूर्णांकerrupt */
	अगर (devpriv->ai_cmd_running == 1)
		*rps++ = S626_RPS_IRQ;

	/* Restart RPS program at its beginning. */
	*rps++ = S626_RPS_JUMP;	/* Branch to start of RPS program. */
	*rps++ = (u32)devpriv->rps_buf.physical_base;

	/* End of RPS program build */
पूर्ण

अटल पूर्णांक s626_ai_eoc(काष्ठा comedi_device *dev,
		       काष्ठा comedi_subdevice *s,
		       काष्ठा comedi_insn *insn,
		       अचिन्हित दीर्घ context)
अणु
	अचिन्हित पूर्णांक status;

	status = पढ़ोl(dev->mmio + S626_P_PSR);
	अगर (status & S626_PSR_GPIO2)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक s626_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s,
			     काष्ठा comedi_insn *insn,
			     अचिन्हित पूर्णांक *data)
अणु
	u16 chan = CR_CHAN(insn->chanspec);
	u16 range = CR_RANGE(insn->chanspec);
	u16 adc_spec = 0;
	u32 gpio_image;
	u32 पंचांगp;
	पूर्णांक ret;
	पूर्णांक n;

	/*
	 * Convert application's ADC specअगरication पूर्णांकo क्रमm
	 *  appropriate क्रम रेजिस्टर programming.
	 */
	अगर (range == 0)
		adc_spec = (chan << 8) | (S626_GSEL_BIPOLAR5V);
	अन्यथा
		adc_spec = (chan << 8) | (S626_GSEL_BIPOLAR10V);

	/* Switch ADC analog gain. */
	s626_debi_ग_लिखो(dev, S626_LP_GSEL, adc_spec);	/* Set gain. */

	/* Select ADC analog input channel. */
	s626_debi_ग_लिखो(dev, S626_LP_ISEL, adc_spec);	/* Select channel. */

	क्रम (n = 0; n < insn->n; n++) अणु
		/* Delay 10 microseconds क्रम analog input settling. */
		usleep_range(10, 20);

		/* Start ADC by pulsing GPIO1 low */
		gpio_image = पढ़ोl(dev->mmio + S626_P_GPIO);
		/* Assert ADC Start command */
		ग_लिखोl(gpio_image & ~S626_GPIO1_HI, dev->mmio + S626_P_GPIO);
		/* and stretch it out */
		ग_लिखोl(gpio_image & ~S626_GPIO1_HI, dev->mmio + S626_P_GPIO);
		ग_लिखोl(gpio_image & ~S626_GPIO1_HI, dev->mmio + S626_P_GPIO);
		/* Negate ADC Start command */
		ग_लिखोl(gpio_image | S626_GPIO1_HI, dev->mmio + S626_P_GPIO);

		/*
		 * Wait क्रम ADC to complete (GPIO2 is निश्चितed high when
		 * ADC not busy) and क्रम data from previous conversion to
		 * shअगरt पूर्णांकo FB BUFFER 1 रेजिस्टर.
		 */

		/* Wait क्रम ADC करोne */
		ret = comedi_समयout(dev, s, insn, s626_ai_eoc, 0);
		अगर (ret)
			वापस ret;

		/* Fetch ADC data */
		अगर (n != 0) अणु
			पंचांगp = पढ़ोl(dev->mmio + S626_P_FB_BUFFER1);
			data[n - 1] = s626_ai_reg_to_uपूर्णांक(पंचांगp);
		पूर्ण

		/*
		 * Allow the ADC to stabilize क्रम 4 microseconds beक्रमe
		 * starting the next (final) conversion.  This delay is
		 * necessary to allow sufficient समय between last
		 * conversion finished and the start of the next
		 * conversion.  Without this delay, the last conversion's
		 * data value is someबार set to the previous
		 * conversion's data value.
		 */
		udelay(4);
	पूर्ण

	/*
	 * Start a dummy conversion to cause the data from the
	 * previous conversion to be shअगरted in.
	 */
	gpio_image = पढ़ोl(dev->mmio + S626_P_GPIO);
	/* Assert ADC Start command */
	ग_लिखोl(gpio_image & ~S626_GPIO1_HI, dev->mmio + S626_P_GPIO);
	/* and stretch it out */
	ग_लिखोl(gpio_image & ~S626_GPIO1_HI, dev->mmio + S626_P_GPIO);
	ग_लिखोl(gpio_image & ~S626_GPIO1_HI, dev->mmio + S626_P_GPIO);
	/* Negate ADC Start command */
	ग_लिखोl(gpio_image | S626_GPIO1_HI, dev->mmio + S626_P_GPIO);

	/* Wait क्रम the data to arrive in FB BUFFER 1 रेजिस्टर. */

	/* Wait क्रम ADC करोne */
	ret = comedi_समयout(dev, s, insn, s626_ai_eoc, 0);
	अगर (ret)
		वापस ret;

	/* Fetch ADC data from audio पूर्णांकerface's input shअगरt रेजिस्टर. */

	/* Fetch ADC data */
	अगर (n != 0) अणु
		पंचांगp = पढ़ोl(dev->mmio + S626_P_FB_BUFFER1);
		data[n - 1] = s626_ai_reg_to_uपूर्णांक(पंचांगp);
	पूर्ण

	वापस n;
पूर्ण

अटल पूर्णांक s626_ai_load_polllist(u8 *ppl, काष्ठा comedi_cmd *cmd)
अणु
	पूर्णांक n;

	क्रम (n = 0; n < cmd->chanlist_len; n++) अणु
		अगर (CR_RANGE(cmd->chanlist[n]) == 0)
			ppl[n] = CR_CHAN(cmd->chanlist[n]) | S626_RANGE_5V;
		अन्यथा
			ppl[n] = CR_CHAN(cmd->chanlist[n]) | S626_RANGE_10V;
	पूर्ण
	अगर (n != 0)
		ppl[n - 1] |= S626_EOPL;

	वापस n;
पूर्ण

अटल पूर्णांक s626_ai_पूर्णांकtrig(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s,
			   अचिन्हित पूर्णांक trig_num)
अणु
	काष्ठा comedi_cmd *cmd = &s->async->cmd;

	अगर (trig_num != cmd->start_arg)
		वापस -EINVAL;

	/* Start executing the RPS program */
	s626_mc_enable(dev, S626_MC1_ERPS1, S626_P_MC1);

	s->async->पूर्णांकtrig = शून्य;

	वापस 1;
पूर्ण

/*
 * This function करोesn't require a particular क्रमm, this is just what
 * happens to be used in some of the drivers.  It should convert ns
 * nanoseconds to a counter value suitable क्रम programming the device.
 * Also, it should adjust ns so that it cooresponds to the actual समय
 * that the device will use.
 */
अटल पूर्णांक s626_ns_to_समयr(अचिन्हित पूर्णांक *nanosec, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक भागider, base;

	base = 500;		/* 2MHz पूर्णांकernal घड़ी */

	चयन (flags & CMDF_ROUND_MASK) अणु
	हाल CMDF_ROUND_NEAREST:
	शेष:
		भागider = DIV_ROUND_CLOSEST(*nanosec, base);
		अवरोध;
	हाल CMDF_ROUND_DOWN:
		भागider = (*nanosec) / base;
		अवरोध;
	हाल CMDF_ROUND_UP:
		भागider = DIV_ROUND_UP(*nanosec, base);
		अवरोध;
	पूर्ण

	*nanosec = base * भागider;
	वापस भागider - 1;
पूर्ण

अटल व्योम s626_समयr_load(काष्ठा comedi_device *dev,
			    अचिन्हित पूर्णांक chan, पूर्णांक tick)
अणु
	u16 setup =
		/* Preload upon index. */
		S626_SET_STD_LOADSRC(S626_LOADSRC_INDX) |
		/* Disable hardware index. */
		S626_SET_STD_INDXSRC(S626_INDXSRC_SOFT) |
		/* Operating mode is Timer. */
		S626_SET_STD_ENCMODE(S626_ENCMODE_TIMER) |
		/* Count direction is Down. */
		S626_SET_STD_CLKPOL(S626_CNTसूची_DOWN) |
		/* Clock multiplier is 1x. */
		S626_SET_STD_CLKMULT(S626_CLKMULT_1X) |
		/* Enabled by index */
		S626_SET_STD_CLKENAB(S626_CLKENAB_INDEX);
	u16 value_latchsrc = S626_LATCHSRC_A_INDXA;
	/* uपूर्णांक16_t enab = S626_CLKENAB_ALWAYS; */

	s626_set_mode(dev, chan, setup, false);

	/* Set the preload रेजिस्टर */
	s626_preload(dev, chan, tick);

	/*
	 * Software index pulse क्रमces the preload रेजिस्टर to load
	 * पूर्णांकo the counter
	 */
	s626_set_load_trig(dev, chan, 0);
	s626_pulse_index(dev, chan);

	/* set reload on counter overflow */
	s626_set_load_trig(dev, chan, 1);

	/* set पूर्णांकerrupt on overflow */
	s626_set_पूर्णांक_src(dev, chan, S626_INTSRC_OVER);

	s626_set_latch_source(dev, chan, value_latchsrc);
	/* s626_set_enable(dev, chan, (uपूर्णांक16_t)(enab != 0)); */
पूर्ण

/* TO COMPLETE  */
अटल पूर्णांक s626_ai_cmd(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा s626_निजी *devpriv = dev->निजी;
	u8 ppl[16];
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	पूर्णांक tick;

	अगर (devpriv->ai_cmd_running) अणु
		dev_err(dev->class_dev,
			"%s: Another ai_cmd is running\n", __func__);
		वापस -EBUSY;
	पूर्ण
	/* disable पूर्णांकerrupt */
	ग_लिखोl(0, dev->mmio + S626_P_IER);

	/* clear पूर्णांकerrupt request */
	ग_लिखोl(S626_IRQ_RPS1 | S626_IRQ_GPIO3, dev->mmio + S626_P_ISR);

	/* clear any pending पूर्णांकerrupt */
	s626_dio_clear_irq(dev);
	/* s626_enc_clear_irq(dev); */

	/* reset ai_cmd_running flag */
	devpriv->ai_cmd_running = 0;

	s626_ai_load_polllist(ppl, cmd);
	devpriv->ai_cmd_running = 1;
	devpriv->ai_convert_count = 0;

	चयन (cmd->scan_begin_src) अणु
	हाल TRIG_FOLLOW:
		अवरोध;
	हाल TRIG_TIMER:
		/*
		 * set a counter to generate adc trigger at scan_begin_arg
		 * पूर्णांकerval
		 */
		tick = s626_ns_to_समयr(&cmd->scan_begin_arg, cmd->flags);

		/* load समयr value and enable पूर्णांकerrupt */
		s626_समयr_load(dev, 5, tick);
		s626_set_enable(dev, 5, S626_CLKENAB_ALWAYS);
		अवरोध;
	हाल TRIG_EXT:
		/* set the digital line and पूर्णांकerrupt क्रम scan trigger */
		अगर (cmd->start_src != TRIG_EXT)
			s626_dio_set_irq(dev, cmd->scan_begin_arg);
		अवरोध;
	पूर्ण

	चयन (cmd->convert_src) अणु
	हाल TRIG_NOW:
		अवरोध;
	हाल TRIG_TIMER:
		/*
		 * set a counter to generate adc trigger at convert_arg
		 * पूर्णांकerval
		 */
		tick = s626_ns_to_समयr(&cmd->convert_arg, cmd->flags);

		/* load समयr value and enable पूर्णांकerrupt */
		s626_समयr_load(dev, 4, tick);
		s626_set_enable(dev, 4, S626_CLKENAB_INDEX);
		अवरोध;
	हाल TRIG_EXT:
		/* set the digital line and पूर्णांकerrupt क्रम convert trigger */
		अगर (cmd->scan_begin_src != TRIG_EXT &&
		    cmd->start_src == TRIG_EXT)
			s626_dio_set_irq(dev, cmd->convert_arg);
		अवरोध;
	पूर्ण

	s626_reset_adc(dev, ppl);

	चयन (cmd->start_src) अणु
	हाल TRIG_NOW:
		/* Trigger ADC scan loop start */
		/* s626_mc_enable(dev, S626_MC2_ADC_RPS, S626_P_MC2); */

		/* Start executing the RPS program */
		s626_mc_enable(dev, S626_MC1_ERPS1, S626_P_MC1);
		s->async->पूर्णांकtrig = शून्य;
		अवरोध;
	हाल TRIG_EXT:
		/* configure DIO channel क्रम acquisition trigger */
		s626_dio_set_irq(dev, cmd->start_arg);
		s->async->पूर्णांकtrig = शून्य;
		अवरोध;
	हाल TRIG_INT:
		s->async->पूर्णांकtrig = s626_ai_पूर्णांकtrig;
		अवरोध;
	पूर्ण

	/* enable पूर्णांकerrupt */
	ग_लिखोl(S626_IRQ_GPIO3 | S626_IRQ_RPS1, dev->mmio + S626_P_IER);

	वापस 0;
पूर्ण

अटल पूर्णांक s626_ai_cmdtest(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s, काष्ठा comedi_cmd *cmd)
अणु
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक arg;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src,
					TRIG_NOW | TRIG_INT | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src,
					TRIG_TIMER | TRIG_EXT | TRIG_FOLLOW);
	err |= comedi_check_trigger_src(&cmd->convert_src,
					TRIG_TIMER | TRIG_EXT | TRIG_NOW);
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

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	चयन (cmd->start_src) अणु
	हाल TRIG_NOW:
	हाल TRIG_INT:
		err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);
		अवरोध;
	हाल TRIG_EXT:
		err |= comedi_check_trigger_arg_max(&cmd->start_arg, 39);
		अवरोध;
	पूर्ण

	अगर (cmd->scan_begin_src == TRIG_EXT)
		err |= comedi_check_trigger_arg_max(&cmd->scan_begin_arg, 39);
	अगर (cmd->convert_src == TRIG_EXT)
		err |= comedi_check_trigger_arg_max(&cmd->convert_arg, 39);

#घोषणा S626_MAX_SPEED	200000	/* in nanoseconds */
#घोषणा S626_MIN_SPEED	2000000000	/* in nanoseconds */

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg,
						    S626_MAX_SPEED);
		err |= comedi_check_trigger_arg_max(&cmd->scan_begin_arg,
						    S626_MIN_SPEED);
	पूर्ण अन्यथा अणु
		/*
		 * बाह्यal trigger
		 * should be level/edge, hi/lo specअगरication here
		 * should specअगरy multiple बाह्यal triggers
		 * err |= comedi_check_trigger_arg_max(&cmd->scan_begin_arg, 9);
		 */
	पूर्ण
	अगर (cmd->convert_src == TRIG_TIMER) अणु
		err |= comedi_check_trigger_arg_min(&cmd->convert_arg,
						    S626_MAX_SPEED);
		err |= comedi_check_trigger_arg_max(&cmd->convert_arg,
						    S626_MIN_SPEED);
	पूर्ण अन्यथा अणु
		/*
		 * बाह्यal trigger - see above
		 * err |= comedi_check_trigger_arg_max(&cmd->scan_begin_arg, 9);
		 */
	पूर्ण

	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	अन्यथा	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* step 4: fix up any arguments */

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		arg = cmd->scan_begin_arg;
		s626_ns_to_समयr(&arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, arg);
	पूर्ण

	अगर (cmd->convert_src == TRIG_TIMER) अणु
		arg = cmd->convert_arg;
		s626_ns_to_समयr(&arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, arg);

		अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
			arg = cmd->convert_arg * cmd->scan_end_arg;
			err |= comedi_check_trigger_arg_min(
					&cmd->scan_begin_arg, arg);
		पूर्ण
	पूर्ण

	अगर (err)
		वापस 4;

	वापस 0;
पूर्ण

अटल पूर्णांक s626_ai_cancel(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा s626_निजी *devpriv = dev->निजी;

	/* Stop RPS program in हाल it is currently running */
	s626_mc_disable(dev, S626_MC1_ERPS1, S626_P_MC1);

	/* disable master पूर्णांकerrupt */
	ग_लिखोl(0, dev->mmio + S626_P_IER);

	devpriv->ai_cmd_running = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक s626_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn,
			      अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		s16 dacdata = (s16)data[i];
		पूर्णांक ret;

		dacdata -= (0x1fff);

		ret = s626_set_dac(dev, chan, dacdata);
		अगर (ret)
			वापस ret;

		s->पढ़ोback[chan] = data[i];
	पूर्ण

	वापस insn->n;
पूर्ण

/* *************** DIGITAL I/O FUNCTIONS *************** */

/*
 * All DIO functions address a group of DIO channels by means of
 * "group" argument.  group may be 0, 1 or 2, which correspond to DIO
 * ports A, B and C, respectively.
 */

अटल व्योम s626_dio_init(काष्ठा comedi_device *dev)
अणु
	u16 group;

	/* Prepare to treat ग_लिखोs to WRCapSel as capture disables. */
	s626_debi_ग_लिखो(dev, S626_LP_MISC1, S626_MISC1_NOEDCAP);

	/* For each group of sixteen channels ... */
	क्रम (group = 0; group < S626_DIO_BANKS; group++) अणु
		/* Disable all पूर्णांकerrupts */
		s626_debi_ग_लिखो(dev, S626_LP_WRINTSEL(group), 0);
		/* Disable all event captures */
		s626_debi_ग_लिखो(dev, S626_LP_WRCAPSEL(group), 0xffff);
		/* Init all DIOs to शेष edge polarity */
		s626_debi_ग_लिखो(dev, S626_LP_WREDGSEL(group), 0);
		/* Program all outमाला_दो to inactive state */
		s626_debi_ग_लिखो(dev, S626_LP_WRDOUT(group), 0);
	पूर्ण
पूर्ण

अटल पूर्णांक s626_dio_insn_bits(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn,
			      अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित दीर्घ group = (अचिन्हित दीर्घ)s->निजी;

	अगर (comedi_dio_update_state(s, data))
		s626_debi_ग_लिखो(dev, S626_LP_WRDOUT(group), s->state);

	data[1] = s626_debi_पढ़ो(dev, S626_LP_RDDIN(group));

	वापस insn->n;
पूर्ण

अटल पूर्णांक s626_dio_insn_config(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित दीर्घ group = (अचिन्हित दीर्घ)s->निजी;
	पूर्णांक ret;

	ret = comedi_dio_insn_config(dev, s, insn, data, 0);
	अगर (ret)
		वापस ret;

	s626_debi_ग_लिखो(dev, S626_LP_WRDOUT(group), s->io_bits);

	वापस insn->n;
पूर्ण

/*
 * Now this function initializes the value of the counter (data[0])
 * and set the subdevice. To complete with trigger and पूर्णांकerrupt
 * configuration.
 *
 * FIXME: data[0] is supposed to be an INSN_CONFIG_xxx स्थिरant indicating
 * what is being configured, but this function appears to be using data[0]
 * as a variable.
 */
अटल पूर्णांक s626_enc_insn_config(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	u16 setup =
		/* Preload upon index. */
		S626_SET_STD_LOADSRC(S626_LOADSRC_INDX) |
		/* Disable hardware index. */
		S626_SET_STD_INDXSRC(S626_INDXSRC_SOFT) |
		/* Operating mode is Counter. */
		S626_SET_STD_ENCMODE(S626_ENCMODE_COUNTER) |
		/* Active high घड़ी. */
		S626_SET_STD_CLKPOL(S626_CLKPOL_POS) |
		/* Clock multiplier is 1x. */
		S626_SET_STD_CLKMULT(S626_CLKMULT_1X) |
		/* Enabled by index */
		S626_SET_STD_CLKENAB(S626_CLKENAB_INDEX);
	/* uपूर्णांक16_t disable_पूर्णांक_src = true; */
	/* uपूर्णांक32_t Preloadvalue;              //Counter initial value */
	u16 value_latchsrc = S626_LATCHSRC_AB_READ;
	u16 enab = S626_CLKENAB_ALWAYS;

	/* (data==शून्य) ? (Preloadvalue=0) : (Preloadvalue=data[0]); */

	s626_set_mode(dev, chan, setup, true);
	s626_preload(dev, chan, data[0]);
	s626_pulse_index(dev, chan);
	s626_set_latch_source(dev, chan, value_latchsrc);
	s626_set_enable(dev, chan, (enab != 0));

	वापस insn->n;
पूर्ण

अटल पूर्णांक s626_enc_insn_पढ़ो(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn,
			      अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	u16 cntr_latch_reg = S626_LP_CNTR(chan);
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		अचिन्हित पूर्णांक val;

		/*
		 * Read the counter's output latch LSW/MSW.
		 * Latches on LSW पढ़ो.
		 */
		val = s626_debi_पढ़ो(dev, cntr_latch_reg);
		val |= (s626_debi_पढ़ो(dev, cntr_latch_reg + 2) << 16);
		data[i] = val;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक s626_enc_insn_ग_लिखो(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);

	/* Set the preload रेजिस्टर */
	s626_preload(dev, chan, data[0]);

	/*
	 * Software index pulse क्रमces the preload रेजिस्टर to load
	 * पूर्णांकo the counter
	 */
	s626_set_load_trig(dev, chan, 0);
	s626_pulse_index(dev, chan);
	s626_set_load_trig(dev, chan, 2);

	वापस 1;
पूर्ण

अटल व्योम s626_ग_लिखो_misc2(काष्ठा comedi_device *dev, u16 new_image)
अणु
	s626_debi_ग_लिखो(dev, S626_LP_MISC1, S626_MISC1_WENABLE);
	s626_debi_ग_लिखो(dev, S626_LP_WRMISC2, new_image);
	s626_debi_ग_लिखो(dev, S626_LP_MISC1, S626_MISC1_WDISABLE);
पूर्ण

अटल व्योम s626_counters_init(काष्ठा comedi_device *dev)
अणु
	पूर्णांक chan;
	u16 setup =
		/* Preload upon index. */
		S626_SET_STD_LOADSRC(S626_LOADSRC_INDX) |
		/* Disable hardware index. */
		S626_SET_STD_INDXSRC(S626_INDXSRC_SOFT) |
		/* Operating mode is counter. */
		S626_SET_STD_ENCMODE(S626_ENCMODE_COUNTER) |
		/* Active high घड़ी. */
		S626_SET_STD_CLKPOL(S626_CLKPOL_POS) |
		/* Clock multiplier is 1x. */
		S626_SET_STD_CLKMULT(S626_CLKMULT_1X) |
		/* Enabled by index */
		S626_SET_STD_CLKENAB(S626_CLKENAB_INDEX);

	/*
	 * Disable all counter पूर्णांकerrupts and clear any captured counter events.
	 */
	क्रम (chan = 0; chan < S626_ENCODER_CHANNELS; chan++) अणु
		s626_set_mode(dev, chan, setup, true);
		s626_set_पूर्णांक_src(dev, chan, 0);
		s626_reset_cap_flags(dev, chan);
		s626_set_enable(dev, chan, S626_CLKENAB_ALWAYS);
	पूर्ण
पूर्ण

अटल पूर्णांक s626_allocate_dma_buffers(काष्ठा comedi_device *dev)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	काष्ठा s626_निजी *devpriv = dev->निजी;
	व्योम *addr;
	dma_addr_t appdma;

	addr = dma_alloc_coherent(&pcidev->dev, S626_DMABUF_SIZE, &appdma,
				  GFP_KERNEL);
	अगर (!addr)
		वापस -ENOMEM;
	devpriv->ana_buf.logical_base = addr;
	devpriv->ana_buf.physical_base = appdma;

	addr = dma_alloc_coherent(&pcidev->dev, S626_DMABUF_SIZE, &appdma,
				  GFP_KERNEL);
	अगर (!addr)
		वापस -ENOMEM;
	devpriv->rps_buf.logical_base = addr;
	devpriv->rps_buf.physical_base = appdma;

	वापस 0;
पूर्ण

अटल व्योम s626_मुक्त_dma_buffers(काष्ठा comedi_device *dev)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	काष्ठा s626_निजी *devpriv = dev->निजी;

	अगर (!devpriv)
		वापस;

	अगर (devpriv->rps_buf.logical_base)
		dma_मुक्त_coherent(&pcidev->dev, S626_DMABUF_SIZE,
				  devpriv->rps_buf.logical_base,
				  devpriv->rps_buf.physical_base);
	अगर (devpriv->ana_buf.logical_base)
		dma_मुक्त_coherent(&pcidev->dev, S626_DMABUF_SIZE,
				  devpriv->ana_buf.logical_base,
				  devpriv->ana_buf.physical_base);
पूर्ण

अटल पूर्णांक s626_initialize(काष्ठा comedi_device *dev)
अणु
	काष्ठा s626_निजी *devpriv = dev->निजी;
	dma_addr_t phys_buf;
	u16 chan;
	पूर्णांक i;
	पूर्णांक ret;

	/* Enable DEBI and audio pins, enable I2C पूर्णांकerface */
	s626_mc_enable(dev, S626_MC1_DEBI | S626_MC1_AUDIO | S626_MC1_I2C,
		       S626_P_MC1);

	/*
	 * Configure DEBI operating mode
	 *
	 *  Local bus is 16 bits wide
	 *  Declare DEBI transfer समयout पूर्णांकerval
	 *  Set up byte lane steering
	 *  Intel-compatible local bus (DEBI never बार out)
	 */
	ग_लिखोl(S626_DEBI_CFG_SLAVE16 |
	       (S626_DEBI_TOUT << S626_DEBI_CFG_TOUT_BIT) | S626_DEBI_SWAP |
	       S626_DEBI_CFG_INTEL, dev->mmio + S626_P_DEBICFG);

	/* Disable MMU paging */
	ग_लिखोl(S626_DEBI_PAGE_DISABLE, dev->mmio + S626_P_DEBIPAGE);

	/* Init GPIO so that ADC Start* is negated */
	ग_लिखोl(S626_GPIO_BASE | S626_GPIO1_HI, dev->mmio + S626_P_GPIO);

	/* I2C device address क्रम onboard eeprom (revb) */
	devpriv->i2c_adrs = 0xA0;

	/*
	 * Issue an I2C ABORT command to halt any I2C
	 * operation in progress and reset BUSY flag.
	 */
	ग_लिखोl(S626_I2C_CLKSEL | S626_I2C_ABORT,
	       dev->mmio + S626_P_I2CSTAT);
	s626_mc_enable(dev, S626_MC2_UPLD_IIC, S626_P_MC2);
	ret = comedi_समयout(dev, शून्य, शून्य, s626_i2c_handshake_eoc, 0);
	अगर (ret)
		वापस ret;

	/*
	 * Per SAA7146 data sheet, ग_लिखो to STATUS
	 * reg twice to reset all  I2C error flags.
	 */
	क्रम (i = 0; i < 2; i++) अणु
		ग_लिखोl(S626_I2C_CLKSEL, dev->mmio + S626_P_I2CSTAT);
		s626_mc_enable(dev, S626_MC2_UPLD_IIC, S626_P_MC2);
		ret = comedi_समयout(dev, शून्य,
				     शून्य, s626_i2c_handshake_eoc, 0);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * Init audio पूर्णांकerface functional attributes: set DAC/ADC
	 * serial घड़ी rates, invert DAC serial घड़ी so that
	 * DAC data setup बार are satisfied, enable DAC serial
	 * घड़ी out.
	 */
	ग_लिखोl(S626_ACON2_INIT, dev->mmio + S626_P_ACON2);

	/*
	 * Set up TSL1 slot list, which is used to control the
	 * accumulation of ADC data: S626_RSD1 = shअगरt data in on SD1.
	 * S626_SIB_A1  = store data uपूर्णांक8_t at next available location
	 * in FB BUFFER1 रेजिस्टर.
	 */
	ग_लिखोl(S626_RSD1 | S626_SIB_A1, dev->mmio + S626_P_TSL1);
	ग_लिखोl(S626_RSD1 | S626_SIB_A1 | S626_EOS,
	       dev->mmio + S626_P_TSL1 + 4);

	/* Enable TSL1 slot list so that it executes all the समय */
	ग_लिखोl(S626_ACON1_ADCSTART, dev->mmio + S626_P_ACON1);

	/*
	 * Initialize RPS रेजिस्टरs used क्रम ADC
	 */

	/* Physical start of RPS program */
	ग_लिखोl((u32)devpriv->rps_buf.physical_base,
	       dev->mmio + S626_P_RPSADDR1);
	/* RPS program perक्रमms no explicit mem ग_लिखोs */
	ग_लिखोl(0, dev->mmio + S626_P_RPSPAGE1);
	/* Disable RPS समयouts */
	ग_लिखोl(0, dev->mmio + S626_P_RPS1_TOUT);

#अगर 0
	/*
	 * SAA7146 BUG WORKAROUND
	 *
	 * Initialize SAA7146 ADC पूर्णांकerface to a known state by
	 * invoking ADCs until FB BUFFER 1 रेजिस्टर shows that it
	 * is correctly receiving ADC data. This is necessary
	 * because the SAA7146 ADC पूर्णांकerface करोes not start up in
	 * a defined state after a PCI reset.
	 */
	अणु
		काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
		u8 poll_list;
		u16 adc_data;
		u16 start_val;
		u16 index;
		अचिन्हित पूर्णांक data[16];

		/* Create a simple polling list क्रम analog input channel 0 */
		poll_list = S626_EOPL;
		s626_reset_adc(dev, &poll_list);

		/* Get initial ADC value */
		s626_ai_rinsn(dev, s, शून्य, data);
		start_val = data[0];

		/*
		 * VERSION 2.01 CHANGE: TIMEOUT ADDED TO PREVENT HANGED
		 * EXECUTION.
		 *
		 * Invoke ADCs until the new ADC value dअगरfers from the initial
		 * value or a समयout occurs.  The समयout protects against the
		 * possibility that the driver is restarting and the ADC data is
		 * a fixed value resulting from the applied ADC analog input
		 * being unusually quiet or at the rail.
		 */
		क्रम (index = 0; index < 500; index++) अणु
			s626_ai_rinsn(dev, s, शून्य, data);
			adc_data = data[0];
			अगर (adc_data != start_val)
				अवरोध;
		पूर्ण
	पूर्ण
#पूर्ण_अगर	/* SAA7146 BUG WORKAROUND */

	/*
	 * Initialize the DAC पूर्णांकerface
	 */

	/*
	 * Init Audio2's output DMAC attributes:
	 *   burst length = 1 DWORD
	 *   threshold = 1 DWORD.
	 */
	ग_लिखोl(0, dev->mmio + S626_P_PCI_BT_A);

	/*
	 * Init Audio2's output DMA physical addresses.  The protection
	 * address is set to 1 DWORD past the base address so that a
	 * single DWORD will be transferred each समय a DMA transfer is
	 * enabled.
	 */
	phys_buf = devpriv->ana_buf.physical_base +
		   (S626_DAC_WDMABUF_OS * माप(u32));
	ग_लिखोl((u32)phys_buf, dev->mmio + S626_P_BASEA2_OUT);
	ग_लिखोl((u32)(phys_buf + माप(u32)),
	       dev->mmio + S626_P_PROTA2_OUT);

	/*
	 * Cache Audio2's output DMA buffer logical address.  This is
	 * where DAC data is buffered क्रम A2 output DMA transfers.
	 */
	devpriv->dac_wbuf = (u32 *)devpriv->ana_buf.logical_base +
			    S626_DAC_WDMABUF_OS;

	/*
	 * Audio2's output channels करोes not use paging.  The
	 * protection violation handling bit is set so that the
	 * DMAC will स्वतःmatically halt and its PCI address poपूर्णांकer
	 * will be reset when the protection address is reached.
	 */
	ग_लिखोl(8, dev->mmio + S626_P_PAGEA2_OUT);

	/*
	 * Initialize समय slot list 2 (TSL2), which is used to control
	 * the घड़ी generation क्रम and serialization of data to be sent
	 * to the DAC devices.  Slot 0 is a NOP that is used to trap TSL
	 * execution; this permits other slots to be safely modअगरied
	 * without first turning off the TSL sequencer (which is
	 * apparently impossible to करो).  Also, SD3 (which is driven by a
	 * pull-up resistor) is shअगरted in and stored to the MSB of
	 * FB_BUFFER2 to be used as evidence that the slot sequence has
	 * not yet finished executing.
	 */

	/* Slot 0: Trap TSL execution, shअगरt 0xFF पूर्णांकo FB_BUFFER2 */
	ग_लिखोl(S626_XSD2 | S626_RSD3 | S626_SIB_A2 | S626_EOS,
	       dev->mmio + S626_VECTPORT(0));

	/*
	 * Initialize slot 1, which is स्थिरant.  Slot 1 causes a
	 * DWORD to be transferred from audio channel 2's output FIFO
	 * to the FIFO's output buffer so that it can be serialized
	 * and sent to the DAC during subsequent slots.  All reमुख्यing
	 * slots are dynamically populated as required by the target
	 * DAC device.
	 */

	/* Slot 1: Fetch DWORD from Audio2's output FIFO */
	ग_लिखोl(S626_LF_A2, dev->mmio + S626_VECTPORT(1));

	/* Start DAC's audio पूर्णांकerface (TSL2) running */
	ग_लिखोl(S626_ACON1_DACSTART, dev->mmio + S626_P_ACON1);

	/*
	 * Init Trim DACs to calibrated values.  Do it twice because the
	 * SAA7146 audio channel करोes not always reset properly and
	 * someबार causes the first few TrimDAC ग_लिखोs to malfunction.
	 */
	s626_load_trim_dacs(dev);
	ret = s626_load_trim_dacs(dev);
	अगर (ret)
		वापस ret;

	/*
	 * Manually init all gate array hardware in हाल this is a soft
	 * reset (we have no way of determining whether this is a warm
	 * or cold start).  This is necessary because the gate array will
	 * reset only in response to a PCI hard reset; there is no soft
	 * reset function.
	 */

	/*
	 * Init all DAC outमाला_दो to 0V and init all DAC setpoपूर्णांक and
	 * polarity images.
	 */
	क्रम (chan = 0; chan < S626_DAC_CHANNELS; chan++) अणु
		ret = s626_set_dac(dev, chan, 0);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Init counters */
	s626_counters_init(dev);

	/*
	 * Without modअगरying the state of the Battery Backup enab, disable
	 * the watchकरोg समयr, set DIO channels 0-5 to operate in the
	 * standard DIO (vs. counter overflow) mode, disable the battery
	 * अक्षरger, and reset the watchकरोg पूर्णांकerval selector to zero.
	 */
	s626_ग_लिखो_misc2(dev, (s626_debi_पढ़ो(dev, S626_LP_RDMISC2) &
			       S626_MISC2_BATT_ENABLE));

	/* Initialize the digital I/O subप्रणाली */
	s626_dio_init(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक s626_स्वतः_attach(काष्ठा comedi_device *dev,
			    अचिन्हित दीर्घ context_unused)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	काष्ठा s626_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;

	dev->mmio = pci_ioremap_bar(pcidev, 0);
	अगर (!dev->mmio)
		वापस -ENOMEM;

	/* disable master पूर्णांकerrupt */
	ग_लिखोl(0, dev->mmio + S626_P_IER);

	/* soft reset */
	ग_लिखोl(S626_MC1_SOFT_RESET, dev->mmio + S626_P_MC1);

	/* DMA FIXME DMA// */

	ret = s626_allocate_dma_buffers(dev);
	अगर (ret)
		वापस ret;

	अगर (pcidev->irq) अणु
		ret = request_irq(pcidev->irq, s626_irq_handler, IRQF_SHARED,
				  dev->board_name, dev);

		अगर (ret == 0)
			dev->irq = pcidev->irq;
	पूर्ण

	ret = comedi_alloc_subdevices(dev, 6);
	अगर (ret)
		वापस ret;

	s = &dev->subdevices[0];
	/* analog input subdevice */
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE | SDF_DIFF;
	s->n_chan	= S626_ADC_CHANNELS;
	s->maxdata	= 0x3fff;
	s->range_table	= &s626_range_table;
	s->len_chanlist	= S626_ADC_CHANNELS;
	s->insn_पढ़ो	= s626_ai_insn_पढ़ो;
	अगर (dev->irq) अणु
		dev->पढ़ो_subdev = s;
		s->subdev_flags	|= SDF_CMD_READ;
		s->करो_cmd	= s626_ai_cmd;
		s->करो_cmdtest	= s626_ai_cmdtest;
		s->cancel	= s626_ai_cancel;
	पूर्ण

	s = &dev->subdevices[1];
	/* analog output subdevice */
	s->type		= COMEDI_SUBD_AO;
	s->subdev_flags	= SDF_WRITABLE | SDF_READABLE;
	s->n_chan	= S626_DAC_CHANNELS;
	s->maxdata	= 0x3fff;
	s->range_table	= &range_bipolar10;
	s->insn_ग_लिखो	= s626_ao_insn_ग_लिखो;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	s = &dev->subdevices[2];
	/* digital I/O subdevice */
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_flags	= SDF_WRITABLE | SDF_READABLE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->io_bits	= 0xffff;
	s->निजी	= (व्योम *)0;	/* DIO group 0 */
	s->range_table	= &range_digital;
	s->insn_config	= s626_dio_insn_config;
	s->insn_bits	= s626_dio_insn_bits;

	s = &dev->subdevices[3];
	/* digital I/O subdevice */
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_flags	= SDF_WRITABLE | SDF_READABLE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->io_bits	= 0xffff;
	s->निजी	= (व्योम *)1;	/* DIO group 1 */
	s->range_table	= &range_digital;
	s->insn_config	= s626_dio_insn_config;
	s->insn_bits	= s626_dio_insn_bits;

	s = &dev->subdevices[4];
	/* digital I/O subdevice */
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_flags	= SDF_WRITABLE | SDF_READABLE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->io_bits	= 0xffff;
	s->निजी	= (व्योम *)2;	/* DIO group 2 */
	s->range_table	= &range_digital;
	s->insn_config	= s626_dio_insn_config;
	s->insn_bits	= s626_dio_insn_bits;

	s = &dev->subdevices[5];
	/* encoder (counter) subdevice */
	s->type		= COMEDI_SUBD_COUNTER;
	s->subdev_flags	= SDF_WRITABLE | SDF_READABLE | SDF_LSAMPL;
	s->n_chan	= S626_ENCODER_CHANNELS;
	s->maxdata	= 0xffffff;
	s->range_table	= &range_unknown;
	s->insn_config	= s626_enc_insn_config;
	s->insn_पढ़ो	= s626_enc_insn_पढ़ो;
	s->insn_ग_लिखो	= s626_enc_insn_ग_लिखो;

	वापस s626_initialize(dev);
पूर्ण

अटल व्योम s626_detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा s626_निजी *devpriv = dev->निजी;

	अगर (devpriv) अणु
		/* stop ai_command */
		devpriv->ai_cmd_running = 0;

		अगर (dev->mmio) अणु
			/* पूर्णांकerrupt mask */
			/* Disable master पूर्णांकerrupt */
			ग_लिखोl(0, dev->mmio + S626_P_IER);
			/* Clear board's IRQ status flag */
			ग_लिखोl(S626_IRQ_GPIO3 | S626_IRQ_RPS1,
			       dev->mmio + S626_P_ISR);

			/* Disable the watchकरोg समयr and battery अक्षरger. */
			s626_ग_लिखो_misc2(dev, 0);

			/* Close all पूर्णांकerfaces on 7146 device */
			ग_लिखोl(S626_MC1_SHUTDOWN, dev->mmio + S626_P_MC1);
			ग_लिखोl(S626_ACON1_BASE, dev->mmio + S626_P_ACON1);
		पूर्ण
	पूर्ण
	comedi_pci_detach(dev);
	s626_मुक्त_dma_buffers(dev);
पूर्ण

अटल काष्ठा comedi_driver s626_driver = अणु
	.driver_name	= "s626",
	.module		= THIS_MODULE,
	.स्वतः_attach	= s626_स्वतः_attach,
	.detach		= s626_detach,
पूर्ण;

अटल पूर्णांक s626_pci_probe(काष्ठा pci_dev *dev,
			  स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &s626_driver, id->driver_data);
पूर्ण

/*
 * For devices with venकरोr:device id == 0x1131:0x7146 you must specअगरy
 * also subvenकरोr:subdevice ids, because otherwise it will conflict with
 * Philips SAA7146 media/dvb based cards.
 */
अटल स्थिर काष्ठा pci_device_id s626_pci_table[] = अणु
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_PHILIPS, PCI_DEVICE_ID_PHILIPS_SAA7146,
			 0x6000, 0x0272) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, s626_pci_table);

अटल काष्ठा pci_driver s626_pci_driver = अणु
	.name		= "s626",
	.id_table	= s626_pci_table,
	.probe		= s626_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(s626_driver, s626_pci_driver);

MODULE_AUTHOR("Gianluca Palli <gpalli@deis.unibo.it>");
MODULE_DESCRIPTION("Sensoray 626 Comedi driver module");
MODULE_LICENSE("GPL");
