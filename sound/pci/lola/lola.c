<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Support क्रम Digigram Lola PCI-e boards
 *
 *  Copyright (c) 2011 Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/initval.h>
#समावेश "lola.h"

/* Standard options */
अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for Digigram Lola driver.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for Digigram Lola driver.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable Digigram Lola driver.");

/* Lola-specअगरic options */

/* क्रम instance use always max granularity which is compatible
 * with all sample rates
 */
अटल पूर्णांक granularity[SNDRV_CARDS] = अणु
	[0 ... (SNDRV_CARDS - 1)] = LOLA_GRANULARITY_MAX
पूर्ण;

/* below a sample_rate of 16kHz the analogue audio quality is NOT excellent */
अटल पूर्णांक sample_rate_min[SNDRV_CARDS] = अणु
	[0 ... (SNDRV_CARDS - 1) ] = 16000
पूर्ण;

module_param_array(granularity, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(granularity, "Granularity value");
module_param_array(sample_rate_min, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(sample_rate_min, "Minimal sample rate");

/*
 */

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Digigram Lola driver");
MODULE_AUTHOR("Takashi Iwai <tiwai@suse.de>");

#अगर_घोषित CONFIG_SND_DEBUG_VERBOSE
अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
#घोषणा verbose_debug(fmt, args...)			\
	करो अणु अगर (debug > 1) pr_debug(SFX fmt, ##args); पूर्ण जबतक (0)
#अन्यथा
#घोषणा verbose_debug(fmt, args...)
#पूर्ण_अगर

/*
 * pseuकरो-codec पढ़ो/ग_लिखो via CORB/RIRB
 */

अटल पूर्णांक corb_send_verb(काष्ठा lola *chip, अचिन्हित पूर्णांक nid,
			  अचिन्हित पूर्णांक verb, अचिन्हित पूर्णांक data,
			  अचिन्हित पूर्णांक extdata)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -EIO;

	chip->last_cmd_nid = nid;
	chip->last_verb = verb;
	chip->last_data = data;
	chip->last_extdata = extdata;
	data |= (nid << 20) | (verb << 8);

	spin_lock_irqsave(&chip->reg_lock, flags);
	अगर (chip->rirb.cmds < LOLA_CORB_ENTRIES - 1) अणु
		अचिन्हित पूर्णांक wp = chip->corb.wp + 1;
		wp %= LOLA_CORB_ENTRIES;
		chip->corb.wp = wp;
		chip->corb.buf[wp * 2] = cpu_to_le32(data);
		chip->corb.buf[wp * 2 + 1] = cpu_to_le32(extdata);
		lola_ग_लिखोw(chip, BAR0, CORBWP, wp);
		chip->rirb.cmds++;
		smp_wmb();
		ret = 0;
	पूर्ण
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस ret;
पूर्ण

अटल व्योम lola_queue_unsol_event(काष्ठा lola *chip, अचिन्हित पूर्णांक res,
				   अचिन्हित पूर्णांक res_ex)
अणु
	lola_update_ext_घड़ी_freq(chip, res);
पूर्ण

/* retrieve RIRB entry - called from पूर्णांकerrupt handler */
अटल व्योम lola_update_rirb(काष्ठा lola *chip)
अणु
	अचिन्हित पूर्णांक rp, wp;
	u32 res, res_ex;

	wp = lola_पढ़ोw(chip, BAR0, RIRBWP);
	अगर (wp == chip->rirb.wp)
		वापस;
	chip->rirb.wp = wp;

	जबतक (chip->rirb.rp != wp) अणु
		chip->rirb.rp++;
		chip->rirb.rp %= LOLA_CORB_ENTRIES;

		rp = chip->rirb.rp << 1; /* an RIRB entry is 8-bytes */
		res_ex = le32_to_cpu(chip->rirb.buf[rp + 1]);
		res = le32_to_cpu(chip->rirb.buf[rp]);
		अगर (res_ex & LOLA_RIRB_EX_UNSOL_EV)
			lola_queue_unsol_event(chip, res, res_ex);
		अन्यथा अगर (chip->rirb.cmds) अणु
			chip->res = res;
			chip->res_ex = res_ex;
			smp_wmb();
			chip->rirb.cmds--;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक rirb_get_response(काष्ठा lola *chip, अचिन्हित पूर्णांक *val,
			     अचिन्हित पूर्णांक *extval)
अणु
	अचिन्हित दीर्घ समयout;

 again:
	समयout = jअगरfies + msecs_to_jअगरfies(1000);
	क्रम (;;) अणु
		अगर (chip->polling_mode) अणु
			spin_lock_irq(&chip->reg_lock);
			lola_update_rirb(chip);
			spin_unlock_irq(&chip->reg_lock);
		पूर्ण
		अगर (!chip->rirb.cmds) अणु
			*val = chip->res;
			अगर (extval)
				*extval = chip->res_ex;
			verbose_debug("get_response: %x, %x\n",
				      chip->res, chip->res_ex);
			अगर (chip->res_ex & LOLA_RIRB_EX_ERROR) अणु
				dev_warn(chip->card->dev, "RIRB ERROR: "
				       "NID=%x, verb=%x, data=%x, ext=%x\n",
				       chip->last_cmd_nid,
				       chip->last_verb, chip->last_data,
				       chip->last_extdata);
				वापस -EIO;
			पूर्ण
			वापस 0;
		पूर्ण
		अगर (समय_after(jअगरfies, समयout))
			अवरोध;
		udelay(20);
		cond_resched();
	पूर्ण
	dev_warn(chip->card->dev, "RIRB response error\n");
	अगर (!chip->polling_mode) अणु
		dev_warn(chip->card->dev, "switching to polling mode\n");
		chip->polling_mode = 1;
		जाओ again;
	पूर्ण
	वापस -EIO;
पूर्ण

/* aynchronous ग_लिखो of a codec verb with data */
पूर्णांक lola_codec_ग_लिखो(काष्ठा lola *chip, अचिन्हित पूर्णांक nid, अचिन्हित पूर्णांक verb,
		     अचिन्हित पूर्णांक data, अचिन्हित पूर्णांक extdata)
अणु
	verbose_debug("codec_write NID=%x, verb=%x, data=%x, ext=%x\n",
		      nid, verb, data, extdata);
	वापस corb_send_verb(chip, nid, verb, data, extdata);
पूर्ण

/* ग_लिखो a codec verb with data and पढ़ो the वापसed status */
पूर्णांक lola_codec_पढ़ो(काष्ठा lola *chip, अचिन्हित पूर्णांक nid, अचिन्हित पूर्णांक verb,
		    अचिन्हित पूर्णांक data, अचिन्हित पूर्णांक extdata,
		    अचिन्हित पूर्णांक *val, अचिन्हित पूर्णांक *extval)
अणु
	पूर्णांक err;

	verbose_debug("codec_read NID=%x, verb=%x, data=%x, ext=%x\n",
		      nid, verb, data, extdata);
	err = corb_send_verb(chip, nid, verb, data, extdata);
	अगर (err < 0)
		वापस err;
	err = rirb_get_response(chip, val, extval);
	वापस err;
पूर्ण

/* flush all pending codec ग_लिखोs */
पूर्णांक lola_codec_flush(काष्ठा lola *chip)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	वापस rirb_get_response(chip, &पंचांगp, शून्य);
पूर्ण

/*
 * पूर्णांकerrupt handler
 */
अटल irqवापस_t lola_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा lola *chip = dev_id;
	अचिन्हित पूर्णांक notअगरy_ins, notअगरy_outs, error_ins, error_outs;
	पूर्णांक handled = 0;
	पूर्णांक i;

	notअगरy_ins = notअगरy_outs = error_ins = error_outs = 0;
	spin_lock(&chip->reg_lock);
	क्रम (;;) अणु
		अचिन्हित पूर्णांक status, in_sts, out_sts;
		अचिन्हित पूर्णांक reg;

		status = lola_पढ़ोl(chip, BAR1, DINTSTS);
		अगर (!status || status == -1)
			अवरोध;

		in_sts = lola_पढ़ोl(chip, BAR1, DIINTSTS);
		out_sts = lola_पढ़ोl(chip, BAR1, DOINTSTS);

		/* clear Input Interrupts */
		क्रम (i = 0; in_sts && i < chip->pcm[CAPT].num_streams; i++) अणु
			अगर (!(in_sts & (1 << i)))
				जारी;
			in_sts &= ~(1 << i);
			reg = lola_dsd_पढ़ो(chip, i, STS);
			अगर (reg & LOLA_DSD_STS_DESE) /* error */
				error_ins |= (1 << i);
			अगर (reg & LOLA_DSD_STS_BCIS) /* notअगरy */
				notअगरy_ins |= (1 << i);
			/* clear */
			lola_dsd_ग_लिखो(chip, i, STS, reg);
		पूर्ण

		/* clear Output Interrupts */
		क्रम (i = 0; out_sts && i < chip->pcm[PLAY].num_streams; i++) अणु
			अगर (!(out_sts & (1 << i)))
				जारी;
			out_sts &= ~(1 << i);
			reg = lola_dsd_पढ़ो(chip, i + MAX_STREAM_IN_COUNT, STS);
			अगर (reg & LOLA_DSD_STS_DESE) /* error */
				error_outs |= (1 << i);
			अगर (reg & LOLA_DSD_STS_BCIS) /* notअगरy */
				notअगरy_outs |= (1 << i);
			lola_dsd_ग_लिखो(chip, i + MAX_STREAM_IN_COUNT, STS, reg);
		पूर्ण

		अगर (status & LOLA_DINT_CTRL) अणु
			अचिन्हित अक्षर rbsts; /* ring status is byte access */
			rbsts = lola_पढ़ोb(chip, BAR0, RIRBSTS);
			rbsts &= LOLA_RIRB_INT_MASK;
			अगर (rbsts)
				lola_ग_लिखोb(chip, BAR0, RIRBSTS, rbsts);
			rbsts = lola_पढ़ोb(chip, BAR0, CORBSTS);
			rbsts &= LOLA_CORB_INT_MASK;
			अगर (rbsts)
				lola_ग_लिखोb(chip, BAR0, CORBSTS, rbsts);

			lola_update_rirb(chip);
		पूर्ण

		अगर (status & (LOLA_DINT_FIFOERR | LOLA_DINT_MUERR)) अणु
			/* clear global fअगरo error पूर्णांकerrupt */
			lola_ग_लिखोl(chip, BAR1, DINTSTS,
				    (status & (LOLA_DINT_FIFOERR | LOLA_DINT_MUERR)));
		पूर्ण
		handled = 1;
	पूर्ण
	spin_unlock(&chip->reg_lock);

	lola_pcm_update(chip, &chip->pcm[CAPT], notअगरy_ins);
	lola_pcm_update(chip, &chip->pcm[PLAY], notअगरy_outs);

	वापस IRQ_RETVAL(handled);
पूर्ण


/*
 * controller
 */
अटल पूर्णांक reset_controller(काष्ठा lola *chip)
अणु
	अचिन्हित पूर्णांक gctl = lola_पढ़ोl(chip, BAR0, GCTL);
	अचिन्हित दीर्घ end_समय;

	अगर (gctl) अणु
		/* to be sure */
		lola_ग_लिखोl(chip, BAR1, BOARD_MODE, 0);
		वापस 0;
	पूर्ण

	chip->cold_reset = 1;
	lola_ग_लिखोl(chip, BAR0, GCTL, LOLA_GCTL_RESET);
	end_समय = jअगरfies + msecs_to_jअगरfies(200);
	करो अणु
		msleep(1);
		gctl = lola_पढ़ोl(chip, BAR0, GCTL);
		अगर (gctl)
			अवरोध;
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, end_समय));
	अगर (!gctl) अणु
		dev_err(chip->card->dev, "cannot reset controller\n");
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम lola_irq_enable(काष्ठा lola *chip)
अणु
	अचिन्हित पूर्णांक val;

	/* enalbe all I/O streams */
	val = (1 << chip->pcm[PLAY].num_streams) - 1;
	lola_ग_लिखोl(chip, BAR1, DOINTCTL, val);
	val = (1 << chip->pcm[CAPT].num_streams) - 1;
	lola_ग_लिखोl(chip, BAR1, DIINTCTL, val);

	/* enable global irqs */
	val = LOLA_DINT_GLOBAL | LOLA_DINT_CTRL | LOLA_DINT_FIFOERR |
		LOLA_DINT_MUERR;
	lola_ग_लिखोl(chip, BAR1, DINTCTL, val);
पूर्ण

अटल व्योम lola_irq_disable(काष्ठा lola *chip)
अणु
	lola_ग_लिखोl(chip, BAR1, DINTCTL, 0);
	lola_ग_लिखोl(chip, BAR1, DIINTCTL, 0);
	lola_ग_लिखोl(chip, BAR1, DOINTCTL, 0);
पूर्ण

अटल पूर्णांक setup_corb_rirb(काष्ठा lola *chip)
अणु
	पूर्णांक err;
	अचिन्हित अक्षर पंचांगp;
	अचिन्हित दीर्घ end_समय;

	err = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV,
				  &chip->pci->dev,
				  PAGE_SIZE, &chip->rb);
	अगर (err < 0)
		वापस err;

	chip->corb.addr = chip->rb.addr;
	chip->corb.buf = (__le32 *)chip->rb.area;
	chip->rirb.addr = chip->rb.addr + 2048;
	chip->rirb.buf = (__le32 *)(chip->rb.area + 2048);

	/* disable ringbuffer DMAs */
	lola_ग_लिखोb(chip, BAR0, RIRBCTL, 0);
	lola_ग_लिखोb(chip, BAR0, CORBCTL, 0);

	end_समय = jअगरfies + msecs_to_jअगरfies(200);
	करो अणु
		अगर (!lola_पढ़ोb(chip, BAR0, RIRBCTL) &&
		    !lola_पढ़ोb(chip, BAR0, CORBCTL))
			अवरोध;
		msleep(1);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, end_समय));

	/* CORB set up */
	lola_ग_लिखोl(chip, BAR0, CORBLBASE, (u32)chip->corb.addr);
	lola_ग_लिखोl(chip, BAR0, CORBUBASE, upper_32_bits(chip->corb.addr));
	/* set the corb size to 256 entries */
	lola_ग_लिखोb(chip, BAR0, CORBSIZE, 0x02);
	/* set the corb ग_लिखो poपूर्णांकer to 0 */
	lola_ग_लिखोw(chip, BAR0, CORBWP, 0);
	/* reset the corb hw पढ़ो poपूर्णांकer */
	lola_ग_लिखोw(chip, BAR0, CORBRP, LOLA_RBRWP_CLR);
	/* enable corb dma */
	lola_ग_लिखोb(chip, BAR0, CORBCTL, LOLA_RBCTL_DMA_EN);
	/* clear flags अगर set */
	पंचांगp = lola_पढ़ोb(chip, BAR0, CORBSTS) & LOLA_CORB_INT_MASK;
	अगर (पंचांगp)
		lola_ग_लिखोb(chip, BAR0, CORBSTS, पंचांगp);
	chip->corb.wp = 0;

	/* RIRB set up */
	lola_ग_लिखोl(chip, BAR0, RIRBLBASE, (u32)chip->rirb.addr);
	lola_ग_लिखोl(chip, BAR0, RIRBUBASE, upper_32_bits(chip->rirb.addr));
	/* set the rirb size to 256 entries */
	lola_ग_लिखोb(chip, BAR0, RIRBSIZE, 0x02);
	/* reset the rirb hw ग_लिखो poपूर्णांकer */
	lola_ग_लिखोw(chip, BAR0, RIRBWP, LOLA_RBRWP_CLR);
	/* set N=1, get RIRB response पूर्णांकerrupt क्रम new entry */
	lola_ग_लिखोw(chip, BAR0, RINTCNT, 1);
	/* enable rirb dma and response irq */
	lola_ग_लिखोb(chip, BAR0, RIRBCTL, LOLA_RBCTL_DMA_EN | LOLA_RBCTL_IRQ_EN);
	/* clear flags अगर set */
	पंचांगp =  lola_पढ़ोb(chip, BAR0, RIRBSTS) & LOLA_RIRB_INT_MASK;
	अगर (पंचांगp)
		lola_ग_लिखोb(chip, BAR0, RIRBSTS, पंचांगp);
	chip->rirb.rp = chip->rirb.cmds = 0;

	वापस 0;
पूर्ण

अटल व्योम stop_corb_rirb(काष्ठा lola *chip)
अणु
	/* disable ringbuffer DMAs */
	lola_ग_लिखोb(chip, BAR0, RIRBCTL, 0);
	lola_ग_लिखोb(chip, BAR0, CORBCTL, 0);
पूर्ण

अटल व्योम lola_reset_setups(काष्ठा lola *chip)
अणु
	/* update the granularity */
	lola_set_granularity(chip, chip->granularity, true);
	/* update the sample घड़ी */
	lola_set_घड़ी_index(chip, chip->घड़ी.cur_index);
	/* enable unsolicited events of the घड़ी widget */
	lola_enable_घड़ी_events(chip);
	/* update the analog gains */
	lola_setup_all_analog_gains(chip, CAPT, false); /* input, update */
	/* update SRC configuration अगर applicable */
	lola_set_src_config(chip, chip->input_src_mask, false);
	/* update the analog outमाला_दो */
	lola_setup_all_analog_gains(chip, PLAY, false); /* output, update */
पूर्ण

अटल पूर्णांक lola_parse_tree(काष्ठा lola *chip)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक nid, err;

	err = lola_पढ़ो_param(chip, 0, LOLA_PAR_VENDOR_ID, &val);
	अगर (err < 0) अणु
		dev_err(chip->card->dev, "Can't read VENDOR_ID\n");
		वापस err;
	पूर्ण
	val >>= 16;
	अगर (val != 0x1369) अणु
		dev_err(chip->card->dev, "Unknown codec vendor 0x%x\n", val);
		वापस -EINVAL;
	पूर्ण

	err = lola_पढ़ो_param(chip, 1, LOLA_PAR_FUNCTION_TYPE, &val);
	अगर (err < 0) अणु
		dev_err(chip->card->dev, "Can't read FUNCTION_TYPE\n");
		वापस err;
	पूर्ण
	अगर (val != 1) अणु
		dev_err(chip->card->dev, "Unknown function type %d\n", val);
		वापस -EINVAL;
	पूर्ण

	err = lola_पढ़ो_param(chip, 1, LOLA_PAR_SPECIFIC_CAPS, &val);
	अगर (err < 0) अणु
		dev_err(chip->card->dev, "Can't read SPECCAPS\n");
		वापस err;
	पूर्ण
	chip->lola_caps = val;
	chip->pin[CAPT].num_pins = LOLA_AFG_INPUT_PIN_COUNT(chip->lola_caps);
	chip->pin[PLAY].num_pins = LOLA_AFG_OUTPUT_PIN_COUNT(chip->lola_caps);
	dev_dbg(chip->card->dev, "speccaps=0x%x, pins in=%d, out=%d\n",
		    chip->lola_caps,
		    chip->pin[CAPT].num_pins, chip->pin[PLAY].num_pins);

	अगर (chip->pin[CAPT].num_pins > MAX_AUDIO_INOUT_COUNT ||
	    chip->pin[PLAY].num_pins > MAX_AUDIO_INOUT_COUNT) अणु
		dev_err(chip->card->dev, "Invalid Lola-spec caps 0x%x\n", val);
		वापस -EINVAL;
	पूर्ण

	nid = 0x02;
	err = lola_init_pcm(chip, CAPT, &nid);
	अगर (err < 0)
		वापस err;
	err = lola_init_pcm(chip, PLAY, &nid);
	अगर (err < 0)
		वापस err;

	err = lola_init_pins(chip, CAPT, &nid);
	अगर (err < 0)
		वापस err;
	err = lola_init_pins(chip, PLAY, &nid);
	अगर (err < 0)
		वापस err;

	अगर (LOLA_AFG_CLOCK_WIDGET_PRESENT(chip->lola_caps)) अणु
		err = lola_init_घड़ी_widget(chip, nid);
		अगर (err < 0)
			वापस err;
		nid++;
	पूर्ण
	अगर (LOLA_AFG_MIXER_WIDGET_PRESENT(chip->lola_caps)) अणु
		err = lola_init_mixer_widget(chip, nid);
		अगर (err < 0)
			वापस err;
		nid++;
	पूर्ण

	/* enable unsolicited events of the घड़ी widget */
	err = lola_enable_घड़ी_events(chip);
	अगर (err < 0)
		वापस err;

	/* अगर last ResetController was not a ColdReset, we करोn't know
	 * the state of the card; initialize here again
	 */
	अगर (!chip->cold_reset) अणु
		lola_reset_setups(chip);
		chip->cold_reset = 1;
	पूर्ण अन्यथा अणु
		/* set the granularity अगर it is not the शेष */
		अगर (chip->granularity != LOLA_GRANULARITY_MIN)
			lola_set_granularity(chip, chip->granularity, true);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम lola_stop_hw(काष्ठा lola *chip)
अणु
	stop_corb_rirb(chip);
	lola_irq_disable(chip);
पूर्ण

अटल व्योम lola_मुक्त(काष्ठा lola *chip)
अणु
	अगर (chip->initialized)
		lola_stop_hw(chip);
	lola_मुक्त_pcm(chip);
	lola_मुक्त_mixer(chip);
	अगर (chip->irq >= 0)
		मुक्त_irq(chip->irq, (व्योम *)chip);
	iounmap(chip->bar[0].remap_addr);
	iounmap(chip->bar[1].remap_addr);
	अगर (chip->rb.area)
		snd_dma_मुक्त_pages(&chip->rb);
	pci_release_regions(chip->pci);
	pci_disable_device(chip->pci);
	kमुक्त(chip);
पूर्ण

अटल पूर्णांक lola_dev_मुक्त(काष्ठा snd_device *device)
अणु
	lola_मुक्त(device->device_data);
	वापस 0;
पूर्ण

अटल पूर्णांक lola_create(काष्ठा snd_card *card, काष्ठा pci_dev *pci,
		       पूर्णांक dev, काष्ठा lola **rchip)
अणु
	काष्ठा lola *chip;
	पूर्णांक err;
	अचिन्हित पूर्णांक dever;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त = lola_dev_मुक्त,
	पूर्ण;

	*rchip = शून्य;

	err = pci_enable_device(pci);
	अगर (err < 0)
		वापस err;

	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (!chip) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण

	spin_lock_init(&chip->reg_lock);
	mutex_init(&chip->खोलो_mutex);
	chip->card = card;
	chip->pci = pci;
	chip->irq = -1;

	chip->granularity = granularity[dev];
	चयन (chip->granularity) अणु
	हाल 8:
		chip->sample_rate_max = 48000;
		अवरोध;
	हाल 16:
		chip->sample_rate_max = 96000;
		अवरोध;
	हाल 32:
		chip->sample_rate_max = 192000;
		अवरोध;
	शेष:
		dev_warn(chip->card->dev,
			   "Invalid granularity %d, reset to %d\n",
			   chip->granularity, LOLA_GRANULARITY_MAX);
		chip->granularity = LOLA_GRANULARITY_MAX;
		chip->sample_rate_max = 192000;
		अवरोध;
	पूर्ण
	chip->sample_rate_min = sample_rate_min[dev];
	अगर (chip->sample_rate_min > chip->sample_rate_max) अणु
		dev_warn(chip->card->dev,
			   "Invalid sample_rate_min %d, reset to 16000\n",
			   chip->sample_rate_min);
		chip->sample_rate_min = 16000;
	पूर्ण

	err = pci_request_regions(pci, DRVNAME);
	अगर (err < 0) अणु
		kमुक्त(chip);
		pci_disable_device(pci);
		वापस err;
	पूर्ण

	chip->bar[0].addr = pci_resource_start(pci, 0);
	chip->bar[0].remap_addr = pci_ioremap_bar(pci, 0);
	chip->bar[1].addr = pci_resource_start(pci, 2);
	chip->bar[1].remap_addr = pci_ioremap_bar(pci, 2);
	अगर (!chip->bar[0].remap_addr || !chip->bar[1].remap_addr) अणु
		dev_err(chip->card->dev, "ioremap error\n");
		err = -ENXIO;
		जाओ errout;
	पूर्ण

	pci_set_master(pci);

	err = reset_controller(chip);
	अगर (err < 0)
		जाओ errout;

	अगर (request_irq(pci->irq, lola_पूर्णांकerrupt, IRQF_SHARED,
			KBUILD_MODNAME, chip)) अणु
		dev_err(chip->card->dev, "unable to grab IRQ %d\n", pci->irq);
		err = -EBUSY;
		जाओ errout;
	पूर्ण
	chip->irq = pci->irq;
	card->sync_irq = chip->irq;

	dever = lola_पढ़ोl(chip, BAR1, DEVER);
	chip->pcm[CAPT].num_streams = (dever >> 0) & 0x3ff;
	chip->pcm[PLAY].num_streams = (dever >> 10) & 0x3ff;
	chip->version = (dever >> 24) & 0xff;
	dev_dbg(chip->card->dev, "streams in=%d, out=%d, version=0x%x\n",
		    chip->pcm[CAPT].num_streams, chip->pcm[PLAY].num_streams,
		    chip->version);

	/* Test LOLA_BAR1_DEVER */
	अगर (chip->pcm[CAPT].num_streams > MAX_STREAM_IN_COUNT ||
	    chip->pcm[PLAY].num_streams > MAX_STREAM_OUT_COUNT ||
	    (!chip->pcm[CAPT].num_streams &&
	     !chip->pcm[PLAY].num_streams)) अणु
		dev_err(chip->card->dev, "invalid DEVER = %x\n", dever);
		err = -EINVAL;
		जाओ errout;
	पूर्ण

	err = setup_corb_rirb(chip);
	अगर (err < 0)
		जाओ errout;

	err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops);
	अगर (err < 0) अणु
		dev_err(chip->card->dev, "Error creating device [card]!\n");
		जाओ errout;
	पूर्ण

	म_नकल(card->driver, "Lola");
	strscpy(card->लघुname, "Digigram Lola", माप(card->लघुname));
	snम_लिखो(card->दीर्घname, माप(card->दीर्घname),
		 "%s at 0x%lx irq %i",
		 card->लघुname, chip->bar[0].addr, chip->irq);
	म_नकल(card->mixername, card->लघुname);

	lola_irq_enable(chip);

	chip->initialized = 1;
	*rchip = chip;
	वापस 0;

 errout:
	lola_मुक्त(chip);
	वापस err;
पूर्ण

अटल पूर्णांक lola_probe(काष्ठा pci_dev *pci,
		      स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	काष्ठा lola *chip;
	पूर्णांक err;

	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;
	अगर (!enable[dev]) अणु
		dev++;
		वापस -ENOENT;
	पूर्ण

	err = snd_card_new(&pci->dev, index[dev], id[dev], THIS_MODULE,
			   0, &card);
	अगर (err < 0) अणु
		dev_err(&pci->dev, "Error creating card!\n");
		वापस err;
	पूर्ण

	err = lola_create(card, pci, dev, &chip);
	अगर (err < 0)
		जाओ out_मुक्त;
	card->निजी_data = chip;

	err = lola_parse_tree(chip);
	अगर (err < 0)
		जाओ out_मुक्त;

	err = lola_create_pcm(chip);
	अगर (err < 0)
		जाओ out_मुक्त;

	err = lola_create_mixer(chip);
	अगर (err < 0)
		जाओ out_मुक्त;

	lola_proc_debug_new(chip);

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ out_मुक्त;

	pci_set_drvdata(pci, card);
	dev++;
	वापस err;
out_मुक्त:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल व्योम lola_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

/* PCI IDs */
अटल स्थिर काष्ठा pci_device_id lola_ids[] = अणु
	अणु PCI_VDEVICE(DIGIGRAM, 0x0001) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, lola_ids);

/* pci_driver definition */
अटल काष्ठा pci_driver lola_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = lola_ids,
	.probe = lola_probe,
	.हटाओ = lola_हटाओ,
पूर्ण;

module_pci_driver(lola_driver);
