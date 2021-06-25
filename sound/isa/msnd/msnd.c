<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*********************************************************************
 *
 * 2002/06/30 Karsten Wiese:
 *	हटाओd kernel-version dependencies.
 *	ripped from linux kernel 2.4.18 (OSS Implementation) by me.
 *	In the OSS Version, this file is compiled to a separate MODULE,
 *	that is used by the pinnacle and the classic driver.
 *	since there is no classic driver क्रम alsa yet (i करोnt have a classic
 *	& writing one blindfold is dअगरficult) this file's object is अटलally
 *	linked पूर्णांकo the pinnacle-driver-module क्रम now.	look क्रम the string
 *		"uncomment this to make this a module again"
 *	to करो guess what.
 *
 * the following is a copy of the 2.4.18 OSS FREE file-heading comment:
 *
 * msnd.c - Driver Base
 *
 * Turtle Beach MultiSound Sound Card Driver क्रम Linux
 *
 * Copyright (C) 1998 Andrew Veliath
 *
 ********************************************************************/

#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/fs.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>

#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>

#समावेश "msnd.h"

#घोषणा LOGNAME			"msnd"


व्योम snd_msnd_init_queue(व्योम __iomem *base, पूर्णांक start, पूर्णांक size)
अणु
	ग_लिखोw(PCTODSP_BASED(start), base + JQS_wStart);
	ग_लिखोw(PCTODSP_OFFSET(size) - 1, base + JQS_wSize);
	ग_लिखोw(0, base + JQS_wHead);
	ग_लिखोw(0, base + JQS_wTail);
पूर्ण
EXPORT_SYMBOL(snd_msnd_init_queue);

अटल पूर्णांक snd_msnd_रुको_TXDE(काष्ठा snd_msnd *dev)
अणु
	अचिन्हित पूर्णांक io = dev->io;
	पूर्णांक समयout = 1000;

	जबतक (समयout-- > 0)
		अगर (inb(io + HP_ISR) & HPISR_TXDE)
			वापस 0;

	वापस -EIO;
पूर्ण

अटल पूर्णांक snd_msnd_रुको_HC0(काष्ठा snd_msnd *dev)
अणु
	अचिन्हित पूर्णांक io = dev->io;
	पूर्णांक समयout = 1000;

	जबतक (समयout-- > 0)
		अगर (!(inb(io + HP_CVR) & HPCVR_HC))
			वापस 0;

	वापस -EIO;
पूर्ण

पूर्णांक snd_msnd_send_dsp_cmd(काष्ठा snd_msnd *dev, u8 cmd)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->lock, flags);
	अगर (snd_msnd_रुको_HC0(dev) == 0) अणु
		outb(cmd, dev->io + HP_CVR);
		spin_unlock_irqrestore(&dev->lock, flags);
		वापस 0;
	पूर्ण
	spin_unlock_irqrestore(&dev->lock, flags);

	snd_prपूर्णांकd(KERN_ERR LOGNAME ": Send DSP command timeout\n");

	वापस -EIO;
पूर्ण
EXPORT_SYMBOL(snd_msnd_send_dsp_cmd);

पूर्णांक snd_msnd_send_word(काष्ठा snd_msnd *dev, अचिन्हित अक्षर high,
		   अचिन्हित अक्षर mid, अचिन्हित अक्षर low)
अणु
	अचिन्हित पूर्णांक io = dev->io;

	अगर (snd_msnd_रुको_TXDE(dev) == 0) अणु
		outb(high, io + HP_TXH);
		outb(mid, io + HP_TXM);
		outb(low, io + HP_TXL);
		वापस 0;
	पूर्ण

	snd_prपूर्णांकd(KERN_ERR LOGNAME ": Send host word timeout\n");

	वापस -EIO;
पूर्ण
EXPORT_SYMBOL(snd_msnd_send_word);

पूर्णांक snd_msnd_upload_host(काष्ठा snd_msnd *dev, स्थिर u8 *bin, पूर्णांक len)
अणु
	पूर्णांक i;

	अगर (len % 3 != 0) अणु
		snd_prपूर्णांकk(KERN_ERR LOGNAME
			   ": Upload host data not multiple of 3!\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < len; i += 3)
		अगर (snd_msnd_send_word(dev, bin[i], bin[i + 1], bin[i + 2]))
			वापस -EIO;

	inb(dev->io + HP_RXL);
	inb(dev->io + HP_CVR);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_msnd_upload_host);

पूर्णांक snd_msnd_enable_irq(काष्ठा snd_msnd *dev)
अणु
	अचिन्हित दीर्घ flags;

	अगर (dev->irq_ref++)
		वापस 0;

	snd_prपूर्णांकdd(LOGNAME ": Enabling IRQ\n");

	spin_lock_irqsave(&dev->lock, flags);
	अगर (snd_msnd_रुको_TXDE(dev) == 0) अणु
		outb(inb(dev->io + HP_ICR) | HPICR_TREQ, dev->io + HP_ICR);
		अगर (dev->type == msndClassic)
			outb(dev->irqid, dev->io + HP_IRQM);

		outb(inb(dev->io + HP_ICR) & ~HPICR_TREQ, dev->io + HP_ICR);
		outb(inb(dev->io + HP_ICR) | HPICR_RREQ, dev->io + HP_ICR);
		enable_irq(dev->irq);
		snd_msnd_init_queue(dev->DSPQ, dev->dspq_data_buff,
				    dev->dspq_buff_size);
		spin_unlock_irqrestore(&dev->lock, flags);
		वापस 0;
	पूर्ण
	spin_unlock_irqrestore(&dev->lock, flags);

	snd_prपूर्णांकd(KERN_ERR LOGNAME ": Enable IRQ failed\n");

	वापस -EIO;
पूर्ण
EXPORT_SYMBOL(snd_msnd_enable_irq);

पूर्णांक snd_msnd_disable_irq(काष्ठा snd_msnd *dev)
अणु
	अचिन्हित दीर्घ flags;

	अगर (--dev->irq_ref > 0)
		वापस 0;

	अगर (dev->irq_ref < 0)
		snd_prपूर्णांकd(KERN_WARNING LOGNAME ": IRQ ref count is %d\n",
			   dev->irq_ref);

	snd_prपूर्णांकdd(LOGNAME ": Disabling IRQ\n");

	spin_lock_irqsave(&dev->lock, flags);
	अगर (snd_msnd_रुको_TXDE(dev) == 0) अणु
		outb(inb(dev->io + HP_ICR) & ~HPICR_RREQ, dev->io + HP_ICR);
		अगर (dev->type == msndClassic)
			outb(HPIRQ_NONE, dev->io + HP_IRQM);
		disable_irq(dev->irq);
		spin_unlock_irqrestore(&dev->lock, flags);
		वापस 0;
	पूर्ण
	spin_unlock_irqrestore(&dev->lock, flags);

	snd_prपूर्णांकd(KERN_ERR LOGNAME ": Disable IRQ failed\n");

	वापस -EIO;
पूर्ण
EXPORT_SYMBOL(snd_msnd_disable_irq);

अटल अंतरभूत दीर्घ get_play_delay_jअगरfies(काष्ठा snd_msnd *chip, दीर्घ size)
अणु
	दीर्घ पंचांगp = (size * HZ * chip->play_sample_size) / 8;
	वापस पंचांगp / (chip->play_sample_rate * chip->play_channels);
पूर्ण

अटल व्योम snd_msnd_dsp_ग_लिखो_flush(काष्ठा snd_msnd *chip)
अणु
	अगर (!(chip->mode & FMODE_WRITE) || !test_bit(F_WRITING, &chip->flags))
		वापस;
	set_bit(F_WRITEFLUSH, &chip->flags);
/*	पूर्णांकerruptible_sleep_on_समयout(
		&chip->ग_लिखोflush,
		get_play_delay_jअगरfies(&chip, chip->DAPF.len));*/
	clear_bit(F_WRITEFLUSH, &chip->flags);
	अगर (!संकेत_pending(current))
		schedule_समयout_पूर्णांकerruptible(
			get_play_delay_jअगरfies(chip, chip->play_period_bytes));
	clear_bit(F_WRITING, &chip->flags);
पूर्ण

व्योम snd_msnd_dsp_halt(काष्ठा snd_msnd *chip, काष्ठा file *file)
अणु
	अगर ((file ? file->f_mode : chip->mode) & FMODE_READ) अणु
		clear_bit(F_READING, &chip->flags);
		snd_msnd_send_dsp_cmd(chip, HDEX_RECORD_STOP);
		snd_msnd_disable_irq(chip);
		अगर (file) अणु
			snd_prपूर्णांकd(KERN_INFO LOGNAME
				   ": Stopping read for %p\n", file);
			chip->mode &= ~FMODE_READ;
		पूर्ण
		clear_bit(F_AUDIO_READ_INUSE, &chip->flags);
	पूर्ण
	अगर ((file ? file->f_mode : chip->mode) & FMODE_WRITE) अणु
		अगर (test_bit(F_WRITING, &chip->flags)) अणु
			snd_msnd_dsp_ग_लिखो_flush(chip);
			snd_msnd_send_dsp_cmd(chip, HDEX_PLAY_STOP);
		पूर्ण
		snd_msnd_disable_irq(chip);
		अगर (file) अणु
			snd_prपूर्णांकd(KERN_INFO
				   LOGNAME ": Stopping write for %p\n", file);
			chip->mode &= ~FMODE_WRITE;
		पूर्ण
		clear_bit(F_AUDIO_WRITE_INUSE, &chip->flags);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(snd_msnd_dsp_halt);


पूर्णांक snd_msnd_DARQ(काष्ठा snd_msnd *chip, पूर्णांक bank)
अणु
	पूर्णांक /*size, n,*/ समयout = 3;
	u16 wTmp;
	/* व्योम *DAQD; */

	/* Increment the tail and check क्रम queue wrap */
	wTmp = पढ़ोw(chip->DARQ + JQS_wTail) + PCTODSP_OFFSET(DAQDS__size);
	अगर (wTmp > पढ़ोw(chip->DARQ + JQS_wSize))
		wTmp = 0;
	जबतक (wTmp == पढ़ोw(chip->DARQ + JQS_wHead) && समयout--)
		udelay(1);

	अगर (chip->capturePeriods == 2) अणु
		व्योम __iomem *pDAQ = chip->mappedbase + DARQ_DATA_BUFF +
			     bank * DAQDS__size + DAQDS_wStart;
		अचिन्हित लघु offset = 0x3000 + chip->capturePeriodBytes;

		अगर (पढ़ोw(pDAQ) != PCTODSP_BASED(0x3000))
			offset = 0x3000;
		ग_लिखोw(PCTODSP_BASED(offset), pDAQ);
	पूर्ण

	ग_लिखोw(wTmp, chip->DARQ + JQS_wTail);

#अगर 0
	/* Get our digital audio queue काष्ठा */
	DAQD = bank * DAQDS__size + chip->mappedbase + DARQ_DATA_BUFF;

	/* Get length of data */
	size = पढ़ोw(DAQD + DAQDS_wSize);

	/* Read data from the head (unरक्षित bank 1 access okay
	   since this is only called inside an पूर्णांकerrupt) */
	outb(HPBLKSEL_1, chip->io + HP_BLKS);
	n = msnd_fअगरo_ग_लिखो(&chip->DARF,
			    (अक्षर *)(chip->base + bank * DAR_BUFF_SIZE),
			    size, 0);
	अगर (n <= 0) अणु
		outb(HPBLKSEL_0, chip->io + HP_BLKS);
		वापस n;
	पूर्ण
	outb(HPBLKSEL_0, chip->io + HP_BLKS);
#पूर्ण_अगर

	वापस 1;
पूर्ण
EXPORT_SYMBOL(snd_msnd_DARQ);

पूर्णांक snd_msnd_DAPQ(काष्ठा snd_msnd *chip, पूर्णांक start)
अणु
	u16	DAPQ_tail;
	पूर्णांक	protect = start, nbanks = 0;
	व्योम	__iomem *DAQD;
	अटल पूर्णांक play_banks_submitted;
	/* अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&chip->lock, flags); not necessary */

	DAPQ_tail = पढ़ोw(chip->DAPQ + JQS_wTail);
	जबतक (DAPQ_tail != पढ़ोw(chip->DAPQ + JQS_wHead) || start) अणु
		पूर्णांक bank_num = DAPQ_tail / PCTODSP_OFFSET(DAQDS__size);

		अगर (start) अणु
			start = 0;
			play_banks_submitted = 0;
		पूर्ण

		/* Get our digital audio queue काष्ठा */
		DAQD = bank_num * DAQDS__size + chip->mappedbase +
			DAPQ_DATA_BUFF;

		/* Write size of this bank */
		ग_लिखोw(chip->play_period_bytes, DAQD + DAQDS_wSize);
		अगर (play_banks_submitted < 3)
			++play_banks_submitted;
		अन्यथा अगर (chip->playPeriods == 2) अणु
			अचिन्हित लघु offset = chip->play_period_bytes;

			अगर (पढ़ोw(DAQD + DAQDS_wStart) != PCTODSP_BASED(0x0))
				offset = 0;

			ग_लिखोw(PCTODSP_BASED(offset), DAQD + DAQDS_wStart);
		पूर्ण
		++nbanks;

		/* Then advance the tail */
		/*
		अगर (protect)
			snd_prपूर्णांकd(KERN_INFO "B %X %lX\n",
				   bank_num, xसमय.tv_usec);
		*/

		DAPQ_tail = (++bank_num % 3) * PCTODSP_OFFSET(DAQDS__size);
		ग_लिखोw(DAPQ_tail, chip->DAPQ + JQS_wTail);
		/* Tell the DSP to play the bank */
		snd_msnd_send_dsp_cmd(chip, HDEX_PLAY_START);
		अगर (protect)
			अगर (2 == bank_num)
				अवरोध;
	पूर्ण
	/*
	अगर (protect)
		snd_prपूर्णांकd(KERN_INFO "%lX\n", xसमय.tv_usec);
	*/
	/* spin_unlock_irqrestore(&chip->lock, flags); not necessary */
	वापस nbanks;
पूर्ण
EXPORT_SYMBOL(snd_msnd_DAPQ);

अटल व्योम snd_msnd_play_reset_queue(काष्ठा snd_msnd *chip,
				      अचिन्हित पूर्णांक pcm_periods,
				      अचिन्हित पूर्णांक pcm_count)
अणु
	पूर्णांक	n;
	व्योम	__iomem *pDAQ = chip->mappedbase + DAPQ_DATA_BUFF;

	chip->last_playbank = -1;
	chip->playLimit = pcm_count * (pcm_periods - 1);
	chip->playPeriods = pcm_periods;
	ग_लिखोw(PCTODSP_OFFSET(0 * DAQDS__size), chip->DAPQ + JQS_wHead);
	ग_लिखोw(PCTODSP_OFFSET(0 * DAQDS__size), chip->DAPQ + JQS_wTail);

	chip->play_period_bytes = pcm_count;

	क्रम (n = 0; n < pcm_periods; ++n, pDAQ += DAQDS__size) अणु
		ग_लिखोw(PCTODSP_BASED((u32)(pcm_count * n)),
			pDAQ + DAQDS_wStart);
		ग_लिखोw(0, pDAQ + DAQDS_wSize);
		ग_लिखोw(1, pDAQ + DAQDS_wFormat);
		ग_लिखोw(chip->play_sample_size, pDAQ + DAQDS_wSampleSize);
		ग_लिखोw(chip->play_channels, pDAQ + DAQDS_wChannels);
		ग_लिखोw(chip->play_sample_rate, pDAQ + DAQDS_wSampleRate);
		ग_लिखोw(HIMT_PLAY_DONE * 0x100 + n, pDAQ + DAQDS_wIntMsg);
		ग_लिखोw(n, pDAQ + DAQDS_wFlags);
	पूर्ण
पूर्ण

अटल व्योम snd_msnd_capture_reset_queue(काष्ठा snd_msnd *chip,
					 अचिन्हित पूर्णांक pcm_periods,
					 अचिन्हित पूर्णांक pcm_count)
अणु
	पूर्णांक		n;
	व्योम		__iomem *pDAQ;
	/* अचिन्हित दीर्घ	flags; */

	/* snd_msnd_init_queue(chip->DARQ, DARQ_DATA_BUFF, DARQ_BUFF_SIZE); */

	chip->last_recbank = 2;
	chip->captureLimit = pcm_count * (pcm_periods - 1);
	chip->capturePeriods = pcm_periods;
	ग_लिखोw(PCTODSP_OFFSET(0 * DAQDS__size), chip->DARQ + JQS_wHead);
	ग_लिखोw(PCTODSP_OFFSET(chip->last_recbank * DAQDS__size),
		chip->DARQ + JQS_wTail);

#अगर 0 /* Critical section: bank 1 access. this is how the OSS driver करोes it:*/
	spin_lock_irqsave(&chip->lock, flags);
	outb(HPBLKSEL_1, chip->io + HP_BLKS);
	स_रखो_io(chip->mappedbase, 0, DAR_BUFF_SIZE * 3);
	outb(HPBLKSEL_0, chip->io + HP_BLKS);
	spin_unlock_irqrestore(&chip->lock, flags);
#पूर्ण_अगर

	chip->capturePeriodBytes = pcm_count;
	snd_prपूर्णांकdd("snd_msnd_capture_reset_queue() %i\n", pcm_count);

	pDAQ = chip->mappedbase + DARQ_DATA_BUFF;

	क्रम (n = 0; n < pcm_periods; ++n, pDAQ += DAQDS__size) अणु
		u32 पंचांगp = pcm_count * n;

		ग_लिखोw(PCTODSP_BASED(पंचांगp + 0x3000), pDAQ + DAQDS_wStart);
		ग_लिखोw(pcm_count, pDAQ + DAQDS_wSize);
		ग_लिखोw(1, pDAQ + DAQDS_wFormat);
		ग_लिखोw(chip->capture_sample_size, pDAQ + DAQDS_wSampleSize);
		ग_लिखोw(chip->capture_channels, pDAQ + DAQDS_wChannels);
		ग_लिखोw(chip->capture_sample_rate, pDAQ + DAQDS_wSampleRate);
		ग_लिखोw(HIMT_RECORD_DONE * 0x100 + n, pDAQ + DAQDS_wIntMsg);
		ग_लिखोw(n, pDAQ + DAQDS_wFlags);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_msnd_playback = अणु
	.info =			SNDRV_PCM_INFO_MMAP |
				SNDRV_PCM_INFO_INTERLEAVED |
				SNDRV_PCM_INFO_MMAP_VALID |
				SNDRV_PCM_INFO_BATCH,
	.क्रमmats =		SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_8000_48000,
	.rate_min =		8000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	0x3000,
	.period_bytes_min =	0x40,
	.period_bytes_max =	0x1800,
	.periods_min =		2,
	.periods_max =		3,
	.fअगरo_size =		0,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_msnd_capture = अणु
	.info =			SNDRV_PCM_INFO_MMAP |
				SNDRV_PCM_INFO_INTERLEAVED |
				SNDRV_PCM_INFO_MMAP_VALID |
				SNDRV_PCM_INFO_BATCH,
	.क्रमmats =		SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_8000_48000,
	.rate_min =		8000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	0x3000,
	.period_bytes_min =	0x40,
	.period_bytes_max =	0x1800,
	.periods_min =		2,
	.periods_max =		3,
	.fअगरo_size =		0,
पूर्ण;


अटल पूर्णांक snd_msnd_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_msnd *chip = snd_pcm_substream_chip(substream);

	set_bit(F_AUDIO_WRITE_INUSE, &chip->flags);
	clear_bit(F_WRITING, &chip->flags);
	snd_msnd_enable_irq(chip);

	runसमय->dma_area = (__क्रमce व्योम *)chip->mappedbase;
	runसमय->dma_bytes = 0x3000;

	chip->playback_substream = substream;
	runसमय->hw = snd_msnd_playback;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_msnd_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_msnd *chip = snd_pcm_substream_chip(substream);

	snd_msnd_disable_irq(chip);
	clear_bit(F_AUDIO_WRITE_INUSE, &chip->flags);
	वापस 0;
पूर्ण


अटल पूर्णांक snd_msnd_playback_hw_params(काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_pcm_hw_params *params)
अणु
	पूर्णांक	i;
	काष्ठा snd_msnd *chip = snd_pcm_substream_chip(substream);
	व्योम	__iomem *pDAQ =	chip->mappedbase + DAPQ_DATA_BUFF;

	chip->play_sample_size = snd_pcm_क्रमmat_width(params_क्रमmat(params));
	chip->play_channels = params_channels(params);
	chip->play_sample_rate = params_rate(params);

	क्रम (i = 0; i < 3; ++i, pDAQ += DAQDS__size) अणु
		ग_लिखोw(chip->play_sample_size, pDAQ + DAQDS_wSampleSize);
		ग_लिखोw(chip->play_channels, pDAQ + DAQDS_wChannels);
		ग_लिखोw(chip->play_sample_rate, pDAQ + DAQDS_wSampleRate);
	पूर्ण
	/* करोnt करो this here:
	 * snd_msnd_calibrate_adc(chip->play_sample_rate);
	 */

	वापस 0;
पूर्ण

अटल पूर्णांक snd_msnd_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_msnd *chip = snd_pcm_substream_chip(substream);
	अचिन्हित पूर्णांक pcm_size = snd_pcm_lib_buffer_bytes(substream);
	अचिन्हित पूर्णांक pcm_count = snd_pcm_lib_period_bytes(substream);
	अचिन्हित पूर्णांक pcm_periods = pcm_size / pcm_count;

	snd_msnd_play_reset_queue(chip, pcm_periods, pcm_count);
	chip->playDMAPos = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_msnd_playback_trigger(काष्ठा snd_pcm_substream *substream,
				     पूर्णांक cmd)
अणु
	काष्ठा snd_msnd *chip = snd_pcm_substream_chip(substream);
	पूर्णांक	result = 0;

	अगर (cmd == SNDRV_PCM_TRIGGER_START) अणु
		snd_prपूर्णांकdd("snd_msnd_playback_trigger(START)\n");
		chip->banksPlayed = 0;
		set_bit(F_WRITING, &chip->flags);
		snd_msnd_DAPQ(chip, 1);
	पूर्ण अन्यथा अगर (cmd == SNDRV_PCM_TRIGGER_STOP) अणु
		snd_prपूर्णांकdd("snd_msnd_playback_trigger(STop)\n");
		/* पूर्णांकerrupt diagnostic, comment this out later */
		clear_bit(F_WRITING, &chip->flags);
		snd_msnd_send_dsp_cmd(chip, HDEX_PLAY_STOP);
	पूर्ण अन्यथा अणु
		snd_prपूर्णांकd(KERN_ERR "snd_msnd_playback_trigger(?????)\n");
		result = -EINVAL;
	पूर्ण

	snd_prपूर्णांकdd("snd_msnd_playback_trigger() ENDE\n");
	वापस result;
पूर्ण

अटल snd_pcm_uframes_t
snd_msnd_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_msnd *chip = snd_pcm_substream_chip(substream);

	वापस bytes_to_frames(substream->runसमय, chip->playDMAPos);
पूर्ण


अटल स्थिर काष्ठा snd_pcm_ops snd_msnd_playback_ops = अणु
	.खोलो =		snd_msnd_playback_खोलो,
	.बंद =	snd_msnd_playback_बंद,
	.hw_params =	snd_msnd_playback_hw_params,
	.prepare =	snd_msnd_playback_prepare,
	.trigger =	snd_msnd_playback_trigger,
	.poपूर्णांकer =	snd_msnd_playback_poपूर्णांकer,
पूर्ण;

अटल पूर्णांक snd_msnd_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_msnd *chip = snd_pcm_substream_chip(substream);

	set_bit(F_AUDIO_READ_INUSE, &chip->flags);
	snd_msnd_enable_irq(chip);
	runसमय->dma_area = (__क्रमce व्योम *)chip->mappedbase + 0x3000;
	runसमय->dma_bytes = 0x3000;
	स_रखो(runसमय->dma_area, 0, runसमय->dma_bytes);
	chip->capture_substream = substream;
	runसमय->hw = snd_msnd_capture;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_msnd_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_msnd *chip = snd_pcm_substream_chip(substream);

	snd_msnd_disable_irq(chip);
	clear_bit(F_AUDIO_READ_INUSE, &chip->flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_msnd_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_msnd *chip = snd_pcm_substream_chip(substream);
	अचिन्हित पूर्णांक pcm_size = snd_pcm_lib_buffer_bytes(substream);
	अचिन्हित पूर्णांक pcm_count = snd_pcm_lib_period_bytes(substream);
	अचिन्हित पूर्णांक pcm_periods = pcm_size / pcm_count;

	snd_msnd_capture_reset_queue(chip, pcm_periods, pcm_count);
	chip->captureDMAPos = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_msnd_capture_trigger(काष्ठा snd_pcm_substream *substream,
				    पूर्णांक cmd)
अणु
	काष्ठा snd_msnd *chip = snd_pcm_substream_chip(substream);

	अगर (cmd == SNDRV_PCM_TRIGGER_START) अणु
		chip->last_recbank = -1;
		set_bit(F_READING, &chip->flags);
		अगर (snd_msnd_send_dsp_cmd(chip, HDEX_RECORD_START) == 0)
			वापस 0;

		clear_bit(F_READING, &chip->flags);
	पूर्ण अन्यथा अगर (cmd == SNDRV_PCM_TRIGGER_STOP) अणु
		clear_bit(F_READING, &chip->flags);
		snd_msnd_send_dsp_cmd(chip, HDEX_RECORD_STOP);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण


अटल snd_pcm_uframes_t
snd_msnd_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_msnd *chip = snd_pcm_substream_chip(substream);

	वापस bytes_to_frames(runसमय, chip->captureDMAPos);
पूर्ण


अटल पूर्णांक snd_msnd_capture_hw_params(काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_pcm_hw_params *params)
अणु
	पूर्णांक		i;
	काष्ठा snd_msnd *chip = snd_pcm_substream_chip(substream);
	व्योम		__iomem *pDAQ = chip->mappedbase + DARQ_DATA_BUFF;

	chip->capture_sample_size = snd_pcm_क्रमmat_width(params_क्रमmat(params));
	chip->capture_channels = params_channels(params);
	chip->capture_sample_rate = params_rate(params);

	क्रम (i = 0; i < 3; ++i, pDAQ += DAQDS__size) अणु
		ग_लिखोw(chip->capture_sample_size, pDAQ + DAQDS_wSampleSize);
		ग_लिखोw(chip->capture_channels, pDAQ + DAQDS_wChannels);
		ग_लिखोw(chip->capture_sample_rate, pDAQ + DAQDS_wSampleRate);
	पूर्ण
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा snd_pcm_ops snd_msnd_capture_ops = अणु
	.खोलो =		snd_msnd_capture_खोलो,
	.बंद =	snd_msnd_capture_बंद,
	.hw_params =	snd_msnd_capture_hw_params,
	.prepare =	snd_msnd_capture_prepare,
	.trigger =	snd_msnd_capture_trigger,
	.poपूर्णांकer =	snd_msnd_capture_poपूर्णांकer,
पूर्ण;


पूर्णांक snd_msnd_pcm(काष्ठा snd_card *card, पूर्णांक device)
अणु
	काष्ठा snd_msnd *chip = card->निजी_data;
	काष्ठा snd_pcm	*pcm;
	पूर्णांक err;

	err = snd_pcm_new(card, "MSNDPINNACLE", device, 1, 1, &pcm);
	अगर (err < 0)
		वापस err;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_msnd_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_msnd_capture_ops);

	pcm->निजी_data = chip;
	म_नकल(pcm->name, "Hurricane");

	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_msnd_pcm);

MODULE_DESCRIPTION("Common routines for Turtle Beach Multisound drivers");
MODULE_LICENSE("GPL");

