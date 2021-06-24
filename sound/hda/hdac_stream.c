<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HD-audio stream operations
 */

#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/hdaudपन.स>
#समावेश <sound/hda_रेजिस्टर.h>
#समावेश "trace.h"

/**
 * snd_hdac_get_stream_stripe_ctl - get stripe control value
 * @bus: HD-audio core bus
 * @substream: PCM substream
 */
पूर्णांक snd_hdac_get_stream_stripe_ctl(काष्ठा hdac_bus *bus,
				   काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित पूर्णांक channels = runसमय->channels,
		     rate = runसमय->rate,
		     bits_per_sample = runसमय->sample_bits,
		     max_sकरो_lines, value, sकरो_line;

	/* T_AZA_GCAP_NSDO is 1:2 bitfields in GCAP */
	max_sकरो_lines = snd_hdac_chip_पढ़ोl(bus, GCAP) & AZX_GCAP_NSDO;

	/* following is from HD audio spec */
	क्रम (sकरो_line = max_sकरो_lines; sकरो_line > 0; sकरो_line >>= 1) अणु
		अगर (rate > 48000)
			value = (channels * bits_per_sample *
					(rate / 48000)) / sकरो_line;
		अन्यथा
			value = (channels * bits_per_sample) / sकरो_line;

		अगर (value >= bus->sकरो_limit)
			अवरोध;
	पूर्ण

	/* stripe value: 0 क्रम 1SDO, 1 क्रम 2SDO, 2 क्रम 4SDO lines */
	वापस sकरो_line >> 1;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_get_stream_stripe_ctl);

/**
 * snd_hdac_stream_init - initialize each stream (aka device)
 * @bus: HD-audio core bus
 * @azx_dev: HD-audio core stream object to initialize
 * @idx: stream index number
 * @direction: stream direction (SNDRV_PCM_STREAM_PLAYBACK or SNDRV_PCM_STREAM_CAPTURE)
 * @tag: the tag id to assign
 *
 * Assign the starting bdl address to each stream (device) and initialize.
 */
व्योम snd_hdac_stream_init(काष्ठा hdac_bus *bus, काष्ठा hdac_stream *azx_dev,
			  पूर्णांक idx, पूर्णांक direction, पूर्णांक tag)
अणु
	azx_dev->bus = bus;
	/* offset: SDI0=0x80, SDI1=0xa0, ... SDO3=0x160 */
	azx_dev->sd_addr = bus->remap_addr + (0x20 * idx + 0x80);
	/* पूर्णांक mask: SDI0=0x01, SDI1=0x02, ... SDO3=0x80 */
	azx_dev->sd_पूर्णांक_sta_mask = 1 << idx;
	azx_dev->index = idx;
	azx_dev->direction = direction;
	azx_dev->stream_tag = tag;
	snd_hdac_dsp_lock_init(azx_dev);
	list_add_tail(&azx_dev->list, &bus->stream_list);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_stream_init);

/**
 * snd_hdac_stream_start - start a stream
 * @azx_dev: HD-audio core stream to start
 * @fresh_start: false = wallघड़ी बारtamp relative to period wallघड़ी
 *
 * Start a stream, set start_wallclk and set the running flag.
 */
व्योम snd_hdac_stream_start(काष्ठा hdac_stream *azx_dev, bool fresh_start)
अणु
	काष्ठा hdac_bus *bus = azx_dev->bus;
	पूर्णांक stripe_ctl;

	trace_snd_hdac_stream_start(bus, azx_dev);

	azx_dev->start_wallclk = snd_hdac_chip_पढ़ोl(bus, WALLCLK);
	अगर (!fresh_start)
		azx_dev->start_wallclk -= azx_dev->period_wallclk;

	/* enable SIE */
	snd_hdac_chip_updatel(bus, INTCTL,
			      1 << azx_dev->index,
			      1 << azx_dev->index);
	/* set stripe control */
	अगर (azx_dev->stripe) अणु
		अगर (azx_dev->substream)
			stripe_ctl = snd_hdac_get_stream_stripe_ctl(bus, azx_dev->substream);
		अन्यथा
			stripe_ctl = 0;
		snd_hdac_stream_updateb(azx_dev, SD_CTL_3B, SD_CTL_STRIPE_MASK,
					stripe_ctl);
	पूर्ण
	/* set DMA start and पूर्णांकerrupt mask */
	snd_hdac_stream_updateb(azx_dev, SD_CTL,
				0, SD_CTL_DMA_START | SD_INT_MASK);
	azx_dev->running = true;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_stream_start);

/**
 * snd_hdac_stream_clear - stop a stream DMA
 * @azx_dev: HD-audio core stream to stop
 */
व्योम snd_hdac_stream_clear(काष्ठा hdac_stream *azx_dev)
अणु
	snd_hdac_stream_updateb(azx_dev, SD_CTL,
				SD_CTL_DMA_START | SD_INT_MASK, 0);
	snd_hdac_stream_ग_लिखोb(azx_dev, SD_STS, SD_INT_MASK); /* to be sure */
	अगर (azx_dev->stripe)
		snd_hdac_stream_updateb(azx_dev, SD_CTL_3B, SD_CTL_STRIPE_MASK, 0);
	azx_dev->running = false;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_stream_clear);

/**
 * snd_hdac_stream_stop - stop a stream
 * @azx_dev: HD-audio core stream to stop
 *
 * Stop a stream DMA and disable stream पूर्णांकerrupt
 */
व्योम snd_hdac_stream_stop(काष्ठा hdac_stream *azx_dev)
अणु
	trace_snd_hdac_stream_stop(azx_dev->bus, azx_dev);

	snd_hdac_stream_clear(azx_dev);
	/* disable SIE */
	snd_hdac_chip_updatel(azx_dev->bus, INTCTL, 1 << azx_dev->index, 0);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_stream_stop);

/**
 * snd_hdac_stream_reset - reset a stream
 * @azx_dev: HD-audio core stream to reset
 */
व्योम snd_hdac_stream_reset(काष्ठा hdac_stream *azx_dev)
अणु
	अचिन्हित अक्षर val;
	पूर्णांक समयout;
	पूर्णांक dma_run_state;

	snd_hdac_stream_clear(azx_dev);

	dma_run_state = snd_hdac_stream_पढ़ोb(azx_dev, SD_CTL) & SD_CTL_DMA_START;

	snd_hdac_stream_updateb(azx_dev, SD_CTL, 0, SD_CTL_STREAM_RESET);
	udelay(3);
	समयout = 300;
	करो अणु
		val = snd_hdac_stream_पढ़ोb(azx_dev, SD_CTL) &
			SD_CTL_STREAM_RESET;
		अगर (val)
			अवरोध;
	पूर्ण जबतक (--समयout);

	अगर (azx_dev->bus->dma_stop_delay && dma_run_state)
		udelay(azx_dev->bus->dma_stop_delay);

	val &= ~SD_CTL_STREAM_RESET;
	snd_hdac_stream_ग_लिखोb(azx_dev, SD_CTL, val);
	udelay(3);

	समयout = 300;
	/* रुकोing क्रम hardware to report that the stream is out of reset */
	करो अणु
		val = snd_hdac_stream_पढ़ोb(azx_dev, SD_CTL) &
			SD_CTL_STREAM_RESET;
		अगर (!val)
			अवरोध;
	पूर्ण जबतक (--समयout);

	/* reset first position - may not be synced with hw at this समय */
	अगर (azx_dev->posbuf)
		*azx_dev->posbuf = 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_stream_reset);

/**
 * snd_hdac_stream_setup -  set up the SD क्रम streaming
 * @azx_dev: HD-audio core stream to set up
 */
पूर्णांक snd_hdac_stream_setup(काष्ठा hdac_stream *azx_dev)
अणु
	काष्ठा hdac_bus *bus = azx_dev->bus;
	काष्ठा snd_pcm_runसमय *runसमय;
	अचिन्हित पूर्णांक val;

	अगर (azx_dev->substream)
		runसमय = azx_dev->substream->runसमय;
	अन्यथा
		runसमय = शून्य;
	/* make sure the run bit is zero क्रम SD */
	snd_hdac_stream_clear(azx_dev);
	/* program the stream_tag */
	val = snd_hdac_stream_पढ़ोl(azx_dev, SD_CTL);
	val = (val & ~SD_CTL_STREAM_TAG_MASK) |
		(azx_dev->stream_tag << SD_CTL_STREAM_TAG_SHIFT);
	अगर (!bus->snoop)
		val |= SD_CTL_TRAFFIC_PRIO;
	snd_hdac_stream_ग_लिखोl(azx_dev, SD_CTL, val);

	/* program the length of samples in cyclic buffer */
	snd_hdac_stream_ग_लिखोl(azx_dev, SD_CBL, azx_dev->bufsize);

	/* program the stream क्रमmat */
	/* this value needs to be the same as the one programmed */
	snd_hdac_stream_ग_लिखोw(azx_dev, SD_FORMAT, azx_dev->क्रमmat_val);

	/* program the stream LVI (last valid index) of the BDL */
	snd_hdac_stream_ग_लिखोw(azx_dev, SD_LVI, azx_dev->frags - 1);

	/* program the BDL address */
	/* lower BDL address */
	snd_hdac_stream_ग_लिखोl(azx_dev, SD_BDLPL, (u32)azx_dev->bdl.addr);
	/* upper BDL address */
	snd_hdac_stream_ग_लिखोl(azx_dev, SD_BDLPU,
			       upper_32_bits(azx_dev->bdl.addr));

	/* enable the position buffer */
	अगर (bus->use_posbuf && bus->posbuf.addr) अणु
		अगर (!(snd_hdac_chip_पढ़ोl(bus, DPLBASE) & AZX_DPLBASE_ENABLE))
			snd_hdac_chip_ग_लिखोl(bus, DPLBASE,
				(u32)bus->posbuf.addr | AZX_DPLBASE_ENABLE);
	पूर्ण

	/* set the पूर्णांकerrupt enable bits in the descriptor control रेजिस्टर */
	snd_hdac_stream_updatel(azx_dev, SD_CTL, 0, SD_INT_MASK);

	azx_dev->fअगरo_size = snd_hdac_stream_पढ़ोw(azx_dev, SD_FIFOSIZE) + 1;

	/* when LPIB delay correction gives a small negative value,
	 * we ignore it; currently set the threshold अटलally to
	 * 64 frames
	 */
	अगर (runसमय && runसमय->period_size > 64)
		azx_dev->delay_negative_threshold =
			-frames_to_bytes(runसमय, 64);
	अन्यथा
		azx_dev->delay_negative_threshold = 0;

	/* wallclk has 24Mhz घड़ी source */
	अगर (runसमय)
		azx_dev->period_wallclk = (((runसमय->period_size * 24000) /
				    runसमय->rate) * 1000);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_stream_setup);

/**
 * snd_hdac_stream_cleanup - cleanup a stream
 * @azx_dev: HD-audio core stream to clean up
 */
व्योम snd_hdac_stream_cleanup(काष्ठा hdac_stream *azx_dev)
अणु
	snd_hdac_stream_ग_लिखोl(azx_dev, SD_BDLPL, 0);
	snd_hdac_stream_ग_लिखोl(azx_dev, SD_BDLPU, 0);
	snd_hdac_stream_ग_लिखोl(azx_dev, SD_CTL, 0);
	azx_dev->bufsize = 0;
	azx_dev->period_bytes = 0;
	azx_dev->क्रमmat_val = 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_stream_cleanup);

/**
 * snd_hdac_stream_assign - assign a stream क्रम the PCM
 * @bus: HD-audio core bus
 * @substream: PCM substream to assign
 *
 * Look क्रम an unused stream क्रम the given PCM substream, assign it
 * and वापस the stream object.  If no stream is मुक्त, वापसs शून्य.
 * The function tries to keep using the same stream object when it's used
 * beक्रमehand.  Also, when bus->reverse_assign flag is set, the last मुक्त
 * or matching entry is वापसed.  This is needed क्रम some strange codecs.
 */
काष्ठा hdac_stream *snd_hdac_stream_assign(काष्ठा hdac_bus *bus,
					   काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hdac_stream *azx_dev;
	काष्ठा hdac_stream *res = शून्य;

	/* make a non-zero unique key क्रम the substream */
	पूर्णांक key = (substream->pcm->device << 16) | (substream->number << 2) |
		(substream->stream + 1);

	list_क्रम_each_entry(azx_dev, &bus->stream_list, list) अणु
		अगर (azx_dev->direction != substream->stream)
			जारी;
		अगर (azx_dev->खोलोed)
			जारी;
		अगर (azx_dev->asचिन्हित_key == key) अणु
			res = azx_dev;
			अवरोध;
		पूर्ण
		अगर (!res || bus->reverse_assign)
			res = azx_dev;
	पूर्ण
	अगर (res) अणु
		spin_lock_irq(&bus->reg_lock);
		res->खोलोed = 1;
		res->running = 0;
		res->asचिन्हित_key = key;
		res->substream = substream;
		spin_unlock_irq(&bus->reg_lock);
	पूर्ण
	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_stream_assign);

/**
 * snd_hdac_stream_release - release the asचिन्हित stream
 * @azx_dev: HD-audio core stream to release
 *
 * Release the stream that has been asचिन्हित by snd_hdac_stream_assign().
 */
व्योम snd_hdac_stream_release(काष्ठा hdac_stream *azx_dev)
अणु
	काष्ठा hdac_bus *bus = azx_dev->bus;

	spin_lock_irq(&bus->reg_lock);
	azx_dev->खोलोed = 0;
	azx_dev->running = 0;
	azx_dev->substream = शून्य;
	spin_unlock_irq(&bus->reg_lock);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_stream_release);

/**
 * snd_hdac_get_stream - वापस hdac_stream based on stream_tag and
 * direction
 *
 * @bus: HD-audio core bus
 * @dir: direction क्रम the stream to be found
 * @stream_tag: stream tag क्रम stream to be found
 */
काष्ठा hdac_stream *snd_hdac_get_stream(काष्ठा hdac_bus *bus,
					पूर्णांक dir, पूर्णांक stream_tag)
अणु
	काष्ठा hdac_stream *s;

	list_क्रम_each_entry(s, &bus->stream_list, list) अणु
		अगर (s->direction == dir && s->stream_tag == stream_tag)
			वापस s;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_get_stream);

/*
 * set up a BDL entry
 */
अटल पूर्णांक setup_bdle(काष्ठा hdac_bus *bus,
		      काष्ठा snd_dma_buffer *dmab,
		      काष्ठा hdac_stream *azx_dev, __le32 **bdlp,
		      पूर्णांक ofs, पूर्णांक size, पूर्णांक with_ioc)
अणु
	__le32 *bdl = *bdlp;

	जबतक (size > 0) अणु
		dma_addr_t addr;
		पूर्णांक chunk;

		अगर (azx_dev->frags >= AZX_MAX_BDL_ENTRIES)
			वापस -EINVAL;

		addr = snd_sgbuf_get_addr(dmab, ofs);
		/* program the address field of the BDL entry */
		bdl[0] = cpu_to_le32((u32)addr);
		bdl[1] = cpu_to_le32(upper_32_bits(addr));
		/* program the size field of the BDL entry */
		chunk = snd_sgbuf_get_chunk_size(dmab, ofs, size);
		/* one BDLE cannot cross 4K boundary on CTHDA chips */
		अगर (bus->align_bdle_4k) अणु
			u32 reमुख्य = 0x1000 - (ofs & 0xfff);

			अगर (chunk > reमुख्य)
				chunk = reमुख्य;
		पूर्ण
		bdl[2] = cpu_to_le32(chunk);
		/* program the IOC to enable पूर्णांकerrupt
		 * only when the whole fragment is processed
		 */
		size -= chunk;
		bdl[3] = (size || !with_ioc) ? 0 : cpu_to_le32(0x01);
		bdl += 4;
		azx_dev->frags++;
		ofs += chunk;
	पूर्ण
	*bdlp = bdl;
	वापस ofs;
पूर्ण

/**
 * snd_hdac_stream_setup_periods - set up BDL entries
 * @azx_dev: HD-audio core stream to set up
 *
 * Set up the buffer descriptor table of the given stream based on the
 * period and buffer sizes of the asचिन्हित PCM substream.
 */
पूर्णांक snd_hdac_stream_setup_periods(काष्ठा hdac_stream *azx_dev)
अणु
	काष्ठा hdac_bus *bus = azx_dev->bus;
	काष्ठा snd_pcm_substream *substream = azx_dev->substream;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	__le32 *bdl;
	पूर्णांक i, ofs, periods, period_bytes;
	पूर्णांक pos_adj, pos_align;

	/* reset BDL address */
	snd_hdac_stream_ग_लिखोl(azx_dev, SD_BDLPL, 0);
	snd_hdac_stream_ग_लिखोl(azx_dev, SD_BDLPU, 0);

	period_bytes = azx_dev->period_bytes;
	periods = azx_dev->bufsize / period_bytes;

	/* program the initial BDL entries */
	bdl = (__le32 *)azx_dev->bdl.area;
	ofs = 0;
	azx_dev->frags = 0;

	pos_adj = bus->bdl_pos_adj;
	अगर (!azx_dev->no_period_wakeup && pos_adj > 0) अणु
		pos_align = pos_adj;
		pos_adj = DIV_ROUND_UP(pos_adj * runसमय->rate, 48000);
		अगर (!pos_adj)
			pos_adj = pos_align;
		अन्यथा
			pos_adj = roundup(pos_adj, pos_align);
		pos_adj = frames_to_bytes(runसमय, pos_adj);
		अगर (pos_adj >= period_bytes) अणु
			dev_warn(bus->dev, "Too big adjustment %d\n",
				 pos_adj);
			pos_adj = 0;
		पूर्ण अन्यथा अणु
			ofs = setup_bdle(bus, snd_pcm_get_dma_buf(substream),
					 azx_dev,
					 &bdl, ofs, pos_adj, true);
			अगर (ofs < 0)
				जाओ error;
		पूर्ण
	पूर्ण अन्यथा
		pos_adj = 0;

	क्रम (i = 0; i < periods; i++) अणु
		अगर (i == periods - 1 && pos_adj)
			ofs = setup_bdle(bus, snd_pcm_get_dma_buf(substream),
					 azx_dev, &bdl, ofs,
					 period_bytes - pos_adj, 0);
		अन्यथा
			ofs = setup_bdle(bus, snd_pcm_get_dma_buf(substream),
					 azx_dev, &bdl, ofs,
					 period_bytes,
					 !azx_dev->no_period_wakeup);
		अगर (ofs < 0)
			जाओ error;
	पूर्ण
	वापस 0;

 error:
	dev_err(bus->dev, "Too many BDL entries: buffer=%d, period=%d\n",
		azx_dev->bufsize, period_bytes);
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_stream_setup_periods);

/**
 * snd_hdac_stream_set_params - set stream parameters
 * @azx_dev: HD-audio core stream क्रम which parameters are to be set
 * @क्रमmat_val: क्रमmat value parameter
 *
 * Setup the HD-audio core stream parameters from substream of the stream
 * and passed क्रमmat value
 */
पूर्णांक snd_hdac_stream_set_params(काष्ठा hdac_stream *azx_dev,
				 अचिन्हित पूर्णांक क्रमmat_val)
अणु

	अचिन्हित पूर्णांक bufsize, period_bytes;
	काष्ठा snd_pcm_substream *substream = azx_dev->substream;
	काष्ठा snd_pcm_runसमय *runसमय;
	पूर्णांक err;

	अगर (!substream)
		वापस -EINVAL;
	runसमय = substream->runसमय;
	bufsize = snd_pcm_lib_buffer_bytes(substream);
	period_bytes = snd_pcm_lib_period_bytes(substream);

	अगर (bufsize != azx_dev->bufsize ||
	    period_bytes != azx_dev->period_bytes ||
	    क्रमmat_val != azx_dev->क्रमmat_val ||
	    runसमय->no_period_wakeup != azx_dev->no_period_wakeup) अणु
		azx_dev->bufsize = bufsize;
		azx_dev->period_bytes = period_bytes;
		azx_dev->क्रमmat_val = क्रमmat_val;
		azx_dev->no_period_wakeup = runसमय->no_period_wakeup;
		err = snd_hdac_stream_setup_periods(azx_dev);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_stream_set_params);

अटल u64 azx_cc_पढ़ो(स्थिर काष्ठा cyclecounter *cc)
अणु
	काष्ठा hdac_stream *azx_dev = container_of(cc, काष्ठा hdac_stream, cc);

	वापस snd_hdac_chip_पढ़ोl(azx_dev->bus, WALLCLK);
पूर्ण

अटल व्योम azx_समयcounter_init(काष्ठा hdac_stream *azx_dev,
				 bool क्रमce, u64 last)
अणु
	काष्ठा समयcounter *tc = &azx_dev->tc;
	काष्ठा cyclecounter *cc = &azx_dev->cc;
	u64 nsec;

	cc->पढ़ो = azx_cc_पढ़ो;
	cc->mask = CLOCKSOURCE_MASK(32);

	/*
	 * Converting from 24 MHz to ns means applying a 125/3 factor.
	 * To aव्योम any saturation issues in पूर्णांकermediate operations,
	 * the 125 factor is applied first. The भागision is applied
	 * last after पढ़ोing the समयcounter value.
	 * Applying the 1/3 factor as part of the multiplication
	 * requires at least 20 bits क्रम a decent precision, however
	 * overflows occur after about 4 hours or less, not a option.
	 */

	cc->mult = 125; /* saturation after 195 years */
	cc->shअगरt = 0;

	nsec = 0; /* audio समय is elapsed समय since trigger */
	समयcounter_init(tc, cc, nsec);
	अगर (क्रमce) अणु
		/*
		 * क्रमce समयcounter to use predefined value,
		 * used क्रम synchronized starts
		 */
		tc->cycle_last = last;
	पूर्ण
पूर्ण

/**
 * snd_hdac_stream_समयcounter_init - initialize समय counter
 * @azx_dev: HD-audio core stream (master stream)
 * @streams: bit flags of streams to set up
 *
 * Initializes the समय counter of streams marked by the bit flags (each
 * bit corresponds to the stream index).
 * The trigger बारtamp of PCM substream asचिन्हित to the given stream is
 * updated accordingly, too.
 */
व्योम snd_hdac_stream_समयcounter_init(काष्ठा hdac_stream *azx_dev,
				      अचिन्हित पूर्णांक streams)
अणु
	काष्ठा hdac_bus *bus = azx_dev->bus;
	काष्ठा snd_pcm_runसमय *runसमय = azx_dev->substream->runसमय;
	काष्ठा hdac_stream *s;
	bool inited = false;
	u64 cycle_last = 0;
	पूर्णांक i = 0;

	list_क्रम_each_entry(s, &bus->stream_list, list) अणु
		अगर (streams & (1 << i)) अणु
			azx_समयcounter_init(s, inited, cycle_last);
			अगर (!inited) अणु
				inited = true;
				cycle_last = s->tc.cycle_last;
			पूर्ण
		पूर्ण
		i++;
	पूर्ण

	snd_pcm_समय_लो(runसमय, &runसमय->trigger_tstamp);
	runसमय->trigger_tstamp_latched = true;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_stream_समयcounter_init);

/**
 * snd_hdac_stream_sync_trigger - turn on/off stream sync रेजिस्टर
 * @azx_dev: HD-audio core stream (master stream)
 * @set: true = set, false = clear
 * @streams: bit flags of streams to sync
 * @reg: the stream sync रेजिस्टर address
 */
व्योम snd_hdac_stream_sync_trigger(काष्ठा hdac_stream *azx_dev, bool set,
				  अचिन्हित पूर्णांक streams, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा hdac_bus *bus = azx_dev->bus;
	अचिन्हित पूर्णांक val;

	अगर (!reg)
		reg = AZX_REG_SSYNC;
	val = _snd_hdac_chip_पढ़ोl(bus, reg);
	अगर (set)
		val |= streams;
	अन्यथा
		val &= ~streams;
	_snd_hdac_chip_ग_लिखोl(bus, reg, val);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_stream_sync_trigger);

/**
 * snd_hdac_stream_sync - sync with start/stop trigger operation
 * @azx_dev: HD-audio core stream (master stream)
 * @start: true = start, false = stop
 * @streams: bit flags of streams to sync
 *
 * For @start = true, रुको until all FIFOs get पढ़ोy.
 * For @start = false, रुको until all RUN bits are cleared.
 */
व्योम snd_hdac_stream_sync(काष्ठा hdac_stream *azx_dev, bool start,
			  अचिन्हित पूर्णांक streams)
अणु
	काष्ठा hdac_bus *bus = azx_dev->bus;
	पूर्णांक i, nरुको, समयout;
	काष्ठा hdac_stream *s;

	क्रम (समयout = 5000; समयout; समयout--) अणु
		nरुको = 0;
		i = 0;
		list_क्रम_each_entry(s, &bus->stream_list, list) अणु
			अगर (!(streams & (1 << i++)))
				जारी;

			अगर (start) अणु
				/* check FIFO माला_लो पढ़ोy */
				अगर (!(snd_hdac_stream_पढ़ोb(s, SD_STS) &
				      SD_STS_FIFO_READY))
					nरुको++;
			पूर्ण अन्यथा अणु
				/* check RUN bit is cleared */
				अगर (snd_hdac_stream_पढ़ोb(s, SD_CTL) &
				    SD_CTL_DMA_START) अणु
					nरुको++;
					/*
					 * Perक्रमm stream reset अगर DMA RUN
					 * bit not cleared within given समयout
					 */
					अगर (समयout == 1)
						snd_hdac_stream_reset(s);
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (!nरुको)
			अवरोध;
		cpu_relax();
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_stream_sync);

#अगर_घोषित CONFIG_SND_HDA_DSP_LOADER
/**
 * snd_hdac_dsp_prepare - prepare क्रम DSP loading
 * @azx_dev: HD-audio core stream used क्रम DSP loading
 * @क्रमmat: HD-audio stream क्रमmat
 * @byte_size: data chunk byte size
 * @bufp: allocated buffer
 *
 * Allocate the buffer क्रम the given size and set up the given stream क्रम
 * DSP loading.  Returns the stream tag (>= 0), or a negative error code.
 */
पूर्णांक snd_hdac_dsp_prepare(काष्ठा hdac_stream *azx_dev, अचिन्हित पूर्णांक क्रमmat,
			 अचिन्हित पूर्णांक byte_size, काष्ठा snd_dma_buffer *bufp)
अणु
	काष्ठा hdac_bus *bus = azx_dev->bus;
	__le32 *bdl;
	पूर्णांक err;

	snd_hdac_dsp_lock(azx_dev);
	spin_lock_irq(&bus->reg_lock);
	अगर (azx_dev->running || azx_dev->locked) अणु
		spin_unlock_irq(&bus->reg_lock);
		err = -EBUSY;
		जाओ unlock;
	पूर्ण
	azx_dev->locked = true;
	spin_unlock_irq(&bus->reg_lock);

	err = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV_SG, bus->dev,
				  byte_size, bufp);
	अगर (err < 0)
		जाओ err_alloc;

	azx_dev->substream = शून्य;
	azx_dev->bufsize = byte_size;
	azx_dev->period_bytes = byte_size;
	azx_dev->क्रमmat_val = क्रमmat;

	snd_hdac_stream_reset(azx_dev);

	/* reset BDL address */
	snd_hdac_stream_ग_लिखोl(azx_dev, SD_BDLPL, 0);
	snd_hdac_stream_ग_लिखोl(azx_dev, SD_BDLPU, 0);

	azx_dev->frags = 0;
	bdl = (__le32 *)azx_dev->bdl.area;
	err = setup_bdle(bus, bufp, azx_dev, &bdl, 0, byte_size, 0);
	अगर (err < 0)
		जाओ error;

	snd_hdac_stream_setup(azx_dev);
	snd_hdac_dsp_unlock(azx_dev);
	वापस azx_dev->stream_tag;

 error:
	snd_dma_मुक्त_pages(bufp);
 err_alloc:
	spin_lock_irq(&bus->reg_lock);
	azx_dev->locked = false;
	spin_unlock_irq(&bus->reg_lock);
 unlock:
	snd_hdac_dsp_unlock(azx_dev);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_dsp_prepare);

/**
 * snd_hdac_dsp_trigger - start / stop DSP loading
 * @azx_dev: HD-audio core stream used क्रम DSP loading
 * @start: trigger start or stop
 */
व्योम snd_hdac_dsp_trigger(काष्ठा hdac_stream *azx_dev, bool start)
अणु
	अगर (start)
		snd_hdac_stream_start(azx_dev, true);
	अन्यथा
		snd_hdac_stream_stop(azx_dev);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_dsp_trigger);

/**
 * snd_hdac_dsp_cleanup - clean up the stream from DSP loading to normal
 * @azx_dev: HD-audio core stream used क्रम DSP loading
 * @dmab: buffer used by DSP loading
 */
व्योम snd_hdac_dsp_cleanup(काष्ठा hdac_stream *azx_dev,
			  काष्ठा snd_dma_buffer *dmab)
अणु
	काष्ठा hdac_bus *bus = azx_dev->bus;

	अगर (!dmab->area || !azx_dev->locked)
		वापस;

	snd_hdac_dsp_lock(azx_dev);
	/* reset BDL address */
	snd_hdac_stream_ग_लिखोl(azx_dev, SD_BDLPL, 0);
	snd_hdac_stream_ग_लिखोl(azx_dev, SD_BDLPU, 0);
	snd_hdac_stream_ग_लिखोl(azx_dev, SD_CTL, 0);
	azx_dev->bufsize = 0;
	azx_dev->period_bytes = 0;
	azx_dev->क्रमmat_val = 0;

	snd_dma_मुक्त_pages(dmab);
	dmab->area = शून्य;

	spin_lock_irq(&bus->reg_lock);
	azx_dev->locked = false;
	spin_unlock_irq(&bus->reg_lock);
	snd_hdac_dsp_unlock(azx_dev);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_dsp_cleanup);
#पूर्ण_अगर /* CONFIG_SND_HDA_DSP_LOADER */
