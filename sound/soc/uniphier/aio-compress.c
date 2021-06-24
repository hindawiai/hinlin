<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Socionext UniPhier AIO Compress Audio driver.
//
// Copyright (c) 2017-2018 Socionext Inc.

#समावेश <linux/bitfield.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>

#समावेश "aio.h"

अटल पूर्णांक uniphier_aio_compr_prepare(काष्ठा snd_soc_component *component,
				      काष्ठा snd_compr_stream *cstream);
अटल पूर्णांक uniphier_aio_compr_hw_मुक्त(काष्ठा snd_soc_component *component,
				      काष्ठा snd_compr_stream *cstream);

अटल पूर्णांक uniphier_aio_comprdma_new(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_compr *compr = rtd->compr;
	काष्ठा device *dev = compr->card->dev;
	काष्ठा uniphier_aio *aio = uniphier_priv(asoc_rtd_to_cpu(rtd, 0));
	काष्ठा uniphier_aio_sub *sub = &aio->sub[compr->direction];
	माप_प्रकार size = AUD_RING_SIZE;
	पूर्णांक dma_dir = DMA_FROM_DEVICE, ret;

	ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(33));
	अगर (ret)
		वापस ret;

	sub->compr_area = kzalloc(size, GFP_KERNEL);
	अगर (!sub->compr_area)
		वापस -ENOMEM;

	अगर (sub->swm->dir == PORT_सूची_OUTPUT)
		dma_dir = DMA_TO_DEVICE;

	sub->compr_addr = dma_map_single(dev, sub->compr_area, size, dma_dir);
	अगर (dma_mapping_error(dev, sub->compr_addr)) अणु
		kमुक्त(sub->compr_area);
		sub->compr_area = शून्य;

		वापस -ENOMEM;
	पूर्ण

	sub->compr_bytes = size;

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_aio_comprdma_मुक्त(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_compr *compr = rtd->compr;
	काष्ठा device *dev = compr->card->dev;
	काष्ठा uniphier_aio *aio = uniphier_priv(asoc_rtd_to_cpu(rtd, 0));
	काष्ठा uniphier_aio_sub *sub = &aio->sub[compr->direction];
	पूर्णांक dma_dir = DMA_FROM_DEVICE;

	अगर (sub->swm->dir == PORT_सूची_OUTPUT)
		dma_dir = DMA_TO_DEVICE;

	dma_unmap_single(dev, sub->compr_addr, sub->compr_bytes, dma_dir);
	kमुक्त(sub->compr_area);
	sub->compr_area = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_aio_compr_खोलो(काष्ठा snd_soc_component *component,
				   काष्ठा snd_compr_stream *cstream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	काष्ठा uniphier_aio *aio = uniphier_priv(asoc_rtd_to_cpu(rtd, 0));
	काष्ठा uniphier_aio_sub *sub = &aio->sub[cstream->direction];
	पूर्णांक ret;

	अगर (sub->cstream)
		वापस -EBUSY;

	sub->cstream = cstream;
	sub->pass_through = 1;
	sub->use_mmap = false;

	ret = uniphier_aio_comprdma_new(rtd);
	अगर (ret)
		वापस ret;

	ret = aio_init(sub);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_aio_compr_मुक्त(काष्ठा snd_soc_component *component,
				   काष्ठा snd_compr_stream *cstream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	काष्ठा uniphier_aio *aio = uniphier_priv(asoc_rtd_to_cpu(rtd, 0));
	काष्ठा uniphier_aio_sub *sub = &aio->sub[cstream->direction];
	पूर्णांक ret;

	ret = uniphier_aio_compr_hw_मुक्त(component, cstream);
	अगर (ret)
		वापस ret;
	ret = uniphier_aio_comprdma_मुक्त(rtd);
	अगर (ret)
		वापस ret;

	sub->cstream = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_aio_compr_get_params(काष्ठा snd_soc_component *component,
					 काष्ठा snd_compr_stream *cstream,
					 काष्ठा snd_codec *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	काष्ठा uniphier_aio *aio = uniphier_priv(asoc_rtd_to_cpu(rtd, 0));
	काष्ठा uniphier_aio_sub *sub = &aio->sub[cstream->direction];

	*params = sub->cparams.codec;

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_aio_compr_set_params(काष्ठा snd_soc_component *component,
					 काष्ठा snd_compr_stream *cstream,
					 काष्ठा snd_compr_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	काष्ठा uniphier_aio *aio = uniphier_priv(asoc_rtd_to_cpu(rtd, 0));
	काष्ठा uniphier_aio_sub *sub = &aio->sub[cstream->direction];
	काष्ठा device *dev = &aio->chip->pdev->dev;
	पूर्णांक ret;

	अगर (params->codec.id != SND_AUDIOCODEC_IEC61937) अणु
		dev_err(dev, "Codec ID is not supported(%d)\n",
			params->codec.id);
		वापस -EINVAL;
	पूर्ण
	अगर (params->codec.profile != SND_AUDIOPROखाता_IEC61937_SPDIF) अणु
		dev_err(dev, "Codec profile is not supported(%d)\n",
			params->codec.profile);
		वापस -EINVAL;
	पूर्ण

	/* IEC frame type will be changed after received valid data */
	sub->iec_pc = IEC61937_PC_AAC;

	sub->cparams = *params;
	sub->setting = 1;

	aio_port_reset(sub);
	aio_src_reset(sub);

	ret = uniphier_aio_compr_prepare(component, cstream);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_aio_compr_hw_मुक्त(काष्ठा snd_soc_component *component,
				      काष्ठा snd_compr_stream *cstream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	काष्ठा uniphier_aio *aio = uniphier_priv(asoc_rtd_to_cpu(rtd, 0));
	काष्ठा uniphier_aio_sub *sub = &aio->sub[cstream->direction];

	sub->setting = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_aio_compr_prepare(काष्ठा snd_soc_component *component,
				      काष्ठा snd_compr_stream *cstream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	काष्ठा snd_compr_runसमय *runसमय = cstream->runसमय;
	काष्ठा uniphier_aio *aio = uniphier_priv(asoc_rtd_to_cpu(rtd, 0));
	काष्ठा uniphier_aio_sub *sub = &aio->sub[cstream->direction];
	पूर्णांक bytes = runसमय->fragment_size;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ret = aiodma_ch_set_param(sub);
	अगर (ret)
		वापस ret;

	spin_lock_irqsave(&sub->lock, flags);
	ret = aiodma_rb_set_buffer(sub, sub->compr_addr,
				   sub->compr_addr + sub->compr_bytes,
				   bytes);
	spin_unlock_irqrestore(&sub->lock, flags);
	अगर (ret)
		वापस ret;

	ret = aio_port_set_param(sub, sub->pass_through, &sub->params);
	अगर (ret)
		वापस ret;
	ret = aio_oport_set_stream_type(sub, sub->iec_pc);
	अगर (ret)
		वापस ret;
	aio_port_set_enable(sub, 1);

	ret = aio_अगर_set_param(sub, sub->pass_through);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_aio_compr_trigger(काष्ठा snd_soc_component *component,
				      काष्ठा snd_compr_stream *cstream,
				      पूर्णांक cmd)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	काष्ठा snd_compr_runसमय *runसमय = cstream->runसमय;
	काष्ठा uniphier_aio *aio = uniphier_priv(asoc_rtd_to_cpu(rtd, 0));
	काष्ठा uniphier_aio_sub *sub = &aio->sub[cstream->direction];
	काष्ठा device *dev = &aio->chip->pdev->dev;
	पूर्णांक bytes = runसमय->fragment_size, ret = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sub->lock, flags);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		aiodma_rb_sync(sub, sub->compr_addr, sub->compr_bytes, bytes);
		aiodma_ch_set_enable(sub, 1);
		sub->running = 1;

		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		sub->running = 0;
		aiodma_ch_set_enable(sub, 0);

		अवरोध;
	शेष:
		dev_warn(dev, "Unknown trigger(%d)\n", cmd);
		ret = -EINVAL;
	पूर्ण
	spin_unlock_irqrestore(&sub->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक uniphier_aio_compr_poपूर्णांकer(काष्ठा snd_soc_component *component,
				      काष्ठा snd_compr_stream *cstream,
				      काष्ठा snd_compr_tstamp *tstamp)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	काष्ठा snd_compr_runसमय *runसमय = cstream->runसमय;
	काष्ठा uniphier_aio *aio = uniphier_priv(asoc_rtd_to_cpu(rtd, 0));
	काष्ठा uniphier_aio_sub *sub = &aio->sub[cstream->direction];
	पूर्णांक bytes = runसमय->fragment_size;
	अचिन्हित दीर्घ flags;
	u32 pos;

	spin_lock_irqsave(&sub->lock, flags);

	aiodma_rb_sync(sub, sub->compr_addr, sub->compr_bytes, bytes);

	अगर (sub->swm->dir == PORT_सूची_OUTPUT) अणु
		pos = sub->rd_offs;
		/* Size of AIO output क्रमmat is द्विगुन of IEC61937 */
		tstamp->copied_total = sub->rd_total / 2;
	पूर्ण अन्यथा अणु
		pos = sub->wr_offs;
		tstamp->copied_total = sub->rd_total;
	पूर्ण
	tstamp->byte_offset = pos;

	spin_unlock_irqrestore(&sub->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक aio_compr_send_to_hw(काष्ठा uniphier_aio_sub *sub,
				अक्षर __user *buf, माप_प्रकार dstsize)
अणु
	u32 __user *srcbuf = (u32 __user *)buf;
	u32 *dstbuf = (u32 *)(sub->compr_area + sub->wr_offs);
	पूर्णांक src = 0, dst = 0, ret;
	u32 frm, frm_a, frm_b;

	जबतक (dstsize > 0) अणु
		ret = get_user(frm, srcbuf + src);
		अगर (ret)
			वापस ret;
		src++;

		frm_a = frm & 0xffff;
		frm_b = (frm >> 16) & 0xffff;

		अगर (frm == IEC61937_HEADER_SIGN) अणु
			frm_a |= 0x01000000;

			/* Next data is Pc and Pd */
			sub->iec_header = true;
		पूर्ण अन्यथा अणु
			u16 pc = be16_to_cpu((__be16)frm_a);

			अगर (sub->iec_header && sub->iec_pc != pc) अणु
				/* Force overग_लिखो IEC frame type */
				sub->iec_pc = pc;
				ret = aio_oport_set_stream_type(sub, pc);
				अगर (ret)
					वापस ret;
			पूर्ण
			sub->iec_header = false;
		पूर्ण
		dstbuf[dst++] = frm_a;
		dstbuf[dst++] = frm_b;

		dstsize -= माप(u32) * 2;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_aio_compr_copy(काष्ठा snd_soc_component *component,
				   काष्ठा snd_compr_stream *cstream,
				   अक्षर __user *buf, माप_प्रकार count)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = cstream->निजी_data;
	काष्ठा snd_compr_runसमय *runसमय = cstream->runसमय;
	काष्ठा device *carddev = rtd->compr->card->dev;
	काष्ठा uniphier_aio *aio = uniphier_priv(asoc_rtd_to_cpu(rtd, 0));
	काष्ठा uniphier_aio_sub *sub = &aio->sub[cstream->direction];
	माप_प्रकार cnt = min_t(माप_प्रकार, count, aio_rb_space_to_end(sub) / 2);
	पूर्णांक bytes = runसमय->fragment_size;
	अचिन्हित दीर्घ flags;
	माप_प्रकार s;
	पूर्णांक ret;

	अगर (cnt < माप(u32))
		वापस 0;

	अगर (sub->swm->dir == PORT_सूची_OUTPUT) अणु
		dma_addr_t dmapos = sub->compr_addr + sub->wr_offs;

		/* Size of AIO output क्रमmat is द्विगुन of IEC61937 */
		s = cnt * 2;

		dma_sync_single_क्रम_cpu(carddev, dmapos, s, DMA_TO_DEVICE);
		ret = aio_compr_send_to_hw(sub, buf, s);
		dma_sync_single_क्रम_device(carddev, dmapos, s, DMA_TO_DEVICE);
	पूर्ण अन्यथा अणु
		dma_addr_t dmapos = sub->compr_addr + sub->rd_offs;

		s = cnt;

		dma_sync_single_क्रम_cpu(carddev, dmapos, s, DMA_FROM_DEVICE);
		ret = copy_to_user(buf, sub->compr_area + sub->rd_offs, s);
		dma_sync_single_क्रम_device(carddev, dmapos, s, DMA_FROM_DEVICE);
	पूर्ण
	अगर (ret)
		वापस -EFAULT;

	spin_lock_irqsave(&sub->lock, flags);

	sub->threshold = 2 * bytes;
	aiodma_rb_set_threshold(sub, sub->compr_bytes, 2 * bytes);

	अगर (sub->swm->dir == PORT_सूची_OUTPUT) अणु
		sub->wr_offs += s;
		अगर (sub->wr_offs >= sub->compr_bytes)
			sub->wr_offs -= sub->compr_bytes;
	पूर्ण अन्यथा अणु
		sub->rd_offs += s;
		अगर (sub->rd_offs >= sub->compr_bytes)
			sub->rd_offs -= sub->compr_bytes;
	पूर्ण
	aiodma_rb_sync(sub, sub->compr_addr, sub->compr_bytes, bytes);

	spin_unlock_irqrestore(&sub->lock, flags);

	वापस cnt;
पूर्ण

अटल पूर्णांक uniphier_aio_compr_get_caps(काष्ठा snd_soc_component *component,
				       काष्ठा snd_compr_stream *cstream,
				       काष्ठा snd_compr_caps *caps)
अणु
	caps->num_codecs = 1;
	caps->min_fragment_size = AUD_MIN_FRAGMENT_SIZE;
	caps->max_fragment_size = AUD_MAX_FRAGMENT_SIZE;
	caps->min_fragments = AUD_MIN_FRAGMENT;
	caps->max_fragments = AUD_MAX_FRAGMENT;
	caps->codecs[0] = SND_AUDIOCODEC_IEC61937;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_compr_codec_caps caps_iec = अणु
	.num_descriptors = 1,
	.descriptor[0].max_ch = 8,
	.descriptor[0].num_sample_rates = 0,
	.descriptor[0].num_bitrates = 0,
	.descriptor[0].profiles = SND_AUDIOPROखाता_IEC61937_SPDIF,
	.descriptor[0].modes = SND_AUDIOMODE_IEC_AC3 |
				SND_AUDIOMODE_IEC_MPEG1 |
				SND_AUDIOMODE_IEC_MP3 |
				SND_AUDIOMODE_IEC_DTS,
	.descriptor[0].क्रमmats = 0,
पूर्ण;

अटल पूर्णांक uniphier_aio_compr_get_codec_caps(काष्ठा snd_soc_component *component,
					     काष्ठा snd_compr_stream *stream,
					     काष्ठा snd_compr_codec_caps *codec)
अणु
	अगर (codec->codec == SND_AUDIOCODEC_IEC61937)
		*codec = caps_iec;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

स्थिर काष्ठा snd_compress_ops uniphier_aio_compress_ops = अणु
	.खोलो           = uniphier_aio_compr_खोलो,
	.मुक्त           = uniphier_aio_compr_मुक्त,
	.get_params     = uniphier_aio_compr_get_params,
	.set_params     = uniphier_aio_compr_set_params,
	.trigger        = uniphier_aio_compr_trigger,
	.poपूर्णांकer        = uniphier_aio_compr_poपूर्णांकer,
	.copy           = uniphier_aio_compr_copy,
	.get_caps       = uniphier_aio_compr_get_caps,
	.get_codec_caps = uniphier_aio_compr_get_codec_caps,
पूर्ण;
