<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*********************************************************************
 *
 * Linux multisound pinnacle/fiji driver क्रम ALSA.
 *
 * 2002/06/30 Karsten Wiese:
 *	क्रम now this is only used to build a pinnacle / fiji driver.
 *	the OSS parent of this code is deचिन्हित to also support
 *	the multisound classic via the file msnd_classic.c.
 *	to make it easier क्रम some brave heart to implemt classic
 *	support in alsa, i left all the MSND_CLASSIC tokens in this file.
 *	but क्रम now this untested & unकरोne.
 *
 * ripped from linux kernel 2.4.18 by Karsten Wiese.
 *
 * the following is a copy of the 2.4.18 OSS FREE file-heading comment:
 *
 * Turtle Beach MultiSound Sound Card Driver क्रम Linux
 * msnd_pinnacle.c / msnd_classic.c
 *
 * -- If MSND_CLASSIC is defined:
 *
 *     -> driver क्रम Turtle Beach Classic/Monterey/Tahiti
 *
 * -- Else
 *
 *     -> driver क्रम Turtle Beach Pinnacle/Fiji
 *
 * 12-3-2000  Modअगरied IO port validation  Steve Sycamore
 *
 * Copyright (C) 1998 Andrew Veliath
 *
 ********************************************************************/

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/firmware.h>
#समावेश <linux/isa.h>
#समावेश <linux/isapnp.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>

#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/asound.h>
#समावेश <sound/pcm.h>
#समावेश <sound/mpu401.h>

#अगर_घोषित MSND_CLASSIC
# अगरndef __alpha__
#  define SLOWIO
# endअगर
#पूर्ण_अगर
#समावेश "msnd.h"
#अगर_घोषित MSND_CLASSIC
#  include "msnd_classic.h"
#  define LOGNAME			"msnd_classic"
#  define DEV_NAME			"msnd-classic"
#अन्यथा
#  include "msnd_pinnacle.h"
#  define LOGNAME			"snd_msnd_pinnacle"
#  define DEV_NAME			"msnd-pinnacle"
#पूर्ण_अगर

अटल व्योम set_शेष_audio_parameters(काष्ठा snd_msnd *chip)
अणु
	chip->play_sample_size = snd_pcm_क्रमmat_width(DEFSAMPLESIZE);
	chip->play_sample_rate = DEFSAMPLERATE;
	chip->play_channels = DEFCHANNELS;
	chip->capture_sample_size = snd_pcm_क्रमmat_width(DEFSAMPLESIZE);
	chip->capture_sample_rate = DEFSAMPLERATE;
	chip->capture_channels = DEFCHANNELS;
पूर्ण

अटल व्योम snd_msnd_eval_dsp_msg(काष्ठा snd_msnd *chip, u16 wMessage)
अणु
	चयन (HIBYTE(wMessage)) अणु
	हाल HIMT_PLAY_DONE: अणु
		अगर (chip->banksPlayed < 3)
			snd_prपूर्णांकdd("%08X: HIMT_PLAY_DONE: %i\n",
				(अचिन्हित)jअगरfies, LOBYTE(wMessage));

		अगर (chip->last_playbank == LOBYTE(wMessage)) अणु
			snd_prपूर्णांकdd("chip.last_playbank == LOBYTE(wMessage)\n");
			अवरोध;
		पूर्ण
		chip->banksPlayed++;

		अगर (test_bit(F_WRITING, &chip->flags))
			snd_msnd_DAPQ(chip, 0);

		chip->last_playbank = LOBYTE(wMessage);
		chip->playDMAPos += chip->play_period_bytes;
		अगर (chip->playDMAPos > chip->playLimit)
			chip->playDMAPos = 0;
		snd_pcm_period_elapsed(chip->playback_substream);

		अवरोध;
	पूर्ण
	हाल HIMT_RECORD_DONE:
		अगर (chip->last_recbank == LOBYTE(wMessage))
			अवरोध;
		chip->last_recbank = LOBYTE(wMessage);
		chip->captureDMAPos += chip->capturePeriodBytes;
		अगर (chip->captureDMAPos > (chip->captureLimit))
			chip->captureDMAPos = 0;

		अगर (test_bit(F_READING, &chip->flags))
			snd_msnd_DARQ(chip, chip->last_recbank);

		snd_pcm_period_elapsed(chip->capture_substream);
		अवरोध;

	हाल HIMT_DSP:
		चयन (LOBYTE(wMessage)) अणु
#अगर_अघोषित MSND_CLASSIC
		हाल HIDSP_PLAY_UNDER:
#पूर्ण_अगर
		हाल HIDSP_INT_PLAY_UNDER:
			snd_prपूर्णांकd(KERN_WARNING LOGNAME ": Play underflow %i\n",
				chip->banksPlayed);
			अगर (chip->banksPlayed > 2)
				clear_bit(F_WRITING, &chip->flags);
			अवरोध;

		हाल HIDSP_INT_RECORD_OVER:
			snd_prपूर्णांकd(KERN_WARNING LOGNAME ": Record overflow\n");
			clear_bit(F_READING, &chip->flags);
			अवरोध;

		शेष:
			snd_prपूर्णांकd(KERN_WARNING LOGNAME
				   ": DSP message %d 0x%02x\n",
				   LOBYTE(wMessage), LOBYTE(wMessage));
			अवरोध;
		पूर्ण
		अवरोध;

	हाल HIMT_MIDI_IN_UCHAR:
		अगर (chip->msndmidi_mpu)
			snd_msndmidi_input_पढ़ो(chip->msndmidi_mpu);
		अवरोध;

	शेष:
		snd_prपूर्णांकd(KERN_WARNING LOGNAME ": HIMT message %d 0x%02x\n",
			   HIBYTE(wMessage), HIBYTE(wMessage));
		अवरोध;
	पूर्ण
पूर्ण

अटल irqवापस_t snd_msnd_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_msnd *chip = dev_id;
	व्योम __iomem *pwDSPQData = chip->mappedbase + DSPQ_DATA_BUFF;
	u16 head, tail, size;

	/* Send ack to DSP */
	/* inb(chip->io + HP_RXL); */

	/* Evaluate queued DSP messages */
	head = पढ़ोw(chip->DSPQ + JQS_wHead);
	tail = पढ़ोw(chip->DSPQ + JQS_wTail);
	size = पढ़ोw(chip->DSPQ + JQS_wSize);
	अगर (head > size || tail > size)
		जाओ out;
	जबतक (head != tail) अणु
		snd_msnd_eval_dsp_msg(chip, पढ़ोw(pwDSPQData + 2 * head));
		अगर (++head > size)
			head = 0;
		ग_लिखोw(head, chip->DSPQ + JQS_wHead);
	पूर्ण
 out:
	/* Send ack to DSP */
	inb(chip->io + HP_RXL);
	वापस IRQ_HANDLED;
पूर्ण


अटल पूर्णांक snd_msnd_reset_dsp(दीर्घ io, अचिन्हित अक्षर *info)
अणु
	पूर्णांक समयout = 100;

	outb(HPDSPRESET_ON, io + HP_DSPR);
	msleep(1);
#अगर_अघोषित MSND_CLASSIC
	अगर (info)
		*info = inb(io + HP_INFO);
#पूर्ण_अगर
	outb(HPDSPRESET_OFF, io + HP_DSPR);
	msleep(1);
	जबतक (समयout-- > 0) अणु
		अगर (inb(io + HP_CVR) == HP_CVR_DEF)
			वापस 0;
		msleep(1);
	पूर्ण
	snd_prपूर्णांकk(KERN_ERR LOGNAME ": Cannot reset DSP\n");

	वापस -EIO;
पूर्ण

अटल पूर्णांक snd_msnd_probe(काष्ठा snd_card *card)
अणु
	काष्ठा snd_msnd *chip = card->निजी_data;
	अचिन्हित अक्षर info;
#अगर_अघोषित MSND_CLASSIC
	अक्षर *xv, *rev = शून्य;
	अक्षर *pin = "TB Pinnacle", *fiji = "TB Fiji";
	अक्षर *pinfiji = "TB Pinnacle/Fiji";
#पूर्ण_अगर

	अगर (!request_region(chip->io, DSP_NUMIO, "probing")) अणु
		snd_prपूर्णांकk(KERN_ERR LOGNAME ": I/O port conflict\n");
		वापस -ENODEV;
	पूर्ण

	अगर (snd_msnd_reset_dsp(chip->io, &info) < 0) अणु
		release_region(chip->io, DSP_NUMIO);
		वापस -ENODEV;
	पूर्ण

#अगर_घोषित MSND_CLASSIC
	म_नकल(card->लघुname, "Classic/Tahiti/Monterey");
	म_नकल(card->दीर्घname, "Turtle Beach Multisound");
	prपूर्णांकk(KERN_INFO LOGNAME ": %s, "
	       "I/O 0x%lx-0x%lx, IRQ %d, memory mapped to 0x%lX-0x%lX\n",
	       card->लघुname,
	       chip->io, chip->io + DSP_NUMIO - 1,
	       chip->irq,
	       chip->base, chip->base + 0x7fff);
#अन्यथा
	चयन (info >> 4) अणु
	हाल 0xf:
		xv = "<= 1.15";
		अवरोध;
	हाल 0x1:
		xv = "1.18/1.2";
		अवरोध;
	हाल 0x2:
		xv = "1.3";
		अवरोध;
	हाल 0x3:
		xv = "1.4";
		अवरोध;
	शेष:
		xv = "unknown";
		अवरोध;
	पूर्ण

	चयन (info & 0x7) अणु
	हाल 0x0:
		rev = "I";
		म_नकल(card->लघुname, pin);
		अवरोध;
	हाल 0x1:
		rev = "F";
		म_नकल(card->लघुname, pin);
		अवरोध;
	हाल 0x2:
		rev = "G";
		म_नकल(card->लघुname, pin);
		अवरोध;
	हाल 0x3:
		rev = "H";
		म_नकल(card->लघुname, pin);
		अवरोध;
	हाल 0x4:
		rev = "E";
		म_नकल(card->लघुname, fiji);
		अवरोध;
	हाल 0x5:
		rev = "C";
		म_नकल(card->लघुname, fiji);
		अवरोध;
	हाल 0x6:
		rev = "D";
		म_नकल(card->लघुname, fiji);
		अवरोध;
	हाल 0x7:
		rev = "A-B (Fiji) or A-E (Pinnacle)";
		म_नकल(card->लघुname, pinfiji);
		अवरोध;
	पूर्ण
	म_नकल(card->दीर्घname, "Turtle Beach Multisound Pinnacle");
	prपूर्णांकk(KERN_INFO LOGNAME ": %s revision %s, Xilinx version %s, "
	       "I/O 0x%lx-0x%lx, IRQ %d, memory mapped to 0x%lX-0x%lX\n",
	       card->लघुname,
	       rev, xv,
	       chip->io, chip->io + DSP_NUMIO - 1,
	       chip->irq,
	       chip->base, chip->base + 0x7fff);
#पूर्ण_अगर

	release_region(chip->io, DSP_NUMIO);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_msnd_init_sma(काष्ठा snd_msnd *chip)
अणु
	अटल पूर्णांक initted;
	u16 mastVolLeft, mastVolRight;
	अचिन्हित दीर्घ flags;

#अगर_घोषित MSND_CLASSIC
	outb(chip->memid, chip->io + HP_MEMM);
#पूर्ण_अगर
	outb(HPBLKSEL_0, chip->io + HP_BLKS);
	/* Motorola 56k shared memory base */
	chip->SMA = chip->mappedbase + SMA_STRUCT_START;

	अगर (initted) अणु
		mastVolLeft = पढ़ोw(chip->SMA + SMA_wCurrMastVolLeft);
		mastVolRight = पढ़ोw(chip->SMA + SMA_wCurrMastVolRight);
	पूर्ण अन्यथा
		mastVolLeft = mastVolRight = 0;
	स_रखो_io(chip->mappedbase, 0, 0x8000);

	/* Critical section: bank 1 access */
	spin_lock_irqsave(&chip->lock, flags);
	outb(HPBLKSEL_1, chip->io + HP_BLKS);
	स_रखो_io(chip->mappedbase, 0, 0x8000);
	outb(HPBLKSEL_0, chip->io + HP_BLKS);
	spin_unlock_irqrestore(&chip->lock, flags);

	/* Digital audio play queue */
	chip->DAPQ = chip->mappedbase + DAPQ_OFFSET;
	snd_msnd_init_queue(chip->DAPQ, DAPQ_DATA_BUFF, DAPQ_BUFF_SIZE);

	/* Digital audio record queue */
	chip->DARQ = chip->mappedbase + DARQ_OFFSET;
	snd_msnd_init_queue(chip->DARQ, DARQ_DATA_BUFF, DARQ_BUFF_SIZE);

	/* MIDI out queue */
	chip->MODQ = chip->mappedbase + MODQ_OFFSET;
	snd_msnd_init_queue(chip->MODQ, MODQ_DATA_BUFF, MODQ_BUFF_SIZE);

	/* MIDI in queue */
	chip->MIDQ = chip->mappedbase + MIDQ_OFFSET;
	snd_msnd_init_queue(chip->MIDQ, MIDQ_DATA_BUFF, MIDQ_BUFF_SIZE);

	/* DSP -> host message queue */
	chip->DSPQ = chip->mappedbase + DSPQ_OFFSET;
	snd_msnd_init_queue(chip->DSPQ, DSPQ_DATA_BUFF, DSPQ_BUFF_SIZE);

	/* Setup some DSP values */
#अगर_अघोषित MSND_CLASSIC
	ग_लिखोw(1, chip->SMA + SMA_wCurrPlayFormat);
	ग_लिखोw(chip->play_sample_size, chip->SMA + SMA_wCurrPlaySampleSize);
	ग_लिखोw(chip->play_channels, chip->SMA + SMA_wCurrPlayChannels);
	ग_लिखोw(chip->play_sample_rate, chip->SMA + SMA_wCurrPlaySampleRate);
#पूर्ण_अगर
	ग_लिखोw(chip->play_sample_rate, chip->SMA + SMA_wCalFreqAtoD);
	ग_लिखोw(mastVolLeft, chip->SMA + SMA_wCurrMastVolLeft);
	ग_लिखोw(mastVolRight, chip->SMA + SMA_wCurrMastVolRight);
#अगर_अघोषित MSND_CLASSIC
	ग_लिखोl(0x00010000, chip->SMA + SMA_dwCurrPlayPitch);
	ग_लिखोl(0x00000001, chip->SMA + SMA_dwCurrPlayRate);
#पूर्ण_अगर
	ग_लिखोw(0x303, chip->SMA + SMA_wCurrInputTagBits);

	initted = 1;

	वापस 0;
पूर्ण


अटल पूर्णांक upload_dsp_code(काष्ठा snd_card *card)
अणु
	काष्ठा snd_msnd *chip = card->निजी_data;
	स्थिर काष्ठा firmware *init_fw = शून्य, *perm_fw = शून्य;
	पूर्णांक err;

	outb(HPBLKSEL_0, chip->io + HP_BLKS);

	err = request_firmware(&init_fw, INITCODEखाता, card->dev);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR LOGNAME ": Error loading " INITCODEखाता);
		जाओ cleanup1;
	पूर्ण
	err = request_firmware(&perm_fw, PERMCODEखाता, card->dev);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR LOGNAME ": Error loading " PERMCODEखाता);
		जाओ cleanup;
	पूर्ण

	स_नकल_toio(chip->mappedbase, perm_fw->data, perm_fw->size);
	अगर (snd_msnd_upload_host(chip, init_fw->data, init_fw->size) < 0) अणु
		prपूर्णांकk(KERN_WARNING LOGNAME ": Error uploading to DSP\n");
		err = -ENODEV;
		जाओ cleanup;
	पूर्ण
	prपूर्णांकk(KERN_INFO LOGNAME ": DSP firmware uploaded\n");
	err = 0;

cleanup:
	release_firmware(perm_fw);
cleanup1:
	release_firmware(init_fw);
	वापस err;
पूर्ण

#अगर_घोषित MSND_CLASSIC
अटल व्योम reset_proteus(काष्ठा snd_msnd *chip)
अणु
	outb(HPPRORESET_ON, chip->io + HP_PROR);
	msleep(TIME_PRO_RESET);
	outb(HPPRORESET_OFF, chip->io + HP_PROR);
	msleep(TIME_PRO_RESET_DONE);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक snd_msnd_initialize(काष्ठा snd_card *card)
अणु
	काष्ठा snd_msnd *chip = card->निजी_data;
	पूर्णांक err, समयout;

#अगर_घोषित MSND_CLASSIC
	outb(HPWAITSTATE_0, chip->io + HP_WAIT);
	outb(HPBITMODE_16, chip->io + HP_BITM);

	reset_proteus(chip);
#पूर्ण_अगर
	err = snd_msnd_init_sma(chip);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_WARNING LOGNAME ": Cannot initialize SMA\n");
		वापस err;
	पूर्ण

	err = snd_msnd_reset_dsp(chip->io, शून्य);
	अगर (err < 0)
		वापस err;

	err = upload_dsp_code(card);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_WARNING LOGNAME ": Cannot upload DSP code\n");
		वापस err;
	पूर्ण

	समयout = 200;

	जबतक (पढ़ोw(chip->mappedbase)) अणु
		msleep(1);
		अगर (!समयout--) अणु
			snd_prपूर्णांकd(KERN_ERR LOGNAME ": DSP reset timeout\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

	snd_msndmix_setup(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_msnd_dsp_full_reset(काष्ठा snd_card *card)
अणु
	काष्ठा snd_msnd *chip = card->निजी_data;
	पूर्णांक rv;

	अगर (test_bit(F_RESETTING, &chip->flags) || ++chip->nresets > 10)
		वापस 0;

	set_bit(F_RESETTING, &chip->flags);
	snd_msnd_dsp_halt(chip, शून्य);	/* Unconditionally halt */

	rv = snd_msnd_initialize(card);
	अगर (rv)
		prपूर्णांकk(KERN_WARNING LOGNAME ": DSP reset failed\n");
	snd_msndmix_क्रमce_recsrc(chip, 0);
	clear_bit(F_RESETTING, &chip->flags);
	वापस rv;
पूर्ण

अटल पूर्णांक snd_msnd_dev_मुक्त(काष्ठा snd_device *device)
अणु
	snd_prपूर्णांकdd("snd_msnd_chip_free()\n");
	वापस 0;
पूर्ण

अटल पूर्णांक snd_msnd_send_dsp_cmd_chk(काष्ठा snd_msnd *chip, u8 cmd)
अणु
	अगर (snd_msnd_send_dsp_cmd(chip, cmd) == 0)
		वापस 0;
	snd_msnd_dsp_full_reset(chip->card);
	वापस snd_msnd_send_dsp_cmd(chip, cmd);
पूर्ण

अटल पूर्णांक snd_msnd_calibrate_adc(काष्ठा snd_msnd *chip, u16 srate)
अणु
	snd_prपूर्णांकdd("snd_msnd_calibrate_adc(%i)\n", srate);
	ग_लिखोw(srate, chip->SMA + SMA_wCalFreqAtoD);
	अगर (chip->calibrate_संकेत == 0)
		ग_लिखोw(पढ़ोw(chip->SMA + SMA_wCurrHostStatusFlags)
		       | 0x0001, chip->SMA + SMA_wCurrHostStatusFlags);
	अन्यथा
		ग_लिखोw(पढ़ोw(chip->SMA + SMA_wCurrHostStatusFlags)
		       & ~0x0001, chip->SMA + SMA_wCurrHostStatusFlags);
	अगर (snd_msnd_send_word(chip, 0, 0, HDEXAR_CAL_A_TO_D) == 0 &&
	    snd_msnd_send_dsp_cmd_chk(chip, HDEX_AUX_REQ) == 0) अणु
		schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(333));
		वापस 0;
	पूर्ण
	prपूर्णांकk(KERN_WARNING LOGNAME ": ADC calibration failed\n");
	वापस -EIO;
पूर्ण

/*
 * ALSA callback function, called when attempting to खोलो the MIDI device.
 */
अटल पूर्णांक snd_msnd_mpu401_खोलो(काष्ठा snd_mpu401 *mpu)
अणु
	snd_msnd_enable_irq(mpu->निजी_data);
	snd_msnd_send_dsp_cmd(mpu->निजी_data, HDEX_MIDI_IN_START);
	वापस 0;
पूर्ण

अटल व्योम snd_msnd_mpu401_बंद(काष्ठा snd_mpu401 *mpu)
अणु
	snd_msnd_send_dsp_cmd(mpu->निजी_data, HDEX_MIDI_IN_STOP);
	snd_msnd_disable_irq(mpu->निजी_data);
पूर्ण

अटल दीर्घ mpu_io[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;
अटल पूर्णांक mpu_irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;

अटल पूर्णांक snd_msnd_attach(काष्ठा snd_card *card)
अणु
	काष्ठा snd_msnd *chip = card->निजी_data;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =      snd_msnd_dev_मुक्त,
		पूर्ण;

	err = request_irq(chip->irq, snd_msnd_पूर्णांकerrupt, 0, card->लघुname,
			  chip);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR LOGNAME ": Couldn't grab IRQ %d\n", chip->irq);
		वापस err;
	पूर्ण
	card->sync_irq = chip->irq;
	अगर (request_region(chip->io, DSP_NUMIO, card->लघुname) == शून्य) अणु
		मुक्त_irq(chip->irq, chip);
		वापस -EBUSY;
	पूर्ण

	अगर (!request_mem_region(chip->base, BUFFSIZE, card->लघुname)) अणु
		prपूर्णांकk(KERN_ERR LOGNAME
			": unable to grab memory region 0x%lx-0x%lx\n",
			chip->base, chip->base + BUFFSIZE - 1);
		release_region(chip->io, DSP_NUMIO);
		मुक्त_irq(chip->irq, chip);
		वापस -EBUSY;
	पूर्ण
	chip->mappedbase = ioremap(chip->base, 0x8000);
	अगर (!chip->mappedbase) अणु
		prपूर्णांकk(KERN_ERR LOGNAME
			": unable to map memory region 0x%lx-0x%lx\n",
			chip->base, chip->base + BUFFSIZE - 1);
		err = -EIO;
		जाओ err_release_region;
	पूर्ण

	err = snd_msnd_dsp_full_reset(card);
	अगर (err < 0)
		जाओ err_release_region;

	/* Register device */
	err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops);
	अगर (err < 0)
		जाओ err_release_region;

	err = snd_msnd_pcm(card, 0);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR LOGNAME ": error creating new PCM device\n");
		जाओ err_release_region;
	पूर्ण

	err = snd_msndmix_new(card);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR LOGNAME ": error creating new Mixer device\n");
		जाओ err_release_region;
	पूर्ण


	अगर (mpu_io[0] != SNDRV_AUTO_PORT) अणु
		काष्ठा snd_mpu401 *mpu;

		err = snd_mpu401_uart_new(card, 0, MPU401_HW_MPU401,
					  mpu_io[0],
					  MPU401_MODE_INPUT |
					  MPU401_MODE_OUTPUT,
					  mpu_irq[0],
					  &chip->rmidi);
		अगर (err < 0) अणु
			prपूर्णांकk(KERN_ERR LOGNAME
				": error creating new Midi device\n");
			जाओ err_release_region;
		पूर्ण
		mpu = chip->rmidi->निजी_data;

		mpu->खोलो_input = snd_msnd_mpu401_खोलो;
		mpu->बंद_input = snd_msnd_mpu401_बंद;
		mpu->निजी_data = chip;
	पूर्ण

	disable_irq(chip->irq);
	snd_msnd_calibrate_adc(chip, chip->play_sample_rate);
	snd_msndmix_क्रमce_recsrc(chip, 0);

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ err_release_region;

	वापस 0;

err_release_region:
	iounmap(chip->mappedbase);
	release_mem_region(chip->base, BUFFSIZE);
	release_region(chip->io, DSP_NUMIO);
	मुक्त_irq(chip->irq, chip);
	वापस err;
पूर्ण


अटल व्योम snd_msnd_unload(काष्ठा snd_card *card)
अणु
	काष्ठा snd_msnd *chip = card->निजी_data;

	iounmap(chip->mappedbase);
	release_mem_region(chip->base, BUFFSIZE);
	release_region(chip->io, DSP_NUMIO);
	मुक्त_irq(chip->irq, chip);
	snd_card_मुक्त(card);
पूर्ण

#अगर_अघोषित MSND_CLASSIC

/* Pinnacle/Fiji Logical Device Configuration */

अटल पूर्णांक snd_msnd_ग_लिखो_cfg(पूर्णांक cfg, पूर्णांक reg, पूर्णांक value)
अणु
	outb(reg, cfg);
	outb(value, cfg + 1);
	अगर (value != inb(cfg + 1)) अणु
		prपूर्णांकk(KERN_ERR LOGNAME ": snd_msnd_write_cfg: I/O error\n");
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_msnd_ग_लिखो_cfg_io0(पूर्णांक cfg, पूर्णांक num, u16 io)
अणु
	अगर (snd_msnd_ग_लिखो_cfg(cfg, IREG_LOGDEVICE, num))
		वापस -EIO;
	अगर (snd_msnd_ग_लिखो_cfg(cfg, IREG_IO0_BASEHI, HIBYTE(io)))
		वापस -EIO;
	अगर (snd_msnd_ग_लिखो_cfg(cfg, IREG_IO0_BASELO, LOBYTE(io)))
		वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_msnd_ग_लिखो_cfg_io1(पूर्णांक cfg, पूर्णांक num, u16 io)
अणु
	अगर (snd_msnd_ग_लिखो_cfg(cfg, IREG_LOGDEVICE, num))
		वापस -EIO;
	अगर (snd_msnd_ग_लिखो_cfg(cfg, IREG_IO1_BASEHI, HIBYTE(io)))
		वापस -EIO;
	अगर (snd_msnd_ग_लिखो_cfg(cfg, IREG_IO1_BASELO, LOBYTE(io)))
		वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_msnd_ग_लिखो_cfg_irq(पूर्णांक cfg, पूर्णांक num, u16 irq)
अणु
	अगर (snd_msnd_ग_लिखो_cfg(cfg, IREG_LOGDEVICE, num))
		वापस -EIO;
	अगर (snd_msnd_ग_लिखो_cfg(cfg, IREG_IRQ_NUMBER, LOBYTE(irq)))
		वापस -EIO;
	अगर (snd_msnd_ग_लिखो_cfg(cfg, IREG_IRQ_TYPE, IRQTYPE_EDGE))
		वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_msnd_ग_लिखो_cfg_mem(पूर्णांक cfg, पूर्णांक num, पूर्णांक mem)
अणु
	u16 wmem;

	mem >>= 8;
	wmem = (u16)(mem & 0xfff);
	अगर (snd_msnd_ग_लिखो_cfg(cfg, IREG_LOGDEVICE, num))
		वापस -EIO;
	अगर (snd_msnd_ग_लिखो_cfg(cfg, IREG_MEMBASEHI, HIBYTE(wmem)))
		वापस -EIO;
	अगर (snd_msnd_ग_लिखो_cfg(cfg, IREG_MEMBASELO, LOBYTE(wmem)))
		वापस -EIO;
	अगर (wmem && snd_msnd_ग_लिखो_cfg(cfg, IREG_MEMCONTROL,
				       MEMTYPE_HIADDR | MEMTYPE_16BIT))
		वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_msnd_activate_logical(पूर्णांक cfg, पूर्णांक num)
अणु
	अगर (snd_msnd_ग_लिखो_cfg(cfg, IREG_LOGDEVICE, num))
		वापस -EIO;
	अगर (snd_msnd_ग_लिखो_cfg(cfg, IREG_ACTIVATE, LD_ACTIVATE))
		वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_msnd_ग_लिखो_cfg_logical(पूर्णांक cfg, पूर्णांक num, u16 io0,
				      u16 io1, u16 irq, पूर्णांक mem)
अणु
	अगर (snd_msnd_ग_लिखो_cfg(cfg, IREG_LOGDEVICE, num))
		वापस -EIO;
	अगर (snd_msnd_ग_लिखो_cfg_io0(cfg, num, io0))
		वापस -EIO;
	अगर (snd_msnd_ग_लिखो_cfg_io1(cfg, num, io1))
		वापस -EIO;
	अगर (snd_msnd_ग_लिखो_cfg_irq(cfg, num, irq))
		वापस -EIO;
	अगर (snd_msnd_ग_लिखो_cfg_mem(cfg, num, mem))
		वापस -EIO;
	अगर (snd_msnd_activate_logical(cfg, num))
		वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_msnd_pinnacle_cfg_reset(पूर्णांक cfg)
अणु
	पूर्णांक i;

	/* Reset devices अगर told to */
	prपूर्णांकk(KERN_INFO LOGNAME ": Resetting all devices\n");
	क्रम (i = 0; i < 4; ++i)
		अगर (snd_msnd_ग_लिखो_cfg_logical(cfg, i, 0, 0, 0, 0))
			वापस -EIO;

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for msnd_pinnacle soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for msnd_pinnacle soundcard.");

अटल दीर्घ io[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;
अटल पूर्णांक irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;
अटल दीर्घ mem[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;

#अगर_अघोषित MSND_CLASSIC
अटल दीर्घ cfg[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;

/* Extra Peripheral Configuration (Default: Disable) */
अटल दीर्घ ide_io0[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;
अटल दीर्घ ide_io1[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;
अटल पूर्णांक ide_irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;

अटल दीर्घ joystick_io[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;
/* If we have the digital daugherboard... */
अटल पूर्णांक digital[SNDRV_CARDS];

/* Extra Peripheral Configuration */
अटल पूर्णांक reset[SNDRV_CARDS];
#पूर्ण_अगर

अटल पूर्णांक ग_लिखो_ndelay[SNDRV_CARDS] = अणु [0 ... (SNDRV_CARDS-1)] = 1 पूर्ण;

अटल पूर्णांक calibrate_संकेत;

#अगर_घोषित CONFIG_PNP
अटल bool isapnp[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;
module_param_array(isapnp, bool, शून्य, 0444);
MODULE_PARM_DESC(isapnp, "ISA PnP detection for specified soundcard.");
#घोषणा has_isapnp(x) isapnp[x]
#अन्यथा
#घोषणा has_isapnp(x) 0
#पूर्ण_अगर

MODULE_AUTHOR("Karsten Wiese <annabellesgarden@yahoo.de>");
MODULE_DESCRIPTION("Turtle Beach " LONGNAME " Linux Driver");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(INITCODEखाता);
MODULE_FIRMWARE(PERMCODEखाता);

module_param_hw_array(io, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(io, "IO port #");
module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0444);
module_param_hw_array(mem, दीर्घ, iomem, शून्य, 0444);
module_param_array(ग_लिखो_ndelay, पूर्णांक, शून्य, 0444);
module_param(calibrate_संकेत, पूर्णांक, 0444);
#अगर_अघोषित MSND_CLASSIC
module_param_array(digital, पूर्णांक, शून्य, 0444);
module_param_hw_array(cfg, दीर्घ, ioport, शून्य, 0444);
module_param_array(reset, पूर्णांक, शून्य, 0444);
module_param_hw_array(mpu_io, दीर्घ, ioport, शून्य, 0444);
module_param_hw_array(mpu_irq, पूर्णांक, irq, शून्य, 0444);
module_param_hw_array(ide_io0, दीर्घ, ioport, शून्य, 0444);
module_param_hw_array(ide_io1, दीर्घ, ioport, शून्य, 0444);
module_param_hw_array(ide_irq, पूर्णांक, irq, शून्य, 0444);
module_param_hw_array(joystick_io, दीर्घ, ioport, शून्य, 0444);
#पूर्ण_अगर


अटल पूर्णांक snd_msnd_isa_match(काष्ठा device *pdev, अचिन्हित पूर्णांक i)
अणु
	अगर (io[i] == SNDRV_AUTO_PORT)
		वापस 0;

	अगर (irq[i] == SNDRV_AUTO_PORT || mem[i] == SNDRV_AUTO_PORT) अणु
		prपूर्णांकk(KERN_WARNING LOGNAME ": io, irq and mem must be set\n");
		वापस 0;
	पूर्ण

#अगर_घोषित MSND_CLASSIC
	अगर (!(io[i] == 0x290 ||
	      io[i] == 0x260 ||
	      io[i] == 0x250 ||
	      io[i] == 0x240 ||
	      io[i] == 0x230 ||
	      io[i] == 0x220 ||
	      io[i] == 0x210 ||
	      io[i] == 0x3e0)) अणु
		prपूर्णांकk(KERN_ERR LOGNAME ": \"io\" - DSP I/O base must be set "
			" to 0x210, 0x220, 0x230, 0x240, 0x250, 0x260, 0x290, "
			"or 0x3E0\n");
		वापस 0;
	पूर्ण
#अन्यथा
	अगर (io[i] < 0x100 || io[i] > 0x3e0 || (io[i] % 0x10) != 0) अणु
		prपूर्णांकk(KERN_ERR LOGNAME
			": \"io\" - DSP I/O base must within the range 0x100 "
			"to 0x3E0 and must be evenly divisible by 0x10\n");
		वापस 0;
	पूर्ण
#पूर्ण_अगर /* MSND_CLASSIC */

	अगर (!(irq[i] == 5 ||
	      irq[i] == 7 ||
	      irq[i] == 9 ||
	      irq[i] == 10 ||
	      irq[i] == 11 ||
	      irq[i] == 12)) अणु
		prपूर्णांकk(KERN_ERR LOGNAME
			": \"irq\" - must be set to 5, 7, 9, 10, 11 or 12\n");
		वापस 0;
	पूर्ण

	अगर (!(mem[i] == 0xb0000 ||
	      mem[i] == 0xc8000 ||
	      mem[i] == 0xd0000 ||
	      mem[i] == 0xd8000 ||
	      mem[i] == 0xe0000 ||
	      mem[i] == 0xe8000)) अणु
		prपूर्णांकk(KERN_ERR LOGNAME ": \"mem\" - must be set to "
		       "0xb0000, 0xc8000, 0xd0000, 0xd8000, 0xe0000 or "
		       "0xe8000\n");
		वापस 0;
	पूर्ण

#अगर_अघोषित MSND_CLASSIC
	अगर (cfg[i] == SNDRV_AUTO_PORT) अणु
		prपूर्णांकk(KERN_INFO LOGNAME ": Assuming PnP mode\n");
	पूर्ण अन्यथा अगर (cfg[i] != 0x250 && cfg[i] != 0x260 && cfg[i] != 0x270) अणु
		prपूर्णांकk(KERN_INFO LOGNAME
			": Config port must be 0x250, 0x260 or 0x270 "
			"(or unspecified for PnP mode)\n");
		वापस 0;
	पूर्ण
#पूर्ण_अगर /* MSND_CLASSIC */

	वापस 1;
पूर्ण

अटल पूर्णांक snd_msnd_isa_probe(काष्ठा device *pdev, अचिन्हित पूर्णांक idx)
अणु
	पूर्णांक err;
	काष्ठा snd_card *card;
	काष्ठा snd_msnd *chip;

	अगर (has_isapnp(idx)
#अगर_अघोषित MSND_CLASSIC
	    || cfg[idx] == SNDRV_AUTO_PORT
#पूर्ण_अगर
	    ) अणु
		prपूर्णांकk(KERN_INFO LOGNAME ": Assuming PnP mode\n");
		वापस -ENODEV;
	पूर्ण

	err = snd_card_new(pdev, index[idx], id[idx], THIS_MODULE,
			   माप(काष्ठा snd_msnd), &card);
	अगर (err < 0)
		वापस err;

	chip = card->निजी_data;
	chip->card = card;

#अगर_घोषित MSND_CLASSIC
	चयन (irq[idx]) अणु
	हाल 5:
		chip->irqid = HPIRQ_5; अवरोध;
	हाल 7:
		chip->irqid = HPIRQ_7; अवरोध;
	हाल 9:
		chip->irqid = HPIRQ_9; अवरोध;
	हाल 10:
		chip->irqid = HPIRQ_10; अवरोध;
	हाल 11:
		chip->irqid = HPIRQ_11; अवरोध;
	हाल 12:
		chip->irqid = HPIRQ_12; अवरोध;
	पूर्ण

	चयन (mem[idx]) अणु
	हाल 0xb0000:
		chip->memid = HPMEM_B000; अवरोध;
	हाल 0xc8000:
		chip->memid = HPMEM_C800; अवरोध;
	हाल 0xd0000:
		chip->memid = HPMEM_D000; अवरोध;
	हाल 0xd8000:
		chip->memid = HPMEM_D800; अवरोध;
	हाल 0xe0000:
		chip->memid = HPMEM_E000; अवरोध;
	हाल 0xe8000:
		chip->memid = HPMEM_E800; अवरोध;
	पूर्ण
#अन्यथा
	prपूर्णांकk(KERN_INFO LOGNAME ": Non-PnP mode: configuring at port 0x%lx\n",
			cfg[idx]);

	अगर (!request_region(cfg[idx], 2, "Pinnacle/Fiji Config")) अणु
		prपूर्णांकk(KERN_ERR LOGNAME ": Config port 0x%lx conflict\n",
			   cfg[idx]);
		snd_card_मुक्त(card);
		वापस -EIO;
	पूर्ण
	अगर (reset[idx])
		अगर (snd_msnd_pinnacle_cfg_reset(cfg[idx])) अणु
			err = -EIO;
			जाओ cfg_error;
		पूर्ण

	/* DSP */
	err = snd_msnd_ग_लिखो_cfg_logical(cfg[idx], 0,
					 io[idx], 0,
					 irq[idx], mem[idx]);

	अगर (err)
		जाओ cfg_error;

	/* The following are Pinnacle specअगरic */

	/* MPU */
	अगर (mpu_io[idx] != SNDRV_AUTO_PORT
	    && mpu_irq[idx] != SNDRV_AUTO_IRQ) अणु
		prपूर्णांकk(KERN_INFO LOGNAME
		       ": Configuring MPU to I/O 0x%lx IRQ %d\n",
		       mpu_io[idx], mpu_irq[idx]);
		err = snd_msnd_ग_लिखो_cfg_logical(cfg[idx], 1,
						 mpu_io[idx], 0,
						 mpu_irq[idx], 0);

		अगर (err)
			जाओ cfg_error;
	पूर्ण

	/* IDE */
	अगर (ide_io0[idx] != SNDRV_AUTO_PORT
	    && ide_io1[idx] != SNDRV_AUTO_PORT
	    && ide_irq[idx] != SNDRV_AUTO_IRQ) अणु
		prपूर्णांकk(KERN_INFO LOGNAME
		       ": Configuring IDE to I/O 0x%lx, 0x%lx IRQ %d\n",
		       ide_io0[idx], ide_io1[idx], ide_irq[idx]);
		err = snd_msnd_ग_लिखो_cfg_logical(cfg[idx], 2,
						 ide_io0[idx], ide_io1[idx],
						 ide_irq[idx], 0);

		अगर (err)
			जाओ cfg_error;
	पूर्ण

	/* Joystick */
	अगर (joystick_io[idx] != SNDRV_AUTO_PORT) अणु
		prपूर्णांकk(KERN_INFO LOGNAME
		       ": Configuring joystick to I/O 0x%lx\n",
		       joystick_io[idx]);
		err = snd_msnd_ग_लिखो_cfg_logical(cfg[idx], 3,
						 joystick_io[idx], 0,
						 0, 0);

		अगर (err)
			जाओ cfg_error;
	पूर्ण
	release_region(cfg[idx], 2);

#पूर्ण_अगर /* MSND_CLASSIC */

	set_शेष_audio_parameters(chip);
#अगर_घोषित MSND_CLASSIC
	chip->type = msndClassic;
#अन्यथा
	chip->type = msndPinnacle;
#पूर्ण_अगर
	chip->io = io[idx];
	chip->irq = irq[idx];
	chip->base = mem[idx];

	chip->calibrate_संकेत = calibrate_संकेत ? 1 : 0;
	chip->recsrc = 0;
	chip->dspq_data_buff = DSPQ_DATA_BUFF;
	chip->dspq_buff_size = DSPQ_BUFF_SIZE;
	अगर (ग_लिखो_ndelay[idx])
		clear_bit(F_DISABLE_WRITE_NDELAY, &chip->flags);
	अन्यथा
		set_bit(F_DISABLE_WRITE_NDELAY, &chip->flags);
#अगर_अघोषित MSND_CLASSIC
	अगर (digital[idx])
		set_bit(F_HAVEDIGITAL, &chip->flags);
#पूर्ण_अगर
	spin_lock_init(&chip->lock);
	err = snd_msnd_probe(card);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR LOGNAME ": Probe failed\n");
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	err = snd_msnd_attach(card);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR LOGNAME ": Attach failed\n");
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	dev_set_drvdata(pdev, card);

	वापस 0;

#अगर_अघोषित MSND_CLASSIC
cfg_error:
	release_region(cfg[idx], 2);
	snd_card_मुक्त(card);
	वापस err;
#पूर्ण_अगर
पूर्ण

अटल व्योम snd_msnd_isa_हटाओ(काष्ठा device *pdev, अचिन्हित पूर्णांक dev)
अणु
	snd_msnd_unload(dev_get_drvdata(pdev));
पूर्ण

अटल काष्ठा isa_driver snd_msnd_driver = अणु
	.match		= snd_msnd_isa_match,
	.probe		= snd_msnd_isa_probe,
	.हटाओ		= snd_msnd_isa_हटाओ,
	/* FIXME: suspend, resume */
	.driver		= अणु
		.name	= DEV_NAME
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_PNP
अटल पूर्णांक snd_msnd_pnp_detect(काष्ठा pnp_card_link *pcard,
			       स्थिर काष्ठा pnp_card_device_id *pid)
अणु
	अटल पूर्णांक idx;
	काष्ठा pnp_dev *pnp_dev;
	काष्ठा pnp_dev *mpu_dev;
	काष्ठा snd_card *card;
	काष्ठा snd_msnd *chip;
	पूर्णांक ret;

	क्रम ( ; idx < SNDRV_CARDS; idx++) अणु
		अगर (has_isapnp(idx))
			अवरोध;
	पूर्ण
	अगर (idx >= SNDRV_CARDS)
		वापस -ENODEV;

	/*
	 * Check that we still have room क्रम another sound card ...
	 */
	pnp_dev = pnp_request_card_device(pcard, pid->devs[0].id, शून्य);
	अगर (!pnp_dev)
		वापस -ENODEV;

	mpu_dev = pnp_request_card_device(pcard, pid->devs[1].id, शून्य);
	अगर (!mpu_dev)
		वापस -ENODEV;

	अगर (!pnp_is_active(pnp_dev) && pnp_activate_dev(pnp_dev) < 0) अणु
		prपूर्णांकk(KERN_INFO "msnd_pinnacle: device is inactive\n");
		वापस -EBUSY;
	पूर्ण

	अगर (!pnp_is_active(mpu_dev) && pnp_activate_dev(mpu_dev) < 0) अणु
		prपूर्णांकk(KERN_INFO "msnd_pinnacle: MPU device is inactive\n");
		वापस -EBUSY;
	पूर्ण

	/*
	 * Create a new ALSA sound card entry, in anticipation
	 * of detecting our hardware ...
	 */
	ret = snd_card_new(&pcard->card->dev,
			   index[idx], id[idx], THIS_MODULE,
			   माप(काष्ठा snd_msnd), &card);
	अगर (ret < 0)
		वापस ret;

	chip = card->निजी_data;
	chip->card = card;

	/*
	 * Read the correct parameters off the ISA PnP bus ...
	 */
	io[idx] = pnp_port_start(pnp_dev, 0);
	irq[idx] = pnp_irq(pnp_dev, 0);
	mem[idx] = pnp_mem_start(pnp_dev, 0);
	mpu_io[idx] = pnp_port_start(mpu_dev, 0);
	mpu_irq[idx] = pnp_irq(mpu_dev, 0);

	set_शेष_audio_parameters(chip);
#अगर_घोषित MSND_CLASSIC
	chip->type = msndClassic;
#अन्यथा
	chip->type = msndPinnacle;
#पूर्ण_अगर
	chip->io = io[idx];
	chip->irq = irq[idx];
	chip->base = mem[idx];

	chip->calibrate_संकेत = calibrate_संकेत ? 1 : 0;
	chip->recsrc = 0;
	chip->dspq_data_buff = DSPQ_DATA_BUFF;
	chip->dspq_buff_size = DSPQ_BUFF_SIZE;
	अगर (ग_लिखो_ndelay[idx])
		clear_bit(F_DISABLE_WRITE_NDELAY, &chip->flags);
	अन्यथा
		set_bit(F_DISABLE_WRITE_NDELAY, &chip->flags);
#अगर_अघोषित MSND_CLASSIC
	अगर (digital[idx])
		set_bit(F_HAVEDIGITAL, &chip->flags);
#पूर्ण_अगर
	spin_lock_init(&chip->lock);
	ret = snd_msnd_probe(card);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR LOGNAME ": Probe failed\n");
		जाओ _release_card;
	पूर्ण

	ret = snd_msnd_attach(card);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR LOGNAME ": Attach failed\n");
		जाओ _release_card;
	पूर्ण

	pnp_set_card_drvdata(pcard, card);
	++idx;
	वापस 0;

_release_card:
	snd_card_मुक्त(card);
	वापस ret;
पूर्ण

अटल व्योम snd_msnd_pnp_हटाओ(काष्ठा pnp_card_link *pcard)
अणु
	snd_msnd_unload(pnp_get_card_drvdata(pcard));
	pnp_set_card_drvdata(pcard, शून्य);
पूर्ण

अटल पूर्णांक isa_रेजिस्टरed;
अटल पूर्णांक pnp_रेजिस्टरed;

अटल स्थिर काष्ठा pnp_card_device_id msnd_pnpids[] = अणु
	/* Pinnacle PnP */
	अणु .id = "BVJ0440", .devs = अणु अणु "TBS0000" पूर्ण, अणु "TBS0001" पूर्ण पूर्ण पूर्ण,
	अणु .id = "" पूर्ण	/* end */
पूर्ण;

MODULE_DEVICE_TABLE(pnp_card, msnd_pnpids);

अटल काष्ठा pnp_card_driver msnd_pnpc_driver = अणु
	.flags = PNP_DRIVER_RES_DO_NOT_CHANGE,
	.name = "msnd_pinnacle",
	.id_table = msnd_pnpids,
	.probe = snd_msnd_pnp_detect,
	.हटाओ = snd_msnd_pnp_हटाओ,
पूर्ण;
#पूर्ण_अगर /* CONFIG_PNP */

अटल पूर्णांक __init snd_msnd_init(व्योम)
अणु
	पूर्णांक err;

	err = isa_रेजिस्टर_driver(&snd_msnd_driver, SNDRV_CARDS);
#अगर_घोषित CONFIG_PNP
	अगर (!err)
		isa_रेजिस्टरed = 1;

	err = pnp_रेजिस्टर_card_driver(&msnd_pnpc_driver);
	अगर (!err)
		pnp_रेजिस्टरed = 1;

	अगर (isa_रेजिस्टरed)
		err = 0;
#पूर्ण_अगर
	वापस err;
पूर्ण

अटल व्योम __निकास snd_msnd_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_PNP
	अगर (pnp_रेजिस्टरed)
		pnp_unरेजिस्टर_card_driver(&msnd_pnpc_driver);
	अगर (isa_रेजिस्टरed)
#पूर्ण_अगर
		isa_unरेजिस्टर_driver(&snd_msnd_driver);
पूर्ण

module_init(snd_msnd_init);
module_निकास(snd_msnd_निकास);

