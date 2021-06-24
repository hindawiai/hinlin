<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Digigram VX222 V2/Mic soundcards
 *
 * VX222-specअगरic low-level routines
 *
 * Copyright (c) 2002 by Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/firmware.h>
#समावेश <linux/mutex.h>
#समावेश <linux/पन.स>

#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/tlv.h>
#समावेश "vx222.h"


अटल स्थिर पूर्णांक vx2_reg_offset[VX_REG_MAX] = अणु
	[VX_ICR]    = 0x00,
	[VX_CVR]    = 0x04,
	[VX_ISR]    = 0x08,
	[VX_IVR]    = 0x0c,
	[VX_RXH]    = 0x14,
	[VX_RXM]    = 0x18,
	[VX_RXL]    = 0x1c,
	[VX_DMA]    = 0x10,
	[VX_CDSP]   = 0x20,
	[VX_CFG]    = 0x24,
	[VX_RUER]   = 0x28,
	[VX_DATA]   = 0x2c,
	[VX_STATUS] = 0x30,
	[VX_LOFREQ] = 0x34,
	[VX_HIFREQ] = 0x38,
	[VX_CSUER]  = 0x3c,
	[VX_SELMIC] = 0x40,
	[VX_COMPOT] = 0x44, // Write: POTENTIOMETER ; Read: COMPRESSION LEVEL activate
	[VX_SCOMPR] = 0x48, // Read: COMPRESSION THRESHOLD activate
	[VX_GLIMIT] = 0x4c, // Read: LEVEL LIMITATION activate
	[VX_INTCSR] = 0x4c, // VX_INTCSR_REGISTER_OFFSET
	[VX_CNTRL]  = 0x50,		// VX_CNTRL_REGISTER_OFFSET
	[VX_GPIOC]  = 0x54,		// VX_GPIOC (new with PLX9030)
पूर्ण;

अटल स्थिर पूर्णांक vx2_reg_index[VX_REG_MAX] = अणु
	[VX_ICR]	= 1,
	[VX_CVR]	= 1,
	[VX_ISR]	= 1,
	[VX_IVR]	= 1,
	[VX_RXH]	= 1,
	[VX_RXM]	= 1,
	[VX_RXL]	= 1,
	[VX_DMA]	= 1,
	[VX_CDSP]	= 1,
	[VX_CFG]	= 1,
	[VX_RUER]	= 1,
	[VX_DATA]	= 1,
	[VX_STATUS]	= 1,
	[VX_LOFREQ]	= 1,
	[VX_HIFREQ]	= 1,
	[VX_CSUER]	= 1,
	[VX_SELMIC]	= 1,
	[VX_COMPOT]	= 1,
	[VX_SCOMPR]	= 1,
	[VX_GLIMIT]	= 1,
	[VX_INTCSR]	= 0,	/* on the PLX */
	[VX_CNTRL]	= 0,	/* on the PLX */
	[VX_GPIOC]	= 0,	/* on the PLX */
पूर्ण;

अटल अंतरभूत अचिन्हित दीर्घ vx2_reg_addr(काष्ठा vx_core *_chip, पूर्णांक reg)
अणु
	काष्ठा snd_vx222 *chip = to_vx222(_chip);
	वापस chip->port[vx2_reg_index[reg]] + vx2_reg_offset[reg];
पूर्ण

/**
 * vx2_inb - पढ़ो a byte from the रेजिस्टर
 * @chip: VX core instance
 * @offset: रेजिस्टर क्रमागत
 */
अटल अचिन्हित अक्षर vx2_inb(काष्ठा vx_core *chip, पूर्णांक offset)
अणु
	वापस inb(vx2_reg_addr(chip, offset));
पूर्ण

/**
 * vx2_outb - ग_लिखो a byte on the रेजिस्टर
 * @chip: VX core instance
 * @offset: the रेजिस्टर offset
 * @val: the value to ग_लिखो
 */
अटल व्योम vx2_outb(काष्ठा vx_core *chip, पूर्णांक offset, अचिन्हित अक्षर val)
अणु
	outb(val, vx2_reg_addr(chip, offset));
	/*
	dev_dbg(chip->card->dev, "outb: %x -> %x\n", val, vx2_reg_addr(chip, offset));
	*/
पूर्ण

/**
 * vx2_inl - पढ़ो a 32bit word from the रेजिस्टर
 * @chip: VX core instance
 * @offset: रेजिस्टर क्रमागत
 */
अटल अचिन्हित पूर्णांक vx2_inl(काष्ठा vx_core *chip, पूर्णांक offset)
अणु
	वापस inl(vx2_reg_addr(chip, offset));
पूर्ण

/**
 * vx2_outl - ग_लिखो a 32bit word on the रेजिस्टर
 * @chip: VX core instance
 * @offset: the रेजिस्टर क्रमागत
 * @val: the value to ग_लिखो
 */
अटल व्योम vx2_outl(काष्ठा vx_core *chip, पूर्णांक offset, अचिन्हित पूर्णांक val)
अणु
	/*
	dev_dbg(chip->card->dev, "outl: %x -> %x\n", val, vx2_reg_addr(chip, offset));
	*/
	outl(val, vx2_reg_addr(chip, offset));
पूर्ण

/*
 * redefine macros to call directly
 */
#अघोषित vx_inb
#घोषणा vx_inb(chip,reg)	vx2_inb((काष्ठा vx_core*)(chip), VX_##reg)
#अघोषित vx_outb
#घोषणा vx_outb(chip,reg,val)	vx2_outb((काष्ठा vx_core*)(chip), VX_##reg, val)
#अघोषित vx_inl
#घोषणा vx_inl(chip,reg)	vx2_inl((काष्ठा vx_core*)(chip), VX_##reg)
#अघोषित vx_outl
#घोषणा vx_outl(chip,reg,val)	vx2_outl((काष्ठा vx_core*)(chip), VX_##reg, val)


/*
 * vx_reset_dsp - reset the DSP
 */

#घोषणा XX_DSP_RESET_WAIT_TIME		2	/* ms */

अटल व्योम vx2_reset_dsp(काष्ठा vx_core *_chip)
अणु
	काष्ठा snd_vx222 *chip = to_vx222(_chip);

	/* set the reset dsp bit to 0 */
	vx_outl(chip, CDSP, chip->regCDSP & ~VX_CDSP_DSP_RESET_MASK);

	mdelay(XX_DSP_RESET_WAIT_TIME);

	chip->regCDSP |= VX_CDSP_DSP_RESET_MASK;
	/* set the reset dsp bit to 1 */
	vx_outl(chip, CDSP, chip->regCDSP);
पूर्ण


अटल पूर्णांक vx2_test_xilinx(काष्ठा vx_core *_chip)
अणु
	काष्ठा snd_vx222 *chip = to_vx222(_chip);
	अचिन्हित पूर्णांक data;

	dev_dbg(_chip->card->dev, "testing xilinx...\n");
	/* This test uses several ग_लिखो/पढ़ो sequences on TEST0 and TEST1 bits
	 * to figure out whever or not the xilinx was correctly loaded
	 */

	/* We ग_लिखो 1 on CDSP.TEST0. We should get 0 on STATUS.TEST0. */
	vx_outl(chip, CDSP, chip->regCDSP | VX_CDSP_TEST0_MASK);
	vx_inl(chip, ISR);
	data = vx_inl(chip, STATUS);
	अगर ((data & VX_STATUS_VAL_TEST0_MASK) == VX_STATUS_VAL_TEST0_MASK) अणु
		dev_dbg(_chip->card->dev, "bad!\n");
		वापस -ENODEV;
	पूर्ण

	/* We ग_लिखो 0 on CDSP.TEST0. We should get 1 on STATUS.TEST0. */
	vx_outl(chip, CDSP, chip->regCDSP & ~VX_CDSP_TEST0_MASK);
	vx_inl(chip, ISR);
	data = vx_inl(chip, STATUS);
	अगर (! (data & VX_STATUS_VAL_TEST0_MASK)) अणु
		dev_dbg(_chip->card->dev, "bad! #2\n");
		वापस -ENODEV;
	पूर्ण

	अगर (_chip->type == VX_TYPE_BOARD) अणु
		/* not implemented on VX_2_BOARDS */
		/* We ग_लिखो 1 on CDSP.TEST1. We should get 0 on STATUS.TEST1. */
		vx_outl(chip, CDSP, chip->regCDSP | VX_CDSP_TEST1_MASK);
		vx_inl(chip, ISR);
		data = vx_inl(chip, STATUS);
		अगर ((data & VX_STATUS_VAL_TEST1_MASK) == VX_STATUS_VAL_TEST1_MASK) अणु
			dev_dbg(_chip->card->dev, "bad! #3\n");
			वापस -ENODEV;
		पूर्ण

		/* We ग_लिखो 0 on CDSP.TEST1. We should get 1 on STATUS.TEST1. */
		vx_outl(chip, CDSP, chip->regCDSP & ~VX_CDSP_TEST1_MASK);
		vx_inl(chip, ISR);
		data = vx_inl(chip, STATUS);
		अगर (! (data & VX_STATUS_VAL_TEST1_MASK)) अणु
			dev_dbg(_chip->card->dev, "bad! #4\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	dev_dbg(_chip->card->dev, "ok, xilinx fine.\n");
	वापस 0;
पूर्ण


/**
 * vx2_setup_pseuकरो_dma - set up the pseuकरो dma पढ़ो/ग_लिखो mode.
 * @chip: VX core instance
 * @करो_ग_लिखो: 0 = पढ़ो, 1 = set up क्रम DMA ग_लिखो
 */
अटल व्योम vx2_setup_pseuकरो_dma(काष्ठा vx_core *chip, पूर्णांक करो_ग_लिखो)
अणु
	/* Interrupt mode and HREQ pin enabled क्रम host transmit data transfers
	 * (in हाल of the use of the pseuकरो-dma facility).
	 */
	vx_outl(chip, ICR, करो_ग_लिखो ? ICR_TREQ : ICR_RREQ);

	/* Reset the pseuकरो-dma रेजिस्टर (in हाल of the use of the
	 * pseuकरो-dma facility).
	 */
	vx_outl(chip, RESET_DMA, 0);
पूर्ण

/*
 * vx_release_pseuकरो_dma - disable the pseuकरो-DMA mode
 */
अटल अंतरभूत व्योम vx2_release_pseuकरो_dma(काष्ठा vx_core *chip)
अणु
	/* HREQ pin disabled. */
	vx_outl(chip, ICR, 0);
पूर्ण



/* pseuकरो-dma ग_लिखो */
अटल व्योम vx2_dma_ग_लिखो(काष्ठा vx_core *chip, काष्ठा snd_pcm_runसमय *runसमय,
			  काष्ठा vx_pipe *pipe, पूर्णांक count)
अणु
	अचिन्हित दीर्घ port = vx2_reg_addr(chip, VX_DMA);
	पूर्णांक offset = pipe->hw_ptr;
	u32 *addr = (u32 *)(runसमय->dma_area + offset);

	अगर (snd_BUG_ON(count % 4))
		वापस;

	vx2_setup_pseuकरो_dma(chip, 1);

	/* Transfer using pseuकरो-dma.
	 */
	अगर (offset + count >= pipe->buffer_bytes) अणु
		पूर्णांक length = pipe->buffer_bytes - offset;
		count -= length;
		length >>= 2; /* in 32bit words */
		/* Transfer using pseuकरो-dma. */
		क्रम (; length > 0; length--) अणु
			outl(*addr, port);
			addr++;
		पूर्ण
		addr = (u32 *)runसमय->dma_area;
		pipe->hw_ptr = 0;
	पूर्ण
	pipe->hw_ptr += count;
	count >>= 2; /* in 32bit words */
	/* Transfer using pseuकरो-dma. */
	क्रम (; count > 0; count--) अणु
		outl(*addr, port);
		addr++;
	पूर्ण

	vx2_release_pseuकरो_dma(chip);
पूर्ण


/* pseuकरो dma पढ़ो */
अटल व्योम vx2_dma_पढ़ो(काष्ठा vx_core *chip, काष्ठा snd_pcm_runसमय *runसमय,
			 काष्ठा vx_pipe *pipe, पूर्णांक count)
अणु
	पूर्णांक offset = pipe->hw_ptr;
	u32 *addr = (u32 *)(runसमय->dma_area + offset);
	अचिन्हित दीर्घ port = vx2_reg_addr(chip, VX_DMA);

	अगर (snd_BUG_ON(count % 4))
		वापस;

	vx2_setup_pseuकरो_dma(chip, 0);
	/* Transfer using pseuकरो-dma.
	 */
	अगर (offset + count >= pipe->buffer_bytes) अणु
		पूर्णांक length = pipe->buffer_bytes - offset;
		count -= length;
		length >>= 2; /* in 32bit words */
		/* Transfer using pseuकरो-dma. */
		क्रम (; length > 0; length--)
			*addr++ = inl(port);
		addr = (u32 *)runसमय->dma_area;
		pipe->hw_ptr = 0;
	पूर्ण
	pipe->hw_ptr += count;
	count >>= 2; /* in 32bit words */
	/* Transfer using pseuकरो-dma. */
	क्रम (; count > 0; count--)
		*addr++ = inl(port);

	vx2_release_pseuकरो_dma(chip);
पूर्ण

#घोषणा VX_XILINX_RESET_MASK        0x40000000
#घोषणा VX_USERBIT0_MASK            0x00000004
#घोषणा VX_USERBIT1_MASK            0x00000020
#घोषणा VX_CNTRL_REGISTER_VALUE     0x00172012

/*
 * transfer counts bits to PLX
 */
अटल पूर्णांक put_xilinx_data(काष्ठा vx_core *chip, अचिन्हित पूर्णांक port, अचिन्हित पूर्णांक counts, अचिन्हित अक्षर data)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < counts; i++) अणु
		अचिन्हित पूर्णांक val;

		/* set the घड़ी bit to 0. */
		val = VX_CNTRL_REGISTER_VALUE & ~VX_USERBIT0_MASK;
		vx2_outl(chip, port, val);
		vx2_inl(chip, port);
		udelay(1);

		अगर (data & (1 << i))
			val |= VX_USERBIT1_MASK;
		अन्यथा
			val &= ~VX_USERBIT1_MASK;
		vx2_outl(chip, port, val);
		vx2_inl(chip, port);

		/* set the घड़ी bit to 1. */
		val |= VX_USERBIT0_MASK;
		vx2_outl(chip, port, val);
		vx2_inl(chip, port);
		udelay(1);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * load the xilinx image
 */
अटल पूर्णांक vx2_load_xilinx_binary(काष्ठा vx_core *chip, स्थिर काष्ठा firmware *xilinx)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक port;
	स्थिर अचिन्हित अक्षर *image;

	/* XILINX reset (रुको at least 1 millisecond between reset on and off). */
	vx_outl(chip, CNTRL, VX_CNTRL_REGISTER_VALUE | VX_XILINX_RESET_MASK);
	vx_inl(chip, CNTRL);
	msleep(10);
	vx_outl(chip, CNTRL, VX_CNTRL_REGISTER_VALUE);
	vx_inl(chip, CNTRL);
	msleep(10);

	अगर (chip->type == VX_TYPE_BOARD)
		port = VX_CNTRL;
	अन्यथा
		port = VX_GPIOC; /* VX222 V2 and VX222_MIC_BOARD with new PLX9030 use this रेजिस्टर */

	image = xilinx->data;
	क्रम (i = 0; i < xilinx->size; i++, image++) अणु
		अगर (put_xilinx_data(chip, port, 8, *image) < 0)
			वापस -EINVAL;
		/* करोn't take too much समय in this loop... */
		cond_resched();
	पूर्ण
	put_xilinx_data(chip, port, 4, 0xff); /* end signature */

	msleep(200);

	/* test after loading (is buggy with VX222) */
	अगर (chip->type != VX_TYPE_BOARD) अणु
		/* Test अगर load successful: test bit 8 of रेजिस्टर GPIOC (VX222: use CNTRL) ! */
		i = vx_inl(chip, GPIOC);
		अगर (i & 0x0100)
			वापस 0;
		dev_err(chip->card->dev,
			"xilinx test failed after load, GPIOC=0x%x\n", i);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

	
/*
 * load the boot/dsp images
 */
अटल पूर्णांक vx2_load_dsp(काष्ठा vx_core *vx, पूर्णांक index, स्थिर काष्ठा firmware *dsp)
अणु
	पूर्णांक err;

	चयन (index) अणु
	हाल 1:
		/* xilinx image */
		अगर ((err = vx2_load_xilinx_binary(vx, dsp)) < 0)
			वापस err;
		अगर ((err = vx2_test_xilinx(vx)) < 0)
			वापस err;
		वापस 0;
	हाल 2:
		/* DSP boot */
		वापस snd_vx_dsp_boot(vx, dsp);
	हाल 3:
		/* DSP image */
		वापस snd_vx_dsp_load(vx, dsp);
	शेष:
		snd_BUG();
		वापस -EINVAL;
	पूर्ण
पूर्ण


/*
 * vx_test_and_ack - test and acknowledge पूर्णांकerrupt
 *
 * called from irq hander, too
 *
 * spinlock held!
 */
अटल पूर्णांक vx2_test_and_ack(काष्ठा vx_core *chip)
अणु
	/* not booted yet? */
	अगर (! (chip->chip_status & VX_STAT_XILINX_LOADED))
		वापस -ENXIO;

	अगर (! (vx_inl(chip, STATUS) & VX_STATUS_MEMIRQ_MASK))
		वापस -EIO;
	
	/* ok, पूर्णांकerrupts generated, now ack it */
	/* set ACQUIT bit up and करोwn */
	vx_outl(chip, STATUS, 0);
	/* useless पढ़ो just to spend some समय and मुख्यtain
	 * the ACQUIT संकेत up क्रम a जबतक ( a bus cycle )
	 */
	vx_inl(chip, STATUS);
	/* ack */
	vx_outl(chip, STATUS, VX_STATUS_MEMIRQ_MASK);
	/* useless पढ़ो just to spend some समय and मुख्यtain
	 * the ACQUIT संकेत up क्रम a जबतक ( a bus cycle ) */
	vx_inl(chip, STATUS);
	/* clear */
	vx_outl(chip, STATUS, 0);

	वापस 0;
पूर्ण


/*
 * vx_validate_irq - enable/disable IRQ
 */
अटल व्योम vx2_validate_irq(काष्ठा vx_core *_chip, पूर्णांक enable)
अणु
	काष्ठा snd_vx222 *chip = to_vx222(_chip);

	/* Set the पूर्णांकerrupt enable bit to 1 in CDSP रेजिस्टर */
	अगर (enable) अणु
		/* Set the PCI पूर्णांकerrupt enable bit to 1.*/
		vx_outl(chip, INTCSR, VX_INTCSR_VALUE|VX_PCI_INTERRUPT_MASK);
		chip->regCDSP |= VX_CDSP_VALID_IRQ_MASK;
	पूर्ण अन्यथा अणु
		/* Set the PCI पूर्णांकerrupt enable bit to 0. */
		vx_outl(chip, INTCSR, VX_INTCSR_VALUE&~VX_PCI_INTERRUPT_MASK);
		chip->regCDSP &= ~VX_CDSP_VALID_IRQ_MASK;
	पूर्ण
	vx_outl(chip, CDSP, chip->regCDSP);
पूर्ण


/*
 * ग_लिखो an AKM codec data (24bit)
 */
अटल व्योम vx2_ग_लिखो_codec_reg(काष्ठा vx_core *chip, अचिन्हित पूर्णांक data)
अणु
	अचिन्हित पूर्णांक i;

	vx_inl(chip, HIFREQ);

	/* We have to send 24 bits (3 x 8 bits). Start with most signअगर. Bit */
	क्रम (i = 0; i < 24; i++, data <<= 1)
		vx_outl(chip, DATA, ((data & 0x800000) ? VX_DATA_CODEC_MASK : 0));
	/* Terminate access to codec रेजिस्टरs */
	vx_inl(chip, RUER);
पूर्ण


#घोषणा AKM_CODEC_POWER_CONTROL_CMD 0xA007
#घोषणा AKM_CODEC_RESET_ON_CMD      0xA100
#घोषणा AKM_CODEC_RESET_OFF_CMD     0xA103
#घोषणा AKM_CODEC_CLOCK_FORMAT_CMD  0xA240
#घोषणा AKM_CODEC_MUTE_CMD          0xA38D
#घोषणा AKM_CODEC_UNMUTE_CMD        0xA30D
#घोषणा AKM_CODEC_LEFT_LEVEL_CMD    0xA400
#घोषणा AKM_CODEC_RIGHT_LEVEL_CMD   0xA500

अटल स्थिर u8 vx2_akm_gains_lut[VX2_AKM_LEVEL_MAX+1] = अणु
    0x7f,       // [000] =  +0.000 dB  ->  AKM(0x7f) =  +0.000 dB  error(+0.000 dB)
    0x7d,       // [001] =  -0.500 dB  ->  AKM(0x7d) =  -0.572 dB  error(-0.072 dB)
    0x7c,       // [002] =  -1.000 dB  ->  AKM(0x7c) =  -0.873 dB  error(+0.127 dB)
    0x7a,       // [003] =  -1.500 dB  ->  AKM(0x7a) =  -1.508 dB  error(-0.008 dB)
    0x79,       // [004] =  -2.000 dB  ->  AKM(0x79) =  -1.844 dB  error(+0.156 dB)
    0x77,       // [005] =  -2.500 dB  ->  AKM(0x77) =  -2.557 dB  error(-0.057 dB)
    0x76,       // [006] =  -3.000 dB  ->  AKM(0x76) =  -2.937 dB  error(+0.063 dB)
    0x75,       // [007] =  -3.500 dB  ->  AKM(0x75) =  -3.334 dB  error(+0.166 dB)
    0x73,       // [008] =  -4.000 dB  ->  AKM(0x73) =  -4.188 dB  error(-0.188 dB)
    0x72,       // [009] =  -4.500 dB  ->  AKM(0x72) =  -4.648 dB  error(-0.148 dB)
    0x71,       // [010] =  -5.000 dB  ->  AKM(0x71) =  -5.134 dB  error(-0.134 dB)
    0x70,       // [011] =  -5.500 dB  ->  AKM(0x70) =  -5.649 dB  error(-0.149 dB)
    0x6f,       // [012] =  -6.000 dB  ->  AKM(0x6f) =  -6.056 dB  error(-0.056 dB)
    0x6d,       // [013] =  -6.500 dB  ->  AKM(0x6d) =  -6.631 dB  error(-0.131 dB)
    0x6c,       // [014] =  -7.000 dB  ->  AKM(0x6c) =  -6.933 dB  error(+0.067 dB)
    0x6a,       // [015] =  -7.500 dB  ->  AKM(0x6a) =  -7.571 dB  error(-0.071 dB)
    0x69,       // [016] =  -8.000 dB  ->  AKM(0x69) =  -7.909 dB  error(+0.091 dB)
    0x67,       // [017] =  -8.500 dB  ->  AKM(0x67) =  -8.626 dB  error(-0.126 dB)
    0x66,       // [018] =  -9.000 dB  ->  AKM(0x66) =  -9.008 dB  error(-0.008 dB)
    0x65,       // [019] =  -9.500 dB  ->  AKM(0x65) =  -9.407 dB  error(+0.093 dB)
    0x64,       // [020] = -10.000 dB  ->  AKM(0x64) =  -9.826 dB  error(+0.174 dB)
    0x62,       // [021] = -10.500 dB  ->  AKM(0x62) = -10.730 dB  error(-0.230 dB)
    0x61,       // [022] = -11.000 dB  ->  AKM(0x61) = -11.219 dB  error(-0.219 dB)
    0x60,       // [023] = -11.500 dB  ->  AKM(0x60) = -11.738 dB  error(-0.238 dB)
    0x5f,       // [024] = -12.000 dB  ->  AKM(0x5f) = -12.149 dB  error(-0.149 dB)
    0x5e,       // [025] = -12.500 dB  ->  AKM(0x5e) = -12.434 dB  error(+0.066 dB)
    0x5c,       // [026] = -13.000 dB  ->  AKM(0x5c) = -13.033 dB  error(-0.033 dB)
    0x5b,       // [027] = -13.500 dB  ->  AKM(0x5b) = -13.350 dB  error(+0.150 dB)
    0x59,       // [028] = -14.000 dB  ->  AKM(0x59) = -14.018 dB  error(-0.018 dB)
    0x58,       // [029] = -14.500 dB  ->  AKM(0x58) = -14.373 dB  error(+0.127 dB)
    0x56,       // [030] = -15.000 dB  ->  AKM(0x56) = -15.130 dB  error(-0.130 dB)
    0x55,       // [031] = -15.500 dB  ->  AKM(0x55) = -15.534 dB  error(-0.034 dB)
    0x54,       // [032] = -16.000 dB  ->  AKM(0x54) = -15.958 dB  error(+0.042 dB)
    0x53,       // [033] = -16.500 dB  ->  AKM(0x53) = -16.404 dB  error(+0.096 dB)
    0x52,       // [034] = -17.000 dB  ->  AKM(0x52) = -16.874 dB  error(+0.126 dB)
    0x51,       // [035] = -17.500 dB  ->  AKM(0x51) = -17.371 dB  error(+0.129 dB)
    0x50,       // [036] = -18.000 dB  ->  AKM(0x50) = -17.898 dB  error(+0.102 dB)
    0x4e,       // [037] = -18.500 dB  ->  AKM(0x4e) = -18.605 dB  error(-0.105 dB)
    0x4d,       // [038] = -19.000 dB  ->  AKM(0x4d) = -18.905 dB  error(+0.095 dB)
    0x4b,       // [039] = -19.500 dB  ->  AKM(0x4b) = -19.538 dB  error(-0.038 dB)
    0x4a,       // [040] = -20.000 dB  ->  AKM(0x4a) = -19.872 dB  error(+0.128 dB)
    0x48,       // [041] = -20.500 dB  ->  AKM(0x48) = -20.583 dB  error(-0.083 dB)
    0x47,       // [042] = -21.000 dB  ->  AKM(0x47) = -20.961 dB  error(+0.039 dB)
    0x46,       // [043] = -21.500 dB  ->  AKM(0x46) = -21.356 dB  error(+0.144 dB)
    0x44,       // [044] = -22.000 dB  ->  AKM(0x44) = -22.206 dB  error(-0.206 dB)
    0x43,       // [045] = -22.500 dB  ->  AKM(0x43) = -22.664 dB  error(-0.164 dB)
    0x42,       // [046] = -23.000 dB  ->  AKM(0x42) = -23.147 dB  error(-0.147 dB)
    0x41,       // [047] = -23.500 dB  ->  AKM(0x41) = -23.659 dB  error(-0.159 dB)
    0x40,       // [048] = -24.000 dB  ->  AKM(0x40) = -24.203 dB  error(-0.203 dB)
    0x3f,       // [049] = -24.500 dB  ->  AKM(0x3f) = -24.635 dB  error(-0.135 dB)
    0x3e,       // [050] = -25.000 dB  ->  AKM(0x3e) = -24.935 dB  error(+0.065 dB)
    0x3c,       // [051] = -25.500 dB  ->  AKM(0x3c) = -25.569 dB  error(-0.069 dB)
    0x3b,       // [052] = -26.000 dB  ->  AKM(0x3b) = -25.904 dB  error(+0.096 dB)
    0x39,       // [053] = -26.500 dB  ->  AKM(0x39) = -26.615 dB  error(-0.115 dB)
    0x38,       // [054] = -27.000 dB  ->  AKM(0x38) = -26.994 dB  error(+0.006 dB)
    0x37,       // [055] = -27.500 dB  ->  AKM(0x37) = -27.390 dB  error(+0.110 dB)
    0x36,       // [056] = -28.000 dB  ->  AKM(0x36) = -27.804 dB  error(+0.196 dB)
    0x34,       // [057] = -28.500 dB  ->  AKM(0x34) = -28.699 dB  error(-0.199 dB)
    0x33,       // [058] = -29.000 dB  ->  AKM(0x33) = -29.183 dB  error(-0.183 dB)
    0x32,       // [059] = -29.500 dB  ->  AKM(0x32) = -29.696 dB  error(-0.196 dB)
    0x31,       // [060] = -30.000 dB  ->  AKM(0x31) = -30.241 dB  error(-0.241 dB)
    0x31,       // [061] = -30.500 dB  ->  AKM(0x31) = -30.241 dB  error(+0.259 dB)
    0x30,       // [062] = -31.000 dB  ->  AKM(0x30) = -30.823 dB  error(+0.177 dB)
    0x2e,       // [063] = -31.500 dB  ->  AKM(0x2e) = -31.610 dB  error(-0.110 dB)
    0x2d,       // [064] = -32.000 dB  ->  AKM(0x2d) = -31.945 dB  error(+0.055 dB)
    0x2b,       // [065] = -32.500 dB  ->  AKM(0x2b) = -32.659 dB  error(-0.159 dB)
    0x2a,       // [066] = -33.000 dB  ->  AKM(0x2a) = -33.038 dB  error(-0.038 dB)
    0x29,       // [067] = -33.500 dB  ->  AKM(0x29) = -33.435 dB  error(+0.065 dB)
    0x28,       // [068] = -34.000 dB  ->  AKM(0x28) = -33.852 dB  error(+0.148 dB)
    0x27,       // [069] = -34.500 dB  ->  AKM(0x27) = -34.289 dB  error(+0.211 dB)
    0x25,       // [070] = -35.000 dB  ->  AKM(0x25) = -35.235 dB  error(-0.235 dB)
    0x24,       // [071] = -35.500 dB  ->  AKM(0x24) = -35.750 dB  error(-0.250 dB)
    0x24,       // [072] = -36.000 dB  ->  AKM(0x24) = -35.750 dB  error(+0.250 dB)
    0x23,       // [073] = -36.500 dB  ->  AKM(0x23) = -36.297 dB  error(+0.203 dB)
    0x22,       // [074] = -37.000 dB  ->  AKM(0x22) = -36.881 dB  error(+0.119 dB)
    0x21,       // [075] = -37.500 dB  ->  AKM(0x21) = -37.508 dB  error(-0.008 dB)
    0x20,       // [076] = -38.000 dB  ->  AKM(0x20) = -38.183 dB  error(-0.183 dB)
    0x1f,       // [077] = -38.500 dB  ->  AKM(0x1f) = -38.726 dB  error(-0.226 dB)
    0x1e,       // [078] = -39.000 dB  ->  AKM(0x1e) = -39.108 dB  error(-0.108 dB)
    0x1d,       // [079] = -39.500 dB  ->  AKM(0x1d) = -39.507 dB  error(-0.007 dB)
    0x1c,       // [080] = -40.000 dB  ->  AKM(0x1c) = -39.926 dB  error(+0.074 dB)
    0x1b,       // [081] = -40.500 dB  ->  AKM(0x1b) = -40.366 dB  error(+0.134 dB)
    0x1a,       // [082] = -41.000 dB  ->  AKM(0x1a) = -40.829 dB  error(+0.171 dB)
    0x19,       // [083] = -41.500 dB  ->  AKM(0x19) = -41.318 dB  error(+0.182 dB)
    0x18,       // [084] = -42.000 dB  ->  AKM(0x18) = -41.837 dB  error(+0.163 dB)
    0x17,       // [085] = -42.500 dB  ->  AKM(0x17) = -42.389 dB  error(+0.111 dB)
    0x16,       // [086] = -43.000 dB  ->  AKM(0x16) = -42.978 dB  error(+0.022 dB)
    0x15,       // [087] = -43.500 dB  ->  AKM(0x15) = -43.610 dB  error(-0.110 dB)
    0x14,       // [088] = -44.000 dB  ->  AKM(0x14) = -44.291 dB  error(-0.291 dB)
    0x14,       // [089] = -44.500 dB  ->  AKM(0x14) = -44.291 dB  error(+0.209 dB)
    0x13,       // [090] = -45.000 dB  ->  AKM(0x13) = -45.031 dB  error(-0.031 dB)
    0x12,       // [091] = -45.500 dB  ->  AKM(0x12) = -45.840 dB  error(-0.340 dB)
    0x12,       // [092] = -46.000 dB  ->  AKM(0x12) = -45.840 dB  error(+0.160 dB)
    0x11,       // [093] = -46.500 dB  ->  AKM(0x11) = -46.731 dB  error(-0.231 dB)
    0x11,       // [094] = -47.000 dB  ->  AKM(0x11) = -46.731 dB  error(+0.269 dB)
    0x10,       // [095] = -47.500 dB  ->  AKM(0x10) = -47.725 dB  error(-0.225 dB)
    0x10,       // [096] = -48.000 dB  ->  AKM(0x10) = -47.725 dB  error(+0.275 dB)
    0x0f,       // [097] = -48.500 dB  ->  AKM(0x0f) = -48.553 dB  error(-0.053 dB)
    0x0e,       // [098] = -49.000 dB  ->  AKM(0x0e) = -49.152 dB  error(-0.152 dB)
    0x0d,       // [099] = -49.500 dB  ->  AKM(0x0d) = -49.796 dB  error(-0.296 dB)
    0x0d,       // [100] = -50.000 dB  ->  AKM(0x0d) = -49.796 dB  error(+0.204 dB)
    0x0c,       // [101] = -50.500 dB  ->  AKM(0x0c) = -50.491 dB  error(+0.009 dB)
    0x0b,       // [102] = -51.000 dB  ->  AKM(0x0b) = -51.247 dB  error(-0.247 dB)
    0x0b,       // [103] = -51.500 dB  ->  AKM(0x0b) = -51.247 dB  error(+0.253 dB)
    0x0a,       // [104] = -52.000 dB  ->  AKM(0x0a) = -52.075 dB  error(-0.075 dB)
    0x0a,       // [105] = -52.500 dB  ->  AKM(0x0a) = -52.075 dB  error(+0.425 dB)
    0x09,       // [106] = -53.000 dB  ->  AKM(0x09) = -52.990 dB  error(+0.010 dB)
    0x09,       // [107] = -53.500 dB  ->  AKM(0x09) = -52.990 dB  error(+0.510 dB)
    0x08,       // [108] = -54.000 dB  ->  AKM(0x08) = -54.013 dB  error(-0.013 dB)
    0x08,       // [109] = -54.500 dB  ->  AKM(0x08) = -54.013 dB  error(+0.487 dB)
    0x07,       // [110] = -55.000 dB  ->  AKM(0x07) = -55.173 dB  error(-0.173 dB)
    0x07,       // [111] = -55.500 dB  ->  AKM(0x07) = -55.173 dB  error(+0.327 dB)
    0x06,       // [112] = -56.000 dB  ->  AKM(0x06) = -56.512 dB  error(-0.512 dB)
    0x06,       // [113] = -56.500 dB  ->  AKM(0x06) = -56.512 dB  error(-0.012 dB)
    0x06,       // [114] = -57.000 dB  ->  AKM(0x06) = -56.512 dB  error(+0.488 dB)
    0x05,       // [115] = -57.500 dB  ->  AKM(0x05) = -58.095 dB  error(-0.595 dB)
    0x05,       // [116] = -58.000 dB  ->  AKM(0x05) = -58.095 dB  error(-0.095 dB)
    0x05,       // [117] = -58.500 dB  ->  AKM(0x05) = -58.095 dB  error(+0.405 dB)
    0x05,       // [118] = -59.000 dB  ->  AKM(0x05) = -58.095 dB  error(+0.905 dB)
    0x04,       // [119] = -59.500 dB  ->  AKM(0x04) = -60.034 dB  error(-0.534 dB)
    0x04,       // [120] = -60.000 dB  ->  AKM(0x04) = -60.034 dB  error(-0.034 dB)
    0x04,       // [121] = -60.500 dB  ->  AKM(0x04) = -60.034 dB  error(+0.466 dB)
    0x04,       // [122] = -61.000 dB  ->  AKM(0x04) = -60.034 dB  error(+0.966 dB)
    0x03,       // [123] = -61.500 dB  ->  AKM(0x03) = -62.532 dB  error(-1.032 dB)
    0x03,       // [124] = -62.000 dB  ->  AKM(0x03) = -62.532 dB  error(-0.532 dB)
    0x03,       // [125] = -62.500 dB  ->  AKM(0x03) = -62.532 dB  error(-0.032 dB)
    0x03,       // [126] = -63.000 dB  ->  AKM(0x03) = -62.532 dB  error(+0.468 dB)
    0x03,       // [127] = -63.500 dB  ->  AKM(0x03) = -62.532 dB  error(+0.968 dB)
    0x03,       // [128] = -64.000 dB  ->  AKM(0x03) = -62.532 dB  error(+1.468 dB)
    0x02,       // [129] = -64.500 dB  ->  AKM(0x02) = -66.054 dB  error(-1.554 dB)
    0x02,       // [130] = -65.000 dB  ->  AKM(0x02) = -66.054 dB  error(-1.054 dB)
    0x02,       // [131] = -65.500 dB  ->  AKM(0x02) = -66.054 dB  error(-0.554 dB)
    0x02,       // [132] = -66.000 dB  ->  AKM(0x02) = -66.054 dB  error(-0.054 dB)
    0x02,       // [133] = -66.500 dB  ->  AKM(0x02) = -66.054 dB  error(+0.446 dB)
    0x02,       // [134] = -67.000 dB  ->  AKM(0x02) = -66.054 dB  error(+0.946 dB)
    0x02,       // [135] = -67.500 dB  ->  AKM(0x02) = -66.054 dB  error(+1.446 dB)
    0x02,       // [136] = -68.000 dB  ->  AKM(0x02) = -66.054 dB  error(+1.946 dB)
    0x02,       // [137] = -68.500 dB  ->  AKM(0x02) = -66.054 dB  error(+2.446 dB)
    0x02,       // [138] = -69.000 dB  ->  AKM(0x02) = -66.054 dB  error(+2.946 dB)
    0x01,       // [139] = -69.500 dB  ->  AKM(0x01) = -72.075 dB  error(-2.575 dB)
    0x01,       // [140] = -70.000 dB  ->  AKM(0x01) = -72.075 dB  error(-2.075 dB)
    0x01,       // [141] = -70.500 dB  ->  AKM(0x01) = -72.075 dB  error(-1.575 dB)
    0x01,       // [142] = -71.000 dB  ->  AKM(0x01) = -72.075 dB  error(-1.075 dB)
    0x01,       // [143] = -71.500 dB  ->  AKM(0x01) = -72.075 dB  error(-0.575 dB)
    0x01,       // [144] = -72.000 dB  ->  AKM(0x01) = -72.075 dB  error(-0.075 dB)
    0x01,       // [145] = -72.500 dB  ->  AKM(0x01) = -72.075 dB  error(+0.425 dB)
    0x01,       // [146] = -73.000 dB  ->  AKM(0x01) = -72.075 dB  error(+0.925 dB)
    0x00पूर्ण;      // [147] = -73.500 dB  ->  AKM(0x00) =  mute       error(+infini)

/*
 * pseuकरो-codec ग_लिखो entry
 */
अटल व्योम vx2_ग_लिखो_akm(काष्ठा vx_core *chip, पूर्णांक reg, अचिन्हित पूर्णांक data)
अणु
	अचिन्हित पूर्णांक val;

	अगर (reg == XX_CODEC_DAC_CONTROL_REGISTER) अणु
		vx2_ग_लिखो_codec_reg(chip, data ? AKM_CODEC_MUTE_CMD : AKM_CODEC_UNMUTE_CMD);
		वापस;
	पूर्ण

	/* `data' is a value between 0x0 and VX2_AKM_LEVEL_MAX = 0x093, in the हाल of the AKM codecs, we need
	   a look up table, as there is no linear matching between the driver codec values
	   and the real dBu value
	*/
	अगर (snd_BUG_ON(data >= माप(vx2_akm_gains_lut)))
		वापस;

	चयन (reg) अणु
	हाल XX_CODEC_LEVEL_LEFT_REGISTER:
		val = AKM_CODEC_LEFT_LEVEL_CMD;
		अवरोध;
	हाल XX_CODEC_LEVEL_RIGHT_REGISTER:
		val = AKM_CODEC_RIGHT_LEVEL_CMD;
		अवरोध;
	शेष:
		snd_BUG();
		वापस;
	पूर्ण
	val |= vx2_akm_gains_lut[data];

	vx2_ग_लिखो_codec_reg(chip, val);
पूर्ण


/*
 * ग_लिखो codec bit क्रम old VX222 board
 */
अटल व्योम vx2_old_ग_लिखो_codec_bit(काष्ठा vx_core *chip, पूर्णांक codec, अचिन्हित पूर्णांक data)
अणु
	पूर्णांक i;

	/* activate access to codec रेजिस्टरs */
	vx_inl(chip, HIFREQ);

	क्रम (i = 0; i < 24; i++, data <<= 1)
		vx_outl(chip, DATA, ((data & 0x800000) ? VX_DATA_CODEC_MASK : 0));

	/* Terminate access to codec रेजिस्टरs */
	vx_inl(chip, RUER);
पूर्ण


/*
 * reset codec bit
 */
अटल व्योम vx2_reset_codec(काष्ठा vx_core *_chip)
अणु
	काष्ठा snd_vx222 *chip = to_vx222(_chip);

	/* Set the reset CODEC bit to 0. */
	vx_outl(chip, CDSP, chip->regCDSP &~ VX_CDSP_CODEC_RESET_MASK);
	vx_inl(chip, CDSP);
	msleep(10);
	/* Set the reset CODEC bit to 1. */
	chip->regCDSP |= VX_CDSP_CODEC_RESET_MASK;
	vx_outl(chip, CDSP, chip->regCDSP);
	vx_inl(chip, CDSP);
	अगर (_chip->type == VX_TYPE_BOARD) अणु
		msleep(1);
		वापस;
	पूर्ण

	msleep(5);  /* additionnel रुको समय क्रम AKM's */

	vx2_ग_लिखो_codec_reg(_chip, AKM_CODEC_POWER_CONTROL_CMD); /* DAC घातer up, ADC घातer up, Vref घातer करोwn */
	
	vx2_ग_लिखो_codec_reg(_chip, AKM_CODEC_CLOCK_FORMAT_CMD); /* शेष */
	vx2_ग_लिखो_codec_reg(_chip, AKM_CODEC_MUTE_CMD); /* Mute = ON ,Deemphasis = OFF */
	vx2_ग_लिखो_codec_reg(_chip, AKM_CODEC_RESET_OFF_CMD); /* DAC and ADC normal operation */

	अगर (_chip->type == VX_TYPE_MIC) अणु
		/* set up the micro input selector */
		chip->regSELMIC =  MICRO_SELECT_INPUT_NORM |
			MICRO_SELECT_PREAMPLI_G_0 |
			MICRO_SELECT_NOISE_T_52DB;

		/* reset phantom घातer supply */
		chip->regSELMIC &= ~MICRO_SELECT_PHANTOM_ALIM;

		vx_outl(_chip, SELMIC, chip->regSELMIC);
	पूर्ण
पूर्ण


/*
 * change the audio source
 */
अटल व्योम vx2_change_audio_source(काष्ठा vx_core *_chip, पूर्णांक src)
अणु
	काष्ठा snd_vx222 *chip = to_vx222(_chip);

	चयन (src) अणु
	हाल VX_AUDIO_SRC_DIGITAL:
		chip->regCFG |= VX_CFG_DATAIN_SEL_MASK;
		अवरोध;
	शेष:
		chip->regCFG &= ~VX_CFG_DATAIN_SEL_MASK;
		अवरोध;
	पूर्ण
	vx_outl(chip, CFG, chip->regCFG);
पूर्ण


/*
 * set the घड़ी source
 */
अटल व्योम vx2_set_घड़ी_source(काष्ठा vx_core *_chip, पूर्णांक source)
अणु
	काष्ठा snd_vx222 *chip = to_vx222(_chip);

	अगर (source == INTERNAL_QUARTZ)
		chip->regCFG &= ~VX_CFG_CLOCKIN_SEL_MASK;
	अन्यथा
		chip->regCFG |= VX_CFG_CLOCKIN_SEL_MASK;
	vx_outl(chip, CFG, chip->regCFG);
पूर्ण

/*
 * reset the board
 */
अटल व्योम vx2_reset_board(काष्ठा vx_core *_chip, पूर्णांक cold_reset)
अणु
	काष्ठा snd_vx222 *chip = to_vx222(_chip);

	/* initialize the रेजिस्टर values */
	chip->regCDSP = VX_CDSP_CODEC_RESET_MASK | VX_CDSP_DSP_RESET_MASK ;
	chip->regCFG = 0;
पूर्ण



/*
 * input level controls क्रम VX222 Mic
 */

/* Micro level is specअगरied to be adjustable from -96dB to 63 dB (board coded 0x00 ... 318),
 * 318 = 210 + 36 + 36 + 36   (210 = +9dB variable) (3 * 36 = 3 steps of 18dB pre ampli)
 * as we will mute अगर less than -110dB, so let's simply use line input coded levels and add स्थिरant offset !
 */
#घोषणा V2_MICRO_LEVEL_RANGE        (318 - 255)

अटल व्योम vx2_set_input_level(काष्ठा snd_vx222 *chip)
अणु
	पूर्णांक i, miclevel, preamp;
	अचिन्हित पूर्णांक data;

	miclevel = chip->mic_level;
	miclevel += V2_MICRO_LEVEL_RANGE; /* add 318 - 0xff */
	preamp = 0;
        जबतक (miclevel > 210) अणु /* limitation to +9dB of 3310 real gain */
		preamp++;	/* उठाओ pre ampli + 18dB */
		miclevel -= (18 * 2);   /* lower level 18 dB (*2 because of 0.5 dB steps !) */
        पूर्ण
	अगर (snd_BUG_ON(preamp >= 4))
		वापस;

	/* set pre-amp level */
	chip->regSELMIC &= ~MICRO_SELECT_PREAMPLI_MASK;
	chip->regSELMIC |= (preamp << MICRO_SELECT_PREAMPLI_OFFSET) & MICRO_SELECT_PREAMPLI_MASK;
	vx_outl(chip, SELMIC, chip->regSELMIC);

	data = (अचिन्हित पूर्णांक)miclevel << 16 |
		(अचिन्हित पूर्णांक)chip->input_level[1] << 8 |
		(अचिन्हित पूर्णांक)chip->input_level[0];
	vx_inl(chip, DATA); /* Activate input level programming */

	/* We have to send 32 bits (4 x 8 bits) */
	क्रम (i = 0; i < 32; i++, data <<= 1)
		vx_outl(chip, DATA, ((data & 0x80000000) ? VX_DATA_CODEC_MASK : 0));

	vx_inl(chip, RUER); /* Terminate input level programming */
पूर्ण


#घोषणा MIC_LEVEL_MAX	0xff

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_mic, -6450, 50, 0);

/*
 * controls API क्रम input levels
 */

/* input levels */
अटल पूर्णांक vx_input_level_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = MIC_LEVEL_MAX;
	वापस 0;
पूर्ण

अटल पूर्णांक vx_input_level_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा vx_core *_chip = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_vx222 *chip = to_vx222(_chip);
	mutex_lock(&_chip->mixer_mutex);
	ucontrol->value.पूर्णांकeger.value[0] = chip->input_level[0];
	ucontrol->value.पूर्णांकeger.value[1] = chip->input_level[1];
	mutex_unlock(&_chip->mixer_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक vx_input_level_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा vx_core *_chip = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_vx222 *chip = to_vx222(_chip);
	अगर (ucontrol->value.पूर्णांकeger.value[0] < 0 ||
	    ucontrol->value.पूर्णांकeger.value[0] > MIC_LEVEL_MAX)
		वापस -EINVAL;
	अगर (ucontrol->value.पूर्णांकeger.value[1] < 0 ||
	    ucontrol->value.पूर्णांकeger.value[1] > MIC_LEVEL_MAX)
		वापस -EINVAL;
	mutex_lock(&_chip->mixer_mutex);
	अगर (chip->input_level[0] != ucontrol->value.पूर्णांकeger.value[0] ||
	    chip->input_level[1] != ucontrol->value.पूर्णांकeger.value[1]) अणु
		chip->input_level[0] = ucontrol->value.पूर्णांकeger.value[0];
		chip->input_level[1] = ucontrol->value.पूर्णांकeger.value[1];
		vx2_set_input_level(chip);
		mutex_unlock(&_chip->mixer_mutex);
		वापस 1;
	पूर्ण
	mutex_unlock(&_chip->mixer_mutex);
	वापस 0;
पूर्ण

/* mic level */
अटल पूर्णांक vx_mic_level_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = MIC_LEVEL_MAX;
	वापस 0;
पूर्ण

अटल पूर्णांक vx_mic_level_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा vx_core *_chip = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_vx222 *chip = to_vx222(_chip);
	ucontrol->value.पूर्णांकeger.value[0] = chip->mic_level;
	वापस 0;
पूर्ण

अटल पूर्णांक vx_mic_level_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा vx_core *_chip = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_vx222 *chip = to_vx222(_chip);
	अगर (ucontrol->value.पूर्णांकeger.value[0] < 0 ||
	    ucontrol->value.पूर्णांकeger.value[0] > MIC_LEVEL_MAX)
		वापस -EINVAL;
	mutex_lock(&_chip->mixer_mutex);
	अगर (chip->mic_level != ucontrol->value.पूर्णांकeger.value[0]) अणु
		chip->mic_level = ucontrol->value.पूर्णांकeger.value[0];
		vx2_set_input_level(chip);
		mutex_unlock(&_chip->mixer_mutex);
		वापस 1;
	पूर्ण
	mutex_unlock(&_chip->mixer_mutex);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new vx_control_input_level = अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.access =	(SNDRV_CTL_ELEM_ACCESS_READWRITE |
			 SNDRV_CTL_ELEM_ACCESS_TLV_READ),
	.name =		"Capture Volume",
	.info =		vx_input_level_info,
	.get =		vx_input_level_get,
	.put =		vx_input_level_put,
	.tlv = अणु .p = db_scale_mic पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new vx_control_mic_level = अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.access =	(SNDRV_CTL_ELEM_ACCESS_READWRITE |
			 SNDRV_CTL_ELEM_ACCESS_TLV_READ),
	.name =		"Mic Capture Volume",
	.info =		vx_mic_level_info,
	.get =		vx_mic_level_get,
	.put =		vx_mic_level_put,
	.tlv = अणु .p = db_scale_mic पूर्ण,
पूर्ण;

/*
 * FIXME: compressor/limiter implementation is missing yet...
 */

अटल पूर्णांक vx2_add_mic_controls(काष्ठा vx_core *_chip)
अणु
	काष्ठा snd_vx222 *chip = to_vx222(_chip);
	पूर्णांक err;

	अगर (_chip->type != VX_TYPE_MIC)
		वापस 0;

	/* mute input levels */
	chip->input_level[0] = chip->input_level[1] = 0;
	chip->mic_level = 0;
	vx2_set_input_level(chip);

	/* controls */
	अगर ((err = snd_ctl_add(_chip->card, snd_ctl_new1(&vx_control_input_level, chip))) < 0)
		वापस err;
	अगर ((err = snd_ctl_add(_chip->card, snd_ctl_new1(&vx_control_mic_level, chip))) < 0)
		वापस err;

	वापस 0;
पूर्ण


/*
 * callbacks
 */
स्थिर काष्ठा snd_vx_ops vx222_ops = अणु
	.in8 = vx2_inb,
	.in32 = vx2_inl,
	.out8 = vx2_outb,
	.out32 = vx2_outl,
	.test_and_ack = vx2_test_and_ack,
	.validate_irq = vx2_validate_irq,
	.akm_ग_लिखो = vx2_ग_लिखो_akm,
	.reset_codec = vx2_reset_codec,
	.change_audio_source = vx2_change_audio_source,
	.set_घड़ी_source = vx2_set_घड़ी_source,
	.load_dsp = vx2_load_dsp,
	.reset_dsp = vx2_reset_dsp,
	.reset_board = vx2_reset_board,
	.dma_ग_लिखो = vx2_dma_ग_लिखो,
	.dma_पढ़ो = vx2_dma_पढ़ो,
	.add_controls = vx2_add_mic_controls,
पूर्ण;

/* क्रम old VX222 board */
स्थिर काष्ठा snd_vx_ops vx222_old_ops = अणु
	.in8 = vx2_inb,
	.in32 = vx2_inl,
	.out8 = vx2_outb,
	.out32 = vx2_outl,
	.test_and_ack = vx2_test_and_ack,
	.validate_irq = vx2_validate_irq,
	.ग_लिखो_codec = vx2_old_ग_लिखो_codec_bit,
	.reset_codec = vx2_reset_codec,
	.change_audio_source = vx2_change_audio_source,
	.set_घड़ी_source = vx2_set_घड़ी_source,
	.load_dsp = vx2_load_dsp,
	.reset_dsp = vx2_reset_dsp,
	.reset_board = vx2_reset_board,
	.dma_ग_लिखो = vx2_dma_ग_लिखो,
	.dma_पढ़ो = vx2_dma_पढ़ो,
पूर्ण;

