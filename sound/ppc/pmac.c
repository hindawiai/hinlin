<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PMac DBDMA lowlevel functions
 *
 * Copyright (c) by Takashi Iwai <tiwai@suse.de>
 * code based on dmasound.c.
 */


#समावेश <linux/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <sound/core.h>
#समावेश "pmac.h"
#समावेश <sound/pcm_params.h>
#समावेश <यंत्र/pmac_feature.h>


/* fixed frequency table क्रम awacs, screamer, burgundy, DACA (44100 max) */
अटल स्थिर पूर्णांक awacs_freqs[8] = अणु
	44100, 29400, 22050, 17640, 14700, 11025, 8820, 7350
पूर्ण;
/* fixed frequency table क्रम tumbler */
अटल स्थिर पूर्णांक tumbler_freqs[1] = अणु
	44100
पूर्ण;


/*
 * we will allocate a single 'emergency' dbdma cmd block to use अगर the
 * tx status comes up "DEAD".  This happens on some PowerComputing Pmac
 * clones, either owing to a bug in dbdma or some पूर्णांकeraction between
 * IDE and sound.  However, this measure would deal with DEAD status अगर
 * it appeared अन्यथाwhere.
 */
अटल काष्ठा pmac_dbdma emergency_dbdma;
अटल पूर्णांक emergency_in_use;


/*
 * allocate DBDMA command arrays
 */
अटल पूर्णांक snd_pmac_dbdma_alloc(काष्ठा snd_pmac *chip, काष्ठा pmac_dbdma *rec, पूर्णांक size)
अणु
	अचिन्हित पूर्णांक rsize = माप(काष्ठा dbdma_cmd) * (size + 1);

	rec->space = dma_alloc_coherent(&chip->pdev->dev, rsize,
					&rec->dma_base, GFP_KERNEL);
	अगर (rec->space == शून्य)
		वापस -ENOMEM;
	rec->size = size;
	स_रखो(rec->space, 0, rsize);
	rec->cmds = (व्योम __iomem *)DBDMA_ALIGN(rec->space);
	rec->addr = rec->dma_base + (अचिन्हित दीर्घ)((अक्षर *)rec->cmds - (अक्षर *)rec->space);

	वापस 0;
पूर्ण

अटल व्योम snd_pmac_dbdma_मुक्त(काष्ठा snd_pmac *chip, काष्ठा pmac_dbdma *rec)
अणु
	अगर (rec->space) अणु
		अचिन्हित पूर्णांक rsize = माप(काष्ठा dbdma_cmd) * (rec->size + 1);

		dma_मुक्त_coherent(&chip->pdev->dev, rsize, rec->space, rec->dma_base);
	पूर्ण
पूर्ण


/*
 * pcm stuff
 */

/*
 * look up frequency table
 */

अचिन्हित पूर्णांक snd_pmac_rate_index(काष्ठा snd_pmac *chip, काष्ठा pmac_stream *rec, अचिन्हित पूर्णांक rate)
अणु
	पूर्णांक i, ok, found;

	ok = rec->cur_freqs;
	अगर (rate > chip->freq_table[0])
		वापस 0;
	found = 0;
	क्रम (i = 0; i < chip->num_freqs; i++, ok >>= 1) अणु
		अगर (! (ok & 1)) जारी;
		found = i;
		अगर (rate >= chip->freq_table[i])
			अवरोध;
	पूर्ण
	वापस found;
पूर्ण

/*
 * check whether another stream is active
 */
अटल अंतरभूत पूर्णांक another_stream(पूर्णांक stream)
अणु
	वापस (stream == SNDRV_PCM_STREAM_PLAYBACK) ?
		SNDRV_PCM_STREAM_CAPTURE : SNDRV_PCM_STREAM_PLAYBACK;
पूर्ण

/*
 * get a stream of the opposite direction
 */
अटल काष्ठा pmac_stream *snd_pmac_get_stream(काष्ठा snd_pmac *chip, पूर्णांक stream)
अणु
	चयन (stream) अणु
	हाल SNDRV_PCM_STREAM_PLAYBACK:
		वापस &chip->playback;
	हाल SNDRV_PCM_STREAM_CAPTURE:
		वापस &chip->capture;
	शेष:
		snd_BUG();
		वापस शून्य;
	पूर्ण
पूर्ण

/*
 * रुको जबतक run status is on
 */
अटल अंतरभूत व्योम
snd_pmac_रुको_ack(काष्ठा pmac_stream *rec)
अणु
	पूर्णांक समयout = 50000;
	जबतक ((in_le32(&rec->dma->status) & RUN) && समयout-- > 0)
		udelay(1);
पूर्ण

/*
 * set the क्रमmat and rate to the chip.
 * call the lowlevel function अगर defined (e.g. क्रम AWACS).
 */
अटल व्योम snd_pmac_pcm_set_क्रमmat(काष्ठा snd_pmac *chip)
अणु
	/* set up frequency and क्रमmat */
	out_le32(&chip->awacs->control, chip->control_mask | (chip->rate_index << 8));
	out_le32(&chip->awacs->byteswap, chip->क्रमmat == SNDRV_PCM_FORMAT_S16_LE ? 1 : 0);
	अगर (chip->set_क्रमmat)
		chip->set_क्रमmat(chip);
पूर्ण

/*
 * stop the DMA transfer
 */
अटल अंतरभूत व्योम snd_pmac_dma_stop(काष्ठा pmac_stream *rec)
अणु
	out_le32(&rec->dma->control, (RUN|WAKE|FLUSH|PAUSE) << 16);
	snd_pmac_रुको_ack(rec);
पूर्ण

/*
 * set the command poपूर्णांकer address
 */
अटल अंतरभूत व्योम snd_pmac_dma_set_command(काष्ठा pmac_stream *rec, काष्ठा pmac_dbdma *cmd)
अणु
	out_le32(&rec->dma->cmdptr, cmd->addr);
पूर्ण

/*
 * start the DMA
 */
अटल अंतरभूत व्योम snd_pmac_dma_run(काष्ठा pmac_stream *rec, पूर्णांक status)
अणु
	out_le32(&rec->dma->control, status | (status << 16));
पूर्ण


/*
 * prepare playback/capture stream
 */
अटल पूर्णांक snd_pmac_pcm_prepare(काष्ठा snd_pmac *chip, काष्ठा pmac_stream *rec, काष्ठा snd_pcm_substream *subs)
अणु
	पूर्णांक i;
	अस्थिर काष्ठा dbdma_cmd __iomem *cp;
	काष्ठा snd_pcm_runसमय *runसमय = subs->runसमय;
	पूर्णांक rate_index;
	दीर्घ offset;
	काष्ठा pmac_stream *astr;

	rec->dma_size = snd_pcm_lib_buffer_bytes(subs);
	rec->period_size = snd_pcm_lib_period_bytes(subs);
	rec->nperiods = rec->dma_size / rec->period_size;
	rec->cur_period = 0;
	rate_index = snd_pmac_rate_index(chip, rec, runसमय->rate);

	/* set up स्थिरraपूर्णांकs */
	astr = snd_pmac_get_stream(chip, another_stream(rec->stream));
	अगर (! astr)
		वापस -EINVAL;
	astr->cur_freqs = 1 << rate_index;
	astr->cur_क्रमmats = 1 << runसमय->क्रमmat;
	chip->rate_index = rate_index;
	chip->क्रमmat = runसमय->क्रमmat;

	/* We really want to execute a DMA stop command, after the AWACS
	 * is initialized.
	 * For reasons I करोn't understand, it stops the hissing noise
	 * common to many PowerBook G3 प्रणालीs and अक्रमom noise otherwise
	 * captured on iBook2's about every third समय. -ReneR
	 */
	spin_lock_irq(&chip->reg_lock);
	snd_pmac_dma_stop(rec);
	chip->extra_dma.cmds->command = cpu_to_le16(DBDMA_STOP);
	snd_pmac_dma_set_command(rec, &chip->extra_dma);
	snd_pmac_dma_run(rec, RUN);
	spin_unlock_irq(&chip->reg_lock);
	mdelay(5);
	spin_lock_irq(&chip->reg_lock);
	/* continuous DMA memory type करोesn't provide the physical address,
	 * so we need to resolve the address here...
	 */
	offset = runसमय->dma_addr;
	क्रम (i = 0, cp = rec->cmd.cmds; i < rec->nperiods; i++, cp++) अणु
		cp->phy_addr = cpu_to_le32(offset);
		cp->req_count = cpu_to_le16(rec->period_size);
		/*cp->res_count = cpu_to_le16(0);*/
		cp->xfer_status = cpu_to_le16(0);
		offset += rec->period_size;
	पूर्ण
	/* make loop */
	cp->command = cpu_to_le16(DBDMA_NOP | BR_ALWAYS);
	cp->cmd_dep = cpu_to_le32(rec->cmd.addr);

	snd_pmac_dma_stop(rec);
	snd_pmac_dma_set_command(rec, &rec->cmd);
	spin_unlock_irq(&chip->reg_lock);

	वापस 0;
पूर्ण


/*
 * PCM trigger/stop
 */
अटल पूर्णांक snd_pmac_pcm_trigger(काष्ठा snd_pmac *chip, काष्ठा pmac_stream *rec,
				काष्ठा snd_pcm_substream *subs, पूर्णांक cmd)
अणु
	अस्थिर काष्ठा dbdma_cmd __iomem *cp;
	पूर्णांक i, command;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		अगर (rec->running)
			वापस -EBUSY;
		command = (subs->stream == SNDRV_PCM_STREAM_PLAYBACK ?
			   OUTPUT_MORE : INPUT_MORE) + INTR_ALWAYS;
		spin_lock(&chip->reg_lock);
		snd_pmac_beep_stop(chip);
		snd_pmac_pcm_set_क्रमmat(chip);
		क्रम (i = 0, cp = rec->cmd.cmds; i < rec->nperiods; i++, cp++)
			out_le16(&cp->command, command);
		snd_pmac_dma_set_command(rec, &rec->cmd);
		(व्योम)in_le32(&rec->dma->status);
		snd_pmac_dma_run(rec, RUN|WAKE);
		rec->running = 1;
		spin_unlock(&chip->reg_lock);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		spin_lock(&chip->reg_lock);
		rec->running = 0;
		/*prपूर्णांकk(KERN_DEBUG "stopped!!\n");*/
		snd_pmac_dma_stop(rec);
		क्रम (i = 0, cp = rec->cmd.cmds; i < rec->nperiods; i++, cp++)
			out_le16(&cp->command, DBDMA_STOP);
		spin_unlock(&chip->reg_lock);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * वापस the current poपूर्णांकer
 */
अंतरभूत
अटल snd_pcm_uframes_t snd_pmac_pcm_poपूर्णांकer(काष्ठा snd_pmac *chip,
					      काष्ठा pmac_stream *rec,
					      काष्ठा snd_pcm_substream *subs)
अणु
	पूर्णांक count = 0;

#अगर 1 /* hmm.. how can we get the current dma poपूर्णांकer?? */
	पूर्णांक stat;
	अस्थिर काष्ठा dbdma_cmd __iomem *cp = &rec->cmd.cmds[rec->cur_period];
	stat = le16_to_cpu(cp->xfer_status);
	अगर (stat & (ACTIVE|DEAD)) अणु
		count = in_le16(&cp->res_count);
		अगर (count)
			count = rec->period_size - count;
	पूर्ण
#पूर्ण_अगर
	count += rec->cur_period * rec->period_size;
	/*prपूर्णांकk(KERN_DEBUG "pointer=%d\n", count);*/
	वापस bytes_to_frames(subs->runसमय, count);
पूर्ण

/*
 * playback
 */

अटल पूर्णांक snd_pmac_playback_prepare(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_pmac *chip = snd_pcm_substream_chip(subs);
	वापस snd_pmac_pcm_prepare(chip, &chip->playback, subs);
पूर्ण

अटल पूर्णांक snd_pmac_playback_trigger(काष्ठा snd_pcm_substream *subs,
				     पूर्णांक cmd)
अणु
	काष्ठा snd_pmac *chip = snd_pcm_substream_chip(subs);
	वापस snd_pmac_pcm_trigger(chip, &chip->playback, subs, cmd);
पूर्ण

अटल snd_pcm_uframes_t snd_pmac_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_pmac *chip = snd_pcm_substream_chip(subs);
	वापस snd_pmac_pcm_poपूर्णांकer(chip, &chip->playback, subs);
पूर्ण


/*
 * capture
 */

अटल पूर्णांक snd_pmac_capture_prepare(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_pmac *chip = snd_pcm_substream_chip(subs);
	वापस snd_pmac_pcm_prepare(chip, &chip->capture, subs);
पूर्ण

अटल पूर्णांक snd_pmac_capture_trigger(काष्ठा snd_pcm_substream *subs,
				    पूर्णांक cmd)
अणु
	काष्ठा snd_pmac *chip = snd_pcm_substream_chip(subs);
	वापस snd_pmac_pcm_trigger(chip, &chip->capture, subs, cmd);
पूर्ण

अटल snd_pcm_uframes_t snd_pmac_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_pmac *chip = snd_pcm_substream_chip(subs);
	वापस snd_pmac_pcm_poपूर्णांकer(chip, &chip->capture, subs);
पूर्ण


/*
 * Handle DEAD DMA transfers:
 * अगर the TX status comes up "DEAD" - reported on some Power Computing machines
 * we need to re-start the dbdma - but from a dअगरferent physical start address
 * and with a dअगरferent transfer length.  It would get very messy to करो this
 * with the normal dbdma_cmd blocks - we would have to re-ग_लिखो the buffer start
 * addresses each समय.  So, we will keep a single dbdma_cmd block which can be
 * fiddled with.
 * When DEAD status is first reported the content of the faulted dbdma block is
 * copied पूर्णांकo the emergency buffer and we note that the buffer is in use.
 * we then bump the start physical address by the amount that was successfully
 * output beक्रमe it died.
 * On any subsequent DEAD result we just करो the bump-ups (we know that we are
 * alपढ़ोy using the emergency dbdma_cmd).
 * CHECK: this just tries to "do it".  It is possible that we should abanकरोn
 * xfers when the number of residual bytes माला_लो below a certain value - I can
 * see that this might cause a loop-क्रमever अगर a too small transfer causes
 * DEAD status.  However this is a TODO क्रम now - we'll see what माला_लो reported.
 * When we get a successful transfer result with the emergency buffer we just
 * pretend that it completed using the original dmdma_cmd and carry on.  The
 * 'next_cmd' field will alपढ़ोy poपूर्णांक back to the original loop of blocks.
 */
अटल अंतरभूत व्योम snd_pmac_pcm_dead_xfer(काष्ठा pmac_stream *rec,
					  अस्थिर काष्ठा dbdma_cmd __iomem *cp)
अणु
	अचिन्हित लघु req, res ;
	अचिन्हित पूर्णांक phy ;

	/* prपूर्णांकk(KERN_WARNING "snd-powermac: DMA died - patching it up!\n"); */

	/* to clear DEAD status we must first clear RUN
	   set it to quiescent to be on the safe side */
	(व्योम)in_le32(&rec->dma->status);
	out_le32(&rec->dma->control, (RUN|PAUSE|FLUSH|WAKE) << 16);

	अगर (!emergency_in_use) अणु /* new problem */
		स_नकल((व्योम *)emergency_dbdma.cmds, (व्योम *)cp,
		       माप(काष्ठा dbdma_cmd));
		emergency_in_use = 1;
		cp->xfer_status = cpu_to_le16(0);
		cp->req_count = cpu_to_le16(rec->period_size);
		cp = emergency_dbdma.cmds;
	पूर्ण

	/* now bump the values to reflect the amount
	   we haven't yet shअगरted */
	req = le16_to_cpu(cp->req_count);
	res = le16_to_cpu(cp->res_count);
	phy = le32_to_cpu(cp->phy_addr);
	phy += (req - res);
	cp->req_count = cpu_to_le16(res);
	cp->res_count = cpu_to_le16(0);
	cp->xfer_status = cpu_to_le16(0);
	cp->phy_addr = cpu_to_le32(phy);

	cp->cmd_dep = cpu_to_le32(rec->cmd.addr
		+ माप(काष्ठा dbdma_cmd)*((rec->cur_period+1)%rec->nperiods));

	cp->command = cpu_to_le16(OUTPUT_MORE | BR_ALWAYS | INTR_ALWAYS);

	/* poपूर्णांक at our patched up command block */
	out_le32(&rec->dma->cmdptr, emergency_dbdma.addr);

	/* we must re-start the controller */
	(व्योम)in_le32(&rec->dma->status);
	/* should complete clearing the DEAD status */
	out_le32(&rec->dma->control, ((RUN|WAKE) << 16) + (RUN|WAKE));
पूर्ण

/*
 * update playback/capture poपूर्णांकer from पूर्णांकerrupts
 */
अटल व्योम snd_pmac_pcm_update(काष्ठा snd_pmac *chip, काष्ठा pmac_stream *rec)
अणु
	अस्थिर काष्ठा dbdma_cmd __iomem *cp;
	पूर्णांक c;
	पूर्णांक stat;

	spin_lock(&chip->reg_lock);
	अगर (rec->running) अणु
		क्रम (c = 0; c < rec->nperiods; c++) अणु /* at most all fragments */

			अगर (emergency_in_use)   /* alपढ़ोy using DEAD xfer? */
				cp = emergency_dbdma.cmds;
			अन्यथा
				cp = &rec->cmd.cmds[rec->cur_period];

			stat = le16_to_cpu(cp->xfer_status);

			अगर (stat & DEAD) अणु
				snd_pmac_pcm_dead_xfer(rec, cp);
				अवरोध; /* this block is still going */
			पूर्ण

			अगर (emergency_in_use)
				emergency_in_use = 0 ; /* करोne that */

			अगर (! (stat & ACTIVE))
				अवरोध;

			/*prपूर्णांकk(KERN_DEBUG "update frag %d\n", rec->cur_period);*/
			cp->xfer_status = cpu_to_le16(0);
			cp->req_count = cpu_to_le16(rec->period_size);
			/*cp->res_count = cpu_to_le16(0);*/
			rec->cur_period++;
			अगर (rec->cur_period >= rec->nperiods) अणु
				rec->cur_period = 0;
			पूर्ण

			spin_unlock(&chip->reg_lock);
			snd_pcm_period_elapsed(rec->substream);
			spin_lock(&chip->reg_lock);
		पूर्ण
	पूर्ण
	spin_unlock(&chip->reg_lock);
पूर्ण


/*
 * hw info
 */

अटल स्थिर काष्ठा snd_pcm_hardware snd_pmac_playback =
अणु
	.info =			(SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_MMAP |
				 SNDRV_PCM_INFO_MMAP_VALID |
				 SNDRV_PCM_INFO_RESUME),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S16_BE | SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_8000_44100,
	.rate_min =		7350,
	.rate_max =		44100,
	.channels_min =		2,
	.channels_max =		2,
	.buffer_bytes_max =	131072,
	.period_bytes_min =	256,
	.period_bytes_max =	16384,
	.periods_min =		3,
	.periods_max =		PMAC_MAX_FRAGS,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_pmac_capture =
अणु
	.info =			(SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_MMAP |
				 SNDRV_PCM_INFO_MMAP_VALID |
				 SNDRV_PCM_INFO_RESUME),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S16_BE | SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_8000_44100,
	.rate_min =		7350,
	.rate_max =		44100,
	.channels_min =		2,
	.channels_max =		2,
	.buffer_bytes_max =	131072,
	.period_bytes_min =	256,
	.period_bytes_max =	16384,
	.periods_min =		3,
	.periods_max =		PMAC_MAX_FRAGS,
पूर्ण;


#अगर 0 // NYI
अटल पूर्णांक snd_pmac_hw_rule_rate(काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_pmac *chip = rule->निजी;
	काष्ठा pmac_stream *rec = snd_pmac_get_stream(chip, rule->deps[0]);
	पूर्णांक i, freq_table[8], num_freqs;

	अगर (! rec)
		वापस -EINVAL;
	num_freqs = 0;
	क्रम (i = chip->num_freqs - 1; i >= 0; i--) अणु
		अगर (rec->cur_freqs & (1 << i))
			freq_table[num_freqs++] = chip->freq_table[i];
	पूर्ण

	वापस snd_पूर्णांकerval_list(hw_param_पूर्णांकerval(params, rule->var),
				 num_freqs, freq_table, 0);
पूर्ण

अटल पूर्णांक snd_pmac_hw_rule_क्रमmat(काष्ठा snd_pcm_hw_params *params,
				   काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_pmac *chip = rule->निजी;
	काष्ठा pmac_stream *rec = snd_pmac_get_stream(chip, rule->deps[0]);

	अगर (! rec)
		वापस -EINVAL;
	वापस snd_mask_refine_set(hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT),
				   rec->cur_क्रमmats);
पूर्ण
#पूर्ण_अगर // NYI

अटल पूर्णांक snd_pmac_pcm_खोलो(काष्ठा snd_pmac *chip, काष्ठा pmac_stream *rec,
			     काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = subs->runसमय;
	पूर्णांक i;

	/* look up frequency table and fill bit mask */
	runसमय->hw.rates = 0;
	क्रम (i = 0; i < chip->num_freqs; i++)
		अगर (chip->freqs_ok & (1 << i))
			runसमय->hw.rates |=
				snd_pcm_rate_to_rate_bit(chip->freq_table[i]);

	/* check क्रम minimum and maximum rates */
	क्रम (i = 0; i < chip->num_freqs; i++) अणु
		अगर (chip->freqs_ok & (1 << i)) अणु
			runसमय->hw.rate_max = chip->freq_table[i];
			अवरोध;
		पूर्ण
	पूर्ण
	क्रम (i = chip->num_freqs - 1; i >= 0; i--) अणु
		अगर (chip->freqs_ok & (1 << i)) अणु
			runसमय->hw.rate_min = chip->freq_table[i];
			अवरोध;
		पूर्ण
	पूर्ण
	runसमय->hw.क्रमmats = chip->क्रमmats_ok;
	अगर (chip->can_capture) अणु
		अगर (! chip->can_duplex)
			runसमय->hw.info |= SNDRV_PCM_INFO_HALF_DUPLEX;
		runसमय->hw.info |= SNDRV_PCM_INFO_JOINT_DUPLEX;
	पूर्ण
	runसमय->निजी_data = rec;
	rec->substream = subs;

#अगर 0 /* FIXME: still under development.. */
	snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
			    snd_pmac_hw_rule_rate, chip, rec->stream, -1);
	snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_FORMAT,
			    snd_pmac_hw_rule_क्रमmat, chip, rec->stream, -1);
#पूर्ण_अगर

	runसमय->hw.periods_max = rec->cmd.size - 1;

	/* स्थिरraपूर्णांकs to fix choppy sound */
	snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय, SNDRV_PCM_HW_PARAM_PERIODS);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pmac_pcm_बंद(काष्ठा snd_pmac *chip, काष्ठा pmac_stream *rec,
			      काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा pmac_stream *astr;

	snd_pmac_dma_stop(rec);

	astr = snd_pmac_get_stream(chip, another_stream(rec->stream));
	अगर (! astr)
		वापस -EINVAL;

	/* reset स्थिरraपूर्णांकs */
	astr->cur_freqs = chip->freqs_ok;
	astr->cur_क्रमmats = chip->क्रमmats_ok;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_pmac_playback_खोलो(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_pmac *chip = snd_pcm_substream_chip(subs);

	subs->runसमय->hw = snd_pmac_playback;
	वापस snd_pmac_pcm_खोलो(chip, &chip->playback, subs);
पूर्ण

अटल पूर्णांक snd_pmac_capture_खोलो(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_pmac *chip = snd_pcm_substream_chip(subs);

	subs->runसमय->hw = snd_pmac_capture;
	वापस snd_pmac_pcm_खोलो(chip, &chip->capture, subs);
पूर्ण

अटल पूर्णांक snd_pmac_playback_बंद(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_pmac *chip = snd_pcm_substream_chip(subs);

	वापस snd_pmac_pcm_बंद(chip, &chip->playback, subs);
पूर्ण

अटल पूर्णांक snd_pmac_capture_बंद(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_pmac *chip = snd_pcm_substream_chip(subs);

	वापस snd_pmac_pcm_बंद(chip, &chip->capture, subs);
पूर्ण

/*
 */

अटल स्थिर काष्ठा snd_pcm_ops snd_pmac_playback_ops = अणु
	.खोलो =		snd_pmac_playback_खोलो,
	.बंद =	snd_pmac_playback_बंद,
	.prepare =	snd_pmac_playback_prepare,
	.trigger =	snd_pmac_playback_trigger,
	.poपूर्णांकer =	snd_pmac_playback_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_pmac_capture_ops = अणु
	.खोलो =		snd_pmac_capture_खोलो,
	.बंद =	snd_pmac_capture_बंद,
	.prepare =	snd_pmac_capture_prepare,
	.trigger =	snd_pmac_capture_trigger,
	.poपूर्णांकer =	snd_pmac_capture_poपूर्णांकer,
पूर्ण;

पूर्णांक snd_pmac_pcm_new(काष्ठा snd_pmac *chip)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;
	पूर्णांक num_captures = 1;

	अगर (! chip->can_capture)
		num_captures = 0;
	err = snd_pcm_new(chip->card, chip->card->driver, 0, 1, num_captures, &pcm);
	अगर (err < 0)
		वापस err;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_pmac_playback_ops);
	अगर (chip->can_capture)
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_pmac_capture_ops);

	pcm->निजी_data = chip;
	pcm->info_flags = SNDRV_PCM_INFO_JOINT_DUPLEX;
	म_नकल(pcm->name, chip->card->लघुname);
	chip->pcm = pcm;

	chip->क्रमmats_ok = SNDRV_PCM_FMTBIT_S16_BE;
	अगर (chip->can_byte_swap)
		chip->क्रमmats_ok |= SNDRV_PCM_FMTBIT_S16_LE;

	chip->playback.cur_क्रमmats = chip->क्रमmats_ok;
	chip->capture.cur_क्रमmats = chip->क्रमmats_ok;
	chip->playback.cur_freqs = chip->freqs_ok;
	chip->capture.cur_freqs = chip->freqs_ok;

	/* pपुनः_स्मृतिate 64k buffer */
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       &chip->pdev->dev,
				       64 * 1024, 64 * 1024);

	वापस 0;
पूर्ण


अटल व्योम snd_pmac_dbdma_reset(काष्ठा snd_pmac *chip)
अणु
	out_le32(&chip->playback.dma->control, (RUN|PAUSE|FLUSH|WAKE|DEAD) << 16);
	snd_pmac_रुको_ack(&chip->playback);
	out_le32(&chip->capture.dma->control, (RUN|PAUSE|FLUSH|WAKE|DEAD) << 16);
	snd_pmac_रुको_ack(&chip->capture);
पूर्ण


/*
 * handling beep
 */
व्योम snd_pmac_beep_dma_start(काष्ठा snd_pmac *chip, पूर्णांक bytes, अचिन्हित दीर्घ addr, पूर्णांक speed)
अणु
	काष्ठा pmac_stream *rec = &chip->playback;

	snd_pmac_dma_stop(rec);
	chip->extra_dma.cmds->req_count = cpu_to_le16(bytes);
	chip->extra_dma.cmds->xfer_status = cpu_to_le16(0);
	chip->extra_dma.cmds->cmd_dep = cpu_to_le32(chip->extra_dma.addr);
	chip->extra_dma.cmds->phy_addr = cpu_to_le32(addr);
	chip->extra_dma.cmds->command = cpu_to_le16(OUTPUT_MORE | BR_ALWAYS);
	out_le32(&chip->awacs->control,
		 (in_le32(&chip->awacs->control) & ~0x1f00)
		 | (speed << 8));
	out_le32(&chip->awacs->byteswap, 0);
	snd_pmac_dma_set_command(rec, &chip->extra_dma);
	snd_pmac_dma_run(rec, RUN);
पूर्ण

व्योम snd_pmac_beep_dma_stop(काष्ठा snd_pmac *chip)
अणु
	snd_pmac_dma_stop(&chip->playback);
	chip->extra_dma.cmds->command = cpu_to_le16(DBDMA_STOP);
	snd_pmac_pcm_set_क्रमmat(chip); /* reset क्रमmat */
पूर्ण


/*
 * पूर्णांकerrupt handlers
 */
अटल irqवापस_t
snd_pmac_tx_पूर्णांकr(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा snd_pmac *chip = devid;
	snd_pmac_pcm_update(chip, &chip->playback);
	वापस IRQ_HANDLED;
पूर्ण


अटल irqवापस_t
snd_pmac_rx_पूर्णांकr(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा snd_pmac *chip = devid;
	snd_pmac_pcm_update(chip, &chip->capture);
	वापस IRQ_HANDLED;
पूर्ण


अटल irqवापस_t
snd_pmac_ctrl_पूर्णांकr(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा snd_pmac *chip = devid;
	पूर्णांक ctrl = in_le32(&chip->awacs->control);

	/*prपूर्णांकk(KERN_DEBUG "pmac: control interrupt.. 0x%x\n", ctrl);*/
	अगर (ctrl & MASK_PORTCHG) अणु
		/* करो something when headphone is plugged/unplugged? */
		अगर (chip->update_स्वतःmute)
			chip->update_स्वतःmute(chip, 1);
	पूर्ण
	अगर (ctrl & MASK_CNTLERR) अणु
		पूर्णांक err = (in_le32(&chip->awacs->codec_stat) & MASK_ERRCODE) >> 16;
		अगर (err && chip->model <= PMAC_SCREAMER)
			snd_prपूर्णांकk(KERN_DEBUG "error %x\n", err);
	पूर्ण
	/* Writing 1s to the CNTLERR and PORTCHG bits clears them... */
	out_le32(&chip->awacs->control, ctrl);
	वापस IRQ_HANDLED;
पूर्ण


/*
 * a wrapper to feature call क्रम compatibility
 */
अटल व्योम snd_pmac_sound_feature(काष्ठा snd_pmac *chip, पूर्णांक enable)
अणु
	अगर (ppc_md.feature_call)
		ppc_md.feature_call(PMAC_FTR_SOUND_CHIP_ENABLE, chip->node, 0, enable);
पूर्ण

/*
 * release resources
 */

अटल पूर्णांक snd_pmac_मुक्त(काष्ठा snd_pmac *chip)
अणु
	/* stop sounds */
	अगर (chip->initialized) अणु
		snd_pmac_dbdma_reset(chip);
		/* disable पूर्णांकerrupts from awacs पूर्णांकerface */
		out_le32(&chip->awacs->control, in_le32(&chip->awacs->control) & 0xfff);
	पूर्ण

	अगर (chip->node)
		snd_pmac_sound_feature(chip, 0);

	/* clean up mixer अगर any */
	अगर (chip->mixer_मुक्त)
		chip->mixer_मुक्त(chip);

	snd_pmac_detach_beep(chip);

	/* release resources */
	अगर (chip->irq >= 0)
		मुक्त_irq(chip->irq, (व्योम*)chip);
	अगर (chip->tx_irq >= 0)
		मुक्त_irq(chip->tx_irq, (व्योम*)chip);
	अगर (chip->rx_irq >= 0)
		मुक्त_irq(chip->rx_irq, (व्योम*)chip);
	snd_pmac_dbdma_मुक्त(chip, &chip->playback.cmd);
	snd_pmac_dbdma_मुक्त(chip, &chip->capture.cmd);
	snd_pmac_dbdma_मुक्त(chip, &chip->extra_dma);
	snd_pmac_dbdma_मुक्त(chip, &emergency_dbdma);
	iounmap(chip->macio_base);
	iounmap(chip->latch_base);
	iounmap(chip->awacs);
	iounmap(chip->playback.dma);
	iounmap(chip->capture.dma);

	अगर (chip->node) अणु
		पूर्णांक i;
		क्रम (i = 0; i < 3; i++) अणु
			अगर (chip->requested & (1 << i))
				release_mem_region(chip->rsrc[i].start,
						   resource_size(&chip->rsrc[i]));
		पूर्ण
	पूर्ण

	pci_dev_put(chip->pdev);
	of_node_put(chip->node);
	kमुक्त(chip);
	वापस 0;
पूर्ण


/*
 * मुक्त the device
 */
अटल पूर्णांक snd_pmac_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_pmac *chip = device->device_data;
	वापस snd_pmac_मुक्त(chip);
पूर्ण


/*
 * check the machine support byteswap (little-endian)
 */

अटल व्योम detect_byte_swap(काष्ठा snd_pmac *chip)
अणु
	काष्ठा device_node *mio;

	/* अगर seems that Keylargo can't byte-swap  */
	क्रम (mio = chip->node->parent; mio; mio = mio->parent) अणु
		अगर (of_node_name_eq(mio, "mac-io")) अणु
			अगर (of_device_is_compatible(mio, "Keylargo"))
				chip->can_byte_swap = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	/* it seems the Pismo & iBook can't byte-swap in hardware. */
	अगर (of_machine_is_compatible("PowerBook3,1") ||
	    of_machine_is_compatible("PowerBook2,1"))
		chip->can_byte_swap = 0 ;

	अगर (of_machine_is_compatible("PowerBook2,1"))
		chip->can_duplex = 0;
पूर्ण


/*
 * detect a sound chip
 */
अटल पूर्णांक snd_pmac_detect(काष्ठा snd_pmac *chip)
अणु
	काष्ठा device_node *sound;
	काष्ठा device_node *dn;
	स्थिर अचिन्हित पूर्णांक *prop;
	अचिन्हित पूर्णांक l;
	काष्ठा macio_chip* macio;

	अगर (!machine_is(घातermac))
		वापस -ENODEV;

	chip->subframe = 0;
	chip->revision = 0;
	chip->freqs_ok = 0xff; /* all ok */
	chip->model = PMAC_AWACS;
	chip->can_byte_swap = 1;
	chip->can_duplex = 1;
	chip->can_capture = 1;
	chip->num_freqs = ARRAY_SIZE(awacs_freqs);
	chip->freq_table = awacs_freqs;
	chip->pdev = शून्य;

	chip->control_mask = MASK_IEPC | MASK_IEE | 0x11; /* शेष */

	/* check machine type */
	अगर (of_machine_is_compatible("AAPL,3400/2400")
	    || of_machine_is_compatible("AAPL,3500"))
		chip->is_pbook_3400 = 1;
	अन्यथा अगर (of_machine_is_compatible("PowerBook1,1")
		 || of_machine_is_compatible("AAPL,PowerBook1998"))
		chip->is_pbook_G3 = 1;
	chip->node = of_find_node_by_name(शून्य, "awacs");
	sound = of_node_get(chip->node);

	/*
	 * घातermac G3 models have a node called "davbus"
	 * with a child called "sound".
	 */
	अगर (!chip->node)
		chip->node = of_find_node_by_name(शून्य, "davbus");
	/*
	 * अगर we didn't find a davbus device, try 'i2s-a' since
	 * this seems to be what iBooks have
	 */
	अगर (! chip->node) अणु
		chip->node = of_find_node_by_name(शून्य, "i2s-a");
		अगर (chip->node && chip->node->parent &&
		    chip->node->parent->parent) अणु
			अगर (of_device_is_compatible(chip->node->parent->parent,
						 "K2-Keylargo"))
				chip->is_k2 = 1;
		पूर्ण
	पूर्ण
	अगर (! chip->node)
		वापस -ENODEV;

	अगर (!sound) अणु
		क्रम_each_node_by_name(sound, "sound")
			अगर (sound->parent == chip->node)
				अवरोध;
	पूर्ण
	अगर (! sound) अणु
		of_node_put(chip->node);
		chip->node = शून्य;
		वापस -ENODEV;
	पूर्ण
	prop = of_get_property(sound, "sub-frame", शून्य);
	अगर (prop && *prop < 16)
		chip->subframe = *prop;
	prop = of_get_property(sound, "layout-id", शून्य);
	अगर (prop) अणु
		/* partly deprecate snd-घातermac, क्रम those machines
		 * that have a layout-id property क्रम now */
		prपूर्णांकk(KERN_INFO "snd-powermac no longer handles any "
				 "machines with a layout-id property "
				 "in the device-tree, use snd-aoa.\n");
		of_node_put(sound);
		of_node_put(chip->node);
		chip->node = शून्य;
		वापस -ENODEV;
	पूर्ण
	/* This should be verअगरied on older screamers */
	अगर (of_device_is_compatible(sound, "screamer")) अणु
		chip->model = PMAC_SCREAMER;
		// chip->can_byte_swap = 0; /* FIXME: check this */
	पूर्ण
	अगर (of_device_is_compatible(sound, "burgundy")) अणु
		chip->model = PMAC_BURGUNDY;
		chip->control_mask = MASK_IEPC | 0x11; /* disable IEE */
	पूर्ण
	अगर (of_device_is_compatible(sound, "daca")) अणु
		chip->model = PMAC_DACA;
		chip->can_capture = 0;  /* no capture */
		chip->can_duplex = 0;
		// chip->can_byte_swap = 0; /* FIXME: check this */
		chip->control_mask = MASK_IEPC | 0x11; /* disable IEE */
	पूर्ण
	अगर (of_device_is_compatible(sound, "tumbler")) अणु
		chip->model = PMAC_TUMBLER;
		chip->can_capture = of_machine_is_compatible("PowerMac4,2")
				|| of_machine_is_compatible("PowerBook3,2")
				|| of_machine_is_compatible("PowerBook3,3")
				|| of_machine_is_compatible("PowerBook4,1")
				|| of_machine_is_compatible("PowerBook4,2")
				|| of_machine_is_compatible("PowerBook4,3");
		chip->can_duplex = 0;
		// chip->can_byte_swap = 0; /* FIXME: check this */
		chip->num_freqs = ARRAY_SIZE(tumbler_freqs);
		chip->freq_table = tumbler_freqs;
		chip->control_mask = MASK_IEPC | 0x11; /* disable IEE */
	पूर्ण
	अगर (of_device_is_compatible(sound, "snapper")) अणु
		chip->model = PMAC_SNAPPER;
		// chip->can_byte_swap = 0; /* FIXME: check this */
		chip->num_freqs = ARRAY_SIZE(tumbler_freqs);
		chip->freq_table = tumbler_freqs;
		chip->control_mask = MASK_IEPC | 0x11; /* disable IEE */
	पूर्ण
	prop = of_get_property(sound, "device-id", शून्य);
	अगर (prop)
		chip->device_id = *prop;
	dn = of_find_node_by_name(शून्य, "perch");
	chip->has_iic = (dn != शून्य);
	of_node_put(dn);

	/* We need the PCI device क्रम DMA allocations, let's use a crude method
	 * क्रम now ...
	 */
	macio = macio_find(chip->node, macio_unknown);
	अगर (macio == शून्य)
		prपूर्णांकk(KERN_WARNING "snd-powermac: can't locate macio !\n");
	अन्यथा अणु
		काष्ठा pci_dev *pdev = शून्य;

		क्रम_each_pci_dev(pdev) अणु
			काष्ठा device_node *np = pci_device_to_OF_node(pdev);
			अगर (np && np == macio->of_node) अणु
				chip->pdev = pdev;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (chip->pdev == शून्य)
		prपूर्णांकk(KERN_WARNING "snd-powermac: can't locate macio PCI"
		       " device !\n");

	detect_byte_swap(chip);

	/* look क्रम a property saying what sample rates
	   are available */
	prop = of_get_property(sound, "sample-rates", &l);
	अगर (! prop)
		prop = of_get_property(sound, "output-frame-rates", &l);
	अगर (prop) अणु
		पूर्णांक i;
		chip->freqs_ok = 0;
		क्रम (l /= माप(पूर्णांक); l > 0; --l) अणु
			अचिन्हित पूर्णांक r = *prop++;
			/* Apple 'Fixed' क्रमmat */
			अगर (r >= 0x10000)
				r >>= 16;
			क्रम (i = 0; i < chip->num_freqs; ++i) अणु
				अगर (r == chip->freq_table[i]) अणु
					chip->freqs_ok |= (1 << i);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* assume only 44.1khz */
		chip->freqs_ok = 1;
	पूर्ण

	of_node_put(sound);
	वापस 0;
पूर्ण

#अगर_घोषित PMAC_SUPPORT_AUTOMUTE
/*
 * स्वतः-mute
 */
अटल पूर्णांक pmac_स्वतः_mute_get(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	ucontrol->value.पूर्णांकeger.value[0] = chip->स्वतः_mute;
	वापस 0;
पूर्ण

अटल पूर्णांक pmac_स्वतः_mute_put(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	अगर (ucontrol->value.पूर्णांकeger.value[0] != chip->स्वतः_mute) अणु
		chip->स्वतः_mute = !!ucontrol->value.पूर्णांकeger.value[0];
		अगर (chip->update_स्वतःmute)
			chip->update_स्वतःmute(chip, 1);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pmac_hp_detect_get(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	अगर (chip->detect_headphone)
		ucontrol->value.पूर्णांकeger.value[0] = chip->detect_headphone(chip);
	अन्यथा
		ucontrol->value.पूर्णांकeger.value[0] = 0;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new स्वतः_mute_controls[] = अणु
	अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	  .name = "Auto Mute Switch",
	  .info = snd_pmac_boolean_mono_info,
	  .get = pmac_स्वतः_mute_get,
	  .put = pmac_स्वतः_mute_put,
	पूर्ण,
	अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	  .name = "Headphone Detection",
	  .access = SNDRV_CTL_ELEM_ACCESS_READ,
	  .info = snd_pmac_boolean_mono_info,
	  .get = pmac_hp_detect_get,
	पूर्ण,
पूर्ण;

पूर्णांक snd_pmac_add_स्वतःmute(काष्ठा snd_pmac *chip)
अणु
	पूर्णांक err;
	chip->स्वतः_mute = 1;
	err = snd_ctl_add(chip->card, snd_ctl_new1(&स्वतः_mute_controls[0], chip));
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR "snd-powermac: Failed to add automute control\n");
		वापस err;
	पूर्ण
	chip->hp_detect_ctl = snd_ctl_new1(&स्वतः_mute_controls[1], chip);
	वापस snd_ctl_add(chip->card, chip->hp_detect_ctl);
पूर्ण
#पूर्ण_अगर /* PMAC_SUPPORT_AUTOMUTE */

/*
 * create and detect a pmac chip record
 */
पूर्णांक snd_pmac_new(काष्ठा snd_card *card, काष्ठा snd_pmac **chip_वापस)
अणु
	काष्ठा snd_pmac *chip;
	काष्ठा device_node *np;
	पूर्णांक i, err;
	अचिन्हित पूर्णांक irq;
	अचिन्हित दीर्घ ctrl_addr, txdma_addr, rxdma_addr;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_pmac_dev_मुक्त,
	पूर्ण;

	*chip_वापस = शून्य;

	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य)
		वापस -ENOMEM;
	chip->card = card;

	spin_lock_init(&chip->reg_lock);
	chip->irq = chip->tx_irq = chip->rx_irq = -1;

	chip->playback.stream = SNDRV_PCM_STREAM_PLAYBACK;
	chip->capture.stream = SNDRV_PCM_STREAM_CAPTURE;

	अगर ((err = snd_pmac_detect(chip)) < 0)
		जाओ __error;

	अगर (snd_pmac_dbdma_alloc(chip, &chip->playback.cmd, PMAC_MAX_FRAGS + 1) < 0 ||
	    snd_pmac_dbdma_alloc(chip, &chip->capture.cmd, PMAC_MAX_FRAGS + 1) < 0 ||
	    snd_pmac_dbdma_alloc(chip, &chip->extra_dma, 2) < 0 ||
	    snd_pmac_dbdma_alloc(chip, &emergency_dbdma, 2) < 0) अणु
		err = -ENOMEM;
		जाओ __error;
	पूर्ण

	np = chip->node;
	chip->requested = 0;
	अगर (chip->is_k2) अणु
		अटल स्थिर अक्षर * स्थिर rnames[] = अणु
			"Sound Control", "Sound DMA" पूर्ण;
		क्रम (i = 0; i < 2; i ++) अणु
			अगर (of_address_to_resource(np->parent, i,
						   &chip->rsrc[i])) अणु
				prपूर्णांकk(KERN_ERR "snd: can't translate rsrc "
				       " %d (%s)\n", i, rnames[i]);
				err = -ENODEV;
				जाओ __error;
			पूर्ण
			अगर (request_mem_region(chip->rsrc[i].start,
					       resource_size(&chip->rsrc[i]),
					       rnames[i]) == शून्य) अणु
				prपूर्णांकk(KERN_ERR "snd: can't request rsrc "
				       " %d (%s: %pR)\n",
				       i, rnames[i], &chip->rsrc[i]);
				err = -ENODEV;
				जाओ __error;
			पूर्ण
			chip->requested |= (1 << i);
		पूर्ण
		ctrl_addr = chip->rsrc[0].start;
		txdma_addr = chip->rsrc[1].start;
		rxdma_addr = txdma_addr + 0x100;
	पूर्ण अन्यथा अणु
		अटल स्थिर अक्षर * स्थिर rnames[] = अणु
			"Sound Control", "Sound Tx DMA", "Sound Rx DMA" पूर्ण;
		क्रम (i = 0; i < 3; i ++) अणु
			अगर (of_address_to_resource(np, i,
						   &chip->rsrc[i])) अणु
				prपूर्णांकk(KERN_ERR "snd: can't translate rsrc "
				       " %d (%s)\n", i, rnames[i]);
				err = -ENODEV;
				जाओ __error;
			पूर्ण
			अगर (request_mem_region(chip->rsrc[i].start,
					       resource_size(&chip->rsrc[i]),
					       rnames[i]) == शून्य) अणु
				prपूर्णांकk(KERN_ERR "snd: can't request rsrc "
				       " %d (%s: %pR)\n",
				       i, rnames[i], &chip->rsrc[i]);
				err = -ENODEV;
				जाओ __error;
			पूर्ण
			chip->requested |= (1 << i);
		पूर्ण
		ctrl_addr = chip->rsrc[0].start;
		txdma_addr = chip->rsrc[1].start;
		rxdma_addr = chip->rsrc[2].start;
	पूर्ण

	chip->awacs = ioremap(ctrl_addr, 0x1000);
	chip->playback.dma = ioremap(txdma_addr, 0x100);
	chip->capture.dma = ioremap(rxdma_addr, 0x100);
	अगर (chip->model <= PMAC_BURGUNDY) अणु
		irq = irq_of_parse_and_map(np, 0);
		अगर (request_irq(irq, snd_pmac_ctrl_पूर्णांकr, 0,
				"PMac", (व्योम*)chip)) अणु
			snd_prपूर्णांकk(KERN_ERR "pmac: unable to grab IRQ %d\n",
				   irq);
			err = -EBUSY;
			जाओ __error;
		पूर्ण
		chip->irq = irq;
	पूर्ण
	irq = irq_of_parse_and_map(np, 1);
	अगर (request_irq(irq, snd_pmac_tx_पूर्णांकr, 0, "PMac Output", (व्योम*)chip))अणु
		snd_prपूर्णांकk(KERN_ERR "pmac: unable to grab IRQ %d\n", irq);
		err = -EBUSY;
		जाओ __error;
	पूर्ण
	chip->tx_irq = irq;
	irq = irq_of_parse_and_map(np, 2);
	अगर (request_irq(irq, snd_pmac_rx_पूर्णांकr, 0, "PMac Input", (व्योम*)chip)) अणु
		snd_prपूर्णांकk(KERN_ERR "pmac: unable to grab IRQ %d\n", irq);
		err = -EBUSY;
		जाओ __error;
	पूर्ण
	chip->rx_irq = irq;

	snd_pmac_sound_feature(chip, 1);

	/* reset & enable पूर्णांकerrupts */
	अगर (chip->model <= PMAC_BURGUNDY)
		out_le32(&chip->awacs->control, chip->control_mask);

	/* Powerbooks have odd ways of enabling inमाला_दो such as
	   an expansion-bay CD or sound from an पूर्णांकernal modem
	   or a PC-card modem. */
	अगर (chip->is_pbook_3400) अणु
		/* Enable CD and PC-card sound inमाला_दो. */
		/* This is करोne by पढ़ोing from address
		 * f301a000, + 0x10 to enable the expansion-bay
		 * CD sound input, + 0x80 to enable the PC-card
		 * sound input.  The 0x100 enables the SCSI bus
		 * terminator घातer.
		 */
		chip->latch_base = ioremap (0xf301a000, 0x1000);
		in_8(chip->latch_base + 0x190);
	पूर्ण अन्यथा अगर (chip->is_pbook_G3) अणु
		काष्ठा device_node* mio;
		क्रम (mio = chip->node->parent; mio; mio = mio->parent) अणु
			अगर (of_node_name_eq(mio, "mac-io")) अणु
				काष्ठा resource r;
				अगर (of_address_to_resource(mio, 0, &r) == 0)
					chip->macio_base =
						ioremap(r.start, 0x40);
				अवरोध;
			पूर्ण
		पूर्ण
		/* Enable CD sound input. */
		/* The relevant bits क्रम writing to this byte are 0x8f.
		 * I haven't found out what the 0x80 bit करोes.
		 * For the 0xf bits, writing 3 or 7 enables the CD
		 * input, any other value disables it.  Values
		 * 1, 3, 5, 7 enable the microphone.  Values 0, 2,
		 * 4, 6, 8 - f enable the input from the modem.
		 */
		अगर (chip->macio_base)
			out_8(chip->macio_base + 0x37, 3);
	पूर्ण

	/* Reset dbdma channels */
	snd_pmac_dbdma_reset(chip);

	अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops)) < 0)
		जाओ __error;

	*chip_वापस = chip;
	वापस 0;

 __error:
	snd_pmac_मुक्त(chip);
	वापस err;
पूर्ण


/*
 * sleep notअगरy क्रम घातerbook
 */

#अगर_घोषित CONFIG_PM

/*
 * Save state when going to sleep, restore it afterwards.
 */

व्योम snd_pmac_suspend(काष्ठा snd_pmac *chip)
अणु
	अचिन्हित दीर्घ flags;

	snd_घातer_change_state(chip->card, SNDRV_CTL_POWER_D3hot);
	अगर (chip->suspend)
		chip->suspend(chip);
	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_pmac_beep_stop(chip);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	अगर (chip->irq >= 0)
		disable_irq(chip->irq);
	अगर (chip->tx_irq >= 0)
		disable_irq(chip->tx_irq);
	अगर (chip->rx_irq >= 0)
		disable_irq(chip->rx_irq);
	snd_pmac_sound_feature(chip, 0);
पूर्ण

व्योम snd_pmac_resume(काष्ठा snd_pmac *chip)
अणु
	snd_pmac_sound_feature(chip, 1);
	अगर (chip->resume)
		chip->resume(chip);
	/* enable CD sound input */
	अगर (chip->macio_base && chip->is_pbook_G3)
		out_8(chip->macio_base + 0x37, 3);
	अन्यथा अगर (chip->is_pbook_3400)
		in_8(chip->latch_base + 0x190);

	snd_pmac_pcm_set_क्रमmat(chip);

	अगर (chip->irq >= 0)
		enable_irq(chip->irq);
	अगर (chip->tx_irq >= 0)
		enable_irq(chip->tx_irq);
	अगर (chip->rx_irq >= 0)
		enable_irq(chip->rx_irq);

	snd_घातer_change_state(chip->card, SNDRV_CTL_POWER_D0);
पूर्ण

#पूर्ण_अगर /* CONFIG_PM */

