<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * i2sbus driver -- pcm routines
 *
 * Copyright 2006 Johannes Berg <johannes@sipsolutions.net>
 */

#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <यंत्र/macपन.स>
#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश "../soundbus.h"
#समावेश "i2sbus.h"

अटल अंतरभूत व्योम get_pcm_info(काष्ठा i2sbus_dev *i2sdev, पूर्णांक in,
				काष्ठा pcm_info **pi, काष्ठा pcm_info **other)
अणु
	अगर (in) अणु
		अगर (pi)
			*pi = &i2sdev->in;
		अगर (other)
			*other = &i2sdev->out;
	पूर्ण अन्यथा अणु
		अगर (pi)
			*pi = &i2sdev->out;
		अगर (other)
			*other = &i2sdev->in;
	पूर्ण
पूर्ण

अटल पूर्णांक घड़ी_and_भागisors(पूर्णांक mclk, पूर्णांक sclk, पूर्णांक rate, पूर्णांक *out)
अणु
	/* sclk must be derived from mclk! */
	अगर (mclk % sclk)
		वापस -1;
	/* derive sclk रेजिस्टर value */
	अगर (i2s_sf_sclkभाग(mclk / sclk, out))
		वापस -1;

	अगर (I2S_CLOCK_SPEED_18MHz % (rate * mclk) == 0) अणु
		अगर (!i2s_sf_mclkभाग(I2S_CLOCK_SPEED_18MHz / (rate * mclk), out)) अणु
			*out |= I2S_SF_CLOCK_SOURCE_18MHz;
			वापस 0;
		पूर्ण
	पूर्ण
	अगर (I2S_CLOCK_SPEED_45MHz % (rate * mclk) == 0) अणु
		अगर (!i2s_sf_mclkभाग(I2S_CLOCK_SPEED_45MHz / (rate * mclk), out)) अणु
			*out |= I2S_SF_CLOCK_SOURCE_45MHz;
			वापस 0;
		पूर्ण
	पूर्ण
	अगर (I2S_CLOCK_SPEED_49MHz % (rate * mclk) == 0) अणु
		अगर (!i2s_sf_mclkभाग(I2S_CLOCK_SPEED_49MHz / (rate * mclk), out)) अणु
			*out |= I2S_SF_CLOCK_SOURCE_49MHz;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -1;
पूर्ण

#घोषणा CHECK_RATE(rate)						\
	करो अणु अगर (rates & SNDRV_PCM_RATE_ ##rate) अणु			\
		पूर्णांक dummy;						\
		अगर (घड़ी_and_भागisors(sysघड़ी_factor,			\
				       bus_factor, rate, &dummy))	\
			rates &= ~SNDRV_PCM_RATE_ ##rate;		\
	पूर्ण पूर्ण जबतक (0)

अटल पूर्णांक i2sbus_pcm_खोलो(काष्ठा i2sbus_dev *i2sdev, पूर्णांक in)
अणु
	काष्ठा pcm_info *pi, *other;
	काष्ठा soundbus_dev *sdev;
	पूर्णांक masks_inited = 0, err;
	काष्ठा codec_info_item *cii, *rev;
	काष्ठा snd_pcm_hardware *hw;
	u64 क्रमmats = 0;
	अचिन्हित पूर्णांक rates = 0;
	काष्ठा transfer_info v;
	पूर्णांक result = 0;
	पूर्णांक bus_factor = 0, sysघड़ी_factor = 0;
	पूर्णांक found_this;

	mutex_lock(&i2sdev->lock);

	get_pcm_info(i2sdev, in, &pi, &other);

	hw = &pi->substream->runसमय->hw;
	sdev = &i2sdev->sound;

	अगर (pi->active) अणु
		/* alsa messed up */
		result = -EBUSY;
		जाओ out_unlock;
	पूर्ण

	/* we now need to assign the hw */
	list_क्रम_each_entry(cii, &sdev->codec_list, list) अणु
		काष्ठा transfer_info *ti = cii->codec->transfers;
		bus_factor = cii->codec->bus_factor;
		sysघड़ी_factor = cii->codec->sysघड़ी_factor;
		जबतक (ti->क्रमmats && ti->rates) अणु
			v = *ti;
			अगर (ti->transfer_in == in
			    && cii->codec->usable(cii, ti, &v)) अणु
				अगर (masks_inited) अणु
					क्रमmats &= v.क्रमmats;
					rates &= v.rates;
				पूर्ण अन्यथा अणु
					क्रमmats = v.क्रमmats;
					rates = v.rates;
					masks_inited = 1;
				पूर्ण
			पूर्ण
			ti++;
		पूर्ण
	पूर्ण
	अगर (!masks_inited || !bus_factor || !sysघड़ी_factor) अणु
		result = -ENODEV;
		जाओ out_unlock;
	पूर्ण
	/* bus dependent stuff */
	hw->info = SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_MMAP_VALID |
		   SNDRV_PCM_INFO_INTERLEAVED | SNDRV_PCM_INFO_RESUME |
		   SNDRV_PCM_INFO_JOINT_DUPLEX;

	CHECK_RATE(5512);
	CHECK_RATE(8000);
	CHECK_RATE(11025);
	CHECK_RATE(16000);
	CHECK_RATE(22050);
	CHECK_RATE(32000);
	CHECK_RATE(44100);
	CHECK_RATE(48000);
	CHECK_RATE(64000);
	CHECK_RATE(88200);
	CHECK_RATE(96000);
	CHECK_RATE(176400);
	CHECK_RATE(192000);
	hw->rates = rates;

	/* well. the codec might want 24 bits only, and we'll
	 * ever only transfer 24 bits, but they are top-aligned!
	 * So क्रम alsa, we claim that we're करोing full 32 bit
	 * जबतक in reality we'll ignore the lower 8 bits of
	 * that when करोing playback (they're transferred as 0
	 * as far as I know, no codecs we have are 32-bit capable
	 * so I can't really test) and when doing recording we'll
	 * always have those lower 8 bits recorded as 0 */
	अगर (क्रमmats & SNDRV_PCM_FMTBIT_S24_BE)
		क्रमmats |= SNDRV_PCM_FMTBIT_S32_BE;
	अगर (क्रमmats & SNDRV_PCM_FMTBIT_U24_BE)
		क्रमmats |= SNDRV_PCM_FMTBIT_U32_BE;
	/* now mask off what we can support. I suppose we could
	 * also support S24_3LE and some similar क्रमmats, but I
	 * करोubt there's a codec that would be able to use that,
	 * so we करोn't support it here. */
	hw->क्रमmats = क्रमmats & (SNDRV_PCM_FMTBIT_S16_BE |
				 SNDRV_PCM_FMTBIT_U16_BE |
				 SNDRV_PCM_FMTBIT_S32_BE |
				 SNDRV_PCM_FMTBIT_U32_BE);

	/* we need to set the highest and lowest rate possible.
	 * These are the highest and lowest rates alsa can
	 * support properly in its bitfield.
	 * Below, we'll use that to restrict to the rate
	 * currently in use (अगर any). */
	hw->rate_min = 5512;
	hw->rate_max = 192000;
	/* अगर the other stream is active, then we can only
	 * support what it is currently using.
	 * FIXME: I lied. This comment is wrong. We can support
	 * anything that works with the same serial क्रमmat, ie.
	 * when recording 24 bit sound we can well play 16 bit
	 * sound at the same समय अगरf using the same transfer mode.
	 */
	अगर (other->active) अणु
		/* FIXME: is this guaranteed by the alsa api? */
		hw->क्रमmats &= pcm_क्रमmat_to_bits(i2sdev->क्रमmat);
		/* see above, restrict rates to the one we alपढ़ोy have */
		hw->rate_min = i2sdev->rate;
		hw->rate_max = i2sdev->rate;
	पूर्ण

	hw->channels_min = 2;
	hw->channels_max = 2;
	/* these are somewhat arbitrary */
	hw->buffer_bytes_max = 131072;
	hw->period_bytes_min = 256;
	hw->period_bytes_max = 16384;
	hw->periods_min = 3;
	hw->periods_max = MAX_DBDMA_COMMANDS;
	err = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(pi->substream->runसमय,
					    SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (err < 0) अणु
		result = err;
		जाओ out_unlock;
	पूर्ण
	list_क्रम_each_entry(cii, &sdev->codec_list, list) अणु
		अगर (cii->codec->खोलो) अणु
			err = cii->codec->खोलो(cii, pi->substream);
			अगर (err) अणु
				result = err;
				/* unwind */
				found_this = 0;
				list_क्रम_each_entry_reverse(rev,
				    &sdev->codec_list, list) अणु
					अगर (found_this && rev->codec->बंद) अणु
						rev->codec->बंद(rev,
								pi->substream);
					पूर्ण
					अगर (rev == cii)
						found_this = 1;
				पूर्ण
				जाओ out_unlock;
			पूर्ण
		पूर्ण
	पूर्ण

 out_unlock:
	mutex_unlock(&i2sdev->lock);
	वापस result;
पूर्ण

#अघोषित CHECK_RATE

अटल पूर्णांक i2sbus_pcm_बंद(काष्ठा i2sbus_dev *i2sdev, पूर्णांक in)
अणु
	काष्ठा codec_info_item *cii;
	काष्ठा pcm_info *pi;
	पूर्णांक err = 0, पंचांगp;

	mutex_lock(&i2sdev->lock);

	get_pcm_info(i2sdev, in, &pi, शून्य);

	list_क्रम_each_entry(cii, &i2sdev->sound.codec_list, list) अणु
		अगर (cii->codec->बंद) अणु
			पंचांगp = cii->codec->बंद(cii, pi->substream);
			अगर (पंचांगp)
				err = पंचांगp;
		पूर्ण
	पूर्ण

	pi->substream = शून्य;
	pi->active = 0;
	mutex_unlock(&i2sdev->lock);
	वापस err;
पूर्ण

अटल व्योम i2sbus_रुको_क्रम_stop(काष्ठा i2sbus_dev *i2sdev,
				 काष्ठा pcm_info *pi)
अणु
	अचिन्हित दीर्घ flags;
	DECLARE_COMPLETION_ONSTACK(करोne);
	दीर्घ समयout;

	spin_lock_irqsave(&i2sdev->low_lock, flags);
	अगर (pi->dbdma_ring.stopping) अणु
		pi->stop_completion = &करोne;
		spin_unlock_irqrestore(&i2sdev->low_lock, flags);
		समयout = रुको_क्रम_completion_समयout(&करोne, HZ);
		spin_lock_irqsave(&i2sdev->low_lock, flags);
		pi->stop_completion = शून्य;
		अगर (समयout == 0) अणु
			/* समयout expired, stop dbdma क्रमcefully */
			prपूर्णांकk(KERN_ERR "i2sbus_wait_for_stop: timed out\n");
			/* make sure RUN, PAUSE and S0 bits are cleared */
			out_le32(&pi->dbdma->control, (RUN | PAUSE | 1) << 16);
			pi->dbdma_ring.stopping = 0;
			समयout = 10;
			जबतक (in_le32(&pi->dbdma->status) & ACTIVE) अणु
				अगर (--समयout <= 0)
					अवरोध;
				udelay(1);
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&i2sdev->low_lock, flags);
पूर्ण

#अगर_घोषित CONFIG_PM
व्योम i2sbus_रुको_क्रम_stop_both(काष्ठा i2sbus_dev *i2sdev)
अणु
	काष्ठा pcm_info *pi;

	get_pcm_info(i2sdev, 0, &pi, शून्य);
	i2sbus_रुको_क्रम_stop(i2sdev, pi);
	get_pcm_info(i2sdev, 1, &pi, शून्य);
	i2sbus_रुको_क्रम_stop(i2sdev, pi);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक i2sbus_hw_मुक्त(काष्ठा snd_pcm_substream *substream, पूर्णांक in)
अणु
	काष्ठा i2sbus_dev *i2sdev = snd_pcm_substream_chip(substream);
	काष्ठा pcm_info *pi;

	get_pcm_info(i2sdev, in, &pi, शून्य);
	अगर (pi->dbdma_ring.stopping)
		i2sbus_रुको_क्रम_stop(i2sdev, pi);
	वापस 0;
पूर्ण

अटल पूर्णांक i2sbus_playback_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	वापस i2sbus_hw_मुक्त(substream, 0);
पूर्ण

अटल पूर्णांक i2sbus_record_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	वापस i2sbus_hw_मुक्त(substream, 1);
पूर्ण

अटल पूर्णांक i2sbus_pcm_prepare(काष्ठा i2sbus_dev *i2sdev, पूर्णांक in)
अणु
	/* whee. Hard work now. The user has selected a bitrate
	 * and bit क्रमmat, so now we have to program our
	 * I2S controller appropriately. */
	काष्ठा snd_pcm_runसमय *runसमय;
	काष्ठा dbdma_cmd *command;
	पूर्णांक i, periodsize, nperiods;
	dma_addr_t offset;
	काष्ठा bus_info bi;
	काष्ठा codec_info_item *cii;
	पूर्णांक sfr = 0;		/* serial क्रमmat रेजिस्टर */
	पूर्णांक dws = 0;		/* data word sizes reg */
	पूर्णांक input_16bit;
	काष्ठा pcm_info *pi, *other;
	पूर्णांक cnt;
	पूर्णांक result = 0;
	अचिन्हित पूर्णांक cmd, stopaddr;

	mutex_lock(&i2sdev->lock);

	get_pcm_info(i2sdev, in, &pi, &other);

	अगर (pi->dbdma_ring.running) अणु
		result = -EBUSY;
		जाओ out_unlock;
	पूर्ण
	अगर (pi->dbdma_ring.stopping)
		i2sbus_रुको_क्रम_stop(i2sdev, pi);

	अगर (!pi->substream || !pi->substream->runसमय) अणु
		result = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	runसमय = pi->substream->runसमय;
	pi->active = 1;
	अगर (other->active &&
	    ((i2sdev->क्रमmat != runसमय->क्रमmat)
	     || (i2sdev->rate != runसमय->rate))) अणु
		result = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	i2sdev->क्रमmat = runसमय->क्रमmat;
	i2sdev->rate = runसमय->rate;

	periodsize = snd_pcm_lib_period_bytes(pi->substream);
	nperiods = pi->substream->runसमय->periods;
	pi->current_period = 0;

	/* generate dbdma command ring first */
	command = pi->dbdma_ring.cmds;
	स_रखो(command, 0, (nperiods + 2) * माप(काष्ठा dbdma_cmd));

	/* commands to DMA to/from the ring */
	/*
	 * For input, we need to करो a graceful stop; अगर we पात
	 * the DMA, we end up with leftover bytes that corrupt
	 * the next recording.  To करो this we set the S0 status
	 * bit and रुको क्रम the DMA controller to stop.  Each
	 * command has a branch condition to
	 * make it branch to a stop command अगर S0 is set.
	 * On input we also need to रुको क्रम the S7 bit to be
	 * set beक्रमe turning off the DMA controller.
	 * In fact we करो the graceful stop क्रम output as well.
	 */
	offset = runसमय->dma_addr;
	cmd = (in? INPUT_MORE: OUTPUT_MORE) | BR_IFSET | INTR_ALWAYS;
	stopaddr = pi->dbdma_ring.bus_cmd_start +
		(nperiods + 1) * माप(काष्ठा dbdma_cmd);
	क्रम (i = 0; i < nperiods; i++, command++, offset += periodsize) अणु
		command->command = cpu_to_le16(cmd);
		command->cmd_dep = cpu_to_le32(stopaddr);
		command->phy_addr = cpu_to_le32(offset);
		command->req_count = cpu_to_le16(periodsize);
	पूर्ण

	/* branch back to beginning of ring */
	command->command = cpu_to_le16(DBDMA_NOP | BR_ALWAYS);
	command->cmd_dep = cpu_to_le32(pi->dbdma_ring.bus_cmd_start);
	command++;

	/* set stop command */
	command->command = cpu_to_le16(DBDMA_STOP);

	/* ok, let's set the serial क्रमmat and stuff */
	चयन (runसमय->क्रमmat) अणु
	/* 16 bit क्रमmats */
	हाल SNDRV_PCM_FORMAT_S16_BE:
	हाल SNDRV_PCM_FORMAT_U16_BE:
		/* FIXME: अगर we add dअगरferent bus factors we need to
		 * करो more here!! */
		bi.bus_factor = 0;
		list_क्रम_each_entry(cii, &i2sdev->sound.codec_list, list) अणु
			bi.bus_factor = cii->codec->bus_factor;
			अवरोध;
		पूर्ण
		अगर (!bi.bus_factor) अणु
			result = -ENODEV;
			जाओ out_unlock;
		पूर्ण
		input_16bit = 1;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_BE:
	हाल SNDRV_PCM_FORMAT_U32_BE:
		/* क्रमce 64x bus speed, otherwise the data cannot be
		 * transferred quickly enough! */
		bi.bus_factor = 64;
		input_16bit = 0;
		अवरोध;
	शेष:
		result = -EINVAL;
		जाओ out_unlock;
	पूर्ण
	/* we assume all sysघड़ीs are the same! */
	list_क्रम_each_entry(cii, &i2sdev->sound.codec_list, list) अणु
		bi.sysघड़ी_factor = cii->codec->sysघड़ी_factor;
		अवरोध;
	पूर्ण

	अगर (घड़ी_and_भागisors(bi.sysघड़ी_factor,
			       bi.bus_factor,
			       runसमय->rate,
			       &sfr) < 0) अणु
		result = -EINVAL;
		जाओ out_unlock;
	पूर्ण
	चयन (bi.bus_factor) अणु
	हाल 32:
		sfr |= I2S_SF_SERIAL_FORMAT_I2S_32X;
		अवरोध;
	हाल 64:
		sfr |= I2S_SF_SERIAL_FORMAT_I2S_64X;
		अवरोध;
	पूर्ण
	/* FIXME: THIS ASSUMES MASTER ALL THE TIME */
	sfr |= I2S_SF_SCLK_MASTER;

	list_क्रम_each_entry(cii, &i2sdev->sound.codec_list, list) अणु
		पूर्णांक err = 0;
		अगर (cii->codec->prepare)
			err = cii->codec->prepare(cii, &bi, pi->substream);
		अगर (err) अणु
			result = err;
			जाओ out_unlock;
		पूर्ण
	पूर्ण
	/* codecs are fine with it, so set our घड़ीs */
	अगर (input_16bit)
		dws =	(2 << I2S_DWS_NUM_CHANNELS_IN_SHIFT) |
			(2 << I2S_DWS_NUM_CHANNELS_OUT_SHIFT) |
			I2S_DWS_DATA_IN_16BIT | I2S_DWS_DATA_OUT_16BIT;
	अन्यथा
		dws =	(2 << I2S_DWS_NUM_CHANNELS_IN_SHIFT) |
			(2 << I2S_DWS_NUM_CHANNELS_OUT_SHIFT) |
			I2S_DWS_DATA_IN_24BIT | I2S_DWS_DATA_OUT_24BIT;

	/* early निकास अगर alपढ़ोy programmed correctly */
	/* not locking these is fine since we touch them only in this function */
	अगर (in_le32(&i2sdev->पूर्णांकfregs->serial_क्रमmat) == sfr
	 && in_le32(&i2sdev->पूर्णांकfregs->data_word_sizes) == dws)
		जाओ out_unlock;

	/* let's notअगरy the codecs about घड़ीs going away.
	 * For now we only करो mastering on the i2s cell... */
	list_क्रम_each_entry(cii, &i2sdev->sound.codec_list, list)
		अगर (cii->codec->चयन_घड़ी)
			cii->codec->चयन_घड़ी(cii, CLOCK_SWITCH_PREPARE_SLAVE);

	i2sbus_control_enable(i2sdev->control, i2sdev);
	i2sbus_control_cell(i2sdev->control, i2sdev, 1);

	out_le32(&i2sdev->पूर्णांकfregs->पूर्णांकr_ctl, I2S_PENDING_CLOCKS_STOPPED);

	i2sbus_control_घड़ी(i2sdev->control, i2sdev, 0);

	msleep(1);

	/* रुको क्रम घड़ी stopped. This can apparently take a जबतक... */
	cnt = 100;
	जबतक (cnt-- &&
	    !(in_le32(&i2sdev->पूर्णांकfregs->पूर्णांकr_ctl) & I2S_PENDING_CLOCKS_STOPPED)) अणु
		msleep(5);
	पूर्ण
	out_le32(&i2sdev->पूर्णांकfregs->पूर्णांकr_ctl, I2S_PENDING_CLOCKS_STOPPED);

	/* not locking these is fine since we touch them only in this function */
	out_le32(&i2sdev->पूर्णांकfregs->serial_क्रमmat, sfr);
	out_le32(&i2sdev->पूर्णांकfregs->data_word_sizes, dws);

        i2sbus_control_enable(i2sdev->control, i2sdev);
        i2sbus_control_cell(i2sdev->control, i2sdev, 1);
        i2sbus_control_घड़ी(i2sdev->control, i2sdev, 1);
	msleep(1);

	list_क्रम_each_entry(cii, &i2sdev->sound.codec_list, list)
		अगर (cii->codec->चयन_घड़ी)
			cii->codec->चयन_घड़ी(cii, CLOCK_SWITCH_SLAVE);

 out_unlock:
	mutex_unlock(&i2sdev->lock);
	वापस result;
पूर्ण

#अगर_घोषित CONFIG_PM
व्योम i2sbus_pcm_prepare_both(काष्ठा i2sbus_dev *i2sdev)
अणु
	i2sbus_pcm_prepare(i2sdev, 0);
	i2sbus_pcm_prepare(i2sdev, 1);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक i2sbus_pcm_trigger(काष्ठा i2sbus_dev *i2sdev, पूर्णांक in, पूर्णांक cmd)
अणु
	काष्ठा codec_info_item *cii;
	काष्ठा pcm_info *pi;
	पूर्णांक result = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&i2sdev->low_lock, flags);

	get_pcm_info(i2sdev, in, &pi, शून्य);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		अगर (pi->dbdma_ring.running) अणु
			result = -EALREADY;
			जाओ out_unlock;
		पूर्ण
		list_क्रम_each_entry(cii, &i2sdev->sound.codec_list, list)
			अगर (cii->codec->start)
				cii->codec->start(cii, pi->substream);
		pi->dbdma_ring.running = 1;

		अगर (pi->dbdma_ring.stopping) अणु
			/* Clear the S0 bit, then see अगर we stopped yet */
			out_le32(&pi->dbdma->control, 1 << 16);
			अगर (in_le32(&pi->dbdma->status) & ACTIVE) अणु
				/* possible race here? */
				udelay(10);
				अगर (in_le32(&pi->dbdma->status) & ACTIVE) अणु
					pi->dbdma_ring.stopping = 0;
					जाओ out_unlock; /* keep running */
				पूर्ण
			पूर्ण
		पूर्ण

		/* make sure RUN, PAUSE and S0 bits are cleared */
		out_le32(&pi->dbdma->control, (RUN | PAUSE | 1) << 16);

		/* set branch condition select रेजिस्टर */
		out_le32(&pi->dbdma->br_sel, (1 << 16) | 1);

		/* ग_लिखो dma command buffer address to the dbdma chip */
		out_le32(&pi->dbdma->cmdptr, pi->dbdma_ring.bus_cmd_start);

		/* initialize the frame count and current period */
		pi->current_period = 0;
		pi->frame_count = in_le32(&i2sdev->पूर्णांकfregs->frame_count);

		/* set the DMA controller running */
		out_le32(&pi->dbdma->control, (RUN << 16) | RUN);

		/* off you go! */
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		अगर (!pi->dbdma_ring.running) अणु
			result = -EALREADY;
			जाओ out_unlock;
		पूर्ण
		pi->dbdma_ring.running = 0;

		/* Set the S0 bit to make the DMA branch to the stop cmd */
		out_le32(&pi->dbdma->control, (1 << 16) | 1);
		pi->dbdma_ring.stopping = 1;

		list_क्रम_each_entry(cii, &i2sdev->sound.codec_list, list)
			अगर (cii->codec->stop)
				cii->codec->stop(cii, pi->substream);
		अवरोध;
	शेष:
		result = -EINVAL;
		जाओ out_unlock;
	पूर्ण

 out_unlock:
	spin_unlock_irqrestore(&i2sdev->low_lock, flags);
	वापस result;
पूर्ण

अटल snd_pcm_uframes_t i2sbus_pcm_poपूर्णांकer(काष्ठा i2sbus_dev *i2sdev, पूर्णांक in)
अणु
	काष्ठा pcm_info *pi;
	u32 fc;

	get_pcm_info(i2sdev, in, &pi, शून्य);

	fc = in_le32(&i2sdev->पूर्णांकfregs->frame_count);
	fc = fc - pi->frame_count;

	अगर (fc >= pi->substream->runसमय->buffer_size)
		fc %= pi->substream->runसमय->buffer_size;
	वापस fc;
पूर्ण

अटल अंतरभूत व्योम handle_पूर्णांकerrupt(काष्ठा i2sbus_dev *i2sdev, पूर्णांक in)
अणु
	काष्ठा pcm_info *pi;
	u32 fc, nframes;
	u32 status;
	पूर्णांक समयout, i;
	पूर्णांक dma_stopped = 0;
	काष्ठा snd_pcm_runसमय *runसमय;

	spin_lock(&i2sdev->low_lock);
	get_pcm_info(i2sdev, in, &pi, शून्य);
	अगर (!pi->dbdma_ring.running && !pi->dbdma_ring.stopping)
		जाओ out_unlock;

	i = pi->current_period;
	runसमय = pi->substream->runसमय;
	जबतक (pi->dbdma_ring.cmds[i].xfer_status) अणु
		अगर (le16_to_cpu(pi->dbdma_ring.cmds[i].xfer_status) & BT)
			/*
			 * BT is the branch taken bit.  If it took a branch
			 * it is because we set the S0 bit to make it
			 * branch to the stop command.
			 */
			dma_stopped = 1;
		pi->dbdma_ring.cmds[i].xfer_status = 0;

		अगर (++i >= runसमय->periods) अणु
			i = 0;
			pi->frame_count += runसमय->buffer_size;
		पूर्ण
		pi->current_period = i;

		/*
		 * Check the frame count.  The DMA tends to get a bit
		 * ahead of the frame counter, which confuses the core.
		 */
		fc = in_le32(&i2sdev->पूर्णांकfregs->frame_count);
		nframes = i * runसमय->period_size;
		अगर (fc < pi->frame_count + nframes)
			pi->frame_count = fc - nframes;
	पूर्ण

	अगर (dma_stopped) अणु
		समयout = 1000;
		क्रम (;;) अणु
			status = in_le32(&pi->dbdma->status);
			अगर (!(status & ACTIVE) && (!in || (status & 0x80)))
				अवरोध;
			अगर (--समयout <= 0) अणु
				prपूर्णांकk(KERN_ERR "i2sbus: timed out "
				       "waiting for DMA to stop!\n");
				अवरोध;
			पूर्ण
			udelay(1);
		पूर्ण

		/* Turn off DMA controller, clear S0 bit */
		out_le32(&pi->dbdma->control, (RUN | PAUSE | 1) << 16);

		pi->dbdma_ring.stopping = 0;
		अगर (pi->stop_completion)
			complete(pi->stop_completion);
	पूर्ण

	अगर (!pi->dbdma_ring.running)
		जाओ out_unlock;
	spin_unlock(&i2sdev->low_lock);
	/* may call _trigger again, hence needs to be unlocked */
	snd_pcm_period_elapsed(pi->substream);
	वापस;

 out_unlock:
	spin_unlock(&i2sdev->low_lock);
पूर्ण

irqवापस_t i2sbus_tx_पूर्णांकr(पूर्णांक irq, व्योम *devid)
अणु
	handle_पूर्णांकerrupt((काष्ठा i2sbus_dev *)devid, 0);
	वापस IRQ_HANDLED;
पूर्ण

irqवापस_t i2sbus_rx_पूर्णांकr(पूर्णांक irq, व्योम *devid)
अणु
	handle_पूर्णांकerrupt((काष्ठा i2sbus_dev *)devid, 1);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक i2sbus_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा i2sbus_dev *i2sdev = snd_pcm_substream_chip(substream);

	अगर (!i2sdev)
		वापस -EINVAL;
	i2sdev->out.substream = substream;
	वापस i2sbus_pcm_खोलो(i2sdev, 0);
पूर्ण

अटल पूर्णांक i2sbus_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा i2sbus_dev *i2sdev = snd_pcm_substream_chip(substream);
	पूर्णांक err;

	अगर (!i2sdev)
		वापस -EINVAL;
	अगर (i2sdev->out.substream != substream)
		वापस -EINVAL;
	err = i2sbus_pcm_बंद(i2sdev, 0);
	अगर (!err)
		i2sdev->out.substream = शून्य;
	वापस err;
पूर्ण

अटल पूर्णांक i2sbus_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा i2sbus_dev *i2sdev = snd_pcm_substream_chip(substream);

	अगर (!i2sdev)
		वापस -EINVAL;
	अगर (i2sdev->out.substream != substream)
		वापस -EINVAL;
	वापस i2sbus_pcm_prepare(i2sdev, 0);
पूर्ण

अटल पूर्णांक i2sbus_playback_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा i2sbus_dev *i2sdev = snd_pcm_substream_chip(substream);

	अगर (!i2sdev)
		वापस -EINVAL;
	अगर (i2sdev->out.substream != substream)
		वापस -EINVAL;
	वापस i2sbus_pcm_trigger(i2sdev, 0, cmd);
पूर्ण

अटल snd_pcm_uframes_t i2sbus_playback_poपूर्णांकer(काष्ठा snd_pcm_substream
						 *substream)
अणु
	काष्ठा i2sbus_dev *i2sdev = snd_pcm_substream_chip(substream);

	अगर (!i2sdev)
		वापस -EINVAL;
	अगर (i2sdev->out.substream != substream)
		वापस 0;
	वापस i2sbus_pcm_poपूर्णांकer(i2sdev, 0);
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops i2sbus_playback_ops = अणु
	.खोलो =		i2sbus_playback_खोलो,
	.बंद =	i2sbus_playback_बंद,
	.hw_मुक्त =	i2sbus_playback_hw_मुक्त,
	.prepare =	i2sbus_playback_prepare,
	.trigger =	i2sbus_playback_trigger,
	.poपूर्णांकer =	i2sbus_playback_poपूर्णांकer,
पूर्ण;

अटल पूर्णांक i2sbus_record_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा i2sbus_dev *i2sdev = snd_pcm_substream_chip(substream);

	अगर (!i2sdev)
		वापस -EINVAL;
	i2sdev->in.substream = substream;
	वापस i2sbus_pcm_खोलो(i2sdev, 1);
पूर्ण

अटल पूर्णांक i2sbus_record_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा i2sbus_dev *i2sdev = snd_pcm_substream_chip(substream);
	पूर्णांक err;

	अगर (!i2sdev)
		वापस -EINVAL;
	अगर (i2sdev->in.substream != substream)
		वापस -EINVAL;
	err = i2sbus_pcm_बंद(i2sdev, 1);
	अगर (!err)
		i2sdev->in.substream = शून्य;
	वापस err;
पूर्ण

अटल पूर्णांक i2sbus_record_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा i2sbus_dev *i2sdev = snd_pcm_substream_chip(substream);

	अगर (!i2sdev)
		वापस -EINVAL;
	अगर (i2sdev->in.substream != substream)
		वापस -EINVAL;
	वापस i2sbus_pcm_prepare(i2sdev, 1);
पूर्ण

अटल पूर्णांक i2sbus_record_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा i2sbus_dev *i2sdev = snd_pcm_substream_chip(substream);

	अगर (!i2sdev)
		वापस -EINVAL;
	अगर (i2sdev->in.substream != substream)
		वापस -EINVAL;
	वापस i2sbus_pcm_trigger(i2sdev, 1, cmd);
पूर्ण

अटल snd_pcm_uframes_t i2sbus_record_poपूर्णांकer(काष्ठा snd_pcm_substream
					       *substream)
अणु
	काष्ठा i2sbus_dev *i2sdev = snd_pcm_substream_chip(substream);

	अगर (!i2sdev)
		वापस -EINVAL;
	अगर (i2sdev->in.substream != substream)
		वापस 0;
	वापस i2sbus_pcm_poपूर्णांकer(i2sdev, 1);
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops i2sbus_record_ops = अणु
	.खोलो =		i2sbus_record_खोलो,
	.बंद =	i2sbus_record_बंद,
	.hw_मुक्त =	i2sbus_record_hw_मुक्त,
	.prepare =	i2sbus_record_prepare,
	.trigger =	i2sbus_record_trigger,
	.poपूर्णांकer =	i2sbus_record_poपूर्णांकer,
पूर्ण;

अटल व्योम i2sbus_निजी_मुक्त(काष्ठा snd_pcm *pcm)
अणु
	काष्ठा i2sbus_dev *i2sdev = snd_pcm_chip(pcm);
	काष्ठा codec_info_item *p, *पंचांगp;

	i2sdev->sound.pcm = शून्य;
	i2sdev->out.created = 0;
	i2sdev->in.created = 0;
	list_क्रम_each_entry_safe(p, पंचांगp, &i2sdev->sound.codec_list, list) अणु
		prपूर्णांकk(KERN_ERR "i2sbus: a codec didn't unregister!\n");
		list_del(&p->list);
		module_put(p->codec->owner);
		kमुक्त(p);
	पूर्ण
	soundbus_dev_put(&i2sdev->sound);
	module_put(THIS_MODULE);
पूर्ण

पूर्णांक
i2sbus_attach_codec(काष्ठा soundbus_dev *dev, काष्ठा snd_card *card,
		    काष्ठा codec_info *ci, व्योम *data)
अणु
	पूर्णांक err, in = 0, out = 0;
	काष्ठा transfer_info *पंचांगp;
	काष्ठा i2sbus_dev *i2sdev = soundbus_dev_to_i2sbus_dev(dev);
	काष्ठा codec_info_item *cii;

	अगर (!dev->pcmname || dev->pcmid == -1) अणु
		prपूर्णांकk(KERN_ERR "i2sbus: pcm name and id must be set!\n");
		वापस -EINVAL;
	पूर्ण

	list_क्रम_each_entry(cii, &dev->codec_list, list) अणु
		अगर (cii->codec_data == data)
			वापस -EALREADY;
	पूर्ण

	अगर (!ci->transfers || !ci->transfers->क्रमmats
	    || !ci->transfers->rates || !ci->usable)
		वापस -EINVAL;

	/* we currently code the i2s transfer on the घड़ी, and support only
	 * 32 and 64 */
	अगर (ci->bus_factor != 32 && ci->bus_factor != 64)
		वापस -EINVAL;

	/* If you want to fix this, you need to keep track of what transport infos
	 * are to be used, which codecs they beदीर्घ to, and then fix all the
	 * sysघड़ी/busघड़ी stuff above to depend on which is usable */
	list_क्रम_each_entry(cii, &dev->codec_list, list) अणु
		अगर (cii->codec->sysघड़ी_factor != ci->sysघड़ी_factor) अणु
			prपूर्णांकk(KERN_DEBUG
			       "cannot yet handle multiple different sysclocks!\n");
			वापस -EINVAL;
		पूर्ण
		अगर (cii->codec->bus_factor != ci->bus_factor) अणु
			prपूर्णांकk(KERN_DEBUG
			       "cannot yet handle multiple different bus clocks!\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	पंचांगp = ci->transfers;
	जबतक (पंचांगp->क्रमmats && पंचांगp->rates) अणु
		अगर (पंचांगp->transfer_in)
			in = 1;
		अन्यथा
			out = 1;
		पंचांगp++;
	पूर्ण

	cii = kzalloc(माप(काष्ठा codec_info_item), GFP_KERNEL);
	अगर (!cii) अणु
		prपूर्णांकk(KERN_DEBUG "i2sbus: failed to allocate cii\n");
		वापस -ENOMEM;
	पूर्ण

	/* use the निजी data to poपूर्णांक to the codec info */
	cii->sdev = soundbus_dev_get(dev);
	cii->codec = ci;
	cii->codec_data = data;

	अगर (!cii->sdev) अणु
		prपूर्णांकk(KERN_DEBUG
		       "i2sbus: failed to get soundbus dev reference\n");
		err = -ENODEV;
		जाओ out_मुक्त_cii;
	पूर्ण

	अगर (!try_module_get(THIS_MODULE)) अणु
		prपूर्णांकk(KERN_DEBUG "i2sbus: failed to get module reference!\n");
		err = -EBUSY;
		जाओ out_put_sdev;
	पूर्ण

	अगर (!try_module_get(ci->owner)) अणु
		prपूर्णांकk(KERN_DEBUG
		       "i2sbus: failed to get module reference to codec owner!\n");
		err = -EBUSY;
		जाओ out_put_this_module;
	पूर्ण

	अगर (!dev->pcm) अणु
		err = snd_pcm_new(card, dev->pcmname, dev->pcmid, 0, 0,
				  &dev->pcm);
		अगर (err) अणु
			prपूर्णांकk(KERN_DEBUG "i2sbus: failed to create pcm\n");
			जाओ out_put_ci_module;
		पूर्ण
	पूर्ण

	/* ALSA yet again sucks.
	 * If it is ever fixed, हटाओ this line. See below. */
	out = in = 1;

	अगर (!i2sdev->out.created && out) अणु
		अगर (dev->pcm->card != card) अणु
			/* eh? */
			prपूर्णांकk(KERN_ERR
			       "Can't attach same bus to different cards!\n");
			err = -EINVAL;
			जाओ out_put_ci_module;
		पूर्ण
		err = snd_pcm_new_stream(dev->pcm, SNDRV_PCM_STREAM_PLAYBACK, 1);
		अगर (err)
			जाओ out_put_ci_module;
		snd_pcm_set_ops(dev->pcm, SNDRV_PCM_STREAM_PLAYBACK,
				&i2sbus_playback_ops);
		dev->pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].dev.parent =
			&dev->ofdev.dev;
		i2sdev->out.created = 1;
	पूर्ण

	अगर (!i2sdev->in.created && in) अणु
		अगर (dev->pcm->card != card) अणु
			prपूर्णांकk(KERN_ERR
			       "Can't attach same bus to different cards!\n");
			err = -EINVAL;
			जाओ out_put_ci_module;
		पूर्ण
		err = snd_pcm_new_stream(dev->pcm, SNDRV_PCM_STREAM_CAPTURE, 1);
		अगर (err)
			जाओ out_put_ci_module;
		snd_pcm_set_ops(dev->pcm, SNDRV_PCM_STREAM_CAPTURE,
				&i2sbus_record_ops);
		dev->pcm->streams[SNDRV_PCM_STREAM_CAPTURE].dev.parent =
			&dev->ofdev.dev;
		i2sdev->in.created = 1;
	पूर्ण

	/* so we have to रेजिस्टर the pcm after adding any substream
	 * to it because alsa करोesn't create the devices क्रम the
	 * substreams when we add them later.
	 * Thereक्रमe, क्रमce in and out on both busses (above) and
	 * रेजिस्टर the pcm now instead of just after creating it.
	 */
	err = snd_device_रेजिस्टर(card, dev->pcm);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "i2sbus: error registering new pcm\n");
		जाओ out_put_ci_module;
	पूर्ण
	/* no errors any more, so let's add this to our list */
	list_add(&cii->list, &dev->codec_list);

	dev->pcm->निजी_data = i2sdev;
	dev->pcm->निजी_मुक्त = i2sbus_निजी_मुक्त;

	/* well, we really should support scatter/gather DMA */
	snd_pcm_set_managed_buffer_all(
		dev->pcm, SNDRV_DMA_TYPE_DEV,
		&macio_get_pci_dev(i2sdev->macio)->dev,
		64 * 1024, 64 * 1024);

	वापस 0;
 out_put_ci_module:
	module_put(ci->owner);
 out_put_this_module:
	module_put(THIS_MODULE);
 out_put_sdev:
	soundbus_dev_put(dev);
 out_मुक्त_cii:
	kमुक्त(cii);
	वापस err;
पूर्ण

व्योम i2sbus_detach_codec(काष्ठा soundbus_dev *dev, व्योम *data)
अणु
	काष्ठा codec_info_item *cii = शून्य, *i;

	list_क्रम_each_entry(i, &dev->codec_list, list) अणु
		अगर (i->codec_data == data) अणु
			cii = i;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (cii) अणु
		list_del(&cii->list);
		module_put(cii->codec->owner);
		kमुक्त(cii);
	पूर्ण
	/* no more codecs, but still a pcm? */
	अगर (list_empty(&dev->codec_list) && dev->pcm) अणु
		/* the actual cleanup is करोne by the callback above! */
		snd_device_मुक्त(dev->pcm->card, dev->pcm);
	पूर्ण
पूर्ण
