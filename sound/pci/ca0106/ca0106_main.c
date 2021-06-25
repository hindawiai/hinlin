<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 2004 James Courtier-Dutton <James@superbug.demon.co.uk>
 *  Driver CA0106 chips. e.g. Sound Blaster Audigy LS and Live 24bit
 *  Version: 0.0.25
 *
 *  FEATURES currently supported:
 *    Front, Rear and Center/LFE.
 *    Surround40 and Surround51.
 *    Capture from MIC an LINE IN input.
 *    SPDIF digital playback of PCM stereo and AC3/DTS works.
 *    (One can use a standard mono mini-jack to one RCA plugs cable.
 *     or one can use a standard stereo mini-jack to two RCA plugs cable.
 *     Plug one of the RCA plugs पूर्णांकo the Coax input of the बाह्यal decoder/receiver.)
 *    ( In theory one could output 3 dअगरferent AC3 streams at once, to 3 dअगरferent SPDIF outमाला_दो. )
 *    Notes on how to capture sound:
 *      The AC97 is used in the PLAYBACK direction.
 *      The output from the AC97 chip, instead of reaching the speakers, is fed पूर्णांकo the Philips 1361T ADC.
 *      So, to record from the MIC, set the MIC Playback volume to max,
 *      unmute the MIC and turn up the MASTER Playback volume.
 *      So, to prevent feedback when capturing, minimise the "Capture feedback into Playback" volume.
 *   
 *    The only playback controls that currently करो anything are: -
 *    Analog Front
 *    Analog Rear
 *    Analog Center/LFE
 *    SPDIF Front
 *    SPDIF Rear
 *    SPDIF Center/LFE
 *   
 *    For capture from Mic in or Line in.
 *    Digital/Analog ( चयन must be in Analog mode क्रम CAPTURE. )
 * 
 *    CAPTURE feedback पूर्णांकo PLAYBACK
 * 
 *  Changelog:
 *    Support पूर्णांकerrupts per period.
 *    Removed noise from Center/LFE channel when in Analog mode.
 *    Rename and हटाओ mixer controls.
 *  0.0.6
 *    Use separate card based DMA buffer क्रम periods table list.
 *  0.0.7
 *    Change हटाओ and नाम ctrls पूर्णांकo lists.
 *  0.0.8
 *    Try to fix capture sources.
 *  0.0.9
 *    Fix AC3 output.
 *    Enable S32_LE क्रमmat support.
 *  0.0.10
 *    Enable playback 48000 and 96000 rates. (Rates other that these करो not work, even with "plug:front".)
 *  0.0.11
 *    Add Model name recognition.
 *  0.0.12
 *    Correct पूर्णांकerrupt timing. पूर्णांकerrupt at end of period, instead of in the middle of a playback period.
 *    Remove redundent "voice" handling.
 *  0.0.13
 *    Single trigger call क्रम multi channels.
 *  0.0.14
 *    Set limits based on what the sound card hardware can करो.
 *    playback periods_min=2, periods_max=8
 *    capture hw स्थिरraपूर्णांकs require period_size = n * 64 bytes.
 *    playback hw स्थिरraपूर्णांकs require period_size = n * 64 bytes.
 *  0.0.15
 *    Minor updates.
 *  0.0.16
 *    Implement 192000 sample rate.
 *  0.0.17
 *    Add support क्रम SB0410 and SB0413.
 *  0.0.18
 *    Modअगरied Copyright message.
 *  0.0.19
 *    Finally fix support क्रम SB Live 24 bit. SB0410 and SB0413.
 *    The output codec needs resetting, otherwise all output is muted.
 *  0.0.20
 *    Merge "pci_disable_device(pci);" fixes.
 *  0.0.21
 *    Add 4 capture channels. (SPDIF only comes in on channel 0. )
 *    Add SPDIF capture using optional digital I/O module क्रम SB Live 24bit. (Analog capture करोes not yet work.)
 *  0.0.22
 *    Add support क्रम MSI K8N Diamond Motherboard with onboard SB Live 24bit without AC97. From kiksen, bug #901
 *  0.0.23
 *    Implement support क्रम Line-in capture on SB Live 24bit.
 *  0.0.24
 *    Add support क्रम mute control on SB Live 24bit (cards w/ SPI DAC)
 *  0.0.25
 *    Powerकरोwn SPI DAC channels when not in use
 *
 *  BUGS:
 *    Some stability problems when unloading the snd-ca0106 kernel module.
 *    --
 *
 *  TODO:
 *    4 Capture channels, only one implemented so far.
 *    Other capture rates apart from 48khz not implemented.
 *    MIDI
 *    --
 *  GENERAL INFO:
 *    Model: SB0310
 *    P17 Chip: CA0106-DAT
 *    AC97 Codec: STAC 9721
 *    ADC: Philips 1361T (Stereo 24bit)
 *    DAC: WM8746EDS (6-channel, 24bit, 192Khz)
 *
 *  GENERAL INFO:
 *    Model: SB0410
 *    P17 Chip: CA0106-DAT
 *    AC97 Codec: None
 *    ADC: WM8775EDS (4 Channel)
 *    DAC: CS4382 (114 dB, 24-Bit, 192 kHz, 8-Channel D/A Converter with DSD Support)
 *    SPDIF Out control चयनes between Mic in and SPDIF out.
 *    No sound out or mic input working yet.
 * 
 *  GENERAL INFO:
 *    Model: SB0413
 *    P17 Chip: CA0106-DAT
 *    AC97 Codec: None.
 *    ADC: Unknown
 *    DAC: Unknown
 *    Trying to handle it like the SB0410.
 *
 *  This code was initially based on code from ALSA's emu10k1x.c which is:
 *  Copyright (c) by Francisco Moraes <fmoraes@nc.rr.com>
 */
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/dma-mapping.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/info.h>

MODULE_AUTHOR("James Courtier-Dutton <James@superbug.demon.co.uk>");
MODULE_DESCRIPTION("CA0106");
MODULE_LICENSE("GPL");

// module parameters (see "Module Parameters")
अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;
अटल uपूर्णांक subप्रणाली[SNDRV_CARDS]; /* Force card subप्रणाली model */

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for the CA0106 soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for the CA0106 soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable the CA0106 soundcard.");
module_param_array(subप्रणाली, uपूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(subप्रणाली, "Force card subsystem model.");

#समावेश "ca0106.h"

अटल स्थिर काष्ठा snd_ca0106_details ca0106_chip_details[] = अणु
	 /* Sound Blaster X-Fi Extreme Audio. This करोes not have an AC97. 53SB079000000 */
	 /* It is really just a normal SB Live 24bit. */
	 /* Tested:
	  * See ALSA bug#3251
	  */
	 अणु .serial = 0x10131102,
	   .name   = "X-Fi Extreme Audio [SBxxxx]",
	   .gpio_type = 1,
	   .i2c_adc = 1 पूर्ण ,
	 /* Sound Blaster X-Fi Extreme Audio. This करोes not have an AC97. 53SB079000000 */
	 /* It is really just a normal SB Live 24bit. */
	 /*
 	  * CTRL:CA0111-WTLF
	  * ADC: WM8775SEDS
	  * DAC: CS4382-KQZ
	  */
	 /* Tested:
	  * Playback on front, rear, center/lfe speakers
	  * Capture from Mic in.
	  * Not-Tested:
	  * Capture from Line in.
	  * Playback to digital out.
	  */
	 अणु .serial = 0x10121102,
	   .name   = "X-Fi Extreme Audio [SB0790]",
	   .gpio_type = 1,
	   .i2c_adc = 1 पूर्ण ,
	 /* New Dell Sound Blaster Live! 7.1 24bit. This करोes not have an AC97.  */
	 /* AudigyLS[SB0310] */
	 अणु .serial = 0x10021102,
	   .name   = "AudigyLS [SB0310]",
	   .ac97   = 1 पूर्ण , 
	 /* Unknown AudigyLS that also says SB0310 on it */
	 अणु .serial = 0x10051102,
	   .name   = "AudigyLS [SB0310b]",
	   .ac97   = 1 पूर्ण ,
	 /* New Sound Blaster Live! 7.1 24bit. This करोes not have an AC97. 53SB041000001 */
	 अणु .serial = 0x10061102,
	   .name   = "Live! 7.1 24bit [SB0410]",
	   .gpio_type = 1,
	   .i2c_adc = 1 पूर्ण ,
	 /* New Dell Sound Blaster Live! 7.1 24bit. This करोes not have an AC97.  */
	 अणु .serial = 0x10071102,
	   .name   = "Live! 7.1 24bit [SB0413]",
	   .gpio_type = 1,
	   .i2c_adc = 1 पूर्ण ,
	 /* New Audigy SE. Has a dअगरferent DAC. */
	 /* SB0570:
	  * CTRL:CA0106-DAT
	  * ADC: WM8775EDS
	  * DAC: WM8768GEDS
	  */
	 अणु .serial = 0x100a1102,
	   .name   = "Audigy SE [SB0570]",
	   .gpio_type = 1,
	   .i2c_adc = 1,
	   .spi_dac = 0x4021 पूर्ण ,
	 /* New Audigy LS. Has a dअगरferent DAC. */
	 /* SB0570:
	  * CTRL:CA0106-DAT
	  * ADC: WM8775EDS
	  * DAC: WM8768GEDS
	  */
	 अणु .serial = 0x10111102,
	   .name   = "Audigy SE OEM [SB0570a]",
	   .gpio_type = 1,
	   .i2c_adc = 1,
	   .spi_dac = 0x4021 पूर्ण ,
	/* Sound Blaster 5.1vx
	 * Tested: Playback on front, rear, center/lfe speakers
	 * Not-Tested: Capture
	 */
	अणु .serial = 0x10041102,
	  .name   = "Sound Blaster 5.1vx [SB1070]",
	  .gpio_type = 1,
	  .i2c_adc = 0,
	  .spi_dac = 0x0124
	 पूर्ण ,
	 /* MSI K8N Diamond Motherboard with onboard SB Live 24bit without AC97 */
	 /* SB0438
	  * CTRL:CA0106-DAT
	  * ADC: WM8775SEDS
	  * DAC: CS4382-KQZ
	  */
	 अणु .serial = 0x10091462,
	   .name   = "MSI K8N Diamond MB [SB0438]",
	   .gpio_type = 2,
	   .i2c_adc = 1 पूर्ण ,
	 /* MSI K8N Diamond PLUS MB */
	 अणु .serial = 0x10091102,
	   .name   = "MSI K8N Diamond MB",
	   .gpio_type = 2,
	   .i2c_adc = 1,
	   .spi_dac = 0x4021 पूर्ण ,
	/* Giga-byte GA-G1975X mobo
	 * Novell bnc#395807
	 */
	/* FIXME: the GPIO and I2C setting aren't tested well */
	अणु .serial = 0x1458a006,
	  .name = "Giga-byte GA-G1975X",
	  .gpio_type = 1,
	  .i2c_adc = 1 पूर्ण,
	 /* Shuttle XPC SD31P which has an onboard Creative Lअसल
	  * Sound Blaster Live! 24-bit EAX
	  * high-definition 7.1 audio processor".
	  * Added using info from andrewvegan in alsa bug #1298
	  */
	 अणु .serial = 0x30381297,
	   .name   = "Shuttle XPC SD31P [SD31P]",
	   .gpio_type = 1,
	   .i2c_adc = 1 पूर्ण ,
	/* Shuttle XPC SD11G5 which has an onboard Creative Lअसल
	 * Sound Blaster Live! 24-bit EAX
	 * high-definition 7.1 audio processor".
	 * Fixes ALSA bug#1600
         */
	अणु .serial = 0x30411297,
	  .name = "Shuttle XPC SD11G5 [SD11G5]",
	  .gpio_type = 1,
	  .i2c_adc = 1 पूर्ण ,
	 अणु .serial = 0,
	   .name   = "AudigyLS [Unknown]" पूर्ण
पूर्ण;

/* hardware definition */
अटल स्थिर काष्ठा snd_pcm_hardware snd_ca0106_playback_hw = अणु
	.info =			SNDRV_PCM_INFO_MMAP | 
				SNDRV_PCM_INFO_INTERLEAVED |
				SNDRV_PCM_INFO_BLOCK_TRANSFER |
				SNDRV_PCM_INFO_MMAP_VALID |
				SNDRV_PCM_INFO_SYNC_START,
	.क्रमmats =		SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S32_LE,
	.rates =		(SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_96000 |
				 SNDRV_PCM_RATE_192000),
	.rate_min =		48000,
	.rate_max =		192000,
	.channels_min =		2,  //1,
	.channels_max =		2,  //6,
	.buffer_bytes_max =	((65536 - 64) * 8),
	.period_bytes_min =	64,
	.period_bytes_max =	(65536 - 64),
	.periods_min =		2,
	.periods_max =		8,
	.fअगरo_size =		0,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_ca0106_capture_hw = अणु
	.info =			(SNDRV_PCM_INFO_MMAP | 
				 SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S32_LE,
#अगर 0 /* FIXME: looks like 44.1kHz capture causes noisy output on 48kHz */
	.rates =		(SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000 |
				 SNDRV_PCM_RATE_96000 | SNDRV_PCM_RATE_192000),
	.rate_min =		44100,
#अन्यथा
	.rates =		(SNDRV_PCM_RATE_48000 |
				 SNDRV_PCM_RATE_96000 | SNDRV_PCM_RATE_192000),
	.rate_min =		48000,
#पूर्ण_अगर /* FIXME */
	.rate_max =		192000,
	.channels_min =		2,
	.channels_max =		2,
	.buffer_bytes_max =	65536 - 128,
	.period_bytes_min =	64,
	.period_bytes_max =	32768 - 64,
	.periods_min =		2,
	.periods_max =		2,
	.fअगरo_size =		0,
पूर्ण;

अचिन्हित पूर्णांक snd_ca0106_ptr_पढ़ो(काष्ठा snd_ca0106 * emu, 
					  अचिन्हित पूर्णांक reg, 
					  अचिन्हित पूर्णांक chn)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक regptr, val;
  
	regptr = (reg << 16) | chn;

	spin_lock_irqsave(&emu->emu_lock, flags);
	outl(regptr, emu->port + PTR);
	val = inl(emu->port + DATA);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
	वापस val;
पूर्ण

व्योम snd_ca0106_ptr_ग_लिखो(काष्ठा snd_ca0106 *emu, 
				   अचिन्हित पूर्णांक reg, 
				   अचिन्हित पूर्णांक chn, 
				   अचिन्हित पूर्णांक data)
अणु
	अचिन्हित पूर्णांक regptr;
	अचिन्हित दीर्घ flags;

	regptr = (reg << 16) | chn;

	spin_lock_irqsave(&emu->emu_lock, flags);
	outl(regptr, emu->port + PTR);
	outl(data, emu->port + DATA);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
पूर्ण

पूर्णांक snd_ca0106_spi_ग_लिखो(काष्ठा snd_ca0106 * emu,
				   अचिन्हित पूर्णांक data)
अणु
	अचिन्हित पूर्णांक reset, set;
	अचिन्हित पूर्णांक reg, पंचांगp;
	पूर्णांक n, result;
	reg = SPI;
	अगर (data > 0xffff) /* Only 16bit values allowed */
		वापस 1;
	पंचांगp = snd_ca0106_ptr_पढ़ो(emu, reg, 0);
	reset = (पंचांगp & ~0x3ffff) | 0x20000; /* Set xxx20000 */
	set = reset | 0x10000; /* Set xxx1xxxx */
	snd_ca0106_ptr_ग_लिखो(emu, reg, 0, reset | data);
	पंचांगp = snd_ca0106_ptr_पढ़ो(emu, reg, 0); /* ग_लिखो post */
	snd_ca0106_ptr_ग_लिखो(emu, reg, 0, set | data);
	result = 1;
	/* Wait क्रम status bit to वापस to 0 */
	क्रम (n = 0; n < 100; n++) अणु
		udelay(10);
		पंचांगp = snd_ca0106_ptr_पढ़ो(emu, reg, 0);
		अगर (!(पंचांगp & 0x10000)) अणु
			result = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (result) /* Timed out */
		वापस 1;
	snd_ca0106_ptr_ग_लिखो(emu, reg, 0, reset | data);
	पंचांगp = snd_ca0106_ptr_पढ़ो(emu, reg, 0); /* Write post */
	वापस 0;
पूर्ण

/* The ADC करोes not support i2c पढ़ो, so only ग_लिखो is implemented */
पूर्णांक snd_ca0106_i2c_ग_लिखो(काष्ठा snd_ca0106 *emu,
				u32 reg,
				u32 value)
अणु
	u32 पंचांगp;
	पूर्णांक समयout = 0;
	पूर्णांक status;
	पूर्णांक retry;
	अगर ((reg > 0x7f) || (value > 0x1ff)) अणु
		dev_err(emu->card->dev, "i2c_write: invalid values.\n");
		वापस -EINVAL;
	पूर्ण

	पंचांगp = reg << 25 | value << 16;
	/*
	dev_dbg(emu->card->dev, "I2C-write:reg=0x%x, value=0x%x\n", reg, value);
	*/
	/* Not sure what this I2C channel controls. */
	/* snd_ca0106_ptr_ग_लिखो(emu, I2C_D0, 0, पंचांगp); */

	/* This controls the I2C connected to the WM8775 ADC Codec */
	snd_ca0106_ptr_ग_लिखो(emu, I2C_D1, 0, पंचांगp);

	क्रम (retry = 0; retry < 10; retry++) अणु
		/* Send the data to i2c */
		//पंचांगp = snd_ca0106_ptr_पढ़ो(emu, I2C_A, 0);
		//पंचांगp = पंचांगp & ~(I2C_A_ADC_READ|I2C_A_ADC_LAST|I2C_A_ADC_START|I2C_A_ADC_ADD_MASK);
		पंचांगp = 0;
		पंचांगp = पंचांगp | (I2C_A_ADC_LAST|I2C_A_ADC_START|I2C_A_ADC_ADD);
		snd_ca0106_ptr_ग_लिखो(emu, I2C_A, 0, पंचांगp);

		/* Wait till the transaction ends */
		जबतक (1) अणु
			status = snd_ca0106_ptr_पढ़ो(emu, I2C_A, 0);
			/*dev_dbg(emu->card->dev, "I2C:status=0x%x\n", status);*/
			समयout++;
			अगर ((status & I2C_A_ADC_START) == 0)
				अवरोध;

			अगर (समयout > 1000)
				अवरोध;
		पूर्ण
		//Read back and see अगर the transaction is successful
		अगर ((status & I2C_A_ADC_ABORT) == 0)
			अवरोध;
	पूर्ण

	अगर (retry == 10) अणु
		dev_err(emu->card->dev, "Writing to ADC failed!\n");
		वापस -EINVAL;
	पूर्ण
    
    	वापस 0;
पूर्ण


अटल व्योम snd_ca0106_पूर्णांकr_enable(काष्ठा snd_ca0106 *emu, अचिन्हित पूर्णांक पूर्णांकrenb)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक पूर्णांकr_enable;

	spin_lock_irqsave(&emu->emu_lock, flags);
	पूर्णांकr_enable = inl(emu->port + INTE) | पूर्णांकrenb;
	outl(पूर्णांकr_enable, emu->port + INTE);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
पूर्ण

अटल व्योम snd_ca0106_पूर्णांकr_disable(काष्ठा snd_ca0106 *emu, अचिन्हित पूर्णांक पूर्णांकrenb)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक पूर्णांकr_enable;

	spin_lock_irqsave(&emu->emu_lock, flags);
	पूर्णांकr_enable = inl(emu->port + INTE) & ~पूर्णांकrenb;
	outl(पूर्णांकr_enable, emu->port + INTE);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
पूर्ण


अटल व्योम snd_ca0106_pcm_मुक्त_substream(काष्ठा snd_pcm_runसमय *runसमय)
अणु
	kमुक्त(runसमय->निजी_data);
पूर्ण

अटल स्थिर पूर्णांक spi_dacd_reg[] = अणु
	SPI_DACD0_REG,
	SPI_DACD1_REG,
	SPI_DACD2_REG,
	0,
	SPI_DACD4_REG,
पूर्ण;
अटल स्थिर पूर्णांक spi_dacd_bit[] = अणु
	SPI_DACD0_BIT,
	SPI_DACD1_BIT,
	SPI_DACD2_BIT,
	0,
	SPI_DACD4_BIT,
पूर्ण;

अटल व्योम restore_spdअगर_bits(काष्ठा snd_ca0106 *chip, पूर्णांक idx)
अणु
	अगर (chip->spdअगर_str_bits[idx] != chip->spdअगर_bits[idx]) अणु
		chip->spdअगर_str_bits[idx] = chip->spdअगर_bits[idx];
		snd_ca0106_ptr_ग_लिखो(chip, SPCS0 + idx, 0,
				     chip->spdअगर_str_bits[idx]);
	पूर्ण
पूर्ण

अटल पूर्णांक snd_ca0106_channel_dac(काष्ठा snd_ca0106 *chip,
				  स्थिर काष्ठा snd_ca0106_details *details,
				  पूर्णांक channel_id)
अणु
	चयन (channel_id) अणु
	हाल PCM_FRONT_CHANNEL:
		वापस (details->spi_dac & 0xf000) >> (4 * 3);
	हाल PCM_REAR_CHANNEL:
		वापस (details->spi_dac & 0x0f00) >> (4 * 2);
	हाल PCM_CENTER_LFE_CHANNEL:
		वापस (details->spi_dac & 0x00f0) >> (4 * 1);
	हाल PCM_UNKNOWN_CHANNEL:
		वापस (details->spi_dac & 0x000f) >> (4 * 0);
	शेष:
		dev_dbg(chip->card->dev, "ca0106: unknown channel_id %d\n",
			   channel_id);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ca0106_pcm_घातer_dac(काष्ठा snd_ca0106 *chip, पूर्णांक channel_id,
				    पूर्णांक घातer)
अणु
	अगर (chip->details->spi_dac) अणु
		स्थिर पूर्णांक dac = snd_ca0106_channel_dac(chip, chip->details,
						       channel_id);
		स्थिर पूर्णांक reg = spi_dacd_reg[dac];
		स्थिर पूर्णांक bit = spi_dacd_bit[dac];

		अगर (घातer)
			/* Power up */
			chip->spi_dac_reg[reg] &= ~bit;
		अन्यथा
			/* Power करोwn */
			chip->spi_dac_reg[reg] |= bit;
		अगर (snd_ca0106_spi_ग_लिखो(chip, chip->spi_dac_reg[reg]) != 0)
			वापस -ENXIO;
	पूर्ण
	वापस 0;
पूर्ण

/* खोलो_playback callback */
अटल पूर्णांक snd_ca0106_pcm_खोलो_playback_channel(काष्ठा snd_pcm_substream *substream,
						पूर्णांक channel_id)
अणु
	काष्ठा snd_ca0106 *chip = snd_pcm_substream_chip(substream);
        काष्ठा snd_ca0106_channel *channel = &(chip->playback_channels[channel_id]);
	काष्ठा snd_ca0106_pcm *epcm;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

	epcm = kzalloc(माप(*epcm), GFP_KERNEL);

	अगर (epcm == शून्य)
		वापस -ENOMEM;
	epcm->emu = chip;
	epcm->substream = substream;
        epcm->channel_id=channel_id;
  
	runसमय->निजी_data = epcm;
	runसमय->निजी_मुक्त = snd_ca0106_pcm_मुक्त_substream;
  
	runसमय->hw = snd_ca0106_playback_hw;

        channel->emu = chip;
        channel->number = channel_id;

	channel->use = 1;
	/*
	dev_dbg(chip->card->dev, "open:channel_id=%d, chip=%p, channel=%p\n",
	       channel_id, chip, channel);
	*/
        //channel->पूर्णांकerrupt = snd_ca0106_pcm_channel_पूर्णांकerrupt;
	channel->epcm = epcm;
	अगर ((err = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय, SNDRV_PCM_HW_PARAM_PERIODS)) < 0)
                वापस err;
	अगर ((err = snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 64)) < 0)
                वापस err;
	snd_pcm_set_sync(substream);

	/* Front channel dac should alपढ़ोy be on */
	अगर (channel_id != PCM_FRONT_CHANNEL) अणु
		err = snd_ca0106_pcm_घातer_dac(chip, channel_id, 1);
		अगर (err < 0)
			वापस err;
	पूर्ण

	restore_spdअगर_bits(chip, channel_id);

	वापस 0;
पूर्ण

/* बंद callback */
अटल पूर्णांक snd_ca0106_pcm_बंद_playback(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ca0106 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
        काष्ठा snd_ca0106_pcm *epcm = runसमय->निजी_data;
	chip->playback_channels[epcm->channel_id].use = 0;

	restore_spdअगर_bits(chip, epcm->channel_id);

	/* Front channel dac should stay on */
	अगर (epcm->channel_id != PCM_FRONT_CHANNEL) अणु
		पूर्णांक err;
		err = snd_ca0106_pcm_घातer_dac(chip, epcm->channel_id, 0);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* FIXME: maybe zero others */
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ca0106_pcm_खोलो_playback_front(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_ca0106_pcm_खोलो_playback_channel(substream, PCM_FRONT_CHANNEL);
पूर्ण

अटल पूर्णांक snd_ca0106_pcm_खोलो_playback_center_lfe(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_ca0106_pcm_खोलो_playback_channel(substream, PCM_CENTER_LFE_CHANNEL);
पूर्ण

अटल पूर्णांक snd_ca0106_pcm_खोलो_playback_unknown(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_ca0106_pcm_खोलो_playback_channel(substream, PCM_UNKNOWN_CHANNEL);
पूर्ण

अटल पूर्णांक snd_ca0106_pcm_खोलो_playback_rear(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_ca0106_pcm_खोलो_playback_channel(substream, PCM_REAR_CHANNEL);
पूर्ण

/* खोलो_capture callback */
अटल पूर्णांक snd_ca0106_pcm_खोलो_capture_channel(काष्ठा snd_pcm_substream *substream,
					       पूर्णांक channel_id)
अणु
	काष्ठा snd_ca0106 *chip = snd_pcm_substream_chip(substream);
        काष्ठा snd_ca0106_channel *channel = &(chip->capture_channels[channel_id]);
	काष्ठा snd_ca0106_pcm *epcm;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

	epcm = kzalloc(माप(*epcm), GFP_KERNEL);
	अगर (!epcm)
		वापस -ENOMEM;

	epcm->emu = chip;
	epcm->substream = substream;
        epcm->channel_id=channel_id;
  
	runसमय->निजी_data = epcm;
	runसमय->निजी_मुक्त = snd_ca0106_pcm_मुक्त_substream;
  
	runसमय->hw = snd_ca0106_capture_hw;

        channel->emu = chip;
        channel->number = channel_id;

	channel->use = 1;
	/*
	dev_dbg(chip->card->dev, "open:channel_id=%d, chip=%p, channel=%p\n",
	       channel_id, chip, channel);
	*/
        //channel->पूर्णांकerrupt = snd_ca0106_pcm_channel_पूर्णांकerrupt;
        channel->epcm = epcm;
	अगर ((err = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय, SNDRV_PCM_HW_PARAM_PERIODS)) < 0)
                वापस err;
	//snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_SIZE, &hw_स्थिरraपूर्णांकs_capture_period_sizes);
	अगर ((err = snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 64)) < 0)
                वापस err;
	वापस 0;
पूर्ण

/* बंद callback */
अटल पूर्णांक snd_ca0106_pcm_बंद_capture(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ca0106 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
        काष्ठा snd_ca0106_pcm *epcm = runसमय->निजी_data;
	chip->capture_channels[epcm->channel_id].use = 0;
	/* FIXME: maybe zero others */
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ca0106_pcm_खोलो_0_capture(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_ca0106_pcm_खोलो_capture_channel(substream, 0);
पूर्ण

अटल पूर्णांक snd_ca0106_pcm_खोलो_1_capture(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_ca0106_pcm_खोलो_capture_channel(substream, 1);
पूर्ण

अटल पूर्णांक snd_ca0106_pcm_खोलो_2_capture(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_ca0106_pcm_खोलो_capture_channel(substream, 2);
पूर्ण

अटल पूर्णांक snd_ca0106_pcm_खोलो_3_capture(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_ca0106_pcm_खोलो_capture_channel(substream, 3);
पूर्ण

/* prepare playback callback */
अटल पूर्णांक snd_ca0106_pcm_prepare_playback(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ca0106 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_ca0106_pcm *epcm = runसमय->निजी_data;
	पूर्णांक channel = epcm->channel_id;
	u32 *table_base = (u32 *)(emu->buffer.area+(8*16*channel));
	u32 period_size_bytes = frames_to_bytes(runसमय, runसमय->period_size);
	u32 hcfg_mask = HCFG_PLAYBACK_S32_LE;
	u32 hcfg_set = 0x00000000;
	u32 hcfg;
	u32 reg40_mask = 0x30000 << (channel<<1);
	u32 reg40_set = 0;
	u32 reg40;
	/* FIXME: Depending on mixer selection of SPDIF out or not, select the spdअगर rate or the DAC rate. */
	u32 reg71_mask = 0x03030000 ; /* Global. Set SPDIF rate. We only support 44100 to spdअगर, not to DAC. */
	u32 reg71_set = 0;
	u32 reg71;
	पूर्णांक i;
	
#अगर 0 /* debug */
	dev_dbg(emu->card->dev,
		   "prepare:channel_number=%d, rate=%d, format=0x%x, "
		   "channels=%d, buffer_size=%ld, period_size=%ld, "
		   "periods=%u, frames_to_bytes=%d\n",
		   channel, runसमय->rate, runसमय->क्रमmat,
		   runसमय->channels, runसमय->buffer_size,
		   runसमय->period_size, runसमय->periods,
		   frames_to_bytes(runसमय, 1));
	dev_dbg(emu->card->dev,
		"dma_addr=%x, dma_area=%p, table_base=%p\n",
		   runसमय->dma_addr, runसमय->dma_area, table_base);
	dev_dbg(emu->card->dev,
		"dma_addr=%x, dma_area=%p, dma_bytes(size)=%x\n",
		   emu->buffer.addr, emu->buffer.area, emu->buffer.bytes);
#पूर्ण_अगर /* debug */
	/* Rate can be set per channel. */
	/* reg40 control host to fअगरo */
	/* reg71 controls DAC rate. */
	चयन (runसमय->rate) अणु
	हाल 44100:
		reg40_set = 0x10000 << (channel<<1);
		reg71_set = 0x01010000; 
		अवरोध;
        हाल 48000:
		reg40_set = 0;
		reg71_set = 0; 
		अवरोध;
	हाल 96000:
		reg40_set = 0x20000 << (channel<<1);
		reg71_set = 0x02020000; 
		अवरोध;
	हाल 192000:
		reg40_set = 0x30000 << (channel<<1);
		reg71_set = 0x03030000; 
		अवरोध;
	शेष:
		reg40_set = 0;
		reg71_set = 0; 
		अवरोध;
	पूर्ण
	/* Format is a global setting */
	/* FIXME: Only let the first channel accessed set this. */
	चयन (runसमय->क्रमmat) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		hcfg_set = 0;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		hcfg_set = HCFG_PLAYBACK_S32_LE;
		अवरोध;
	शेष:
		hcfg_set = 0;
		अवरोध;
	पूर्ण
	hcfg = inl(emu->port + HCFG) ;
	hcfg = (hcfg & ~hcfg_mask) | hcfg_set;
	outl(hcfg, emu->port + HCFG);
	reg40 = snd_ca0106_ptr_पढ़ो(emu, 0x40, 0);
	reg40 = (reg40 & ~reg40_mask) | reg40_set;
	snd_ca0106_ptr_ग_लिखो(emu, 0x40, 0, reg40);
	reg71 = snd_ca0106_ptr_पढ़ो(emu, 0x71, 0);
	reg71 = (reg71 & ~reg71_mask) | reg71_set;
	snd_ca0106_ptr_ग_लिखो(emu, 0x71, 0, reg71);

	/* FIXME: Check emu->buffer.size beक्रमe actually writing to it. */
        क्रम(i=0; i < runसमय->periods; i++) अणु
		table_base[i*2] = runसमय->dma_addr + (i * period_size_bytes);
		table_base[i*2+1] = period_size_bytes << 16;
	पूर्ण
 
	snd_ca0106_ptr_ग_लिखो(emu, PLAYBACK_LIST_ADDR, channel, emu->buffer.addr+(8*16*channel));
	snd_ca0106_ptr_ग_लिखो(emu, PLAYBACK_LIST_SIZE, channel, (runसमय->periods - 1) << 19);
	snd_ca0106_ptr_ग_लिखो(emu, PLAYBACK_LIST_PTR, channel, 0);
	snd_ca0106_ptr_ग_लिखो(emu, PLAYBACK_DMA_ADDR, channel, runसमय->dma_addr);
	snd_ca0106_ptr_ग_लिखो(emu, PLAYBACK_PERIOD_SIZE, channel, frames_to_bytes(runसमय, runसमय->period_size)<<16); // buffer size in bytes
	/* FIXME  test what 0 bytes करोes. */
	snd_ca0106_ptr_ग_लिखो(emu, PLAYBACK_PERIOD_SIZE, channel, 0); // buffer size in bytes
	snd_ca0106_ptr_ग_लिखो(emu, PLAYBACK_POINTER, channel, 0);
	snd_ca0106_ptr_ग_लिखो(emu, 0x07, channel, 0x0);
	snd_ca0106_ptr_ग_लिखो(emu, 0x08, channel, 0);
        snd_ca0106_ptr_ग_लिखो(emu, PLAYBACK_MUTE, 0x0, 0x0); /* Unmute output */
#अगर 0
	snd_ca0106_ptr_ग_लिखो(emu, SPCS0, 0,
			       SPCS_CLKACCY_1000PPM | SPCS_SAMPLERATE_48 |
			       SPCS_CHANNELNUM_LEFT | SPCS_SOURCENUM_UNSPEC |
			       SPCS_GENERATIONSTATUS | 0x00001200 |
			       0x00000000 | SPCS_EMPHASIS_NONE | SPCS_COPYRIGHT );
#पूर्ण_अगर

	वापस 0;
पूर्ण

/* prepare capture callback */
अटल पूर्णांक snd_ca0106_pcm_prepare_capture(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ca0106 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_ca0106_pcm *epcm = runसमय->निजी_data;
	पूर्णांक channel = epcm->channel_id;
	u32 hcfg_mask = HCFG_CAPTURE_S32_LE;
	u32 hcfg_set = 0x00000000;
	u32 hcfg;
	u32 over_sampling=0x2;
	u32 reg71_mask = 0x0000c000 ; /* Global. Set ADC rate. */
	u32 reg71_set = 0;
	u32 reg71;
	
#अगर 0 /* debug */
	dev_dbg(emu->card->dev,
		   "prepare:channel_number=%d, rate=%d, format=0x%x, "
		   "channels=%d, buffer_size=%ld, period_size=%ld, "
		   "periods=%u, frames_to_bytes=%d\n",
		   channel, runसमय->rate, runसमय->क्रमmat,
		   runसमय->channels, runसमय->buffer_size,
		   runसमय->period_size, runसमय->periods,
		   frames_to_bytes(runसमय, 1));
	dev_dbg(emu->card->dev,
		"dma_addr=%x, dma_area=%p, table_base=%p\n",
		   runसमय->dma_addr, runसमय->dma_area, table_base);
	dev_dbg(emu->card->dev,
		"dma_addr=%x, dma_area=%p, dma_bytes(size)=%x\n",
		   emu->buffer.addr, emu->buffer.area, emu->buffer.bytes);
#पूर्ण_अगर /* debug */
	/* reg71 controls ADC rate. */
	चयन (runसमय->rate) अणु
	हाल 44100:
		reg71_set = 0x00004000;
		अवरोध;
        हाल 48000:
		reg71_set = 0; 
		अवरोध;
	हाल 96000:
		reg71_set = 0x00008000;
		over_sampling=0xa;
		अवरोध;
	हाल 192000:
		reg71_set = 0x0000c000; 
		over_sampling=0xa;
		अवरोध;
	शेष:
		reg71_set = 0; 
		अवरोध;
	पूर्ण
	/* Format is a global setting */
	/* FIXME: Only let the first channel accessed set this. */
	चयन (runसमय->क्रमmat) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		hcfg_set = 0;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		hcfg_set = HCFG_CAPTURE_S32_LE;
		अवरोध;
	शेष:
		hcfg_set = 0;
		अवरोध;
	पूर्ण
	hcfg = inl(emu->port + HCFG) ;
	hcfg = (hcfg & ~hcfg_mask) | hcfg_set;
	outl(hcfg, emu->port + HCFG);
	reg71 = snd_ca0106_ptr_पढ़ो(emu, 0x71, 0);
	reg71 = (reg71 & ~reg71_mask) | reg71_set;
	snd_ca0106_ptr_ग_लिखो(emu, 0x71, 0, reg71);
        अगर (emu->details->i2c_adc == 1) अणु /* The SB0410 and SB0413 use I2C to control ADC. */
	        snd_ca0106_i2c_ग_लिखो(emu, ADC_MASTER, over_sampling); /* Adjust the over sampler to better suit the capture rate. */
	पूर्ण


	/*
	dev_dbg(emu->card->dev,
	       "prepare:channel_number=%d, rate=%d, format=0x%x, channels=%d, "
	       "buffer_size=%ld, period_size=%ld, frames_to_bytes=%d\n",
	       channel, runसमय->rate, runसमय->क्रमmat, runसमय->channels,
	       runसमय->buffer_size, runसमय->period_size,
	       frames_to_bytes(runसमय, 1));
	*/
	snd_ca0106_ptr_ग_लिखो(emu, 0x13, channel, 0);
	snd_ca0106_ptr_ग_लिखो(emu, CAPTURE_DMA_ADDR, channel, runसमय->dma_addr);
	snd_ca0106_ptr_ग_लिखो(emu, CAPTURE_BUFFER_SIZE, channel, frames_to_bytes(runसमय, runसमय->buffer_size)<<16); // buffer size in bytes
	snd_ca0106_ptr_ग_लिखो(emu, CAPTURE_POINTER, channel, 0);

	वापस 0;
पूर्ण

/* trigger_playback callback */
अटल पूर्णांक snd_ca0106_pcm_trigger_playback(काष्ठा snd_pcm_substream *substream,
				    पूर्णांक cmd)
अणु
	काष्ठा snd_ca0106 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय;
	काष्ठा snd_ca0106_pcm *epcm;
	पूर्णांक channel;
	पूर्णांक result = 0;
        काष्ठा snd_pcm_substream *s;
	u32 basic = 0;
	u32 extended = 0;
	u32 bits;
	पूर्णांक running = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		running = 1;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	शेष:
		running = 0;
		अवरोध;
	पूर्ण
        snd_pcm_group_क्रम_each_entry(s, substream) अणु
		अगर (snd_pcm_substream_chip(s) != emu ||
		    s->stream != SNDRV_PCM_STREAM_PLAYBACK)
			जारी;
		runसमय = s->runसमय;
		epcm = runसमय->निजी_data;
		channel = epcm->channel_id;
		/* dev_dbg(emu->card->dev, "channel=%d\n", channel); */
		epcm->running = running;
		basic |= (0x1 << channel);
		extended |= (0x10 << channel);
                snd_pcm_trigger_करोne(s, substream);
        पूर्ण
	/* dev_dbg(emu->card->dev, "basic=0x%x, extended=0x%x\n",basic, extended); */

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		bits = snd_ca0106_ptr_पढ़ो(emu, EXTENDED_INT_MASK, 0);
		bits |= extended;
		snd_ca0106_ptr_ग_लिखो(emu, EXTENDED_INT_MASK, 0, bits);
		bits = snd_ca0106_ptr_पढ़ो(emu, BASIC_INTERRUPT, 0);
		bits |= basic;
		snd_ca0106_ptr_ग_लिखो(emu, BASIC_INTERRUPT, 0, bits);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		bits = snd_ca0106_ptr_पढ़ो(emu, BASIC_INTERRUPT, 0);
		bits &= ~basic;
		snd_ca0106_ptr_ग_लिखो(emu, BASIC_INTERRUPT, 0, bits);
		bits = snd_ca0106_ptr_पढ़ो(emu, EXTENDED_INT_MASK, 0);
		bits &= ~extended;
		snd_ca0106_ptr_ग_लिखो(emu, EXTENDED_INT_MASK, 0, bits);
		अवरोध;
	शेष:
		result = -EINVAL;
		अवरोध;
	पूर्ण
	वापस result;
पूर्ण

/* trigger_capture callback */
अटल पूर्णांक snd_ca0106_pcm_trigger_capture(काष्ठा snd_pcm_substream *substream,
				    पूर्णांक cmd)
अणु
	काष्ठा snd_ca0106 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_ca0106_pcm *epcm = runसमय->निजी_data;
	पूर्णांक channel = epcm->channel_id;
	पूर्णांक result = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		snd_ca0106_ptr_ग_लिखो(emu, EXTENDED_INT_MASK, 0, snd_ca0106_ptr_पढ़ो(emu, EXTENDED_INT_MASK, 0) | (0x110000<<channel));
		snd_ca0106_ptr_ग_लिखो(emu, BASIC_INTERRUPT, 0, snd_ca0106_ptr_पढ़ो(emu, BASIC_INTERRUPT, 0)|(0x100<<channel));
		epcm->running = 1;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		snd_ca0106_ptr_ग_लिखो(emu, BASIC_INTERRUPT, 0, snd_ca0106_ptr_पढ़ो(emu, BASIC_INTERRUPT, 0) & ~(0x100<<channel));
		snd_ca0106_ptr_ग_लिखो(emu, EXTENDED_INT_MASK, 0, snd_ca0106_ptr_पढ़ो(emu, EXTENDED_INT_MASK, 0) & ~(0x110000<<channel));
		epcm->running = 0;
		अवरोध;
	शेष:
		result = -EINVAL;
		अवरोध;
	पूर्ण
	वापस result;
पूर्ण

/* poपूर्णांकer_playback callback */
अटल snd_pcm_uframes_t
snd_ca0106_pcm_poपूर्णांकer_playback(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ca0106 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_ca0106_pcm *epcm = runसमय->निजी_data;
	अचिन्हित पूर्णांक ptr, prev_ptr;
	पूर्णांक channel = epcm->channel_id;
	पूर्णांक समयout = 10;

	अगर (!epcm->running)
		वापस 0;

	prev_ptr = -1;
	करो अणु
		ptr = snd_ca0106_ptr_पढ़ो(emu, PLAYBACK_LIST_PTR, channel);
		ptr = (ptr >> 3) * runसमय->period_size;
		ptr += bytes_to_frames(runसमय,
			snd_ca0106_ptr_पढ़ो(emu, PLAYBACK_POINTER, channel));
		अगर (ptr >= runसमय->buffer_size)
			ptr -= runसमय->buffer_size;
		अगर (prev_ptr == ptr)
			वापस ptr;
		prev_ptr = ptr;
	पूर्ण जबतक (--समयout);
	dev_warn(emu->card->dev, "ca0106: unstable DMA pointer!\n");
	वापस 0;
पूर्ण

/* poपूर्णांकer_capture callback */
अटल snd_pcm_uframes_t
snd_ca0106_pcm_poपूर्णांकer_capture(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ca0106 *emu = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_ca0106_pcm *epcm = runसमय->निजी_data;
	snd_pcm_uframes_t ptr, ptr1, ptr2 = 0;
	पूर्णांक channel = epcm->channel_id;

	अगर (!epcm->running)
		वापस 0;

	ptr1 = snd_ca0106_ptr_पढ़ो(emu, CAPTURE_POINTER, channel);
	ptr2 = bytes_to_frames(runसमय, ptr1);
	ptr=ptr2;
        अगर (ptr >= runसमय->buffer_size)
		ptr -= runसमय->buffer_size;
	/*
	dev_dbg(emu->card->dev, "ptr1 = 0x%lx, ptr2=0x%lx, ptr=0x%lx, "
	       "buffer_size = 0x%x, period_size = 0x%x, bits=%d, rate=%d\n",
	       ptr1, ptr2, ptr, (पूर्णांक)runसमय->buffer_size,
	       (पूर्णांक)runसमय->period_size, (पूर्णांक)runसमय->frame_bits,
	       (पूर्णांक)runसमय->rate);
	*/
	वापस ptr;
पूर्ण

/* चालकs */
अटल स्थिर काष्ठा snd_pcm_ops snd_ca0106_playback_front_ops = अणु
	.खोलो =        snd_ca0106_pcm_खोलो_playback_front,
	.बंद =       snd_ca0106_pcm_बंद_playback,
	.prepare =     snd_ca0106_pcm_prepare_playback,
	.trigger =     snd_ca0106_pcm_trigger_playback,
	.poपूर्णांकer =     snd_ca0106_pcm_poपूर्णांकer_playback,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_ca0106_capture_0_ops = अणु
	.खोलो =        snd_ca0106_pcm_खोलो_0_capture,
	.बंद =       snd_ca0106_pcm_बंद_capture,
	.prepare =     snd_ca0106_pcm_prepare_capture,
	.trigger =     snd_ca0106_pcm_trigger_capture,
	.poपूर्णांकer =     snd_ca0106_pcm_poपूर्णांकer_capture,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_ca0106_capture_1_ops = अणु
	.खोलो =        snd_ca0106_pcm_खोलो_1_capture,
	.बंद =       snd_ca0106_pcm_बंद_capture,
	.prepare =     snd_ca0106_pcm_prepare_capture,
	.trigger =     snd_ca0106_pcm_trigger_capture,
	.poपूर्णांकer =     snd_ca0106_pcm_poपूर्णांकer_capture,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_ca0106_capture_2_ops = अणु
	.खोलो =        snd_ca0106_pcm_खोलो_2_capture,
	.बंद =       snd_ca0106_pcm_बंद_capture,
	.prepare =     snd_ca0106_pcm_prepare_capture,
	.trigger =     snd_ca0106_pcm_trigger_capture,
	.poपूर्णांकer =     snd_ca0106_pcm_poपूर्णांकer_capture,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_ca0106_capture_3_ops = अणु
	.खोलो =        snd_ca0106_pcm_खोलो_3_capture,
	.बंद =       snd_ca0106_pcm_बंद_capture,
	.prepare =     snd_ca0106_pcm_prepare_capture,
	.trigger =     snd_ca0106_pcm_trigger_capture,
	.poपूर्णांकer =     snd_ca0106_pcm_poपूर्णांकer_capture,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_ca0106_playback_center_lfe_ops = अणु
        .खोलो =         snd_ca0106_pcm_खोलो_playback_center_lfe,
        .बंद =        snd_ca0106_pcm_बंद_playback,
        .prepare =      snd_ca0106_pcm_prepare_playback,     
        .trigger =      snd_ca0106_pcm_trigger_playback,  
        .poपूर्णांकer =      snd_ca0106_pcm_poपूर्णांकer_playback, 
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_ca0106_playback_unknown_ops = अणु
        .खोलो =         snd_ca0106_pcm_खोलो_playback_unknown,
        .बंद =        snd_ca0106_pcm_बंद_playback,
        .prepare =      snd_ca0106_pcm_prepare_playback,     
        .trigger =      snd_ca0106_pcm_trigger_playback,  
        .poपूर्णांकer =      snd_ca0106_pcm_poपूर्णांकer_playback, 
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_ca0106_playback_rear_ops = अणु
        .खोलो =         snd_ca0106_pcm_खोलो_playback_rear,
        .बंद =        snd_ca0106_pcm_बंद_playback,
        .prepare =      snd_ca0106_pcm_prepare_playback,     
        .trigger =      snd_ca0106_pcm_trigger_playback,  
        .poपूर्णांकer =      snd_ca0106_pcm_poपूर्णांकer_playback, 
पूर्ण;


अटल अचिन्हित लघु snd_ca0106_ac97_पढ़ो(काष्ठा snd_ac97 *ac97,
					     अचिन्हित लघु reg)
अणु
	काष्ठा snd_ca0106 *emu = ac97->निजी_data;
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु val;

	spin_lock_irqsave(&emu->emu_lock, flags);
	outb(reg, emu->port + AC97ADDRESS);
	val = inw(emu->port + AC97DATA);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
	वापस val;
पूर्ण

अटल व्योम snd_ca0106_ac97_ग_लिखो(काष्ठा snd_ac97 *ac97,
				    अचिन्हित लघु reg, अचिन्हित लघु val)
अणु
	काष्ठा snd_ca0106 *emu = ac97->निजी_data;
	अचिन्हित दीर्घ flags;
  
	spin_lock_irqsave(&emu->emu_lock, flags);
	outb(reg, emu->port + AC97ADDRESS);
	outw(val, emu->port + AC97DATA);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
पूर्ण

अटल पूर्णांक snd_ca0106_ac97(काष्ठा snd_ca0106 *chip)
अणु
	काष्ठा snd_ac97_bus *pbus;
	काष्ठा snd_ac97_ढाँचा ac97;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_ac97_bus_ops ops = अणु
		.ग_लिखो = snd_ca0106_ac97_ग_लिखो,
		.पढ़ो = snd_ca0106_ac97_पढ़ो,
	पूर्ण;
  
	अगर ((err = snd_ac97_bus(chip->card, 0, &ops, शून्य, &pbus)) < 0)
		वापस err;
	pbus->no_vra = 1; /* we करोn't need VRA */

	स_रखो(&ac97, 0, माप(ac97));
	ac97.निजी_data = chip;
	ac97.scaps = AC97_SCAP_NO_SPDIF;
	वापस snd_ac97_mixer(pbus, &ac97, &chip->ac97);
पूर्ण

अटल व्योम ca0106_stop_chip(काष्ठा snd_ca0106 *chip);

अटल पूर्णांक snd_ca0106_मुक्त(काष्ठा snd_ca0106 *chip)
अणु
	अगर (chip->res_port != शून्य) अणु
		/* aव्योम access to alपढ़ोy used hardware */
		ca0106_stop_chip(chip);
	पूर्ण
	अगर (chip->irq >= 0)
		मुक्त_irq(chip->irq, chip);
	// release the data
#अगर 1
	अगर (chip->buffer.area)
		snd_dma_मुक्त_pages(&chip->buffer);
#पूर्ण_अगर

	// release the i/o port
	release_and_मुक्त_resource(chip->res_port);

	pci_disable_device(chip->pci);
	kमुक्त(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ca0106_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_ca0106 *chip = device->device_data;
	वापस snd_ca0106_मुक्त(chip);
पूर्ण

अटल irqवापस_t snd_ca0106_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित पूर्णांक status;

	काष्ठा snd_ca0106 *chip = dev_id;
	पूर्णांक i;
	पूर्णांक mask;
        अचिन्हित पूर्णांक stat76;
	काष्ठा snd_ca0106_channel *pchannel;

	status = inl(chip->port + IPR);
	अगर (! status)
		वापस IRQ_NONE;

        stat76 = snd_ca0106_ptr_पढ़ो(chip, EXTENDED_INT, 0);
	/*
	dev_dbg(emu->card->dev, "interrupt status = 0x%08x, stat76=0x%08x\n",
		   status, stat76);
	dev_dbg(emu->card->dev, "ptr=0x%08x\n",
		   snd_ca0106_ptr_पढ़ो(chip, PLAYBACK_POINTER, 0));
	*/
        mask = 0x11; /* 0x1 क्रम one half, 0x10 क्रम the other half period. */
	क्रम(i = 0; i < 4; i++) अणु
		pchannel = &(chip->playback_channels[i]);
		अगर (stat76 & mask) अणु
/* FIXME: Select the correct substream क्रम period elapsed */
			अगर(pchannel->use) अणु
				snd_pcm_period_elapsed(pchannel->epcm->substream);
				/* dev_dbg(emu->card->dev, "interrupt [%d] used\n", i); */
                        पूर्ण
		पूर्ण
		/*
		dev_dbg(emu->card->dev, "channel=%p\n", pchannel);
		dev_dbg(emu->card->dev, "interrupt stat76[%d] = %08x, use=%d, channel=%d\n", i, stat76, pchannel->use, pchannel->number);
		*/
		mask <<= 1;
	पूर्ण
        mask = 0x110000; /* 0x1 क्रम one half, 0x10 क्रम the other half period. */
	क्रम(i = 0; i < 4; i++) अणु
		pchannel = &(chip->capture_channels[i]);
		अगर (stat76 & mask) अणु
/* FIXME: Select the correct substream क्रम period elapsed */
			अगर(pchannel->use) अणु
				snd_pcm_period_elapsed(pchannel->epcm->substream);
				/* dev_dbg(emu->card->dev, "interrupt [%d] used\n", i); */
                        पूर्ण
		पूर्ण
		/*
		dev_dbg(emu->card->dev, "channel=%p\n", pchannel);
		dev_dbg(emu->card->dev, "interrupt stat76[%d] = %08x, use=%d, channel=%d\n", i, stat76, pchannel->use, pchannel->number);
		*/
		mask <<= 1;
	पूर्ण

        snd_ca0106_ptr_ग_लिखो(chip, EXTENDED_INT, 0, stat76);

	अगर (chip->midi.dev_id &&
	    (status & (chip->midi.ipr_tx|chip->midi.ipr_rx))) अणु
		अगर (chip->midi.पूर्णांकerrupt)
			chip->midi.पूर्णांकerrupt(&chip->midi, status);
		अन्यथा
			chip->midi.पूर्णांकerrupt_disable(&chip->midi, chip->midi.tx_enable | chip->midi.rx_enable);
	पूर्ण

	// acknowledge the पूर्णांकerrupt अगर necessary
	outl(status, chip->port+IPR);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_chmap_elem surround_map[] = अणु
	अणु .channels = 2,
	  .map = अणु SNDRV_CHMAP_RL, SNDRV_CHMAP_RR पूर्ण पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_chmap_elem clfe_map[] = अणु
	अणु .channels = 2,
	  .map = अणु SNDRV_CHMAP_FC, SNDRV_CHMAP_LFE पूर्ण पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_chmap_elem side_map[] = अणु
	अणु .channels = 2,
	  .map = अणु SNDRV_CHMAP_SL, SNDRV_CHMAP_SR पूर्ण पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक snd_ca0106_pcm(काष्ठा snd_ca0106 *emu, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_pcm_substream *substream;
	स्थिर काष्ठा snd_pcm_chmap_elem *map = शून्य;
	पूर्णांक err;
  
	err = snd_pcm_new(emu->card, "ca0106", device, 1, 1, &pcm);
	अगर (err < 0)
		वापस err;
  
	pcm->निजी_data = emu;

	चयन (device) अणु
	हाल 0:
	  snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_ca0106_playback_front_ops);
	  snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_ca0106_capture_0_ops);
	  map = snd_pcm_std_chmaps;
          अवरोध;
	हाल 1:
	  snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_ca0106_playback_rear_ops);
	  snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_ca0106_capture_1_ops);
	  map = surround_map;
          अवरोध;
	हाल 2:
	  snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_ca0106_playback_center_lfe_ops);
	  snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_ca0106_capture_2_ops);
	  map = clfe_map;
          अवरोध;
	हाल 3:
	  snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_ca0106_playback_unknown_ops);
	  snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_ca0106_capture_3_ops);
	  map = side_map;
          अवरोध;
        पूर्ण

	pcm->info_flags = 0;
	म_नकल(pcm->name, "CA0106");

	क्रम(substream = pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream; 
	    substream; 
	    substream = substream->next) अणु
		snd_pcm_set_managed_buffer(substream, SNDRV_DMA_TYPE_DEV,
					   &emu->pci->dev,
					   64*1024, 64*1024);
	पूर्ण

	क्रम (substream = pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream; 
	      substream; 
	      substream = substream->next) अणु
		snd_pcm_set_managed_buffer(substream, SNDRV_DMA_TYPE_DEV,
					   &emu->pci->dev,
					   64*1024, 64*1024);
	पूर्ण
  
	err = snd_pcm_add_chmap_ctls(pcm, SNDRV_PCM_STREAM_PLAYBACK, map, 2,
				     1 << 2, शून्य);
	अगर (err < 0)
		वापस err;

	emu->pcm[device] = pcm;
  
	वापस 0;
पूर्ण

#घोषणा SPI_REG(reg, value)	(((reg) << SPI_REG_SHIFT) | (value))
अटल स्थिर अचिन्हित पूर्णांक spi_dac_init[] = अणु
	SPI_REG(SPI_LDA1_REG,	SPI_DA_BIT_0dB), /* 0dB dig. attenuation */
	SPI_REG(SPI_RDA1_REG,	SPI_DA_BIT_0dB),
	SPI_REG(SPI_PL_REG,	SPI_PL_BIT_L_L | SPI_PL_BIT_R_R | SPI_IZD_BIT),
	SPI_REG(SPI_FMT_REG,	SPI_FMT_BIT_I2S | SPI_IWL_BIT_24),
	SPI_REG(SPI_LDA2_REG,	SPI_DA_BIT_0dB),
	SPI_REG(SPI_RDA2_REG,	SPI_DA_BIT_0dB),
	SPI_REG(SPI_LDA3_REG,	SPI_DA_BIT_0dB),
	SPI_REG(SPI_RDA3_REG,	SPI_DA_BIT_0dB),
	SPI_REG(SPI_MASTDA_REG,	SPI_DA_BIT_0dB),
	SPI_REG(9,		0x00),
	SPI_REG(SPI_MS_REG,	SPI_DACD0_BIT | SPI_DACD1_BIT | SPI_DACD2_BIT),
	SPI_REG(12,		0x00),
	SPI_REG(SPI_LDA4_REG,	SPI_DA_BIT_0dB),
	SPI_REG(SPI_RDA4_REG,	SPI_DA_BIT_0dB | SPI_DA_BIT_UPDATE),
	SPI_REG(SPI_DACD4_REG,	SPI_DACD4_BIT),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक i2c_adc_init[][2] = अणु
	अणु 0x17, 0x00 पूर्ण, /* Reset */
	अणु 0x07, 0x00 पूर्ण, /* Timeout */
	अणु 0x0b, 0x22 पूर्ण,  /* Interface control */
	अणु 0x0c, 0x22 पूर्ण,  /* Master mode control */
	अणु 0x0d, 0x08 पूर्ण,  /* Powerकरोwn control */
	अणु 0x0e, 0xcf पूर्ण,  /* Attenuation Left  0x01 = -103dB, 0xff = 24dB */
	अणु 0x0f, 0xcf पूर्ण,  /* Attenuation Right 0.5dB steps */
	अणु 0x10, 0x7b पूर्ण,  /* ALC Control 1 */
	अणु 0x11, 0x00 पूर्ण,  /* ALC Control 2 */
	अणु 0x12, 0x32 पूर्ण,  /* ALC Control 3 */
	अणु 0x13, 0x00 पूर्ण,  /* Noise gate control */
	अणु 0x14, 0xa6 पूर्ण,  /* Limiter control */
	अणु 0x15, ADC_MUX_LINEIN पूर्ण,  /* ADC Mixer control */
पूर्ण;

अटल व्योम ca0106_init_chip(काष्ठा snd_ca0106 *chip, पूर्णांक resume)
अणु
	पूर्णांक ch;
	अचिन्हित पूर्णांक def_bits;

	outl(0, chip->port + INTE);

	/*
	 *  Init to 0x02109204 :
	 *  Clock accuracy    = 0     (1000ppm)
	 *  Sample Rate       = 2     (48kHz)
	 *  Audio Channel     = 1     (Left of 2)
	 *  Source Number     = 0     (Unspecअगरied)
	 *  Generation Status = 1     (Original क्रम Cat Code 12)
	 *  Cat Code          = 12    (Digital Signal Mixer)
	 *  Mode              = 0     (Mode 0)
	 *  Emphasis          = 0     (None)
	 *  CP                = 1     (Copyright unनिश्चितed)
	 *  AN                = 0     (Audio data)
	 *  P                 = 0     (Consumer)
	 */
	def_bits =
		SPCS_CLKACCY_1000PPM | SPCS_SAMPLERATE_48 |
		SPCS_CHANNELNUM_LEFT | SPCS_SOURCENUM_UNSPEC |
		SPCS_GENERATIONSTATUS | 0x00001200 |
		0x00000000 | SPCS_EMPHASIS_NONE | SPCS_COPYRIGHT;
	अगर (!resume) अणु
		chip->spdअगर_str_bits[0] = chip->spdअगर_bits[0] = def_bits;
		chip->spdअगर_str_bits[1] = chip->spdअगर_bits[1] = def_bits;
		chip->spdअगर_str_bits[2] = chip->spdअगर_bits[2] = def_bits;
		chip->spdअगर_str_bits[3] = chip->spdअगर_bits[3] = def_bits;
	पूर्ण
	/* Only SPCS1 has been tested */
	snd_ca0106_ptr_ग_लिखो(chip, SPCS1, 0, chip->spdअगर_str_bits[1]);
	snd_ca0106_ptr_ग_लिखो(chip, SPCS0, 0, chip->spdअगर_str_bits[0]);
	snd_ca0106_ptr_ग_लिखो(chip, SPCS2, 0, chip->spdअगर_str_bits[2]);
	snd_ca0106_ptr_ग_लिखो(chip, SPCS3, 0, chip->spdअगर_str_bits[3]);

        snd_ca0106_ptr_ग_लिखो(chip, PLAYBACK_MUTE, 0, 0x00fc0000);
        snd_ca0106_ptr_ग_लिखो(chip, CAPTURE_MUTE, 0, 0x00fc0000);

        /* Write 0x8000 to AC97_REC_GAIN to mute it. */
        outb(AC97_REC_GAIN, chip->port + AC97ADDRESS);
        outw(0x8000, chip->port + AC97DATA);
#अगर 0 /* FIXME: what are these? */
	snd_ca0106_ptr_ग_लिखो(chip, SPCS0, 0, 0x2108006);
	snd_ca0106_ptr_ग_लिखो(chip, 0x42, 0, 0x2108006);
	snd_ca0106_ptr_ग_लिखो(chip, 0x43, 0, 0x2108006);
	snd_ca0106_ptr_ग_लिखो(chip, 0x44, 0, 0x2108006);
#पूर्ण_अगर

	/* OSS drivers set this. */
	/* snd_ca0106_ptr_ग_लिखो(chip, SPDIF_SELECT2, 0, 0xf0f003f); */

	/* Analog or Digital output */
	snd_ca0106_ptr_ग_लिखो(chip, SPDIF_SELECT1, 0, 0xf);
	/* 0x0b000000 क्रम digital, 0x000b0000 क्रम analog, from win2000 drivers.
	 * Use 0x000f0000 क्रम surround71
	 */
	snd_ca0106_ptr_ग_लिखो(chip, SPDIF_SELECT2, 0, 0x000f0000);

	chip->spdअगर_enable = 0; /* Set digital SPDIF output off */
	/*snd_ca0106_ptr_ग_लिखो(chip, 0x45, 0, 0);*/ /* Analogue out */
	/*snd_ca0106_ptr_ग_लिखो(chip, 0x45, 0, 0xf00);*/ /* Digital out */

	/* goes to 0x40c80000 when करोing SPDIF IN/OUT */
	snd_ca0106_ptr_ग_लिखो(chip, CAPTURE_CONTROL, 0, 0x40c81000);
	/* (Mute) CAPTURE feedback पूर्णांकo PLAYBACK volume.
	 * Only lower 16 bits matter.
	 */
	snd_ca0106_ptr_ग_लिखो(chip, CAPTURE_CONTROL, 1, 0xffffffff);
	/* SPDIF IN Volume */
	snd_ca0106_ptr_ग_लिखो(chip, CAPTURE_CONTROL, 2, 0x30300000);
	/* SPDIF IN Volume, 0x70 = (vol & 0x3f) | 0x40 */
	snd_ca0106_ptr_ग_लिखो(chip, CAPTURE_CONTROL, 3, 0x00700000);

	snd_ca0106_ptr_ग_लिखो(chip, PLAYBACK_ROUTING1, 0, 0x32765410);
	snd_ca0106_ptr_ग_लिखो(chip, PLAYBACK_ROUTING2, 0, 0x76767676);
	snd_ca0106_ptr_ग_लिखो(chip, CAPTURE_ROUTING1, 0, 0x32765410);
	snd_ca0106_ptr_ग_लिखो(chip, CAPTURE_ROUTING2, 0, 0x76767676);

	क्रम (ch = 0; ch < 4; ch++) अणु
		/* Only high 16 bits matter */
		snd_ca0106_ptr_ग_लिखो(chip, CAPTURE_VOLUME1, ch, 0x30303030);
		snd_ca0106_ptr_ग_लिखो(chip, CAPTURE_VOLUME2, ch, 0x30303030);
#अगर 0 /* Mute */
		snd_ca0106_ptr_ग_लिखो(chip, PLAYBACK_VOLUME1, ch, 0x40404040);
		snd_ca0106_ptr_ग_लिखो(chip, PLAYBACK_VOLUME2, ch, 0x40404040);
		snd_ca0106_ptr_ग_लिखो(chip, PLAYBACK_VOLUME1, ch, 0xffffffff);
		snd_ca0106_ptr_ग_लिखो(chip, PLAYBACK_VOLUME2, ch, 0xffffffff);
#पूर्ण_अगर
	पूर्ण
	अगर (chip->details->i2c_adc == 1) अणु
	        /* Select MIC, Line in, TAD in, AUX in */
	        snd_ca0106_ptr_ग_लिखो(chip, CAPTURE_SOURCE, 0x0, 0x333300e4);
		/* Default to CAPTURE_SOURCE to i2s in */
		अगर (!resume)
			chip->capture_source = 3;
	पूर्ण अन्यथा अगर (chip->details->ac97 == 1) अणु
	        /* Default to AC97 in */
	        snd_ca0106_ptr_ग_लिखो(chip, CAPTURE_SOURCE, 0x0, 0x444400e4);
		/* Default to CAPTURE_SOURCE to AC97 in */
		अगर (!resume)
			chip->capture_source = 4;
	पूर्ण अन्यथा अणु
	        /* Select MIC, Line in, TAD in, AUX in */
	        snd_ca0106_ptr_ग_लिखो(chip, CAPTURE_SOURCE, 0x0, 0x333300e4);
		/* Default to Set CAPTURE_SOURCE to i2s in */
		अगर (!resume)
			chip->capture_source = 3;
	पूर्ण

	अगर (chip->details->gpio_type == 2) अणु
		/* The SB0438 use GPIO dअगरferently. */
		/* FIXME: Still need to find out what the other GPIO bits करो.
		 * E.g. For digital spdअगर out.
		 */
		outl(0x0, chip->port+GPIO);
		/* outl(0x00f0e000, chip->port+GPIO); */ /* Analog */
		outl(0x005f5301, chip->port+GPIO); /* Analog */
	पूर्ण अन्यथा अगर (chip->details->gpio_type == 1) अणु
		/* The SB0410 and SB0413 use GPIO dअगरferently. */
		/* FIXME: Still need to find out what the other GPIO bits करो.
		 * E.g. For digital spdअगर out.
		 */
		outl(0x0, chip->port+GPIO);
		/* outl(0x00f0e000, chip->port+GPIO); */ /* Analog */
		outl(0x005f5301, chip->port+GPIO); /* Analog */
	पूर्ण अन्यथा अणु
		outl(0x0, chip->port+GPIO);
		outl(0x005f03a3, chip->port+GPIO); /* Analog */
		/* outl(0x005f02a2, chip->port+GPIO); */ /* SPDIF */
	पूर्ण
	snd_ca0106_पूर्णांकr_enable(chip, 0x105); /* Win2000 uses 0x1e0 */

	/* outl(HCFG_LOCKSOUNDCACHE|HCFG_AUDIOENABLE, chip->port+HCFG); */
	/* 0x1000 causes AC3 to fails. Maybe it effects 24 bit output. */
	/* outl(0x00001409, chip->port+HCFG); */
	/* outl(0x00000009, chip->port+HCFG); */
	/* AC97 2.0, Enable outमाला_दो. */
	outl(HCFG_AC97 | HCFG_AUDIOENABLE, chip->port+HCFG);

	अगर (chip->details->i2c_adc == 1) अणु
		/* The SB0410 and SB0413 use I2C to control ADC. */
		पूर्णांक size, n;

		size = ARRAY_SIZE(i2c_adc_init);
		/* dev_dbg(emu->card->dev, "I2C:array size=0x%x\n", size); */
		क्रम (n = 0; n < size; n++)
			snd_ca0106_i2c_ग_लिखो(chip, i2c_adc_init[n][0],
					     i2c_adc_init[n][1]);
		क्रम (n = 0; n < 4; n++) अणु
			chip->i2c_capture_volume[n][0] = 0xcf;
			chip->i2c_capture_volume[n][1] = 0xcf;
		पूर्ण
		chip->i2c_capture_source = 2; /* Line in */
		/* Enable Line-in capture. MIC in currently untested. */
		/* snd_ca0106_i2c_ग_लिखो(chip, ADC_MUX, ADC_MUX_LINEIN); */
	पूर्ण

	अगर (chip->details->spi_dac) अणु
		/* The SB0570 use SPI to control DAC. */
		पूर्णांक size, n;

		size = ARRAY_SIZE(spi_dac_init);
		क्रम (n = 0; n < size; n++) अणु
			पूर्णांक reg = spi_dac_init[n] >> SPI_REG_SHIFT;

			snd_ca0106_spi_ग_लिखो(chip, spi_dac_init[n]);
			अगर (reg < ARRAY_SIZE(chip->spi_dac_reg))
				chip->spi_dac_reg[reg] = spi_dac_init[n];
		पूर्ण

		/* Enable front dac only */
		snd_ca0106_pcm_घातer_dac(chip, PCM_FRONT_CHANNEL, 1);
	पूर्ण
पूर्ण

अटल व्योम ca0106_stop_chip(काष्ठा snd_ca0106 *chip)
अणु
	/* disable पूर्णांकerrupts */
	snd_ca0106_ptr_ग_लिखो(chip, BASIC_INTERRUPT, 0, 0);
	outl(0, chip->port + INTE);
	snd_ca0106_ptr_ग_लिखो(chip, EXTENDED_INT_MASK, 0, 0);
	udelay(1000);
	/* disable audio */
	/* outl(HCFG_LOCKSOUNDCACHE, chip->port + HCFG); */
	outl(0, chip->port + HCFG);
	/* FIXME: We need to stop and DMA transfers here.
	 *        But as I am not sure how yet, we cannot from the dma pages.
	 * So we can fix: snd-दो_स्मृति: Memory leak?  pages not मुक्तd = 8
	 */
पूर्ण

अटल पूर्णांक snd_ca0106_create(पूर्णांक dev, काष्ठा snd_card *card,
					 काष्ठा pci_dev *pci,
					 काष्ठा snd_ca0106 **rchip)
अणु
	काष्ठा snd_ca0106 *chip;
	स्थिर काष्ठा snd_ca0106_details *c;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त = snd_ca0106_dev_मुक्त,
	पूर्ण;

	*rchip = शून्य;

	err = pci_enable_device(pci);
	अगर (err < 0)
		वापस err;
	अगर (dma_set_mask_and_coherent(&pci->dev, DMA_BIT_MASK(32))) अणु
		dev_err(card->dev, "error to set 32bit mask DMA\n");
		pci_disable_device(pci);
		वापस -ENXIO;
	पूर्ण

	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण

	chip->card = card;
	chip->pci = pci;
	chip->irq = -1;

	spin_lock_init(&chip->emu_lock);

	chip->port = pci_resource_start(pci, 0);
	chip->res_port = request_region(chip->port, 0x20, "snd_ca0106");
	अगर (!chip->res_port) अणु
		snd_ca0106_मुक्त(chip);
		dev_err(card->dev, "cannot allocate the port\n");
		वापस -EBUSY;
	पूर्ण

	अगर (request_irq(pci->irq, snd_ca0106_पूर्णांकerrupt,
			IRQF_SHARED, KBUILD_MODNAME, chip)) अणु
		snd_ca0106_मुक्त(chip);
		dev_err(card->dev, "cannot grab irq\n");
		वापस -EBUSY;
	पूर्ण
	chip->irq = pci->irq;
	card->sync_irq = chip->irq;

	/* This stores the periods table. */
	अगर (snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, &pci->dev,
				1024, &chip->buffer) < 0) अणु
		snd_ca0106_मुक्त(chip);
		वापस -ENOMEM;
	पूर्ण

	pci_set_master(pci);
	/* पढ़ो serial */
	pci_पढ़ो_config_dword(pci, PCI_SUBSYSTEM_VENDOR_ID, &chip->serial);
	pci_पढ़ो_config_word(pci, PCI_SUBSYSTEM_ID, &chip->model);
	dev_info(card->dev, "Model %04x Rev %08x Serial %08x\n",
	       chip->model, pci->revision, chip->serial);
	म_नकल(card->driver, "CA0106");
	म_नकल(card->लघुname, "CA0106");

	क्रम (c = ca0106_chip_details; c->serial; c++) अणु
		अगर (subप्रणाली[dev]) अणु
			अगर (c->serial == subप्रणाली[dev])
				अवरोध;
		पूर्ण अन्यथा अगर (c->serial == chip->serial)
			अवरोध;
	पूर्ण
	chip->details = c;
	अगर (subप्रणाली[dev]) अणु
		dev_info(card->dev, "Sound card name=%s, "
		       "subsystem=0x%x. Forced to subsystem=0x%x\n",
		       c->name, chip->serial, subप्रणाली[dev]);
	पूर्ण

	प्र_लिखो(card->दीर्घname, "%s at 0x%lx irq %i",
		c->name, chip->port, chip->irq);

	ca0106_init_chip(chip, 0);

	err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops);
	अगर (err < 0) अणु
		snd_ca0106_मुक्त(chip);
		वापस err;
	पूर्ण
	*rchip = chip;
	वापस 0;
पूर्ण


अटल व्योम ca0106_midi_पूर्णांकerrupt_enable(काष्ठा snd_ca_midi *midi, पूर्णांक पूर्णांकr)
अणु
	snd_ca0106_पूर्णांकr_enable((काष्ठा snd_ca0106 *)(midi->dev_id), पूर्णांकr);
पूर्ण

अटल व्योम ca0106_midi_पूर्णांकerrupt_disable(काष्ठा snd_ca_midi *midi, पूर्णांक पूर्णांकr)
अणु
	snd_ca0106_पूर्णांकr_disable((काष्ठा snd_ca0106 *)(midi->dev_id), पूर्णांकr);
पूर्ण

अटल अचिन्हित अक्षर ca0106_midi_पढ़ो(काष्ठा snd_ca_midi *midi, पूर्णांक idx)
अणु
	वापस (अचिन्हित अक्षर)snd_ca0106_ptr_पढ़ो((काष्ठा snd_ca0106 *)(midi->dev_id),
						  midi->port + idx, 0);
पूर्ण

अटल व्योम ca0106_midi_ग_लिखो(काष्ठा snd_ca_midi *midi, पूर्णांक data, पूर्णांक idx)
अणु
	snd_ca0106_ptr_ग_लिखो((काष्ठा snd_ca0106 *)(midi->dev_id), midi->port + idx, 0, data);
पूर्ण

अटल काष्ठा snd_card *ca0106_dev_id_card(व्योम *dev_id)
अणु
	वापस ((काष्ठा snd_ca0106 *)dev_id)->card;
पूर्ण

अटल पूर्णांक ca0106_dev_id_port(व्योम *dev_id)
अणु
	वापस ((काष्ठा snd_ca0106 *)dev_id)->port;
पूर्ण

अटल पूर्णांक snd_ca0106_midi(काष्ठा snd_ca0106 *chip, अचिन्हित पूर्णांक channel)
अणु
	काष्ठा snd_ca_midi *midi;
	अक्षर *name;
	पूर्णांक err;

	अगर (channel == CA0106_MIDI_CHAN_B) अणु
		name = "CA0106 MPU-401 (UART) B";
		midi =  &chip->midi2;
		midi->tx_enable = INTE_MIDI_TX_B;
		midi->rx_enable = INTE_MIDI_RX_B;
		midi->ipr_tx = IPR_MIDI_TX_B;
		midi->ipr_rx = IPR_MIDI_RX_B;
		midi->port = MIDI_UART_B_DATA;
	पूर्ण अन्यथा अणु
		name = "CA0106 MPU-401 (UART)";
		midi =  &chip->midi;
		midi->tx_enable = INTE_MIDI_TX_A;
		midi->rx_enable = INTE_MIDI_TX_B;
		midi->ipr_tx = IPR_MIDI_TX_A;
		midi->ipr_rx = IPR_MIDI_RX_A;
		midi->port = MIDI_UART_A_DATA;
	पूर्ण

	midi->reset = CA0106_MPU401_RESET;
	midi->enter_uart = CA0106_MPU401_ENTER_UART;
	midi->ack = CA0106_MPU401_ACK;

	midi->input_avail = CA0106_MIDI_INPUT_AVAIL;
	midi->output_पढ़ोy = CA0106_MIDI_OUTPUT_READY;

	midi->channel = channel;

	midi->पूर्णांकerrupt_enable = ca0106_midi_पूर्णांकerrupt_enable;
	midi->पूर्णांकerrupt_disable = ca0106_midi_पूर्णांकerrupt_disable;

	midi->पढ़ो = ca0106_midi_पढ़ो;
	midi->ग_लिखो = ca0106_midi_ग_लिखो;

	midi->get_dev_id_card = ca0106_dev_id_card;
	midi->get_dev_id_port = ca0106_dev_id_port;

	midi->dev_id = chip;
	
	अगर ((err = ca_midi_init(chip, midi, 0, name)) < 0)
		वापस err;

	वापस 0;
पूर्ण


अटल पूर्णांक snd_ca0106_probe(काष्ठा pci_dev *pci,
					स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	काष्ठा snd_ca0106 *chip;
	पूर्णांक i, err;

	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;
	अगर (!enable[dev]) अणु
		dev++;
		वापस -ENOENT;
	पूर्ण

	err = snd_card_new(&pci->dev, index[dev], id[dev], THIS_MODULE,
			   0, &card);
	अगर (err < 0)
		वापस err;

	err = snd_ca0106_create(dev, card, pci, &chip);
	अगर (err < 0)
		जाओ error;
	card->निजी_data = chip;

	क्रम (i = 0; i < 4; i++) अणु
		err = snd_ca0106_pcm(chip, i);
		अगर (err < 0)
			जाओ error;
	पूर्ण

	अगर (chip->details->ac97 == 1) अणु
		/* The SB0410 and SB0413 करो not have an AC97 chip. */
		err = snd_ca0106_ac97(chip);
		अगर (err < 0)
			जाओ error;
	पूर्ण
	err = snd_ca0106_mixer(chip);
	अगर (err < 0)
		जाओ error;

	dev_dbg(card->dev, "probe for MIDI channel A ...");
	err = snd_ca0106_midi(chip, CA0106_MIDI_CHAN_A);
	अगर (err < 0)
		जाओ error;
	dev_dbg(card->dev, " done.\n");

#अगर_घोषित CONFIG_SND_PROC_FS
	snd_ca0106_proc_init(chip);
#पूर्ण_अगर

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ error;

	pci_set_drvdata(pci, card);
	dev++;
	वापस 0;

 error:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल व्योम snd_ca0106_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक snd_ca0106_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा snd_ca0106 *chip = card->निजी_data;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	अगर (chip->details->ac97)
		snd_ac97_suspend(chip->ac97);
	snd_ca0106_mixer_suspend(chip);

	ca0106_stop_chip(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ca0106_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा snd_ca0106 *chip = card->निजी_data;
	पूर्णांक i;

	ca0106_init_chip(chip, 1);

	अगर (chip->details->ac97)
		snd_ac97_resume(chip->ac97);
	snd_ca0106_mixer_resume(chip);
	अगर (chip->details->spi_dac) अणु
		क्रम (i = 0; i < ARRAY_SIZE(chip->spi_dac_reg); i++)
			snd_ca0106_spi_ग_लिखो(chip, chip->spi_dac_reg[i]);
	पूर्ण

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(snd_ca0106_pm, snd_ca0106_suspend, snd_ca0106_resume);
#घोषणा SND_CA0106_PM_OPS	&snd_ca0106_pm
#अन्यथा
#घोषणा SND_CA0106_PM_OPS	शून्य
#पूर्ण_अगर

// PCI IDs
अटल स्थिर काष्ठा pci_device_id snd_ca0106_ids[] = अणु
	अणु PCI_VDEVICE(CREATIVE, 0x0007), 0 पूर्ण,	/* Audigy LS or Live 24bit */
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, snd_ca0106_ids);

// pci_driver definition
अटल काष्ठा pci_driver ca0106_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_ca0106_ids,
	.probe = snd_ca0106_probe,
	.हटाओ = snd_ca0106_हटाओ,
	.driver = अणु
		.pm = SND_CA0106_PM_OPS,
	पूर्ण,
पूर्ण;

module_pci_driver(ca0106_driver);
