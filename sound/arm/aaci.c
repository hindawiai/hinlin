<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/sound/arm/aaci.c - ARM PrimeCell AACI PL041 driver
 *
 *  Copyright (C) 2003 Deep Blue Solutions Ltd, All Rights Reserved.
 *
 *  Documentation: ARM DDI 0173B
 */
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/err.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/पन.स>

#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>

#समावेश "aaci.h"

#घोषणा DRIVER_NAME	"aaci-pl041"

#घोषणा FRAME_PERIOD_US	21

/*
 * PM support is not complete.  Turn it off.
 */
#अघोषित CONFIG_PM

अटल व्योम aaci_ac97_select_codec(काष्ठा aaci *aaci, काष्ठा snd_ac97 *ac97)
अणु
	u32 v, मुख्यcr = aaci->मुख्यcr | MAINCR_SCRA(ac97->num);

	/*
	 * Ensure that the slot 1/2 RX रेजिस्टरs are empty.
	 */
	v = पढ़ोl(aaci->base + AACI_SLFR);
	अगर (v & SLFR_2RXV)
		पढ़ोl(aaci->base + AACI_SL2RX);
	अगर (v & SLFR_1RXV)
		पढ़ोl(aaci->base + AACI_SL1RX);

	अगर (मुख्यcr != पढ़ोl(aaci->base + AACI_MAINCR)) अणु
		ग_लिखोl(मुख्यcr, aaci->base + AACI_MAINCR);
		पढ़ोl(aaci->base + AACI_MAINCR);
		udelay(1);
	पूर्ण
पूर्ण

/*
 * P29:
 *  The recommended use of programming the बाह्यal codec through slot 1
 *  and slot 2 data is to use the channels during setup routines and the
 *  slot रेजिस्टर at any other समय.  The data written पूर्णांकo slot 1, slot 2
 *  and slot 12 रेजिस्टरs is transmitted only when their corresponding
 *  SI1TxEn, SI2TxEn and SI12TxEn bits are set in the AACI_MAINCR
 *  रेजिस्टर.
 */
अटल व्योम aaci_ac97_ग_लिखो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg,
			    अचिन्हित लघु val)
अणु
	काष्ठा aaci *aaci = ac97->निजी_data;
	पूर्णांक समयout;
	u32 v;

	अगर (ac97->num >= 4)
		वापस;

	mutex_lock(&aaci->ac97_sem);

	aaci_ac97_select_codec(aaci, ac97);

	/*
	 * P54: You must ensure that AACI_SL2TX is always written
	 * to, अगर required, beक्रमe data is written to AACI_SL1TX.
	 */
	ग_लिखोl(val << 4, aaci->base + AACI_SL2TX);
	ग_लिखोl(reg << 12, aaci->base + AACI_SL1TX);

	/* Initially, रुको one frame period */
	udelay(FRAME_PERIOD_US);

	/* And then रुको an additional eight frame periods क्रम it to be sent */
	समयout = FRAME_PERIOD_US * 8;
	करो अणु
		udelay(1);
		v = पढ़ोl(aaci->base + AACI_SLFR);
	पूर्ण जबतक ((v & (SLFR_1TXB|SLFR_2TXB)) && --समयout);

	अगर (v & (SLFR_1TXB|SLFR_2TXB))
		dev_err(&aaci->dev->dev,
			"timeout waiting for write to complete\n");

	mutex_unlock(&aaci->ac97_sem);
पूर्ण

/*
 * Read an AC'97 रेजिस्टर.
 */
अटल अचिन्हित लघु aaci_ac97_पढ़ो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg)
अणु
	काष्ठा aaci *aaci = ac97->निजी_data;
	पूर्णांक समयout, retries = 10;
	u32 v;

	अगर (ac97->num >= 4)
		वापस ~0;

	mutex_lock(&aaci->ac97_sem);

	aaci_ac97_select_codec(aaci, ac97);

	/*
	 * Write the रेजिस्टर address to slot 1.
	 */
	ग_लिखोl((reg << 12) | (1 << 19), aaci->base + AACI_SL1TX);

	/* Initially, रुको one frame period */
	udelay(FRAME_PERIOD_US);

	/* And then रुको an additional eight frame periods क्रम it to be sent */
	समयout = FRAME_PERIOD_US * 8;
	करो अणु
		udelay(1);
		v = पढ़ोl(aaci->base + AACI_SLFR);
	पूर्ण जबतक ((v & SLFR_1TXB) && --समयout);

	अगर (v & SLFR_1TXB) अणु
		dev_err(&aaci->dev->dev, "timeout on slot 1 TX busy\n");
		v = ~0;
		जाओ out;
	पूर्ण

	/* Now रुको क्रम the response frame */
	udelay(FRAME_PERIOD_US);

	/* And then रुको an additional eight frame periods क्रम data */
	समयout = FRAME_PERIOD_US * 8;
	करो अणु
		udelay(1);
		cond_resched();
		v = पढ़ोl(aaci->base + AACI_SLFR) & (SLFR_1RXV|SLFR_2RXV);
	पूर्ण जबतक ((v != (SLFR_1RXV|SLFR_2RXV)) && --समयout);

	अगर (v != (SLFR_1RXV|SLFR_2RXV)) अणु
		dev_err(&aaci->dev->dev, "timeout on RX valid\n");
		v = ~0;
		जाओ out;
	पूर्ण

	करो अणु
		v = पढ़ोl(aaci->base + AACI_SL1RX) >> 12;
		अगर (v == reg) अणु
			v = पढ़ोl(aaci->base + AACI_SL2RX) >> 4;
			अवरोध;
		पूर्ण अन्यथा अगर (--retries) अणु
			dev_warn(&aaci->dev->dev,
				 "ac97 read back fail.  retry\n");
			जारी;
		पूर्ण अन्यथा अणु
			dev_warn(&aaci->dev->dev,
				"wrong ac97 register read back (%x != %x)\n",
				v, reg);
			v = ~0;
		पूर्ण
	पूर्ण जबतक (retries);
 out:
	mutex_unlock(&aaci->ac97_sem);
	वापस v;
पूर्ण

अटल अंतरभूत व्योम
aaci_chan_रुको_पढ़ोy(काष्ठा aaci_runसमय *aacirun, अचिन्हित दीर्घ mask)
अणु
	u32 val;
	पूर्णांक समयout = 5000;

	करो अणु
		udelay(1);
		val = पढ़ोl(aacirun->base + AACI_SR);
	पूर्ण जबतक (val & mask && समयout--);
पूर्ण



/*
 * Interrupt support.
 */
अटल व्योम aaci_fअगरo_irq(काष्ठा aaci *aaci, पूर्णांक channel, u32 mask)
अणु
	अगर (mask & ISR_ORINTR) अणु
		dev_warn(&aaci->dev->dev, "RX overrun on chan %d\n", channel);
		ग_लिखोl(ICLR_RXOEC1 << channel, aaci->base + AACI_INTCLR);
	पूर्ण

	अगर (mask & ISR_RXTOINTR) अणु
		dev_warn(&aaci->dev->dev, "RX timeout on chan %d\n", channel);
		ग_लिखोl(ICLR_RXTOFEC1 << channel, aaci->base + AACI_INTCLR);
	पूर्ण

	अगर (mask & ISR_RXINTR) अणु
		काष्ठा aaci_runसमय *aacirun = &aaci->capture;
		bool period_elapsed = false;
		व्योम *ptr;

		अगर (!aacirun->substream || !aacirun->start) अणु
			dev_warn(&aaci->dev->dev, "RX interrupt???\n");
			ग_लिखोl(0, aacirun->base + AACI_IE);
			वापस;
		पूर्ण

		spin_lock(&aacirun->lock);

		ptr = aacirun->ptr;
		करो अणु
			अचिन्हित पूर्णांक len = aacirun->fअगरo_bytes;
			u32 val;

			अगर (aacirun->bytes <= 0) अणु
				aacirun->bytes += aacirun->period;
				period_elapsed = true;
			पूर्ण
			अगर (!(aacirun->cr & CR_EN))
				अवरोध;

			val = पढ़ोl(aacirun->base + AACI_SR);
			अगर (!(val & SR_RXHF))
				अवरोध;
			अगर (!(val & SR_RXFF))
				len >>= 1;

			aacirun->bytes -= len;

			/* पढ़ोing 16 bytes at a समय */
			क्रम( ; len > 0; len -= 16) अणु
				यंत्र(
					"ldmia	%1, {r0, r1, r2, r3}\n\t"
					"stmia	%0!, {r0, r1, r2, r3}"
					: "+r" (ptr)
					: "r" (aacirun->fअगरo)
					: "r0", "r1", "r2", "r3", "cc");

				अगर (ptr >= aacirun->end)
					ptr = aacirun->start;
			पूर्ण
		पूर्ण जबतक(1);

		aacirun->ptr = ptr;

		spin_unlock(&aacirun->lock);

		अगर (period_elapsed)
			snd_pcm_period_elapsed(aacirun->substream);
	पूर्ण

	अगर (mask & ISR_URINTR) अणु
		dev_dbg(&aaci->dev->dev, "TX underrun on chan %d\n", channel);
		ग_लिखोl(ICLR_TXUEC1 << channel, aaci->base + AACI_INTCLR);
	पूर्ण

	अगर (mask & ISR_TXINTR) अणु
		काष्ठा aaci_runसमय *aacirun = &aaci->playback;
		bool period_elapsed = false;
		व्योम *ptr;

		अगर (!aacirun->substream || !aacirun->start) अणु
			dev_warn(&aaci->dev->dev, "TX interrupt???\n");
			ग_लिखोl(0, aacirun->base + AACI_IE);
			वापस;
		पूर्ण

		spin_lock(&aacirun->lock);

		ptr = aacirun->ptr;
		करो अणु
			अचिन्हित पूर्णांक len = aacirun->fअगरo_bytes;
			u32 val;

			अगर (aacirun->bytes <= 0) अणु
				aacirun->bytes += aacirun->period;
				period_elapsed = true;
			पूर्ण
			अगर (!(aacirun->cr & CR_EN))
				अवरोध;

			val = पढ़ोl(aacirun->base + AACI_SR);
			अगर (!(val & SR_TXHE))
				अवरोध;
			अगर (!(val & SR_TXFE))
				len >>= 1;

			aacirun->bytes -= len;

			/* writing 16 bytes at a समय */
			क्रम ( ; len > 0; len -= 16) अणु
				यंत्र(
					"ldmia	%0!, {r0, r1, r2, r3}\n\t"
					"stmia	%1, {r0, r1, r2, r3}"
					: "+r" (ptr)
					: "r" (aacirun->fअगरo)
					: "r0", "r1", "r2", "r3", "cc");

				अगर (ptr >= aacirun->end)
					ptr = aacirun->start;
			पूर्ण
		पूर्ण जबतक (1);

		aacirun->ptr = ptr;

		spin_unlock(&aacirun->lock);

		अगर (period_elapsed)
			snd_pcm_period_elapsed(aacirun->substream);
	पूर्ण
पूर्ण

अटल irqवापस_t aaci_irq(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा aaci *aaci = devid;
	u32 mask;
	पूर्णांक i;

	mask = पढ़ोl(aaci->base + AACI_ALLINTS);
	अगर (mask) अणु
		u32 m = mask;
		क्रम (i = 0; i < 4; i++, m >>= 7) अणु
			अगर (m & 0x7f) अणु
				aaci_fअगरo_irq(aaci, i, m);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस mask ? IRQ_HANDLED : IRQ_NONE;
पूर्ण



/*
 * ALSA support.
 */
अटल स्थिर काष्ठा snd_pcm_hardware aaci_hw_info = अणु
	.info			= SNDRV_PCM_INFO_MMAP |
				  SNDRV_PCM_INFO_MMAP_VALID |
				  SNDRV_PCM_INFO_INTERLEAVED |
				  SNDRV_PCM_INFO_BLOCK_TRANSFER |
				  SNDRV_PCM_INFO_RESUME,

	/*
	 * ALSA करोesn't support 18-bit or 20-bit packed पूर्णांकo 32-bit
	 * words.  It also करोesn't support 12-bit at all.
	 */
	.क्रमmats		= SNDRV_PCM_FMTBIT_S16_LE,

	/* rates are setup from the AC'97 codec */
	.channels_min		= 2,
	.channels_max		= 2,
	.buffer_bytes_max	= 64 * 1024,
	.period_bytes_min	= 256,
	.period_bytes_max	= PAGE_SIZE,
	.periods_min		= 4,
	.periods_max		= PAGE_SIZE / 16,
पूर्ण;

/*
 * We can support two and four channel audio.  Unक्रमtunately
 * six channel audio requires a non-standard channel ordering:
 *   2 -> FL(3), FR(4)
 *   4 -> FL(3), FR(4), SL(7), SR(8)
 *   6 -> FL(3), FR(4), SL(7), SR(8), C(6), LFE(9) (required)
 *        FL(3), FR(4), C(6), SL(7), SR(8), LFE(9) (actual)
 * This requires an ALSA configuration file to correct.
 */
अटल पूर्णांक aaci_rule_channels(काष्ठा snd_pcm_hw_params *p,
	काष्ठा snd_pcm_hw_rule *rule)
अणु
	अटल स्थिर अचिन्हित पूर्णांक channel_list[] = अणु 2, 4, 6 पूर्ण;
	काष्ठा aaci *aaci = rule->निजी;
	अचिन्हित पूर्णांक mask = 1 << 0, slots;

	/* pcms[0] is the our 5.1 PCM instance. */
	slots = aaci->ac97_bus->pcms[0].r[0].slots;
	अगर (slots & (1 << AC97_SLOT_PCM_SLEFT)) अणु
		mask |= 1 << 1;
		अगर (slots & (1 << AC97_SLOT_LFE))
			mask |= 1 << 2;
	पूर्ण

	वापस snd_पूर्णांकerval_list(hw_param_पूर्णांकerval(p, rule->var),
				 ARRAY_SIZE(channel_list), channel_list, mask);
पूर्ण

अटल पूर्णांक aaci_pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा aaci *aaci = substream->निजी_data;
	काष्ठा aaci_runसमय *aacirun;
	पूर्णांक ret = 0;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		aacirun = &aaci->playback;
	पूर्ण अन्यथा अणु
		aacirun = &aaci->capture;
	पूर्ण

	aacirun->substream = substream;
	runसमय->निजी_data = aacirun;
	runसमय->hw = aaci_hw_info;
	runसमय->hw.rates = aacirun->pcm->rates;
	snd_pcm_limit_hw_rates(runसमय);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		runसमय->hw.channels_max = 6;

		/* Add rule describing channel dependency. */
		ret = snd_pcm_hw_rule_add(substream->runसमय, 0,
					  SNDRV_PCM_HW_PARAM_CHANNELS,
					  aaci_rule_channels, aaci,
					  SNDRV_PCM_HW_PARAM_CHANNELS, -1);
		अगर (ret)
			वापस ret;

		अगर (aacirun->pcm->r[1].slots)
			snd_ac97_pcm_द्विगुन_rate_rules(runसमय);
	पूर्ण

	/*
	 * ALSA wants the byte-size of the FIFOs.  As we only support
	 * 16-bit samples, this is twice the FIFO depth irrespective
	 * of whether it's in compact mode or not.
	 */
	runसमय->hw.fअगरo_size = aaci->fअगरo_depth * 2;

	mutex_lock(&aaci->irq_lock);
	अगर (!aaci->users++) अणु
		ret = request_irq(aaci->dev->irq[0], aaci_irq,
			   IRQF_SHARED, DRIVER_NAME, aaci);
		अगर (ret != 0)
			aaci->users--;
	पूर्ण
	mutex_unlock(&aaci->irq_lock);

	वापस ret;
पूर्ण


/*
 * Common ALSA stuff
 */
अटल पूर्णांक aaci_pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा aaci *aaci = substream->निजी_data;
	काष्ठा aaci_runसमय *aacirun = substream->runसमय->निजी_data;

	WARN_ON(aacirun->cr & CR_EN);

	aacirun->substream = शून्य;

	mutex_lock(&aaci->irq_lock);
	अगर (!--aaci->users)
		मुक्त_irq(aaci->dev->irq[0], aaci);
	mutex_unlock(&aaci->irq_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक aaci_pcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा aaci_runसमय *aacirun = substream->runसमय->निजी_data;

	/*
	 * This must not be called with the device enabled.
	 */
	WARN_ON(aacirun->cr & CR_EN);

	अगर (aacirun->pcm_खोलो)
		snd_ac97_pcm_बंद(aacirun->pcm);
	aacirun->pcm_खोलो = 0;

	वापस 0;
पूर्ण

/* Channel to slot mask */
अटल स्थिर u32 channels_to_sloपंचांगask[] = अणु
	[2] = CR_SL3 | CR_SL4,
	[4] = CR_SL3 | CR_SL4 | CR_SL7 | CR_SL8,
	[6] = CR_SL3 | CR_SL4 | CR_SL7 | CR_SL8 | CR_SL6 | CR_SL9,
पूर्ण;

अटल पूर्णांक aaci_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा aaci_runसमय *aacirun = substream->runसमय->निजी_data;
	काष्ठा aaci *aaci = substream->निजी_data;
	अचिन्हित पूर्णांक channels = params_channels(params);
	अचिन्हित पूर्णांक rate = params_rate(params);
	पूर्णांक dbl = rate > 48000;
	पूर्णांक err;

	aaci_pcm_hw_मुक्त(substream);
	अगर (aacirun->pcm_खोलो) अणु
		snd_ac97_pcm_बंद(aacirun->pcm);
		aacirun->pcm_खोलो = 0;
	पूर्ण

	/* channels is alपढ़ोy limited to 2, 4, or 6 by aaci_rule_channels */
	अगर (dbl && channels != 2)
		वापस -EINVAL;

	err = snd_ac97_pcm_खोलो(aacirun->pcm, rate, channels,
				aacirun->pcm->r[dbl].slots);

	aacirun->pcm_खोलो = err == 0;
	aacirun->cr = CR_FEN | CR_COMPACT | CR_SZ16;
	aacirun->cr |= channels_to_sloपंचांगask[channels + dbl * 2];

	/*
	 * fअगरo_bytes is the number of bytes we transfer to/from
	 * the FIFO, including padding.  So that's x4.  As we're
	 * in compact mode, the FIFO is half the size.
	 */
	aacirun->fअगरo_bytes = aaci->fअगरo_depth * 4 / 2;

	वापस err;
पूर्ण

अटल पूर्णांक aaci_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा aaci_runसमय *aacirun = runसमय->निजी_data;

	aacirun->period	= snd_pcm_lib_period_bytes(substream);
	aacirun->start	= runसमय->dma_area;
	aacirun->end	= aacirun->start + snd_pcm_lib_buffer_bytes(substream);
	aacirun->ptr	= aacirun->start;
	aacirun->bytes	= aacirun->period;

	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t aaci_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा aaci_runसमय *aacirun = runसमय->निजी_data;
	sमाप_प्रकार bytes = aacirun->ptr - aacirun->start;

	वापस bytes_to_frames(runसमय, bytes);
पूर्ण


/*
 * Playback specअगरic ALSA stuff
 */
अटल व्योम aaci_pcm_playback_stop(काष्ठा aaci_runसमय *aacirun)
अणु
	u32 ie;

	ie = पढ़ोl(aacirun->base + AACI_IE);
	ie &= ~(IE_URIE|IE_TXIE);
	ग_लिखोl(ie, aacirun->base + AACI_IE);
	aacirun->cr &= ~CR_EN;
	aaci_chan_रुको_पढ़ोy(aacirun, SR_TXB);
	ग_लिखोl(aacirun->cr, aacirun->base + AACI_TXCR);
पूर्ण

अटल व्योम aaci_pcm_playback_start(काष्ठा aaci_runसमय *aacirun)
अणु
	u32 ie;

	aaci_chan_रुको_पढ़ोy(aacirun, SR_TXB);
	aacirun->cr |= CR_EN;

	ie = पढ़ोl(aacirun->base + AACI_IE);
	ie |= IE_URIE | IE_TXIE;
	ग_लिखोl(ie, aacirun->base + AACI_IE);
	ग_लिखोl(aacirun->cr, aacirun->base + AACI_TXCR);
पूर्ण

अटल पूर्णांक aaci_pcm_playback_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा aaci_runसमय *aacirun = substream->runसमय->निजी_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&aacirun->lock, flags);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		aaci_pcm_playback_start(aacirun);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_RESUME:
		aaci_pcm_playback_start(aacirun);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
		aaci_pcm_playback_stop(aacirun);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		aaci_pcm_playback_stop(aacirun);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		अवरोध;

	शेष:
		ret = -EINVAL;
	पूर्ण

	spin_unlock_irqrestore(&aacirun->lock, flags);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops aaci_playback_ops = अणु
	.खोलो		= aaci_pcm_खोलो,
	.बंद		= aaci_pcm_बंद,
	.hw_params	= aaci_pcm_hw_params,
	.hw_मुक्त	= aaci_pcm_hw_मुक्त,
	.prepare	= aaci_pcm_prepare,
	.trigger	= aaci_pcm_playback_trigger,
	.poपूर्णांकer	= aaci_pcm_poपूर्णांकer,
पूर्ण;

अटल व्योम aaci_pcm_capture_stop(काष्ठा aaci_runसमय *aacirun)
अणु
	u32 ie;

	aaci_chan_रुको_पढ़ोy(aacirun, SR_RXB);

	ie = पढ़ोl(aacirun->base + AACI_IE);
	ie &= ~(IE_ORIE | IE_RXIE);
	ग_लिखोl(ie, aacirun->base+AACI_IE);

	aacirun->cr &= ~CR_EN;

	ग_लिखोl(aacirun->cr, aacirun->base + AACI_RXCR);
पूर्ण

अटल व्योम aaci_pcm_capture_start(काष्ठा aaci_runसमय *aacirun)
अणु
	u32 ie;

	aaci_chan_रुको_पढ़ोy(aacirun, SR_RXB);

#अगर_घोषित DEBUG
	/* RX Timeout value: bits 28:17 in RXCR */
	aacirun->cr |= 0xf << 17;
#पूर्ण_अगर

	aacirun->cr |= CR_EN;
	ग_लिखोl(aacirun->cr, aacirun->base + AACI_RXCR);

	ie = पढ़ोl(aacirun->base + AACI_IE);
	ie |= IE_ORIE |IE_RXIE; // overrun and rx पूर्णांकerrupt -- half full
	ग_लिखोl(ie, aacirun->base + AACI_IE);
पूर्ण

अटल पूर्णांक aaci_pcm_capture_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा aaci_runसमय *aacirun = substream->runसमय->निजी_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&aacirun->lock, flags);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		aaci_pcm_capture_start(aacirun);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_RESUME:
		aaci_pcm_capture_start(aacirun);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
		aaci_pcm_capture_stop(aacirun);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		aaci_pcm_capture_stop(aacirun);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		अवरोध;

	शेष:
		ret = -EINVAL;
	पूर्ण

	spin_unlock_irqrestore(&aacirun->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक aaci_pcm_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा aaci *aaci = substream->निजी_data;

	aaci_pcm_prepare(substream);

	/* allow changing of sample rate */
	aaci_ac97_ग_लिखो(aaci->ac97, AC97_EXTENDED_STATUS, 0x0001); /* VRA */
	aaci_ac97_ग_लिखो(aaci->ac97, AC97_PCM_LR_ADC_RATE, runसमय->rate);
	aaci_ac97_ग_लिखो(aaci->ac97, AC97_PCM_MIC_ADC_RATE, runसमय->rate);

	/* Record select: Mic: 0, Aux: 3, Line: 4 */
	aaci_ac97_ग_लिखो(aaci->ac97, AC97_REC_SEL, 0x0404);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops aaci_capture_ops = अणु
	.खोलो		= aaci_pcm_खोलो,
	.बंद		= aaci_pcm_बंद,
	.hw_params	= aaci_pcm_hw_params,
	.hw_मुक्त	= aaci_pcm_hw_मुक्त,
	.prepare	= aaci_pcm_capture_prepare,
	.trigger	= aaci_pcm_capture_trigger,
	.poपूर्णांकer	= aaci_pcm_poपूर्णांकer,
पूर्ण;

/*
 * Power Management.
 */
#अगर_घोषित CONFIG_PM
अटल पूर्णांक aaci_करो_suspend(काष्ठा snd_card *card)
अणु
	काष्ठा aaci *aaci = card->निजी_data;
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3cold);
	वापस 0;
पूर्ण

अटल पूर्णांक aaci_करो_resume(काष्ठा snd_card *card)
अणु
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण

अटल पूर्णांक aaci_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	वापस card ? aaci_करो_suspend(card) : 0;
पूर्ण

अटल पूर्णांक aaci_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	वापस card ? aaci_करो_resume(card) : 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(aaci_dev_pm_ops, aaci_suspend, aaci_resume);
#घोषणा AACI_DEV_PM_OPS (&aaci_dev_pm_ops)
#अन्यथा
#घोषणा AACI_DEV_PM_OPS शून्य
#पूर्ण_अगर


अटल स्थिर काष्ठा ac97_pcm ac97_defs[] = अणु
	[0] = अणु	/* Front PCM */
		.exclusive = 1,
		.r = अणु
			[0] = अणु
				.slots	= (1 << AC97_SLOT_PCM_LEFT) |
					  (1 << AC97_SLOT_PCM_RIGHT) |
					  (1 << AC97_SLOT_PCM_CENTER) |
					  (1 << AC97_SLOT_PCM_SLEFT) |
					  (1 << AC97_SLOT_PCM_SRIGHT) |
					  (1 << AC97_SLOT_LFE),
			पूर्ण,
			[1] = अणु
				.slots	= (1 << AC97_SLOT_PCM_LEFT) |
					  (1 << AC97_SLOT_PCM_RIGHT) |
					  (1 << AC97_SLOT_PCM_LEFT_0) |
					  (1 << AC97_SLOT_PCM_RIGHT_0),
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[1] = अणु	/* PCM in */
		.stream = 1,
		.exclusive = 1,
		.r = अणु
			[0] = अणु
				.slots	= (1 << AC97_SLOT_PCM_LEFT) |
					  (1 << AC97_SLOT_PCM_RIGHT),
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[2] = अणु	/* Mic in */
		.stream = 1,
		.exclusive = 1,
		.r = अणु
			[0] = अणु
				.slots	= (1 << AC97_SLOT_MIC),
			पूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_ac97_bus_ops aaci_bus_ops = अणु
	.ग_लिखो	= aaci_ac97_ग_लिखो,
	.पढ़ो	= aaci_ac97_पढ़ो,
पूर्ण;

अटल पूर्णांक aaci_probe_ac97(काष्ठा aaci *aaci)
अणु
	काष्ठा snd_ac97_ढाँचा ac97_ढाँचा;
	काष्ठा snd_ac97_bus *ac97_bus;
	काष्ठा snd_ac97 *ac97;
	पूर्णांक ret;

	/*
	 * Assert AACIRESET क्रम 2us
	 */
	ग_लिखोl(0, aaci->base + AACI_RESET);
	udelay(2);
	ग_लिखोl(RESET_NRST, aaci->base + AACI_RESET);

	/*
	 * Give the AC'97 codec more than enough समय
	 * to wake up. (42us = ~2 frames at 48kHz.)
	 */
	udelay(FRAME_PERIOD_US * 2);

	ret = snd_ac97_bus(aaci->card, 0, &aaci_bus_ops, aaci, &ac97_bus);
	अगर (ret)
		जाओ out;

	ac97_bus->घड़ी = 48000;
	aaci->ac97_bus = ac97_bus;

	स_रखो(&ac97_ढाँचा, 0, माप(काष्ठा snd_ac97_ढाँचा));
	ac97_ढाँचा.निजी_data = aaci;
	ac97_ढाँचा.num = 0;
	ac97_ढाँचा.scaps = AC97_SCAP_SKIP_MODEM;

	ret = snd_ac97_mixer(ac97_bus, &ac97_ढाँचा, &ac97);
	अगर (ret)
		जाओ out;
	aaci->ac97 = ac97;

	/*
	 * Disable AC97 PC Beep input on audio codecs.
	 */
	अगर (ac97_is_audio(ac97))
		snd_ac97_ग_लिखो_cache(ac97, AC97_PC_BEEP, 0x801e);

	ret = snd_ac97_pcm_assign(ac97_bus, ARRAY_SIZE(ac97_defs), ac97_defs);
	अगर (ret)
		जाओ out;

	aaci->playback.pcm = &ac97_bus->pcms[0];
	aaci->capture.pcm  = &ac97_bus->pcms[1];

 out:
	वापस ret;
पूर्ण

अटल व्योम aaci_मुक्त_card(काष्ठा snd_card *card)
अणु
	काष्ठा aaci *aaci = card->निजी_data;

	iounmap(aaci->base);
पूर्ण

अटल काष्ठा aaci *aaci_init_card(काष्ठा amba_device *dev)
अणु
	काष्ठा aaci *aaci;
	काष्ठा snd_card *card;
	पूर्णांक err;

	err = snd_card_new(&dev->dev, SNDRV_DEFAULT_IDX1, SNDRV_DEFAULT_STR1,
			   THIS_MODULE, माप(काष्ठा aaci), &card);
	अगर (err < 0)
		वापस शून्य;

	card->निजी_मुक्त = aaci_मुक्त_card;

	strscpy(card->driver, DRIVER_NAME, माप(card->driver));
	strscpy(card->लघुname, "ARM AC'97 Interface", माप(card->लघुname));
	snम_लिखो(card->दीर्घname, माप(card->दीर्घname),
		 "%s PL%03x rev%u at 0x%08llx, irq %d",
		 card->लघुname, amba_part(dev), amba_rev(dev),
		 (अचिन्हित दीर्घ दीर्घ)dev->res.start, dev->irq[0]);

	aaci = card->निजी_data;
	mutex_init(&aaci->ac97_sem);
	mutex_init(&aaci->irq_lock);
	aaci->card = card;
	aaci->dev = dev;

	/* Set MAINCR to allow slot 1 and 2 data IO */
	aaci->मुख्यcr = MAINCR_IE | MAINCR_SL1RXEN | MAINCR_SL1TXEN |
		       MAINCR_SL2RXEN | MAINCR_SL2TXEN;

	वापस aaci;
पूर्ण

अटल पूर्णांक aaci_init_pcm(काष्ठा aaci *aaci)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक ret;

	ret = snd_pcm_new(aaci->card, "AACI AC'97", 0, 1, 1, &pcm);
	अगर (ret == 0) अणु
		aaci->pcm = pcm;
		pcm->निजी_data = aaci;
		pcm->info_flags = 0;

		strscpy(pcm->name, DRIVER_NAME, माप(pcm->name));

		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &aaci_playback_ops);
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &aaci_capture_ops);
		snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
					       aaci->card->dev,
					       0, 64 * 1024);
	पूर्ण

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक aaci_size_fअगरo(काष्ठा aaci *aaci)
अणु
	काष्ठा aaci_runसमय *aacirun = &aaci->playback;
	पूर्णांक i;

	/*
	 * Enable the channel, but करोn't assign it to any slots, so
	 * it won't empty onto the AC'97 link.
	 */
	ग_लिखोl(CR_FEN | CR_SZ16 | CR_EN, aacirun->base + AACI_TXCR);

	क्रम (i = 0; !(पढ़ोl(aacirun->base + AACI_SR) & SR_TXFF) && i < 4096; i++)
		ग_लिखोl(0, aacirun->fअगरo);

	ग_लिखोl(0, aacirun->base + AACI_TXCR);

	/*
	 * Re-initialise the AACI after the FIFO depth test, to
	 * ensure that the FIFOs are empty.  Unक्रमtunately, merely
	 * disabling the channel करोesn't clear the FIFO.
	 */
	ग_लिखोl(aaci->मुख्यcr & ~MAINCR_IE, aaci->base + AACI_MAINCR);
	पढ़ोl(aaci->base + AACI_MAINCR);
	udelay(1);
	ग_लिखोl(aaci->मुख्यcr, aaci->base + AACI_MAINCR);

	/*
	 * If we hit 4096 entries, we failed.  Go back to the specअगरied
	 * fअगरo depth.
	 */
	अगर (i == 4096)
		i = 8;

	वापस i;
पूर्ण

अटल पूर्णांक aaci_probe(काष्ठा amba_device *dev,
		      स्थिर काष्ठा amba_id *id)
अणु
	काष्ठा aaci *aaci;
	पूर्णांक ret, i;

	ret = amba_request_regions(dev, शून्य);
	अगर (ret)
		वापस ret;

	aaci = aaci_init_card(dev);
	अगर (!aaci) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	aaci->base = ioremap(dev->res.start, resource_size(&dev->res));
	अगर (!aaci->base) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/*
	 * Playback uses AACI channel 0
	 */
	spin_lock_init(&aaci->playback.lock);
	aaci->playback.base = aaci->base + AACI_CSCH1;
	aaci->playback.fअगरo = aaci->base + AACI_DR1;

	/*
	 * Capture uses AACI channel 0
	 */
	spin_lock_init(&aaci->capture.lock);
	aaci->capture.base = aaci->base + AACI_CSCH1;
	aaci->capture.fअगरo = aaci->base + AACI_DR1;

	क्रम (i = 0; i < 4; i++) अणु
		व्योम __iomem *base = aaci->base + i * 0x14;

		ग_लिखोl(0, base + AACI_IE);
		ग_लिखोl(0, base + AACI_TXCR);
		ग_लिखोl(0, base + AACI_RXCR);
	पूर्ण

	ग_लिखोl(0x1fff, aaci->base + AACI_INTCLR);
	ग_लिखोl(aaci->मुख्यcr, aaci->base + AACI_MAINCR);
	/*
	 * Fix: ac97 पढ़ो back fail errors by पढ़ोing
	 * from any arbitrary aaci रेजिस्टर.
	 */
	पढ़ोl(aaci->base + AACI_CSCH1);
	ret = aaci_probe_ac97(aaci);
	अगर (ret)
		जाओ out;

	/*
	 * Size the FIFOs (must be multiple of 16).
	 * This is the number of entries in the FIFO.
	 */
	aaci->fअगरo_depth = aaci_size_fअगरo(aaci);
	अगर (aaci->fअगरo_depth & 15) अणु
		prपूर्णांकk(KERN_WARNING "AACI: FIFO depth %d not supported\n",
		       aaci->fअगरo_depth);
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	ret = aaci_init_pcm(aaci);
	अगर (ret)
		जाओ out;

	ret = snd_card_रेजिस्टर(aaci->card);
	अगर (ret == 0) अणु
		dev_info(&dev->dev, "%s\n", aaci->card->दीर्घname);
		dev_info(&dev->dev, "FIFO %u entries\n", aaci->fअगरo_depth);
		amba_set_drvdata(dev, aaci->card);
		वापस ret;
	पूर्ण

 out:
	अगर (aaci)
		snd_card_मुक्त(aaci->card);
	amba_release_regions(dev);
	वापस ret;
पूर्ण

अटल व्योम aaci_हटाओ(काष्ठा amba_device *dev)
अणु
	काष्ठा snd_card *card = amba_get_drvdata(dev);

	अगर (card) अणु
		काष्ठा aaci *aaci = card->निजी_data;
		ग_लिखोl(0, aaci->base + AACI_MAINCR);

		snd_card_मुक्त(card);
		amba_release_regions(dev);
	पूर्ण
पूर्ण

अटल काष्ठा amba_id aaci_ids[] = अणु
	अणु
		.id	= 0x00041041,
		.mask	= 0x000fffff,
	पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(amba, aaci_ids);

अटल काष्ठा amba_driver aaci_driver = अणु
	.drv		= अणु
		.name	= DRIVER_NAME,
		.pm	= AACI_DEV_PM_OPS,
	पूर्ण,
	.probe		= aaci_probe,
	.हटाओ		= aaci_हटाओ,
	.id_table	= aaci_ids,
पूर्ण;

module_amba_driver(aaci_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("ARM PrimeCell PL041 Advanced Audio CODEC Interface driver");
