<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *                   Creative Lअसल, Inc.
 *  Routines क्रम control of EMU10K1 chips
 *
 *  Copyright (c) by James Courtier-Dutton <James@superbug.co.uk>
 *      Added support क्रम Audigy 2 Value.
 *  	Added EMU 1010 support.
 *  	General bug fixes and enhancements.
 *
 *  BUGS:
 *    --
 *
 *  TODO:
 *    --
 */

#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iommu.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mutex.h>


#समावेश <sound/core.h>
#समावेश <sound/emu10k1.h>
#समावेश <linux/firmware.h>
#समावेश "p16v.h"
#समावेश "tina2.h"
#समावेश "p17v.h"


#घोषणा HANA_खाताNAME "emu/hana.fw"
#घोषणा DOCK_खाताNAME "emu/audio_dock.fw"
#घोषणा EMU1010B_खाताNAME "emu/emu1010b.fw"
#घोषणा MICRO_DOCK_खाताNAME "emu/micro_dock.fw"
#घोषणा EMU0404_खाताNAME "emu/emu0404.fw"
#घोषणा EMU1010_NOTEBOOK_खाताNAME "emu/emu1010_notebook.fw"

MODULE_FIRMWARE(HANA_खाताNAME);
MODULE_FIRMWARE(DOCK_खाताNAME);
MODULE_FIRMWARE(EMU1010B_खाताNAME);
MODULE_FIRMWARE(MICRO_DOCK_खाताNAME);
MODULE_FIRMWARE(EMU0404_खाताNAME);
MODULE_FIRMWARE(EMU1010_NOTEBOOK_खाताNAME);


/*************************************************************************
 * EMU10K1 init / करोne
 *************************************************************************/

व्योम snd_emu10k1_voice_init(काष्ठा snd_emu10k1 *emu, पूर्णांक ch)
अणु
	snd_emu10k1_ptr_ग_लिखो(emu, DCYSUSV, ch, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, IP, ch, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, VTFT, ch, 0xffff);
	snd_emu10k1_ptr_ग_लिखो(emu, CVCF, ch, 0xffff);
	snd_emu10k1_ptr_ग_लिखो(emu, PTRX, ch, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, CPF, ch, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, CCR, ch, 0);

	snd_emu10k1_ptr_ग_लिखो(emu, PSST, ch, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, DSL, ch, 0x10);
	snd_emu10k1_ptr_ग_लिखो(emu, CCCA, ch, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, Z1, ch, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, Z2, ch, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, FXRT, ch, 0x32100000);

	snd_emu10k1_ptr_ग_लिखो(emu, ATKHLDM, ch, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, DCYSUSM, ch, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, IFATN, ch, 0xffff);
	snd_emu10k1_ptr_ग_लिखो(emu, PEFE, ch, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, FMMOD, ch, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, TREMFRQ, ch, 24);	/* 1 Hz */
	snd_emu10k1_ptr_ग_लिखो(emu, FM2FRQ2, ch, 24);	/* 1 Hz */
	snd_emu10k1_ptr_ग_लिखो(emu, TEMPENV, ch, 0);

	/*** these are last so OFF prevents writing ***/
	snd_emu10k1_ptr_ग_लिखो(emu, LFOVAL2, ch, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, LFOVAL1, ch, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, ATKHLDV, ch, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, ENVVOL, ch, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, ENVVAL, ch, 0);

	/* Audigy extra stuffs */
	अगर (emu->audigy) अणु
		snd_emu10k1_ptr_ग_लिखो(emu, 0x4c, ch, 0); /* ?? */
		snd_emu10k1_ptr_ग_लिखो(emu, 0x4d, ch, 0); /* ?? */
		snd_emu10k1_ptr_ग_लिखो(emu, 0x4e, ch, 0); /* ?? */
		snd_emu10k1_ptr_ग_लिखो(emu, 0x4f, ch, 0); /* ?? */
		snd_emu10k1_ptr_ग_लिखो(emu, A_FXRT1, ch, 0x03020100);
		snd_emu10k1_ptr_ग_लिखो(emu, A_FXRT2, ch, 0x3f3f3f3f);
		snd_emu10k1_ptr_ग_लिखो(emu, A_SENDAMOUNTS, ch, 0);
	पूर्ण
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक spi_dac_init[] = अणु
		0x00ff,
		0x02ff,
		0x0400,
		0x0520,
		0x0600,
		0x08ff,
		0x0aff,
		0x0cff,
		0x0eff,
		0x10ff,
		0x1200,
		0x1400,
		0x1480,
		0x1800,
		0x1aff,
		0x1cff,
		0x1e00,
		0x0530,
		0x0602,
		0x0622,
		0x1400,
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
	अणु 0x15, ADC_MUX_2 पूर्ण,  /* ADC Mixer control. Mic क्रम A2ZS Notebook */
पूर्ण;

अटल पूर्णांक snd_emu10k1_init(काष्ठा snd_emu10k1 *emu, पूर्णांक enable_ir, पूर्णांक resume)
अणु
	अचिन्हित पूर्णांक silent_page;
	पूर्णांक ch;
	u32 पंचांगp;

	/* disable audio and lock cache */
	outl(HCFG_LOCKSOUNDCACHE | HCFG_LOCKTANKCACHE_MASK |
		HCFG_MUTEBUTTONENABLE, emu->port + HCFG);

	/* reset recording buffers */
	snd_emu10k1_ptr_ग_लिखो(emu, MICBS, 0, ADCBS_बफ_मानE_NONE);
	snd_emu10k1_ptr_ग_लिखो(emu, MICBA, 0, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, FXBS, 0, ADCBS_बफ_मानE_NONE);
	snd_emu10k1_ptr_ग_लिखो(emu, FXBA, 0, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, ADCBS, 0, ADCBS_बफ_मानE_NONE);
	snd_emu10k1_ptr_ग_लिखो(emu, ADCBA, 0, 0);

	/* disable channel पूर्णांकerrupt */
	outl(0, emu->port + INTE);
	snd_emu10k1_ptr_ग_लिखो(emu, CLIEL, 0, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, CLIEH, 0, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, SOLEL, 0, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, SOLEH, 0, 0);

	अगर (emu->audigy) अणु
		/* set SPDIF bypass mode */
		snd_emu10k1_ptr_ग_लिखो(emu, SPBYPASS, 0, SPBYPASS_FORMAT);
		/* enable rear left + rear right AC97 slots */
		snd_emu10k1_ptr_ग_लिखो(emu, AC97SLOT, 0, AC97SLOT_REAR_RIGHT |
				      AC97SLOT_REAR_LEFT);
	पूर्ण

	/* init envelope engine */
	क्रम (ch = 0; ch < NUM_G; ch++)
		snd_emu10k1_voice_init(emu, ch);

	snd_emu10k1_ptr_ग_लिखो(emu, SPCS0, 0, emu->spdअगर_bits[0]);
	snd_emu10k1_ptr_ग_लिखो(emu, SPCS1, 0, emu->spdअगर_bits[1]);
	snd_emu10k1_ptr_ग_लिखो(emu, SPCS2, 0, emu->spdअगर_bits[2]);

	अगर (emu->card_capabilities->ca0151_chip) अणु /* audigy2 */
		/* Hacks क्रम Alice3 to work independent of haP16V driver */
		/* Setup SRCMulti_I2S SamplingRate */
		पंचांगp = snd_emu10k1_ptr_पढ़ो(emu, A_SPDIF_SAMPLERATE, 0);
		पंचांगp &= 0xfffff1ff;
		पंचांगp |= (0x2<<9);
		snd_emu10k1_ptr_ग_लिखो(emu, A_SPDIF_SAMPLERATE, 0, पंचांगp);

		/* Setup SRCSel (Enable Spdअगर,I2S SRCMulti) */
		snd_emu10k1_ptr20_ग_लिखो(emu, SRCSel, 0, 0x14);
		/* Setup SRCMulti Input Audio Enable */
		/* Use 0xFFFFFFFF to enable P16V sounds. */
		snd_emu10k1_ptr20_ग_लिखो(emu, SRCMULTI_ENABLE, 0, 0xFFFFFFFF);

		/* Enabled Phased (8-channel) P16V playback */
		outl(0x0201, emu->port + HCFG2);
		/* Set playback routing. */
		snd_emu10k1_ptr20_ग_लिखो(emu, CAPTURE_P16V_SOURCE, 0, 0x78e4);
	पूर्ण
	अगर (emu->card_capabilities->ca0108_chip) अणु /* audigy2 Value */
		/* Hacks क्रम Alice3 to work independent of haP16V driver */
		dev_info(emu->card->dev, "Audigy2 value: Special config.\n");
		/* Setup SRCMulti_I2S SamplingRate */
		पंचांगp = snd_emu10k1_ptr_पढ़ो(emu, A_SPDIF_SAMPLERATE, 0);
		पंचांगp &= 0xfffff1ff;
		पंचांगp |= (0x2<<9);
		snd_emu10k1_ptr_ग_लिखो(emu, A_SPDIF_SAMPLERATE, 0, पंचांगp);

		/* Setup SRCSel (Enable Spdअगर,I2S SRCMulti) */
		outl(0x600000, emu->port + 0x20);
		outl(0x14, emu->port + 0x24);

		/* Setup SRCMulti Input Audio Enable */
		outl(0x7b0000, emu->port + 0x20);
		outl(0xFF000000, emu->port + 0x24);

		/* Setup SPDIF Out Audio Enable */
		/* The Audigy 2 Value has a separate SPDIF out,
		 * so no need क्रम a mixer चयन
		 */
		outl(0x7a0000, emu->port + 0x20);
		outl(0xFF000000, emu->port + 0x24);
		पंचांगp = inl(emu->port + A_IOCFG) & ~0x8; /* Clear bit 3 */
		outl(पंचांगp, emu->port + A_IOCFG);
	पूर्ण
	अगर (emu->card_capabilities->spi_dac) अणु /* Audigy 2 ZS Notebook with DAC Wolfson WM8768/WM8568 */
		पूर्णांक size, n;

		size = ARRAY_SIZE(spi_dac_init);
		क्रम (n = 0; n < size; n++)
			snd_emu10k1_spi_ग_लिखो(emu, spi_dac_init[n]);

		snd_emu10k1_ptr20_ग_लिखो(emu, 0x60, 0, 0x10);
		/* Enable GPIOs
		 * GPIO0: Unknown
		 * GPIO1: Speakers-enabled.
		 * GPIO2: Unknown
		 * GPIO3: Unknown
		 * GPIO4: IEC958 Output on.
		 * GPIO5: Unknown
		 * GPIO6: Unknown
		 * GPIO7: Unknown
		 */
		outl(0x76, emu->port + A_IOCFG); /* Winकरोws uses 0x3f76 */
	पूर्ण
	अगर (emu->card_capabilities->i2c_adc) अणु /* Audigy 2 ZS Notebook with ADC Wolfson WM8775 */
		पूर्णांक size, n;

		snd_emu10k1_ptr20_ग_लिखो(emu, P17V_I2S_SRC_SEL, 0, 0x2020205f);
		पंचांगp = inl(emu->port + A_IOCFG);
		outl(पंचांगp | 0x4, emu->port + A_IOCFG);  /* Set bit 2 क्रम mic input */
		पंचांगp = inl(emu->port + A_IOCFG);
		size = ARRAY_SIZE(i2c_adc_init);
		क्रम (n = 0; n < size; n++)
			snd_emu10k1_i2c_ग_लिखो(emu, i2c_adc_init[n][0], i2c_adc_init[n][1]);
		क्रम (n = 0; n < 4; n++) अणु
			emu->i2c_capture_volume[n][0] = 0xcf;
			emu->i2c_capture_volume[n][1] = 0xcf;
		पूर्ण
	पूर्ण


	snd_emu10k1_ptr_ग_लिखो(emu, PTB, 0, emu->ptb_pages.addr);
	snd_emu10k1_ptr_ग_लिखो(emu, TCB, 0, 0);	/* taken from original driver */
	snd_emu10k1_ptr_ग_लिखो(emu, TCBS, 0, 4);	/* taken from original driver */

	silent_page = (emu->silent_page.addr << emu->address_mode) | (emu->address_mode ? MAP_PTI_MASK1 : MAP_PTI_MASK0);
	क्रम (ch = 0; ch < NUM_G; ch++) अणु
		snd_emu10k1_ptr_ग_लिखो(emu, MAPA, ch, silent_page);
		snd_emu10k1_ptr_ग_लिखो(emu, MAPB, ch, silent_page);
	पूर्ण

	अगर (emu->card_capabilities->emu_model) अणु
		outl(HCFG_AUTOMUTE_ASYNC |
			HCFG_EMU32_SLAVE |
			HCFG_AUDIOENABLE, emu->port + HCFG);
	/*
	 *  Hokay, setup HCFG
	 *   Mute Disable Audio = 0
	 *   Lock Tank Memory = 1
	 *   Lock Sound Memory = 0
	 *   Auto Mute = 1
	 */
	पूर्ण अन्यथा अगर (emu->audigy) अणु
		अगर (emu->revision == 4) /* audigy2 */
			outl(HCFG_AUDIOENABLE |
			     HCFG_AC3ENABLE_CDSPDIF |
			     HCFG_AC3ENABLE_GPSPDIF |
			     HCFG_AUTOMUTE | HCFG_JOYENABLE, emu->port + HCFG);
		अन्यथा
			outl(HCFG_AUTOMUTE | HCFG_JOYENABLE, emu->port + HCFG);
	/* FIXME: Remove all these emu->model and replace it with a card recognition parameter,
	 * e.g. card_capabilities->joystick */
	पूर्ण अन्यथा अगर (emu->model == 0x20 ||
	    emu->model == 0xc400 ||
	    (emu->model == 0x21 && emu->revision < 6))
		outl(HCFG_LOCKTANKCACHE_MASK | HCFG_AUTOMUTE, emu->port + HCFG);
	अन्यथा
		/* With on-chip joystick */
		outl(HCFG_LOCKTANKCACHE_MASK | HCFG_AUTOMUTE | HCFG_JOYENABLE, emu->port + HCFG);

	अगर (enable_ir) अणु	/* enable IR क्रम SB Live */
		अगर (emu->card_capabilities->emu_model) अणु
			;  /* Disable all access to A_IOCFG क्रम the emu1010 */
		पूर्ण अन्यथा अगर (emu->card_capabilities->i2c_adc) अणु
			;  /* Disable A_IOCFG क्रम Audigy 2 ZS Notebook */
		पूर्ण अन्यथा अगर (emu->audigy) अणु
			अचिन्हित पूर्णांक reg = inl(emu->port + A_IOCFG);
			outl(reg | A_IOCFG_GPOUT2, emu->port + A_IOCFG);
			udelay(500);
			outl(reg | A_IOCFG_GPOUT1 | A_IOCFG_GPOUT2, emu->port + A_IOCFG);
			udelay(100);
			outl(reg, emu->port + A_IOCFG);
		पूर्ण अन्यथा अणु
			अचिन्हित पूर्णांक reg = inl(emu->port + HCFG);
			outl(reg | HCFG_GPOUT2, emu->port + HCFG);
			udelay(500);
			outl(reg | HCFG_GPOUT1 | HCFG_GPOUT2, emu->port + HCFG);
			udelay(100);
			outl(reg, emu->port + HCFG);
		पूर्ण
	पूर्ण

	अगर (emu->card_capabilities->emu_model) अणु
		;  /* Disable all access to A_IOCFG क्रम the emu1010 */
	पूर्ण अन्यथा अगर (emu->card_capabilities->i2c_adc) अणु
		;  /* Disable A_IOCFG क्रम Audigy 2 ZS Notebook */
	पूर्ण अन्यथा अगर (emu->audigy) अणु	/* enable analog output */
		अचिन्हित पूर्णांक reg = inl(emu->port + A_IOCFG);
		outl(reg | A_IOCFG_GPOUT0, emu->port + A_IOCFG);
	पूर्ण

	अगर (emu->address_mode == 0) अणु
		/* use 16M in 4G */
		outl(inl(emu->port + HCFG) | HCFG_EXPANDED_MEM, emu->port + HCFG);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम snd_emu10k1_audio_enable(काष्ठा snd_emu10k1 *emu)
अणु
	/*
	 *  Enable the audio bit
	 */
	outl(inl(emu->port + HCFG) | HCFG_AUDIOENABLE, emu->port + HCFG);

	/* Enable analog/digital outs on audigy */
	अगर (emu->card_capabilities->emu_model) अणु
		;  /* Disable all access to A_IOCFG क्रम the emu1010 */
	पूर्ण अन्यथा अगर (emu->card_capabilities->i2c_adc) अणु
		;  /* Disable A_IOCFG क्रम Audigy 2 ZS Notebook */
	पूर्ण अन्यथा अगर (emu->audigy) अणु
		outl(inl(emu->port + A_IOCFG) & ~0x44, emu->port + A_IOCFG);

		अगर (emu->card_capabilities->ca0151_chip) अणु /* audigy2 */
			/* Unmute Analog now.  Set GPO6 to 1 क्रम Apollo.
			 * This has to be करोne after init ALice3 I2SOut beyond 48KHz.
			 * So, sequence is important. */
			outl(inl(emu->port + A_IOCFG) | 0x0040, emu->port + A_IOCFG);
		पूर्ण अन्यथा अगर (emu->card_capabilities->ca0108_chip) अणु /* audigy2 value */
			/* Unmute Analog now. */
			outl(inl(emu->port + A_IOCFG) | 0x0060, emu->port + A_IOCFG);
		पूर्ण अन्यथा अणु
			/* Disable routing from AC97 line out to Front speakers */
			outl(inl(emu->port + A_IOCFG) | 0x0080, emu->port + A_IOCFG);
		पूर्ण
	पूर्ण

#अगर 0
	अणु
	अचिन्हित पूर्णांक पंचांगp;
	/* FIXME: the following routine disables LiveDrive-II !! */
	/* TOSLink detection */
	emu->tos_link = 0;
	पंचांगp = inl(emu->port + HCFG);
	अगर (पंचांगp & (HCFG_GPINPUT0 | HCFG_GPINPUT1)) अणु
		outl(पंचांगp|0x800, emu->port + HCFG);
		udelay(50);
		अगर (पंचांगp != (inl(emu->port + HCFG) & ~0x800)) अणु
			emu->tos_link = 1;
			outl(पंचांगp, emu->port + HCFG);
		पूर्ण
	पूर्ण
	पूर्ण
#पूर्ण_अगर

	snd_emu10k1_पूर्णांकr_enable(emu, INTE_PCIERRORENABLE);
पूर्ण

पूर्णांक snd_emu10k1_करोne(काष्ठा snd_emu10k1 *emu)
अणु
	पूर्णांक ch;

	outl(0, emu->port + INTE);

	/*
	 *  Shutकरोwn the chip
	 */
	क्रम (ch = 0; ch < NUM_G; ch++)
		snd_emu10k1_ptr_ग_लिखो(emu, DCYSUSV, ch, 0);
	क्रम (ch = 0; ch < NUM_G; ch++) अणु
		snd_emu10k1_ptr_ग_लिखो(emu, VTFT, ch, 0);
		snd_emu10k1_ptr_ग_लिखो(emu, CVCF, ch, 0);
		snd_emu10k1_ptr_ग_लिखो(emu, PTRX, ch, 0);
		snd_emu10k1_ptr_ग_लिखो(emu, CPF, ch, 0);
	पूर्ण

	/* reset recording buffers */
	snd_emu10k1_ptr_ग_लिखो(emu, MICBS, 0, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, MICBA, 0, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, FXBS, 0, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, FXBA, 0, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, FXWC, 0, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, ADCBS, 0, ADCBS_बफ_मानE_NONE);
	snd_emu10k1_ptr_ग_लिखो(emu, ADCBA, 0, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, TCBS, 0, TCBS_BUFFSIZE_16K);
	snd_emu10k1_ptr_ग_लिखो(emu, TCB, 0, 0);
	अगर (emu->audigy)
		snd_emu10k1_ptr_ग_लिखो(emu, A_DBG, 0, A_DBG_SINGLE_STEP);
	अन्यथा
		snd_emu10k1_ptr_ग_लिखो(emu, DBG, 0, EMU10K1_DBG_SINGLE_STEP);

	/* disable channel पूर्णांकerrupt */
	snd_emu10k1_ptr_ग_लिखो(emu, CLIEL, 0, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, CLIEH, 0, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, SOLEL, 0, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, SOLEH, 0, 0);

	/* disable audio and lock cache */
	outl(HCFG_LOCKSOUNDCACHE | HCFG_LOCKTANKCACHE_MASK | HCFG_MUTEBUTTONENABLE, emu->port + HCFG);
	snd_emu10k1_ptr_ग_लिखो(emu, PTB, 0, 0);

	वापस 0;
पूर्ण

/*************************************************************************
 * ECARD functional implementation
 *************************************************************************/

/* In A1 Silicon, these bits are in the HC रेजिस्टर */
#घोषणा HOOKN_BIT		(1L << 12)
#घोषणा HANDN_BIT		(1L << 11)
#घोषणा PULSEN_BIT		(1L << 10)

#घोषणा EC_GDI1			(1 << 13)
#घोषणा EC_GDI0			(1 << 14)

#घोषणा EC_NUM_CONTROL_BITS	20

#घोषणा EC_AC3_DATA_SELN	0x0001L
#घोषणा EC_EE_DATA_SEL		0x0002L
#घोषणा EC_EE_CNTRL_SELN	0x0004L
#घोषणा EC_EECLK		0x0008L
#घोषणा EC_EECS			0x0010L
#घोषणा EC_EESDO		0x0020L
#घोषणा EC_TRIM_CSN		0x0040L
#घोषणा EC_TRIM_SCLK		0x0080L
#घोषणा EC_TRIM_SDATA		0x0100L
#घोषणा EC_TRIM_MUTEN		0x0200L
#घोषणा EC_ADCCAL		0x0400L
#घोषणा EC_ADCRSTN		0x0800L
#घोषणा EC_DACCAL		0x1000L
#घोषणा EC_DACMUTEN		0x2000L
#घोषणा EC_LEDN			0x4000L

#घोषणा EC_SPDIF0_SEL_SHIFT	15
#घोषणा EC_SPDIF1_SEL_SHIFT	17
#घोषणा EC_SPDIF0_SEL_MASK	(0x3L << EC_SPDIF0_SEL_SHIFT)
#घोषणा EC_SPDIF1_SEL_MASK	(0x7L << EC_SPDIF1_SEL_SHIFT)
#घोषणा EC_SPDIF0_SELECT(_x)	(((_x) << EC_SPDIF0_SEL_SHIFT) & EC_SPDIF0_SEL_MASK)
#घोषणा EC_SPDIF1_SELECT(_x)	(((_x) << EC_SPDIF1_SEL_SHIFT) & EC_SPDIF1_SEL_MASK)
#घोषणा EC_CURRENT_PROM_VERSION 0x01	/* Self-explanatory.  This should
					 * be incremented any समय the EEPROM's
					 * क्रमmat is changed.  */

#घोषणा EC_EEPROM_SIZE		0x40	/* ECARD EEPROM has 64 16-bit words */

/* Addresses क्रम special values stored in to EEPROM */
#घोषणा EC_PROM_VERSION_ADDR	0x20	/* Address of the current prom version */
#घोषणा EC_BOARDREV0_ADDR	0x21	/* LSW of board rev */
#घोषणा EC_BOARDREV1_ADDR	0x22	/* MSW of board rev */

#घोषणा EC_LAST_PROMखाता_ADDR	0x2f

#घोषणा EC_SERIALNUM_ADDR	0x30	/* First word of serial number.  The
					 * can be up to 30 अक्षरacters in length
					 * and is stored as a शून्य-terminated
					 * ASCII string.  Any unused bytes must be
					 * filled with zeros */
#घोषणा EC_CHECKSUM_ADDR	0x3f	/* Location at which checksum is stored */


/* Most of this stuff is pretty self-evident.  According to the hardware
 * dudes, we need to leave the ADCCAL bit low in order to aव्योम a DC
 * offset problem.  Weird.
 */
#घोषणा EC_RAW_RUN_MODE		(EC_DACMUTEN | EC_ADCRSTN | EC_TRIM_MUTEN | \
				 EC_TRIM_CSN)


#घोषणा EC_DEFAULT_ADC_GAIN	0xC4C4
#घोषणा EC_DEFAULT_SPDIF0_SEL	0x0
#घोषणा EC_DEFAULT_SPDIF1_SEL	0x4

/**************************************************************************
 * @func Clock bits पूर्णांकo the Ecard's control latch.  The Ecard uses a
 *  control latch will is loaded bit-serially by toggling the Modem control
 *  lines from function 2 on the E8010.  This function hides these details
 *  and presents the illusion that we are actually writing to a distinct
 *  रेजिस्टर.
 */

अटल व्योम snd_emu10k1_ecard_ग_लिखो(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक value)
अणु
	अचिन्हित लघु count;
	अचिन्हित पूर्णांक data;
	अचिन्हित दीर्घ hc_port;
	अचिन्हित पूर्णांक hc_value;

	hc_port = emu->port + HCFG;
	hc_value = inl(hc_port) & ~(HOOKN_BIT | HANDN_BIT | PULSEN_BIT);
	outl(hc_value, hc_port);

	क्रम (count = 0; count < EC_NUM_CONTROL_BITS; count++) अणु

		/* Set up the value */
		data = ((value & 0x1) ? PULSEN_BIT : 0);
		value >>= 1;

		outl(hc_value | data, hc_port);

		/* Clock the shअगरt रेजिस्टर */
		outl(hc_value | data | HANDN_BIT, hc_port);
		outl(hc_value | data, hc_port);
	पूर्ण

	/* Latch the bits */
	outl(hc_value | HOOKN_BIT, hc_port);
	outl(hc_value, hc_port);
पूर्ण

/**************************************************************************
 * @func Set the gain of the ECARD's CS3310 Trim/gain controller.  The
 * trim value consists of a 16bit value which is composed of two
 * 8 bit gain/trim values, one क्रम the left channel and one क्रम the
 * right channel.  The following table maps from the Gain/Attenuation
 * value in decibels पूर्णांकo the corresponding bit pattern क्रम a single
 * channel.
 */

अटल व्योम snd_emu10k1_ecard_setadcgain(काष्ठा snd_emu10k1 *emu,
					 अचिन्हित लघु gain)
अणु
	अचिन्हित पूर्णांक bit;

	/* Enable writing to the TRIM रेजिस्टरs */
	snd_emu10k1_ecard_ग_लिखो(emu, emu->ecard_ctrl & ~EC_TRIM_CSN);

	/* Do it again to insure that we meet hold समय requirements */
	snd_emu10k1_ecard_ग_लिखो(emu, emu->ecard_ctrl & ~EC_TRIM_CSN);

	क्रम (bit = (1 << 15); bit; bit >>= 1) अणु
		अचिन्हित पूर्णांक value;

		value = emu->ecard_ctrl & ~(EC_TRIM_CSN | EC_TRIM_SDATA);

		अगर (gain & bit)
			value |= EC_TRIM_SDATA;

		/* Clock the bit */
		snd_emu10k1_ecard_ग_लिखो(emu, value);
		snd_emu10k1_ecard_ग_लिखो(emu, value | EC_TRIM_SCLK);
		snd_emu10k1_ecard_ग_लिखो(emu, value);
	पूर्ण

	snd_emu10k1_ecard_ग_लिखो(emu, emu->ecard_ctrl);
पूर्ण

अटल पूर्णांक snd_emu10k1_ecard_init(काष्ठा snd_emu10k1 *emu)
अणु
	अचिन्हित पूर्णांक hc_value;

	/* Set up the initial settings */
	emu->ecard_ctrl = EC_RAW_RUN_MODE |
			  EC_SPDIF0_SELECT(EC_DEFAULT_SPDIF0_SEL) |
			  EC_SPDIF1_SELECT(EC_DEFAULT_SPDIF1_SEL);

	/* Step 0: Set the codec type in the hardware control रेजिस्टर
	 * and enable audio output */
	hc_value = inl(emu->port + HCFG);
	outl(hc_value | HCFG_AUDIOENABLE | HCFG_CODECFORMAT_I2S, emu->port + HCFG);
	inl(emu->port + HCFG);

	/* Step 1: Turn off the led and deनिश्चित TRIM_CS */
	snd_emu10k1_ecard_ग_लिखो(emu, EC_ADCCAL | EC_LEDN | EC_TRIM_CSN);

	/* Step 2: Calibrate the ADC and DAC */
	snd_emu10k1_ecard_ग_लिखो(emu, EC_DACCAL | EC_LEDN | EC_TRIM_CSN);

	/* Step 3: Wait क्रम aजबतक;   XXX We can't get away with this
	 * under a real operating प्रणाली; we'll need to block and रुको that
	 * way. */
	snd_emu10k1_रुको(emu, 48000);

	/* Step 4: Switch off the DAC and ADC calibration.  Note
	 * That ADC_CAL is actually an inverted संकेत, so we निश्चित
	 * it here to stop calibration.  */
	snd_emu10k1_ecard_ग_लिखो(emu, EC_ADCCAL | EC_LEDN | EC_TRIM_CSN);

	/* Step 4: Switch पूर्णांकo run mode */
	snd_emu10k1_ecard_ग_लिखो(emu, emu->ecard_ctrl);

	/* Step 5: Set the analog input gain */
	snd_emu10k1_ecard_setadcgain(emu, EC_DEFAULT_ADC_GAIN);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_cardbus_init(काष्ठा snd_emu10k1 *emu)
अणु
	अचिन्हित दीर्घ special_port;
	__always_unused अचिन्हित पूर्णांक value;

	/* Special initialisation routine
	 * beक्रमe the rest of the IO-Ports become active.
	 */
	special_port = emu->port + 0x38;
	value = inl(special_port);
	outl(0x00d00000, special_port);
	value = inl(special_port);
	outl(0x00d00001, special_port);
	value = inl(special_port);
	outl(0x00d0005f, special_port);
	value = inl(special_port);
	outl(0x00d0007f, special_port);
	value = inl(special_port);
	outl(0x0090007f, special_port);
	value = inl(special_port);

	snd_emu10k1_ptr20_ग_लिखो(emu, TINA2_VOLUME, 0, 0xfefefefe); /* Defaults to 0x30303030 */
	/* Delay to give समय क्रम ADC chip to चयन on. It needs 113ms */
	msleep(200);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu1010_load_firmware_entry(काष्ठा snd_emu10k1 *emu,
				     स्थिर काष्ठा firmware *fw_entry)
अणु
	पूर्णांक n, i;
	पूर्णांक reg;
	पूर्णांक value;
	__always_unused अचिन्हित पूर्णांक ग_लिखो_post;
	अचिन्हित दीर्घ flags;

	अगर (!fw_entry)
		वापस -EIO;

	/* The FPGA is a Xilinx Spartan IIE XC2S50E */
	/* GPIO7 -> FPGA PGMN
	 * GPIO6 -> FPGA CCLK
	 * GPIO5 -> FPGA DIN
	 * FPGA CONFIG OFF -> FPGA PGMN
	 */
	spin_lock_irqsave(&emu->emu_lock, flags);
	outl(0x00, emu->port + A_IOCFG); /* Set PGMN low क्रम 1uS. */
	ग_लिखो_post = inl(emu->port + A_IOCFG);
	udelay(100);
	outl(0x80, emu->port + A_IOCFG); /* Leave bit 7 set during netlist setup. */
	ग_लिखो_post = inl(emu->port + A_IOCFG);
	udelay(100); /* Allow FPGA memory to clean */
	क्रम (n = 0; n < fw_entry->size; n++) अणु
		value = fw_entry->data[n];
		क्रम (i = 0; i < 8; i++) अणु
			reg = 0x80;
			अगर (value & 0x1)
				reg = reg | 0x20;
			value = value >> 1;
			outl(reg, emu->port + A_IOCFG);
			ग_लिखो_post = inl(emu->port + A_IOCFG);
			outl(reg | 0x40, emu->port + A_IOCFG);
			ग_लिखो_post = inl(emu->port + A_IOCFG);
		पूर्ण
	पूर्ण
	/* After programming, set GPIO bit 4 high again. */
	outl(0x10, emu->port + A_IOCFG);
	ग_लिखो_post = inl(emu->port + A_IOCFG);
	spin_unlock_irqrestore(&emu->emu_lock, flags);

	वापस 0;
पूर्ण

/* firmware file names, per model, init-fw and करोck-fw (optional) */
अटल स्थिर अक्षर * स्थिर firmware_names[5][2] = अणु
	[EMU_MODEL_EMU1010] = अणु
		HANA_खाताNAME, DOCK_खाताNAME
	पूर्ण,
	[EMU_MODEL_EMU1010B] = अणु
		EMU1010B_खाताNAME, MICRO_DOCK_खाताNAME
	पूर्ण,
	[EMU_MODEL_EMU1616] = अणु
		EMU1010_NOTEBOOK_खाताNAME, MICRO_DOCK_खाताNAME
	पूर्ण,
	[EMU_MODEL_EMU0404] = अणु
		EMU0404_खाताNAME, शून्य
	पूर्ण,
पूर्ण;

अटल पूर्णांक snd_emu1010_load_firmware(काष्ठा snd_emu10k1 *emu, पूर्णांक करोck,
				     स्थिर काष्ठा firmware **fw)
अणु
	स्थिर अक्षर *filename;
	पूर्णांक err;

	अगर (!*fw) अणु
		filename = firmware_names[emu->card_capabilities->emu_model][करोck];
		अगर (!filename)
			वापस 0;
		err = request_firmware(fw, filename, &emu->pci->dev);
		अगर (err)
			वापस err;
	पूर्ण

	वापस snd_emu1010_load_firmware_entry(emu, *fw);
पूर्ण

अटल व्योम emu1010_firmware_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा snd_emu10k1 *emu;
	u32 पंचांगp, पंचांगp2, reg;
	पूर्णांक err;

	emu = container_of(work, काष्ठा snd_emu10k1,
			   emu1010.firmware_work.work);
	अगर (emu->card->shutकरोwn)
		वापस;
#अगर_घोषित CONFIG_PM_SLEEP
	अगर (emu->suspend)
		वापस;
#पूर्ण_अगर
	snd_emu1010_fpga_पढ़ो(emu, EMU_HANA_IRQ_STATUS, &पंचांगp); /* IRQ Status */
	snd_emu1010_fpga_पढ़ो(emu, EMU_HANA_OPTION_CARDS, &reg); /* OPTIONS: Which cards are attached to the EMU */
	अगर (reg & EMU_HANA_OPTION_DOCK_OFFLINE) अणु
		/* Audio Dock attached */
		/* Return to Audio Dock programming mode */
		dev_info(emu->card->dev,
			 "emu1010: Loading Audio Dock Firmware\n");
		snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_FPGA_CONFIG,
				       EMU_HANA_FPGA_CONFIG_AUDIODOCK);
		err = snd_emu1010_load_firmware(emu, 1, &emu->करोck_fw);
		अगर (err < 0)
			जाओ next;

		snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_FPGA_CONFIG, 0);
		snd_emu1010_fpga_पढ़ो(emu, EMU_HANA_IRQ_STATUS, &पंचांगp);
		dev_info(emu->card->dev,
			 "emu1010: EMU_HANA+DOCK_IRQ_STATUS = 0x%x\n", पंचांगp);
		/* ID, should पढ़ो & 0x7f = 0x55 when FPGA programmed. */
		snd_emu1010_fpga_पढ़ो(emu, EMU_HANA_ID, &पंचांगp);
		dev_info(emu->card->dev,
			 "emu1010: EMU_HANA+DOCK_ID = 0x%x\n", पंचांगp);
		अगर ((पंचांगp & 0x1f) != 0x15) अणु
			/* FPGA failed to be programmed */
			dev_info(emu->card->dev,
				 "emu1010: Loading Audio Dock Firmware file failed, reg = 0x%x\n",
				 पंचांगp);
			जाओ next;
		पूर्ण
		dev_info(emu->card->dev,
			 "emu1010: Audio Dock Firmware loaded\n");
		snd_emu1010_fpga_पढ़ो(emu, EMU_DOCK_MAJOR_REV, &पंचांगp);
		snd_emu1010_fpga_पढ़ो(emu, EMU_DOCK_MINOR_REV, &पंचांगp2);
		dev_info(emu->card->dev, "Audio Dock ver: %u.%u\n", पंचांगp, पंचांगp2);
		/* Sync घड़ीing between 1010 and Dock */
		/* Allow DLL to settle */
		msleep(10);
		/* Unmute all. Default is muted after a firmware load */
		snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_UNMUTE, EMU_UNMUTE);
	पूर्ण अन्यथा अगर (!reg && emu->emu1010.last_reg) अणु
		/* Audio Dock हटाओd */
		dev_info(emu->card->dev, "emu1010: Audio Dock detached\n");
		/* Unmute all */
		snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_UNMUTE, EMU_UNMUTE);
	पूर्ण

 next:
	emu->emu1010.last_reg = reg;
	अगर (!emu->card->shutकरोwn)
		schedule_delayed_work(&emu->emu1010.firmware_work,
				      msecs_to_jअगरfies(1000));
पूर्ण

/*
 * EMU-1010 - details found out from this driver, official MS Win drivers,
 * testing the card:
 *
 * Audigy2 (aka Alice2):
 * ---------------------
 * 	* communication over PCI
 * 	* conversion of 32-bit data coming over EMU32 links from HANA FPGA
 *	  to 2 x 16-bit, using पूर्णांकernal DSP inकाष्ठाions
 * 	* slave mode, घड़ी supplied by HANA
 * 	* linked to HANA using:
 * 		32 x 32-bit serial EMU32 output channels
 * 		16 x EMU32 input channels
 * 		(?) x I2S I/O channels (?)
 *
 * FPGA (aka HANA):
 * ---------------
 * 	* provides all (?) physical inमाला_दो and outमाला_दो of the card
 * 		(ADC, DAC, SPDIF I/O, ADAT I/O, etc.)
 * 	* provides घड़ी संकेत क्रम the card and Alice2
 * 	* two crystals - क्रम 44.1kHz and 48kHz multiples
 * 	* provides पूर्णांकernal routing of संकेत sources to संकेत destinations
 * 	* inमाला_दो/outमाला_दो to Alice2 - see above
 *
 * Current status of the driver:
 * ----------------------------
 * 	* only 44.1/48kHz supported (the MS Win driver supports up to 192 kHz)
 * 	* PCM device nb. 2:
 *		16 x 16-bit playback - snd_emu10k1_fx8010_playback_ops
 * 		16 x 32-bit capture - snd_emu10k1_capture_efx_ops
 */
अटल पूर्णांक snd_emu10k1_emu1010_init(काष्ठा snd_emu10k1 *emu)
अणु
	अचिन्हित पूर्णांक i;
	u32 पंचांगp, पंचांगp2, reg;
	पूर्णांक err;

	dev_info(emu->card->dev, "emu1010: Special config.\n");
	/* AC97 2.1, Any 16Meg of 4Gig address, Auto-Mute, EMU32 Slave,
	 * Lock Sound Memory Cache, Lock Tank Memory Cache,
	 * Mute all codecs.
	 */
	outl(0x0005a00c, emu->port + HCFG);
	/* AC97 2.1, Any 16Meg of 4Gig address, Auto-Mute, EMU32 Slave,
	 * Lock Tank Memory Cache,
	 * Mute all codecs.
	 */
	outl(0x0005a004, emu->port + HCFG);
	/* AC97 2.1, Any 16Meg of 4Gig address, Auto-Mute, EMU32 Slave,
	 * Mute all codecs.
	 */
	outl(0x0005a000, emu->port + HCFG);
	/* AC97 2.1, Any 16Meg of 4Gig address, Auto-Mute, EMU32 Slave,
	 * Mute all codecs.
	 */
	outl(0x0005a000, emu->port + HCFG);

	/* Disable 48Volt घातer to Audio Dock */
	snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_DOCK_PWR, 0);

	/* ID, should पढ़ो & 0x7f = 0x55. (Bit 7 is the IRQ bit) */
	snd_emu1010_fpga_पढ़ो(emu, EMU_HANA_ID, &reg);
	dev_dbg(emu->card->dev, "reg1 = 0x%x\n", reg);
	अगर ((reg & 0x3f) == 0x15) अणु
		/* FPGA netlist alपढ़ोy present so clear it */
		/* Return to programming mode */

		snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_FPGA_CONFIG, 0x02);
	पूर्ण
	snd_emu1010_fpga_पढ़ो(emu, EMU_HANA_ID, &reg);
	dev_dbg(emu->card->dev, "reg2 = 0x%x\n", reg);
	अगर ((reg & 0x3f) == 0x15) अणु
		/* FPGA failed to वापस to programming mode */
		dev_info(emu->card->dev,
			 "emu1010: FPGA failed to return to programming mode\n");
		वापस -ENODEV;
	पूर्ण
	dev_info(emu->card->dev, "emu1010: EMU_HANA_ID = 0x%x\n", reg);

	err = snd_emu1010_load_firmware(emu, 0, &emu->firmware);
	अगर (err < 0) अणु
		dev_info(emu->card->dev, "emu1010: Loading Firmware failed\n");
		वापस err;
	पूर्ण

	/* ID, should पढ़ो & 0x7f = 0x55 when FPGA programmed. */
	snd_emu1010_fpga_पढ़ो(emu, EMU_HANA_ID, &reg);
	अगर ((reg & 0x3f) != 0x15) अणु
		/* FPGA failed to be programmed */
		dev_info(emu->card->dev,
			 "emu1010: Loading Hana Firmware file failed, reg = 0x%x\n",
			 reg);
		वापस -ENODEV;
	पूर्ण

	dev_info(emu->card->dev, "emu1010: Hana Firmware loaded\n");
	snd_emu1010_fpga_पढ़ो(emu, EMU_HANA_MAJOR_REV, &पंचांगp);
	snd_emu1010_fpga_पढ़ो(emu, EMU_HANA_MINOR_REV, &पंचांगp2);
	dev_info(emu->card->dev, "emu1010: Hana version: %u.%u\n", पंचांगp, पंचांगp2);
	/* Enable 48Volt घातer to Audio Dock */
	snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_DOCK_PWR, EMU_HANA_DOCK_PWR_ON);

	snd_emu1010_fpga_पढ़ो(emu, EMU_HANA_OPTION_CARDS, &reg);
	dev_info(emu->card->dev, "emu1010: Card options = 0x%x\n", reg);
	snd_emu1010_fpga_पढ़ो(emu, EMU_HANA_OPTION_CARDS, &reg);
	dev_info(emu->card->dev, "emu1010: Card options = 0x%x\n", reg);
	snd_emu1010_fpga_पढ़ो(emu, EMU_HANA_OPTICAL_TYPE, &पंचांगp);
	/* Optical -> ADAT I/O  */
	/* 0 : SPDIF
	 * 1 : ADAT
	 */
	emu->emu1010.optical_in = 1; /* IN_ADAT */
	emu->emu1010.optical_out = 1; /* IN_ADAT */
	पंचांगp = 0;
	पंचांगp = (emu->emu1010.optical_in ? EMU_HANA_OPTICAL_IN_ADAT : 0) |
		(emu->emu1010.optical_out ? EMU_HANA_OPTICAL_OUT_ADAT : 0);
	snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_OPTICAL_TYPE, पंचांगp);
	snd_emu1010_fpga_पढ़ो(emu, EMU_HANA_ADC_PADS, &पंचांगp);
	/* Set no attenuation on Audio Dock pads. */
	snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_ADC_PADS, 0x00);
	emu->emu1010.adc_pads = 0x00;
	snd_emu1010_fpga_पढ़ो(emu, EMU_HANA_DOCK_MISC, &पंचांगp);
	/* Unmute Audio करोck DACs, Headphone source DAC-4. */
	snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_DOCK_MISC, 0x30);
	snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_DOCK_LEDS_2, 0x12);
	snd_emu1010_fpga_पढ़ो(emu, EMU_HANA_DAC_PADS, &पंचांगp);
	/* DAC PADs. */
	snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_DAC_PADS, 0x0f);
	emu->emu1010.dac_pads = 0x0f;
	snd_emu1010_fpga_पढ़ो(emu, EMU_HANA_DOCK_MISC, &पंचांगp);
	snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_DOCK_MISC, 0x30);
	snd_emu1010_fpga_पढ़ो(emu, EMU_HANA_SPDIF_MODE, &पंचांगp);
	/* SPDIF Format. Set Consumer mode, 24bit, copy enable */
	snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_SPDIF_MODE, 0x10);
	/* MIDI routing */
	snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_MIDI_IN, 0x19);
	/* Unknown. */
	snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_MIDI_OUT, 0x0c);
	/* IRQ Enable: All on */
	/* snd_emu1010_fpga_ग_लिखो(emu, 0x09, 0x0f ); */
	/* IRQ Enable: All off */
	snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_IRQ_ENABLE, 0x00);

	snd_emu1010_fpga_पढ़ो(emu, EMU_HANA_OPTION_CARDS, &reg);
	dev_info(emu->card->dev, "emu1010: Card options3 = 0x%x\n", reg);
	/* Default WCLK set to 48kHz. */
	snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_DEFCLOCK, 0x00);
	/* Word Clock source, Internal 48kHz x1 */
	snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_WCLOCK, EMU_HANA_WCLOCK_INT_48K);
	/* snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_WCLOCK, EMU_HANA_WCLOCK_INT_48K | EMU_HANA_WCLOCK_4X); */
	/* Audio Dock LEDs. */
	snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_DOCK_LEDS_2, 0x12);

#अगर 0
	/* For 96kHz */
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_0, EMU_SRC_HAMOA_ADC_LEFT1);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_1, EMU_SRC_HAMOA_ADC_RIGHT1);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_4, EMU_SRC_HAMOA_ADC_LEFT2);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_5, EMU_SRC_HAMOA_ADC_RIGHT2);
#पूर्ण_अगर
#अगर 0
	/* For 192kHz */
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_0, EMU_SRC_HAMOA_ADC_LEFT1);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_1, EMU_SRC_HAMOA_ADC_RIGHT1);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_2, EMU_SRC_HAMOA_ADC_LEFT2);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_3, EMU_SRC_HAMOA_ADC_RIGHT2);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_4, EMU_SRC_HAMOA_ADC_LEFT3);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_5, EMU_SRC_HAMOA_ADC_RIGHT3);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_6, EMU_SRC_HAMOA_ADC_LEFT4);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_7, EMU_SRC_HAMOA_ADC_RIGHT4);
#पूर्ण_अगर
#अगर 1
	/* For 48kHz */
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_0, EMU_SRC_DOCK_MIC_A1);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_1, EMU_SRC_DOCK_MIC_B1);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_2, EMU_SRC_HAMOA_ADC_LEFT2);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_3, EMU_SRC_HAMOA_ADC_LEFT2);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_4, EMU_SRC_DOCK_ADC1_LEFT1);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_5, EMU_SRC_DOCK_ADC1_RIGHT1);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_6, EMU_SRC_DOCK_ADC2_LEFT1);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_7, EMU_SRC_DOCK_ADC2_RIGHT1);
	/* Pavel Hofman - setting शेषs क्रम 8 more capture channels
	 * Defaults only, users will set their own values anyways, let's
	 * just copy/paste.
	 */

	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_8, EMU_SRC_DOCK_MIC_A1);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_9, EMU_SRC_DOCK_MIC_B1);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_A, EMU_SRC_HAMOA_ADC_LEFT2);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_B, EMU_SRC_HAMOA_ADC_LEFT2);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_C, EMU_SRC_DOCK_ADC1_LEFT1);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_D, EMU_SRC_DOCK_ADC1_RIGHT1);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_E, EMU_SRC_DOCK_ADC2_LEFT1);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_F, EMU_SRC_DOCK_ADC2_RIGHT1);
#पूर्ण_अगर
#अगर 0
	/* Original */
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_4, EMU_SRC_HANA_ADAT);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_5, EMU_SRC_HANA_ADAT + 1);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_6, EMU_SRC_HANA_ADAT + 2);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_7, EMU_SRC_HANA_ADAT + 3);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_8, EMU_SRC_HANA_ADAT + 4);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_9, EMU_SRC_HANA_ADAT + 5);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_A, EMU_SRC_HANA_ADAT + 6);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_B, EMU_SRC_HANA_ADAT + 7);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_C, EMU_SRC_DOCK_MIC_A1);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_D, EMU_SRC_DOCK_MIC_B1);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_E, EMU_SRC_HAMOA_ADC_LEFT2);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE2_EMU32_F, EMU_SRC_HAMOA_ADC_LEFT2);
#पूर्ण_अगर
	क्रम (i = 0; i < 0x20; i++) अणु
		/* AudioDock Elink <- Silence */
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu, 0x0100 + i, EMU_SRC_SILENCE);
	पूर्ण
	क्रम (i = 0; i < 4; i++) अणु
		/* Hana SPDIF Out <- Silence */
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu, 0x0200 + i, EMU_SRC_SILENCE);
	पूर्ण
	क्रम (i = 0; i < 7; i++) अणु
		/* Hamoa DAC <- Silence */
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu, 0x0300 + i, EMU_SRC_SILENCE);
	पूर्ण
	क्रम (i = 0; i < 7; i++) अणु
		/* Hana ADAT Out <- Silence */
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu, EMU_DST_HANA_ADAT + i, EMU_SRC_SILENCE);
	पूर्ण
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE_I2S0_LEFT, EMU_SRC_DOCK_ADC1_LEFT1);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE_I2S0_RIGHT, EMU_SRC_DOCK_ADC1_RIGHT1);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE_I2S1_LEFT, EMU_SRC_DOCK_ADC2_LEFT1);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE_I2S1_RIGHT, EMU_SRC_DOCK_ADC2_RIGHT1);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE_I2S2_LEFT, EMU_SRC_DOCK_ADC3_LEFT1);
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_ALICE_I2S2_RIGHT, EMU_SRC_DOCK_ADC3_RIGHT1);
	snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_UNMUTE, 0x01); /* Unmute all */

	snd_emu1010_fpga_पढ़ो(emu, EMU_HANA_OPTION_CARDS, &पंचांगp);

	/* AC97 1.03, Any 32Meg of 2Gig address, Auto-Mute, EMU32 Slave,
	 * Lock Sound Memory Cache, Lock Tank Memory Cache,
	 * Mute all codecs.
	 */
	outl(0x0000a000, emu->port + HCFG);
	/* AC97 1.03, Any 32Meg of 2Gig address, Auto-Mute, EMU32 Slave,
	 * Lock Sound Memory Cache, Lock Tank Memory Cache,
	 * Un-Mute all codecs.
	 */
	outl(0x0000a001, emu->port + HCFG);

	/* Initial boot complete. Now patches */

	snd_emu1010_fpga_पढ़ो(emu, EMU_HANA_OPTION_CARDS, &पंचांगp);
	snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_MIDI_IN, 0x19); /* MIDI Route */
	snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_MIDI_OUT, 0x0c); /* Unknown */
	snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_MIDI_IN, 0x19); /* MIDI Route */
	snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_MIDI_OUT, 0x0c); /* Unknown */
	snd_emu1010_fpga_पढ़ो(emu, EMU_HANA_SPDIF_MODE, &पंचांगp);
	snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_SPDIF_MODE, 0x10); /* SPDIF Format spdअगर  (or 0x11 क्रम aes/ebu) */

#अगर 0
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_HAMOA_DAC_LEFT1, EMU_SRC_ALICE_EMU32B + 2); /* ALICE2 bus 0xa2 */
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_HAMOA_DAC_RIGHT1, EMU_SRC_ALICE_EMU32B + 3); /* ALICE2 bus 0xa3 */
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_HANA_SPDIF_LEFT1, EMU_SRC_ALICE_EMU32A + 2); /* ALICE2 bus 0xb2 */
	snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
		EMU_DST_HANA_SPDIF_RIGHT1, EMU_SRC_ALICE_EMU32A + 3); /* ALICE2 bus 0xb3 */
#पूर्ण_अगर
	/* Default outमाला_दो */
	अगर (emu->card_capabilities->emu_model == EMU_MODEL_EMU1616) अणु
		/* 1616(M) cardbus शेष outमाला_दो */
		/* ALICE2 bus 0xa0 */
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			EMU_DST_DOCK_DAC1_LEFT1, EMU_SRC_ALICE_EMU32A + 0);
		emu->emu1010.output_source[0] = 17;
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			EMU_DST_DOCK_DAC1_RIGHT1, EMU_SRC_ALICE_EMU32A + 1);
		emu->emu1010.output_source[1] = 18;
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			EMU_DST_DOCK_DAC2_LEFT1, EMU_SRC_ALICE_EMU32A + 2);
		emu->emu1010.output_source[2] = 19;
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			EMU_DST_DOCK_DAC2_RIGHT1, EMU_SRC_ALICE_EMU32A + 3);
		emu->emu1010.output_source[3] = 20;
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			EMU_DST_DOCK_DAC3_LEFT1, EMU_SRC_ALICE_EMU32A + 4);
		emu->emu1010.output_source[4] = 21;
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			EMU_DST_DOCK_DAC3_RIGHT1, EMU_SRC_ALICE_EMU32A + 5);
		emu->emu1010.output_source[5] = 22;
		/* ALICE2 bus 0xa0 */
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			EMU_DST_MANA_DAC_LEFT, EMU_SRC_ALICE_EMU32A + 0);
		emu->emu1010.output_source[16] = 17;
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			EMU_DST_MANA_DAC_RIGHT, EMU_SRC_ALICE_EMU32A + 1);
		emu->emu1010.output_source[17] = 18;
	पूर्ण अन्यथा अणु
		/* ALICE2 bus 0xa0 */
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			EMU_DST_DOCK_DAC1_LEFT1, EMU_SRC_ALICE_EMU32A + 0);
		emu->emu1010.output_source[0] = 21;
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			EMU_DST_DOCK_DAC1_RIGHT1, EMU_SRC_ALICE_EMU32A + 1);
		emu->emu1010.output_source[1] = 22;
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			EMU_DST_DOCK_DAC2_LEFT1, EMU_SRC_ALICE_EMU32A + 2);
		emu->emu1010.output_source[2] = 23;
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			EMU_DST_DOCK_DAC2_RIGHT1, EMU_SRC_ALICE_EMU32A + 3);
		emu->emu1010.output_source[3] = 24;
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			EMU_DST_DOCK_DAC3_LEFT1, EMU_SRC_ALICE_EMU32A + 4);
		emu->emu1010.output_source[4] = 25;
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			EMU_DST_DOCK_DAC3_RIGHT1, EMU_SRC_ALICE_EMU32A + 5);
		emu->emu1010.output_source[5] = 26;
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			EMU_DST_DOCK_DAC4_LEFT1, EMU_SRC_ALICE_EMU32A + 6);
		emu->emu1010.output_source[6] = 27;
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			EMU_DST_DOCK_DAC4_RIGHT1, EMU_SRC_ALICE_EMU32A + 7);
		emu->emu1010.output_source[7] = 28;
		/* ALICE2 bus 0xa0 */
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			EMU_DST_DOCK_PHONES_LEFT1, EMU_SRC_ALICE_EMU32A + 0);
		emu->emu1010.output_source[8] = 21;
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			EMU_DST_DOCK_PHONES_RIGHT1, EMU_SRC_ALICE_EMU32A + 1);
		emu->emu1010.output_source[9] = 22;
		/* ALICE2 bus 0xa0 */
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			EMU_DST_DOCK_SPDIF_LEFT1, EMU_SRC_ALICE_EMU32A + 0);
		emu->emu1010.output_source[10] = 21;
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			EMU_DST_DOCK_SPDIF_RIGHT1, EMU_SRC_ALICE_EMU32A + 1);
		emu->emu1010.output_source[11] = 22;
		/* ALICE2 bus 0xa0 */
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			EMU_DST_HANA_SPDIF_LEFT1, EMU_SRC_ALICE_EMU32A + 0);
		emu->emu1010.output_source[12] = 21;
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			EMU_DST_HANA_SPDIF_RIGHT1, EMU_SRC_ALICE_EMU32A + 1);
		emu->emu1010.output_source[13] = 22;
		/* ALICE2 bus 0xa0 */
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			EMU_DST_HAMOA_DAC_LEFT1, EMU_SRC_ALICE_EMU32A + 0);
		emu->emu1010.output_source[14] = 21;
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			EMU_DST_HAMOA_DAC_RIGHT1, EMU_SRC_ALICE_EMU32A + 1);
		emu->emu1010.output_source[15] = 22;
		/* ALICE2 bus 0xa0 */
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			EMU_DST_HANA_ADAT, EMU_SRC_ALICE_EMU32A + 0);
		emu->emu1010.output_source[16] = 21;
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			EMU_DST_HANA_ADAT + 1, EMU_SRC_ALICE_EMU32A + 1);
		emu->emu1010.output_source[17] = 22;
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			EMU_DST_HANA_ADAT + 2, EMU_SRC_ALICE_EMU32A + 2);
		emu->emu1010.output_source[18] = 23;
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			EMU_DST_HANA_ADAT + 3, EMU_SRC_ALICE_EMU32A + 3);
		emu->emu1010.output_source[19] = 24;
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			EMU_DST_HANA_ADAT + 4, EMU_SRC_ALICE_EMU32A + 4);
		emu->emu1010.output_source[20] = 25;
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			EMU_DST_HANA_ADAT + 5, EMU_SRC_ALICE_EMU32A + 5);
		emu->emu1010.output_source[21] = 26;
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			EMU_DST_HANA_ADAT + 6, EMU_SRC_ALICE_EMU32A + 6);
		emu->emu1010.output_source[22] = 27;
		snd_emu1010_fpga_link_dst_src_ग_लिखो(emu,
			EMU_DST_HANA_ADAT + 7, EMU_SRC_ALICE_EMU32A + 7);
		emu->emu1010.output_source[23] = 28;
	पूर्ण
	/* TEMP: Select SPDIF in/out */
	/* snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_OPTICAL_TYPE, 0x0); */ /* Output spdअगर */

	/* TEMP: Select 48kHz SPDIF out */
	snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_UNMUTE, 0x0); /* Mute all */
	snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_DEFCLOCK, 0x0); /* Default fallback घड़ी 48kHz */
	/* Word Clock source, Internal 48kHz x1 */
	snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_WCLOCK, EMU_HANA_WCLOCK_INT_48K);
	/* snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_WCLOCK, EMU_HANA_WCLOCK_INT_48K | EMU_HANA_WCLOCK_4X); */
	emu->emu1010.पूर्णांकernal_घड़ी = 1; /* 48000 */
	snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_DOCK_LEDS_2, 0x12); /* Set LEDs on Audio Dock */
	snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_UNMUTE, 0x1); /* Unmute all */
	/* snd_emu1010_fpga_ग_लिखो(emu, 0x7, 0x0); */ /* Mute all */
	/* snd_emu1010_fpga_ग_लिखो(emu, 0x7, 0x1); */ /* Unmute all */
	/* snd_emu1010_fpga_ग_लिखो(emu, 0xe, 0x12); */ /* Set LEDs on Audio Dock */

	वापस 0;
पूर्ण
/*
 *  Create the EMU10K1 instance
 */

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक alloc_pm_buffer(काष्ठा snd_emu10k1 *emu);
अटल व्योम मुक्त_pm_buffer(काष्ठा snd_emu10k1 *emu);
#पूर्ण_अगर

अटल पूर्णांक snd_emu10k1_मुक्त(काष्ठा snd_emu10k1 *emu)
अणु
	अगर (emu->port) अणु	/* aव्योम access to alपढ़ोy used hardware */
		snd_emu10k1_fx8010_tram_setup(emu, 0);
		snd_emu10k1_करोne(emu);
		snd_emu10k1_मुक्त_efx(emu);
	पूर्ण
	अगर (emu->card_capabilities->emu_model == EMU_MODEL_EMU1010) अणु
		/* Disable 48Volt घातer to Audio Dock */
		snd_emu1010_fpga_ग_लिखो(emu, EMU_HANA_DOCK_PWR, 0);
	पूर्ण
	cancel_delayed_work_sync(&emu->emu1010.firmware_work);
	release_firmware(emu->firmware);
	release_firmware(emu->करोck_fw);
	अगर (emu->irq >= 0)
		मुक्त_irq(emu->irq, emu);
	snd_util_memhdr_मुक्त(emu->memhdr);
	अगर (emu->silent_page.area)
		snd_dma_मुक्त_pages(&emu->silent_page);
	अगर (emu->ptb_pages.area)
		snd_dma_मुक्त_pages(&emu->ptb_pages);
	vमुक्त(emu->page_ptr_table);
	vमुक्त(emu->page_addr_table);
#अगर_घोषित CONFIG_PM_SLEEP
	मुक्त_pm_buffer(emu);
#पूर्ण_अगर
	अगर (emu->port)
		pci_release_regions(emu->pci);
	अगर (emu->card_capabilities->ca0151_chip) /* P16V */
		snd_p16v_मुक्त(emu);
	pci_disable_device(emu->pci);
	kमुक्त(emu);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_emu10k1 *emu = device->device_data;
	वापस snd_emu10k1_मुक्त(emu);
पूर्ण

अटल स्थिर काष्ठा snd_emu_chip_details emu_chip_details[] = अणु
	/* Audigy 5/Rx SB1550 */
	/* Tested by michael@gernoth.net 28 Mar 2015 */
	/* DSP: CA10300-IAT LF
	 * DAC: Cirrus Logic CS4382-KQZ
	 * ADC: Philips 1361T
	 * AC97: Sigmatel STAC9750
	 * CA0151: None
	 */
	अणु.venकरोr = 0x1102, .device = 0x0008, .subप्रणाली = 0x10241102,
	 .driver = "Audigy2", .name = "SB Audigy 5/Rx [SB1550]",
	 .id = "Audigy2",
	 .emu10k2_chip = 1,
	 .ca0108_chip = 1,
	 .spk71 = 1,
	 .adc_1361t = 1,  /* 24 bit capture instead of 16bit */
	 .ac97_chip = 1पूर्ण,
	/* Audigy4 (Not PRO) SB0610 */
	/* Tested by James@superbug.co.uk 4th April 2006 */
	/* A_IOCFG bits
	 * Output
	 * 0: ?
	 * 1: ?
	 * 2: ?
	 * 3: 0 - Digital Out, 1 - Line in
	 * 4: ?
	 * 5: ?
	 * 6: ?
	 * 7: ?
	 * Input
	 * 8: ?
	 * 9: ?
	 * A: Green jack sense (Front)
	 * B: ?
	 * C: Black jack sense (Rear/Side Right)
	 * D: Yellow jack sense (Center/LFE/Side Left)
	 * E: ?
	 * F: ?
	 *
	 * Digital Out/Line in चयन using A_IOCFG bit 3 (0x08)
	 * 0 - Digital Out
	 * 1 - Line in
	 */
	/* Mic input not tested.
	 * Analog CD input not tested
	 * Digital Out not tested.
	 * Line in working.
	 * Audio output 5.1 working. Side outमाला_दो not working.
	 */
	/* DSP: CA10300-IAT LF
	 * DAC: Cirrus Logic CS4382-KQZ
	 * ADC: Philips 1361T
	 * AC97: Sigmatel STAC9750
	 * CA0151: None
	 */
	अणु.venकरोr = 0x1102, .device = 0x0008, .subप्रणाली = 0x10211102,
	 .driver = "Audigy2", .name = "SB Audigy 4 [SB0610]",
	 .id = "Audigy2",
	 .emu10k2_chip = 1,
	 .ca0108_chip = 1,
	 .spk71 = 1,
	 .adc_1361t = 1,  /* 24 bit capture instead of 16bit */
	 .ac97_chip = 1पूर्ण ,
	/* Audigy 2 Value AC3 out करोes not work yet.
	 * Need to find out how to turn off पूर्णांकerpolators.
	 */
	/* Tested by James@superbug.co.uk 3rd July 2005 */
	/* DSP: CA0108-IAT
	 * DAC: CS4382-KQ
	 * ADC: Philips 1361T
	 * AC97: STAC9750
	 * CA0151: None
	 */
	अणु.venकरोr = 0x1102, .device = 0x0008, .subप्रणाली = 0x10011102,
	 .driver = "Audigy2", .name = "SB Audigy 2 Value [SB0400]",
	 .id = "Audigy2",
	 .emu10k2_chip = 1,
	 .ca0108_chip = 1,
	 .spk71 = 1,
	 .ac97_chip = 1पूर्ण ,
	/* Audigy 2 ZS Notebook Cardbus card.*/
	/* Tested by James@superbug.co.uk 6th November 2006 */
	/* Audio output 7.1/Headphones working.
	 * Digital output working. (AC3 not checked, only PCM)
	 * Audio Mic/Line inमाला_दो working.
	 * Digital input not tested.
	 */
	/* DSP: Tina2
	 * DAC: Wolfson WM8768/WM8568
	 * ADC: Wolfson WM8775
	 * AC97: None
	 * CA0151: None
	 */
	/* Tested by James@superbug.co.uk 4th April 2006 */
	/* A_IOCFG bits
	 * Output
	 * 0: Not Used
	 * 1: 0 = Mute all the 7.1 channel out. 1 = unmute.
	 * 2: Analog input 0 = line in, 1 = mic in
	 * 3: Not Used
	 * 4: Digital output 0 = off, 1 = on.
	 * 5: Not Used
	 * 6: Not Used
	 * 7: Not Used
	 * Input
	 *      All bits 1 (0x3fxx) means nothing plugged in.
	 * 8-9: 0 = Line in/Mic, 2 = Optical in, 3 = Nothing.
	 * A-B: 0 = Headphones, 2 = Optical out, 3 = Nothing.
	 * C-D: 2 = Front/Rear/etc, 3 = nothing.
	 * E-F: Always 0
	 *
	 */
	अणु.venकरोr = 0x1102, .device = 0x0008, .subप्रणाली = 0x20011102,
	 .driver = "Audigy2", .name = "Audigy 2 ZS Notebook [SB0530]",
	 .id = "Audigy2",
	 .emu10k2_chip = 1,
	 .ca0108_chip = 1,
	 .ca_cardbus_chip = 1,
	 .spi_dac = 1,
	 .i2c_adc = 1,
	 .spk71 = 1पूर्ण ,
	/* Tested by James@superbug.co.uk 4th Nov 2007. */
	अणु.venकरोr = 0x1102, .device = 0x0008, .subप्रणाली = 0x42011102,
	 .driver = "Audigy2", .name = "E-mu 1010 Notebook [MAEM8950]",
	 .id = "EMU1010",
	 .emu10k2_chip = 1,
	 .ca0108_chip = 1,
	 .ca_cardbus_chip = 1,
	 .spk71 = 1 ,
	 .emu_model = EMU_MODEL_EMU1616पूर्ण,
	/* Tested by James@superbug.co.uk 4th Nov 2007. */
	/* This is MAEM8960, 0202 is MAEM 8980 */
	अणु.venकरोr = 0x1102, .device = 0x0008, .subप्रणाली = 0x40041102,
	 .driver = "Audigy2", .name = "E-mu 1010b PCI [MAEM8960]",
	 .id = "EMU1010",
	 .emu10k2_chip = 1,
	 .ca0108_chip = 1,
	 .spk71 = 1,
	 .emu_model = EMU_MODEL_EMU1010Bपूर्ण, /* EMU 1010 new revision */
	/* Tested by Maxim Kachur <mcdebugger@duganet.ru> 17th Oct 2012. */
	/* This is MAEM8986, 0202 is MAEM8980 */
	अणु.venकरोr = 0x1102, .device = 0x0008, .subप्रणाली = 0x40071102,
	 .driver = "Audigy2", .name = "E-mu 1010 PCIe [MAEM8986]",
	 .id = "EMU1010",
	 .emu10k2_chip = 1,
	 .ca0108_chip = 1,
	 .spk71 = 1,
	 .emu_model = EMU_MODEL_EMU1010Bपूर्ण, /* EMU 1010 PCIe */
	/* Tested by James@superbug.co.uk 8th July 2005. */
	/* This is MAEM8810, 0202 is MAEM8820 */
	अणु.venकरोr = 0x1102, .device = 0x0004, .subप्रणाली = 0x40011102,
	 .driver = "Audigy2", .name = "E-mu 1010 [MAEM8810]",
	 .id = "EMU1010",
	 .emu10k2_chip = 1,
	 .ca0102_chip = 1,
	 .spk71 = 1,
	 .emu_model = EMU_MODEL_EMU1010पूर्ण, /* EMU 1010 old revision */
	/* EMU0404b */
	अणु.venकरोr = 0x1102, .device = 0x0008, .subप्रणाली = 0x40021102,
	 .driver = "Audigy2", .name = "E-mu 0404b PCI [MAEM8852]",
	 .id = "EMU0404",
	 .emu10k2_chip = 1,
	 .ca0108_chip = 1,
	 .spk71 = 1,
	 .emu_model = EMU_MODEL_EMU0404पूर्ण, /* EMU 0404 new revision */
	/* Tested by James@superbug.co.uk 20-3-2007. */
	अणु.venकरोr = 0x1102, .device = 0x0004, .subप्रणाली = 0x40021102,
	 .driver = "Audigy2", .name = "E-mu 0404 [MAEM8850]",
	 .id = "EMU0404",
	 .emu10k2_chip = 1,
	 .ca0102_chip = 1,
	 .spk71 = 1,
	 .emu_model = EMU_MODEL_EMU0404पूर्ण, /* EMU 0404 */
	/* EMU0404 PCIe */
	अणु.venकरोr = 0x1102, .device = 0x0008, .subप्रणाली = 0x40051102,
	 .driver = "Audigy2", .name = "E-mu 0404 PCIe [MAEM8984]",
	 .id = "EMU0404",
	 .emu10k2_chip = 1,
	 .ca0108_chip = 1,
	 .spk71 = 1,
	 .emu_model = EMU_MODEL_EMU0404पूर्ण, /* EMU 0404 PCIe ver_03 */
	/* Note that all E-mu cards require kernel 2.6 or newer. */
	अणु.venकरोr = 0x1102, .device = 0x0008,
	 .driver = "Audigy2", .name = "SB Audigy 2 Value [Unknown]",
	 .id = "Audigy2",
	 .emu10k2_chip = 1,
	 .ca0108_chip = 1,
	 .ac97_chip = 1पूर्ण ,
	/* Tested by James@superbug.co.uk 3rd July 2005 */
	अणु.venकरोr = 0x1102, .device = 0x0004, .subप्रणाली = 0x20071102,
	 .driver = "Audigy2", .name = "SB Audigy 4 PRO [SB0380]",
	 .id = "Audigy2",
	 .emu10k2_chip = 1,
	 .ca0102_chip = 1,
	 .ca0151_chip = 1,
	 .spk71 = 1,
	 .spdअगर_bug = 1,
	 .ac97_chip = 1पूर्ण ,
	/* Tested by shane-alsa@cm.nu 5th Nov 2005 */
	/* The 0x20061102 करोes have SB0350 written on it
	 * Just like 0x20021102
	 */
	अणु.venकरोr = 0x1102, .device = 0x0004, .subप्रणाली = 0x20061102,
	 .driver = "Audigy2", .name = "SB Audigy 2 [SB0350b]",
	 .id = "Audigy2",
	 .emu10k2_chip = 1,
	 .ca0102_chip = 1,
	 .ca0151_chip = 1,
	 .spk71 = 1,
	 .spdअगर_bug = 1,
	 .invert_shared_spdअगर = 1,	/* digital/analog चयन swapped */
	 .ac97_chip = 1पूर्ण ,
	/* 0x20051102 also has SB0350 written on it, treated as Audigy 2 ZS by
	   Creative's Winकरोws driver */
	अणु.venकरोr = 0x1102, .device = 0x0004, .subप्रणाली = 0x20051102,
	 .driver = "Audigy2", .name = "SB Audigy 2 ZS [SB0350a]",
	 .id = "Audigy2",
	 .emu10k2_chip = 1,
	 .ca0102_chip = 1,
	 .ca0151_chip = 1,
	 .spk71 = 1,
	 .spdअगर_bug = 1,
	 .invert_shared_spdअगर = 1,	/* digital/analog चयन swapped */
	 .ac97_chip = 1पूर्ण ,
	अणु.venकरोr = 0x1102, .device = 0x0004, .subप्रणाली = 0x20021102,
	 .driver = "Audigy2", .name = "SB Audigy 2 ZS [SB0350]",
	 .id = "Audigy2",
	 .emu10k2_chip = 1,
	 .ca0102_chip = 1,
	 .ca0151_chip = 1,
	 .spk71 = 1,
	 .spdअगर_bug = 1,
	 .invert_shared_spdअगर = 1,	/* digital/analog चयन swapped */
	 .ac97_chip = 1पूर्ण ,
	अणु.venकरोr = 0x1102, .device = 0x0004, .subप्रणाली = 0x20011102,
	 .driver = "Audigy2", .name = "SB Audigy 2 ZS [SB0360]",
	 .id = "Audigy2",
	 .emu10k2_chip = 1,
	 .ca0102_chip = 1,
	 .ca0151_chip = 1,
	 .spk71 = 1,
	 .spdअगर_bug = 1,
	 .invert_shared_spdअगर = 1,	/* digital/analog चयन swapped */
	 .ac97_chip = 1पूर्ण ,
	/* Audigy 2 */
	/* Tested by James@superbug.co.uk 3rd July 2005 */
	/* DSP: CA0102-IAT
	 * DAC: CS4382-KQ
	 * ADC: Philips 1361T
	 * AC97: STAC9721
	 * CA0151: Yes
	 */
	अणु.venकरोr = 0x1102, .device = 0x0004, .subप्रणाली = 0x10071102,
	 .driver = "Audigy2", .name = "SB Audigy 2 [SB0240]",
	 .id = "Audigy2",
	 .emu10k2_chip = 1,
	 .ca0102_chip = 1,
	 .ca0151_chip = 1,
	 .spk71 = 1,
	 .spdअगर_bug = 1,
	 .adc_1361t = 1,  /* 24 bit capture instead of 16bit */
	 .ac97_chip = 1पूर्ण ,
	अणु.venकरोr = 0x1102, .device = 0x0004, .subप्रणाली = 0x10051102,
	 .driver = "Audigy2", .name = "Audigy 2 Platinum EX [SB0280]",
	 .id = "Audigy2",
	 .emu10k2_chip = 1,
	 .ca0102_chip = 1,
	 .ca0151_chip = 1,
	 .spk71 = 1,
	 .spdअगर_bug = 1पूर्ण ,
	/* Dell OEM/Creative Lअसल Audigy 2 ZS */
	/* See ALSA bug#1365 */
	अणु.venकरोr = 0x1102, .device = 0x0004, .subप्रणाली = 0x10031102,
	 .driver = "Audigy2", .name = "SB Audigy 2 ZS [SB0353]",
	 .id = "Audigy2",
	 .emu10k2_chip = 1,
	 .ca0102_chip = 1,
	 .ca0151_chip = 1,
	 .spk71 = 1,
	 .spdअगर_bug = 1,
	 .invert_shared_spdअगर = 1,	/* digital/analog चयन swapped */
	 .ac97_chip = 1पूर्ण ,
	अणु.venकरोr = 0x1102, .device = 0x0004, .subप्रणाली = 0x10021102,
	 .driver = "Audigy2", .name = "SB Audigy 2 Platinum [SB0240P]",
	 .id = "Audigy2",
	 .emu10k2_chip = 1,
	 .ca0102_chip = 1,
	 .ca0151_chip = 1,
	 .spk71 = 1,
	 .spdअगर_bug = 1,
	 .invert_shared_spdअगर = 1,	/* digital/analog चयन swapped */
	 .adc_1361t = 1,  /* 24 bit capture instead of 16bit. Fixes ALSA bug#324 */
	 .ac97_chip = 1पूर्ण ,
	अणु.venकरोr = 0x1102, .device = 0x0004, .revision = 0x04,
	 .driver = "Audigy2", .name = "SB Audigy 2 [Unknown]",
	 .id = "Audigy2",
	 .emu10k2_chip = 1,
	 .ca0102_chip = 1,
	 .ca0151_chip = 1,
	 .spdअगर_bug = 1,
	 .ac97_chip = 1पूर्ण ,
	अणु.venकरोr = 0x1102, .device = 0x0004, .subप्रणाली = 0x00531102,
	 .driver = "Audigy", .name = "SB Audigy 1 [SB0092]",
	 .id = "Audigy",
	 .emu10k2_chip = 1,
	 .ca0102_chip = 1,
	 .ac97_chip = 1पूर्ण ,
	अणु.venकरोr = 0x1102, .device = 0x0004, .subप्रणाली = 0x00521102,
	 .driver = "Audigy", .name = "SB Audigy 1 ES [SB0160]",
	 .id = "Audigy",
	 .emu10k2_chip = 1,
	 .ca0102_chip = 1,
	 .spdअगर_bug = 1,
	 .ac97_chip = 1पूर्ण ,
	अणु.venकरोr = 0x1102, .device = 0x0004, .subप्रणाली = 0x00511102,
	 .driver = "Audigy", .name = "SB Audigy 1 [SB0090]",
	 .id = "Audigy",
	 .emu10k2_chip = 1,
	 .ca0102_chip = 1,
	 .ac97_chip = 1पूर्ण ,
	अणु.venकरोr = 0x1102, .device = 0x0004,
	 .driver = "Audigy", .name = "Audigy 1 [Unknown]",
	 .id = "Audigy",
	 .emu10k2_chip = 1,
	 .ca0102_chip = 1,
	 .ac97_chip = 1पूर्ण ,
	अणु.venकरोr = 0x1102, .device = 0x0002, .subप्रणाली = 0x100a1102,
	 .driver = "EMU10K1", .name = "SB Live! 5.1 [SB0220]",
	 .id = "Live",
	 .emu10k1_chip = 1,
	 .ac97_chip = 1,
	 .sblive51 = 1पूर्ण ,
	अणु.venकरोr = 0x1102, .device = 0x0002, .subप्रणाली = 0x806b1102,
	 .driver = "EMU10K1", .name = "SB Live! [SB0105]",
	 .id = "Live",
	 .emu10k1_chip = 1,
	 .ac97_chip = 1,
	 .sblive51 = 1पूर्ण ,
	अणु.venकरोr = 0x1102, .device = 0x0002, .subप्रणाली = 0x806a1102,
	 .driver = "EMU10K1", .name = "SB Live! Value [SB0103]",
	 .id = "Live",
	 .emu10k1_chip = 1,
	 .ac97_chip = 1,
	 .sblive51 = 1पूर्ण ,
	अणु.venकरोr = 0x1102, .device = 0x0002, .subप्रणाली = 0x80691102,
	 .driver = "EMU10K1", .name = "SB Live! Value [SB0101]",
	 .id = "Live",
	 .emu10k1_chip = 1,
	 .ac97_chip = 1,
	 .sblive51 = 1पूर्ण ,
	/* Tested by ALSA bug#1680 26th December 2005 */
	/* note: It really has SB0220 written on the card, */
	/* but it's SB0228 according to kx.inf */
	अणु.venकरोr = 0x1102, .device = 0x0002, .subप्रणाली = 0x80661102,
	 .driver = "EMU10K1", .name = "SB Live! 5.1 Dell OEM [SB0228]",
	 .id = "Live",
	 .emu10k1_chip = 1,
	 .ac97_chip = 1,
	 .sblive51 = 1पूर्ण ,
	/* Tested by Thomas Zehetbauer 27th Aug 2005 */
	अणु.venकरोr = 0x1102, .device = 0x0002, .subप्रणाली = 0x80651102,
	 .driver = "EMU10K1", .name = "SB Live! 5.1 [SB0220]",
	 .id = "Live",
	 .emu10k1_chip = 1,
	 .ac97_chip = 1,
	 .sblive51 = 1पूर्ण ,
	अणु.venकरोr = 0x1102, .device = 0x0002, .subप्रणाली = 0x80641102,
	 .driver = "EMU10K1", .name = "SB Live! 5.1",
	 .id = "Live",
	 .emu10k1_chip = 1,
	 .ac97_chip = 1,
	 .sblive51 = 1पूर्ण ,
	/* Tested by alsa bugtrack user "hus" bug #1297 12th Aug 2005 */
	अणु.venकरोr = 0x1102, .device = 0x0002, .subप्रणाली = 0x80611102,
	 .driver = "EMU10K1", .name = "SB Live! 5.1 [SB0060]",
	 .id = "Live",
	 .emu10k1_chip = 1,
	 .ac97_chip = 2, /* ac97 is optional; both SBLive 5.1 and platinum
			  * share the same IDs!
			  */
	 .sblive51 = 1पूर्ण ,
	अणु.venकरोr = 0x1102, .device = 0x0002, .subप्रणाली = 0x80511102,
	 .driver = "EMU10K1", .name = "SB Live! Value [CT4850]",
	 .id = "Live",
	 .emu10k1_chip = 1,
	 .ac97_chip = 1,
	 .sblive51 = 1पूर्ण ,
	अणु.venकरोr = 0x1102, .device = 0x0002, .subप्रणाली = 0x80401102,
	 .driver = "EMU10K1", .name = "SB Live! Platinum [CT4760P]",
	 .id = "Live",
	 .emu10k1_chip = 1,
	 .ac97_chip = 1पूर्ण ,
	अणु.venकरोr = 0x1102, .device = 0x0002, .subप्रणाली = 0x80321102,
	 .driver = "EMU10K1", .name = "SB Live! Value [CT4871]",
	 .id = "Live",
	 .emu10k1_chip = 1,
	 .ac97_chip = 1,
	 .sblive51 = 1पूर्ण ,
	अणु.venकरोr = 0x1102, .device = 0x0002, .subप्रणाली = 0x80311102,
	 .driver = "EMU10K1", .name = "SB Live! Value [CT4831]",
	 .id = "Live",
	 .emu10k1_chip = 1,
	 .ac97_chip = 1,
	 .sblive51 = 1पूर्ण ,
	अणु.venकरोr = 0x1102, .device = 0x0002, .subप्रणाली = 0x80281102,
	 .driver = "EMU10K1", .name = "SB Live! Value [CT4870]",
	 .id = "Live",
	 .emu10k1_chip = 1,
	 .ac97_chip = 1,
	 .sblive51 = 1पूर्ण ,
	/* Tested by James@superbug.co.uk 3rd July 2005 */
	अणु.venकरोr = 0x1102, .device = 0x0002, .subप्रणाली = 0x80271102,
	 .driver = "EMU10K1", .name = "SB Live! Value [CT4832]",
	 .id = "Live",
	 .emu10k1_chip = 1,
	 .ac97_chip = 1,
	 .sblive51 = 1पूर्ण ,
	अणु.venकरोr = 0x1102, .device = 0x0002, .subप्रणाली = 0x80261102,
	 .driver = "EMU10K1", .name = "SB Live! Value [CT4830]",
	 .id = "Live",
	 .emu10k1_chip = 1,
	 .ac97_chip = 1,
	 .sblive51 = 1पूर्ण ,
	अणु.venकरोr = 0x1102, .device = 0x0002, .subप्रणाली = 0x80231102,
	 .driver = "EMU10K1", .name = "SB PCI512 [CT4790]",
	 .id = "Live",
	 .emu10k1_chip = 1,
	 .ac97_chip = 1,
	 .sblive51 = 1पूर्ण ,
	अणु.venकरोr = 0x1102, .device = 0x0002, .subप्रणाली = 0x80221102,
	 .driver = "EMU10K1", .name = "SB Live! Value [CT4780]",
	 .id = "Live",
	 .emu10k1_chip = 1,
	 .ac97_chip = 1,
	 .sblive51 = 1पूर्ण ,
	अणु.venकरोr = 0x1102, .device = 0x0002, .subप्रणाली = 0x40011102,
	 .driver = "EMU10K1", .name = "E-mu APS [PC545]",
	 .id = "APS",
	 .emu10k1_chip = 1,
	 .ecard = 1पूर्ण ,
	अणु.venकरोr = 0x1102, .device = 0x0002, .subप्रणाली = 0x00211102,
	 .driver = "EMU10K1", .name = "SB Live! [CT4620]",
	 .id = "Live",
	 .emu10k1_chip = 1,
	 .ac97_chip = 1,
	 .sblive51 = 1पूर्ण ,
	अणु.venकरोr = 0x1102, .device = 0x0002, .subप्रणाली = 0x00201102,
	 .driver = "EMU10K1", .name = "SB Live! Value [CT4670]",
	 .id = "Live",
	 .emu10k1_chip = 1,
	 .ac97_chip = 1,
	 .sblive51 = 1पूर्ण ,
	अणु.venकरोr = 0x1102, .device = 0x0002,
	 .driver = "EMU10K1", .name = "SB Live! [Unknown]",
	 .id = "Live",
	 .emu10k1_chip = 1,
	 .ac97_chip = 1,
	 .sblive51 = 1पूर्ण ,
	अणु पूर्ण /* terminator */
पूर्ण;

/*
 * The chip (at least the Audigy 2 CA0102 chip, but most likely others, too)
 * has a problem that from समय to समय it likes to करो few DMA पढ़ोs a bit
 * beyond its normal allocation and माला_लो very confused अगर these पढ़ोs get
 * blocked by a IOMMU.
 *
 * This behaviour has been observed क्रम the first (reserved) page
 * (क्रम which it happens multiple बार at every playback), often क्रम various
 * synth pages and someबार क्रम PCM playback buffers and the page table
 * memory itself.
 *
 * As a workaround let's widen these DMA allocations by an extra page अगर we
 * detect that the device is behind a non-passthrough IOMMU.
 */
अटल व्योम snd_emu10k1_detect_iommu(काष्ठा snd_emu10k1 *emu)
अणु
	काष्ठा iommu_करोमुख्य *करोमुख्य;

	emu->iommu_workaround = false;

	अगर (!iommu_present(emu->card->dev->bus))
		वापस;

	करोमुख्य = iommu_get_करोमुख्य_क्रम_dev(emu->card->dev);
	अगर (करोमुख्य && करोमुख्य->type == IOMMU_DOMAIN_IDENTITY)
		वापस;

	dev_notice(emu->card->dev,
		   "non-passthrough IOMMU detected, widening DMA allocations");
	emu->iommu_workaround = true;
पूर्ण

पूर्णांक snd_emu10k1_create(काष्ठा snd_card *card,
		       काष्ठा pci_dev *pci,
		       अचिन्हित लघु extin_mask,
		       अचिन्हित लघु extout_mask,
		       दीर्घ max_cache_bytes,
		       पूर्णांक enable_ir,
		       uपूर्णांक subप्रणाली,
		       काष्ठा snd_emu10k1 **remu)
अणु
	काष्ठा snd_emu10k1 *emu;
	पूर्णांक idx, err;
	पूर्णांक is_audigy;
	माप_प्रकार page_table_size;
	__le32 *pgtbl;
	अचिन्हित पूर्णांक silent_page;
	स्थिर काष्ठा snd_emu_chip_details *c;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_emu10k1_dev_मुक्त,
	पूर्ण;

	*remu = शून्य;

	/* enable PCI device */
	err = pci_enable_device(pci);
	अगर (err < 0)
		वापस err;

	emu = kzalloc(माप(*emu), GFP_KERNEL);
	अगर (emu == शून्य) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण
	emu->card = card;
	spin_lock_init(&emu->reg_lock);
	spin_lock_init(&emu->emu_lock);
	spin_lock_init(&emu->spi_lock);
	spin_lock_init(&emu->i2c_lock);
	spin_lock_init(&emu->voice_lock);
	spin_lock_init(&emu->synth_lock);
	spin_lock_init(&emu->memblk_lock);
	mutex_init(&emu->fx8010.lock);
	INIT_LIST_HEAD(&emu->mapped_link_head);
	INIT_LIST_HEAD(&emu->mapped_order_link_head);
	emu->pci = pci;
	emu->irq = -1;
	emu->synth = शून्य;
	emu->get_synth_voice = शून्य;
	INIT_DELAYED_WORK(&emu->emu1010.firmware_work, emu1010_firmware_work);
	/* पढ़ो revision & serial */
	emu->revision = pci->revision;
	pci_पढ़ो_config_dword(pci, PCI_SUBSYSTEM_VENDOR_ID, &emu->serial);
	pci_पढ़ो_config_word(pci, PCI_SUBSYSTEM_ID, &emu->model);
	dev_dbg(card->dev,
		"vendor = 0x%x, device = 0x%x, subsystem_vendor_id = 0x%x, subsystem_id = 0x%x\n",
		pci->venकरोr, pci->device, emu->serial, emu->model);

	क्रम (c = emu_chip_details; c->venकरोr; c++) अणु
		अगर (c->venकरोr == pci->venकरोr && c->device == pci->device) अणु
			अगर (subप्रणाली) अणु
				अगर (c->subप्रणाली && (c->subप्रणाली == subप्रणाली))
					अवरोध;
				अन्यथा
					जारी;
			पूर्ण अन्यथा अणु
				अगर (c->subप्रणाली && (c->subप्रणाली != emu->serial))
					जारी;
				अगर (c->revision && c->revision != emu->revision)
					जारी;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (c->venकरोr == 0) अणु
		dev_err(card->dev, "emu10k1: Card not recognised\n");
		kमुक्त(emu);
		pci_disable_device(pci);
		वापस -ENOENT;
	पूर्ण
	emu->card_capabilities = c;
	अगर (c->subप्रणाली && !subप्रणाली)
		dev_dbg(card->dev, "Sound card name = %s\n", c->name);
	अन्यथा अगर (subप्रणाली)
		dev_dbg(card->dev, "Sound card name = %s, "
			"vendor = 0x%x, device = 0x%x, subsystem = 0x%x. "
			"Forced to subsystem = 0x%x\n",	c->name,
			pci->venकरोr, pci->device, emu->serial, c->subप्रणाली);
	अन्यथा
		dev_dbg(card->dev, "Sound card name = %s, "
			"vendor = 0x%x, device = 0x%x, subsystem = 0x%x.\n",
			c->name, pci->venकरोr, pci->device,
			emu->serial);

	अगर (!*card->id && c->id)
		strscpy(card->id, c->id, माप(card->id));

	is_audigy = emu->audigy = c->emu10k2_chip;

	snd_emu10k1_detect_iommu(emu);

	/* set addressing mode */
	emu->address_mode = is_audigy ? 0 : 1;
	/* set the DMA transfer mask */
	emu->dma_mask = emu->address_mode ? EMU10K1_DMA_MASK : AUDIGY_DMA_MASK;
	अगर (dma_set_mask_and_coherent(&pci->dev, emu->dma_mask) < 0) अणु
		dev_err(card->dev,
			"architecture does not support PCI busmaster DMA with mask 0x%lx\n",
			emu->dma_mask);
		kमुक्त(emu);
		pci_disable_device(pci);
		वापस -ENXIO;
	पूर्ण
	अगर (is_audigy)
		emu->gpr_base = A_FXGPREGBASE;
	अन्यथा
		emu->gpr_base = FXGPREGBASE;

	err = pci_request_regions(pci, "EMU10K1");
	अगर (err < 0) अणु
		kमुक्त(emu);
		pci_disable_device(pci);
		वापस err;
	पूर्ण
	emu->port = pci_resource_start(pci, 0);

	emu->max_cache_pages = max_cache_bytes >> PAGE_SHIFT;

	page_table_size = माप(u32) * (emu->address_mode ? MAXPAGES1 :
					 MAXPAGES0);
	अगर (snd_emu10k1_alloc_pages_maybe_wider(emu, page_table_size,
						&emu->ptb_pages) < 0) अणु
		err = -ENOMEM;
		जाओ error;
	पूर्ण
	dev_dbg(card->dev, "page table address range is %.8lx:%.8lx\n",
		(अचिन्हित दीर्घ)emu->ptb_pages.addr,
		(अचिन्हित दीर्घ)(emu->ptb_pages.addr + emu->ptb_pages.bytes));

	emu->page_ptr_table = vदो_स्मृति(array_size(माप(व्योम *),
						 emu->max_cache_pages));
	emu->page_addr_table = vदो_स्मृति(array_size(माप(अचिन्हित दीर्घ),
						  emu->max_cache_pages));
	अगर (emu->page_ptr_table == शून्य || emu->page_addr_table == शून्य) अणु
		err = -ENOMEM;
		जाओ error;
	पूर्ण

	अगर (snd_emu10k1_alloc_pages_maybe_wider(emu, EMUPAGESIZE,
						&emu->silent_page) < 0) अणु
		err = -ENOMEM;
		जाओ error;
	पूर्ण
	dev_dbg(card->dev, "silent page range is %.8lx:%.8lx\n",
		(अचिन्हित दीर्घ)emu->silent_page.addr,
		(अचिन्हित दीर्घ)(emu->silent_page.addr +
				emu->silent_page.bytes));

	emu->memhdr = snd_util_memhdr_new(emu->max_cache_pages * PAGE_SIZE);
	अगर (emu->memhdr == शून्य) अणु
		err = -ENOMEM;
		जाओ error;
	पूर्ण
	emu->memhdr->block_extra_size = माप(काष्ठा snd_emu10k1_memblk) -
		माप(काष्ठा snd_util_memblk);

	pci_set_master(pci);

	emu->fx8010.fxbus_mask = 0x303f;
	अगर (extin_mask == 0)
		extin_mask = 0x3fcf;
	अगर (extout_mask == 0)
		extout_mask = 0x7fff;
	emu->fx8010.extin_mask = extin_mask;
	emu->fx8010.extout_mask = extout_mask;
	emu->enable_ir = enable_ir;

	अगर (emu->card_capabilities->ca_cardbus_chip) अणु
		err = snd_emu10k1_cardbus_init(emu);
		अगर (err < 0)
			जाओ error;
	पूर्ण
	अगर (emu->card_capabilities->ecard) अणु
		err = snd_emu10k1_ecard_init(emu);
		अगर (err < 0)
			जाओ error;
	पूर्ण अन्यथा अगर (emu->card_capabilities->emu_model) अणु
		err = snd_emu10k1_emu1010_init(emu);
		अगर (err < 0) अणु
			snd_emu10k1_मुक्त(emu);
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* 5.1: Enable the additional AC97 Slots. If the emu10k1 version
			करोes not support this, it shouldn't करो any harm */
		snd_emu10k1_ptr_ग_लिखो(emu, AC97SLOT, 0,
					AC97SLOT_CNTR|AC97SLOT_LFE);
	पूर्ण

	/* initialize TRAM setup */
	emu->fx8010.itram_size = (16 * 1024)/2;
	emu->fx8010.etram_pages.area = शून्य;
	emu->fx8010.etram_pages.bytes = 0;

	/* irq handler must be रेजिस्टरed after I/O ports are activated */
	अगर (request_irq(pci->irq, snd_emu10k1_पूर्णांकerrupt, IRQF_SHARED,
			KBUILD_MODNAME, emu)) अणु
		err = -EBUSY;
		जाओ error;
	पूर्ण
	emu->irq = pci->irq;
	card->sync_irq = emu->irq;

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
	emu->spdअगर_bits[0] = emu->spdअगर_bits[1] =
		emu->spdअगर_bits[2] = SPCS_CLKACCY_1000PPM | SPCS_SAMPLERATE_48 |
		SPCS_CHANNELNUM_LEFT | SPCS_SOURCENUM_UNSPEC |
		SPCS_GENERATIONSTATUS | 0x00001200 |
		0x00000000 | SPCS_EMPHASIS_NONE | SPCS_COPYRIGHT;

	/* Clear silent pages and set up poपूर्णांकers */
	स_रखो(emu->silent_page.area, 0, emu->silent_page.bytes);
	silent_page = emu->silent_page.addr << emu->address_mode;
	pgtbl = (__le32 *)emu->ptb_pages.area;
	क्रम (idx = 0; idx < (emu->address_mode ? MAXPAGES1 : MAXPAGES0); idx++)
		pgtbl[idx] = cpu_to_le32(silent_page | idx);

	/* set up voice indices */
	क्रम (idx = 0; idx < NUM_G; idx++) अणु
		emu->voices[idx].emu = emu;
		emu->voices[idx].number = idx;
	पूर्ण

	err = snd_emu10k1_init(emu, enable_ir, 0);
	अगर (err < 0)
		जाओ error;
#अगर_घोषित CONFIG_PM_SLEEP
	err = alloc_pm_buffer(emu);
	अगर (err < 0)
		जाओ error;
#पूर्ण_अगर

	/*  Initialize the effect engine */
	err = snd_emu10k1_init_efx(emu);
	अगर (err < 0)
		जाओ error;
	snd_emu10k1_audio_enable(emu);

	err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, emu, &ops);
	अगर (err < 0)
		जाओ error;

#अगर_घोषित CONFIG_SND_PROC_FS
	snd_emu10k1_proc_init(emu);
#पूर्ण_अगर

	*remu = emu;
	वापस 0;

 error:
	snd_emu10k1_मुक्त(emu);
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल स्थिर अचिन्हित अक्षर saved_regs[] = अणु
	CPF, PTRX, CVCF, VTFT, Z1, Z2, PSST, DSL, CCCA, CCR, CLP,
	FXRT, MAPA, MAPB, ENVVOL, ATKHLDV, DCYSUSV, LFOVAL1, ENVVAL,
	ATKHLDM, DCYSUSM, LFOVAL2, IP, IFATN, PEFE, FMMOD, TREMFRQ, FM2FRQ2,
	TEMPENV, ADCCR, FXWC, MICBA, ADCBA, FXBA,
	MICBS, ADCBS, FXBS, CDCS, GPSCS, SPCS0, SPCS1, SPCS2,
	SPBYPASS, AC97SLOT, CDSRCS, GPSRCS, ZVSRCS, MICIDX, ADCIDX, FXIDX,
	0xff /* end */
पूर्ण;
अटल स्थिर अचिन्हित अक्षर saved_regs_audigy[] = अणु
	A_ADCIDX, A_MICIDX, A_FXWC1, A_FXWC2, A_SAMPLE_RATE,
	A_FXRT2, A_SENDAMOUNTS, A_FXRT1,
	0xff /* end */
पूर्ण;

अटल पूर्णांक alloc_pm_buffer(काष्ठा snd_emu10k1 *emu)
अणु
	पूर्णांक size;

	size = ARRAY_SIZE(saved_regs);
	अगर (emu->audigy)
		size += ARRAY_SIZE(saved_regs_audigy);
	emu->saved_ptr = vदो_स्मृति(array3_size(4, NUM_G, size));
	अगर (!emu->saved_ptr)
		वापस -ENOMEM;
	अगर (snd_emu10k1_efx_alloc_pm_buffer(emu) < 0)
		वापस -ENOMEM;
	अगर (emu->card_capabilities->ca0151_chip &&
	    snd_p16v_alloc_pm_buffer(emu) < 0)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम मुक्त_pm_buffer(काष्ठा snd_emu10k1 *emu)
अणु
	vमुक्त(emu->saved_ptr);
	snd_emu10k1_efx_मुक्त_pm_buffer(emu);
	अगर (emu->card_capabilities->ca0151_chip)
		snd_p16v_मुक्त_pm_buffer(emu);
पूर्ण

व्योम snd_emu10k1_suspend_regs(काष्ठा snd_emu10k1 *emu)
अणु
	पूर्णांक i;
	स्थिर अचिन्हित अक्षर *reg;
	अचिन्हित पूर्णांक *val;

	val = emu->saved_ptr;
	क्रम (reg = saved_regs; *reg != 0xff; reg++)
		क्रम (i = 0; i < NUM_G; i++, val++)
			*val = snd_emu10k1_ptr_पढ़ो(emu, *reg, i);
	अगर (emu->audigy) अणु
		क्रम (reg = saved_regs_audigy; *reg != 0xff; reg++)
			क्रम (i = 0; i < NUM_G; i++, val++)
				*val = snd_emu10k1_ptr_पढ़ो(emu, *reg, i);
	पूर्ण
	अगर (emu->audigy)
		emu->saved_a_iocfg = inl(emu->port + A_IOCFG);
	emu->saved_hcfg = inl(emu->port + HCFG);
पूर्ण

व्योम snd_emu10k1_resume_init(काष्ठा snd_emu10k1 *emu)
अणु
	अगर (emu->card_capabilities->ca_cardbus_chip)
		snd_emu10k1_cardbus_init(emu);
	अगर (emu->card_capabilities->ecard)
		snd_emu10k1_ecard_init(emu);
	अन्यथा अगर (emu->card_capabilities->emu_model)
		snd_emu10k1_emu1010_init(emu);
	अन्यथा
		snd_emu10k1_ptr_ग_लिखो(emu, AC97SLOT, 0, AC97SLOT_CNTR|AC97SLOT_LFE);
	snd_emu10k1_init(emu, emu->enable_ir, 1);
पूर्ण

व्योम snd_emu10k1_resume_regs(काष्ठा snd_emu10k1 *emu)
अणु
	पूर्णांक i;
	स्थिर अचिन्हित अक्षर *reg;
	अचिन्हित पूर्णांक *val;

	snd_emu10k1_audio_enable(emu);

	/* resore क्रम spdअगर */
	अगर (emu->audigy)
		outl(emu->saved_a_iocfg, emu->port + A_IOCFG);
	outl(emu->saved_hcfg, emu->port + HCFG);

	val = emu->saved_ptr;
	क्रम (reg = saved_regs; *reg != 0xff; reg++)
		क्रम (i = 0; i < NUM_G; i++, val++)
			snd_emu10k1_ptr_ग_लिखो(emu, *reg, i, *val);
	अगर (emu->audigy) अणु
		क्रम (reg = saved_regs_audigy; *reg != 0xff; reg++)
			क्रम (i = 0; i < NUM_G; i++, val++)
				snd_emu10k1_ptr_ग_लिखो(emu, *reg, i, *val);
	पूर्ण
पूर्ण
#पूर्ण_अगर
