<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Hewlett-Packard Harmony audio driver
 *
 *   This is a driver क्रम the Harmony audio chipset found
 *   on the LASI ASIC of various early HP PA-RISC workstations.
 *
 *   Copyright (C) 2004, Kyle McMartin <kyle@अणुdebian.org,parisc-linux.orgपूर्ण>
 *
 *     Based on the previous Harmony incarnations by,
 *       Copyright 2000 (c) Linuxcare Canada, Alex deVries
 *       Copyright 2000-2003 (c) Helge Deller
 *       Copyright 2001 (c) Matthieu Delahaye
 *       Copyright 2001 (c) Jean-Christophe Vaugeois
 *       Copyright 2003 (c) Laurent Canet
 *       Copyright 2004 (c) Stuart Brady
 *
 * Notes:
 *   - graveyard and silence buffers last क्रम lअगरeसमय of
 *     the driver. playback and capture buffers are allocated
 *     per _खोलो()/_बंद().
 * 
 * TODO:
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/रुको.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/control.h>
#समावेश <sound/rawmidi.h>
#समावेश <sound/initval.h>
#समावेश <sound/info.h>

#समावेश <यंत्र/hardware.h>
#समावेश <यंत्र/parisc-device.h>

#समावेश "harmony.h"

अटल पूर्णांक index = SNDRV_DEFAULT_IDX1;	/* Index 0-MAX */
अटल अक्षर *id = SNDRV_DEFAULT_STR1;	/* ID क्रम this card */
module_param(index, पूर्णांक, 0444);
MODULE_PARM_DESC(index, "Index value for Harmony driver.");
module_param(id, अक्षरp, 0444);
MODULE_PARM_DESC(id, "ID string for Harmony driver.");


अटल स्थिर काष्ठा parisc_device_id snd_harmony_devtable[] __initस्थिर = अणु
	/* bushmaster / flounder */
	अणु HPHW_FIO, HVERSION_REV_ANY_ID, HVERSION_ANY_ID, 0x0007A पूर्ण, 
	/* 712 / 715 */
	अणु HPHW_FIO, HVERSION_REV_ANY_ID, HVERSION_ANY_ID, 0x0007B पूर्ण, 
	/* pace */
	अणु HPHW_FIO, HVERSION_REV_ANY_ID, HVERSION_ANY_ID, 0x0007E पूर्ण, 
	/* outfield / coral II */
	अणु HPHW_FIO, HVERSION_REV_ANY_ID, HVERSION_ANY_ID, 0x0007F पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(parisc, snd_harmony_devtable);

#घोषणा NAME "harmony"
#घोषणा PFX  NAME ": "

अटल स्थिर अचिन्हित पूर्णांक snd_harmony_rates[] = अणु
	5512, 6615, 8000, 9600,
	11025, 16000, 18900, 22050,
	27428, 32000, 33075, 37800,
	44100, 48000
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक rate_bits[14] = अणु
	HARMONY_SR_5KHZ, HARMONY_SR_6KHZ, HARMONY_SR_8KHZ,
	HARMONY_SR_9KHZ, HARMONY_SR_11KHZ, HARMONY_SR_16KHZ,
	HARMONY_SR_18KHZ, HARMONY_SR_22KHZ, HARMONY_SR_27KHZ,
	HARMONY_SR_32KHZ, HARMONY_SR_33KHZ, HARMONY_SR_37KHZ,
	HARMONY_SR_44KHZ, HARMONY_SR_48KHZ
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_स्थिरraपूर्णांक_rates = अणु
	.count = ARRAY_SIZE(snd_harmony_rates),
	.list = snd_harmony_rates,
	.mask = 0,
पूर्ण;

अटल अंतरभूत अचिन्हित दीर्घ
harmony_पढ़ो(काष्ठा snd_harmony *h, अचिन्हित r)
अणु
	वापस __raw_पढ़ोl(h->iobase + r);
पूर्ण

अटल अंतरभूत व्योम
harmony_ग_लिखो(काष्ठा snd_harmony *h, अचिन्हित r, अचिन्हित दीर्घ v)
अणु
	__raw_ग_लिखोl(v, h->iobase + r);
पूर्ण

अटल अंतरभूत व्योम
harmony_रुको_क्रम_control(काष्ठा snd_harmony *h)
अणु
	जबतक (harmony_पढ़ो(h, HARMONY_CNTL) & HARMONY_CNTL_C) ;
पूर्ण

अटल अंतरभूत व्योम
harmony_reset(काष्ठा snd_harmony *h)
अणु
	harmony_ग_लिखो(h, HARMONY_RESET, 1);
	mdelay(50);
	harmony_ग_लिखो(h, HARMONY_RESET, 0);
पूर्ण

अटल व्योम
harmony_disable_पूर्णांकerrupts(काष्ठा snd_harmony *h)
अणु
	u32 dstatus;
	harmony_रुको_क्रम_control(h);
	dstatus = harmony_पढ़ो(h, HARMONY_DSTATUS);
	dstatus &= ~HARMONY_DSTATUS_IE;
	harmony_ग_लिखो(h, HARMONY_DSTATUS, dstatus);
पूर्ण

अटल व्योम
harmony_enable_पूर्णांकerrupts(काष्ठा snd_harmony *h)
अणु
	u32 dstatus;
	harmony_रुको_क्रम_control(h);
	dstatus = harmony_पढ़ो(h, HARMONY_DSTATUS);
	dstatus |= HARMONY_DSTATUS_IE;
	harmony_ग_लिखो(h, HARMONY_DSTATUS, dstatus);
पूर्ण

अटल व्योम
harmony_mute(काष्ठा snd_harmony *h)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&h->mixer_lock, flags);
	harmony_रुको_क्रम_control(h);
	harmony_ग_लिखो(h, HARMONY_GAINCTL, HARMONY_GAIN_SILENCE);
	spin_unlock_irqrestore(&h->mixer_lock, flags);
पूर्ण

अटल व्योम
harmony_unmute(काष्ठा snd_harmony *h)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&h->mixer_lock, flags);
	harmony_रुको_क्रम_control(h);
	harmony_ग_लिखो(h, HARMONY_GAINCTL, h->st.gain);
	spin_unlock_irqrestore(&h->mixer_lock, flags);
पूर्ण

अटल व्योम
harmony_set_control(काष्ठा snd_harmony *h)
अणु
	u32 ctrl;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&h->lock, flags);

	ctrl = (HARMONY_CNTL_C      |
		(h->st.क्रमmat << 6) |
		(h->st.stereo << 5) |
		(h->st.rate));

	harmony_रुको_क्रम_control(h);
	harmony_ग_लिखो(h, HARMONY_CNTL, ctrl);

	spin_unlock_irqrestore(&h->lock, flags);
पूर्ण

अटल irqवापस_t
snd_harmony_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
	u32 dstatus;
	काष्ठा snd_harmony *h = dev;

	spin_lock(&h->lock);
	harmony_disable_पूर्णांकerrupts(h);
	harmony_रुको_क्रम_control(h);
	dstatus = harmony_पढ़ो(h, HARMONY_DSTATUS);
	spin_unlock(&h->lock);

	अगर (dstatus & HARMONY_DSTATUS_PN) अणु
		अगर (h->psubs && h->st.playing) अणु
			spin_lock(&h->lock);
			h->pbuf.buf += h->pbuf.count; /* PAGE_SIZE */
			h->pbuf.buf %= h->pbuf.size; /* MAX_BUFS*PAGE_SIZE */

			harmony_ग_लिखो(h, HARMONY_PNXTADD, 
				      h->pbuf.addr + h->pbuf.buf);
			h->stats.play_पूर्णांकr++;
			spin_unlock(&h->lock);
                        snd_pcm_period_elapsed(h->psubs);
		पूर्ण अन्यथा अणु
			spin_lock(&h->lock);
			harmony_ग_लिखो(h, HARMONY_PNXTADD, h->sdma.addr);
			h->stats.silence_पूर्णांकr++;
			spin_unlock(&h->lock);
		पूर्ण
	पूर्ण

	अगर (dstatus & HARMONY_DSTATUS_RN) अणु
		अगर (h->csubs && h->st.capturing) अणु
			spin_lock(&h->lock);
			h->cbuf.buf += h->cbuf.count;
			h->cbuf.buf %= h->cbuf.size;

			harmony_ग_लिखो(h, HARMONY_RNXTADD,
				      h->cbuf.addr + h->cbuf.buf);
			h->stats.rec_पूर्णांकr++;
			spin_unlock(&h->lock);
                        snd_pcm_period_elapsed(h->csubs);
		पूर्ण अन्यथा अणु
			spin_lock(&h->lock);
			harmony_ग_लिखो(h, HARMONY_RNXTADD, h->gdma.addr);
			h->stats.graveyard_पूर्णांकr++;
			spin_unlock(&h->lock);
		पूर्ण
	पूर्ण

	spin_lock(&h->lock);
	harmony_enable_पूर्णांकerrupts(h);
	spin_unlock(&h->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल अचिन्हित पूर्णांक 
snd_harmony_rate_bits(पूर्णांक rate)
अणु
	अचिन्हित पूर्णांक i;
	
	क्रम (i = 0; i < ARRAY_SIZE(snd_harmony_rates); i++)
		अगर (snd_harmony_rates[i] == rate)
			वापस rate_bits[i];

	वापस HARMONY_SR_44KHZ;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_harmony_playback =
अणु
	.info =	(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED | 
		 SNDRV_PCM_INFO_JOINT_DUPLEX | SNDRV_PCM_INFO_MMAP_VALID |
		 SNDRV_PCM_INFO_BLOCK_TRANSFER),
	.क्रमmats = (SNDRV_PCM_FMTBIT_S16_BE | SNDRV_PCM_FMTBIT_MU_LAW |
		    SNDRV_PCM_FMTBIT_A_LAW),
	.rates = (SNDRV_PCM_RATE_5512 | SNDRV_PCM_RATE_8000_48000 |
		  SNDRV_PCM_RATE_KNOT),
	.rate_min = 5512,
	.rate_max = 48000,
	.channels_min =	1,
	.channels_max =	2,
	.buffer_bytes_max = MAX_BUF_SIZE,
	.period_bytes_min = BUF_SIZE,
	.period_bytes_max = BUF_SIZE,
	.periods_min = 1,
	.periods_max = MAX_BUFS,
	.fअगरo_size = 0,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_harmony_capture =
अणु
        .info = (SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
                 SNDRV_PCM_INFO_JOINT_DUPLEX | SNDRV_PCM_INFO_MMAP_VALID |
                 SNDRV_PCM_INFO_BLOCK_TRANSFER),
        .क्रमmats = (SNDRV_PCM_FMTBIT_S16_BE | SNDRV_PCM_FMTBIT_MU_LAW |
                    SNDRV_PCM_FMTBIT_A_LAW),
        .rates = (SNDRV_PCM_RATE_5512 | SNDRV_PCM_RATE_8000_48000 |
		  SNDRV_PCM_RATE_KNOT),
        .rate_min = 5512,
        .rate_max = 48000,
        .channels_min = 1,
        .channels_max = 2,
        .buffer_bytes_max = MAX_BUF_SIZE,
        .period_bytes_min = BUF_SIZE,
        .period_bytes_max = BUF_SIZE,
        .periods_min = 1,
        .periods_max = MAX_BUFS,
        .fअगरo_size = 0,
पूर्ण;

अटल पूर्णांक
snd_harmony_playback_trigger(काष्ठा snd_pcm_substream *ss, पूर्णांक cmd)
अणु
	काष्ठा snd_harmony *h = snd_pcm_substream_chip(ss);

	अगर (h->st.capturing)
		वापस -EBUSY;

	spin_lock(&h->lock);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		h->st.playing = 1;
		harmony_ग_लिखो(h, HARMONY_PNXTADD, h->pbuf.addr);
		harmony_ग_लिखो(h, HARMONY_RNXTADD, h->gdma.addr);
		harmony_unmute(h);
		harmony_enable_पूर्णांकerrupts(h);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		h->st.playing = 0;
		harmony_mute(h);
		harmony_ग_लिखो(h, HARMONY_PNXTADD, h->sdma.addr);
		harmony_disable_पूर्णांकerrupts(h);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	शेष:
		spin_unlock(&h->lock);
		snd_BUG();
		वापस -EINVAL;
	पूर्ण
	spin_unlock(&h->lock);
	
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_harmony_capture_trigger(काष्ठा snd_pcm_substream *ss, पूर्णांक cmd)
अणु
        काष्ठा snd_harmony *h = snd_pcm_substream_chip(ss);

	अगर (h->st.playing)
		वापस -EBUSY;

	spin_lock(&h->lock);
        चयन (cmd) अणु
        हाल SNDRV_PCM_TRIGGER_START:
		h->st.capturing = 1;
                harmony_ग_लिखो(h, HARMONY_PNXTADD, h->sdma.addr);
                harmony_ग_लिखो(h, HARMONY_RNXTADD, h->cbuf.addr);
		harmony_unmute(h);
                harmony_enable_पूर्णांकerrupts(h);
		अवरोध;
        हाल SNDRV_PCM_TRIGGER_STOP:
		h->st.capturing = 0;
		harmony_mute(h);
		harmony_ग_लिखो(h, HARMONY_RNXTADD, h->gdma.addr);
		harmony_disable_पूर्णांकerrupts(h);
		अवरोध;
        हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
        हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
        हाल SNDRV_PCM_TRIGGER_SUSPEND:
	शेष:
		spin_unlock(&h->lock);
		snd_BUG();
                वापस -EINVAL;
        पूर्ण
	spin_unlock(&h->lock);
		
        वापस 0;
पूर्ण

अटल पूर्णांक
snd_harmony_set_data_क्रमmat(काष्ठा snd_harmony *h, पूर्णांक fmt, पूर्णांक क्रमce)
अणु
	पूर्णांक o = h->st.क्रमmat;
	पूर्णांक n;

	चयन(fmt) अणु
	हाल SNDRV_PCM_FORMAT_S16_BE:
		n = HARMONY_DF_16BIT_LINEAR;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_A_LAW:
		n = HARMONY_DF_8BIT_ALAW;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_MU_LAW:
		n = HARMONY_DF_8BIT_ULAW;
		अवरोध;
	शेष:
		n = HARMONY_DF_16BIT_LINEAR;
		अवरोध;
	पूर्ण

	अगर (क्रमce || o != n) अणु
		snd_pcm_क्रमmat_set_silence(fmt, h->sdma.area, SILENCE_BUFSZ / 
					   (snd_pcm_क्रमmat_physical_width(fmt)
					    / 8));
	पूर्ण

	वापस n;
पूर्ण

अटल पूर्णांक
snd_harmony_playback_prepare(काष्ठा snd_pcm_substream *ss)
अणु
	काष्ठा snd_harmony *h = snd_pcm_substream_chip(ss);
	काष्ठा snd_pcm_runसमय *rt = ss->runसमय;
	
	अगर (h->st.capturing)
		वापस -EBUSY;
	
	h->pbuf.size = snd_pcm_lib_buffer_bytes(ss);
	h->pbuf.count = snd_pcm_lib_period_bytes(ss);
	अगर (h->pbuf.buf >= h->pbuf.size)
		h->pbuf.buf = 0;
	h->st.playing = 0;

	h->st.rate = snd_harmony_rate_bits(rt->rate);
	h->st.क्रमmat = snd_harmony_set_data_क्रमmat(h, rt->क्रमmat, 0);
	
	अगर (rt->channels == 2)
		h->st.stereo = HARMONY_SS_STEREO;
	अन्यथा
		h->st.stereo = HARMONY_SS_MONO;

	harmony_set_control(h);

	h->pbuf.addr = rt->dma_addr;

	वापस 0;
पूर्ण

अटल पूर्णांक
snd_harmony_capture_prepare(काष्ठा snd_pcm_substream *ss)
अणु
        काष्ठा snd_harmony *h = snd_pcm_substream_chip(ss);
        काष्ठा snd_pcm_runसमय *rt = ss->runसमय;

	अगर (h->st.playing)
		वापस -EBUSY;

        h->cbuf.size = snd_pcm_lib_buffer_bytes(ss);
        h->cbuf.count = snd_pcm_lib_period_bytes(ss);
	अगर (h->cbuf.buf >= h->cbuf.size)
	        h->cbuf.buf = 0;
	h->st.capturing = 0;

        h->st.rate = snd_harmony_rate_bits(rt->rate);
        h->st.क्रमmat = snd_harmony_set_data_क्रमmat(h, rt->क्रमmat, 0);

        अगर (rt->channels == 2)
                h->st.stereo = HARMONY_SS_STEREO;
        अन्यथा
                h->st.stereo = HARMONY_SS_MONO;

        harmony_set_control(h);

        h->cbuf.addr = rt->dma_addr;

        वापस 0;
पूर्ण

अटल snd_pcm_uframes_t 
snd_harmony_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *ss)
अणु
	काष्ठा snd_pcm_runसमय *rt = ss->runसमय;
	काष्ठा snd_harmony *h = snd_pcm_substream_chip(ss);
	अचिन्हित दीर्घ pcuradd;
	अचिन्हित दीर्घ played;

	अगर (!(h->st.playing) || (h->psubs == शून्य)) 
		वापस 0;

	अगर ((h->pbuf.addr == 0) || (h->pbuf.size == 0))
		वापस 0;
	
	pcuradd = harmony_पढ़ो(h, HARMONY_PCURADD);
	played = pcuradd - h->pbuf.addr;

#अगर_घोषित HARMONY_DEBUG
	prपूर्णांकk(KERN_DEBUG PFX "playback_pointer is 0x%lx-0x%lx = %d bytes\n", 
	       pcuradd, h->pbuf.addr, played);	
#पूर्ण_अगर

	अगर (pcuradd > h->pbuf.addr + h->pbuf.size) अणु
		वापस 0;
	पूर्ण

	वापस bytes_to_frames(rt, played);
पूर्ण

अटल snd_pcm_uframes_t
snd_harmony_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *ss)
अणु
        काष्ठा snd_pcm_runसमय *rt = ss->runसमय;
        काष्ठा snd_harmony *h = snd_pcm_substream_chip(ss);
        अचिन्हित दीर्घ rcuradd;
        अचिन्हित दीर्घ caught;

        अगर (!(h->st.capturing) || (h->csubs == शून्य))
                वापस 0;

        अगर ((h->cbuf.addr == 0) || (h->cbuf.size == 0))
                वापस 0;

        rcuradd = harmony_पढ़ो(h, HARMONY_RCURADD);
        caught = rcuradd - h->cbuf.addr;

#अगर_घोषित HARMONY_DEBUG
        prपूर्णांकk(KERN_DEBUG PFX "capture_pointer is 0x%lx-0x%lx = %d bytes\n",
               rcuradd, h->cbuf.addr, caught);
#पूर्ण_अगर

        अगर (rcuradd > h->cbuf.addr + h->cbuf.size) अणु
		वापस 0;
	पूर्ण

        वापस bytes_to_frames(rt, caught);
पूर्ण

अटल पूर्णांक 
snd_harmony_playback_खोलो(काष्ठा snd_pcm_substream *ss)
अणु
	काष्ठा snd_harmony *h = snd_pcm_substream_chip(ss);
	काष्ठा snd_pcm_runसमय *rt = ss->runसमय;
	पूर्णांक err;
	
	h->psubs = ss;
	rt->hw = snd_harmony_playback;
	snd_pcm_hw_स्थिरraपूर्णांक_list(rt, 0, SNDRV_PCM_HW_PARAM_RATE, 
				   &hw_स्थिरraपूर्णांक_rates);
	
	err = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(rt, SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (err < 0)
		वापस err;
	
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_harmony_capture_खोलो(काष्ठा snd_pcm_substream *ss)
अणु
        काष्ठा snd_harmony *h = snd_pcm_substream_chip(ss);
        काष्ठा snd_pcm_runसमय *rt = ss->runसमय;
        पूर्णांक err;

        h->csubs = ss;
        rt->hw = snd_harmony_capture;
        snd_pcm_hw_स्थिरraपूर्णांक_list(rt, 0, SNDRV_PCM_HW_PARAM_RATE,
                                   &hw_स्थिरraपूर्णांक_rates);

        err = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(rt, SNDRV_PCM_HW_PARAM_PERIODS);
        अगर (err < 0)
                वापस err;

        वापस 0;
पूर्ण

अटल पूर्णांक 
snd_harmony_playback_बंद(काष्ठा snd_pcm_substream *ss)
अणु
	काष्ठा snd_harmony *h = snd_pcm_substream_chip(ss);
	h->psubs = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_harmony_capture_बंद(काष्ठा snd_pcm_substream *ss)
अणु
        काष्ठा snd_harmony *h = snd_pcm_substream_chip(ss);
        h->csubs = शून्य;
        वापस 0;
पूर्ण

अटल पूर्णांक 
snd_harmony_hw_params(काष्ठा snd_pcm_substream *ss,
		      काष्ठा snd_pcm_hw_params *hw)
अणु
	काष्ठा snd_harmony *h = snd_pcm_substream_chip(ss);
	
	अगर (h->dma.type == SNDRV_DMA_TYPE_CONTINUOUS)
		ss->runसमय->dma_addr = __pa(ss->runसमय->dma_area);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_harmony_playback_ops = अणु
	.खोलो =	snd_harmony_playback_खोलो,
	.बंद = snd_harmony_playback_बंद,
	.hw_params = snd_harmony_hw_params,
	.prepare = snd_harmony_playback_prepare,
	.trigger = snd_harmony_playback_trigger,
 	.poपूर्णांकer = snd_harmony_playback_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_harmony_capture_ops = अणु
        .खोलो = snd_harmony_capture_खोलो,
        .बंद = snd_harmony_capture_बंद,
        .hw_params = snd_harmony_hw_params,
        .prepare = snd_harmony_capture_prepare,
        .trigger = snd_harmony_capture_trigger,
        .poपूर्णांकer = snd_harmony_capture_poपूर्णांकer,
पूर्ण;

अटल पूर्णांक 
snd_harmony_pcm_init(काष्ठा snd_harmony *h)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	अगर (snd_BUG_ON(!h))
		वापस -EINVAL;

	harmony_disable_पूर्णांकerrupts(h);
	
   	err = snd_pcm_new(h->card, "harmony", 0, 1, 1, &pcm);
	अगर (err < 0)
		वापस err;
	
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, 
			&snd_harmony_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
			&snd_harmony_capture_ops);

	pcm->निजी_data = h;
	pcm->info_flags = 0;
	म_नकल(pcm->name, "harmony");
	h->pcm = pcm;

	h->psubs = शून्य;
	h->csubs = शून्य;
	
	/* initialize graveyard buffer */
	h->dma.type = SNDRV_DMA_TYPE_DEV;
	h->dma.dev = &h->dev->dev;
	err = snd_dma_alloc_pages(h->dma.type,
				  h->dma.dev,
				  BUF_SIZE*GRAVEYARD_BUFS,
				  &h->gdma);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR PFX "cannot allocate graveyard buffer!\n");
		वापस err;
	पूर्ण
	
	/* initialize silence buffers */
	err = snd_dma_alloc_pages(h->dma.type,
				  h->dma.dev,
				  BUF_SIZE*SILENCE_BUFS,
				  &h->sdma);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR PFX "cannot allocate silence buffer!\n");
		वापस err;
	पूर्ण

	/* pre-allocate space क्रम DMA */
	snd_pcm_set_managed_buffer_all(pcm, h->dma.type, h->dma.dev,
				       MAX_BUF_SIZE, MAX_BUF_SIZE);

	h->st.क्रमmat = snd_harmony_set_data_क्रमmat(h,
		SNDRV_PCM_FORMAT_S16_BE, 1);

	वापस 0;
पूर्ण

अटल व्योम 
snd_harmony_set_new_gain(काष्ठा snd_harmony *h)
अणु
 	harmony_रुको_क्रम_control(h);
	harmony_ग_लिखो(h, HARMONY_GAINCTL, h->st.gain);
पूर्ण

अटल पूर्णांक 
snd_harmony_mixercontrol_info(काष्ठा snd_kcontrol *kc, 
			      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक mask = (kc->निजी_value >> 16) & 0xff;
	पूर्णांक left_shअगरt = (kc->निजी_value) & 0xff;
	पूर्णांक right_shअगरt = (kc->निजी_value >> 8) & 0xff;
	
	uinfo->type = mask == 1 ? SNDRV_CTL_ELEM_TYPE_BOOLEAN : 
		       SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = left_shअगरt == right_shअगरt ? 1 : 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = mask;

	वापस 0;
पूर्ण

अटल पूर्णांक 
snd_harmony_volume_get(काष्ठा snd_kcontrol *kc, 
		       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_harmony *h = snd_kcontrol_chip(kc);
	पूर्णांक shअगरt_left = (kc->निजी_value) & 0xff;
	पूर्णांक shअगरt_right = (kc->निजी_value >> 8) & 0xff;
	पूर्णांक mask = (kc->निजी_value >> 16) & 0xff;
	पूर्णांक invert = (kc->निजी_value >> 24) & 0xff;
	पूर्णांक left, right;
	
	spin_lock_irq(&h->mixer_lock);

	left = (h->st.gain >> shअगरt_left) & mask;
	right = (h->st.gain >> shअगरt_right) & mask;
	अगर (invert) अणु
		left = mask - left;
		right = mask - right;
	पूर्ण
	
	ucontrol->value.पूर्णांकeger.value[0] = left;
	अगर (shअगरt_left != shअगरt_right)
		ucontrol->value.पूर्णांकeger.value[1] = right;

	spin_unlock_irq(&h->mixer_lock);

	वापस 0;
पूर्ण  

अटल पूर्णांक 
snd_harmony_volume_put(काष्ठा snd_kcontrol *kc, 
		       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_harmony *h = snd_kcontrol_chip(kc);
	पूर्णांक shअगरt_left = (kc->निजी_value) & 0xff;
	पूर्णांक shअगरt_right = (kc->निजी_value >> 8) & 0xff;
	पूर्णांक mask = (kc->निजी_value >> 16) & 0xff;
	पूर्णांक invert = (kc->निजी_value >> 24) & 0xff;
	पूर्णांक left, right;
	पूर्णांक old_gain = h->st.gain;
	
	spin_lock_irq(&h->mixer_lock);

	left = ucontrol->value.पूर्णांकeger.value[0] & mask;
	अगर (invert)
		left = mask - left;
	h->st.gain &= ~( (mask << shअगरt_left ) );
 	h->st.gain |= (left << shअगरt_left);

	अगर (shअगरt_left != shअगरt_right) अणु
		right = ucontrol->value.पूर्णांकeger.value[1] & mask;
		अगर (invert)
			right = mask - right;
		h->st.gain &= ~( (mask << shअगरt_right) );
		h->st.gain |= (right << shअगरt_right);
	पूर्ण

	snd_harmony_set_new_gain(h);

	spin_unlock_irq(&h->mixer_lock);
	
	वापस h->st.gain != old_gain;
पूर्ण

अटल पूर्णांक 
snd_harmony_captureroute_info(काष्ठा snd_kcontrol *kc, 
			      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[2] = अणु "Line", "Mic" पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, texts);
पूर्ण

अटल पूर्णांक 
snd_harmony_captureroute_get(काष्ठा snd_kcontrol *kc, 
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_harmony *h = snd_kcontrol_chip(kc);
	पूर्णांक value;
	
	spin_lock_irq(&h->mixer_lock);

	value = (h->st.gain >> HARMONY_GAIN_IS_SHIFT) & 1;
	ucontrol->value.क्रमागतerated.item[0] = value;

	spin_unlock_irq(&h->mixer_lock);

	वापस 0;
पूर्ण  

अटल पूर्णांक 
snd_harmony_captureroute_put(काष्ठा snd_kcontrol *kc, 
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_harmony *h = snd_kcontrol_chip(kc);
	पूर्णांक value;
	पूर्णांक old_gain = h->st.gain;
	
	spin_lock_irq(&h->mixer_lock);

	value = ucontrol->value.क्रमागतerated.item[0] & 1;
	h->st.gain &= ~HARMONY_GAIN_IS_MASK;
 	h->st.gain |= value << HARMONY_GAIN_IS_SHIFT;

	snd_harmony_set_new_gain(h);

	spin_unlock_irq(&h->mixer_lock);
	
	वापस h->st.gain != old_gain;
पूर्ण

#घोषणा HARMONY_CONTROLS	ARRAY_SIZE(snd_harmony_controls)

#घोषणा HARMONY_VOLUME(xname, left_shअगरt, right_shअगरt, mask, invert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname,                \
  .info = snd_harmony_mixercontrol_info,                             \
  .get = snd_harmony_volume_get, .put = snd_harmony_volume_put,      \
  .निजी_value = ((left_shअगरt) | ((right_shअगरt) << 8) |            \
                   ((mask) << 16) | ((invert) << 24)) पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_harmony_controls[] = अणु
	HARMONY_VOLUME("Master Playback Volume", HARMONY_GAIN_LO_SHIFT, 
		       HARMONY_GAIN_RO_SHIFT, HARMONY_GAIN_OUT, 1),
	HARMONY_VOLUME("Capture Volume", HARMONY_GAIN_LI_SHIFT,
		       HARMONY_GAIN_RI_SHIFT, HARMONY_GAIN_IN, 0),
	HARMONY_VOLUME("Monitor Volume", HARMONY_GAIN_MA_SHIFT,
		       HARMONY_GAIN_MA_SHIFT, HARMONY_GAIN_MA, 1),
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Input Route",
		.info = snd_harmony_captureroute_info,
		.get = snd_harmony_captureroute_get,
		.put = snd_harmony_captureroute_put
	पूर्ण,
	HARMONY_VOLUME("Internal Speaker Switch", HARMONY_GAIN_SE_SHIFT,
		       HARMONY_GAIN_SE_SHIFT, 1, 0),
	HARMONY_VOLUME("Line-Out Switch", HARMONY_GAIN_LE_SHIFT,
		       HARMONY_GAIN_LE_SHIFT, 1, 0),
	HARMONY_VOLUME("Headphones Switch", HARMONY_GAIN_HE_SHIFT,
		       HARMONY_GAIN_HE_SHIFT, 1, 0),
पूर्ण;

अटल व्योम
snd_harmony_mixer_reset(काष्ठा snd_harmony *h)
अणु
	harmony_mute(h);
	harmony_reset(h);
	h->st.gain = HARMONY_GAIN_DEFAULT;
	harmony_unmute(h);
पूर्ण

अटल पूर्णांक
snd_harmony_mixer_init(काष्ठा snd_harmony *h)
अणु
	काष्ठा snd_card *card;
	पूर्णांक idx, err;

	अगर (snd_BUG_ON(!h))
		वापस -EINVAL;
	card = h->card;
	म_नकल(card->mixername, "Harmony Gain control interface");

	क्रम (idx = 0; idx < HARMONY_CONTROLS; idx++) अणु
		err = snd_ctl_add(card, 
				  snd_ctl_new1(&snd_harmony_controls[idx], h));
		अगर (err < 0)
			वापस err;
	पूर्ण
	
	snd_harmony_mixer_reset(h);

	वापस 0;
पूर्ण

अटल पूर्णांक
snd_harmony_मुक्त(काष्ठा snd_harmony *h)
अणु
        अगर (h->gdma.addr)
                snd_dma_मुक्त_pages(&h->gdma);
        अगर (h->sdma.addr)
                snd_dma_मुक्त_pages(&h->sdma);

	अगर (h->irq >= 0)
		मुक्त_irq(h->irq, h);

	iounmap(h->iobase);
	kमुक्त(h);
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_harmony_dev_मुक्त(काष्ठा snd_device *dev)
अणु
	काष्ठा snd_harmony *h = dev->device_data;
	वापस snd_harmony_मुक्त(h);
पूर्ण

अटल पूर्णांक
snd_harmony_create(काष्ठा snd_card *card, 
		   काष्ठा parisc_device *padev, 
		   काष्ठा snd_harmony **rchip)
अणु
	पूर्णांक err;
	काष्ठा snd_harmony *h;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त = snd_harmony_dev_मुक्त,
	पूर्ण;

	*rchip = शून्य;

	h = kzalloc(माप(*h), GFP_KERNEL);
	अगर (h == शून्य)
		वापस -ENOMEM;

	h->hpa = padev->hpa.start;
	h->card = card;
	h->dev = padev;
	h->irq = -1;
	h->iobase = ioremap(padev->hpa.start, HARMONY_SIZE);
	अगर (h->iobase == शून्य) अणु
		prपूर्णांकk(KERN_ERR PFX "unable to remap hpa 0x%lx\n",
		       (अचिन्हित दीर्घ)padev->hpa.start);
		err = -EBUSY;
		जाओ मुक्त_and_ret;
	पूर्ण
		
	err = request_irq(padev->irq, snd_harmony_पूर्णांकerrupt, 0,
			  "harmony", h);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR PFX "could not obtain interrupt %d",
		       padev->irq);
		जाओ मुक्त_and_ret;
	पूर्ण
	h->irq = padev->irq;

	spin_lock_init(&h->mixer_lock);
	spin_lock_init(&h->lock);

        अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL,
                                  h, &ops)) < 0) अणु
                जाओ मुक्त_and_ret;
        पूर्ण

	*rchip = h;

	वापस 0;

मुक्त_and_ret:
	snd_harmony_मुक्त(h);
	वापस err;
पूर्ण

अटल पूर्णांक __init
snd_harmony_probe(काष्ठा parisc_device *padev)
अणु
	पूर्णांक err;
	काष्ठा snd_card *card;
	काष्ठा snd_harmony *h;

	err = snd_card_new(&padev->dev, index, id, THIS_MODULE, 0, &card);
	अगर (err < 0)
		वापस err;

	err = snd_harmony_create(card, padev, &h);
	अगर (err < 0)
		जाओ मुक्त_and_ret;

	err = snd_harmony_pcm_init(h);
	अगर (err < 0)
		जाओ मुक्त_and_ret;

	err = snd_harmony_mixer_init(h);
	अगर (err < 0)
		जाओ मुक्त_and_ret;

	म_नकल(card->driver, "harmony");
	म_नकल(card->लघुname, "Harmony");
	प्र_लिखो(card->दीर्घname, "%s at 0x%lx, irq %i",
		card->लघुname, h->hpa, h->irq);

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ मुक्त_and_ret;

	parisc_set_drvdata(padev, card);
	वापस 0;

मुक्त_and_ret:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल पूर्णांक __निकास
snd_harmony_हटाओ(काष्ठा parisc_device *padev)
अणु
	snd_card_मुक्त(parisc_get_drvdata(padev));
	वापस 0;
पूर्ण

अटल काष्ठा parisc_driver snd_harmony_driver __refdata = अणु
	.name = "harmony",
	.id_table = snd_harmony_devtable,
	.probe = snd_harmony_probe,
	.हटाओ = __निकास_p(snd_harmony_हटाओ),
पूर्ण;

अटल पूर्णांक __init 
alsa_harmony_init(व्योम)
अणु
	वापस रेजिस्टर_parisc_driver(&snd_harmony_driver);
पूर्ण

अटल व्योम __निकास
alsa_harmony_fini(व्योम)
अणु
	unरेजिस्टर_parisc_driver(&snd_harmony_driver);
पूर्ण

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kyle McMartin <kyle@parisc-linux.org>");
MODULE_DESCRIPTION("Harmony sound driver");

module_init(alsa_harmony_init);
module_निकास(alsa_harmony_fini);
