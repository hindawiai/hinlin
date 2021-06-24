<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Digigram VXpocket soundcards
 *
 * lowlevel routines क्रम VXpocket soundcards
 *
 * Copyright (c) 2002 by Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/firmware.h>
#समावेश <linux/पन.स>
#समावेश <sound/core.h>
#समावेश "vxpocket.h"


अटल स्थिर पूर्णांक vxp_reg_offset[VX_REG_MAX] = अणु
	[VX_ICR]	= 0x00,		// ICR
	[VX_CVR]	= 0x01,		// CVR
	[VX_ISR]	= 0x02,		// ISR
	[VX_IVR]	= 0x03,		// IVR
	[VX_RXH]	= 0x05,		// RXH
	[VX_RXM]	= 0x06,		// RXM
	[VX_RXL]	= 0x07,		// RXL
	[VX_DMA]	= 0x04,		// DMA
	[VX_CDSP]	= 0x08,		// CDSP
	[VX_LOFREQ]	= 0x09,		// LFREQ
	[VX_HIFREQ]	= 0x0a,		// HFREQ
	[VX_DATA]	= 0x0b,		// DATA
	[VX_MICRO]	= 0x0c,		// MICRO
	[VX_DIALOG]	= 0x0d,		// DIALOG
	[VX_CSUER]	= 0x0e,		// CSUER
	[VX_RUER]	= 0x0f,		// RUER
पूर्ण;


अटल अंतरभूत अचिन्हित दीर्घ vxp_reg_addr(काष्ठा vx_core *_chip, पूर्णांक reg)
अणु
	काष्ठा snd_vxpocket *chip = to_vxpocket(_chip);
	वापस chip->port + vxp_reg_offset[reg];
पूर्ण

/*
 * snd_vx_inb - पढ़ो a byte from the रेजिस्टर
 * @offset: रेजिस्टर offset
 */
अटल अचिन्हित अक्षर vxp_inb(काष्ठा vx_core *chip, पूर्णांक offset)
अणु
	वापस inb(vxp_reg_addr(chip, offset));
पूर्ण

/*
 * snd_vx_outb - ग_लिखो a byte on the रेजिस्टर
 * @offset: the रेजिस्टर offset
 * @val: the value to ग_लिखो
 */
अटल व्योम vxp_outb(काष्ठा vx_core *chip, पूर्णांक offset, अचिन्हित अक्षर val)
अणु
	outb(val, vxp_reg_addr(chip, offset));
पूर्ण

/*
 * redefine macros to call directly
 */
#अघोषित vx_inb
#घोषणा vx_inb(chip,reg)	vxp_inb((काष्ठा vx_core *)(chip), VX_##reg)
#अघोषित vx_outb
#घोषणा vx_outb(chip,reg,val)	vxp_outb((काष्ठा vx_core *)(chip), VX_##reg,val)


/*
 * vx_check_magic - check the magic word on xilinx
 *
 * वापसs zero अगर a magic word is detected, or a negative error code.
 */
अटल पूर्णांक vx_check_magic(काष्ठा vx_core *chip)
अणु
	अचिन्हित दीर्घ end_समय = jअगरfies + HZ / 5;
	पूर्णांक c;
	करो अणु
		c = vx_inb(chip, CDSP);
		अगर (c == CDSP_MAGIC)
			वापस 0;
		msleep(10);
	पूर्ण जबतक (समय_after_eq(end_समय, jअगरfies));
	snd_prपूर्णांकk(KERN_ERR "cannot find xilinx magic word (%x)\n", c);
	वापस -EIO;
पूर्ण


/*
 * vx_reset_dsp - reset the DSP
 */

#घोषणा XX_DSP_RESET_WAIT_TIME		2	/* ms */

अटल व्योम vxp_reset_dsp(काष्ठा vx_core *_chip)
अणु
	काष्ठा snd_vxpocket *chip = to_vxpocket(_chip);

	/* set the reset dsp bit to 1 */
	vx_outb(chip, CDSP, chip->regCDSP | VXP_CDSP_DSP_RESET_MASK);
	vx_inb(chip, CDSP);
	mdelay(XX_DSP_RESET_WAIT_TIME);
	/* reset the bit */
	chip->regCDSP &= ~VXP_CDSP_DSP_RESET_MASK;
	vx_outb(chip, CDSP, chip->regCDSP);
	vx_inb(chip, CDSP);
	mdelay(XX_DSP_RESET_WAIT_TIME);
पूर्ण

/*
 * reset codec bit
 */
अटल व्योम vxp_reset_codec(काष्ठा vx_core *_chip)
अणु
	काष्ठा snd_vxpocket *chip = to_vxpocket(_chip);

	/* Set the reset CODEC bit to 1. */
	vx_outb(chip, CDSP, chip->regCDSP | VXP_CDSP_CODEC_RESET_MASK);
	vx_inb(chip, CDSP);
	msleep(10);
	/* Set the reset CODEC bit to 0. */
	chip->regCDSP &= ~VXP_CDSP_CODEC_RESET_MASK;
	vx_outb(chip, CDSP, chip->regCDSP);
	vx_inb(chip, CDSP);
	msleep(1);
पूर्ण

/*
 * vx_load_xilinx_binary - load the xilinx binary image
 * the binary image is the binary array converted from the bitstream file.
 */
अटल पूर्णांक vxp_load_xilinx_binary(काष्ठा vx_core *_chip, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा snd_vxpocket *chip = to_vxpocket(_chip);
	अचिन्हित पूर्णांक i;
	पूर्णांक c;
	पूर्णांक regCSUER, regRUER;
	स्थिर अचिन्हित अक्षर *image;
	अचिन्हित अक्षर data;

	/* Switch to programmation mode */
	chip->regDIALOG |= VXP_DLG_XILINX_REPROG_MASK;
	vx_outb(chip, DIALOG, chip->regDIALOG);

	/* Save रेजिस्टर CSUER and RUER */
	regCSUER = vx_inb(chip, CSUER);
	regRUER = vx_inb(chip, RUER);

	/* reset HF0 and HF1 */
	vx_outb(chip, ICR, 0);

	/* Wait क्रम answer HF2 equal to 1 */
	snd_prपूर्णांकdd(KERN_DEBUG "check ISR_HF2\n");
	अगर (vx_check_isr(_chip, ISR_HF2, ISR_HF2, 20) < 0)
		जाओ _error;

	/* set HF1 क्रम loading xilinx binary */
	vx_outb(chip, ICR, ICR_HF1);
	image = fw->data;
	क्रम (i = 0; i < fw->size; i++, image++) अणु
		data = *image;
		अगर (vx_रुको_isr_bit(_chip, ISR_TX_EMPTY) < 0)
			जाओ _error;
		vx_outb(chip, TXL, data);
		/* रुको क्रम पढ़ोing */
		अगर (vx_रुको_क्रम_rx_full(_chip) < 0)
			जाओ _error;
		c = vx_inb(chip, RXL);
		अगर (c != (पूर्णांक)data)
			snd_prपूर्णांकk(KERN_ERR "vxpocket: load xilinx mismatch at %d: 0x%x != 0x%x\n", i, c, (पूर्णांक)data);
        पूर्ण

	/* reset HF1 */
	vx_outb(chip, ICR, 0);

	/* रुको क्रम HF3 */
	अगर (vx_check_isr(_chip, ISR_HF3, ISR_HF3, 20) < 0)
		जाओ _error;

	/* पढ़ो the number of bytes received */
	अगर (vx_रुको_क्रम_rx_full(_chip) < 0)
		जाओ _error;

	c = (पूर्णांक)vx_inb(chip, RXH) << 16;
	c |= (पूर्णांक)vx_inb(chip, RXM) << 8;
	c |= vx_inb(chip, RXL);

	snd_prपूर्णांकdd(KERN_DEBUG "xilinx: dsp size received 0x%x, orig 0x%zx\n", c, fw->size);

	vx_outb(chip, ICR, ICR_HF0);

	/* TEMPO 250ms : रुको until Xilinx is करोwnloaded */
	msleep(300);

	/* test magical word */
	अगर (vx_check_magic(_chip) < 0)
		जाओ _error;

	/* Restore रेजिस्टर 0x0E and 0x0F (thus replacing COR and FCSR) */
	vx_outb(chip, CSUER, regCSUER);
	vx_outb(chip, RUER, regRUER);

	/* Reset the Xilinx's संकेत enabling IO access */
	chip->regDIALOG |= VXP_DLG_XILINX_REPROG_MASK;
	vx_outb(chip, DIALOG, chip->regDIALOG);
	vx_inb(chip, DIALOG);
	msleep(10);
	chip->regDIALOG &= ~VXP_DLG_XILINX_REPROG_MASK;
	vx_outb(chip, DIALOG, chip->regDIALOG);
	vx_inb(chip, DIALOG);

	/* Reset of the Codec */
	vxp_reset_codec(_chip);
	vx_reset_dsp(_chip);

	वापस 0;

 _error:
	vx_outb(chip, CSUER, regCSUER);
	vx_outb(chip, RUER, regRUER);
	chip->regDIALOG &= ~VXP_DLG_XILINX_REPROG_MASK;
	vx_outb(chip, DIALOG, chip->regDIALOG);
	वापस -EIO;
पूर्ण


/*
 * vxp_load_dsp - load_dsp callback
 */
अटल पूर्णांक vxp_load_dsp(काष्ठा vx_core *vx, पूर्णांक index, स्थिर काष्ठा firmware *fw)
अणु
	पूर्णांक err;

	चयन (index) अणु
	हाल 0:
		/* xilinx boot */
		अगर ((err = vx_check_magic(vx)) < 0)
			वापस err;
		अगर ((err = snd_vx_load_boot_image(vx, fw)) < 0)
			वापस err;
		वापस 0;
	हाल 1:
		/* xilinx image */
		वापस vxp_load_xilinx_binary(vx, fw);
	हाल 2:
		/* DSP boot */
		वापस snd_vx_dsp_boot(vx, fw);
	हाल 3:
		/* DSP image */
		वापस snd_vx_dsp_load(vx, fw);
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
अटल पूर्णांक vxp_test_and_ack(काष्ठा vx_core *_chip)
अणु
	काष्ठा snd_vxpocket *chip = to_vxpocket(_chip);

	/* not booted yet? */
	अगर (! (_chip->chip_status & VX_STAT_XILINX_LOADED))
		वापस -ENXIO;

	अगर (! (vx_inb(chip, DIALOG) & VXP_DLG_MEMIRQ_MASK))
		वापस -EIO;
	
	/* ok, पूर्णांकerrupts generated, now ack it */
	/* set ACQUIT bit up and करोwn */
	vx_outb(chip, DIALOG, chip->regDIALOG | VXP_DLG_ACK_MEMIRQ_MASK);
	/* useless पढ़ो just to spend some समय and मुख्यtain
	 * the ACQUIT संकेत up क्रम a जबतक ( a bus cycle )
	 */
	vx_inb(chip, DIALOG);
	vx_outb(chip, DIALOG, chip->regDIALOG & ~VXP_DLG_ACK_MEMIRQ_MASK);

	वापस 0;
पूर्ण


/*
 * vx_validate_irq - enable/disable IRQ
 */
अटल व्योम vxp_validate_irq(काष्ठा vx_core *_chip, पूर्णांक enable)
अणु
	काष्ठा snd_vxpocket *chip = to_vxpocket(_chip);

	/* Set the पूर्णांकerrupt enable bit to 1 in CDSP रेजिस्टर */
	अगर (enable)
		chip->regCDSP |= VXP_CDSP_VALID_IRQ_MASK;
	अन्यथा
		chip->regCDSP &= ~VXP_CDSP_VALID_IRQ_MASK;
	vx_outb(chip, CDSP, chip->regCDSP);
पूर्ण

/*
 * vx_setup_pseuकरो_dma - set up the pseuकरो dma पढ़ो/ग_लिखो mode.
 * @करो_ग_लिखो: 0 = पढ़ो, 1 = set up क्रम DMA ग_लिखो
 */
अटल व्योम vx_setup_pseuकरो_dma(काष्ठा vx_core *_chip, पूर्णांक करो_ग_लिखो)
अणु
	काष्ठा snd_vxpocket *chip = to_vxpocket(_chip);

	/* Interrupt mode and HREQ pin enabled क्रम host transmit / receive data transfers */
	vx_outb(chip, ICR, करो_ग_लिखो ? ICR_TREQ : ICR_RREQ);
	/* Reset the pseuकरो-dma रेजिस्टर */
	vx_inb(chip, ISR);
	vx_outb(chip, ISR, 0);

	/* Select DMA in पढ़ो/ग_लिखो transfer mode and in 16-bit accesses */
	chip->regDIALOG |= VXP_DLG_DMA16_SEL_MASK;
	chip->regDIALOG |= करो_ग_लिखो ? VXP_DLG_DMAWRITE_SEL_MASK : VXP_DLG_DMAREAD_SEL_MASK;
	vx_outb(chip, DIALOG, chip->regDIALOG);

पूर्ण

/*
 * vx_release_pseuकरो_dma - disable the pseuकरो-DMA mode
 */
अटल व्योम vx_release_pseuकरो_dma(काष्ठा vx_core *_chip)
अणु
	काष्ठा snd_vxpocket *chip = to_vxpocket(_chip);

	/* Disable DMA and 16-bit accesses */
	chip->regDIALOG &= ~(VXP_DLG_DMAWRITE_SEL_MASK|
			     VXP_DLG_DMAREAD_SEL_MASK|
			     VXP_DLG_DMA16_SEL_MASK);
	vx_outb(chip, DIALOG, chip->regDIALOG);
	/* HREQ pin disabled. */
	vx_outb(chip, ICR, 0);
पूर्ण

/*
 * vx_pseuकरो_dma_ग_लिखो - ग_लिखो bulk data on pseuकरो-DMA mode
 * @count: data length to transfer in bytes
 *
 * data size must be aligned to 6 bytes to ensure the 24bit alignment on DSP.
 * NB: call with a certain lock!
 */
अटल व्योम vxp_dma_ग_लिखो(काष्ठा vx_core *chip, काष्ठा snd_pcm_runसमय *runसमय,
			  काष्ठा vx_pipe *pipe, पूर्णांक count)
अणु
	दीर्घ port = vxp_reg_addr(chip, VX_DMA);
	पूर्णांक offset = pipe->hw_ptr;
	अचिन्हित लघु *addr = (अचिन्हित लघु *)(runसमय->dma_area + offset);

	vx_setup_pseuकरो_dma(chip, 1);
	अगर (offset + count >= pipe->buffer_bytes) अणु
		पूर्णांक length = pipe->buffer_bytes - offset;
		count -= length;
		length >>= 1; /* in 16bit words */
		/* Transfer using pseuकरो-dma. */
		क्रम (; length > 0; length--) अणु
			outw(*addr, port);
			addr++;
		पूर्ण
		addr = (अचिन्हित लघु *)runसमय->dma_area;
		pipe->hw_ptr = 0;
	पूर्ण
	pipe->hw_ptr += count;
	count >>= 1; /* in 16bit words */
	/* Transfer using pseuकरो-dma. */
	क्रम (; count > 0; count--) अणु
		outw(*addr, port);
		addr++;
	पूर्ण
	vx_release_pseuकरो_dma(chip);
पूर्ण


/*
 * vx_pseuकरो_dma_पढ़ो - पढ़ो bulk data on pseuकरो DMA mode
 * @offset: buffer offset in bytes
 * @count: data length to transfer in bytes
 *
 * the पढ़ो length must be aligned to 6 bytes, as well as ग_लिखो.
 * NB: call with a certain lock!
 */
अटल व्योम vxp_dma_पढ़ो(काष्ठा vx_core *chip, काष्ठा snd_pcm_runसमय *runसमय,
			 काष्ठा vx_pipe *pipe, पूर्णांक count)
अणु
	काष्ठा snd_vxpocket *pchip = to_vxpocket(chip);
	दीर्घ port = vxp_reg_addr(chip, VX_DMA);
	पूर्णांक offset = pipe->hw_ptr;
	अचिन्हित लघु *addr = (अचिन्हित लघु *)(runसमय->dma_area + offset);

	अगर (snd_BUG_ON(count % 2))
		वापस;
	vx_setup_pseuकरो_dma(chip, 0);
	अगर (offset + count >= pipe->buffer_bytes) अणु
		पूर्णांक length = pipe->buffer_bytes - offset;
		count -= length;
		length >>= 1; /* in 16bit words */
		/* Transfer using pseuकरो-dma. */
		क्रम (; length > 0; length--)
			*addr++ = inw(port);
		addr = (अचिन्हित लघु *)runसमय->dma_area;
		pipe->hw_ptr = 0;
	पूर्ण
	pipe->hw_ptr += count;
	count >>= 1; /* in 16bit words */
	/* Transfer using pseuकरो-dma. */
	क्रम (; count > 1; count--)
		*addr++ = inw(port);
	/* Disable DMA */
	pchip->regDIALOG &= ~VXP_DLG_DMAREAD_SEL_MASK;
	vx_outb(chip, DIALOG, pchip->regDIALOG);
	/* Read the last word (16 bits) */
	*addr = inw(port);
	/* Disable 16-bit accesses */
	pchip->regDIALOG &= ~VXP_DLG_DMA16_SEL_MASK;
	vx_outb(chip, DIALOG, pchip->regDIALOG);
	/* HREQ pin disabled. */
	vx_outb(chip, ICR, 0);
पूर्ण


/*
 * ग_लिखो a codec data (24bit)
 */
अटल व्योम vxp_ग_लिखो_codec_reg(काष्ठा vx_core *chip, पूर्णांक codec, अचिन्हित पूर्णांक data)
अणु
	पूर्णांक i;

	/* Activate access to the corresponding codec रेजिस्टर */
	अगर (! codec)
		vx_inb(chip, LOFREQ);
	अन्यथा
		vx_inb(chip, CODEC2);
		
	/* We have to send 24 bits (3 x 8 bits). Start with most signअगर. Bit */
	क्रम (i = 0; i < 24; i++, data <<= 1)
		vx_outb(chip, DATA, ((data & 0x800000) ? VX_DATA_CODEC_MASK : 0));
	
	/* Terminate access to codec रेजिस्टरs */
	vx_inb(chip, HIFREQ);
पूर्ण


/*
 * vx_set_mic_boost - set mic boost level (on vxp440 only)
 * @boost: 0 = 20dB, 1 = +38dB
 */
व्योम vx_set_mic_boost(काष्ठा vx_core *chip, पूर्णांक boost)
अणु
	काष्ठा snd_vxpocket *pchip = to_vxpocket(chip);

	अगर (chip->chip_status & VX_STAT_IS_STALE)
		वापस;

	mutex_lock(&chip->lock);
	अगर (pchip->regCDSP & P24_CDSP_MICS_SEL_MASK) अणु
		अगर (boost) अणु
			/* boost: 38 dB */
			pchip->regCDSP &= ~P24_CDSP_MIC20_SEL_MASK;
			pchip->regCDSP |=  P24_CDSP_MIC38_SEL_MASK;
		पूर्ण अन्यथा अणु
			/* minimum value: 20 dB */
			pchip->regCDSP |=  P24_CDSP_MIC20_SEL_MASK;
			pchip->regCDSP &= ~P24_CDSP_MIC38_SEL_MASK;
                पूर्ण
		vx_outb(chip, CDSP, pchip->regCDSP);
	पूर्ण
	mutex_unlock(&chip->lock);
पूर्ण

/*
 * remap the linear value (0-8) to the actual value (0-15)
 */
अटल पूर्णांक vx_compute_mic_level(पूर्णांक level)
अणु
	चयन (level) अणु
	हाल 5: level = 6 ; अवरोध;
	हाल 6: level = 8 ; अवरोध;
	हाल 7: level = 11; अवरोध;
	हाल 8: level = 15; अवरोध;
	शेष: अवरोध ;
	पूर्ण
	वापस level;
पूर्ण

/*
 * vx_set_mic_level - set mic level (on vxpocket only)
 * @level: the mic level = 0 - 8 (max)
 */
व्योम vx_set_mic_level(काष्ठा vx_core *chip, पूर्णांक level)
अणु
	काष्ठा snd_vxpocket *pchip = to_vxpocket(chip);

	अगर (chip->chip_status & VX_STAT_IS_STALE)
		वापस;

	mutex_lock(&chip->lock);
	अगर (pchip->regCDSP & VXP_CDSP_MIC_SEL_MASK) अणु
		level = vx_compute_mic_level(level);
		vx_outb(chip, MICRO, level);
	पूर्ण
	mutex_unlock(&chip->lock);
पूर्ण


/*
 * change the input audio source
 */
अटल व्योम vxp_change_audio_source(काष्ठा vx_core *_chip, पूर्णांक src)
अणु
	काष्ठा snd_vxpocket *chip = to_vxpocket(_chip);

	चयन (src) अणु
	हाल VX_AUDIO_SRC_DIGITAL:
		chip->regCDSP |= VXP_CDSP_DATAIN_SEL_MASK;
		vx_outb(chip, CDSP, chip->regCDSP);
		अवरोध;
	हाल VX_AUDIO_SRC_LINE:
		chip->regCDSP &= ~VXP_CDSP_DATAIN_SEL_MASK;
		अगर (_chip->type == VX_TYPE_VXP440)
			chip->regCDSP &= ~P24_CDSP_MICS_SEL_MASK;
		अन्यथा
			chip->regCDSP &= ~VXP_CDSP_MIC_SEL_MASK;
		vx_outb(chip, CDSP, chip->regCDSP);
		अवरोध;
	हाल VX_AUDIO_SRC_MIC:
		chip->regCDSP &= ~VXP_CDSP_DATAIN_SEL_MASK;
		/* reset mic levels */
		अगर (_chip->type == VX_TYPE_VXP440) अणु
			chip->regCDSP &= ~P24_CDSP_MICS_SEL_MASK;
			अगर (chip->mic_level)
				chip->regCDSP |=  P24_CDSP_MIC38_SEL_MASK;
			अन्यथा
				chip->regCDSP |= P24_CDSP_MIC20_SEL_MASK;
			vx_outb(chip, CDSP, chip->regCDSP);
		पूर्ण अन्यथा अणु
			chip->regCDSP |= VXP_CDSP_MIC_SEL_MASK;
			vx_outb(chip, CDSP, chip->regCDSP);
			vx_outb(chip, MICRO, vx_compute_mic_level(chip->mic_level));
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

/*
 * change the घड़ी source
 * source = INTERNAL_QUARTZ or UER_SYNC
 */
अटल व्योम vxp_set_घड़ी_source(काष्ठा vx_core *_chip, पूर्णांक source)
अणु
	काष्ठा snd_vxpocket *chip = to_vxpocket(_chip);

	अगर (source == INTERNAL_QUARTZ)
		chip->regCDSP &= ~VXP_CDSP_CLOCKIN_SEL_MASK;
	अन्यथा
		chip->regCDSP |= VXP_CDSP_CLOCKIN_SEL_MASK;
	vx_outb(chip, CDSP, chip->regCDSP);
पूर्ण


/*
 * reset the board
 */
अटल व्योम vxp_reset_board(काष्ठा vx_core *_chip, पूर्णांक cold_reset)
अणु
	काष्ठा snd_vxpocket *chip = to_vxpocket(_chip);

	chip->regCDSP = 0;
	chip->regDIALOG = 0;
पूर्ण


/*
 * callbacks
 */
/* exported */
स्थिर काष्ठा snd_vx_ops snd_vxpocket_ops = अणु
	.in8 = vxp_inb,
	.out8 = vxp_outb,
	.test_and_ack = vxp_test_and_ack,
	.validate_irq = vxp_validate_irq,
	.ग_लिखो_codec = vxp_ग_लिखो_codec_reg,
	.reset_codec = vxp_reset_codec,
	.change_audio_source = vxp_change_audio_source,
	.set_घड़ी_source = vxp_set_घड़ी_source,
	.load_dsp = vxp_load_dsp,
	.add_controls = vxp_add_mic_controls,
	.reset_dsp = vxp_reset_dsp,
	.reset_board = vxp_reset_board,
	.dma_ग_लिखो = vxp_dma_ग_लिखो,
	.dma_पढ़ो = vxp_dma_पढ़ो,
पूर्ण;
