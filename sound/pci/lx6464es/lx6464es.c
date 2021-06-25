<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* -*- linux-c -*- *
 *
 * ALSA driver क्रम the digigram lx6464es पूर्णांकerface
 *
 * Copyright (c) 2008, 2009 Tim Blechmann <tim@klingt.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>

#समावेश <sound/initval.h>
#समावेश <sound/control.h>
#समावेश <sound/info.h>

#समावेश "lx6464es.h"

MODULE_AUTHOR("Tim Blechmann");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("digigram lx6464es");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for Digigram LX6464ES interface.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for  Digigram LX6464ES interface.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable/disable specific Digigram LX6464ES soundcards.");

अटल स्थिर अक्षर card_name[] = "LX6464ES";


#घोषणा PCI_DEVICE_ID_PLX_LX6464ES		PCI_DEVICE_ID_PLX_9056

अटल स्थिर काष्ठा pci_device_id snd_lx6464es_ids[] = अणु
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_LX6464ES,
			 PCI_VENDOR_ID_DIGIGRAM,
			 PCI_SUBDEVICE_ID_DIGIGRAM_LX6464ES_SERIAL_SUBSYSTEM),
	पूर्ण,			/* LX6464ES */
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_LX6464ES,
			 PCI_VENDOR_ID_DIGIGRAM,
			 PCI_SUBDEVICE_ID_DIGIGRAM_LX6464ES_CAE_SERIAL_SUBSYSTEM),
	पूर्ण,			/* LX6464ES-CAE */
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_LX6464ES,
			 PCI_VENDOR_ID_DIGIGRAM,
			 PCI_SUBDEVICE_ID_DIGIGRAM_LX6464ESE_SERIAL_SUBSYSTEM),
	पूर्ण,			/* LX6464ESe */
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_LX6464ES,
			 PCI_VENDOR_ID_DIGIGRAM,
			 PCI_SUBDEVICE_ID_DIGIGRAM_LX6464ESE_CAE_SERIAL_SUBSYSTEM),
	पूर्ण,			/* LX6464ESe-CAE */
	अणु 0, पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_lx6464es_ids);



/* PGO pour USERo dans le registre pci_0x06/loc_0xEC */
#घोषणा CHIPSC_RESET_XILINX (1L<<16)


/* alsa callbacks */
अटल स्थिर काष्ठा snd_pcm_hardware lx_caps = अणु
	.info             = (SNDRV_PCM_INFO_MMAP |
			     SNDRV_PCM_INFO_INTERLEAVED |
			     SNDRV_PCM_INFO_MMAP_VALID |
			     SNDRV_PCM_INFO_SYNC_START),
	.क्रमmats	  = (SNDRV_PCM_FMTBIT_S16_LE |
			     SNDRV_PCM_FMTBIT_S16_BE |
			     SNDRV_PCM_FMTBIT_S24_3LE |
			     SNDRV_PCM_FMTBIT_S24_3BE),
	.rates            = (SNDRV_PCM_RATE_CONTINUOUS |
			     SNDRV_PCM_RATE_8000_192000),
	.rate_min         = 8000,
	.rate_max         = 192000,
	.channels_min     = 2,
	.channels_max     = 64,
	.buffer_bytes_max = 64*2*3*MICROBLAZE_IBL_MAX*MAX_STREAM_BUFFER,
	.period_bytes_min = (2*2*MICROBLAZE_IBL_MIN*2),
	.period_bytes_max = (4*64*MICROBLAZE_IBL_MAX*MAX_STREAM_BUFFER),
	.periods_min      = 2,
	.periods_max      = MAX_STREAM_BUFFER,
पूर्ण;

अटल पूर्णांक lx_set_granularity(काष्ठा lx6464es *chip, u32 gran);


अटल पूर्णांक lx_hardware_खोलो(काष्ठा lx6464es *chip,
			    काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक err = 0;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक channels = runसमय->channels;
	पूर्णांक is_capture = (substream->stream == SNDRV_PCM_STREAM_CAPTURE);

	snd_pcm_uframes_t period_size = runसमय->period_size;

	dev_dbg(chip->card->dev, "allocating pipe for %d channels\n", channels);
	err = lx_pipe_allocate(chip, 0, is_capture, channels);
	अगर (err < 0) अणु
		dev_err(chip->card->dev, LXP "allocating pipe failed\n");
		वापस err;
	पूर्ण

	err = lx_set_granularity(chip, period_size);
	अगर (err < 0) अणु
		dev_err(chip->card->dev, "setting granularity to %ld failed\n",
			   period_size);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lx_hardware_start(काष्ठा lx6464es *chip,
			     काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक err = 0;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक is_capture = (substream->stream == SNDRV_PCM_STREAM_CAPTURE);

	dev_dbg(chip->card->dev, "setting stream format\n");
	err = lx_stream_set_क्रमmat(chip, runसमय, 0, is_capture);
	अगर (err < 0) अणु
		dev_err(chip->card->dev, "setting stream format failed\n");
		वापस err;
	पूर्ण

	dev_dbg(chip->card->dev, "starting pipe\n");
	err = lx_pipe_start(chip, 0, is_capture);
	अगर (err < 0) अणु
		dev_err(chip->card->dev, "starting pipe failed\n");
		वापस err;
	पूर्ण

	dev_dbg(chip->card->dev, "waiting for pipe to start\n");
	err = lx_pipe_रुको_क्रम_start(chip, 0, is_capture);
	अगर (err < 0) अणु
		dev_err(chip->card->dev, "waiting for pipe failed\n");
		वापस err;
	पूर्ण

	वापस err;
पूर्ण


अटल पूर्णांक lx_hardware_stop(काष्ठा lx6464es *chip,
			    काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक err = 0;
	पूर्णांक is_capture = (substream->stream == SNDRV_PCM_STREAM_CAPTURE);

	dev_dbg(chip->card->dev, "pausing pipe\n");
	err = lx_pipe_छोड़ो(chip, 0, is_capture);
	अगर (err < 0) अणु
		dev_err(chip->card->dev, "pausing pipe failed\n");
		वापस err;
	पूर्ण

	dev_dbg(chip->card->dev, "waiting for pipe to become idle\n");
	err = lx_pipe_रुको_क्रम_idle(chip, 0, is_capture);
	अगर (err < 0) अणु
		dev_err(chip->card->dev, "waiting for pipe failed\n");
		वापस err;
	पूर्ण

	dev_dbg(chip->card->dev, "stopping pipe\n");
	err = lx_pipe_stop(chip, 0, is_capture);
	अगर (err < 0) अणु
		dev_err(chip->card->dev, "stopping pipe failed\n");
		वापस err;
	पूर्ण

	वापस err;
पूर्ण


अटल पूर्णांक lx_hardware_बंद(काष्ठा lx6464es *chip,
			     काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक err = 0;
	पूर्णांक is_capture = (substream->stream == SNDRV_PCM_STREAM_CAPTURE);

	dev_dbg(chip->card->dev, "releasing pipe\n");
	err = lx_pipe_release(chip, 0, is_capture);
	अगर (err < 0) अणु
		dev_err(chip->card->dev, "releasing pipe failed\n");
		वापस err;
	पूर्ण

	वापस err;
पूर्ण


अटल पूर्णांक lx_pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा lx6464es *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err = 0;
	पूर्णांक board_rate;

	dev_dbg(chip->card->dev, "->lx_pcm_open\n");
	mutex_lock(&chip->setup_mutex);

	/* copy the काष्ठा snd_pcm_hardware काष्ठा */
	runसमय->hw = lx_caps;

#अगर 0
	/* buffer-size should better be multiple of period-size */
	err = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय,
					    SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (err < 0) अणु
		dev_warn(chip->card->dev, "could not constrain periods\n");
		जाओ निकास;
	पूर्ण
#पूर्ण_अगर

	/* the घड़ी rate cannot be changed */
	board_rate = chip->board_sample_rate;
	err = snd_pcm_hw_स्थिरraपूर्णांक_single(runसमय, SNDRV_PCM_HW_PARAM_RATE,
					   board_rate);

	अगर (err < 0) अणु
		dev_warn(chip->card->dev, "could not constrain periods\n");
		जाओ निकास;
	पूर्ण

	/* स्थिरrain period size */
	err = snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय,
					   SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
					   MICROBLAZE_IBL_MIN,
					   MICROBLAZE_IBL_MAX);
	अगर (err < 0) अणु
		dev_warn(chip->card->dev,
			   "could not constrain period size\n");
		जाओ निकास;
	पूर्ण

	snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0,
				   SNDRV_PCM_HW_PARAM_BUFFER_SIZE, 32);

	snd_pcm_set_sync(substream);
	err = 0;

निकास:
	runसमय->निजी_data = chip;

	mutex_unlock(&chip->setup_mutex);
	dev_dbg(chip->card->dev, "<-lx_pcm_open, %d\n", err);
	वापस err;
पूर्ण

अटल पूर्णांक lx_pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	dev_dbg(substream->pcm->card->dev, "->lx_pcm_close\n");
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t lx_pcm_stream_poपूर्णांकer(काष्ठा snd_pcm_substream
					       *substream)
अणु
	काष्ठा lx6464es *chip = snd_pcm_substream_chip(substream);
	snd_pcm_uframes_t pos;
	पूर्णांक is_capture = (substream->stream == SNDRV_PCM_STREAM_CAPTURE);

	काष्ठा lx_stream *lx_stream = is_capture ? &chip->capture_stream :
		&chip->playback_stream;

	dev_dbg(chip->card->dev, "->lx_pcm_stream_pointer\n");

	mutex_lock(&chip->lock);
	pos = lx_stream->frame_pos * substream->runसमय->period_size;
	mutex_unlock(&chip->lock);

	dev_dbg(chip->card->dev, "stream_pointer at %ld\n", pos);
	वापस pos;
पूर्ण

अटल पूर्णांक lx_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा lx6464es *chip = snd_pcm_substream_chip(substream);
	पूर्णांक err = 0;
	स्थिर पूर्णांक is_capture = (substream->stream == SNDRV_PCM_STREAM_CAPTURE);

	dev_dbg(chip->card->dev, "->lx_pcm_prepare\n");

	mutex_lock(&chip->setup_mutex);

	अगर (chip->hardware_running[is_capture]) अणु
		err = lx_hardware_stop(chip, substream);
		अगर (err < 0) अणु
			dev_err(chip->card->dev, "failed to stop hardware. "
				   "Error code %d\n", err);
			जाओ निकास;
		पूर्ण

		err = lx_hardware_बंद(chip, substream);
		अगर (err < 0) अणु
			dev_err(chip->card->dev, "failed to close hardware. "
				   "Error code %d\n", err);
			जाओ निकास;
		पूर्ण
	पूर्ण

	dev_dbg(chip->card->dev, "opening hardware\n");
	err = lx_hardware_खोलो(chip, substream);
	अगर (err < 0) अणु
		dev_err(chip->card->dev, "failed to open hardware. "
			   "Error code %d\n", err);
		जाओ निकास;
	पूर्ण

	err = lx_hardware_start(chip, substream);
	अगर (err < 0) अणु
		dev_err(chip->card->dev, "failed to start hardware. "
			   "Error code %d\n", err);
		जाओ निकास;
	पूर्ण

	chip->hardware_running[is_capture] = 1;

	अगर (chip->board_sample_rate != substream->runसमय->rate) अणु
		अगर (!err)
			chip->board_sample_rate = substream->runसमय->rate;
	पूर्ण

निकास:
	mutex_unlock(&chip->setup_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक lx_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *hw_params, पूर्णांक is_capture)
अणु
	काष्ठा lx6464es *chip = snd_pcm_substream_chip(substream);

	dev_dbg(chip->card->dev, "->lx_pcm_hw_params\n");

	mutex_lock(&chip->setup_mutex);

	अगर (is_capture)
		chip->capture_stream.stream = substream;
	अन्यथा
		chip->playback_stream.stream = substream;

	mutex_unlock(&chip->setup_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक lx_pcm_hw_params_playback(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *hw_params)
अणु
	वापस lx_pcm_hw_params(substream, hw_params, 0);
पूर्ण

अटल पूर्णांक lx_pcm_hw_params_capture(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *hw_params)
अणु
	वापस lx_pcm_hw_params(substream, hw_params, 1);
पूर्ण

अटल पूर्णांक lx_pcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा lx6464es *chip = snd_pcm_substream_chip(substream);
	पूर्णांक err = 0;
	पूर्णांक is_capture = (substream->stream == SNDRV_PCM_STREAM_CAPTURE);

	dev_dbg(chip->card->dev, "->lx_pcm_hw_free\n");
	mutex_lock(&chip->setup_mutex);

	अगर (chip->hardware_running[is_capture]) अणु
		err = lx_hardware_stop(chip, substream);
		अगर (err < 0) अणु
			dev_err(chip->card->dev, "failed to stop hardware. "
				   "Error code %d\n", err);
			जाओ निकास;
		पूर्ण

		err = lx_hardware_बंद(chip, substream);
		अगर (err < 0) अणु
			dev_err(chip->card->dev, "failed to close hardware. "
				   "Error code %d\n", err);
			जाओ निकास;
		पूर्ण

		chip->hardware_running[is_capture] = 0;
	पूर्ण

	अगर (is_capture)
		chip->capture_stream.stream = शून्य;
	अन्यथा
		chip->playback_stream.stream = शून्य;

निकास:
	mutex_unlock(&chip->setup_mutex);
	वापस err;
पूर्ण

अटल व्योम lx_trigger_start(काष्ठा lx6464es *chip, काष्ठा lx_stream *lx_stream)
अणु
	काष्ठा snd_pcm_substream *substream = lx_stream->stream;
	स्थिर अचिन्हित पूर्णांक is_capture = lx_stream->is_capture;

	पूर्णांक err;

	स्थिर u32 channels = substream->runसमय->channels;
	स्थिर u32 bytes_per_frame = channels * 3;
	स्थिर u32 period_size = substream->runसमय->period_size;
	स्थिर u32 periods = substream->runसमय->periods;
	स्थिर u32 period_bytes = period_size * bytes_per_frame;

	dma_addr_t buf = substream->dma_buffer.addr;
	पूर्णांक i;

	u32 needed, मुक्तd;
	u32 size_array[5];

	क्रम (i = 0; i != periods; ++i) अणु
		u32 buffer_index = 0;

		err = lx_buffer_ask(chip, 0, is_capture, &needed, &मुक्तd,
				    size_array);
		dev_dbg(chip->card->dev, "starting: needed %d, freed %d\n",
			    needed, मुक्तd);

		err = lx_buffer_give(chip, 0, is_capture, period_bytes,
				     lower_32_bits(buf), upper_32_bits(buf),
				     &buffer_index);

		dev_dbg(chip->card->dev, "starting: buffer index %x on 0x%lx (%d bytes)\n",
			    buffer_index, (अचिन्हित दीर्घ)buf, period_bytes);
		buf += period_bytes;
	पूर्ण

	err = lx_buffer_ask(chip, 0, is_capture, &needed, &मुक्तd, size_array);
	dev_dbg(chip->card->dev, "starting: needed %d, freed %d\n", needed, मुक्तd);

	dev_dbg(chip->card->dev, "starting: starting stream\n");
	err = lx_stream_start(chip, 0, is_capture);
	अगर (err < 0)
		dev_err(chip->card->dev, "couldn't start stream\n");
	अन्यथा
		lx_stream->status = LX_STREAM_STATUS_RUNNING;

	lx_stream->frame_pos = 0;
पूर्ण

अटल व्योम lx_trigger_stop(काष्ठा lx6464es *chip, काष्ठा lx_stream *lx_stream)
अणु
	स्थिर अचिन्हित पूर्णांक is_capture = lx_stream->is_capture;
	पूर्णांक err;

	dev_dbg(chip->card->dev, "stopping: stopping stream\n");
	err = lx_stream_stop(chip, 0, is_capture);
	अगर (err < 0)
		dev_err(chip->card->dev, "couldn't stop stream\n");
	अन्यथा
		lx_stream->status = LX_STREAM_STATUS_FREE;

पूर्ण

अटल व्योम lx_trigger_dispatch_stream(काष्ठा lx6464es *chip,
				       काष्ठा lx_stream *lx_stream)
अणु
	चयन (lx_stream->status) अणु
	हाल LX_STREAM_STATUS_SCHEDULE_RUN:
		lx_trigger_start(chip, lx_stream);
		अवरोध;

	हाल LX_STREAM_STATUS_SCHEDULE_STOP:
		lx_trigger_stop(chip, lx_stream);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक lx_pcm_trigger_dispatch(काष्ठा lx6464es *chip,
				   काष्ठा lx_stream *lx_stream, पूर्णांक cmd)
अणु
	पूर्णांक err = 0;

	mutex_lock(&chip->lock);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		lx_stream->status = LX_STREAM_STATUS_SCHEDULE_RUN;
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
		lx_stream->status = LX_STREAM_STATUS_SCHEDULE_STOP;
		अवरोध;

	शेष:
		err = -EINVAL;
		जाओ निकास;
	पूर्ण

	lx_trigger_dispatch_stream(chip, &chip->capture_stream);
	lx_trigger_dispatch_stream(chip, &chip->playback_stream);

निकास:
	mutex_unlock(&chip->lock);
	वापस err;
पूर्ण


अटल पूर्णांक lx_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा lx6464es *chip = snd_pcm_substream_chip(substream);
	स्थिर पूर्णांक is_capture = (substream->stream == SNDRV_PCM_STREAM_CAPTURE);
	काष्ठा lx_stream *stream = is_capture ? &chip->capture_stream :
		&chip->playback_stream;

	dev_dbg(chip->card->dev, "->lx_pcm_trigger\n");

	वापस lx_pcm_trigger_dispatch(chip, stream, cmd);
पूर्ण

अटल पूर्णांक snd_lx6464es_मुक्त(काष्ठा lx6464es *chip)
अणु
	dev_dbg(chip->card->dev, "->snd_lx6464es_free\n");

	lx_irq_disable(chip);

	अगर (chip->irq >= 0)
		मुक्त_irq(chip->irq, chip);

	iounmap(chip->port_dsp_bar);
	ioport_unmap(chip->port_plx_remapped);

	pci_release_regions(chip->pci);
	pci_disable_device(chip->pci);

	kमुक्त(chip);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_lx6464es_dev_मुक्त(काष्ठा snd_device *device)
अणु
	वापस snd_lx6464es_मुक्त(device->device_data);
पूर्ण

/* reset the dsp during initialization */
अटल पूर्णांक lx_init_xilinx_reset(काष्ठा lx6464es *chip)
अणु
	पूर्णांक i;
	u32 plx_reg = lx_plx_reg_पढ़ो(chip, ePLX_CHIPSC);

	dev_dbg(chip->card->dev, "->lx_init_xilinx_reset\n");

	/* activate reset of xilinx */
	plx_reg &= ~CHIPSC_RESET_XILINX;

	lx_plx_reg_ग_लिखो(chip, ePLX_CHIPSC, plx_reg);
	msleep(1);

	lx_plx_reg_ग_लिखो(chip, ePLX_MBOX3, 0);
	msleep(1);

	plx_reg |= CHIPSC_RESET_XILINX;
	lx_plx_reg_ग_लिखो(chip, ePLX_CHIPSC, plx_reg);

	/* deactivate reset of xilinx */
	क्रम (i = 0; i != 100; ++i) अणु
		u32 reg_mbox3;
		msleep(10);
		reg_mbox3 = lx_plx_reg_पढ़ो(chip, ePLX_MBOX3);
		अगर (reg_mbox3) अणु
			dev_dbg(chip->card->dev, "xilinx reset done\n");
			dev_dbg(chip->card->dev, "xilinx took %d loops\n", i);
			अवरोध;
		पूर्ण
	पूर्ण

	/* toकरो: add some error handling? */

	/* clear mr */
	lx_dsp_reg_ग_लिखो(chip, eReg_CSM, 0);

	/* le xilinx ES peut ne pas etre encore pret, on attend. */
	msleep(600);

	वापस 0;
पूर्ण

अटल पूर्णांक lx_init_xilinx_test(काष्ठा lx6464es *chip)
अणु
	u32 reg;

	dev_dbg(chip->card->dev, "->lx_init_xilinx_test\n");

	/* TEST अगर we have access to Xilinx/MicroBlaze */
	lx_dsp_reg_ग_लिखो(chip, eReg_CSM, 0);

	reg = lx_dsp_reg_पढ़ो(chip, eReg_CSM);

	अगर (reg) अणु
		dev_err(chip->card->dev, "Problem: Reg_CSM %x.\n", reg);

		/* PCI9056_SPACE0_REMAP */
		lx_plx_reg_ग_लिखो(chip, ePLX_PCICR, 1);

		reg = lx_dsp_reg_पढ़ो(chip, eReg_CSM);
		अगर (reg) अणु
			dev_err(chip->card->dev, "Error: Reg_CSM %x.\n", reg);
			वापस -EAGAIN; /* seems to be appropriate */
		पूर्ण
	पूर्ण

	dev_dbg(chip->card->dev, "Xilinx/MicroBlaze access test successful\n");

	वापस 0;
पूर्ण

/* initialize ethersound */
अटल पूर्णांक lx_init_ethersound_config(काष्ठा lx6464es *chip)
अणु
	पूर्णांक i;
	u32 orig_conf_es = lx_dsp_reg_पढ़ो(chip, eReg_CONFES);

	/* configure 64 io channels */
	u32 conf_es = (orig_conf_es & CONFES_READ_PART_MASK) |
		(64 << IOCR_INPUTS_OFFSET) |
		(64 << IOCR_OUTPUTS_OFFSET) |
		(FREQ_RATIO_SINGLE_MODE << FREQ_RATIO_OFFSET);

	dev_dbg(chip->card->dev, "->lx_init_ethersound\n");

	chip->freq_ratio = FREQ_RATIO_SINGLE_MODE;

	/*
	 * ग_लिखो it to the card !
	 * this actually kicks the ES xilinx, the first समय since घातeron.
	 * the MAC address in the Reg_ADMACESMSB Reg_ADMACESLSB रेजिस्टरs
	 * is not पढ़ोy beक्रमe this is करोne, and the bit 2 in Reg_CSES is set.
	 * */
	lx_dsp_reg_ग_लिखो(chip, eReg_CONFES, conf_es);

	क्रम (i = 0; i != 1000; ++i) अणु
		अगर (lx_dsp_reg_पढ़ो(chip, eReg_CSES) & 4) अणु
			dev_dbg(chip->card->dev, "ethersound initialized after %dms\n",
				   i);
			जाओ ethersound_initialized;
		पूर्ण
		msleep(1);
	पूर्ण
	dev_warn(chip->card->dev,
		   "ethersound could not be initialized after %dms\n", i);
	वापस -ETIMEDOUT;

 ethersound_initialized:
	dev_dbg(chip->card->dev, "ethersound initialized\n");
	वापस 0;
पूर्ण

अटल पूर्णांक lx_init_get_version_features(काष्ठा lx6464es *chip)
अणु
	u32 dsp_version;

	पूर्णांक err;

	dev_dbg(chip->card->dev, "->lx_init_get_version_features\n");

	err = lx_dsp_get_version(chip, &dsp_version);

	अगर (err == 0) अणु
		u32 freq;

		dev_info(chip->card->dev, "DSP version: V%02d.%02d #%d\n",
			   (dsp_version>>16) & 0xff, (dsp_version>>8) & 0xff,
			   dsp_version & 0xff);

		/* later: what firmware version करो we expect? */

		/* retrieve Play/Rec features */
		/* करोne here because we may have to handle alternate
		 * DSP files. */
		/* later */

		/* init the EtherSound sample rate */
		err = lx_dsp_get_घड़ी_frequency(chip, &freq);
		अगर (err == 0)
			chip->board_sample_rate = freq;
		dev_dbg(chip->card->dev, "actual clock frequency %d\n", freq);
	पूर्ण अन्यथा अणु
		dev_err(chip->card->dev, "DSP corrupted \n");
		err = -EAGAIN;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक lx_set_granularity(काष्ठा lx6464es *chip, u32 gran)
अणु
	पूर्णांक err = 0;
	u32 snapped_gran = MICROBLAZE_IBL_MIN;

	dev_dbg(chip->card->dev, "->lx_set_granularity\n");

	/* blocksize is a घातer of 2 */
	जबतक ((snapped_gran < gran) &&
	       (snapped_gran < MICROBLAZE_IBL_MAX)) अणु
		snapped_gran *= 2;
	पूर्ण

	अगर (snapped_gran == chip->pcm_granularity)
		वापस 0;

	err = lx_dsp_set_granularity(chip, snapped_gran);
	अगर (err < 0) अणु
		dev_warn(chip->card->dev, "could not set granularity\n");
		err = -EAGAIN;
	पूर्ण

	अगर (snapped_gran != gran)
		dev_err(chip->card->dev, "snapped blocksize to %d\n", snapped_gran);

	dev_dbg(chip->card->dev, "set blocksize on board %d\n", snapped_gran);
	chip->pcm_granularity = snapped_gran;

	वापस err;
पूर्ण

/* initialize and test the xilinx dsp chip */
अटल पूर्णांक lx_init_dsp(काष्ठा lx6464es *chip)
अणु
	पूर्णांक err;
	पूर्णांक i;

	dev_dbg(chip->card->dev, "->lx_init_dsp\n");

	dev_dbg(chip->card->dev, "initialize board\n");
	err = lx_init_xilinx_reset(chip);
	अगर (err)
		वापस err;

	dev_dbg(chip->card->dev, "testing board\n");
	err = lx_init_xilinx_test(chip);
	अगर (err)
		वापस err;

	dev_dbg(chip->card->dev, "initialize ethersound configuration\n");
	err = lx_init_ethersound_config(chip);
	अगर (err)
		वापस err;

	lx_irq_enable(chip);

	/** \टoकरो the mac address should be पढ़ोy by not, but it isn't,
	 *  so we रुको क्रम it */
	क्रम (i = 0; i != 1000; ++i) अणु
		err = lx_dsp_get_mac(chip);
		अगर (err)
			वापस err;
		अगर (chip->mac_address[0] || chip->mac_address[1] || chip->mac_address[2] ||
		    chip->mac_address[3] || chip->mac_address[4] || chip->mac_address[5])
			जाओ mac_पढ़ोy;
		msleep(1);
	पूर्ण
	वापस -ETIMEDOUT;

mac_पढ़ोy:
	dev_dbg(chip->card->dev, "mac address ready read after: %dms\n", i);
	dev_info(chip->card->dev,
		 "mac address: %02X.%02X.%02X.%02X.%02X.%02X\n",
		   chip->mac_address[0], chip->mac_address[1], chip->mac_address[2],
		   chip->mac_address[3], chip->mac_address[4], chip->mac_address[5]);

	err = lx_init_get_version_features(chip);
	अगर (err)
		वापस err;

	lx_set_granularity(chip, MICROBLAZE_IBL_DEFAULT);

	chip->playback_mute = 0;

	वापस err;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops lx_ops_playback = अणु
	.खोलो      = lx_pcm_खोलो,
	.बंद     = lx_pcm_बंद,
	.prepare   = lx_pcm_prepare,
	.hw_params = lx_pcm_hw_params_playback,
	.hw_मुक्त   = lx_pcm_hw_मुक्त,
	.trigger   = lx_pcm_trigger,
	.poपूर्णांकer   = lx_pcm_stream_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops lx_ops_capture = अणु
	.खोलो      = lx_pcm_खोलो,
	.बंद     = lx_pcm_बंद,
	.prepare   = lx_pcm_prepare,
	.hw_params = lx_pcm_hw_params_capture,
	.hw_मुक्त   = lx_pcm_hw_मुक्त,
	.trigger   = lx_pcm_trigger,
	.poपूर्णांकer   = lx_pcm_stream_poपूर्णांकer,
पूर्ण;

अटल पूर्णांक lx_pcm_create(काष्ठा lx6464es *chip)
अणु
	पूर्णांक err;
	काष्ठा snd_pcm *pcm;

	u32 size = 64 *		     /* channels */
		3 *		     /* 24 bit samples */
		MAX_STREAM_BUFFER *  /* periods */
		MICROBLAZE_IBL_MAX * /* frames per period */
		2;		     /* duplex */

	size = PAGE_ALIGN(size);

	/* hardcoded device name & channel count */
	err = snd_pcm_new(chip->card, (अक्षर *)card_name, 0,
			  1, 1, &pcm);
	अगर (err < 0)
		वापस err;

	pcm->निजी_data = chip;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &lx_ops_playback);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &lx_ops_capture);

	pcm->info_flags = 0;
	pcm->nonatomic = true;
	म_नकल(pcm->name, card_name);

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       &chip->pci->dev, size, size);

	chip->pcm = pcm;
	chip->capture_stream.is_capture = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक lx_control_playback_info(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक lx_control_playback_get(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा lx6464es *chip = snd_kcontrol_chip(kcontrol);
	ucontrol->value.पूर्णांकeger.value[0] = chip->playback_mute;
	वापस 0;
पूर्ण

अटल पूर्णांक lx_control_playback_put(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा lx6464es *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक changed = 0;
	पूर्णांक current_value = chip->playback_mute;

	अगर (current_value != ucontrol->value.पूर्णांकeger.value[0]) अणु
		lx_level_unmute(chip, 0, !current_value);
		chip->playback_mute = !current_value;
		changed = 1;
	पूर्ण
	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new lx_control_playback_चयन = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "PCM Playback Switch",
	.index = 0,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.निजी_value = 0,
	.info = lx_control_playback_info,
	.get = lx_control_playback_get,
	.put = lx_control_playback_put
पूर्ण;



अटल व्योम lx_proc_levels_पढ़ो(काष्ठा snd_info_entry *entry,
				काष्ठा snd_info_buffer *buffer)
अणु
	u32 levels[64];
	पूर्णांक err;
	पूर्णांक i, j;
	काष्ठा lx6464es *chip = entry->निजी_data;

	snd_iम_लिखो(buffer, "capture levels:\n");
	err = lx_level_peaks(chip, 1, 64, levels);
	अगर (err < 0)
		वापस;

	क्रम (i = 0; i != 8; ++i) अणु
		क्रम (j = 0; j != 8; ++j)
			snd_iम_लिखो(buffer, "%08x ", levels[i*8+j]);
		snd_iम_लिखो(buffer, "\n");
	पूर्ण

	snd_iम_लिखो(buffer, "\nplayback levels:\n");

	err = lx_level_peaks(chip, 0, 64, levels);
	अगर (err < 0)
		वापस;

	क्रम (i = 0; i != 8; ++i) अणु
		क्रम (j = 0; j != 8; ++j)
			snd_iम_लिखो(buffer, "%08x ", levels[i*8+j]);
		snd_iम_लिखो(buffer, "\n");
	पूर्ण

	snd_iम_लिखो(buffer, "\n");
पूर्ण

अटल पूर्णांक lx_proc_create(काष्ठा snd_card *card, काष्ठा lx6464es *chip)
अणु
	वापस snd_card_ro_proc_new(card, "levels", chip, lx_proc_levels_पढ़ो);
पूर्ण


अटल पूर्णांक snd_lx6464es_create(काष्ठा snd_card *card,
			       काष्ठा pci_dev *pci,
			       काष्ठा lx6464es **rchip)
अणु
	काष्ठा lx6464es *chip;
	पूर्णांक err;

	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त = snd_lx6464es_dev_मुक्त,
	पूर्ण;

	dev_dbg(card->dev, "->snd_lx6464es_create\n");

	*rchip = शून्य;

	/* enable PCI device */
	err = pci_enable_device(pci);
	अगर (err < 0)
		वापस err;

	pci_set_master(pci);

	/* check अगर we can restrict PCI DMA transfers to 32 bits */
	err = dma_set_mask(&pci->dev, DMA_BIT_MASK(32));
	अगर (err < 0) अणु
		dev_err(card->dev,
			"architecture does not support 32bit PCI busmaster DMA\n");
		pci_disable_device(pci);
		वापस -ENXIO;
	पूर्ण

	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य) अणु
		err = -ENOMEM;
		जाओ alloc_failed;
	पूर्ण

	chip->card = card;
	chip->pci = pci;
	chip->irq = -1;

	/* initialize synchronization काष्ठाs */
	mutex_init(&chip->lock);
	mutex_init(&chip->msg_lock);
	mutex_init(&chip->setup_mutex);

	/* request resources */
	err = pci_request_regions(pci, card_name);
	अगर (err < 0)
		जाओ request_regions_failed;

	/* plx port */
	chip->port_plx = pci_resource_start(pci, 1);
	chip->port_plx_remapped = ioport_map(chip->port_plx,
					     pci_resource_len(pci, 1));

	/* dsp port */
	chip->port_dsp_bar = pci_ioremap_bar(pci, 2);
	अगर (!chip->port_dsp_bar) अणु
		dev_err(card->dev, "cannot remap PCI memory region\n");
		err = -ENOMEM;
		जाओ remap_pci_failed;
	पूर्ण

	err = request_thपढ़ोed_irq(pci->irq, lx_पूर्णांकerrupt, lx_thपढ़ोed_irq,
				   IRQF_SHARED, KBUILD_MODNAME, chip);
	अगर (err) अणु
		dev_err(card->dev, "unable to grab IRQ %d\n", pci->irq);
		जाओ request_irq_failed;
	पूर्ण
	chip->irq = pci->irq;
	card->sync_irq = chip->irq;

	err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops);
	अगर (err < 0)
		जाओ device_new_failed;

	err = lx_init_dsp(chip);
	अगर (err < 0) अणु
		dev_err(card->dev, "error during DSP initialization\n");
		वापस err;
	पूर्ण

	err = lx_pcm_create(chip);
	अगर (err < 0)
		वापस err;

	err = lx_proc_create(card, chip);
	अगर (err < 0)
		वापस err;

	err = snd_ctl_add(card, snd_ctl_new1(&lx_control_playback_चयन,
					     chip));
	अगर (err < 0)
		वापस err;

	*rchip = chip;
	वापस 0;

device_new_failed:
	मुक्त_irq(pci->irq, chip);

request_irq_failed:
	iounmap(chip->port_dsp_bar);

remap_pci_failed:
	pci_release_regions(pci);

request_regions_failed:
	kमुक्त(chip);

alloc_failed:
	pci_disable_device(pci);

	वापस err;
पूर्ण

अटल पूर्णांक snd_lx6464es_probe(काष्ठा pci_dev *pci,
			      स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	काष्ठा lx6464es *chip;
	पूर्णांक err;

	dev_dbg(&pci->dev, "->snd_lx6464es_probe\n");

	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;
	अगर (!enable[dev]) अणु
		dev++;
		वापस -ENOENT;
	पूर्ण

	err = snd_card_new(&pci->dev, index[dev], id[dev], THIS_MODULE,
			   0, &card);
	अगर (err < 0)
		वापस err;

	err = snd_lx6464es_create(card, pci, &chip);
	अगर (err < 0) अणु
		dev_err(card->dev, "error during snd_lx6464es_create\n");
		जाओ out_मुक्त;
	पूर्ण

	म_नकल(card->driver, "LX6464ES");
	प्र_लिखो(card->id, "LX6464ES_%02X%02X%02X",
		chip->mac_address[3], chip->mac_address[4], chip->mac_address[5]);

	प्र_लिखो(card->लघुname, "LX6464ES %02X.%02X.%02X.%02X.%02X.%02X",
		chip->mac_address[0], chip->mac_address[1], chip->mac_address[2],
		chip->mac_address[3], chip->mac_address[4], chip->mac_address[5]);

	प्र_लिखो(card->दीर्घname, "%s at 0x%lx, 0x%p, irq %i",
		card->लघुname, chip->port_plx,
		chip->port_dsp_bar, chip->irq);

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ out_मुक्त;

	dev_dbg(chip->card->dev, "initialization successful\n");
	pci_set_drvdata(pci, card);
	dev++;
	वापस 0;

out_मुक्त:
	snd_card_मुक्त(card);
	वापस err;

पूर्ण

अटल व्योम snd_lx6464es_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण


अटल काष्ठा pci_driver lx6464es_driver = अणु
	.name =     KBUILD_MODNAME,
	.id_table = snd_lx6464es_ids,
	.probe =    snd_lx6464es_probe,
	.हटाओ = snd_lx6464es_हटाओ,
पूर्ण;

module_pci_driver(lx6464es_driver);
