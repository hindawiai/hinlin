<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Sound driver क्रम Silicon Graphics O2 Workstations A/V board audio.
 *
 *   Copyright 2003 Vivien Chappelier <vivien.chappelier@linux-mips.org>
 *   Copyright 2008 Thomas Bogenकरोerfer <tsbogend@alpha.franken.de>
 *   Mxier part taken from mace_audio.c:
 *   Copyright 2007 Thorben Jथअndling <tj.trevelyan@gmail.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/ip32/ip32_पूर्णांकs.h>
#समावेश <यंत्र/ip32/mace.h>

#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#घोषणा SNDRV_GET_ID
#समावेश <sound/initval.h>
#समावेश <sound/ad1843.h>


MODULE_AUTHOR("Vivien Chappelier <vivien.chappelier@linux-mips.org>");
MODULE_DESCRIPTION("SGI O2 Audio");
MODULE_LICENSE("GPL");

अटल पूर्णांक index = SNDRV_DEFAULT_IDX1;  /* Index 0-MAX */
अटल अक्षर *id = SNDRV_DEFAULT_STR1;   /* ID क्रम this card */

module_param(index, पूर्णांक, 0444);
MODULE_PARM_DESC(index, "Index value for SGI O2 soundcard.");
module_param(id, अक्षरp, 0444);
MODULE_PARM_DESC(id, "ID string for SGI O2 soundcard.");


#घोषणा AUDIO_CONTROL_RESET              BIT(0) /* 1: reset audio पूर्णांकerface */
#घोषणा AUDIO_CONTROL_CODEC_PRESENT      BIT(1) /* 1: codec detected */

#घोषणा CODEC_CONTROL_WORD_SHIFT        0
#घोषणा CODEC_CONTROL_READ              BIT(16)
#घोषणा CODEC_CONTROL_ADDRESS_SHIFT     17

#घोषणा CHANNEL_CONTROL_RESET           BIT(10) /* 1: reset channel */
#घोषणा CHANNEL_DMA_ENABLE              BIT(9)  /* 1: enable DMA transfer */
#घोषणा CHANNEL_INT_THRESHOLD_DISABLED  (0 << 5) /* पूर्णांकerrupt disabled */
#घोषणा CHANNEL_INT_THRESHOLD_25        (1 << 5) /* पूर्णांक on buffer >25% full */
#घोषणा CHANNEL_INT_THRESHOLD_50        (2 << 5) /* पूर्णांक on buffer >50% full */
#घोषणा CHANNEL_INT_THRESHOLD_75        (3 << 5) /* पूर्णांक on buffer >75% full */
#घोषणा CHANNEL_INT_THRESHOLD_EMPTY     (4 << 5) /* पूर्णांक on buffer empty */
#घोषणा CHANNEL_INT_THRESHOLD_NOT_EMPTY (5 << 5) /* पूर्णांक on buffer !empty */
#घोषणा CHANNEL_INT_THRESHOLD_FULL      (6 << 5) /* पूर्णांक on buffer empty */
#घोषणा CHANNEL_INT_THRESHOLD_NOT_FULL  (7 << 5) /* पूर्णांक on buffer !empty */

#घोषणा CHANNEL_RING_SHIFT              12
#घोषणा CHANNEL_RING_SIZE               (1 << CHANNEL_RING_SHIFT)
#घोषणा CHANNEL_RING_MASK               (CHANNEL_RING_SIZE - 1)

#घोषणा CHANNEL_LEFT_SHIFT 40
#घोषणा CHANNEL_RIGHT_SHIFT 8

काष्ठा snd_sgio2audio_chan अणु
	पूर्णांक idx;
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक pos;
	snd_pcm_uframes_t size;
	spinlock_t lock;
पूर्ण;

/* definition of the chip-specअगरic record */
काष्ठा snd_sgio2audio अणु
	काष्ठा snd_card *card;

	/* codec */
	काष्ठा snd_ad1843 ad1843;
	spinlock_t ad1843_lock;

	/* channels */
	काष्ठा snd_sgio2audio_chan channel[3];

	/* resources */
	व्योम *ring_base;
	dma_addr_t ring_base_dma;
पूर्ण;

/* AD1843 access */

/*
 * पढ़ो_ad1843_reg वापसs the current contents of a 16 bit AD1843 रेजिस्टर.
 *
 * Returns अचिन्हित रेजिस्टर value on success, -त्रुटि_सं on failure.
 */
अटल पूर्णांक पढ़ो_ad1843_reg(व्योम *priv, पूर्णांक reg)
अणु
	काष्ठा snd_sgio2audio *chip = priv;
	पूर्णांक val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->ad1843_lock, flags);

	ग_लिखोq((reg << CODEC_CONTROL_ADDRESS_SHIFT) |
	       CODEC_CONTROL_READ, &mace->perअगर.audio.codec_control);
	wmb();
	val = पढ़ोq(&mace->perअगर.audio.codec_control); /* flush bus */
	udelay(200);

	val = पढ़ोq(&mace->perअगर.audio.codec_पढ़ो);

	spin_unlock_irqrestore(&chip->ad1843_lock, flags);
	वापस val;
पूर्ण

/*
 * ग_लिखो_ad1843_reg ग_लिखोs the specअगरied value to a 16 bit AD1843 रेजिस्टर.
 */
अटल पूर्णांक ग_लिखो_ad1843_reg(व्योम *priv, पूर्णांक reg, पूर्णांक word)
अणु
	काष्ठा snd_sgio2audio *chip = priv;
	पूर्णांक val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->ad1843_lock, flags);

	ग_लिखोq((reg << CODEC_CONTROL_ADDRESS_SHIFT) |
	       (word << CODEC_CONTROL_WORD_SHIFT),
	       &mace->perअगर.audio.codec_control);
	wmb();
	val = पढ़ोq(&mace->perअगर.audio.codec_control); /* flush bus */
	udelay(200);

	spin_unlock_irqrestore(&chip->ad1843_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक sgio2audio_gain_info(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा snd_sgio2audio *chip = snd_kcontrol_chip(kcontrol);

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = ad1843_get_gain_max(&chip->ad1843,
					     (पूर्णांक)kcontrol->निजी_value);
	वापस 0;
पूर्ण

अटल पूर्णांक sgio2audio_gain_get(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_sgio2audio *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक vol;

	vol = ad1843_get_gain(&chip->ad1843, (पूर्णांक)kcontrol->निजी_value);

	ucontrol->value.पूर्णांकeger.value[0] = (vol >> 8) & 0xFF;
	ucontrol->value.पूर्णांकeger.value[1] = vol & 0xFF;

	वापस 0;
पूर्ण

अटल पूर्णांक sgio2audio_gain_put(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_sgio2audio *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक newvol, oldvol;

	oldvol = ad1843_get_gain(&chip->ad1843, kcontrol->निजी_value);
	newvol = (ucontrol->value.पूर्णांकeger.value[0] << 8) |
		ucontrol->value.पूर्णांकeger.value[1];

	newvol = ad1843_set_gain(&chip->ad1843, kcontrol->निजी_value,
		newvol);

	वापस newvol != oldvol;
पूर्ण

अटल पूर्णांक sgio2audio_source_info(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[3] = अणु
		"Cam Mic", "Mic", "Line"
	पूर्ण;
	वापस snd_ctl_क्रमागत_info(uinfo, 1, 3, texts);
पूर्ण

अटल पूर्णांक sgio2audio_source_get(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_sgio2audio *chip = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = ad1843_get_recsrc(&chip->ad1843);
	वापस 0;
पूर्ण

अटल पूर्णांक sgio2audio_source_put(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_sgio2audio *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक newsrc, oldsrc;

	oldsrc = ad1843_get_recsrc(&chip->ad1843);
	newsrc = ad1843_set_recsrc(&chip->ad1843,
				   ucontrol->value.क्रमागतerated.item[0]);

	वापस newsrc != oldsrc;
पूर्ण

/* dac1/pcm0 mixer control */
अटल स्थिर काष्ठा snd_kcontrol_new sgio2audio_ctrl_pcm0 = अणु
	.अगरace          = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name           = "PCM Playback Volume",
	.index          = 0,
	.access         = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.निजी_value  = AD1843_GAIN_PCM_0,
	.info           = sgio2audio_gain_info,
	.get            = sgio2audio_gain_get,
	.put            = sgio2audio_gain_put,
पूर्ण;

/* dac2/pcm1 mixer control */
अटल स्थिर काष्ठा snd_kcontrol_new sgio2audio_ctrl_pcm1 = अणु
	.अगरace          = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name           = "PCM Playback Volume",
	.index          = 1,
	.access         = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.निजी_value  = AD1843_GAIN_PCM_1,
	.info           = sgio2audio_gain_info,
	.get            = sgio2audio_gain_get,
	.put            = sgio2audio_gain_put,
पूर्ण;

/* record level mixer control */
अटल स्थिर काष्ठा snd_kcontrol_new sgio2audio_ctrl_reclevel = अणु
	.अगरace          = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name           = "Capture Volume",
	.access         = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.निजी_value  = AD1843_GAIN_RECLEV,
	.info           = sgio2audio_gain_info,
	.get            = sgio2audio_gain_get,
	.put            = sgio2audio_gain_put,
पूर्ण;

/* record level source control */
अटल स्थिर काष्ठा snd_kcontrol_new sgio2audio_ctrl_recsource = अणु
	.अगरace          = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name           = "Capture Source",
	.access         = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.info           = sgio2audio_source_info,
	.get            = sgio2audio_source_get,
	.put            = sgio2audio_source_put,
पूर्ण;

/* line mixer control */
अटल स्थिर काष्ठा snd_kcontrol_new sgio2audio_ctrl_line = अणु
	.अगरace          = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name           = "Line Playback Volume",
	.index          = 0,
	.access         = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.निजी_value  = AD1843_GAIN_LINE,
	.info           = sgio2audio_gain_info,
	.get            = sgio2audio_gain_get,
	.put            = sgio2audio_gain_put,
पूर्ण;

/* cd mixer control */
अटल स्थिर काष्ठा snd_kcontrol_new sgio2audio_ctrl_cd = अणु
	.अगरace          = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name           = "Line Playback Volume",
	.index          = 1,
	.access         = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.निजी_value  = AD1843_GAIN_LINE_2,
	.info           = sgio2audio_gain_info,
	.get            = sgio2audio_gain_get,
	.put            = sgio2audio_gain_put,
पूर्ण;

/* mic mixer control */
अटल स्थिर काष्ठा snd_kcontrol_new sgio2audio_ctrl_mic = अणु
	.अगरace          = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name           = "Mic Playback Volume",
	.access         = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.निजी_value  = AD1843_GAIN_MIC,
	.info           = sgio2audio_gain_info,
	.get            = sgio2audio_gain_get,
	.put            = sgio2audio_gain_put,
पूर्ण;


अटल पूर्णांक snd_sgio2audio_new_mixer(काष्ठा snd_sgio2audio *chip)
अणु
	पूर्णांक err;

	err = snd_ctl_add(chip->card,
			  snd_ctl_new1(&sgio2audio_ctrl_pcm0, chip));
	अगर (err < 0)
		वापस err;

	err = snd_ctl_add(chip->card,
			  snd_ctl_new1(&sgio2audio_ctrl_pcm1, chip));
	अगर (err < 0)
		वापस err;

	err = snd_ctl_add(chip->card,
			  snd_ctl_new1(&sgio2audio_ctrl_reclevel, chip));
	अगर (err < 0)
		वापस err;

	err = snd_ctl_add(chip->card,
			  snd_ctl_new1(&sgio2audio_ctrl_recsource, chip));
	अगर (err < 0)
		वापस err;
	err = snd_ctl_add(chip->card,
			  snd_ctl_new1(&sgio2audio_ctrl_line, chip));
	अगर (err < 0)
		वापस err;

	err = snd_ctl_add(chip->card,
			  snd_ctl_new1(&sgio2audio_ctrl_cd, chip));
	अगर (err < 0)
		वापस err;

	err = snd_ctl_add(chip->card,
			  snd_ctl_new1(&sgio2audio_ctrl_mic, chip));
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

/* low-level audio पूर्णांकerface DMA */

/* get data out of bounce buffer, count must be a multiple of 32 */
/* वापसs 1 अगर a period has elapsed */
अटल पूर्णांक snd_sgio2audio_dma_pull_frag(काष्ठा snd_sgio2audio *chip,
					अचिन्हित पूर्णांक ch, अचिन्हित पूर्णांक count)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ src_base, src_pos, dst_mask;
	अचिन्हित अक्षर *dst_base;
	पूर्णांक dst_pos;
	u64 *src;
	s16 *dst;
	u64 x;
	अचिन्हित दीर्घ flags;
	काष्ठा snd_pcm_runसमय *runसमय = chip->channel[ch].substream->runसमय;

	spin_lock_irqsave(&chip->channel[ch].lock, flags);

	src_base = (अचिन्हित दीर्घ) chip->ring_base | (ch << CHANNEL_RING_SHIFT);
	src_pos = पढ़ोq(&mace->perअगर.audio.chan[ch].पढ़ो_ptr);
	dst_base = runसमय->dma_area;
	dst_pos = chip->channel[ch].pos;
	dst_mask = frames_to_bytes(runसमय, runसमय->buffer_size) - 1;

	/* check अगर a period has elapsed */
	chip->channel[ch].size += (count >> 3); /* in frames */
	ret = chip->channel[ch].size >= runसमय->period_size;
	chip->channel[ch].size %= runसमय->period_size;

	जबतक (count) अणु
		src = (u64 *)(src_base + src_pos);
		dst = (s16 *)(dst_base + dst_pos);

		x = *src;
		dst[0] = (x >> CHANNEL_LEFT_SHIFT) & 0xffff;
		dst[1] = (x >> CHANNEL_RIGHT_SHIFT) & 0xffff;

		src_pos = (src_pos + माप(u64)) & CHANNEL_RING_MASK;
		dst_pos = (dst_pos + 2 * माप(s16)) & dst_mask;
		count -= माप(u64);
	पूर्ण

	ग_लिखोq(src_pos, &mace->perअगर.audio.chan[ch].पढ़ो_ptr); /* in bytes */
	chip->channel[ch].pos = dst_pos;

	spin_unlock_irqrestore(&chip->channel[ch].lock, flags);
	वापस ret;
पूर्ण

/* put some DMA data in bounce buffer, count must be a multiple of 32 */
/* वापसs 1 अगर a period has elapsed */
अटल पूर्णांक snd_sgio2audio_dma_push_frag(काष्ठा snd_sgio2audio *chip,
					अचिन्हित पूर्णांक ch, अचिन्हित पूर्णांक count)
अणु
	पूर्णांक ret;
	s64 l, r;
	अचिन्हित दीर्घ dst_base, dst_pos, src_mask;
	अचिन्हित अक्षर *src_base;
	पूर्णांक src_pos;
	u64 *dst;
	s16 *src;
	अचिन्हित दीर्घ flags;
	काष्ठा snd_pcm_runसमय *runसमय = chip->channel[ch].substream->runसमय;

	spin_lock_irqsave(&chip->channel[ch].lock, flags);

	dst_base = (अचिन्हित दीर्घ)chip->ring_base | (ch << CHANNEL_RING_SHIFT);
	dst_pos = पढ़ोq(&mace->perअगर.audio.chan[ch].ग_लिखो_ptr);
	src_base = runसमय->dma_area;
	src_pos = chip->channel[ch].pos;
	src_mask = frames_to_bytes(runसमय, runसमय->buffer_size) - 1;

	/* check अगर a period has elapsed */
	chip->channel[ch].size += (count >> 3); /* in frames */
	ret = chip->channel[ch].size >= runसमय->period_size;
	chip->channel[ch].size %= runसमय->period_size;

	जबतक (count) अणु
		src = (s16 *)(src_base + src_pos);
		dst = (u64 *)(dst_base + dst_pos);

		l = src[0]; /* sign extend */
		r = src[1]; /* sign extend */

		*dst = ((l & 0x00ffffff) << CHANNEL_LEFT_SHIFT) |
			((r & 0x00ffffff) << CHANNEL_RIGHT_SHIFT);

		dst_pos = (dst_pos + माप(u64)) & CHANNEL_RING_MASK;
		src_pos = (src_pos + 2 * माप(s16)) & src_mask;
		count -= माप(u64);
	पूर्ण

	ग_लिखोq(dst_pos, &mace->perअगर.audio.chan[ch].ग_लिखो_ptr); /* in bytes */
	chip->channel[ch].pos = src_pos;

	spin_unlock_irqrestore(&chip->channel[ch].lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक snd_sgio2audio_dma_start(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_sgio2audio *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_sgio2audio_chan *chan = substream->runसमय->निजी_data;
	पूर्णांक ch = chan->idx;

	/* reset DMA channel */
	ग_लिखोq(CHANNEL_CONTROL_RESET, &mace->perअगर.audio.chan[ch].control);
	udelay(10);
	ग_लिखोq(0, &mace->perअगर.audio.chan[ch].control);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		/* push a full buffer */
		snd_sgio2audio_dma_push_frag(chip, ch, CHANNEL_RING_SIZE - 32);
	पूर्ण
	/* set DMA to wake on 50% empty and enable पूर्णांकerrupt */
	ग_लिखोq(CHANNEL_DMA_ENABLE | CHANNEL_INT_THRESHOLD_50,
	       &mace->perअगर.audio.chan[ch].control);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sgio2audio_dma_stop(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_sgio2audio_chan *chan = substream->runसमय->निजी_data;

	ग_लिखोq(0, &mace->perअगर.audio.chan[chan->idx].control);
	वापस 0;
पूर्ण

अटल irqवापस_t snd_sgio2audio_dma_in_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_sgio2audio_chan *chan = dev_id;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_sgio2audio *chip;
	पूर्णांक count, ch;

	substream = chan->substream;
	chip = snd_pcm_substream_chip(substream);
	ch = chan->idx;

	/* empty the ring */
	count = CHANNEL_RING_SIZE -
		पढ़ोq(&mace->perअगर.audio.chan[ch].depth) - 32;
	अगर (snd_sgio2audio_dma_pull_frag(chip, ch, count))
		snd_pcm_period_elapsed(substream);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t snd_sgio2audio_dma_out_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_sgio2audio_chan *chan = dev_id;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_sgio2audio *chip;
	पूर्णांक count, ch;

	substream = chan->substream;
	chip = snd_pcm_substream_chip(substream);
	ch = chan->idx;
	/* fill the ring */
	count = CHANNEL_RING_SIZE -
		पढ़ोq(&mace->perअगर.audio.chan[ch].depth) - 32;
	अगर (snd_sgio2audio_dma_push_frag(chip, ch, count))
		snd_pcm_period_elapsed(substream);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t snd_sgio2audio_error_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_sgio2audio_chan *chan = dev_id;
	काष्ठा snd_pcm_substream *substream;

	substream = chan->substream;
	snd_sgio2audio_dma_stop(substream);
	snd_sgio2audio_dma_start(substream);
	वापस IRQ_HANDLED;
पूर्ण

/* PCM part */
/* PCM hardware definition */
अटल स्थिर काष्ठा snd_pcm_hardware snd_sgio2audio_pcm_hw = अणु
	.info = (SNDRV_PCM_INFO_MMAP |
		 SNDRV_PCM_INFO_MMAP_VALID |
		 SNDRV_PCM_INFO_INTERLEAVED |
		 SNDRV_PCM_INFO_BLOCK_TRANSFER),
	.क्रमmats =          SNDRV_PCM_FMTBIT_S16_BE,
	.rates =            SNDRV_PCM_RATE_8000_48000,
	.rate_min =         8000,
	.rate_max =         48000,
	.channels_min =     2,
	.channels_max =     2,
	.buffer_bytes_max = 65536,
	.period_bytes_min = 32768,
	.period_bytes_max = 65536,
	.periods_min =      1,
	.periods_max =      1024,
पूर्ण;

/* PCM playback खोलो callback */
अटल पूर्णांक snd_sgio2audio_playback1_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_sgio2audio *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	runसमय->hw = snd_sgio2audio_pcm_hw;
	runसमय->निजी_data = &chip->channel[1];
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sgio2audio_playback2_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_sgio2audio *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	runसमय->hw = snd_sgio2audio_pcm_hw;
	runसमय->निजी_data = &chip->channel[2];
	वापस 0;
पूर्ण

/* PCM capture खोलो callback */
अटल पूर्णांक snd_sgio2audio_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_sgio2audio *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	runसमय->hw = snd_sgio2audio_pcm_hw;
	runसमय->निजी_data = &chip->channel[0];
	वापस 0;
पूर्ण

/* PCM बंद callback */
अटल पूर्णांक snd_sgio2audio_pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	runसमय->निजी_data = शून्य;
	वापस 0;
पूर्ण

/* prepare callback */
अटल पूर्णांक snd_sgio2audio_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_sgio2audio *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_sgio2audio_chan *chan = substream->runसमय->निजी_data;
	पूर्णांक ch = chan->idx;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->channel[ch].lock, flags);

	/* Setup the pseuकरो-dma transfer poपूर्णांकers.  */
	chip->channel[ch].pos = 0;
	chip->channel[ch].size = 0;
	chip->channel[ch].substream = substream;

	/* set AD1843 क्रमmat */
	/* hardware क्रमmat is always S16_LE */
	चयन (substream->stream) अणु
	हाल SNDRV_PCM_STREAM_PLAYBACK:
		ad1843_setup_dac(&chip->ad1843,
				 ch - 1,
				 runसमय->rate,
				 SNDRV_PCM_FORMAT_S16_LE,
				 runसमय->channels);
		अवरोध;
	हाल SNDRV_PCM_STREAM_CAPTURE:
		ad1843_setup_adc(&chip->ad1843,
				 runसमय->rate,
				 SNDRV_PCM_FORMAT_S16_LE,
				 runसमय->channels);
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&chip->channel[ch].lock, flags);
	वापस 0;
पूर्ण

/* trigger callback */
अटल पूर्णांक snd_sgio2audio_pcm_trigger(काष्ठा snd_pcm_substream *substream,
				      पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		/* start the PCM engine */
		snd_sgio2audio_dma_start(substream);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		/* stop the PCM engine */
		snd_sgio2audio_dma_stop(substream);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* poपूर्णांकer callback */
अटल snd_pcm_uframes_t
snd_sgio2audio_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_sgio2audio *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_sgio2audio_chan *chan = substream->runसमय->निजी_data;

	/* get the current hardware poपूर्णांकer */
	वापस bytes_to_frames(substream->runसमय,
			       chip->channel[chan->idx].pos);
पूर्ण

/* चालकs */
अटल स्थिर काष्ठा snd_pcm_ops snd_sgio2audio_playback1_ops = अणु
	.खोलो =        snd_sgio2audio_playback1_खोलो,
	.बंद =       snd_sgio2audio_pcm_बंद,
	.prepare =     snd_sgio2audio_pcm_prepare,
	.trigger =     snd_sgio2audio_pcm_trigger,
	.poपूर्णांकer =     snd_sgio2audio_pcm_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_sgio2audio_playback2_ops = अणु
	.खोलो =        snd_sgio2audio_playback2_खोलो,
	.बंद =       snd_sgio2audio_pcm_बंद,
	.prepare =     snd_sgio2audio_pcm_prepare,
	.trigger =     snd_sgio2audio_pcm_trigger,
	.poपूर्णांकer =     snd_sgio2audio_pcm_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_sgio2audio_capture_ops = अणु
	.खोलो =        snd_sgio2audio_capture_खोलो,
	.बंद =       snd_sgio2audio_pcm_बंद,
	.prepare =     snd_sgio2audio_pcm_prepare,
	.trigger =     snd_sgio2audio_pcm_trigger,
	.poपूर्णांकer =     snd_sgio2audio_pcm_poपूर्णांकer,
पूर्ण;

/*
 *  definitions of capture are omitted here...
 */

/* create a pcm device */
अटल पूर्णांक snd_sgio2audio_new_pcm(काष्ठा snd_sgio2audio *chip)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	/* create first pcm device with one outमाला_दो and one input */
	err = snd_pcm_new(chip->card, "SGI O2 Audio", 0, 1, 1, &pcm);
	अगर (err < 0)
		वापस err;

	pcm->निजी_data = chip;
	म_नकल(pcm->name, "SGI O2 DAC1");

	/* set चालकs */
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
			&snd_sgio2audio_playback1_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
			&snd_sgio2audio_capture_ops);
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_VMALLOC, शून्य, 0, 0);

	/* create second  pcm device with one outमाला_दो and no input */
	err = snd_pcm_new(chip->card, "SGI O2 Audio", 1, 1, 0, &pcm);
	अगर (err < 0)
		वापस err;

	pcm->निजी_data = chip;
	म_नकल(pcm->name, "SGI O2 DAC2");

	/* set चालकs */
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
			&snd_sgio2audio_playback2_ops);
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_VMALLOC, शून्य, 0, 0);

	वापस 0;
पूर्ण

अटल काष्ठा अणु
	पूर्णांक idx;
	पूर्णांक irq;
	irqवापस_t (*isr)(पूर्णांक, व्योम *);
	स्थिर अक्षर *desc;
पूर्ण snd_sgio2_isr_table[] = अणु
	अणु
		.idx = 0,
		.irq = MACEISA_AUDIO1_DMAT_IRQ,
		.isr = snd_sgio2audio_dma_in_isr,
		.desc = "Capture DMA Channel 0"
	पूर्ण, अणु
		.idx = 0,
		.irq = MACEISA_AUDIO1_OF_IRQ,
		.isr = snd_sgio2audio_error_isr,
		.desc = "Capture Overflow"
	पूर्ण, अणु
		.idx = 1,
		.irq = MACEISA_AUDIO2_DMAT_IRQ,
		.isr = snd_sgio2audio_dma_out_isr,
		.desc = "Playback DMA Channel 1"
	पूर्ण, अणु
		.idx = 1,
		.irq = MACEISA_AUDIO2_MERR_IRQ,
		.isr = snd_sgio2audio_error_isr,
		.desc = "Memory Error Channel 1"
	पूर्ण, अणु
		.idx = 2,
		.irq = MACEISA_AUDIO3_DMAT_IRQ,
		.isr = snd_sgio2audio_dma_out_isr,
		.desc = "Playback DMA Channel 2"
	पूर्ण, अणु
		.idx = 2,
		.irq = MACEISA_AUDIO3_MERR_IRQ,
		.isr = snd_sgio2audio_error_isr,
		.desc = "Memory Error Channel 2"
	पूर्ण
पूर्ण;

/* ALSA driver */

अटल पूर्णांक snd_sgio2audio_मुक्त(काष्ठा snd_sgio2audio *chip)
अणु
	पूर्णांक i;

	/* reset पूर्णांकerface */
	ग_लिखोq(AUDIO_CONTROL_RESET, &mace->perअगर.audio.control);
	udelay(1);
	ग_लिखोq(0, &mace->perअगर.audio.control);

	/* release IRQ's */
	क्रम (i = 0; i < ARRAY_SIZE(snd_sgio2_isr_table); i++)
		मुक्त_irq(snd_sgio2_isr_table[i].irq,
			 &chip->channel[snd_sgio2_isr_table[i].idx]);

	dma_मुक्त_coherent(chip->card->dev, MACEISA_RINGBUFFERS_SIZE,
			  chip->ring_base, chip->ring_base_dma);

	/* release card data */
	kमुक्त(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sgio2audio_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_sgio2audio *chip = device->device_data;

	वापस snd_sgio2audio_मुक्त(chip);
पूर्ण

अटल स्थिर काष्ठा snd_device_ops ops = अणु
	.dev_मुक्त = snd_sgio2audio_dev_मुक्त,
पूर्ण;

अटल पूर्णांक snd_sgio2audio_create(काष्ठा snd_card *card,
				 काष्ठा snd_sgio2audio **rchip)
अणु
	काष्ठा snd_sgio2audio *chip;
	पूर्णांक i, err;

	*rchip = शून्य;

	/* check अगर a codec is attached to the पूर्णांकerface */
	/* (Audio or Audio/Video board present) */
	अगर (!(पढ़ोq(&mace->perअगर.audio.control) & AUDIO_CONTROL_CODEC_PRESENT))
		वापस -ENOENT;

	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य)
		वापस -ENOMEM;

	chip->card = card;

	chip->ring_base = dma_alloc_coherent(card->dev,
					     MACEISA_RINGBUFFERS_SIZE,
					     &chip->ring_base_dma, GFP_KERNEL);
	अगर (chip->ring_base == शून्य) अणु
		prपूर्णांकk(KERN_ERR
		       "sgio2audio: could not allocate ring buffers\n");
		kमुक्त(chip);
		वापस -ENOMEM;
	पूर्ण

	spin_lock_init(&chip->ad1843_lock);

	/* initialize channels */
	क्रम (i = 0; i < 3; i++) अणु
		spin_lock_init(&chip->channel[i].lock);
		chip->channel[i].idx = i;
	पूर्ण

	/* allocate IRQs */
	क्रम (i = 0; i < ARRAY_SIZE(snd_sgio2_isr_table); i++) अणु
		अगर (request_irq(snd_sgio2_isr_table[i].irq,
				snd_sgio2_isr_table[i].isr,
				0,
				snd_sgio2_isr_table[i].desc,
				&chip->channel[snd_sgio2_isr_table[i].idx])) अणु
			snd_sgio2audio_मुक्त(chip);
			prपूर्णांकk(KERN_ERR "sgio2audio: cannot allocate irq %d\n",
			       snd_sgio2_isr_table[i].irq);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	/* reset the पूर्णांकerface */
	ग_लिखोq(AUDIO_CONTROL_RESET, &mace->perअगर.audio.control);
	udelay(1);
	ग_लिखोq(0, &mace->perअगर.audio.control);
	msleep_पूर्णांकerruptible(1); /* give समय to recover */

	/* set ring base */
	ग_लिखोq(chip->ring_base_dma, &mace->perअगर.ctrl.ringbase);

	/* attach the AD1843 codec */
	chip->ad1843.पढ़ो = पढ़ो_ad1843_reg;
	chip->ad1843.ग_लिखो = ग_लिखो_ad1843_reg;
	chip->ad1843.chip = chip;

	/* initialize the AD1843 codec */
	err = ad1843_init(&chip->ad1843);
	अगर (err < 0) अणु
		snd_sgio2audio_मुक्त(chip);
		वापस err;
	पूर्ण

	err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops);
	अगर (err < 0) अणु
		snd_sgio2audio_मुक्त(chip);
		वापस err;
	पूर्ण
	*rchip = chip;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sgio2audio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_card *card;
	काष्ठा snd_sgio2audio *chip;
	पूर्णांक err;

	err = snd_card_new(&pdev->dev, index, id, THIS_MODULE, 0, &card);
	अगर (err < 0)
		वापस err;

	err = snd_sgio2audio_create(card, &chip);
	अगर (err < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	err = snd_sgio2audio_new_pcm(chip);
	अगर (err < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	err = snd_sgio2audio_new_mixer(chip);
	अगर (err < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	म_नकल(card->driver, "SGI O2 Audio");
	म_नकल(card->लघुname, "SGI O2 Audio");
	प्र_लिखो(card->दीर्घname, "%s irq %i-%i",
		card->लघुname,
		MACEISA_AUDIO1_DMAT_IRQ,
		MACEISA_AUDIO3_MERR_IRQ);

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	platक्रमm_set_drvdata(pdev, card);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sgio2audio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_card *card = platक्रमm_get_drvdata(pdev);

	snd_card_मुक्त(card);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sgio2audio_driver = अणु
	.probe	= snd_sgio2audio_probe,
	.हटाओ	= snd_sgio2audio_हटाओ,
	.driver = अणु
		.name	= "sgio2audio",
	पूर्ण
पूर्ण;

module_platक्रमm_driver(sgio2audio_driver);
