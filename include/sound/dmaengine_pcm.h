<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+
 *
 *  Copyright (C) 2012, Analog Devices Inc.
 *	Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#अगर_अघोषित __SOUND_DMAENGINE_PCM_H__
#घोषणा __SOUND_DMAENGINE_PCM_H__

#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <linux/dmaengine.h>

/**
 * snd_pcm_substream_to_dma_direction - Get dma_transfer_direction क्रम a PCM
 *   substream
 * @substream: PCM substream
 */
अटल अंतरभूत क्रमागत dma_transfer_direction
snd_pcm_substream_to_dma_direction(स्थिर काष्ठा snd_pcm_substream *substream)
अणु
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		वापस DMA_MEM_TO_DEV;
	अन्यथा
		वापस DMA_DEV_TO_MEM;
पूर्ण

पूर्णांक snd_hwparams_to_dma_slave_config(स्थिर काष्ठा snd_pcm_substream *substream,
	स्थिर काष्ठा snd_pcm_hw_params *params, काष्ठा dma_slave_config *slave_config);
पूर्णांक snd_dmaengine_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd);
snd_pcm_uframes_t snd_dmaengine_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream);
snd_pcm_uframes_t snd_dmaengine_pcm_poपूर्णांकer_no_residue(काष्ठा snd_pcm_substream *substream);

पूर्णांक snd_dmaengine_pcm_खोलो(काष्ठा snd_pcm_substream *substream,
	काष्ठा dma_chan *chan);
पूर्णांक snd_dmaengine_pcm_बंद(काष्ठा snd_pcm_substream *substream);

पूर्णांक snd_dmaengine_pcm_खोलो_request_chan(काष्ठा snd_pcm_substream *substream,
	dma_filter_fn filter_fn, व्योम *filter_data);
पूर्णांक snd_dmaengine_pcm_बंद_release_chan(काष्ठा snd_pcm_substream *substream);

काष्ठा dma_chan *snd_dmaengine_pcm_request_channel(dma_filter_fn filter_fn,
	व्योम *filter_data);
काष्ठा dma_chan *snd_dmaengine_pcm_get_chan(काष्ठा snd_pcm_substream *substream);

/*
 * The DAI supports packed transfers, eg 2 16-bit samples in a 32-bit word.
 * If this flag is set the dmaengine driver won't put any restriction on
 * the supported sample क्रमmats and set the DMA transfer size to undefined.
 * The DAI driver is responsible to disable any unsupported क्रमmats in it's
 * configuration and catch corner हालs that are not alपढ़ोy handled in
 * the ALSA core.
 */
#घोषणा SND_DMAENGINE_PCM_DAI_FLAG_PACK BIT(0)

/**
 * काष्ठा snd_dmaengine_dai_dma_data - DAI DMA configuration data
 * @addr: Address of the DAI data source or destination रेजिस्टर.
 * @addr_width: Width of the DAI data source or destination रेजिस्टर.
 * @maxburst: Maximum number of words(note: words, as in units of the
 * src_addr_width member, not bytes) that can be send to or received from the
 * DAI in one burst.
 * @slave_id: Slave requester id क्रम the DMA channel.
 * @filter_data: Custom DMA channel filter data, this will usually be used when
 * requesting the DMA channel.
 * @chan_name: Custom channel name to use when requesting DMA channel.
 * @fअगरo_size: FIFO size of the DAI controller in bytes
 * @flags: PCM_DAI flags, only SND_DMAENGINE_PCM_DAI_FLAG_PACK क्रम now
 * @peripheral_config: peripheral configuration क्रम programming peripheral
 * क्रम dmaengine transfer
 * @peripheral_size: peripheral configuration buffer size
 */
काष्ठा snd_dmaengine_dai_dma_data अणु
	dma_addr_t addr;
	क्रमागत dma_slave_buswidth addr_width;
	u32 maxburst;
	अचिन्हित पूर्णांक slave_id;
	व्योम *filter_data;
	स्थिर अक्षर *chan_name;
	अचिन्हित पूर्णांक fअगरo_size;
	अचिन्हित पूर्णांक flags;
	व्योम *peripheral_config;
	माप_प्रकार peripheral_size;
पूर्ण;

व्योम snd_dmaengine_pcm_set_config_from_dai_data(
	स्थिर काष्ठा snd_pcm_substream *substream,
	स्थिर काष्ठा snd_dmaengine_dai_dma_data *dma_data,
	काष्ठा dma_slave_config *config);

पूर्णांक snd_dmaengine_pcm_refine_runसमय_hwparams(
	काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_dmaengine_dai_dma_data *dma_data,
	काष्ठा snd_pcm_hardware *hw,
	काष्ठा dma_chan *chan);

/*
 * Try to request the DMA channel using compat_request_channel or
 * compat_filter_fn अगर it couldn't be requested through devicetree.
 */
#घोषणा SND_DMAENGINE_PCM_FLAG_COMPAT BIT(0)
/*
 * Don't try to request the DMA channels through devicetree. This flag only
 * makes sense अगर SND_DMAENGINE_PCM_FLAG_COMPAT is set as well.
 */
#घोषणा SND_DMAENGINE_PCM_FLAG_NO_DT BIT(1)
/*
 * The PCM is half duplex and the DMA channel is shared between capture and
 * playback.
 */
#घोषणा SND_DMAENGINE_PCM_FLAG_HALF_DUPLEX BIT(3)

/**
 * काष्ठा snd_dmaengine_pcm_config - Configuration data क्रम dmaengine based PCM
 * @prepare_slave_config: Callback used to fill in the DMA slave_config क्रम a
 *   PCM substream. Will be called from the PCM drivers hwparams callback.
 * @compat_request_channel: Callback to request a DMA channel क्रम platक्रमms
 *   which करो not use devicetree.
 * @process: Callback used to apply processing on samples transferred from/to
 *   user space.
 * @compat_filter_fn: Will be used as the filter function when requesting a
 *  channel क्रम platक्रमms which करो not use devicetree. The filter parameter
 *  will be the DAI's DMA data.
 * @dma_dev: If set, request DMA channel on this device rather than the DAI
 *  device.
 * @chan_names: If set, these custom DMA channel names will be requested at
 *  registration समय.
 * @pcm_hardware: snd_pcm_hardware काष्ठा to be used क्रम the PCM.
 * @pपुनः_स्मृति_buffer_size: Size of the pपुनः_स्मृतिated audio buffer.
 *
 * Note: If both compat_request_channel and compat_filter_fn are set
 * compat_request_channel will be used to request the channel and
 * compat_filter_fn will be ignored. Otherwise the channel will be requested
 * using dma_request_channel with compat_filter_fn as the filter function.
 */
काष्ठा snd_dmaengine_pcm_config अणु
	पूर्णांक (*prepare_slave_config)(काष्ठा snd_pcm_substream *substream,
			काष्ठा snd_pcm_hw_params *params,
			काष्ठा dma_slave_config *slave_config);
	काष्ठा dma_chan *(*compat_request_channel)(
			काष्ठा snd_soc_pcm_runसमय *rtd,
			काष्ठा snd_pcm_substream *substream);
	पूर्णांक (*process)(काष्ठा snd_pcm_substream *substream,
		       पूर्णांक channel, अचिन्हित दीर्घ hwoff,
		       व्योम *buf, अचिन्हित दीर्घ bytes);
	dma_filter_fn compat_filter_fn;
	काष्ठा device *dma_dev;
	स्थिर अक्षर *chan_names[SNDRV_PCM_STREAM_LAST + 1];

	स्थिर काष्ठा snd_pcm_hardware *pcm_hardware;
	अचिन्हित पूर्णांक pपुनः_स्मृति_buffer_size;
पूर्ण;

पूर्णांक snd_dmaengine_pcm_रेजिस्टर(काष्ठा device *dev,
	स्थिर काष्ठा snd_dmaengine_pcm_config *config,
	अचिन्हित पूर्णांक flags);
व्योम snd_dmaengine_pcm_unरेजिस्टर(काष्ठा device *dev);

पूर्णांक devm_snd_dmaengine_pcm_रेजिस्टर(काष्ठा device *dev,
	स्थिर काष्ठा snd_dmaengine_pcm_config *config,
	अचिन्हित पूर्णांक flags);

पूर्णांक snd_dmaengine_pcm_prepare_slave_config(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params,
	काष्ठा dma_slave_config *slave_config);

#घोषणा SND_DMAENGINE_PCM_DRV_NAME "snd_dmaengine_pcm"

काष्ठा dmaengine_pcm अणु
	काष्ठा dma_chan *chan[SNDRV_PCM_STREAM_LAST + 1];
	स्थिर काष्ठा snd_dmaengine_pcm_config *config;
	काष्ठा snd_soc_component component;
	अचिन्हित पूर्णांक flags;
पूर्ण;

अटल अंतरभूत काष्ठा dmaengine_pcm *soc_component_to_pcm(काष्ठा snd_soc_component *p)
अणु
	वापस container_of(p, काष्ठा dmaengine_pcm, component);
पूर्ण
#पूर्ण_अगर
