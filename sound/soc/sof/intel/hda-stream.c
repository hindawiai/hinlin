<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
//
// This file is provided under a dual BSD/GPLv2 license.  When using or
// redistributing this file, you may करो so under either license.
//
// Copyright(c) 2018 Intel Corporation. All rights reserved.
//
// Authors: Liam Girdwood <liam.r.girdwood@linux.पूर्णांकel.com>
//	    Ranjani Sridharan <ranjani.sridharan@linux.पूर्णांकel.com>
//	    Rander Wang <अक्रमer.wang@पूर्णांकel.com>
//          Keyon Jie <yang.jie@linux.पूर्णांकel.com>
//

/*
 * Hardware पूर्णांकerface क्रम generic Intel audio DSP HDA IP
 */

#समावेश <linux/pm_runसमय.स>
#समावेश <sound/hdaudio_ext.h>
#समावेश <sound/hda_रेजिस्टर.h>
#समावेश <sound/sof.h>
#समावेश "../ops.h"
#समावेश "../sof-audio.h"
#समावेश "hda.h"

#घोषणा HDA_LTRP_GB_VALUE_US	95

/*
 * set up one of BDL entries क्रम a stream
 */
अटल पूर्णांक hda_setup_bdle(काष्ठा snd_sof_dev *sdev,
			  काष्ठा snd_dma_buffer *dmab,
			  काष्ठा hdac_stream *stream,
			  काष्ठा sof_पूर्णांकel_dsp_bdl **bdlp,
			  पूर्णांक offset, पूर्णांक size, पूर्णांक ioc)
अणु
	काष्ठा hdac_bus *bus = sof_to_bus(sdev);
	काष्ठा sof_पूर्णांकel_dsp_bdl *bdl = *bdlp;

	जबतक (size > 0) अणु
		dma_addr_t addr;
		पूर्णांक chunk;

		अगर (stream->frags >= HDA_DSP_MAX_BDL_ENTRIES) अणु
			dev_err(sdev->dev, "error: stream frags exceeded\n");
			वापस -EINVAL;
		पूर्ण

		addr = snd_sgbuf_get_addr(dmab, offset);
		/* program BDL addr */
		bdl->addr_l = cpu_to_le32(lower_32_bits(addr));
		bdl->addr_h = cpu_to_le32(upper_32_bits(addr));
		/* program BDL size */
		chunk = snd_sgbuf_get_chunk_size(dmab, offset, size);
		/* one BDLE should not cross 4K boundary */
		अगर (bus->align_bdle_4k) अणु
			u32 reमुख्य = 0x1000 - (offset & 0xfff);

			अगर (chunk > reमुख्य)
				chunk = reमुख्य;
		पूर्ण
		bdl->size = cpu_to_le32(chunk);
		/* only program IOC when the whole segment is processed */
		size -= chunk;
		bdl->ioc = (size || !ioc) ? 0 : cpu_to_le32(0x01);
		bdl++;
		stream->frags++;
		offset += chunk;

		dev_vdbg(sdev->dev, "bdl, frags:%d, chunk size:0x%x;\n",
			 stream->frags, chunk);
	पूर्ण

	*bdlp = bdl;
	वापस offset;
पूर्ण

/*
 * set up Buffer Descriptor List (BDL) क्रम host memory transfer
 * BDL describes the location of the inभागidual buffers and is little endian.
 */
पूर्णांक hda_dsp_stream_setup_bdl(काष्ठा snd_sof_dev *sdev,
			     काष्ठा snd_dma_buffer *dmab,
			     काष्ठा hdac_stream *stream)
अणु
	काष्ठा sof_पूर्णांकel_hda_dev *hda = sdev->pdata->hw_pdata;
	काष्ठा sof_पूर्णांकel_dsp_bdl *bdl;
	पूर्णांक i, offset, period_bytes, periods;
	पूर्णांक reमुख्य, ioc;

	period_bytes = stream->period_bytes;
	dev_dbg(sdev->dev, "period_bytes:0x%x\n", period_bytes);
	अगर (!period_bytes)
		period_bytes = stream->bufsize;

	periods = stream->bufsize / period_bytes;

	dev_dbg(sdev->dev, "periods:%d\n", periods);

	reमुख्य = stream->bufsize % period_bytes;
	अगर (reमुख्य)
		periods++;

	/* program the initial BDL entries */
	bdl = (काष्ठा sof_पूर्णांकel_dsp_bdl *)stream->bdl.area;
	offset = 0;
	stream->frags = 0;

	/*
	 * set IOC अगर करोn't use position IPC
	 * and period_wakeup needed.
	 */
	ioc = hda->no_ipc_position ?
	      !stream->no_period_wakeup : 0;

	क्रम (i = 0; i < periods; i++) अणु
		अगर (i == (periods - 1) && reमुख्य)
			/* set the last small entry */
			offset = hda_setup_bdle(sdev, dmab,
						stream, &bdl, offset,
						reमुख्य, 0);
		अन्यथा
			offset = hda_setup_bdle(sdev, dmab,
						stream, &bdl, offset,
						period_bytes, ioc);
	पूर्ण

	वापस offset;
पूर्ण

पूर्णांक hda_dsp_stream_spib_config(काष्ठा snd_sof_dev *sdev,
			       काष्ठा hdac_ext_stream *stream,
			       पूर्णांक enable, u32 size)
अणु
	काष्ठा hdac_stream *hstream = &stream->hstream;
	u32 mask;

	अगर (!sdev->bar[HDA_DSP_SPIB_BAR]) अणु
		dev_err(sdev->dev, "error: address of spib capability is NULL\n");
		वापस -EINVAL;
	पूर्ण

	mask = (1 << hstream->index);

	/* enable/disable SPIB क्रम the stream */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_SPIB_BAR,
				SOF_HDA_ADSP_REG_CL_SPBFIFO_SPBFCCTL, mask,
				enable << hstream->index);

	/* set the SPIB value */
	sof_io_ग_लिखो(sdev, stream->spib_addr, size);

	वापस 0;
पूर्ण

/* get next unused stream */
काष्ठा hdac_ext_stream *
hda_dsp_stream_get(काष्ठा snd_sof_dev *sdev, पूर्णांक direction, u32 flags)
अणु
	काष्ठा hdac_bus *bus = sof_to_bus(sdev);
	काष्ठा sof_पूर्णांकel_hda_stream *hda_stream;
	काष्ठा hdac_ext_stream *stream = शून्य;
	काष्ठा hdac_stream *s;

	spin_lock_irq(&bus->reg_lock);

	/* get an unused stream */
	list_क्रम_each_entry(s, &bus->stream_list, list) अणु
		अगर (s->direction == direction && !s->खोलोed) अणु
			stream = stream_to_hdac_ext_stream(s);
			hda_stream = container_of(stream,
						  काष्ठा sof_पूर्णांकel_hda_stream,
						  hda_stream);
			/* check अगर the host DMA channel is reserved */
			अगर (hda_stream->host_reserved)
				जारी;

			s->खोलोed = true;
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_irq(&bus->reg_lock);

	/* stream found ? */
	अगर (!stream) अणु
		dev_err(sdev->dev, "error: no free %s streams\n",
			direction == SNDRV_PCM_STREAM_PLAYBACK ?
			"playback" : "capture");
		वापस stream;
	पूर्ण

	hda_stream->flags = flags;

	/*
	 * Prevent DMI Link L1 entry क्रम streams that करोn't support it.
	 * Workaround to address a known issue with host DMA that results
	 * in xruns during छोड़ो/release in capture scenarios.
	 */
	अगर (!IS_ENABLED(CONFIG_SND_SOC_SOF_HDA_ALWAYS_ENABLE_DMI_L1))
		अगर (stream && !(flags & SOF_HDA_STREAM_DMI_L1_COMPATIBLE))
			snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR,
						HDA_VS_INTEL_EM2,
						HDA_VS_INTEL_EM2_L1SEN, 0);

	वापस stream;
पूर्ण

/* मुक्त a stream */
पूर्णांक hda_dsp_stream_put(काष्ठा snd_sof_dev *sdev, पूर्णांक direction, पूर्णांक stream_tag)
अणु
	काष्ठा hdac_bus *bus = sof_to_bus(sdev);
	काष्ठा sof_पूर्णांकel_hda_stream *hda_stream;
	काष्ठा hdac_ext_stream *stream;
	काष्ठा hdac_stream *s;
	bool dmi_l1_enable = true;
	bool found = false;

	spin_lock_irq(&bus->reg_lock);

	/*
	 * बंद stream matching the stream tag and check अगर there are any खोलो streams
	 * that are DMI L1 incompatible.
	 */
	list_क्रम_each_entry(s, &bus->stream_list, list) अणु
		stream = stream_to_hdac_ext_stream(s);
		hda_stream = container_of(stream, काष्ठा sof_पूर्णांकel_hda_stream, hda_stream);

		अगर (!s->खोलोed)
			जारी;

		अगर (s->direction == direction && s->stream_tag == stream_tag) अणु
			s->खोलोed = false;
			found = true;
		पूर्ण अन्यथा अगर (!(hda_stream->flags & SOF_HDA_STREAM_DMI_L1_COMPATIBLE)) अणु
			dmi_l1_enable = false;
		पूर्ण
	पूर्ण

	spin_unlock_irq(&bus->reg_lock);

	/* Enable DMI L1 अगर permitted */
	अगर (!IS_ENABLED(CONFIG_SND_SOC_SOF_HDA_ALWAYS_ENABLE_DMI_L1) && dmi_l1_enable)
		snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR, HDA_VS_INTEL_EM2,
					HDA_VS_INTEL_EM2_L1SEN, HDA_VS_INTEL_EM2_L1SEN);

	अगर (!found) अणु
		dev_dbg(sdev->dev, "stream_tag %d not opened!\n", stream_tag);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hda_dsp_stream_trigger(काष्ठा snd_sof_dev *sdev,
			   काष्ठा hdac_ext_stream *stream, पूर्णांक cmd)
अणु
	काष्ठा hdac_stream *hstream = &stream->hstream;
	पूर्णांक sd_offset = SOF_STREAM_SD_OFFSET(hstream);
	u32 dma_start = SOF_HDA_SD_CTL_DMA_START;
	पूर्णांक ret;
	u32 run;

	/* cmd must be क्रम audio stream */
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_START:
		snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR, SOF_HDA_INTCTL,
					1 << hstream->index,
					1 << hstream->index);

		snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR,
					sd_offset,
					SOF_HDA_SD_CTL_DMA_START |
					SOF_HDA_CL_DMA_SD_INT_MASK,
					SOF_HDA_SD_CTL_DMA_START |
					SOF_HDA_CL_DMA_SD_INT_MASK);

		ret = snd_sof_dsp_पढ़ो_poll_समयout(sdev,
					HDA_DSP_HDA_BAR,
					sd_offset, run,
					((run &	dma_start) == dma_start),
					HDA_DSP_REG_POLL_INTERVAL_US,
					HDA_DSP_STREAM_RUN_TIMEOUT);

		अगर (ret < 0) अणु
			dev_err(sdev->dev,
				"error: %s: cmd %d: timeout on STREAM_SD_OFFSET read\n",
				__func__, cmd);
			वापस ret;
		पूर्ण

		hstream->running = true;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_STOP:
		snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR,
					sd_offset,
					SOF_HDA_SD_CTL_DMA_START |
					SOF_HDA_CL_DMA_SD_INT_MASK, 0x0);

		ret = snd_sof_dsp_पढ़ो_poll_समयout(sdev, HDA_DSP_HDA_BAR,
						sd_offset, run,
						!(run &	dma_start),
						HDA_DSP_REG_POLL_INTERVAL_US,
						HDA_DSP_STREAM_RUN_TIMEOUT);

		अगर (ret < 0) अणु
			dev_err(sdev->dev,
				"error: %s: cmd %d: timeout on STREAM_SD_OFFSET read\n",
				__func__, cmd);
			वापस ret;
		पूर्ण

		snd_sof_dsp_ग_लिखो(sdev, HDA_DSP_HDA_BAR, sd_offset +
				  SOF_HDA_ADSP_REG_CL_SD_STS,
				  SOF_HDA_CL_DMA_SD_INT_MASK);

		hstream->running = false;
		snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR, SOF_HDA_INTCTL,
					1 << hstream->index, 0x0);
		अवरोध;
	शेष:
		dev_err(sdev->dev, "error: unknown command: %d\n", cmd);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* minimal recommended programming क्रम ICCMAX stream */
पूर्णांक hda_dsp_iccmax_stream_hw_params(काष्ठा snd_sof_dev *sdev, काष्ठा hdac_ext_stream *stream,
				    काष्ठा snd_dma_buffer *dmab,
				    काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा hdac_bus *bus = sof_to_bus(sdev);
	काष्ठा hdac_stream *hstream = &stream->hstream;
	पूर्णांक sd_offset = SOF_STREAM_SD_OFFSET(hstream);
	पूर्णांक ret;
	u32 mask = 0x1 << hstream->index;

	अगर (!stream) अणु
		dev_err(sdev->dev, "error: no stream available\n");
		वापस -ENODEV;
	पूर्ण

	अगर (hstream->posbuf)
		*hstream->posbuf = 0;

	/* reset BDL address */
	snd_sof_dsp_ग_लिखो(sdev, HDA_DSP_HDA_BAR,
			  sd_offset + SOF_HDA_ADSP_REG_CL_SD_BDLPL,
			  0x0);
	snd_sof_dsp_ग_लिखो(sdev, HDA_DSP_HDA_BAR,
			  sd_offset + SOF_HDA_ADSP_REG_CL_SD_BDLPU,
			  0x0);

	hstream->frags = 0;

	ret = hda_dsp_stream_setup_bdl(sdev, dmab, hstream);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: set up of BDL failed\n");
		वापस ret;
	पूर्ण

	/* program BDL address */
	snd_sof_dsp_ग_लिखो(sdev, HDA_DSP_HDA_BAR,
			  sd_offset + SOF_HDA_ADSP_REG_CL_SD_BDLPL,
			  (u32)hstream->bdl.addr);
	snd_sof_dsp_ग_लिखो(sdev, HDA_DSP_HDA_BAR,
			  sd_offset + SOF_HDA_ADSP_REG_CL_SD_BDLPU,
			  upper_32_bits(hstream->bdl.addr));

	/* program cyclic buffer length */
	snd_sof_dsp_ग_लिखो(sdev, HDA_DSP_HDA_BAR,
			  sd_offset + SOF_HDA_ADSP_REG_CL_SD_CBL,
			  hstream->bufsize);

	/* program last valid index */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR,
				sd_offset + SOF_HDA_ADSP_REG_CL_SD_LVI,
				0xffff, (hstream->frags - 1));

	/* decouple host and link DMA, enable DSP features */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_PP_BAR, SOF_HDA_REG_PP_PPCTL,
				mask, mask);

	/* Follow HW recommendation to set the guardband value to 95us during FW boot */
	snd_hdac_chip_updateb(bus, VS_LTRP, HDA_VS_INTEL_LTRP_GB_MASK, HDA_LTRP_GB_VALUE_US);

	/* start DMA */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR, sd_offset,
				SOF_HDA_SD_CTL_DMA_START, SOF_HDA_SD_CTL_DMA_START);

	वापस 0;
पूर्ण

/*
 * prepare क्रम common hdac रेजिस्टरs settings, क्रम both code loader
 * and normal stream.
 */
पूर्णांक hda_dsp_stream_hw_params(काष्ठा snd_sof_dev *sdev,
			     काष्ठा hdac_ext_stream *stream,
			     काष्ठा snd_dma_buffer *dmab,
			     काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा hdac_bus *bus = sof_to_bus(sdev);
	काष्ठा hdac_stream *hstream = &stream->hstream;
	पूर्णांक sd_offset = SOF_STREAM_SD_OFFSET(hstream);
	पूर्णांक ret, समयout = HDA_DSP_STREAM_RESET_TIMEOUT;
	u32 dma_start = SOF_HDA_SD_CTL_DMA_START;
	u32 val, mask;
	u32 run;

	अगर (!stream) अणु
		dev_err(sdev->dev, "error: no stream available\n");
		वापस -ENODEV;
	पूर्ण

	/* decouple host and link DMA */
	mask = 0x1 << hstream->index;
	snd_sof_dsp_update_bits(sdev, HDA_DSP_PP_BAR, SOF_HDA_REG_PP_PPCTL,
				mask, mask);

	अगर (!dmab) अणु
		dev_err(sdev->dev, "error: no dma buffer allocated!\n");
		वापस -ENODEV;
	पूर्ण

	/* clear stream status */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR, sd_offset,
				SOF_HDA_CL_DMA_SD_INT_MASK |
				SOF_HDA_SD_CTL_DMA_START, 0);

	ret = snd_sof_dsp_पढ़ो_poll_समयout(sdev, HDA_DSP_HDA_BAR,
					    sd_offset, run,
					    !(run & dma_start),
					    HDA_DSP_REG_POLL_INTERVAL_US,
					    HDA_DSP_STREAM_RUN_TIMEOUT);

	अगर (ret < 0) अणु
		dev_err(sdev->dev,
			"error: %s: timeout on STREAM_SD_OFFSET read1\n",
			__func__);
		वापस ret;
	पूर्ण

	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR,
				sd_offset + SOF_HDA_ADSP_REG_CL_SD_STS,
				SOF_HDA_CL_DMA_SD_INT_MASK,
				SOF_HDA_CL_DMA_SD_INT_MASK);

	/* stream reset */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR, sd_offset, 0x1,
				0x1);
	udelay(3);
	करो अणु
		val = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_HDA_BAR,
				       sd_offset);
		अगर (val & 0x1)
			अवरोध;
	पूर्ण जबतक (--समयout);
	अगर (समयout == 0) अणु
		dev_err(sdev->dev, "error: stream reset failed\n");
		वापस -ETIMEDOUT;
	पूर्ण

	समयout = HDA_DSP_STREAM_RESET_TIMEOUT;
	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR, sd_offset, 0x1,
				0x0);

	/* रुको क्रम hardware to report that stream is out of reset */
	udelay(3);
	करो अणु
		val = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_HDA_BAR,
				       sd_offset);
		अगर ((val & 0x1) == 0)
			अवरोध;
	पूर्ण जबतक (--समयout);
	अगर (समयout == 0) अणु
		dev_err(sdev->dev, "error: timeout waiting for stream reset\n");
		वापस -ETIMEDOUT;
	पूर्ण

	अगर (hstream->posbuf)
		*hstream->posbuf = 0;

	/* reset BDL address */
	snd_sof_dsp_ग_लिखो(sdev, HDA_DSP_HDA_BAR,
			  sd_offset + SOF_HDA_ADSP_REG_CL_SD_BDLPL,
			  0x0);
	snd_sof_dsp_ग_लिखो(sdev, HDA_DSP_HDA_BAR,
			  sd_offset + SOF_HDA_ADSP_REG_CL_SD_BDLPU,
			  0x0);

	/* clear stream status */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR, sd_offset,
				SOF_HDA_CL_DMA_SD_INT_MASK |
				SOF_HDA_SD_CTL_DMA_START, 0);

	ret = snd_sof_dsp_पढ़ो_poll_समयout(sdev, HDA_DSP_HDA_BAR,
					    sd_offset, run,
					    !(run & dma_start),
					    HDA_DSP_REG_POLL_INTERVAL_US,
					    HDA_DSP_STREAM_RUN_TIMEOUT);

	अगर (ret < 0) अणु
		dev_err(sdev->dev,
			"error: %s: timeout on STREAM_SD_OFFSET read2\n",
			__func__);
		वापस ret;
	पूर्ण

	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR,
				sd_offset + SOF_HDA_ADSP_REG_CL_SD_STS,
				SOF_HDA_CL_DMA_SD_INT_MASK,
				SOF_HDA_CL_DMA_SD_INT_MASK);

	hstream->frags = 0;

	ret = hda_dsp_stream_setup_bdl(sdev, dmab, hstream);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: set up of BDL failed\n");
		वापस ret;
	पूर्ण

	/* program stream tag to set up stream descriptor क्रम DMA */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR, sd_offset,
				SOF_HDA_CL_SD_CTL_STREAM_TAG_MASK,
				hstream->stream_tag <<
				SOF_HDA_CL_SD_CTL_STREAM_TAG_SHIFT);

	/* program cyclic buffer length */
	snd_sof_dsp_ग_लिखो(sdev, HDA_DSP_HDA_BAR,
			  sd_offset + SOF_HDA_ADSP_REG_CL_SD_CBL,
			  hstream->bufsize);

	/*
	 * Recommended hardware programming sequence क्रम HDAudio DMA क्रमmat
	 *
	 * 1. Put DMA पूर्णांकo coupled mode by clearing PPCTL.PROCEN bit
	 *    क्रम corresponding stream index beक्रमe the समय of writing
	 *    क्रमmat to SDxFMT रेजिस्टर.
	 * 2. Write SDxFMT
	 * 3. Set PPCTL.PROCEN bit क्रम corresponding stream index to
	 *    enable decoupled mode
	 */

	/* couple host and link DMA, disable DSP features */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_PP_BAR, SOF_HDA_REG_PP_PPCTL,
				mask, 0);

	/* program stream क्रमmat */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR,
				sd_offset +
				SOF_HDA_ADSP_REG_CL_SD_FORMAT,
				0xffff, hstream->क्रमmat_val);

	/* decouple host and link DMA, enable DSP features */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_PP_BAR, SOF_HDA_REG_PP_PPCTL,
				mask, mask);

	/* program last valid index */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR,
				sd_offset + SOF_HDA_ADSP_REG_CL_SD_LVI,
				0xffff, (hstream->frags - 1));

	/* program BDL address */
	snd_sof_dsp_ग_लिखो(sdev, HDA_DSP_HDA_BAR,
			  sd_offset + SOF_HDA_ADSP_REG_CL_SD_BDLPL,
			  (u32)hstream->bdl.addr);
	snd_sof_dsp_ग_लिखो(sdev, HDA_DSP_HDA_BAR,
			  sd_offset + SOF_HDA_ADSP_REG_CL_SD_BDLPU,
			  upper_32_bits(hstream->bdl.addr));

	/* enable position buffer */
	अगर (!(snd_sof_dsp_पढ़ो(sdev, HDA_DSP_HDA_BAR, SOF_HDA_ADSP_DPLBASE)
				& SOF_HDA_ADSP_DPLBASE_ENABLE)) अणु
		snd_sof_dsp_ग_लिखो(sdev, HDA_DSP_HDA_BAR, SOF_HDA_ADSP_DPUBASE,
				  upper_32_bits(bus->posbuf.addr));
		snd_sof_dsp_ग_लिखो(sdev, HDA_DSP_HDA_BAR, SOF_HDA_ADSP_DPLBASE,
				  (u32)bus->posbuf.addr |
				  SOF_HDA_ADSP_DPLBASE_ENABLE);
	पूर्ण

	/* set पूर्णांकerrupt enable bits */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR, sd_offset,
				SOF_HDA_CL_DMA_SD_INT_MASK,
				SOF_HDA_CL_DMA_SD_INT_MASK);

	/* पढ़ो FIFO size */
	अगर (hstream->direction == SNDRV_PCM_STREAM_PLAYBACK) अणु
		hstream->fअगरo_size =
			snd_sof_dsp_पढ़ो(sdev, HDA_DSP_HDA_BAR,
					 sd_offset +
					 SOF_HDA_ADSP_REG_CL_SD_FIFOSIZE);
		hstream->fअगरo_size &= 0xffff;
		hstream->fअगरo_size += 1;
	पूर्ण अन्यथा अणु
		hstream->fअगरo_size = 0;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक hda_dsp_stream_hw_मुक्त(काष्ठा snd_sof_dev *sdev,
			   काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hdac_stream *stream = substream->runसमय->निजी_data;
	काष्ठा hdac_ext_stream *link_dev = container_of(stream,
							काष्ठा hdac_ext_stream,
							hstream);
	काष्ठा hdac_bus *bus = sof_to_bus(sdev);
	u32 mask = 0x1 << stream->index;

	spin_lock_irq(&bus->reg_lock);
	/* couple host and link DMA अगर link DMA channel is idle */
	अगर (!link_dev->link_locked)
		snd_sof_dsp_update_bits(sdev, HDA_DSP_PP_BAR,
					SOF_HDA_REG_PP_PPCTL, mask, 0);
	spin_unlock_irq(&bus->reg_lock);

	stream->substream = शून्य;

	वापस 0;
पूर्ण

bool hda_dsp_check_stream_irq(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा hdac_bus *bus = sof_to_bus(sdev);
	bool ret = false;
	u32 status;

	/* The function can be called at irq thपढ़ो, so use spin_lock_irq */
	spin_lock_irq(&bus->reg_lock);

	status = snd_hdac_chip_पढ़ोl(bus, INTSTS);
	dev_vdbg(bus->dev, "stream irq, INTSTS status: 0x%x\n", status);

	/* अगर Register inaccessible, ignore it.*/
	अगर (status != 0xffffffff)
		ret = true;

	spin_unlock_irq(&bus->reg_lock);

	वापस ret;
पूर्ण

अटल व्योम
hda_dsp_set_bytes_transferred(काष्ठा hdac_stream *hstream, u64 buffer_size)
अणु
	u64 prev_pos, pos, num_bytes;

	भाग64_u64_rem(hstream->curr_pos, buffer_size, &prev_pos);
	pos = snd_hdac_stream_get_pos_posbuf(hstream);

	अगर (pos < prev_pos)
		num_bytes = (buffer_size - prev_pos) +  pos;
	अन्यथा
		num_bytes = pos - prev_pos;

	hstream->curr_pos += num_bytes;
पूर्ण

अटल bool hda_dsp_stream_check(काष्ठा hdac_bus *bus, u32 status)
अणु
	काष्ठा sof_पूर्णांकel_hda_dev *sof_hda = bus_to_sof_hda(bus);
	काष्ठा hdac_stream *s;
	bool active = false;
	u32 sd_status;

	list_क्रम_each_entry(s, &bus->stream_list, list) अणु
		अगर (status & BIT(s->index) && s->खोलोed) अणु
			sd_status = snd_hdac_stream_पढ़ोb(s, SD_STS);

			dev_vdbg(bus->dev, "stream %d status 0x%x\n",
				 s->index, sd_status);

			snd_hdac_stream_ग_लिखोb(s, SD_STS, sd_status);

			active = true;
			अगर ((!s->substream && !s->cstream) ||
			    !s->running ||
			    (sd_status & SOF_HDA_CL_DMA_SD_INT_COMPLETE) == 0)
				जारी;

			/* Inक्रमm ALSA only in हाल not करो that with IPC */
			अगर (s->substream && sof_hda->no_ipc_position) अणु
				snd_sof_pcm_period_elapsed(s->substream);
			पूर्ण अन्यथा अगर (s->cstream) अणु
				hda_dsp_set_bytes_transferred(s,
					s->cstream->runसमय->buffer_size);
				snd_compr_fragment_elapsed(s->cstream);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस active;
पूर्ण

irqवापस_t hda_dsp_stream_thपढ़ोed_handler(पूर्णांक irq, व्योम *context)
अणु
	काष्ठा snd_sof_dev *sdev = context;
	काष्ठा hdac_bus *bus = sof_to_bus(sdev);
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
	u32 rirb_status;
#पूर्ण_अगर
	bool active;
	u32 status;
	पूर्णांक i;

	/*
	 * Loop 10 बार to handle missed पूर्णांकerrupts caused by
	 * unsolicited responses from the codec
	 */
	क्रम (i = 0, active = true; i < 10 && active; i++) अणु
		spin_lock_irq(&bus->reg_lock);

		status = snd_hdac_chip_पढ़ोl(bus, INTSTS);

		/* check streams */
		active = hda_dsp_stream_check(bus, status);

		/* check and clear RIRB पूर्णांकerrupt */
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
		अगर (status & AZX_INT_CTRL_EN) अणु
			rirb_status = snd_hdac_chip_पढ़ोb(bus, RIRBSTS);
			अगर (rirb_status & RIRB_INT_MASK) अणु
				/*
				 * Clearing the पूर्णांकerrupt status here ensures
				 * that no पूर्णांकerrupt माला_लो masked after the RIRB
				 * wp is पढ़ो in snd_hdac_bus_update_rirb.
				 */
				snd_hdac_chip_ग_लिखोb(bus, RIRBSTS,
						     RIRB_INT_MASK);
				active = true;
				अगर (rirb_status & RIRB_INT_RESPONSE)
					snd_hdac_bus_update_rirb(bus);
			पूर्ण
		पूर्ण
#पूर्ण_अगर
		spin_unlock_irq(&bus->reg_lock);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक hda_dsp_stream_init(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा hdac_bus *bus = sof_to_bus(sdev);
	काष्ठा hdac_ext_stream *stream;
	काष्ठा hdac_stream *hstream;
	काष्ठा pci_dev *pci = to_pci_dev(sdev->dev);
	काष्ठा sof_पूर्णांकel_hda_dev *sof_hda = bus_to_sof_hda(bus);
	पूर्णांक sd_offset;
	पूर्णांक i, num_playback, num_capture, num_total, ret;
	u32 gcap;

	gcap = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_HDA_BAR, SOF_HDA_GCAP);
	dev_dbg(sdev->dev, "hda global caps = 0x%x\n", gcap);

	/* get stream count from GCAP */
	num_capture = (gcap >> 8) & 0x0f;
	num_playback = (gcap >> 12) & 0x0f;
	num_total = num_playback + num_capture;

	dev_dbg(sdev->dev, "detected %d playback and %d capture streams\n",
		num_playback, num_capture);

	अगर (num_playback >= SOF_HDA_PLAYBACK_STREAMS) अणु
		dev_err(sdev->dev, "error: too many playback streams %d\n",
			num_playback);
		वापस -EINVAL;
	पूर्ण

	अगर (num_capture >= SOF_HDA_CAPTURE_STREAMS) अणु
		dev_err(sdev->dev, "error: too many capture streams %d\n",
			num_playback);
		वापस -EINVAL;
	पूर्ण

	/*
	 * mem alloc क्रम the position buffer
	 * TODO: check position buffer update
	 */
	ret = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, &pci->dev,
				  SOF_HDA_DPIB_ENTRY_SIZE * num_total,
				  &bus->posbuf);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: posbuffer dma alloc failed\n");
		वापस -ENOMEM;
	पूर्ण

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
	/* mem alloc क्रम the CORB/RIRB ringbuffers */
	ret = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, &pci->dev,
				  PAGE_SIZE, &bus->rb);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: RB alloc failed\n");
		वापस -ENOMEM;
	पूर्ण
#पूर्ण_अगर

	/* create capture streams */
	क्रम (i = 0; i < num_capture; i++) अणु
		काष्ठा sof_पूर्णांकel_hda_stream *hda_stream;

		hda_stream = devm_kzalloc(sdev->dev, माप(*hda_stream),
					  GFP_KERNEL);
		अगर (!hda_stream)
			वापस -ENOMEM;

		hda_stream->sdev = sdev;

		stream = &hda_stream->hda_stream;

		stream->pphc_addr = sdev->bar[HDA_DSP_PP_BAR] +
			SOF_HDA_PPHC_BASE + SOF_HDA_PPHC_INTERVAL * i;

		stream->pplc_addr = sdev->bar[HDA_DSP_PP_BAR] +
			SOF_HDA_PPLC_BASE + SOF_HDA_PPLC_MULTI * num_total +
			SOF_HDA_PPLC_INTERVAL * i;

		/* करो we support SPIB */
		अगर (sdev->bar[HDA_DSP_SPIB_BAR]) अणु
			stream->spib_addr = sdev->bar[HDA_DSP_SPIB_BAR] +
				SOF_HDA_SPIB_BASE + SOF_HDA_SPIB_INTERVAL * i +
				SOF_HDA_SPIB_SPIB;

			stream->fअगरo_addr = sdev->bar[HDA_DSP_SPIB_BAR] +
				SOF_HDA_SPIB_BASE + SOF_HDA_SPIB_INTERVAL * i +
				SOF_HDA_SPIB_MAXFIFO;
		पूर्ण

		hstream = &stream->hstream;
		hstream->bus = bus;
		hstream->sd_पूर्णांक_sta_mask = 1 << i;
		hstream->index = i;
		sd_offset = SOF_STREAM_SD_OFFSET(hstream);
		hstream->sd_addr = sdev->bar[HDA_DSP_HDA_BAR] + sd_offset;
		hstream->stream_tag = i + 1;
		hstream->खोलोed = false;
		hstream->running = false;
		hstream->direction = SNDRV_PCM_STREAM_CAPTURE;

		/* memory alloc क्रम stream BDL */
		ret = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, &pci->dev,
					  HDA_DSP_BDL_SIZE, &hstream->bdl);
		अगर (ret < 0) अणु
			dev_err(sdev->dev, "error: stream bdl dma alloc failed\n");
			वापस -ENOMEM;
		पूर्ण
		hstream->posbuf = (__le32 *)(bus->posbuf.area +
			(hstream->index) * 8);

		list_add_tail(&hstream->list, &bus->stream_list);
	पूर्ण

	/* create playback streams */
	क्रम (i = num_capture; i < num_total; i++) अणु
		काष्ठा sof_पूर्णांकel_hda_stream *hda_stream;

		hda_stream = devm_kzalloc(sdev->dev, माप(*hda_stream),
					  GFP_KERNEL);
		अगर (!hda_stream)
			वापस -ENOMEM;

		hda_stream->sdev = sdev;

		stream = &hda_stream->hda_stream;

		/* we always have DSP support */
		stream->pphc_addr = sdev->bar[HDA_DSP_PP_BAR] +
			SOF_HDA_PPHC_BASE + SOF_HDA_PPHC_INTERVAL * i;

		stream->pplc_addr = sdev->bar[HDA_DSP_PP_BAR] +
			SOF_HDA_PPLC_BASE + SOF_HDA_PPLC_MULTI * num_total +
			SOF_HDA_PPLC_INTERVAL * i;

		/* करो we support SPIB */
		अगर (sdev->bar[HDA_DSP_SPIB_BAR]) अणु
			stream->spib_addr = sdev->bar[HDA_DSP_SPIB_BAR] +
				SOF_HDA_SPIB_BASE + SOF_HDA_SPIB_INTERVAL * i +
				SOF_HDA_SPIB_SPIB;

			stream->fअगरo_addr = sdev->bar[HDA_DSP_SPIB_BAR] +
				SOF_HDA_SPIB_BASE + SOF_HDA_SPIB_INTERVAL * i +
				SOF_HDA_SPIB_MAXFIFO;
		पूर्ण

		hstream = &stream->hstream;
		hstream->bus = bus;
		hstream->sd_पूर्णांक_sta_mask = 1 << i;
		hstream->index = i;
		sd_offset = SOF_STREAM_SD_OFFSET(hstream);
		hstream->sd_addr = sdev->bar[HDA_DSP_HDA_BAR] + sd_offset;
		hstream->stream_tag = i - num_capture + 1;
		hstream->खोलोed = false;
		hstream->running = false;
		hstream->direction = SNDRV_PCM_STREAM_PLAYBACK;

		/* mem alloc क्रम stream BDL */
		ret = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, &pci->dev,
					  HDA_DSP_BDL_SIZE, &hstream->bdl);
		अगर (ret < 0) अणु
			dev_err(sdev->dev, "error: stream bdl dma alloc failed\n");
			वापस -ENOMEM;
		पूर्ण

		hstream->posbuf = (__le32 *)(bus->posbuf.area +
			(hstream->index) * 8);

		list_add_tail(&hstream->list, &bus->stream_list);
	पूर्ण

	/* store total stream count (playback + capture) from GCAP */
	sof_hda->stream_max = num_total;

	वापस 0;
पूर्ण

व्योम hda_dsp_stream_मुक्त(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा hdac_bus *bus = sof_to_bus(sdev);
	काष्ठा hdac_stream *s, *_s;
	काष्ठा hdac_ext_stream *stream;
	काष्ठा sof_पूर्णांकel_hda_stream *hda_stream;

	/* मुक्त position buffer */
	अगर (bus->posbuf.area)
		snd_dma_मुक्त_pages(&bus->posbuf);

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
	/* मुक्त position buffer */
	अगर (bus->rb.area)
		snd_dma_मुक्त_pages(&bus->rb);
#पूर्ण_अगर

	list_क्रम_each_entry_safe(s, _s, &bus->stream_list, list) अणु
		/* TODO: decouple */

		/* मुक्त bdl buffer */
		अगर (s->bdl.area)
			snd_dma_मुक्त_pages(&s->bdl);
		list_del(&s->list);
		stream = stream_to_hdac_ext_stream(s);
		hda_stream = container_of(stream, काष्ठा sof_पूर्णांकel_hda_stream,
					  hda_stream);
		devm_kमुक्त(sdev->dev, hda_stream);
	पूर्ण
पूर्ण
